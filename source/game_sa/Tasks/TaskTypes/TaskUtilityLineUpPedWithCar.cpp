#include "StdInc.h"

#include "TaskUtilityLineUpPedWithCar.h"

void CTaskUtilityLineUpPedWithCar::ProcessPed(CPed* ped, CVehicle* vehicle, CAnimBlendAssociation* animBlendAssoc) {
    return plugin::CallMethod<0x6513A0>(this, ped, vehicle, animBlendAssoc);
}
