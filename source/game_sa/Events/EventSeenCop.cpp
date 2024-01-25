#include "StdInc.h"
#include "EventSeenCop.h"


void CEventSeenCop::InjectHooks()
{
    RH_ScopedClass(CEventSeenCop);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor1, 0x5FF380);
}

// 0x5FF380
CEventSeenCop* CEventSeenCop::Constructor1(CPed* cop)
{
    this->CEventSeenCop::CEventSeenCop(cop);
    return this;
}

