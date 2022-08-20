#include "StdInc.h"

#include "TaskSimpleDieInCar.h"
#include "TaskSimpleDie.h"

// 0x62FC20
CTaskSimpleDieInCar::CTaskSimpleDieInCar(AssocGroupId groupId, AnimationId animId) : CTaskSimpleDie(groupId, animId, 4.0f, 0.0f) {
    // NOP
}

bool CTaskSimpleDieInCar::ProcessPed(CPed* ped) {
    return CTaskSimpleDie::ProcessPed(ped);
}
