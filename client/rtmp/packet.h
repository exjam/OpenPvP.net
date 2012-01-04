#pragma once

#include "types.h"
#include <string.h>

#define MAX_PAK_SIZE 4096

class Packet {
public:
	Packet()
		: mPosition(0), mSize(0), mAllocated(true)
	{
		mData = new uint8[4096];
	}

	Packet(uint32 size, uint8* data)
		: mPosition(0), mSize(size), mData(data), mAllocated(false)
	{
	}

	~Packet(){
		if(mAllocated && mData)
			delete [] mData;
	}

	uint8* data() const {
		return mData;
	}

	uint32 size() const {
		return mSize;
	}

	uint32 position() const {
		return mPosition;
	}

	void seek(uint32 pos){
		mPosition = pos;
	}

	void skip(uint32 skip){
		mPosition += skip;
	}

	void setSize(uint32 size){
		mSize = size;
	}

	template<typename T>
	static Packet create(T& data){
		return Packet((uint32)sizeof(T), (uint8*)&data);
	}

	void add(const char* data, uint32 length){
		add((uint8*)data, length);
	}

	void read(char* data, uint32 length){
		read((uint8*)data, length);
	}

	void add(const uint8* data, uint32 length){
		memcpy(mData + mSize, data, length);
		mSize += length;
	}

	void read(uint8* data, uint32 length){
		memcpy(data, mData + mPosition, length);
		mPosition += length;
	}
	
	//Big Endian
	template<typename T> void add(const T& data){
		uint8* src = (uint8*)&data;
		for(int i = 0; i < sizeof(T); ++i)
			mData[mSize + i] = src[sizeof(T) - 1 - i];

		mSize += sizeof(T);
	}
	
	template<>
	void add(const uint24& data){
		uint32 value = data.value();
		uint8* src = (uint8*)&value;
		mData[mSize + 0] = src[2];
		mData[mSize + 1] = src[1];
		mData[mSize + 2] = src[0];
		mSize += 3;
	}
	
	//Little Endian
	template<typename T>
	void addLE(const T& data){
		memcpy(mData + mSize, &data, sizeof(T));
		mSize += sizeof(T);
	}

	template<>
	void addLE(const uint24& data){
		uint32 value = data.value();
		memcpy(mData + mSize, &value, 3); //-V512
		mSize += 3;
	}

	//Big Endian
	template<typename T>
	T read(){
		T tmp;
		read<T>(tmp);
		return tmp;
	}

	template<typename T>
	void read(T& dest){
		uint8* ptr = (uint8*)&dest;
		for(int i = 0; i < sizeof(T); ++i)
			ptr[i] = mData[sizeof(T) - 1 - i + mPosition];

		mPosition += sizeof(T);
	}

	template<>
	void read(uint24& dest){
		uint32* ptr32 = dest.pointer();
		*ptr32 = 0;

		uint8* ptr = (uint8*)ptr32;
		ptr[0] = mData[2 + mPosition];
		ptr[1] = mData[1 + mPosition];
		ptr[2] = mData[0 + mPosition];
		mPosition += 3;
	}

	//Little Endian
	template<typename T>
	T readLE(){
		T tmp;
		read<T>(tmp);
		return tmp;
	}

	template<typename T>
	void readLE(T& dest){
		memcpy(&dest, mData + mPosition, sizeof(T));
		mPosition += sizeof(T);
	}

	template<>
	void readLE(uint24& dest){
		uint32* ptr = dest.pointer();
		*ptr = 0;

		memcpy(ptr, mData + mPosition, 3); //-V512
		mPosition += 3;
	}

	//Big Endian
	template<typename T>
	T get(uint32 pos){
		T tmp;
		get<T>(pos, tmp);
		return tmp;
	}

	template<typename T>
	void get(uint32 pos, T& dest){
		uint8* ptr = (uint8*)&dest;
		for(int i = 0; i < sizeof(T); ++i)
			ptr[i] = mData[sizeof(T) - 1 - i + pos];
	}

	template<>
	void get(uint32 pos, uint24& dest){
		uint32* ptr32 = dest.pointer();
		*ptr32 = 0;

		uint8* ptr = (uint8*)ptr32;
		ptr[0] = mData[2 + pos];
		ptr[1] = mData[1 + pos];
		ptr[2] = mData[0 + pos];
	}

	//Little Endian
	template<typename T>
	T getLE(uint32 pos){
		T tmp;
		get<T>(pos, tmp);
		return tmp;
	}

	template<typename T>
	void getLE(uint32 pos, T& dest){
		memcpy(&dest, mData + pos, sizeof(T));
	}

	template<>
	void getLE(uint32 pos, uint24& dest){
		uint32* ptr = dest.pointer();
		*ptr = 0;

		memcpy(ptr, mData + pos, 3); //-V512
	}

	//Big Endian
	template<typename T>
	T peek(){
		T tmp;
		get<T>(mPosition, tmp);
		return tmp;
	}

	template<typename T>
	void peek(T& dest){
		get<T>(mPosition, dest);
	}

	//Little Endian
	template<typename T>
	T peekLE(){
		T tmp;
		getLE<T>(mPosition, tmp);
		return tmp;
	}

	template<typename T>
	void peekLE(T& dest){
		getLE<T>(mPosition, dest);
	}

	void chunk(uint32 size){
		if(mSize < size) return;

		for(uint32 i = 0; i < mSize; ++i){
			if(i > 0 && i % size == 0){
				memcpy(mData + i + 1, mData + i, mSize - i);
				mData[i] = 0xC3;
				mSize += 1;
			}
		}
	}

	void dechunk(uint32 size){
		if(mSize < size) return;

		for(uint32 i = 0; i < mSize; ++i){
			if(i > 0 && i % size == 0){
				memcpy(mData + i, mData + i + 1, mSize - i);
				mSize -= 1;
			}
		}
	}

private:
	uint32 mPosition;
	uint32 mSize;
	uint8* mData;
	bool mAllocated;
};
