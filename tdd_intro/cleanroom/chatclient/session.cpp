#include "session.h"
#include "ISocketWrapper.h"
#include "IGui.h"
#include "sessionutils.h"

namespace
{
    ISocketWrapper::SockPtr InitClient(ISocketWrapper& socket)
    {
            return sessionUtils::Connect(socket);

    }
    ISocketWrapper::SockPtr InitServer(ISocketWrapper& socket)
    {
            return sessionUtils::SetupServer(socket);
    }
}

Session::Session(ISocketWrapper& socket, IGui& gui, const std::string& nickName)
{
    try
    {
        m_socket = InitClient(socket);
        m_socket->Write(nickName + ":HELLO!");
        std::string result;
        m_socket->Read(result);
    }
    catch(const std::runtime_error& /*ex*/)
    {
        m_socket = InitServer(socket);
        gui.Print(sessionUtils::GetListenMessage());
        std::string result;
        m_socket->Read(result);
        if (result != "metizik:HELLO!")
        {
            m_socket->DropSocket();
        }
        else
        {
            m_socket->Write(nickName + ":HELLO!");
        }
    }
}
