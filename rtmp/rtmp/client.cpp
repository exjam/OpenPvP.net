#include "amf/log.h"
#include "amf/amf0.h"
#include "amf/amf3.h"
#include "amf/variant.h"

#include "client.h"
#include "packet.h"
#include "messages.h"
#include "bytestream.h"
#include "socket.h"
#include "securesocket.h"
#include "criticalsection.h"

#include <iostream>
#include <openssl/ssl.h>

namespace rtmp {
	Client::Client()
		: mChunkSize(128), mSocket(nullptr)
	{
		mSendLock = new CriticalSection();
	}

	Client::~Client(){
		disconnect();

		if(mSocket)
			delete mSocket;

		delete mSendLock;
	}

	bool Client::connect(const std::string& url){
		std::string protocol, host, port;
		
		int start = url.find("://");
		if(start == std::string::npos)
			return false;

		protocol = url.substr(0, start);

		int end = url.find_last_of(":");
		if(end == std::string::npos)
			return false;

		host = url.substr(start + 3, end - (start + 3));
		if(host.length() == 0)
			return false;
		
		start = end + 1;
		end = url.find_first_not_of("0123456789", start);
		port = url.substr(start, end - start);

		if(port.length() == 0)
			return false;

		if(protocol.compare("rtmps") == 0)
			mSocket = new SecureSocket();
		else if(protocol.compare("rtmp") == 0)
			mSocket = new Socket();
		else
			return false;

		return mSocket->connect(host.c_str(), atoi(port.c_str()));
	}

	void Client::disconnect(){
		mSocket->disconnect();
	}

	void Client::send(ByteStream* stream){
		mSendLock->lock();
		mSendData.push(new ByteStream(stream));
		mSendLock->unlock();
	}

	void Client::send(Packet* pak){
		static ByteStream bs;
		bs.clear();
	
		pak->mHeader.mBodySize = pak->mData.size();
		pak->mData.chunk(mChunkSize);
		
		pak->serialise(bs);

		send(&bs);
		send(&pak->mData);
	}
	
	void Client::send(messages::AmfCommand* command){
		command->setID(getNextCommandID());
		send(command->packet());
	}

	void Client::send(messages::AmfCommand* command, const CommandCallback& onResult){
		command->setID(getNextCommandID());
		mCallbacks.push_back(CommandIDCallback(command->id(), onResult));
		send(command->packet());
	}

	CommandCallback Client::popCallback(double id){
		for(auto itr = mCallbacks.begin(); itr != mCallbacks.end(); ++itr){
			if(itr->mID == id){
				auto func = itr->mFunction;
				mCallbacks.erase(itr);
				return func;
			}
		}

		return CommandCallback();
	}

	uint32 Client::getNextCommandID(){
		static uint32 id = 1;
		return id++;
	}
	
	Client& Client::instance(){
		static Client client;
		return client;
	}

	void Client::onReceivePacket(Packet* pak){
		ByteStream& stream = pak->mData;
		switch(pak->type()){
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
					messages::Amf0Command command(*pak);
					auto callback = popCallback(command.id());
					if(callback._Empty()){
						std::cout << "Unhandled Amf0Command: " << command.name() << "[" << command.id() << "]" << std::endl;

						amf::log::obj obj;
						obj << command.information() << std::endl;
						std::cout << obj.str() << std::endl;
					}else{
						callback(command.information());
					}
				}
				break;
			case AMF3_COMMAND:
				{
					messages::Amf3Command command(*pak);
					auto callback = popCallback(command.id());
					if(callback._Empty()){
						std::cout << "Unhandled Amf3Command [" << command.id() << "]" << std::endl;

						amf::log::obj obj;
						obj << command.object() << std::endl;
						std::cout << obj.str() << std::endl;
					}else{
						callback(command.object());
					}
				}
				break;
			default:
				printf("Unhandled RTMP packet type %u:\n", pak->type());
			
				for(uint32 i = 0; i < stream.size(); ++i)
					printf("%02x ", stream.data()[i]);

				printf("\n");
		};
	}

	uint32 Client::startHandshake(){
		rtmp::messages::HandshakeVersion version = { 3 };

		ByteStream bs1;
		bs1.write((uint8*)&version, sizeof(rtmp::messages::HandshakeVersion));
		send(&bs1);
		
		rtmp::messages::HandshakeSignature signature;
		memset(&signature, 0, sizeof(rtmp::messages::HandshakeSignature));

		ByteStream bs2;
		bs2.write((uint8*)&signature, sizeof(rtmp::messages::HandshakeSignature));
		send(&bs2);

		return waitHandshake(HS_WAIT_SRV_VERSION);
	}

	uint32 Client::onReceiveHandshake(ByteStream* pak){
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

	void Client::onConnect(amf::Variant* result){
		amf::Object* object = result->toObject();
		std::cout << "connect result: "<< object->get("code")->toString() << std::endl;
	}

	uint32 Client::waitHandshake(int stage){
		mHandshakeStage = stage;

		switch(stage){
			case Client::HS_WAIT_SRV_VERSION:
				return sizeof(rtmp::messages::HandshakeVersion);
			case Client::HS_WAIT_CLI_SIGNATURE:
			case Client::HS_WAIT_SRV_SIGNATURE:
				return sizeof(rtmp::messages::HandshakeSignature);
			case Client::HS_COMPLETE:
				{
					using namespace amf;

					Object object;
					object
						<< var("app", "")
						<< var("audioCodecs", 3191)
						<< var("capabilities", 239)
						<< var("flashVer", "WIN 10,1,85,3")
						<< var("fpad", false)
						<< var("objectEncoding", 3)
						<< var("swfUrl", "app:/mod_ser.dat")
						<< var("tcUrl", "rtmps://prod.na1.lol.riotgames.com:2099")
						<< var("videoCodecs", 252)
						<< var("videoFunction", 1);
					
					send(&messages::Amf0Command("connect", &object), std::bind(&Client::onConnect, this, std::placeholders::_1));
				}
			default:
				return 1;
		};
	}

	void Client::start(){
		bool hasHeader = false;
		
		Packet pak;
		ByteStream header;
		ByteStream* read = &header;
		
		pak.mData.reserve(1024);

		header.reserve(16);
		header.setDataSize(startHandshake());

		bool error = false;
		while(!error){
			if(mSocket->canRead()){
				int result = mSocket->read(read->data() + read->tell(), read->size() - read->tell());

				if(result == -1){
					error = true;
					break;
				}else if(result > 0){
					read->skip(result);
					if(read->tell() != read->size())
						continue;

					if(mHandshakeStage != HS_COMPLETE){
						read->setDataSize(onReceiveHandshake(read));
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
						pak.deserialise(*read);
						hasHeader = true;

						read = &pak.mData;
						read->seek(0);
						read->setDataSize(pak.mHeader.mBodySize + pak.mHeader.mBodySize / mChunkSize);
					}else{
						read->dechunk(mChunkSize);
						read->seek(0);
						onReceivePacket(&pak);
			
						hasHeader = false;

						read = &header;
						read->seek(0);
						read->setDataSize(1);
					}
				}

				if(error)
					break;
			}
		
			if(mSocket->canWrite() && mSendData.size()){
				mSendLock->lock();

				while(mSendData.size()){
					ByteStream* stream = mSendData.front();
					mSocket->write(stream->data(), stream->size());
					delete stream;
					mSendData.pop();
				}

				mSendLock->unlock();
			}
		};
		
		mSocket->getLastError();
		disconnect();
	}
};
