#include "FileCopier.h"
#include "IFileSystem.h"

namespace
{
    bool IsSameLocation(const std::string& src, const std::string& dst)
    {
        return src.find(dst) != std::string::npos;
    }

    std::string GetFilename(const std::string& path)
    {
        return path.substr(path.rfind('/') + 1);
    }

    void AppendSlashIfNeed(std::string& path)
    {
        if (path.back() != '/')
        {
            path.append("/");
        }
    }
}

FileCopier::FileCopier(IFileSystem* fsys)
    : m_fsys(fsys)
{
}

bool FileCopier::Copy(const std::string& src, const std::string& dst)
{
    if (src.empty() || dst.empty())
    {
        return false;
    }
    if (IsSameLocation(src, dst))
    {
        return true;
    }
    if (m_fsys->IsFile(src))
    {
        m_fsys->CopyFile(src, dst + GetFilename(src));
        return true;
    }

    RecursiveCopy(src, dst);

    return true;
}

void FileCopier::RecursiveCopy(std::string src, std::string dst)
{
    Files dirContent = m_fsys->ReadDir(src);
    if (dirContent.empty())
    {
        return;
    }
    AppendSlashIfNeed(src);
    AppendSlashIfNeed(dst);
    for (const auto& elem : dirContent)
    {
        if (!elem.isDir)
        {
            m_fsys->CopyFile(src + elem.name, dst + elem.name);
        }
        else
        {
            RecursiveCopy(src + elem.name, dst + elem.name);
        }
    }
}
