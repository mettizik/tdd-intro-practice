#pragma once
#include "ifile.h"

class FileMock: public IFile
{
public:
    using FileMockGuard = std::shared_ptr<FileMock>;
    using ChildMockFiles = std::vector<FileMockGuard>;
    FileMock();
    explicit FileMock(const std::string& name);
    FileMock(const std::string& name, bool isToBeCopied);
    FileMock(const std::string& name, bool isToBeCopied, bool isDir);
    ~FileMock();

    IFileGuard Copy();
    bool IsDir();
    IFileGuard GetParent();
    const IFile::ChildFiles& GetChildrens();
    void AddChild(IFileGuard);
    const std::string& GetName();

private:
    IFile::ChildFiles m_childrens;
    std::string m_name;
    bool m_isToBeCopied;
    bool m_isCopied;
    bool m_isDir;
};
