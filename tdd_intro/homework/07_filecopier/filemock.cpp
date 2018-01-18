#include "stdafx.h"
#include "filemock.h"

FileMock::FileMock()
{

}

FileMock::FileMock(const std::string& name)
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
    return ChildFiles{};
}

void FileMock::AddChild(IFileGuard)
{}
