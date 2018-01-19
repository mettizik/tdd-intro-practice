#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "FileCopier.h"
#include "IFileSystem.h"

/* Tests list:
 * + copy file
 * + copy folder
 * + copy to the same location file
 * + copy to the same location folder
 * - copy not existing file
 * - copy not existing folder
*/

class MockFileSystem : public IFileSystem
{
public:
    MOCK_METHOD1(IsFile, bool(const std::string&));
    MOCK_METHOD1(ReadDir, Files(const std::string&));
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

    ON_CALL(fsys, IsFile(testing::_))
            .WillByDefault(testing::Return(true));

    EXPECT_CALL(fsys, IsFile("C:/f.txt"))
            .Times(1);
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

TEST(FileCopier, CopyFolderToTheSameLocation)
{
    MockFileSystem fsys;
    FileCopier copier(&fsys);

    EXPECT_CALL(fsys, CopyFile(testing::_, testing::_))
            .Times(0);

    EXPECT_TRUE(copier.Copy("C:/", "C:/"));
}

TEST(FileCopier, CopyEmptyFolder)
{
    MockFileSystem fsys;
    FileCopier copier(&fsys);

    ON_CALL(fsys, ReadDir(testing::_))
            .WillByDefault(testing::Return(Files{}));

    EXPECT_CALL(fsys, ReadDir("C:/"))
            .Times(1);
    EXPECT_CALL(fsys, CopyFile(testing::_, testing::_))
            .Times(0);

    EXPECT_TRUE(copier.Copy("C:/", "D:/"));
}

TEST(FileCopier, CopyFolderWithOneFile)
{
    MockFileSystem fsys;
    FileCopier copier(&fsys);

    ON_CALL(fsys, ReadDir(testing::_))
            .WillByDefault(testing::Return(Files{{false, "img.jpg"}}));

    EXPECT_CALL(fsys, ReadDir("C:/"))
            .Times(1);
    EXPECT_CALL(fsys, CopyFile("C:/img.jpg", "D:/img.jpg"))
            .Times(1);

    EXPECT_TRUE(copier.Copy("C:/", "D:/"));
}

TEST(FileCopier, CopyFolderWithSeveralFiles)
{
    MockFileSystem fsys;
    FileCopier copier(&fsys);

    ON_CALL(fsys, ReadDir(testing::_))
            .WillByDefault(testing::Return(Files{{false, "img.jpg"}, {false, "img2.jpg"}, {false, "img3.jpg"}}));

    EXPECT_CALL(fsys, ReadDir("C:/"))
            .Times(1);
    EXPECT_CALL(fsys, CopyFile("C:/img.jpg", "D:/img.jpg"))
            .Times(1);
    EXPECT_CALL(fsys, CopyFile("C:/img2.jpg", "D:/img2.jpg"))
            .Times(1);
    EXPECT_CALL(fsys, CopyFile("C:/img3.jpg", "D:/img3.jpg"))
            .Times(1);

    EXPECT_TRUE(copier.Copy("C:/", "D:/"));
}

TEST(FileCopier, CopyFolderWithEmptyFolder)
{
    MockFileSystem fsys;
    FileCopier copier(&fsys);

    ON_CALL(fsys, ReadDir("C:/"))
            .WillByDefault(testing::Return(Files{{true, "foto"}}));
    ON_CALL(fsys, ReadDir("C:/foto"))
            .WillByDefault(testing::Return(Files{}));

    EXPECT_CALL(fsys, ReadDir("C:/"))
            .Times(1);
    EXPECT_CALL(fsys, ReadDir("C:/foto"))
            .Times(1);
    EXPECT_CALL(fsys, CopyFile(testing::_, testing::_))
            .Times(0);

    EXPECT_TRUE(copier.Copy("C:/", "D:/"));
}

TEST(FileCopier, CopyFolderWithNotEmptyFolder)
{
    MockFileSystem fsys;
    FileCopier copier(&fsys);

    ON_CALL(fsys, ReadDir("C:/"))
            .WillByDefault(testing::Return(Files{{true, "foto"}}));
    ON_CALL(fsys, ReadDir("C:/foto"))
            .WillByDefault(testing::Return(Files{{false, "img.jpg"}, {false, "img2.jpg"}}));

    EXPECT_CALL(fsys, ReadDir("C:/"))
            .Times(1);
    EXPECT_CALL(fsys, ReadDir("C:/foto"))
            .Times(1);
    EXPECT_CALL(fsys, CopyFile("C:/foto/img.jpg", "D:/foto/img.jpg"))
            .Times(1);
    EXPECT_CALL(fsys, CopyFile("C:/foto/img2.jpg", "D:/foto/img2.jpg"))
            .Times(1);

    EXPECT_TRUE(copier.Copy("C:/", "D:/"));
}

TEST(FileCopier, AcceptanceTest)
{
    MockFileSystem fsys;
    FileCopier copier(&fsys);

    ON_CALL(fsys, ReadDir("C:/"))
            .WillByDefault(testing::Return(Files{{true, "foto"}, {true, "video"}}));
    ON_CALL(fsys, ReadDir("C:/foto"))
            .WillByDefault(testing::Return(Files{{false, "img.jpg"}, {false, "img2.jpg"}}));
    ON_CALL(fsys, ReadDir("C:/video"))
            .WillByDefault(testing::Return(Files{{true, "fun"}, {false, "my.mp4"}}));
    ON_CALL(fsys, ReadDir("C:/video/fun"))
            .WillByDefault(testing::Return(Files{{false, "1.mp4"}, {false, "2.mp4"}}));

    EXPECT_CALL(fsys, ReadDir("C:/"))
            .Times(1);
    EXPECT_CALL(fsys, ReadDir("C:/foto"))
            .Times(1);
    EXPECT_CALL(fsys, ReadDir("C:/video"))
            .Times(1);
    EXPECT_CALL(fsys, ReadDir("C:/video/fun"))
            .Times(1);
    EXPECT_CALL(fsys, CopyFile("C:/foto/img.jpg", "D:/foto/img.jpg"))
            .Times(1);
    EXPECT_CALL(fsys, CopyFile("C:/foto/img2.jpg", "D:/foto/img2.jpg"))
            .Times(1);
    EXPECT_CALL(fsys, CopyFile("C:/video/my.mp4", "D:/video/my.mp4"))
            .Times(1);
    EXPECT_CALL(fsys, CopyFile("C:/video/fun/1.mp4", "D:/video/fun/1.mp4"))
            .Times(1);
    EXPECT_CALL(fsys, CopyFile("C:/video/fun/2.mp4", "D:/video/fun/2.mp4"))
            .Times(1);

    EXPECT_TRUE(copier.Copy("C:/", "D:/"));
}
