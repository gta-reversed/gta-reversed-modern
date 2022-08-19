#include "StdInc.h"

#include "TaskSimpleDrownInCar.h"

void CTaskSimpleDrownInCar::InjectHooks() {
    RH_ScopedClass(CTaskSimpleDrownInCar);
    RH_ScopedCategory("Tasks/TaskTypes");
    RH_ScopedInstall(ProcessPed_Reversed, 0x62FF70);
}
bool CTaskSimpleDrownInCar::ProcessPed(CPed* ped) { return ProcessPed_Reversed(ped); }

// 0x62FF70
bool CTaskSimpleDrownInCar::ProcessPed_Reversed(CPed* ped) {
    ped->SetPedState(PEDSTATE_DIE);
    ped->bIsInTheAir = false;

    if (ped == FindPlayerPed()) {
        CStats::IncrementStat(STAT_TIMES_DROWNED, 1.0f);
        ped->m_pVehicle->m_nStatus = STATUS_FORCED_STOP;
    }

    CEventDeath event(true);
    ped->GetEventGroup().Add(&event, false);
    return true;
}
