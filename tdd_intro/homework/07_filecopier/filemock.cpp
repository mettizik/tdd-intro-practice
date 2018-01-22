#include "stdafx.h"
#include "filemock.h"

FileMock::FileMock()
    : FileMock("", false, false)
{
}

FileMock::FileMock(const std::string& name)
    : FileMock(name, false, false)
{
}

FileMock::FileMock(const std::string& name, bool isToBeCopied)
    : FileMock(name, isToBeCopied, false)
{
}

FileMock::FileMock(const std::string& name, bool isToBeCopied, bool isDir)
    : m_childrens{}
    , m_name(name)
    , m_isToBeCopied(isToBeCopied)
    , m_isCopied(false)
    , m_isDir(isDir)
{
}

FileMock::~FileMock()
{
    EXPECT_EQ(m_isToBeCopied, m_isCopied);
}

IFile::IFileGuard FileMock::Copy()
{
    m_isCopied = true;
    return std::make_shared<FileMock>(m_name);
}

bool FileMock::IsDir()
{
    return m_isDir;
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

const std::string& FileMock::GetName()
{
    return m_name;
}
