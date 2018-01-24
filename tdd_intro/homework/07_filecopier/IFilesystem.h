#include <string>

using PathType = std::string;

class IFilesystem
{
public:
    virtual bool Exists(const PathType& path) const = 0;
};
