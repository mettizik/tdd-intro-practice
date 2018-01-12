#include <gtest/gtest.h>
#include <gmock/gmock.h>

class IFileCopier
{
public:
    virtual ~IFileCopier() {}

    virtual void CreateFolder(const std::string& dir) = 0;
    virtual void Copy(const std::string& src, const std::string& dst) = 0;
};

class FolderCopier
{
public:
    explicit FolderCopier(IFileCopier& copier)
        : m_copier(copier)
    {
    }

    virtual void CreateFolder(const std::string& dir)
    {
        m_copier.CreateFolder(dir);
    }

    virtual void Copy(const std::string& src, const std::string& dst)
    {
        if (src.empty() || dst.empty())
        {
            return;
        }
        m_copier.CreateFolder(dst);
        m_copier.Copy(src, dst);
    }

private:
    IFileCopier& m_copier;
};

class MockFileCopier: public IFileCopier
{
public:
    MOCK_METHOD1(CreateFolder, void(const std::string& dir));
    MOCK_METHOD2(Copy, void(const std::string& src, const std::string& dst));
};

TEST(FolderCopier, FolderCopier_Destination_Path_Empty)
{
    MockFileCopier mock;
    FolderCopier copier(mock);

    EXPECT_CALL(mock, Copy(::testing::_, ::testing::_)).Times(0);

    copier.Copy("D:/1", "");
}

TEST(FolderCopier, FolderCopier_Source_Path_Empty)
{
    MockFileCopier mock;
    FolderCopier copier(mock);

    EXPECT_CALL(mock, Copy(::testing::_, ::testing::_)).Times(0);

    copier.Copy("", "E:/1");
}

TEST(FolderCopier, FolderCopier_Create_Directory)
{
    MockFileCopier mock;
    FolderCopier copier(mock);

    EXPECT_CALL(mock, CreateFolder("E:/1")).Times(1);
    EXPECT_CALL(mock, Copy(::testing::_, ::testing::_)).Times(1);

    copier.Copy("D:/1", "E:/1");
}