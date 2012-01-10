#pragma once

#pragma warning(disable:4200) //zero-sized array

#include <string>

typedef char int8;
typedef short int16;
typedef int int32;

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;

struct uint24 {
	uint24(int value = 0)
		: _value(value), _ptr(nullptr)
	{
	}

	uint24(uint32& src)
		: _ptr(&src)
	{
	}

	uint32* pointer(){
		if(_ptr) return _ptr;
		return &_value;
	}

	uint32 value() const {
		if(_ptr) return *_ptr;
		return _value;
	}

	operator uint32(){
		return _value;
	}

	uint32 _value;
	uint32* _ptr;
};

#include "bytestream.h"

struct Serialisable {
	virtual void serialise(ByteStream& stream) const = 0;
	virtual void deserialise(ByteStream& stream) = 0;
	
	virtual std::string toString() const = 0;
};
