#pragma once
#include <memory>
#include <string>

class ISocketWrapper
{
public:
    virtual ~ISocketWrapper() { }
    using SockPtr = std::shared_ptr<ISocketWrapper>;
    virtual SockPtr Connect(const std::string& addr, int16_t port) = 0;
    virtual void Bind(const std::string& addr, int16_t port) = 0;
    virtual void Listen() = 0;
};
