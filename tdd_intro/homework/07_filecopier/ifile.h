#pragma once

class IFile
{
public:
    using IFileGuard = std::shared_ptr<IFile>;
    using ChildFiles = std::vector<IFileGuard>;
    virtual ~IFile(){}
    virtual bool IsDir() = 0;
    virtual IFileGuard Copy() = 0;
    virtual IFileGuard GetParent() = 0;
    virtual const ChildFiles& GetChildrens() = 0;
    virtual void AddChild(IFileGuard) = 0;
};
