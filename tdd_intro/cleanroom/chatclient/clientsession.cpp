#include "clientsession.h"
#include "ISocketWrapper.h"
#include "IGui.h"
#include "sessionutils.h"

ClientSession::ClientSession(ISocketWrapper& socket, IGui& gui, const std::string& nickName)
{
    auto socketConnection = sessionUtils::Connect(socket);
    socketConnection->Write(nickName + ":HELLO!");
}
