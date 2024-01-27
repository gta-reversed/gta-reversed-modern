#include "StdInc.h"
#include "EventHitByWaterCannon.h"


void CEventHitByWaterCannon::InjectHooks()
{
    RH_ScopedClass(CEventHitByWaterCannon);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x4B1290);
    RH_ScopedVirtualInstall(AffectsPed, 0x4B1330);
}

// 0x4B1290
CEventHitByWaterCannon::CEventHitByWaterCannon(const CVector& point, const CVector& moveSpeed)
{
    m_point = point;
    m_moveSpeed = moveSpeed;
}

// 0x4B1290
CEventHitByWaterCannon* CEventHitByWaterCannon::Constructor(const CVector& point, const CVector& moveSpeed)
{
    this->CEventHitByWaterCannon::CEventHitByWaterCannon(point, moveSpeed);
    return this;
}

// 0x4B1330
bool CEventHitByWaterCannon::AffectsPed(CPed* ped)
{
    return CEventHitByWaterCannon::AffectsPed_Reversed(ped);
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

