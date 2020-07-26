#include "StdInc.h"

void CTaskComplexWalkRoundCar::SetNewVehicle(CVehicle* vehicle, std::uint8_t flags)
{
    plugin::CallMethod<0x654290, CTaskComplexWalkRoundCar*, CVehicle*, std::uint8_t>(this, vehicle, flags);
}
