#include "StdInc.h"

#include "EventRevived.h"

// 0x4AECB0
bool CEventRevived::AffectsPed(CPed* ped) {
    return !ped->IsCreatedByMission() && !ped->IsAlive();
}
