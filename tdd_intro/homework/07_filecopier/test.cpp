#include <gtest/gtest.h>
#include <gmock/gmock.h>

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
    IFile Copy();
    bool IsDir();
    const ChildFiles& GetChildrens() = 0;
    IFile GetParent();
    void AddChild(IFile&&);
}
*/
class IFile;
using ChildFiles = std::vector<IFile>;
class IFile
{
public:
    virtual ~IFile(){}
    IFile Copy() = 0;
    bool IsDir() = 0;
    IFile GetParent() = 0;
    const ChildFiles& GetChildrens() = 0;
    void AddChild(IFile&&) = 0;
};

class FileCopier
{
public:
    static void Copy(const IFile& src, IFile& parentDst);
};

class FileMock: public IFile
{
    FileMock(){}
    IFile Copy() {}
    bool IsDir() {return false;}
    IFile GetParent() {return FileMock();}
    const ChildFiles& GetChildrens() {return {};}
    void AddChild(IFile&&) {}
}

