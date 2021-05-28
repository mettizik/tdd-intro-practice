#include "ServerSession.h"
#include "ISocketWrapper.h"
#include "IGui.h"
#include "sessionutils.h"

namespace
{
    ISocketWrapper::SockPtr InitSession(ISocketWrapper& socket, IGui& gui)
    {
        try
        {
            return sessionUtils::Connect(socket);
        }
        catch(const std::runtime_error& /*ex*/)
        {
            auto socketServer = sessionUtils::SetupServer(socket);
            gui.Print(sessionUtils::GetListenMessage());
            return socketServer;
        }
    }
}

ServerSession::ServerSession(ISocketWrapper& socket, IGui& gui, const std::string& nickName)
{
    auto socketConnection = InitSession(socket, gui);
    socketConnection->Write(sessionUtils::GetFullName(nickName));
    std::string handshakeResult;
    socketConnection->Read(handshakeResult);
    const std::string hello(sessionUtils::GetFullName(""));
    if (handshakeResult.find(hello) != handshakeResult.size() - hello.size())
    {
        socketConnection->Close();
    }
    else
    {
        socket.Close();
    }
}
