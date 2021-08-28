#include "StdInc.h"

void CEventInWater::InjectHooks()
{
    ReversibleHooks::Install(0x4B1370, &CEventInWater::Constructor);
    ReversibleHooks::Install(0x4B13D0, &CEventInWater::AffectsPed_Reversed);
    ReversibleHooks::Install(0x4B1420, &CEventInWater::TakesPriorityOver_Reversed);
}

CEventInWater::CEventInWater(float acceleration)
{
    m_acceleration = acceleration;
}

// 0x4B1370
CEventInWater* CEventInWater::Constructor(float acceleration)
{
    this->CEventInWater::CEventInWater(acceleration);
    return this;
}

// 0x4B13D0
bool CEventInWater::AffectsPed(CPed* ped)
{
    return CEventInWater::AffectsPed_Reversed(ped);
}

// 0x4B1420
bool CEventInWater::TakesPriorityOver(const CEvent& refEvent)
{
    return CEventInWater::TakesPriorityOver_Reversed(refEvent);
}

bool CEventInWater::AffectsPed_Reversed(CPed* ped)
{
    CTask* task = ped->GetTaskManager().GetActiveTask();
    if (!ped->IsPlayer() && task && task->GetId() == TASK_COMPLEX_IN_WATER)
        return false;
    return ped->IsAlive();
}

bool CEventInWater::TakesPriorityOver_Reversed(const CEvent& refEvent)
{
    if (refEvent.GetEventType() == EVENT_KNOCK_OFF_BIKE
        || refEvent.GetEventType() == EVENT_DAMAGE
        || refEvent.GetEventType() == EVENT_STUCK_IN_AIR
        && m_acceleration > 1.0f)
    {
        return true;
    }
    return CEvent::TakesPriorityOver(refEvent);
}
