#include "ChatSessionBase.h"

ChatSessionBase::ChatSessionBase(ISocketWrapper& socket, IGui& gui, const std::string& nickName)
    : m_gui(gui)
    , m_nick(nickName)
{
}
