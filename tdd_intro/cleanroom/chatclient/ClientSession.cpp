#include "ClientSession.h"
#include "ISocketWrapper.h"
#include "IGui.h"
#include "sessionutils.h"

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
