#pragma once
#include <string>

class IGui
{
public:
    virtual ~IGui() {}
    virtual void Print(const std::string& text) = 0;
    virtual std::string Read() = 0;
};
