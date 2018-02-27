#include "Application.h"
#include "IGui.h"

Application::Application(IChatSession& chat, const std::string& nickname)
    : m_chat(chat)
{
    m_otherNick = m_chat.PerformHandshake(nickname);
}

void Application::ReadMessage(IGui& gui)
{
    gui.Print("me: ");
    m_chat.SendMessage(gui.Read());
}

void Application::DisplayReceivedMessage(IGui& gui)
{
    std::string answer;
    m_chat.ReadMessage(answer);
    gui.Print(m_otherNick + ": " + answer);
}

void StartCommunication(IApplication& app, IGui& gui)
{
    try
    {
        for (;;)
        {
            app.ReadMessage(gui);
            app.DisplayReceivedMessage(gui);
        }
    }
    catch (const std::runtime_error&)
    {
        gui.Print("You are alone now");
    }
}
