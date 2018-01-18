#pragma once

class IFileSystem
{
public:
    virtual ~IFileSystem() {}
    virtual bool Copy(const std::string& src, const std::string& dst) = 0;
};
