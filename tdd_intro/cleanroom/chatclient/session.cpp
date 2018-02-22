#include "session.h"
#include "ISocketWrapper.h"
#include "IGui.h"
#include "sessionutils.h"

namespace
{
    const std::string handShakeMagic = ":HELLO!";

    ISocketWrapper::SockPtr InitClient(ISocketWrapper& socket)
    {
            return sessionUtils::Connect(socket);

    }

    ISocketWrapper::SockPtr InitServer(ISocketWrapper& socket)
    {
            return sessionUtils::SetupServer(socket);
    }

    bool CheckHandshake(ISocketWrapper::SockPtr& socket)
    {
        std::string result;
        socket->Read(result);
        size_t magicPosition = result.find(handShakeMagic);
        if (magicPosition == std::string::npos)
        {
            socket->DropSocket();
            return false;
        }
        return true;
    }
}

Session::Session(ISocketWrapper& socket, IGui& gui, const std::string& nickName)
{
    try
    {
        m_socket = InitClient(socket);
        m_socket->Write(nickName + handShakeMagic);
        CheckHandshake(m_socket);
    }
    catch(const std::runtime_error& /*ex*/)
    {
        m_socket = InitServer(socket);
        gui.Print(sessionUtils::GetListenMessage());
        if (CheckHandshake(m_socket))
        {
            m_socket->Write(nickName + handShakeMagic);
            socket.DropSocket();
        }
    }
}
