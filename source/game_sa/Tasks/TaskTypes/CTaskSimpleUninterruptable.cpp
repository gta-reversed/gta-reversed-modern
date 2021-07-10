#include "StdInc.h"

void CTaskSimpleUninterruptable::InjectHooks()
{
    ReversibleHooks::Install("CTaskSimpleUninterruptable", "Constructor", 0x43E2E0, &CTaskSimpleUninterruptable::Constructor);
}

CTaskSimpleUninterruptable* CTaskSimpleUninterruptable::Constructor()
{
    this->CTaskSimpleUninterruptable::CTaskSimpleUninterruptable();
    return this;
}

