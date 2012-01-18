#include <time.h>
#include <iostream>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "ssleay32MDd.lib")
#pragma comment(lib, "libeay32MDd.lib")
#pragma comment(lib, "../Debug/rtmp.lib")

#include "rtmp/client.h"
#include "riotgames/summonerservice.h"

int main(int argc, char** argv){
	const char* url = "rtmps://prod.na1.lol.riotgames.com:2099";
	srand((unsigned int)time(NULL));

	rtmp::Client& client = rtmp::Client::instance();
	if(client.connect(url))
		client.start();
	else
		std::cout << "Could not connect to " << url << std::endl;

	system("pause");

	return 0;
}
