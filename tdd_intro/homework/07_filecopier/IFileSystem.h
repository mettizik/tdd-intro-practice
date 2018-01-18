#pragma once

class IFileSystem
{
public:
    virtual ~IFileSystem() {}
    virtual bool CopyFile(const std::string& src, const std::string& dst) = 0;
};
