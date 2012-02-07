#pragma once

#include "types.h"
#include "packet.h"
#include "amf/variant.h"

namespace rtmp {
	typedef enum ProtocolControlMessages {
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
	} MessageType;

	class Packet;

	namespace messages {
		#pragma pack(push, 1)
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
		#pragma pack(pop)

		class AmfCommand {
		public:
			virtual Packet* packet() = 0;

			double id();
			void setID(double id);

		protected:
			double mID;
		};

		class Amf0Command : public AmfCommand, protected Packet {
		public:
			static const int Type = AMF0_COMMAND;
			
			Amf0Command(Packet& source);
			Amf0Command(const std::string& name, amf::Variant& object);
			~Amf0Command();

			Packet* packet();
			const std::string& name();
			const amf::Variant& properties();
			const amf::Variant& information();

		protected:
			std::string mName;
			amf::Variant mProperties;
			amf::Variant mInformation;
		};

		class Amf3Command : public AmfCommand, protected Packet {
		public:
			static const int Type = AMF3_COMMAND;
			
			Amf3Command(Packet& source);
			Amf3Command(amf::Variant& object);

			~Amf3Command();

			Packet* packet();
			const amf::Variant& object();

		private:
			amf::Variant mObject;
		};
	};
};

/*
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
*/