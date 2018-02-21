#include "session.h"
#include "ISocketWrapper.h"
#include "IGui.h"
#include "sessionutils.h"

namespace
{
    ISocketWrapper::SockPtr InitSession(ISocketWrapper& socket, IGui& gui, bool& isClient)
    {
        try
        {
            return sessionUtils::Connect(socket);
        }
        catch(const std::runtime_error& /*ex*/)
        {
            auto socketServer = sessionUtils::SetupServer(socket);
            gui.Print(sessionUtils::GetListenMessage());
            isClient = false;
            return socketServer;
        }
    }

    void WriteHandshake(ISocketWrapper& socket, const std::string& nickName)
    {
        socket.Write(nickName + ":HELLO!");
    }

    void ReadHandshake(ISocketWrapper& socket)
    {
        std::string handshake;
        socket.Read(handshake);
    }
}

Session::Session(ISocketWrapper& socket, IGui& gui, const std::string& nickName)
{
    bool isClient = true;
    auto socketConnection = InitSession(socket, gui, isClient);
    if (isClient)
    {
        WriteHandshake(*socketConnection, nickName);
        ReadHandshake(*socketConnection);
    }
    else
    {
        ReadHandshake(*socketConnection);
        WriteHandshake(*socketConnection, nickName);
    }
}
