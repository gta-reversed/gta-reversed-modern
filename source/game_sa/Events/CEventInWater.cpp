#include "StdInc.h"

void CEventInWater::InjectHooks()
{
    HookInstall(0x4B1370, &CEventInWater::Constructor);
    HookInstall(0x4B13D0, &CEventInWater::AffectsPed_Reversed);
    HookInstall(0x4B1420, &CEventInWater::TakesPriorityOver_Reversed);
}

CEventInWater::CEventInWater(float acceleration)
{
    m_acceleration = acceleration;
}

CEventInWater* CEventInWater::Constructor(float acceleration)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CEventInWater*, 0x4B1370, CEvent*, float>(this, acceleration);
#else
    this->CEventInWater::CEventInWater(acceleration);
    return this;
#endif
}

bool CEventInWater::AffectsPed(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x4B13D0, CEvent*, CPed*>(this, ped);
#else
    return CEventInWater::AffectsPed_Reversed(ped);
#endif
}

bool CEventInWater::TakesPriorityOver(CEvent* refEvent)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x4B1420, CEvent*, CEvent*>(this, refEvent);
#else
    return CEventInWater::TakesPriorityOver_Reversed(refEvent);
#endif
}

bool CEventInWater::AffectsPed_Reversed(CPed* ped)
{
    CTask* task = ped->GetTaskManager().GetActiveTask();
    if (!ped->IsPlayer() && task && task->GetId() == TASK_COMPLEX_IN_WATER)
        return false;
    return ped->IsAlive();
}

bool CEventInWater::TakesPriorityOver_Reversed(CEvent* refEvent)
{
    if (refEvent->GetEventType() == EVENT_KNOCK_OFF_BIKE
        || refEvent->GetEventType() == EVENT_DAMAGE
        || refEvent->GetEventType() == EVENT_STUCK_IN_AIR
        && m_acceleration > 1.0f)
    {
        return true;
    }
    return CEvent::TakesPriorityOver(refEvent);
}
