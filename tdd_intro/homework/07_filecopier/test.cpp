#include <gtest/gtest.h>
#include <gmock/gmock.h>

class IFileCopier
{
public:
    virtual ~IFileCopier() {}
    virtual void Copy(const std::string& src, const std::string& dst) = 0;
};

class FolderCopier
{
public:
    explicit FolderCopier(IFileCopier& copier)
        : m_copier(copier)
    {
    }

    virtual void Copy(const std::string& src, const std::string& dst)
    {
        m_copier.Copy(src, dst);
    }

private:
    IFileCopier& m_copier;
};

class MockFileCopier: public IFileCopier
{
public:
    MOCK_METHOD2(Copy, void(const std::string& src, const std::string& dst));
};

TEST(FolderCopier, FolderCopier_CopyOneFile)
{
    MockFileCopier mock;
    FolderCopier copier(mock);

    EXPECT_CALL(mock, Copy(::testing::_, ::testing::_)).Times(0);

    copier.Copy("D:/1", "");
}
