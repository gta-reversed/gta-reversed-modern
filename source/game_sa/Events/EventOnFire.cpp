#include "StdInc.h"

#include "EventOnFire.h"

void CEventOnFire::InjectHooks() {
    RH_ScopedClass(CEventOnFire);
    RH_ScopedCategory("Events");
    RH_ScopedVirtualInstall(AffectsPed, 0x4B1050);
}
bool CEventOnFire::AffectsPed(CPed* ped) { return CEventOnFire::AffectsPed_Reversed(ped); }

// 0x4B1050
bool CEventOnFire::AffectsPed_Reversed(CPed* ped) {
    if (ped->m_pFire && !ped->physicalFlags.bFireProof) {
        CTask* activeTask = ped->GetTaskManager().GetActiveTask();
        if (activeTask && activeTask->GetTaskType() == TASK_COMPLEX_ON_FIRE)
            return false;

        CTask* partialAnimTask = ped->GetTaskManager().GetTaskSecondary(TASK_SECONDARY_PARTIAL_ANIM);
        if (partialAnimTask && partialAnimTask->GetTaskType() == TASK_SIMPLE_PLAYER_ON_FIRE)
            return false;

        return ped->IsAlive();
    }
    return false;
}
