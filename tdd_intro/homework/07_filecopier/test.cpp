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
    bool IsDirectory(const PathType& path) const override;
    PathType_vt Childrens(const PathType& path) const override;
    void CopyFile(const PathType& src, const PathType& dst) override;

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

bool MockFilesystem::IsDirectory(const PathType& path) const
{
    return m_contents.find(path)->second == MockFiletype::Directory;
}

PathType_vt MockFilesystem::Childrens(const PathType& path) const
{
    PathType_vt result;
    for (const std::pair<PathType, MockFiletype>& entry : m_contents)
    {
        const PathType& entryPath = entry.first;
        if (entryPath.find(path) != PathType::npos && entryPath != path)
        {
            result.push_back(entryPath);
        }
    }
    return result;
}

void MockFilesystem::CopyFile(const PathType& src, const PathType& dst)
{
    m_contents[dst] = MockFiletype::NormalFile;
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

TEST(CopyDirectory, returns_success_when_source_is_empty)
{
    MockFilesystem fs({{"/source", MockFiletype::Directory}});
    EXPECT_FALSE(CopyDirectory(&fs, "/source", "/destination"));
}

TEST(CopyDirectory, returns_success_and_copies_one_file)
{
    MockFilesystem fs({{"/source", MockFiletype::Directory},
                       {"/source/file", MockFiletype::NormalFile},
                       {"/destination", MockFiletype::Directory}});
    EXPECT_FALSE(CopyDirectory(&fs, "/source", "/destination"));
    EXPECT_EQ(fs.Childrens("/destination"), PathType_vt{"/destination/file"});
}


TEST(CopyDirectory, returns_success_and_skips_subdirectory)
{
    MockFilesystem fs({{"/source", MockFiletype::Directory},
                       {"/source/subdir", MockFiletype::Directory},
                       {"/destination", MockFiletype::Directory}});
    EXPECT_FALSE(CopyDirectory(&fs, "/source", "/destination"));
    EXPECT_EQ(fs.Childrens("/destination"), PathType_vt{});
}
