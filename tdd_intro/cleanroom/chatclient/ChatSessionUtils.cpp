#include "ChatSessionUtils.h"


std::string utils::GetListenMessage()
{
    static const std::string s_listenMessage = "No one is here…";
    return s_listenMessage;
}
