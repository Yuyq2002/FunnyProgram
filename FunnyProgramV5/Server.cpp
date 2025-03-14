#pragma once

#include "Shared.cpp"

class Server : public Shared
{
public:
    void Send(const char* buffer)
    {
        int iResult = sendto(sock, sendbuf, (int)strlen(sendbuf), 0, (SOCKADDR*)&remote_addr, sender_addr_len);
        if (iResult == SOCKET_ERROR) {
            wprintf(L"send failed with error: %d\n", WSAGetLastError());
            WSACleanup();
        }
    }

    void Recv()
    {
        int iResult = recv(sock, recvbuf, DEFAULT_BUFLEN, 0);
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
        char buffer[16] = "";
        if (iResult > 0)
        {
            std::cout << recvbuf << std::endl;
            inet_ntop(AF_INET, &remote_addr, buffer, strlen(buffer));
            std::cout << buffer << std::endl;
        }
        else std::cout << WSAGetLastError() << std::endl;
    }

private:
    sockaddr_in remote_addr;
    int sender_addr_len;

    const char* sendbuf;
    char recvbuf[DEFAULT_BUFLEN] = "";
};