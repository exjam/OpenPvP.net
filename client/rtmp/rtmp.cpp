#include "rtmp.h"
#include "packet.h"

namespace rtmp {
	RTMPPacket::RTMPPacket(){
		mBody = new Packet();
	}

	RTMPPacket::~RTMPPacket(){
		delete mBody;
	}

	void PacketHeader::serialize(Packet* pak) const {
		if(mChunkStreamID < 64){
			pak->add<uint8>(mFormat << 6 | mChunkStreamID);
		}else if(mChunkStreamID < 320){
			pak->add<uint8>(mFormat << 6);
			pak->add<uint8>(mChunkStreamID - 64);
		}else{
			pak->add<uint8>(mFormat << 6 | 1);
			pak->add<uint8>(0xFF & (mChunkStreamID - 64));
			pak->add<uint8>((mChunkStreamID - 64) >> 8);
		}

		if(mFormat <= 2){
			if(mTimeStamp >> 24)
				pak->add<uint24>(0xFFFFFF);
			else
				pak->add<uint24>(mTimeStamp);
		}
		
		if(mFormat <= 1){
			pak->add<uint24>(mBodySize);
			pak->add<uint8>(mContentType);
		}
		
		if(mFormat == 0){
			pak->addLE<uint32>(mMessageStreamID);
		}

		if(mTimeStamp >> 24)
			pak->add<uint32>(mTimeStamp);
	}

	void PacketHeader::deserialize(Packet* pak){
		pak->seek(0);

		uint8 header = pak->read<uint8>();
		mFormat = header >> 6;
		mChunkStreamID = header & 0x3F;

		if(mChunkStreamID == 0){
			mChunkStreamID = pak->read<uint8>() + 64;
		}else if(mChunkStreamID == 1){
			mChunkStreamID = pak->read<uint8>() + 64;
			mChunkStreamID += pak->read<uint8>() << 8;
		}
		
		if(mFormat <= 2){
			mTimeStamp = pak->read<uint24>();
		}

		if(mFormat <= 1){
			mBodySize = pak->read<uint24>();
			mContentType = pak->read<uint8>();
		}
		
		if(mFormat == 0){
			pak->readLE<uint32>(mMessageStreamID);
		}

		if(mTimeStamp == 0xFFFFFF)
			pak->read<uint32>(mTimeStamp);
	}

	uint32 PacketHeader::getHeaderSize(Packet* pak){
		uint32 hSize = 1;
		uint8 header = pak->get<uint8>(0);
		uint8 format = header >> 6;
		uint8 strmID = header & 0x3F;

		if(strmID == 0) hSize += 1;
		else if(strmID == 1) hSize += 2;
	
		uint32 timestamp = 0;
		if(format <= 2){
			hSize += 3;

			if(pak->size() >= hSize)
				pak->get(hSize - 3, timestamp);
		}

		if(format <= 1) hSize += 4;
		if(format == 0) hSize += 4;
		if(timestamp == 0xFFFFFF) hSize += 4;

		return hSize;
	}
};
