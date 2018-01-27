#include <string>
#include <stdint.h>

#include "ChatSession.h"
#include "IGui.h"
#include "ISocketWrapper.h"
#include "ChatSessionUtils.h"

ChatSession::ChatSession(const std::string& host, int16_t port)
    : m_host(host)
    , m_port(port)
{
}

void ChatSession::InitSession(ISocketWrapper& socket, IGui& gui)
{
    try
    {
        Connect(socket);
    }
    catch(const std::runtime_error& /*ex*/)
    {
        SetupServer(socket);
        gui.Print(utils::GetListenMessage());
    }
}

void ChatSession::Connect(ISocketWrapper& socket)
{
    socket.Connect(m_host, m_port);
}

void ChatSession::SetupServer(ISocketWrapper& socket)
{
    socket.Bind(m_host, m_port);
    socket.Listen();
}
