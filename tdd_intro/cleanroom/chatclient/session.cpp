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

Session::Session(ISocketWrapper& socket, IGui& gui, const std::string& nickName)
{
    auto socketConnection = InitSession(socket, gui);
    socketConnection->Write(nickName + ":HELLO!");
    std::string handshakeResult;
    socketConnection->Read(handshakeResult);
}

ClientSession::ClientSession(ISocketWrapper& socket, IGui& gui, const std::string& nickName)
{
    auto socketConnection = sessionUtils::Connect(socket);
    socketConnection->Write(nickName + ":HELLO!");
    std::string handshakeResult;
    socketConnection->Read(handshakeResult);
    if (handshakeResult.find("server:HELLO!") == handshakeResult.npos)
    {
        gui.Print(sessionUtils::GetHandshareErrorMessage());
        socketConnection->Close();
    }
}
