#pragma once
#include "ifile.h"

class FileMock: public IFile
{
public:
    using FileMockGuard = std::shared_ptr<FileMock>;
    using ChildMockFiles = std::vector<FileMockGuard>;
    FileMock();
    FileMock(const std::string& name);

    IFileGuard Copy();
    bool IsDir();
    IFileGuard GetParent();
    const IFile::ChildFiles& GetChildrens();
    void AddChild(IFileGuard);
    const std::string& GetName();

private:
    IFile::ChildFiles m_childrens;
    std::string m_name;
};
