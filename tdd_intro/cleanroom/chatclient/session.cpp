#include "session.h"
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
    if (handshakeResult.find_last_of(hello) != handshakeResult.size() - hello.size() - 1)
    {
        socketConnection->Close();
    }
}

ClientSession::ClientSession(ISocketWrapper& socket, IGui& gui, const std::string& nickName)
{
    auto socketConnection = sessionUtils::Connect(socket);
    socketConnection->Write(sessionUtils::GetFullName(nickName));
    std::string handshakeResult;
    socketConnection->Read(handshakeResult);
    if (handshakeResult.find(sessionUtils::GetFullName("server")) == handshakeResult.npos)
    {
        gui.Print(sessionUtils::GetHandshareErrorMessage());
        socketConnection->Close();
    }
}
