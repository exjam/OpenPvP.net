#pragma once

#include "types.h"

#include <vector>
#include <functional>

class ByteStream;
struct sockaddr_in;
typedef struct ssl_st SSL;
typedef __w64 unsigned int SOCKET;

namespace amf {
	class Variant;
};

namespace rtmp {
	class Packet;

	namespace messages {
		class AmfCommand;
	};
	
	typedef std::function<void(amf::Variant*)> CommandCallback;

	class Client {
	private:
		struct CommandIDCallback {
			CommandIDCallback(double id, const CommandCallback& func)
				: mID(id), mFunction(func)
			{
			}

			double mID;
			CommandCallback mFunction;
		};

		enum HANDSHAKE_STAGE {
			HS_WAIT_SRV_VERSION,
			HS_WAIT_SRV_SIGNATURE,
			HS_WAIT_CLI_SIGNATURE,
			HS_COMPLETE,
		};

	public:
		Client();
		~Client();

		bool connect(const char* host, uint16 port);
		void disconnect();

		void recvThread();
	
		void send(Packet* pak);
		void send(ByteStream* pak);
		void send(const uint8* data, uint32 length);

		void send(messages::AmfCommand* command);
		void send(messages::AmfCommand* command, const CommandCallback& onResult);

		void onConnect(amf::Variant* result);

		static Client& instance();

	private:
		uint32 getNextCommandID();

		void onReceivePacket(Packet* pak);

		uint32 startHandshake();
		uint32 waitHandshake(int stage);
		uint32 onReceiveHandshake(ByteStream* pak);

		bool resolve(const char* host, sockaddr_in* address);

		CommandCallback popCallback(double id);
		
	private:
		SSL* mSSL;
		SOCKET mSocket;
		int mChunkSize;
		int mHandshakeStage;
		std::vector<CommandIDCallback> mCallbacks;
	};
};
