#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "FileCopier.h"
#include "IFileSystem.h"

class MockFileSystem : public IFileSystem
{
public:
    MOCK_METHOD2(Copy, bool(const std::string&, const std::string&));
};

TEST(FileCopier, EmptySourcePath)
{
    MockFileSystem fsys;
    FileCopier copier(&fsys);

    EXPECT_CALL(fsys, Copy(testing::_, testing::_))
            .Times(0);

    EXPECT_FALSE(copier.Copy("", "C:/"));
}

TEST(FileCopier, EmptyDestinationPath)
{
    MockFileSystem fsys;
    FileCopier copier(&fsys);

    EXPECT_CALL(fsys, Copy(testing::_, testing::_))
            .Times(0);

    EXPECT_FALSE(copier.Copy("C:/", ""));
}
