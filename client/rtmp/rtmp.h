#pragma once

#include "types.h"

#include <WinSock2.h>
#include <openssl/ssl.h>

class ByteStream;

namespace rtmp {
	class Packet;

	enum ProtocolControlMessages {
		SET_CHUNK_SIZE = 1,
		ABORT_MESSAGE,
		ACKNOWLEDGEMENT,
		CONTROL,
		WINDOW_ACK_SIZE,
		SET_PEER_BW,
		AUDIO = 8,
		VIDEO,
		AMF3_METADATA = 15,
		AMF3_SHARED_OBJECT,
		AMF3_COMMAND,
		AMF0_METADATA,
		AMF0_SHARED_OBJECT,
		AMF0_COMMAND,
		AGGREGATE = 22,
	};

	class Client {
	private:
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
	
		void send(Packet& pak);
		void send(ByteStream& pak);
		void send(const uint8* data, uint32 length);

	private:
		void onReceivePacket(Packet& pak);

		uint32 startHandshake();
		uint32 waitHandshake(int stage);
		uint32 onReceiveHandshake(ByteStream& pak);

		bool resolve(const char* host, sockaddr_in& address);

	private:
		SSL* mSSL;
		SOCKET mSocket;
		int mChunkSize;
		int mHandshakeStage;
	};

#pragma pack(push, 1)
	class Packet : public Serializable {
	public:
		//fmt = 0 = abs timestamp, 1-3 = delta
		Packet(uint8 type = 0);

		struct {
			uint32 mFormat;
			uint32 mChunkStreamID;
			uint32 mTimeStamp;
			uint32 mBodySize;
			uint8 mContentType;
			uint32 mMessageStreamID;
		} mHeader;

		uint8 type() const;

		virtual void serialize(ByteStream& stream) const;
		virtual void deserialize(ByteStream& stream);

		static uint32 getHeaderSize(ByteStream& stream);

		ByteStream mData;
	};

	struct HandshakeVersion {
		uint8 version;
	};

	struct HandshakeSignature {
		union {
			struct {
				uint32 uptime;
				uint32 fms_version;
			};

			uint8 signature[1536];
		};
	};

	struct SetChunkSize {
		uint32 mChunkSize;
	};

	struct AbortMessage {
		uint32 mChunkStreamID;
	};

	struct Acknowledgement {
		uint32 mSequenceID;
	};

	struct Control {
		uint16 mEventType;
		uint8 mEventData[0];
	};

	struct WindowAckSize {
		uint32 mWindowSize;
	};

	struct PeerBandwidth {
		uint32 mWindowSize;
		uint8 mLimitType;
	};
#pragma pack(pop)
}
