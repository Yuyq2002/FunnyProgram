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
#define DEFAULT_PORT 12345

class Shared
{
public:
    ~Shared()
    {
        closesocket(sock);
        WSACleanup();
    }

    bool Init(bool is_server = false)
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
        local_addr.sin_addr.S_un.S_addr = INADDR_ANY;
        if (is_server)
        {
            local_addr.sin_port = htons(DEFAULT_PORT);
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


protected:
    WSADATA wsaData;

    sockaddr_in local_addr;
    SOCKET sock = INVALID_SOCKET;
};

struct byte_stream {
    byte_stream() = default;

    int   m_size{ 0 };
    char  m_buffer[1024] = {};
};

struct byte_stream_writer {
    byte_stream_writer(byte_stream& stream)
        : m_stream(stream)
        , m_cursor(stream.m_buffer + stream.m_size)
        , m_end(stream.m_buffer + sizeof(stream.m_buffer))
    {
    }

    template <typename T>
    bool serialize(T value) {
        static_assert(std::is_fundamental_v<T>, "T needs to be a fundamental datatype!");
        if ((m_cursor + sizeof(T)) >= m_end) {
            return false;
        }

        std::memcpy(m_cursor, &value, sizeof(T));
        m_cursor += sizeof(T);
        m_stream.m_size = int32_t(m_cursor - m_stream.m_buffer);
        return true;
    }

    template <typename T>
    bool serialize_enum(T value)
    {
        static_assert(std::is_enum_v<T>, "T is not a enum");

        int convertedValue = (int)value;

        if (!serialize(convertedValue)) return false;

        return true;
    }

    byte_stream& m_stream;
    char* m_cursor{ nullptr };
    char* m_end{ nullptr };
};

struct byte_stream_reader {
    byte_stream_reader(byte_stream& stream)
        : m_stream(stream)
        , m_cursor(stream.m_buffer)
        , m_end(stream.m_buffer + stream.m_size)
    {
    }

    template <typename T>
    bool serialize(T& value) {
        static_assert(std::is_fundamental_v<T>, "T needs to be a fundamental datatype!");
        int a = sizeof(T);
        char* d = (m_cursor + sizeof(T));
        if ((m_cursor + sizeof(T)) > m_end) {
            return false;
        }

        std::memcpy(&value, m_cursor, sizeof(T));
        m_cursor += sizeof(T);
        return true;
    }

    template <typename T>
    bool serialize_enum(T& value)
    {
        static_assert(std::is_enum_v<T>, "T is not a enum");

        int recvValue;

        if (!serialize(recvValue)) return false;

        value = (T)recvValue;

        return true;
    }

    byte_stream& m_stream;
    char* m_cursor{ nullptr };
    char* m_end{ nullptr };
};