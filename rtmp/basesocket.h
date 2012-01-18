#pragma once

#include "types.h"

class BaseSocket {
public:
	virtual ~BaseSocket(){
	}

	virtual bool connect(const char* host, int port) = 0;
	virtual bool disconnect() = 0;

	virtual int read(uint8* data, uint32 length) = 0;
	virtual int write(uint8* data, uint32 length) = 0;

	virtual bool canRead() = 0;
	virtual bool canWrite() = 0;

	virtual int getLastError() = 0;

private:
};
