#include "StdInc.h"

#include "TaskSimpleUninterruptable.h"

void CTaskSimpleUninterruptable::InjectHooks()
{
    Install("CTaskSimpleUninterruptable", "Constructor", 0x43E2E0, &CTaskSimpleUninterruptable::Constructor);
}

CTaskSimpleUninterruptable* CTaskSimpleUninterruptable::Constructor()
{
    this->CTaskSimpleUninterruptable::CTaskSimpleUninterruptable();
    return this;
}

