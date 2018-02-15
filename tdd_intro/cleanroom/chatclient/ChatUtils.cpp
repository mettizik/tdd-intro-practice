#include "ChatUtils.h"

const std::string& chat::GetHost()
{
    static const std::string s_host("localhost");
    return s_host;
}

const int chat::GetPort()
{
    return 4444;
}

const std::string& chat::GetListenMessage()
{
    static const std::string s_message("No one is here...");
    return s_message;
}
