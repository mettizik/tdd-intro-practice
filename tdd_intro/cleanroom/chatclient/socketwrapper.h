#pragma once
#include "ISocketWrapper.h"

class SocketWrapper : public ISocketWrapper
{
public:
    SocketWrapper();
    explicit SocketWrapper(SOCKET& other);
    ~SocketWrapper();

    void Bind(const std::string& addr, int16_t port);
    void Listen();
    SockPtr Accept() override;
    virtual SockPtr Connect(const std::string& addr, int16_t port) override;
    void Read(std::string& buffer) override;
    void Write(const std::string& buffer) override;

private:
    SOCKET m_socket;
};
