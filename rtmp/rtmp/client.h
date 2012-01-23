#pragma once

#include "types.h"

#include <map>
#include <queue>
#include <vector>
#include <functional>

class ByteStream;

namespace amf {
	class Variant;
};

namespace flex {
	namespace messaging {
		class Consumer;
	};
};

class Lock;
class BaseSocket;

namespace rtmp {
	class Packet;

	namespace messages {
		class AmfCommand;
	};
	
	typedef std::function<void(int, amf::Variant*)> EventCallback;
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

		enum HandshakeStage {
			HS_WAIT_SRV_VERSION,
			HS_WAIT_SRV_SIGNATURE,
			HS_WAIT_CLI_SIGNATURE,
			HS_COMPLETE,
		};

	public:
		enum Event {
			EVT_ERROR,
			EVT_CONNECT,
			EVT_DISCONNECT,
		};

	public:
		Client();
		~Client();

		static Client& instance();
		
		void start();
		bool connect(const std::string& url);
		void disconnect();

		void send(messages::AmfCommand* command);
		void send(messages::AmfCommand* command, const CommandCallback& callback);

		void registerConsumer(flex::messaging::Consumer* consumer);
		void registerEventHandler(const EventCallback& callback);

	private:
		void send(Packet* pak);
		void send(ByteStream* pak);
		void onConnect(amf::Variant* result);

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

		EventCallback mEventCallback;
		std::vector<CommandIDCallback> mCallbacks;
		std::map<std::string, flex::messaging::Consumer*> mConsumers;
	};
};
