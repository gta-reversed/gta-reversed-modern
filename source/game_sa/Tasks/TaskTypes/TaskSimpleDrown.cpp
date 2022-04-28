#include "StdInc.h"

#include "TaskSimpleDrown.h"
#include "TaskSimpleDie.h"

void CTaskSimpleDrown::InjectHooks() {
    RH_ScopedClass(CTaskSimpleDrown);
    RH_ScopedCategory("Tasks/TaskTypes");
    RH_ScopedInstall(ProcessPed_Reversed, 0x639900);
}
bool CTaskSimpleDrown::ProcessPed(CPed* ped) { return ProcessPed_Reversed(ped); }

// 0x62FEC0
CTaskSimpleDrown::CTaskSimpleDrown() : CTaskSimpleDie(ANIM_GROUP_DEFAULT, ANIM_ID_DROWN, 4.0f, 0.0f) {
    m_bShouldExecute = true;
}

// 0x639900
bool CTaskSimpleDrown::ProcessPed_Reversed(CPed* ped) {
    if (m_bShouldExecute) {
        ped->SetPedState(PEDSTATE_DIE);
        ped->bIsInTheAir = false; 
        if (ped == FindPlayerPed()) {
            CStats::IncrementStat(STAT_TIMES_DROWNED, 1.0f);
        }
        m_bShouldExecute = false;
    }
    return CTaskSimpleDie::ProcessPed(ped);
}
