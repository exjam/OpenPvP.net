#pragma once

#include "types.h"

#include <WinSock2.h>
#include <openssl/ssl.h>

class Packet;

namespace rtmp {
	enum ProtocolControlMessages {
		RTMP_SET_CHUNK_SIZE = 1,
		RTMP_ABORT_MESSAGE,
		RTMP_ACK,
		RTMP_CONTROL,
		RTMP_WINDOW_ACK_SIZE,
		RTMP_SET_PEER_BW,
	};

	struct RTMPPacket;

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
	
		void sendPacket(Packet* pak);
		void sendPacket(RTMPPacket* pak);

	private:
		void onReceivePacket(RTMPPacket* mPacket);

		uint32 startHandshake();
		uint32 waitHandshake(int stage);
		uint32 onReceiveHandshake(Packet* pak);

		bool resolve(const char* host, sockaddr_in& address);

	private:
		SSL* mSSL;
		SOCKET mSocket;
		int mChunkSize;
		int mHandshakeStage;
	};

#pragma pack(push, 1)
	struct PacketHeader : public Serializable {
		//fmt = 0 = abs timestamp, 1-3 = delta
		PacketHeader()
			: mFormat(0), mChunkStreamID(0), mTimeStamp(0), mBodySize(0), mContentType(0), mMessageStreamID(0)
		{
		}

		uint32 mFormat;
		uint32 mChunkStreamID;
		uint32 mTimeStamp;
		uint32 mBodySize;
		uint32 mContentType;
		uint32 mMessageStreamID;

		virtual void serialize(Packet* pak) const;
		virtual void deserialize(Packet* pak);

		static uint32 getHeaderSize(Packet* pak);
	};

	struct RTMPPacket {
		RTMPPacket();
		~RTMPPacket();

		PacketHeader mHeader;
		Packet* mBody;
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
