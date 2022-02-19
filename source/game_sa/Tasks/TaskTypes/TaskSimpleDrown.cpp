#include "StdInc.h"

#include "TaskSimpleDrown.h"
#include "TaskSimpleDie.h"

// 0x62FEC0
CTaskSimpleDrown::CTaskSimpleDrown() : CTaskSimpleDie(ANIM_GROUP_DEFAULT, ANIM_ID_DROWN, 4.0f, 0.0f) {
    m_bShouldExecute = true;
}

// 0x639900
bool CTaskSimpleDrown::ProcessPed(CPed* ped) {
    if (m_bShouldExecute) {
        ped->SetPedState(PEDSTATE_DIE);
        ped->bIsInTheAir = false; //  &= ~0x200u
        if (ped == FindPlayerPed())
            CStats::IncrementStat(STAT_TIMES_DROWNED, 1.0f);
        m_bShouldExecute = 0;
    }
    return CTaskSimpleDie::ProcessPed(ped);
}
