#include "stdafx.h"
#include "filemock.h"

FileMock::FileMock()
    : m_childrens(0)
{
}

FileMock::FileMock(const std::string& name)
    : FileMock()
{
    name;
}

IFile::IFileGuard FileMock::Copy()
{
    return std::make_shared<FileMock>();
}

bool FileMock::IsDir()
{
    return false;
}

IFile::IFileGuard FileMock::GetParent()
{
    return std::make_shared<FileMock>();
}

const IFile::ChildFiles& FileMock::GetChildrens()
{
    return m_childrens;
}

void FileMock::AddChild(IFileGuard child)
{
    m_childrens.push_back(child);
}
