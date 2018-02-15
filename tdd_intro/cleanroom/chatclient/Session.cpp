#include "Session.h"
#include "ChatUtils.h"
#include "ISocketWrapper.h"
#include "IGui.h"

chat::Session::Session()
{

}

void chat::Session::InitSession(ISocketWrapper& socket, chat::IGui& gui)
{
    try
    {
        details::Connect(socket);
    }
    catch(const std::runtime_error& /*ex*/)
    {
        details::SetupServer(socket);
        gui.Print(GetListenMessage());
    }
}

void chat::details::Connect(ISocketWrapper& socket)
{
    socket.Connect(GetHost(), GetPort());
}

void chat::details::SetupServer(ISocketWrapper& socket)
{
    socket.Bind(GetHost(), GetPort());
    socket.Listen();
}
