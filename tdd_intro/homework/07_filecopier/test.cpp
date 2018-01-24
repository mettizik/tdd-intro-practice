#include <gtest/gtest.h>
#include <map>
#include "FilesystemUtils.h"

enum class MockFiletype
{
    Directory,
    NormalFile
};

class MockFilesystem : public IFilesystem
{
public:
    using Contents_mt = std::map<PathType, MockFiletype>;

    MockFilesystem(Contents_mt initialContents);
    bool Exists(const PathType &path) const override;

private:
    Contents_mt m_contents;
};

MockFilesystem::MockFilesystem(Contents_mt initialContents)
    : m_contents(std::move(initialContents))
{
}

bool MockFilesystem::Exists(const PathType& path) const
{
    return m_contents.count(path) != 0;
}

TEST(CopyDirectory, returns_nosuchfile_when_source_is_absent)
{
    MockFilesystem fs({});
    EXPECT_EQ(std::errc::no_such_file_or_directory, CopyDirectory(&fs, "/source", "/destination"));
}

TEST(CopyDirectory, returns_notadirectory_when_source_is_not_a_directory)
{
    MockFilesystem fs({{"/source", MockFiletype::NormalFile}});
    EXPECT_EQ(std::errc::not_a_directory, CopyDirectory(&fs, "/source", "/destination"));
}

