#include "StdInc.h"

CTaskComplexLeaveCar* CTaskComplexLeaveCar::Constructor(CVehicle* pTargetVehicle, int nTargetDoor, int nDelayTime, bool bSensibleLeaveCar, bool bForceGetOut)
{
    return plugin::CallMethodAndReturn< CTaskComplexLeaveCar*, 0x63B8C0, CTaskComplexLeaveCar*, CVehicle*, int, int, bool, bool>
        (this, pTargetVehicle, nTargetDoor, nDelayTime, bSensibleLeaveCar, bForceGetOut);
}