#include "sessionutils.h"
#include "ISocketWrapper.h"

const std::string s_host = "localhost";
const int16_t s_port = 4444;
const std::string s_listenMessage = "No one is here…";

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

void sessionUtils::Connect(ISocketWrapper& socket)
{
    socket.Connect(s_host, s_port);
}

void sessionUtils::SetupServer(ISocketWrapper& socket)
{
    socket.Bind(s_host, s_port);
    socket.Listen();
}
