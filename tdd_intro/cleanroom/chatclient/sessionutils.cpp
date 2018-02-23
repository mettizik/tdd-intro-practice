#include "sessionutils.h"
#include "clientsession.h"
#include "serversession.h"

const std::string s_host = "localhost";
const int16_t s_port = 4444;
const std::string s_listenMessage = "No one is here…";
const std::string s_hello = ":HELLO!";

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

const std::string sessionUtils::GetHelloMessage()
{
    return s_hello;
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

std::string sessionUtils::ReadHandShake(ISocketWrapper& socket)
{
    std::string buffer;
    socket.Read(buffer);
    size_t nickEnd = buffer.find(sessionUtils::GetHelloMessage());
    if (nickEnd == std::string::npos)
    {
        socket.Close();
        throw std::runtime_error("Invalid handshake message!");
    }

    return buffer.substr(0, nickEnd);
}

void sessionUtils::SendHandShake(ISocketWrapper& socket, const std::string& nickname)
{
    socket.Write(nickname + sessionUtils::GetHelloMessage());
}

IChatSession_ptr sessionUtils::CreateNewSession(ISocketWrapper& socket, IGui& gui)
{
    try
    {
        return std::make_shared<ClientSession>(sessionUtils::Connect(socket));
    }
    catch (const std::exception& )
    {
        gui.Print(sessionUtils::GetListenMessage());
        return std::make_shared<ServerSession>(SetupServer(socket));
    }
}

IChatSession_ptr sessionUtils::StartSession(ISocketWrapper& socket, IGui& gui, const std::string& nickname)
{
    auto session = CreateNewSession(socket, gui);
    session->PerformHandshake(nickname);
    return session;
}
