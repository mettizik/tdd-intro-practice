#include "FilesystemUtils.h"

std::error_code CopyDirectory(IFilesystem* fs, const PathType& src, const PathType& dst)
{
    if (!fs->Exists(src))
    {
        return std::make_error_code(std::errc::no_such_file_or_directory);
    }
    return std::make_error_code(std::errc::not_a_directory);
}
