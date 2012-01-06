#include "rtmp.h"
#include "amf/amf0.h"
#include "amf/amf3.h"
#include "bytestream.h"

#include <iostream>
#include <WinSock2.h>
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
		if(!resolve(host, &address))
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

	void Client::send(const uint8* data, uint32 length){
		int result = SSL_write(mSSL, data, length);

		if(result != length)//TODO: throw exception
			printf("send result = %d, should be %u\n", result, length);
	}

	void Client::send(ByteStream& stream){
		send(stream.data(), stream.size());
	}

	void Client::send(Packet& pak){
		static ByteStream bs;
		bs.clear();
	
		pak.mHeader.mBodySize = pak.mData.size();
		pak.mData.chunk(mChunkSize);
		
		pak.serialize(bs);

		send(bs);
		send(pak.mData);
	}

	void Client::onReceivePacket(Packet& pak){
		ByteStream& stream = pak.mData;
		switch(pak.type()){
			case WINDOW_ACK_SIZE:
				{
					uint32 ack_size;
					stream >> ack_size;
					std::cout << "WINDOW_ACK_SIZE: " << ack_size << std::endl;
				}
				break;
			case SET_PEER_BW:
				{
					uint32 bw1; uint8 bw2;
					stream >> bw1 >> bw2;
					std::cout << "SET_PEER_BW: " << bw1 << " " << (uint32)bw2 << std::endl;
				}
				break;
			case AMF0_COMMAND:
				{
					amf::Container result;
					result.deserialize(stream);

					std::cout << "AMF0_COMMAND: " << std::endl;
					std::cout << result.toString() << std::endl;
				}
				break;
			default:
				printf("Unhandled RTMP packet type %u:\n", pak.type());
			
				for(uint32 i = 0; i < stream.size(); ++i)
					printf("%02x ", stream.data()[i]);

				printf("\n");
		};
	}

	uint32 Client::startHandshake(){
		rtmp::HandshakeVersion version = { 3 };
		send((uint8*)&version, sizeof(rtmp::HandshakeVersion));

		rtmp::HandshakeSignature signature;
		memset(&signature, 0, sizeof(rtmp::HandshakeSignature));
		send((uint8*)&signature, sizeof(rtmp::HandshakeSignature));

		return waitHandshake(HS_WAIT_SRV_VERSION);
	}

	uint32 Client::onReceiveHandshake(ByteStream& pak){
		switch(mHandshakeStage){
			case HS_WAIT_SRV_VERSION:
				return waitHandshake(HS_WAIT_SRV_SIGNATURE);
			case HS_WAIT_SRV_SIGNATURE:
				send(pak);
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
				{
					using namespace amf;

					Container connect;
					connect
						<< "connect"
						<< 1.0
						<< object_begin
							<< var("app", "")
							<< var("audioCodecs", 3191)
							<< var("capabilities", 239)
							<< var("flashVer", "WIN 10,1,85,3")
							<< var("fpad", false)
							<< var("objectEncoding", 3)
							<< var("pageUrl", undefined)
							<< var("swfUrl", "app:/mod_ser.dat")
							<< var("tcUrl", "rtmps://prod.na1.lol.riotgames.com:2099")
							<< var("videoCodecs", 252)
							<< var("videoFunction", 1)
						<< object_end;
					
					Packet pak(AMF0_COMMAND);
					connect.serialize(pak.mData);
					send(pak);
				}
				return 1;
			default:
				return 1;
		};
	}

	void Client::recvThread(){
		bool hasHeader = false;
		
		Packet pak;
		ByteStream header;
		ByteStream* read = &header;
		
		pak.mData.reserve(1024);

		header.reserve(16);
		header.setDataSize(startHandshake());

		int result, error = 0;
		do {
			Sleep(20);

			if(read->size() == 0)
				continue;

			result = SSL_read(mSSL, read->data() + read->tell(), read->size() - read->tell());
			if(result == -1 && (error = SSL_get_error(mSSL, result)))
				break;

			read->skip(result);
			if(read->tell() != read->size())
				continue;

			if(mHandshakeStage != HS_COMPLETE){
				read->setDataSize(onReceiveHandshake(*read));
				read->seek(0);
				continue;
			}

			if(!hasHeader){
				uint32 hSize = Packet::getHeaderSize(*read);
				if(read->size() < hSize){
					read->setDataSize(hSize);
					continue;
				}

				read->seek(0);
				pak.deserialize(*read);
				hasHeader = true;

				read = &pak.mData;
				read->seek(0);
				read->setDataSize(pak.mHeader.mBodySize + pak.mHeader.mBodySize / mChunkSize);
			}else{
				read->dechunk(mChunkSize);
				read->seek(0);
				onReceivePacket(pak);
			
				hasHeader = false;

				read = &header;
				read->seek(0);
				read->setDataSize(1);
			}
		} while(error == SSL_ERROR_NONE);
		
		printf("Result: %d, SSL_get_error: %d, WSAGetLastError: %d\n", result, error, WSAGetLastError());
		disconnect();
	}

	bool Client::resolve(const char* host, sockaddr_in* address){
		struct addrinfo *result = NULL;
		struct addrinfo *ptr = NULL;
		struct addrinfo hints;

		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;

		if(int ret = getaddrinfo(host, "0", &hints, &result))
			return false;
		
		for(addrinfo* itr = result; itr != NULL; itr = itr->ai_next){
			if(itr->ai_family != AF_INET) continue;
			*address = *(sockaddr_in*)itr->ai_addr;

			printf("Resolved %s to %d.%d.%d.%d\n", host,address->sin_addr.S_un.S_un_b.s_b1,
				address->sin_addr.S_un.S_un_b.s_b2, address->sin_addr.S_un.S_un_b.s_b3, address->sin_addr.S_un.S_un_b.s_b4);

			return true;
		}

		return false;
	}
};
