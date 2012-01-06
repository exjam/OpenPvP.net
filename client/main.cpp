#include "rtmp/rtmp.h"
#include <time.h>
#include <iostream>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "ssleay32MDd.lib")
#pragma comment(lib, "libeay32MDd.lib")
#pragma comment(lib, "../Debug/rtmp.lib")

int main(int argc, char** argv){
	WSADATA wd;
    if(WSAStartup(MAKEWORD(2, 2), &wd) != NO_ERROR){
		std::cout << "Error in WSAStartup" << std::endl;
		return -1;
	}
	
	srand((unsigned int)time(NULL));

	rtmp::Client client;
	client.connect("prod.na1.lol.riotgames.com", 2099);
	client.recvThread();

	system("pause");

	WSACleanup();
	return 0;
}
