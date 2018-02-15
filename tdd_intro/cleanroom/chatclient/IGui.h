#pragma once
#include <string>

namespace chat
{
    class IGui
    {
    public:
        virtual ~IGui() {}
        virtual void Print(const std::string& text) = 0;
    };
}
