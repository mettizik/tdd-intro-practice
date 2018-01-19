#include "stdafx.h"
#include "filemock.h"

/*
Implement a class for recursively copying files from source directory to the destination directory.

A folder hierarchy and file names must be saved.

Empty folders should not be copied at all.

For example it can be something that looks like a

class IFileCopier
{
public:
    virtual void Copy(const std::string& src, const std::string& dst) = 0;
};
You don't need to test filesystem functions. To work with a filesystem you should declare an interface and to mock it.
 */

/*
 Test list:
1. Copied 1 file
2. Copied 1 dir and 1 file in it
3. Copied 1 dir and 2+ file in it
4. Not copied empty dir
5. Copied parrent dir, not copied empty child dir
*/

/*
Needed file interface with such methods:
class IFile
{
    ~IFile(){}
    bool IsDir();
    const ChildFiles& GetChildrens() = 0;
    IFile GetParent();
    void AddChild(IFile&&);
}
*/

class FileCopier
{
public:
    static void Copy(IFile::IFileGuard src, IFile::IFileGuard parentDst)
    {
        if (src->IsDir() && src->GetChildrens().empty())
        {
            return;
        }
        parentDst->AddChild(src->Copy());
    }
};

TEST(FileCopier, CopyCopiesOneFile)
{
    FileMock::FileMockGuard fileToCopy = std::make_shared<FileMock>("fileName");
    FileMock::FileMockGuard parentDist = std::make_shared<FileMock>("parent");
    FileCopier::Copy(fileToCopy, parentDist);
    EXPECT_EQ(1, parentDist->GetChildrens().size());
}

TEST(FileCopier, CopyCopiesOneFileWithSavingNameOfCopiedFile)
{
    std::string copiedFileName = "fileName";
    FileMock::FileMockGuard fileToCopy = std::make_shared<FileMock>(copiedFileName);
    FileMock::FileMockGuard parentDist = std::make_shared<FileMock>("parent");
    FileCopier::Copy(fileToCopy, parentDist);
    EXPECT_EQ(copiedFileName, parentDist->GetChildrens().front()->GetName());
}

TEST(FileCopier, CopyCopiesOneFileAndMockChangesItsStateToCopied)
{
    FileMock::FileMockGuard fileToCopy = std::make_shared<FileMock>("fileName", true);
    FileMock::FileMockGuard parentDist = std::make_shared<FileMock>("parent", false);
    FileCopier::Copy(fileToCopy, parentDist);
    fileToCopy->CheckCopied();
}

TEST(FileCopier, CopyNotCopiesEmptyDir)
{
    FileMock::FileMockGuard dirToCopy = std::make_shared<FileMock>("dirName", false, true);
    FileMock::FileMockGuard parentDist = std::make_shared<FileMock>("parent", false);
    FileCopier::Copy(dirToCopy, parentDist);
    dirToCopy->CheckCopied();
}
