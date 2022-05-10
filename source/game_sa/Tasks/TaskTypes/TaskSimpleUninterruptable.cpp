#include "StdInc.h"

#include "TaskSimpleUninterruptable.h"

void CTaskSimpleUninterruptable::InjectHooks()
{
    RH_ScopedClass(CTaskSimpleUninterruptable);
    RH_ScopedCategory("Tasks/TaskTypes");
    RH_ScopedInstall(Constructor, 0x43E2E0);
}

CTaskSimpleUninterruptable* CTaskSimpleUninterruptable::Constructor()
{
    this->CTaskSimpleUninterruptable::CTaskSimpleUninterruptable();
    return this;
}

