#pragma once

#include "types.h"

#include <queue>
#include <vector>
#include <functional>

class ByteStream;

namespace amf {
	class Variant;
};

class Lock;
class BaseSocket;

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

		bool connect(const std::string& url);
		void disconnect();

		void start();

		void send(messages::AmfCommand* command);
		void send(messages::AmfCommand* command, const CommandCallback& onResult);

		void onConnect(amf::Variant* result);

		static Client& instance();
	
	private:
		void send(Packet* pak);
		void send(ByteStream* pak);

	private:
		uint32 getNextCommandID();

		void onReceivePacket(Packet* pak);

		uint32 startHandshake();
		uint32 waitHandshake(int stage);
		uint32 onReceiveHandshake(ByteStream* pak);

		CommandCallback popCallback(double id);
		
	private:
		BaseSocket* mSocket;

		int mChunkSize;
		int mHandshakeStage;

		Lock* mSendLock;
		std::queue<ByteStream*> mSendData;

		std::vector<CommandIDCallback> mCallbacks;
	};
};
