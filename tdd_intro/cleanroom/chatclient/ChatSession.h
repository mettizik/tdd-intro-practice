#pragma once

class ISocketWrapper;
class IGui;

class ChatSession
{
public:
    ChatSession(const std::string& host, int16_t port);

    void InitSession(ISocketWrapper& socket, IGui& gui);

private:
    void Connect(ISocketWrapper& socket);
    void SetupServer(ISocketWrapper& socket);

private:
    const std::string m_host;
    int16_t m_port;
};
