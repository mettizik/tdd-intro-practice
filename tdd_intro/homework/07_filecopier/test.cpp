#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <memory>

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
class IFile;
using IFileGuard = std::shared_ptr<IFile>;
using ChildFiles = std::vector<IFileGuard>;
class IFile
{
public:
    virtual ~IFile(){}
    virtual bool IsDir() = 0;
    virtual IFileGuard Copy() = 0;
    virtual IFileGuard GetParent() = 0;
    virtual const ChildFiles& GetChildrens() = 0;
    virtual void AddChild(IFileGuard) = 0;
};

class FileCopier
{
public:
    static void Copy(const IFile& src, IFile& parentDst)
    {
        src;
        parentDst;
    }
};

class FileMock;
using FileMockGuard = std::shared_ptr<FileMock>;
using ChildMockFiles = std::vector<FileMockGuard>;
class FileMock: public IFile
{
public:
    FileMock(){}
    IFileGuard Copy() {return std::make_shared<FileMock>();}
    bool IsDir() {return false;}
    IFileGuard GetParent() {return std::make_shared<FileMock>();}
    const ChildFiles& GetChildrens() {return ChildFiles{};}
    void AddChild(IFileGuard) {}
};

TEST(FileCopier, CopyCopiesOneFile)
{
    FileMock fileToCopy("fileName");
    FileMock parentDist("parent");
    FileCopier::Copy(fileToCopy, parentDist);
    EXPECT_EQ(1, parentDist.GetChildrens().size());
}
