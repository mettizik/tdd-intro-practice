#include "clientsession.h"
#include "ISocketWrapper.h"
#include "IGui.h"
#include "sessionutils.h"

ClientSession::ClientSession(ISocketWrapper::SockPtr socket)
    : ChatSessionBase(socket)
{
}

std::string ClientSession::PerformHandshake(const std::string& nickname)
{
    sessionUtils::SendHandShake(*m_socket, nickname);
    return sessionUtils::ReadHandShake(*m_socket);
}
