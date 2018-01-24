#include <string>
#include <vector>

using PathType = std::string;
using PathType_vt = std::vector<PathType>;

class IFilesystem
{
public:
    virtual bool Exists(const PathType& path) const = 0;
    virtual bool IsDirectory(const PathType& path) const = 0;
    virtual PathType_vt Childrens(const PathType& path) const = 0;
    virtual void CopyFile(const PathType& src, const PathType& dst) = 0;
};
