#pragma once
#include "vector"

using Files = std::vector<std::string>;

class IFileSystem
{
public:
    virtual ~IFileSystem() {}
    virtual bool IsFile(const std::string& path) = 0;
    virtual Files ReadDir(const std::string& path) = 0;
    virtual bool CopyFile(const std::string& src, const std::string& dst) = 0;
};
