#include "clientsession.h"
#include "ISocketWrapper.h"
#include "IGui.h"
#include "sessionutils.h"

ClientSession::ClientSession(ISocketWrapper& socket, IGui& gui, const std::string& nickName)
    : m_gui(gui)
    , m_nick(nickName)
{
    m_socket = sessionUtils::Connect(socket);
}

void ClientSession::PerformHandshake()
{
    sessionUtils::SendHandShake(*m_socket, m_nick);
    sessionUtils::ReadHandShake(*m_socket);
}
