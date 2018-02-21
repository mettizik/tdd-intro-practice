#pragma once
#include <string>

class IGui
{
public:
    virtual ~IGui() {}
    virtual void Print(const std::string& text) = 0;
    virtual void Exit() = 0;
};
