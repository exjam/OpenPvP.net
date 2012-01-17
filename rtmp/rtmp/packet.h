#pragma once

#include "types.h"
#include "bytestream.h"

namespace rtmp {
	class Packet {
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

		void serialise(ByteStream& stream) const;
		void deserialise(ByteStream& stream);

		static uint32 getHeaderSize(ByteStream& stream);

		ByteStream mData;
	};
};
