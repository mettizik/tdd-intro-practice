#include "Application.h"
#include "IGui.h"

Application::Application(IChatSession& chat, const std::string& nickname)
    : m_chat(chat)
{
    m_chat.PerformHandshake(nickname);
}

void Application::StartCommunication(IGui& gui)
{
    m_chat.SendMessage(ReadMessage(gui));
    std::string answer;
    m_chat.ReadMessage(answer);
}

std::string Application::ReadMessage(IGui& gui)
{
    gui.Print("me: ");
    return gui.Read();
}
