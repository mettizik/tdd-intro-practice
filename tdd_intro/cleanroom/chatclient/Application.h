#ifndef APPLICATION_H
#define APPLICATION_H

#include "IChatSession.h"
class IGui;

class Application
{
public:
    Application(IChatSession& chat, const std::string& nickname);
    void StartCommunication(IGui& gui);

    std::string ReadMessage(IGui& gui);

private:
    IChatSession& m_chat;
};

#endif // APPLICATION_H
