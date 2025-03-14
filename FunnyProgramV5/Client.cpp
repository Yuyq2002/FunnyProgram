#pragma once

#include "Shared.cpp"


class Client : public Shared
{
public:
    ~Client()
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

        iResult = bind(sock, (SOCKADDR*)&local_addr, sizeof(local_addr));
        if (iResult == SOCKET_ERROR) {
            wprintf(L"connect failed with error: %d\n", WSAGetLastError());
            closesocket(sock);
            WSACleanup();
            return false;
        }

        return true;
    }

    void Connect()
    {
        std::cout << "Send Connection Message" << std::endl;
        sockaddr_in des;
        ZeroMemory(&des, sizeof(des));
        des.sin_family = AF_INET;
        des.sin_port = htons(DEFAULT_PORT);
        inet_pton(AF_INET, "127.0.0.1", &local_addr.sin_addr.s_addr);

        Send(des, "Connect");
    }

    void Send(const sockaddr_in& des, const char* buffer)
    {
        int iResult = sendto(sock, sendbuf, (int)strlen(sendbuf), 0, (SOCKADDR*)&des, sizeof(des));
        if (iResult == SOCKET_ERROR) {
            wprintf(L"send failed with error: %d\n", WSAGetLastError());
            WSACleanup();
        }
    }

    void Recv()
    {
        int iResult = recv(sock, recvbuf, recvbuflen, 0);
        if (iResult > 0)
        {
            wprintf(L"Bytes received: %d\n", iResult);
            std::cout << recvbuf << std::endl;
        }
    }

private:
    int recvbuflen = DEFAULT_BUFLEN;
    const char* sendbuf;
    char recvbuf[DEFAULT_BUFLEN];
};