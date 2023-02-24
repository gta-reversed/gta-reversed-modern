#include "StdInc.h"

#include "TaskComplexPartnerGreet.h"

void CTaskComplexPartnerGreet::InjectHooks()
{
    RH_ScopedClass(CTaskComplexPartnerGreet);
    RH_ScopedCategory("Tasks/TaskTypes");
    RH_ScopedInstall(Constructor, 0x684210);
}

CTaskComplexPartnerGreet::CTaskComplexPartnerGreet(const char* commandName, CPed* partner, bool leadSpeaker, float distanceMultiplier, int32 handShakeType, CVector point) :
    CTaskComplexPartner(commandName, partner, leadSpeaker, distanceMultiplier, true, 1, point)
{
    m_handShakeType = handShakeType;
    m_taskId = TASK_COMPLEX_PARTNER_GREET;
    strcpy_s(m_animBlockName, "gangs");
}

CTaskComplexPartnerGreet* CTaskComplexPartnerGreet::Constructor(const char* commandName, CPed* partner, bool leadSpeaker, float distanceMultiplier, int32 handShakeType, CVector point)
{
    this->CTaskComplexPartnerGreet::CTaskComplexPartnerGreet(commandName, partner, leadSpeaker, distanceMultiplier, handShakeType, point);
    return this;
}


CTask* CTaskComplexPartnerGreet::CreateFirstSubTask(CPed* ped)
{
    return plugin::CallMethodAndReturn<CTask*, 0x6825A0, CTask*, CPed*>(this, ped);
}

void CTaskComplexPartnerGreet::StreamRequiredAnims()
{
    return plugin::CallMethod<0x6825B0, CTask*>(this);
}

CTaskComplexSequence* CTaskComplexPartnerGreet::GetPartnerSequence()
{
    return plugin::CallMethodAndReturn<CTaskComplexSequence*, 0x682630, CTask*>(this);
}
