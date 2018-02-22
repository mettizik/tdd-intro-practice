#include "serversession.h"
#include "ISocketWrapper.h"
#include "IGui.h"
#include "sessionutils.h"


ServerSession::ServerSession(ISocketWrapper& socket, IGui& gui, const std::string& nickName)
    : m_gui(gui)
    , m_nick(nickName)
{
    m_socket = sessionUtils::SetupServer(socket);
    gui.Print(sessionUtils::GetListenMessage());
}

void ServerSession::PerformHandshake()
{
    sessionUtils::ReadHandShake(*m_socket);
    sessionUtils::SendHandShake(*m_socket, m_nick);
}
