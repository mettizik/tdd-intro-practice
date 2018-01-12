#include <gtest/gtest.h>
#include <gmock/gmock.h>

class IFileCopier
{
public:
    virtual ~IFileCopier() {}

    virtual void CreateFolder(const std::string& dir) = 0;
    virtual void Copy(const std::string& src, const std::string& dst) = 0;
};

using FolderList = std::vector<std::string>;
class IFolderIterator
{
public:
    virtual ~IFolderIterator() {}

    virtual FolderList FileList(const std::string& dir) = 0;
};

class FolderCopier
{
public:
    FolderCopier(IFileCopier& copier, IFolderIterator& folderIt)
        : m_copier(copier)
        , m_folderIt(folderIt)
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
        const FolderList& folderIt = m_folderIt.FileList(src);
        if (!folderIt.empty())
        {
            const std::string& item = folderIt[0];
            const std::string relativePath(item.substr(src.size()));
            const std::string destFullPath(dst + relativePath);
            std::string absolutePath(destFullPath);

            if (IsFile(absolutePath))
            {
                absolutePath = AbsolutePath(absolutePath);
            }
            m_copier.CreateFolder(absolutePath);
            m_copier.Copy(item, destFullPath);

            if (folderIt.size() > 1)
            {
                const std::string& item2 = folderIt[1];
                const std::string relativePath2(item2.substr(src.size()));
                const std::string destFullPath2(dst + relativePath2);

                m_copier.Copy(item2, destFullPath2);
            }
        }
    }

    bool IsFile(const std::string& path) const
    {
        return path.find(".") != std::string::npos; // simple check of file
    }

    std::string AbsolutePath(const std::string& path) const
    {
        return path.substr(0, path.find_last_of("/")); // simply check, not real
    }

private:
    IFileCopier& m_copier;
    IFolderIterator& m_folderIt;
};

class MockFileCopier: public IFileCopier, public IFolderIterator
{
public:
    MOCK_METHOD1(CreateFolder, void(const std::string& dir));
    MOCK_METHOD2(Copy, void(const std::string& src, const std::string& dst));
    virtual FolderList FileList(const std::string& /*dir*/)
    {
        return m_folderList;
    }

    void SetFolderList(const FolderList& folderList)
    {
        m_folderList = folderList;
    }

private:
    FolderList m_folderList;
};

TEST(FolderCopier, FolderCopier_Destination_Path_Empty)
{
    MockFileCopier mock;
    FolderCopier copier(mock, mock);

    EXPECT_CALL(mock, Copy(::testing::_, ::testing::_)).Times(0);

    copier.Copy("D:/1", "");
}

TEST(FolderCopier, FolderCopier_Source_Path_Empty)
{
    MockFileCopier mock;
    FolderCopier copier(mock, mock);

    EXPECT_CALL(mock, Copy(::testing::_, ::testing::_)).Times(0);

    copier.Copy("", "E:/1");
}

TEST(FolderCopier, FolderCopier_Create_Directory)
{
    MockFileCopier mock;
    FolderCopier copier(mock, mock);

    EXPECT_CALL(mock, CreateFolder(::testing::_)).Times(0);
    EXPECT_CALL(mock, Copy(::testing::_, ::testing::_)).Times(0);

    copier.Copy("D:/1", "E:/1");
}

TEST(FolderCopier, FolderCopier_Copy_One_File)
{
    MockFileCopier mock;
    FolderCopier copier(mock, mock);

    mock.SetFolderList({"D:/1/file1.txt"});

    EXPECT_CALL(mock, CreateFolder("E:/1")).Times(1);
    EXPECT_CALL(mock, Copy("D:/1/file1.txt", "E:/1/file1.txt")).Times(1);

    copier.Copy("D:/1", "E:/1");
}

TEST(FolderCopier, FolderCopier_Copy_2_Files)
{
    MockFileCopier mock;
    FolderCopier copier(mock, mock);

    mock.SetFolderList({"D:/1/file1.txt",
                        "D:/1/file2.txt"});

    EXPECT_CALL(mock, CreateFolder("E:/1")).Times(1);
    EXPECT_CALL(mock, Copy("D:/1/file1.txt", "E:/1/file1.txt")).Times(1);
    EXPECT_CALL(mock, Copy("D:/1/file2.txt", "E:/1/file2.txt")).Times(1);

    copier.Copy("D:/1", "E:/1");
}
