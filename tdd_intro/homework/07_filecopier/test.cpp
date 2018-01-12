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
            m_copier.CreateFolder(dst);

            for (const auto& item : folderIt)
            {
                const std::string relativePath(item.substr(src.size()));
                const std::string destFullPath(dst + relativePath);

                if (!IsFile(item))
                {
                    Copy(item, dst + item.substr(src.size()));
                }
                else
                {
                    m_copier.Copy(item, destFullPath);
                }
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

using MapFolders = std::map<std::string, FolderList>;
class MockFileCopier: public IFileCopier, public IFolderIterator
{
public:
    MOCK_METHOD1(CreateFolder, void(const std::string& dir));
    MOCK_METHOD2(Copy, void(const std::string& src, const std::string& dst));
    virtual FolderList FileList(const std::string& dir)
    {
        return m_folderList[dir]; // if not exist, create and return empty list
    }

    void SetFolderList(const MapFolders& folderList)
    {
        m_folderList = folderList;
    }

private:
    MapFolders m_folderList;
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

    MapFolders map;
    map["D:/1"] = {"D:/1/file1.txt"};
    mock.SetFolderList(map);

    EXPECT_CALL(mock, CreateFolder("E:/1")).Times(1);
    EXPECT_CALL(mock, Copy("D:/1/file1.txt", "E:/1/file1.txt")).Times(1);

    copier.Copy("D:/1", "E:/1");
}

TEST(FolderCopier, FolderCopier_Copy_2_Files)
{
    MockFileCopier mock;
    FolderCopier copier(mock, mock);

    MapFolders map;
    map["D:/1"] = {"D:/1/file1.txt",
                   "D:/1/file2.txt"};

    mock.SetFolderList(map);

    EXPECT_CALL(mock, CreateFolder("E:/1")).Times(1);
    EXPECT_CALL(mock, Copy("D:/1/file1.txt", "E:/1/file1.txt")).Times(1);
    EXPECT_CALL(mock, Copy("D:/1/file2.txt", "E:/1/file2.txt")).Times(1);

    copier.Copy("D:/1", "E:/1");
}

TEST(FolderCopier, FolderCopier_Copy_1_File_And_1_File_In_Sub_Folder)
{
    MockFileCopier mock;
    FolderCopier copier(mock, mock);

    MapFolders map;
    map["D:/1"] = {"D:/1/file1.txt",
                   "D:/1/2"};

    map["D:/1/2"] = {"D:/1/2/file2.txt"};

    mock.SetFolderList(map);

    EXPECT_CALL(mock, CreateFolder("E:/1")).Times(1);
    EXPECT_CALL(mock, Copy("D:/1/file1.txt", "E:/1/file1.txt")).Times(1);
    EXPECT_CALL(mock, CreateFolder("E:/1/2")).Times(1);
    EXPECT_CALL(mock, Copy("D:/1/2/file2.txt", "E:/1/2/file2.txt")).Times(1);

    copier.Copy("D:/1", "E:/1");
}
