#pragma once

#include "Shared.h"


class Client : public Shared
{
public:
    void Connect()
    {
        std::cout << "Send Connection Message" << std::endl;
        ZeroMemory(&des, sizeof(des));
        des.sin_family = AF_INET;
        des.sin_port = htons(DEFAULT_PORT);
        if (inet_pton(AF_INET, "10.24.2.14", &des.sin_addr) == 1)
            Send(des, "Connect");
        else std::cout << WSAGetLastError() << std::endl;

        ULONG enable = 1;
        if (ioctlsocket(sock, FIONBIO, &enable) == SOCKET_ERROR)
        {
            std::cout << "ERROR: ENABLING NON-BLOCKING FAILED" << std::endl;
        }
    }

    void Send(const sockaddr_in& des, const char* buffer)
    {
        int iResult = sendto(sock, buffer, (int)strlen(buffer), 0, (SOCKADDR*)&des, sizeof(des));
        if (iResult == SOCKET_ERROR) {
            wprintf(L"send failed with error: %d\n", WSAGetLastError());
            WSACleanup();
        }
    }

    void SendToDest(const char* buffer)
    {
        Send(des, buffer);
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
    sockaddr_in des;
};