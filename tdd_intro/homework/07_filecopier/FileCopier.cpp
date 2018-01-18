#include "FileCopier.h"


FileCopier::FileCopier(IFileSystem* fsys)
{

}

bool FileCopier::Copy(const std::string& src, const std::string& dst)
{
    if (src.empty() || dst.empty())
    {
        return false;
    }

    return true;
}
