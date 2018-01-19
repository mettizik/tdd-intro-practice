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

    Files dirContent = m_fsys->ReadDir(src);
    if (dirContent.empty())
    {
        return true;
    }
    for (const auto& elem : dirContent)
    {
        m_fsys->CopyFile(src + elem, dst + elem);
    }

    return true;
}
