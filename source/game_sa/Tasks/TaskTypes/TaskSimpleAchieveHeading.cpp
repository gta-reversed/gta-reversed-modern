#include "StdInc.h"

#include "TaskSimpleAchieveHeading.h"

CTaskSimpleAchieveHeading::CTaskSimpleAchieveHeading(float fAngle, float arg2, float arg3)
{
    plugin::CallMethodAndReturn< CTaskSimpleAchieveHeading*, 0x667E20, CTaskSimpleAchieveHeading*, float, float, float>(this, fAngle, arg2, arg3);
}

CTaskSimpleAchieveHeading::~CTaskSimpleAchieveHeading()
{
    plugin::CallMethod<0x66DB60, CTaskSimpleAchieveHeading*>(this);
}

bool CTaskSimpleAchieveHeading::ProcessPed(CPed* ped)
{
    return plugin::CallMethodAndReturn<bool, 0x668060, CTaskSimpleAchieveHeading*, CPed*>(this, ped);
}

CTask* CTaskSimpleAchieveHeading::Clone()
{
    return plugin::CallMethodAndReturn<CTask*, 0x66CCF0, CTaskSimpleAchieveHeading*>(this);
}

bool CTaskSimpleAchieveHeading::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event)
{
    return plugin::CallMethodAndReturn<bool, 0x667EB0, CTaskSimpleAchieveHeading*, CPed*, eAbortPriority, const CEvent*>(this, ped, priority, event);
}
