#pragma once

#include "types.h"
#include "bytestream.h"

namespace rtmp {
	class Packet {
		struct Header {
			uint32 mFormat;
			uint32 mChunkStreamID;
			uint32 mTimeStamp;
			uint32 mBodySize;
			uint8 mContentType;
			uint32 mMessageStreamID;
		};

	public:
		Packet(uint8 type = 0);

		uint8 type() const;

		void serialise(ByteStream& stream) const;
		void deserialise(ByteStream& stream);

		static uint32 getHeaderSize(ByteStream& stream);
		
		Header mHeader;
		ByteStream mData;
		static Header mLastHeader;
	};
};
