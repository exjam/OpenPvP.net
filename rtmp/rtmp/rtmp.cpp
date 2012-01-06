#include "rtmp.h"
#include "bytestream.h"
#include "amf/amf.h"
#include "amf/amf0.h"

ByteStream::endian_t little_endian(ByteStream::LITTLE_ENDIAN);
ByteStream::endian_t big_endian(ByteStream::BIG_ENDIAN);

namespace rtmp {
	Packet::Packet(uint8 type){
		memset(&mHeader, 0, sizeof(mHeader));
		mHeader.mContentType = type;
		mHeader.mChunkStreamID = 3;
	}
	
	uint8 Packet::type() const {
		return mHeader.mContentType;
	}

	void Packet::serialize(ByteStream& stream) const {
		if(mHeader.mChunkStreamID < 64){
			stream << uint8(mHeader.mFormat << 6 | mHeader.mChunkStreamID);
		}else if(mHeader.mChunkStreamID < 320){
			stream << uint8(mHeader.mFormat << 6);
			stream << uint8(mHeader.mChunkStreamID - 64);
		}else{
			stream << uint8(mHeader.mFormat << 6 | 1);
			stream << uint8(0xFF & (mHeader.mChunkStreamID - 64));
			stream << uint8((mHeader.mChunkStreamID - 64) >> 8);
		}

		if(mHeader.mFormat <= 2){
			if(mHeader.mTimeStamp >> 24)
				stream << uint24(0xFFFFFF);
			else
				stream << uint24(mHeader.mTimeStamp);
		}
		
		if(mHeader.mFormat <= 1){
			stream << uint24(mHeader.mBodySize);
			stream << uint8(mHeader.mContentType);
		}
		
		if(mHeader.mFormat == 0)
			stream << little_endian << uint32(mHeader.mMessageStreamID) << big_endian;

		if(mHeader.mTimeStamp >> 24)
			stream << uint32(mHeader.mTimeStamp);
	}

	void Packet::deserialize(ByteStream& stream){
		uint8 header;
		stream >> header;

		mHeader.mFormat = header >> 6;
		mHeader.mChunkStreamID = header & 0x3F;

		if(mHeader.mChunkStreamID <= 1){
			uint8 chunk;
			stream >> chunk;

			if(mHeader.mChunkStreamID == 0){
				mHeader.mChunkStreamID = chunk + 64;
			}else{
				mHeader.mChunkStreamID = chunk + 64;
				stream >> chunk;
				mHeader.mChunkStreamID += chunk << 8;
			}
		}
		
		if(mHeader.mFormat <= 2){
			stream >> uint24(mHeader.mTimeStamp);
		}

		if(mHeader.mFormat <= 1){
			stream >> uint24(mHeader.mBodySize);
			stream >> mHeader.mContentType;
		}
		
		if(mHeader.mFormat == 0)
			stream >> little_endian >> mHeader.mMessageStreamID >> big_endian;

		if(mHeader.mTimeStamp == 0xFFFFFF)
			stream >> mHeader.mTimeStamp;
	}

	uint32 Packet::getHeaderSize(ByteStream& data){
		uint32 pos = data.tell();
		data.seek(0);

		uint32 hSize = 1;
		uint8 header;
		data >> header;

		uint8 format = header >> 6;
		uint8 strmID = header & 0x3F;

		if(strmID == 0) hSize += 1;
		else if(strmID == 1) hSize += 2;
	
		uint32 timestamp = 0;
		if(format <= 2){
			hSize += 3;

			if(data.size() >= hSize){
				data.seek(hSize - 3);
				data >> uint24(timestamp);
			}
		}

		if(format <= 1) hSize += 4;
		if(format == 0) hSize += 4;
		if(timestamp == 0xFFFFFF) hSize += 4;

		data.seek(pos);
		return hSize;
	}

	Amf3Command::Amf3Command(amf::Object* obj)
		: mNumber(0), mObject(obj)
	{
	}

	void Amf3Command::setObject(amf::Object* object){
		mObject = object;
	}

	std::string Amf3Command::toString() const {
		amf::log::obj obj;
		obj << "{ amf3command " << std::endl;
		obj << amf::log::indent;
		obj << mNumber << std::endl;
		obj << mObject->toString() << std::endl;
		obj << amf::log::outdent;
		obj << "}" << std::endl;
		return obj;
	}
	
	void Amf3Command::serialize(ByteStream& stream) const {
		stream << uint8(0);
		stream << uint8(amf0::AMF0_NULL);
		amf0::Number::serialize(mNumber, stream);
		stream << uint8(amf0::AMF0_NULL);
		stream << uint8(amf0::AMF0_AVMPLUS);
		mObject->serialize(stream);
	}

	void Amf3Command::deserialize(ByteStream& stream){
		uint8 unk;
		stream >> unk;
		if(unk != 0)
			throw new amf::DecodeException("First byte of Amf3Command %u != 0", unk);

		amf::Container* container = new amf::Container();
		amf::Entity::setVersion(amf::AMF0);
		container->deserialize(stream);

		uint32 count = container->entityCount();
		if(count != 4)
			throw new amf::DecodeException("Amf3Command child count %u != 4", count);

		mNumber = container->entity(1)->to<double>();
		mObject = container->entity(3)->to<amf::Object*>();
	}
};
