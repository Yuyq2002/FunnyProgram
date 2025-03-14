#pragma once

#include "Shared.h"

class Server : public Shared
{
public:
    void Send(const byte_stream& stream)
    {
        int iResult = sendto(sock, stream.m_buffer, stream.m_size, 0, (SOCKADDR*)&remote_addr, sender_addr_len);
        if (iResult == SOCKET_ERROR) {
            wprintf(L"send failed with error: %d\n", WSAGetLastError());
            WSACleanup();
        }
    }

    void Recv()
    {
        sockaddr remote;
        int addrlen = INET_ADDRSTRLEN;

        ZeroMemory(&recvbuf, DEFAULT_BUFLEN);

        int iResult = recvfrom(sock, recvbuf, DEFAULT_BUFLEN, 0, &remote, &addrlen);
        if (iResult > 0)
        {
            wprintf(L"Bytes received: %d\n", iResult);
            std::cout << recvbuf << std::endl;
        }
    }

    void Listen()
    {
        std::cout << "Start listening" << std::endl;
        sender_addr_len = sizeof(remote_addr);
        int iResult = recvfrom(sock, recvbuf, DEFAULT_BUFLEN, 0, (sockaddr*)&remote_addr, &sender_addr_len);
        char buffer[INET_ADDRSTRLEN] = "";
        if (iResult > 0)
        {
            std::cout << recvbuf << std::endl;
            inet_ntop(AF_INET, &remote_addr.sin_addr, buffer, INET_ADDRSTRLEN);
            std::cout << buffer << std::endl;
        }
        else std::cout << WSAGetLastError() << std::endl;

        ULONG enable = 1;
        if (ioctlsocket(sock, FIONBIO, &enable) == SOCKET_ERROR)
        {
            std::cout << "ERROR: ENABLING NON-BLOCKING FAILED" << std::endl;
        }
    }

private:
    sockaddr_in remote_addr;
    int sender_addr_len;

    char recvbuf[DEFAULT_BUFLEN] = "";
};