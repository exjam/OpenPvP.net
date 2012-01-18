#pragma once

#include "basesocket.h"

#include <winsock2.h>
#include <ws2tcpip.h>

class Socket : public BaseSocket {
public:
	Socket(){
		WSADATA wd;
		WSAStartup(MAKEWORD(2, 2), &wd);

		mSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	}

	virtual ~Socket(){
		closesocket(mSocket);
		WSACleanup();
	}
	
	virtual bool connect(const char* host, int port){
		connectBlocking(host, port);
		
		u_long iMode = 1;
		ioctlsocket(mSocket, FIONBIO, &iMode);

		return true;
	}

	virtual bool disconnect(){
		closesocket(mSocket);
		return true;
	}

	virtual int read(uint8* data, uint32 length){
		return recv(mSocket, (char*)data, length, 0);
	}

	virtual int write(uint8* data, uint32 length){
		return send(mSocket, (const char*)data, length, 0);
	}
	
	virtual bool canRead(){
		fd_set set;
		timeval timeout = { 0, 20000 };

		FD_ZERO(&set);
		FD_SET(mSocket, &set);

		select(1, &set, 0, 0, &timeout);
		return FD_ISSET(mSocket, &set) != 0;
	}

	virtual bool canWrite(){
		fd_set set;
		timeval timeout = { 0, 0 };

		FD_ZERO(&set);
		FD_SET(mSocket, &set);

		select(1, 0, &set, 0, &timeout);
		return FD_ISSET(mSocket, &set) != 0;
	}

	virtual int getLastError(){
		return WSAGetLastError();
	}
	
protected:
	bool connectBlocking(const char* host, int port){
		sockaddr_in address;
		if(!resolve(host, &address))
			return false;

		address.sin_port = htons(port);
		if(int ret = ::connect(mSocket, (SOCKADDR*)&address, sizeof(address)))
			return false;

		return true;
	}

	bool resolve(const char* host, sockaddr_in* address){
		struct addrinfo *result = NULL;
		struct addrinfo *ptr = NULL;
		struct addrinfo hints;

		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;

		if(int ret = getaddrinfo(host, "0", &hints, &result))
			return false;
		
		for(addrinfo* itr = result; itr != NULL; itr = itr->ai_next){
			if(itr->ai_family != AF_INET) continue;
			*address = *(sockaddr_in*)itr->ai_addr;
			return true;
		}

		return false;
	}

protected:
	SOCKET mSocket;
};