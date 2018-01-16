#pragma once

class SocketWrapper
{
public:
    SocketWrapper();
    explicit SocketWrapper(SOCKET& other);
    ~SocketWrapper();

    void Bind(const std::string& addr, int16_t port);
    void Listen();
    SocketWrapper Accept();
    SocketWrapper Connect(const std::string& addr, int16_t port);
    void Read(std::vector<char>& buffer);
    void Write(const std::vector<char>& buffer);

private:
    SOCKET m_socket;
};
