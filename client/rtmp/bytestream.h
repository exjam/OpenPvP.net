#pragma once

#include "types.h"
#include <string.h>

class ByteStream {
public:
	struct endian_t {
		endian_t(uint32 e) : endian(e) {}
		uint32 endian;
	};

	typedef enum {
		BIG_ENDIAN,
		LITTLE_ENDIAN,
	} Endian;

public:
	ByteStream()
		: mDataLength(0), mCursor(0), mBuffer(0), mBufferLength(0), mEndian(BIG_ENDIAN)
	{
	}

	~ByteStream(){}

	template<typename T>
	ByteStream& operator<<(const T& value){
		checkWrite(sizeof(T));

		uint8* src = (uint8*)&value;
		if(mEndian == BIG_ENDIAN){
			for(int i = 0; i < sizeof(T); ++i)
				mBuffer[mDataLength++] = src[sizeof(T) - 1 - i];
		}else if(mEndian == LITTLE_ENDIAN){
			memcpy(mBuffer + mDataLength, src, sizeof(T));
			mDataLength += sizeof(T);
		}

		return *this;
	}

	template<>
	ByteStream& operator<<(const uint24& _value){
		checkWrite(3);

		uint32 value = _value.value();
		uint8* src = (uint8*)&value;

		if(mEndian == BIG_ENDIAN){
			mBuffer[mDataLength + 0] = src[2];
			mBuffer[mDataLength + 1] = src[1];
			mBuffer[mDataLength + 2] = src[0];
		}else if(mEndian == LITTLE_ENDIAN){
			mBuffer[mDataLength + 0] = src[0];
			mBuffer[mDataLength + 1] = src[1];
			mBuffer[mDataLength + 2] = src[2];
		}

		mDataLength += 3;
		return *this;
	}

	template<typename T>
	ByteStream& operator>>(T& value){
		checkRead(sizeof(T));

		uint8* src = (uint8*)&value;
		if(mEndian == BIG_ENDIAN){
			for(int i = 0; i < sizeof(T); ++i)
				src[sizeof(T) - 1 - i] = mBuffer[mCursor++];
		}else if(mEndian == LITTLE_ENDIAN){
			memcpy(src, mBuffer + mCursor, sizeof(T));
			mCursor += sizeof(T);
		}

		return *this;
	}

	template<>
	ByteStream& operator>>(uint24& _value){
		checkRead(3);

		uint8* src = (uint8*)_value.pointer();

		if(mEndian == BIG_ENDIAN){
			src[2] = mBuffer[mCursor + 0];
			src[1] = mBuffer[mCursor + 1];
			src[0] = mBuffer[mCursor + 2];
		}else if(mEndian == LITTLE_ENDIAN){
			src[0] = mBuffer[mCursor + 0];
			src[1] = mBuffer[mCursor + 1];
			src[2] = mBuffer[mCursor + 2];
		}

		mCursor += 3;
		return *this;
	}
	
	template<>
	ByteStream& operator<<(const endian_t& _value){
		mEndian = _value.endian;
		return *this;
	}
	
	template<>
	ByteStream& operator>>(endian_t& _value){
		mEndian = _value.endian;
		return *this;
	}

	ByteStream& read(char* buffer, uint32 length){
		checkRead(length);
		memcpy(buffer, mBuffer + mCursor, length);
		mCursor += length;
		return *this;
	}

	ByteStream& write(uint8* buffer, uint32 length){
		return write((char*)buffer, length);
	}

	ByteStream& write(const char* buffer, uint32 length){
		checkWrite(length);
		memcpy(mBuffer + mDataLength, buffer, length);
		mDataLength += length;
		return *this;
	}

	bool eof(){
		return mCursor >= mDataLength;
	}

	uint32 tell(){
		return mCursor;
	}
	
	uint32 size(){
		return mDataLength;
	}

	uint32 capacity(){
		return mBufferLength;
	}

	uint8 peek(){
		return mBuffer[mCursor];
	}

	void setDataSize(uint32 length){
		mDataLength = length;
		checkWrite(0);
	}
	
	void seek(uint32 pos){
		mCursor = pos;
		checkRead(0);
	}

	void skip(uint32 b){
		mCursor += b;
		checkRead(0);
	}

	void clear(){
		mCursor = 0;
		mDataLength = 0;
	}

	void reserve(uint32 size){
		checkWrite(size);
	}

	uint8* data(){
		return mBuffer;
	}

	void chunk(uint32 size){
		for(uint32 i = size; i < mDataLength; i += size){
			memcpy(mBuffer + i + 1, mBuffer + i, mDataLength - i);
			mBuffer[i] = 0xC3;
			++mDataLength;
			++i;
		}
	}

	void dechunk(uint32 size){
		for(uint32 i = size; i < mDataLength; i += size){
			memcpy(mBuffer + i, mBuffer + i + 1, mDataLength - i);
			--mDataLength;
		}
	}

private:
	void checkRead(uint32 size){
		if(!mBuffer){
			//TODO: throw exception
		}

		if(mCursor + size >= mDataLength){
			//TODO: throw exception
		}
	}

	void checkWrite(uint32 size){
		size += mDataLength;
		if(size < mBufferLength) return;

		while(mBufferLength <= size)
			mBufferLength += BUFFER_SIZE;

		uint8* nbuffer = new uint8[mBufferLength];
		memcpy(nbuffer, mBuffer, mDataLength);

		if(mBuffer)
			delete [] mBuffer;

		mBuffer = nbuffer;
	}

private:
	uint32 mEndian;

	uint32 mCursor;
	uint32 mDataLength;

	uint8* mBuffer;
	uint32 mBufferLength;

	static const int BUFFER_SIZE = 1024;
};

extern ByteStream::endian_t little_endian;
extern ByteStream::endian_t big_endian;
