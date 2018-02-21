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
}

Session::Session(ISocketWrapper& socket, IGui& gui, const std::string& nickName)
{
    bool isClient = true;
    auto socketConnection = InitSession(socket, gui, isClient);
    if (isClient)
    {
        socketConnection->Write(nickName + ":HELLO!");
        std::string handshakeAnswer;
        socketConnection->Read(handshakeAnswer);
    }
    else
    {
        std::string handshake;
        socketConnection->Read(handshake);
        socketConnection->Write(nickName + ":HELLO!");
    }
}
