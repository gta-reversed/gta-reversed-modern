#include "StdInc.h"

#include "TaskComplexWalkRoundCar.h"

void CTaskComplexWalkRoundCar::SetNewVehicle(CVehicle* vehicle, uint8 flags) {
    plugin::CallMethod<0x654290, CTaskComplexWalkRoundCar*, CVehicle*, uint8>(this, vehicle, flags);
}

bool CTaskComplexWalkRoundCar::IsGoingForDoor() const {
    return m_isPedGoingForCarDoor && m_vehicle && m_vehicle->vehicleFlags.bIsBig;
}
