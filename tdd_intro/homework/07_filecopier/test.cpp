#include <gtest/gtest.h>

#include <system_error>

using PathType = std::string;

class IFilesystem
{
public:
};

std::error_code CopyDirectory(IFilesystem* fs, const PathType& src, const PathType& dst)
{
    return std::make_error_code(std::errc::no_such_file_or_directory);
}

class MockFilesystem : public IFilesystem
{
public:
};

TEST(CopyDirectory, returns_nosuchfile_when_source_is_absent)
{
    MockFilesystem fs;
    EXPECT_EQ(std::errc::no_such_file_or_directory, CopyDirectory(&fs, "/source", "/destination"));
}

