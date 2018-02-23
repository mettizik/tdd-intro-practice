#include "serversession.h"
#include "ISocketWrapper.h"
#include "IGui.h"
#include "sessionutils.h"


ServerSession::ServerSession(ISocketWrapper::SockPtr socket)
    : ChatSessionBase(socket)
{
}

std::string ServerSession::PerformHandshake(const std::string& nickname)
{
    auto handshake = sessionUtils::ReadHandShake(*m_socket);
    sessionUtils::SendHandShake(*m_socket, nickname);
    return handshake;
}
