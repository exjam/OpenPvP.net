#include "rtmp.h"
#include "packet.h"
#include "amf/amf0.h"
#include "amf/amf3.h"

#include <iostream>
#include <ws2tcpip.h>
#include <openssl/ssl.h>

namespace rtmp {
	Client::Client()
		: mChunkSize(128)
	{
		SSL_library_init();
		SSL_load_error_strings();
		OpenSSL_add_all_digests();
	
		SSL_CTX* ctx = SSL_CTX_new(SSLv23_method());
		SSL_CTX_set_options(ctx, SSL_OP_ALL);
		SSL_CTX_set_default_verify_paths(ctx);

		mSSL = SSL_new(ctx);
		mSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	}

	Client::~Client(){
		disconnect();
	}

	bool Client::connect(const char* host, uint16 port){
		sockaddr_in address;
		if(!resolve(host, address))
			return false;

		address.sin_port = htons(port);
		if(int ret = ::connect(mSocket, (SOCKADDR *)&address, sizeof(address)))
			return false;
		
		SSL_set_fd(mSSL, mSocket);
		int result = SSL_connect(mSSL);
		if(result < 0){
			printf("SSL_connect = %d\n", result);
			return false;
		}

		return true;
	}

	void Client::disconnect(){
		if(mSSL){
			SSL_shutdown(mSSL);
			SSL_free(mSSL);
		}

		if(mSocket)
			closesocket(mSocket);

		mSSL = 0;
		mSocket = 0;
	}

	void Client::sendPacket(Packet* pak){
		int result = SSL_write(mSSL, pak->data(), pak->size());

		if(result != pak->size())
			printf("send result = %d, should be %u\n", result, pak->size());
	}

	void Client::sendPacket(RTMPPacket* pak){
		static Packet* header = new Packet();
		header->seek(0);
		header->setSize(0);
	
		pak->mHeader.mBodySize = pak->mBody->size();

		pak->mBody->chunk(mChunkSize);
		pak->mHeader.serialize(header);

		sendPacket(header);
		sendPacket(pak->mBody);
	}

	void Client::onReceivePacket(RTMPPacket* rtmpPacket){
		Packet* pak = rtmpPacket->mBody;

		switch(rtmpPacket->mHeader.mContentType){
			case rtmp::RTMP_WINDOW_ACK_SIZE:
				printf("RTMP_WINDOW_ACK_SIZE: %d\n", pak->read<uint32>());
				break;
			case rtmp::RTMP_SET_PEER_BW:
				printf("RTMP_SET_PEER_BW: %d %d\n", pak->read<uint32>(), pak->read<uint8>());
				break;
			case 0x14:
				{
					amf::Container result;
					result.deserialize(pak);
					std::cout << result.toString() << std::endl;
					printf("yay\n");
				}
				break;
			default:
				printf("Unhandled RTMP packet type %u:\n", rtmpPacket->mHeader.mContentType);
			
				for(uint32 i = 0; i < pak->size(); ++i)
					printf("%02x ", pak->data()[i]);
				printf("\n");
		};
	}

	uint32 Client::startHandshake(){
		rtmp::HandshakeVersion version = { 3 };
		Packet pak = Packet::create(version);
		sendPacket(&pak);

		rtmp::HandshakeSignature signature;
		memset(&signature, 0, sizeof(rtmp::HandshakeSignature));
		pak = Packet::create(signature);
		sendPacket(&pak);

		return waitHandshake(HS_WAIT_SRV_VERSION);
	}

	uint32 Client::onReceiveHandshake(Packet* pak){
		switch(mHandshakeStage){
			case HS_WAIT_SRV_VERSION:
				return waitHandshake(HS_WAIT_SRV_SIGNATURE);
			case HS_WAIT_SRV_SIGNATURE:
				sendPacket(pak);
				return waitHandshake(HS_WAIT_CLI_SIGNATURE);
			case HS_WAIT_CLI_SIGNATURE:
				return waitHandshake(HS_COMPLETE);
			default:
				return 1;
		};
	}

	uint32 Client::waitHandshake(int stage){
		mHandshakeStage = stage;

		switch(stage){
			case Client::HS_WAIT_SRV_VERSION:
				return sizeof(rtmp::HandshakeVersion);
			case Client::HS_WAIT_CLI_SIGNATURE:
			case Client::HS_WAIT_SRV_SIGNATURE:
				return sizeof(rtmp::HandshakeSignature);
			case Client::HS_COMPLETE:
				//INVOKE CONNECT
				{
					RTMPPacket rtmpPacket;

					//lets try create an AMF0 connect object...
					//connect(transaction_id, command_object, opt_user_args)
					amf0::Container obj;
					obj.add("connect");
					obj.add(1.0);

					amf0::Object* cmdObj = new amf0::Object();
					obj.add(cmdObj);

					cmdObj->set("app", "");
					cmdObj->set("audioCodecs", 3191);
					cmdObj->set("capabilities", 239);
					cmdObj->set("flashVer", "WIN 10,1,85,3");
					cmdObj->set("fpad", false);
					cmdObj->set("objectEncoding", 3);
					cmdObj->set("pageUrl", new amf0::Undefined());
					cmdObj->set("swfUrl", "app:/mod_ser.dat");
					cmdObj->set("tcUrl", "rtmps://prod.na1.lol.riotgames.com:2099");
					cmdObj->set("videoCodecs", 252);
					cmdObj->set("videoFunction", 1);
	
					obj.serialize(rtmpPacket.mBody);

					rtmpPacket.mHeader.mChunkStreamID = 3;
					rtmpPacket.mHeader.mContentType = 0x14;
					rtmpPacket.mHeader.mMessageStreamID = 0;

					sendPacket(&rtmpPacket);
				}
				return 1;
			default:
				return 1;
		};
	}

	void Client::recvThread(){
		bool headerComplete = false;

		RTMPPacket* rtmpPacket = new RTMPPacket();
		Packet* headerPacket = new Packet();

		Packet* readPacket = headerPacket;
		readPacket->setSize(startHandshake());

		int result, error = 0;
		do {
			Sleep(100);

			if(readPacket->size() == 0){
				result = 1;
				continue;
			}

			result = SSL_read(mSSL, &readPacket->data()[readPacket->position()], readPacket->size() - readPacket->position());
			if(result == -1 && (error = SSL_get_error(mSSL, result)))
				break;

			readPacket->skip(result);
			if(readPacket->position() != readPacket->size())
				continue;

			if(mHandshakeStage != HS_COMPLETE){
				readPacket->setSize(onReceiveHandshake(readPacket));
				readPacket->seek(0);
				continue;
			}

			if(!headerComplete){
				uint32 hSize = rtmp::PacketHeader::getHeaderSize(readPacket);
				if(readPacket->size() < hSize){
					readPacket->setSize(hSize);
					continue;
				}

				rtmpPacket->mHeader.deserialize(readPacket);
				headerComplete = true;

				readPacket = rtmpPacket->mBody;
				readPacket->seek(0);
				readPacket->setSize(rtmpPacket->mHeader.mBodySize + rtmpPacket->mHeader.mBodySize / mChunkSize);
			}else{
				readPacket->dechunk(mChunkSize);
				readPacket->seek(0);
				onReceivePacket(rtmpPacket);
			
				headerComplete = false;

				readPacket = headerPacket;
				readPacket->seek(0);
				readPacket->setSize(1);
			}
		} while(error == SSL_ERROR_NONE);
		
		printf("Result: %d, SSL_get_error: %d, WSAGetLastError: %d\n", result, error, WSAGetLastError());
		disconnect();
	}

	bool Client::resolve(const char* host, sockaddr_in& address){
		struct addrinfo *result = NULL;
		struct addrinfo *ptr = NULL;
		struct addrinfo hints;

		ZeroMemory( &hints, sizeof(hints) );
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;

		if(int ret = getaddrinfo(host, "0", &hints, &result))
			return false;
		
		for(addrinfo* itr = result; itr != NULL; itr = itr->ai_next){
			if(itr->ai_family != AF_INET) continue;
			address = *(sockaddr_in*)itr->ai_addr;
			printf("Resolved %s to %d.%d.%d.%d\n", host, address.sin_addr.S_un.S_un_b.s_b1, address.sin_addr.S_un.S_un_b.s_b2, address.sin_addr.S_un.S_un_b.s_b3, address.sin_addr.S_un.S_un_b.s_b4);
			return true;
		}

		return false;
	}
};
