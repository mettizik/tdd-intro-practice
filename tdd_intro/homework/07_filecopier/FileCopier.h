#pragma once
#include <string>

class IFileSystem;

class FileCopier
{
public:
    explicit FileCopier(IFileSystem* fsys);
    bool Copy(const std::string& src, const std::string& dst);

private:
    IFileSystem* m_fsys;
};
