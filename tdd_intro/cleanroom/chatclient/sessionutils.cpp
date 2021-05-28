#include "sessionutils.h"
#include "ISocketWrapper.h"

const std::string s_host = "localhost";
const int16_t s_port = 4444;
const std::string s_listenMessage = "No one is here…";
const std::string s_handshakeMessage = "Handshake invalid…";
static const std::string s_hello = ":HELLO!";

const std::string sessionUtils::GetHost()
{
    return s_host;
}

const int16_t sessionUtils::GetPort()
{
    return s_port;
}

const std::string sessionUtils::GetListenMessage()
{
    return s_listenMessage;
}

const std::string sessionUtils::GetHandshareErrorMessage()
{
    return s_handshakeMessage;
}

const std::string sessionUtils::GetFullName(const std::string& userName)
{
    return userName + s_hello;
}

ISocketWrapper::SockPtr sessionUtils::Connect(ISocketWrapper& socket)
{
    return socket.Connect(s_host, s_port);
}

ISocketWrapper::SockPtr sessionUtils::SetupServer(ISocketWrapper& socket)
{
    socket.Bind(s_host, s_port);
    socket.Listen();
    return socket.Accept();
}
