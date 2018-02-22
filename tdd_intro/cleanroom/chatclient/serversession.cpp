#include "serversession.h"
#include "ISocketWrapper.h"
#include "IGui.h"
#include "sessionutils.h"


ServerSession::ServerSession(ISocketWrapper::SockPtr socket)
    : ChatSessionBase(socket)
{
}

ServerSession::ServerSession(ISocketWrapper& socket)
    : ChatSessionBase(nullptr)
{
    m_socket = sessionUtils::SetupServer(socket);
    //gui.Print(sessionUtils::GetListenMessage());
}

void ServerSession::PerformHandshake(const std::string& nickname)
{
    sessionUtils::ReadHandShake(*m_socket);
    sessionUtils::SendHandShake(*m_socket, nickname);
}
