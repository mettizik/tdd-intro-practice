#pragma once

class ISocketWrapper;
class IGui;

class Session
{
    public:
        Session(ISocketWrapper& socket, IGui& gui);
};
