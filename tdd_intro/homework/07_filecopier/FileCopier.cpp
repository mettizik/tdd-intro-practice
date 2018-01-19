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
        if (!elem.isDir)
        {
            m_fsys->CopyFile(src + elem.name, dst + elem.name);
        }
        else
        {
            Files dirContent2 = m_fsys->ReadDir(src + elem.name);
            if (dirContent2.empty())
            {
                continue;
            }
            for (const auto& elem2 : dirContent2)
            {
                if (!elem2.isDir)
                {
                    m_fsys->CopyFile(src + elem.name + '/' + elem2.name, dst + elem.name + '/' + elem2.name);
                }
            }
        }
    }

    return true;
}
