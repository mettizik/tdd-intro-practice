#ifndef APPLICATION_H
#define APPLICATION_H

#include "IChatSession.h"
class IGui;

class IApplication
{
public:
    virtual ~IApplication(){}
    virtual void ReadMessage(IGui& gui) = 0;
    virtual void DisplayReceivedMessage(IGui& gui) = 0;
};

class Application : public IApplication
{
public:
    Application(IChatSession& chat, const std::string& nickname);
    virtual void ReadMessage(IGui& gui) override;
    virtual void DisplayReceivedMessage(IGui& gui) override;

private:
    IChatSession& m_chat;
    std::string m_otherNick;
};

void StartCommunication(IApplication& app, IGui& gui);

#endif // APPLICATION_H
