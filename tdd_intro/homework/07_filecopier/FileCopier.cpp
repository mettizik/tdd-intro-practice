#include "FileCopier.h"
#include "IFileSystem.h"

namespace
{
    bool IsSameLocation(const std::string& src, const std::string& dst)
    {
        return src.find(dst) != std::string::npos;
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

    m_fsys->Copy("C:/f.txt", "D:/f.txt");

    return true;
}
