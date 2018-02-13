#include "Session.h"

namespace
{
    const std::string s_host = "localhost";
    const int16_t s_port = 4444;
    const std::string s_listenMessage = "No one is here…";
}

Session::Session()
{
}

void Session::InitSession(ISocketWrapper& socket, IGui& gui)
{
    bool connectFailed = false;
    try
    {
        utils::Connect(socket);
    }
    catch(const std::runtime_error& /*ex*/)
    {
        connectFailed = true;
    }
    if (connectFailed)
    {
        try
        {
            utils::SetupServer(socket);
            gui.Print(s_listenMessage);
        }
        catch(const std::runtime_error& /*ex*/)
        {
            return;
        }
    }
}

void utils::Connect(ISocketWrapper& socket)
{
    socket.Connect(s_host, s_port);
}

void utils::SetupServer(ISocketWrapper& socket)
{
    socket.Bind(s_host, s_port);
    socket.Listen();
}
