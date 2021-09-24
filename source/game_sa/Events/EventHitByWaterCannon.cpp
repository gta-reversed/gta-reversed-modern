#include "StdInc.h"

void CEventHitByWaterCannon::InjectHooks()
{
    ReversibleHooks::Install("CEventHitByWaterCannon", "Constructor", 0x4B1290, &CEventHitByWaterCannon::Constructor);
    ReversibleHooks::Install("CEventHitByWaterCannon", "AffectsPed_Reversed", 0x4B1330, &CEventHitByWaterCannon::AffectsPed_Reversed);
}

CEventHitByWaterCannon::CEventHitByWaterCannon(CVector const& point, CVector const& moveSpeed)
{
    m_point = point;
    m_moveSpeed = moveSpeed;
}

CEventHitByWaterCannon* CEventHitByWaterCannon::Constructor(CVector const& point, CVector const& moveSpeed)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CEventHitByWaterCannon*, 0x4B1290, CEvent*, CVector const&, CVector const&>(this, point, moveSpeed);
#else
    this->CEventHitByWaterCannon::CEventHitByWaterCannon(point, moveSpeed);
    return this;
#endif
}

bool CEventHitByWaterCannon::AffectsPed(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x4B1330, CEvent*, CPed*>(this, ped);
#else
    return CEventHitByWaterCannon::AffectsPed_Reversed(ped);
#endif
}

bool CEventHitByWaterCannon::AffectsPed_Reversed(CPed* ped)
{
    if (ped->IsAlive()) {
        CTask* task = ped->GetTaskManager().GetActiveTask();
        if (!task || task->GetTaskType() != TASK_COMPLEX_FALL_AND_GET_UP)
            return true;
    }
    return false;
}
