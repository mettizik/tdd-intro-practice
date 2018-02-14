#include "session.h"
#include "ISocketWrapper.h"
#include "IGui.h"
#include "sessionutils.h"

namespace
{
    void InitSession(ISocketWrapper& socket, IGui& gui)
    {
        try
        {
            sessionUtils::Connect(socket);
        }
        catch(const std::runtime_error& /*ex*/)
        {
            sessionUtils::SetupServer(socket);
            gui.Print(sessionUtils::GetListenMessage());
        }
    }
}

Session::Session(ISocketWrapper& socket, IGui& gui)
{
    InitSession(socket, gui);
}
