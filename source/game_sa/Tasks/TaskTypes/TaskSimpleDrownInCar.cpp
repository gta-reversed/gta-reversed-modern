#include "StdInc.h"

#include "TaskSimpleDrownInCar.h"

// 0x62FF70
bool CTaskSimpleDrownInCar::ProcessPed(CPed* ped) {
    ped->SetPedState(PEDSTATE_DIE);
    ped->bIsInTheAir = false; // todo: m_nPedFlags &= ~0x200u;
    if (ped == FindPlayerPed())
        CStats::IncrementStat(STAT_TIMES_DROWNED, 1.0f);

    if (ped == FindPlayerPed()) {
        ped->m_pVehicle->m_nStatus = STATUS_PLANE;
    }

    CEventDeath event(true);
    ped->GetEventGroup().Add(&event, false);
    return true;
}
