#include "StdInc.h"
#include "EventLeaderEntryExit.h"


void CEventLeaderEntryExit::InjectHooks()
{
    RH_ScopedClass(CEventLeaderEntryExit);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x43E1C0);
}

// 0x43E1C0
CEventLeaderEntryExit* CEventLeaderEntryExit::Constructor(CPed* ped)
{
    this->CEventLeaderEntryExit::CEventLeaderEntryExit(ped);
    return this;
}

