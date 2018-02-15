#pragma once
#include <string>

class ISocketWrapper;

namespace chat
{
    class IGui;

    class Session
    {
    public:
        Session();
        void InitSession(ISocketWrapper& socket, IGui& gui);
    };

    namespace details
    {
        void Connect(ISocketWrapper& socket);
        void SetupServer(ISocketWrapper& socket);
    }
}
