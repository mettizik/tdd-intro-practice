#include "clientsession.h"
#include "ISocketWrapper.h"
#include "IGui.h"
#include "sessionutils.h"

ClientSession::ClientSession(ISocketWrapper::SockPtr socket)
    : ChatSessionBase(socket)
{
}

ClientSession::ClientSession(ISocketWrapper& socket)
    : ChatSessionBase(nullptr)
{
    m_socket = sessionUtils::Connect(socket);
}

void ClientSession::PerformHandshake(const std::string& nickname)
{
    sessionUtils::SendHandShake(*m_socket, nickname);
    sessionUtils::ReadHandShake(*m_socket);
}
