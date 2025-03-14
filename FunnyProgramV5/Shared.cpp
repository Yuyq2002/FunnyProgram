#pragma once

#define WIN32_LEAN_AND_MEAN

#include <iostream>

#include <iostream>
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <stdio.h>

// Link with ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT 27015

class Shared
{
public:
	~Shared()
	{
		closesocket(sock);
		WSACleanup();
	}

    bool Init()
    {
        int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (iResult != NO_ERROR) {
            wprintf(L"WSAStartup failed with error: %d\n", iResult);
            return false;
        }

        sock = socket(AF_INET, SOCK_DGRAM, 0);
        if (sock == INVALID_SOCKET) {
            wprintf(L"socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            return false;
        }

        local_addr.sin_family = AF_INET;
        inet_pton(AF_INET, "127.0.0.1", &local_addr.sin_addr.s_addr);
        local_addr.sin_port = htons(DEFAULT_PORT); 

        iResult = bind(sock, (SOCKADDR*)&local_addr, sizeof(local_addr));
        if (iResult == SOCKET_ERROR) {
            wprintf(L"connect failed with error: %d\n", WSAGetLastError());
            closesocket(sock);
            WSACleanup();
            return false;
        }

        return true;
    }


protected:
	WSADATA wsaData;

	sockaddr_in local_addr;
	SOCKET sock = INVALID_SOCKET;
};