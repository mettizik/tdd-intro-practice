#include "stdafx.h"
#include "filemock.h"

FileMock::FileMock()
    : m_childrens(0)
{
}

FileMock::FileMock(const std::string& name)
    : m_childrens(0)
    , m_name(name)
{
}

FileMock::FileMock(const std::string& name, bool isToBeCopied)
    : m_childrens(0)
    , m_name(name)
    , m_isToBeCopied(isToBeCopied)
{
}

FileMock::~FileMock()
{
}

IFile::IFileGuard FileMock::Copy()
{
    m_isCopied = true;
    return std::make_shared<FileMock>(m_name);
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

const std::string& FileMock::GetName()
{
    return m_name;
}

void FileMock::CheckCopied()
{
    EXPECT_EQ(m_isToBeCopied, m_isCopied);
}
