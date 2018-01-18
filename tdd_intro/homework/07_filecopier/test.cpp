#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "FileCopier.h"
#include "IFileSystem.h"

/* Tests list:
 * + copy file
 * - copy folder
 * + copy to the same location file
 * - copy to the same location folder
 * - copy not existing file
 * - copy not existing folder
*/

class MockFileSystem : public IFileSystem
{
public:
    MOCK_METHOD2(CopyFile, bool(const std::string&, const std::string&));
};

TEST(FileCopier, EmptySourcePath)
{
    MockFileSystem fsys;
    FileCopier copier(&fsys);

    EXPECT_CALL(fsys, CopyFile(testing::_, testing::_))
            .Times(0);

    EXPECT_FALSE(copier.Copy("", "C:/"));
}

TEST(FileCopier, EmptyDestinationPath)
{
    MockFileSystem fsys;
    FileCopier copier(&fsys);

    EXPECT_CALL(fsys, CopyFile(testing::_, testing::_))
            .Times(0);

    EXPECT_FALSE(copier.Copy("C:/", ""));
}

TEST(FileCopier, CopyOneFile)
{
    MockFileSystem fsys;
    FileCopier copier(&fsys);

    EXPECT_CALL(fsys, CopyFile("C:/f.txt", "D:/f.txt"))
            .Times(1);

    EXPECT_TRUE(copier.Copy("C:/f.txt", "D:/"));
}

TEST(FileCopier, CopyOneFileToTheSameLocation)
{
    MockFileSystem fsys;
    FileCopier copier(&fsys);

    EXPECT_CALL(fsys, CopyFile(testing::_, testing::_))
            .Times(0);

    EXPECT_TRUE(copier.Copy("C:/f.txt", "C:/"));
}
