#include <gtest/gtest.h>
#include <gmock/gmock.h>

class IFileCopier
{
public:
    virtual ~IFileCopier() {}
    virtual void Copy(const std::string& src, const std::string& dst) = 0;
};

class MockFileCopier: public IFileCopier
{
public:
    MOCK_METHOD2(Copy, void(const std::string& src, const std::string& dst));
};

TEST(FolderCopier, FolderCopier_CopyOneFile)
{
    MockFileCopier mock;

    EXPECT_CALL(mock, Copy(::testing::_, ::testing::_)).WillOnce(::testing::Return());

    mock.Copy("D:/", "E:/");
}
