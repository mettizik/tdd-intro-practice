#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(FolderCopier, FolderCopier_CopyOneFile)
{
    MockFileCopier mock;

    EXPECT_CALL(mock, Copy(_, _)).WillOnce(&ReturnsVoid);

    mock.Copy("D:/", "E:/");
}
