#include "StdInc.h"

#include "CTaskComplexPartnerShove.h"

void CTaskComplexPartnerShove::InjectHooks()
{
    ReversibleHooks::Install("CTaskComplexPartnerShove", "CTaskComplexPartnerShove", 0x6846F0, &CTaskComplexPartnerShove::Constructor);
}

CTaskComplexPartnerShove::CTaskComplexPartnerShove(const char* commandName, CPed* partner, bool leadSpeaker, float distanceMultiplier, int8 updateDirectionCount, CVector point) :
    CTaskComplexPartner(commandName, partner, leadSpeaker, distanceMultiplier, false, updateDirectionCount, point)
{
    m_updateDirectionCount = updateDirectionCount;
    m_taskId = TASK_COMPLEX_PARTNER_SHOVE;
}

CTaskComplexPartnerShove* CTaskComplexPartnerShove::Constructor(const char* commandName, CPed* partner, bool leadSpeaker, float distanceMultiplier, int8 updateDirectionCount, CVector point)
{
    this->CTaskComplexPartnerShove::CTaskComplexPartnerShove(commandName, partner, leadSpeaker, distanceMultiplier, updateDirectionCount, point);
    return this;
}

CTaskComplexSequence* CTaskComplexPartnerShove::GetPartnerSequence()
{
    return plugin::CallMethodAndReturn<CTaskComplexSequence*, 0x683120, CTask*>(this);
}
