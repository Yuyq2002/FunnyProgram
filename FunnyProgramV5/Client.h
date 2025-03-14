#pragma once

#include "Shared.h"
#include "InputSystem.h"


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
        byte_stream stream;
        sockaddr remote;
        int sender_addr_len = sizeof(remote);

        int iResult = recvfrom(sock, stream.m_buffer, 1024, 0, &remote, &sender_addr_len);
        if (iResult > 0)
        {
            stream.m_size = iResult;
            byte_stream_reader reader(stream);

            int vInt = 0;
            bool vBool = false;

            std::vector<INPUT> input;

            while (true)
            {
                if (reader.serialize(vInt) && reader.serialize(vBool))
                {
                    std::cout << vInt << " - " << vBool << std::endl;
                    INPUT new_input;
                    ZeroMemory(&new_input, sizeof(new_input));
                    new_input.type = INPUT_KEYBOARD;
                    new_input.ki.wVk = vInt;
                    if(!vBool)
                        new_input.ki.dwFlags = KEYEVENTF_KEYUP;
                    input.push_back(new_input);
                }
                else
                {
                    break;
                }
            }
            if (SendInput(input.size(), input.data(), sizeof(INPUT)))
            {
                std::cout << "Uppps some error in SendInput: " << GetLastError() << std::endl;
            }

            std::cout << "-------------------------------------------------" << std::endl;
        }
    }

private:
    int recvbuflen = DEFAULT_BUFLEN;
    const char* sendbuf;
    char recvbuf[DEFAULT_BUFLEN];
    sockaddr_in des;
};