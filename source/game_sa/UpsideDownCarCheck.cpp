#include "StdInc.h"

#include "UpsideDownCarCheck.h"

namespace rng = std::ranges;

void CUpsideDownCarCheck::InjectHooks() {
    RH_ScopedClass(CUpsideDownCarCheck);
    RH_ScopedCategoryGlobal();

    //RH_ScopedInstall(Init, 0x46A8C0);
    RH_ScopedInstall(IsCarUpsideDown, 0x463830);
    RH_ScopedInstall(UpdateTimers, 0x4655E0);
    RH_ScopedInstall(AddCarToCheck, 0x4638D0);
    RH_ScopedInstall(RemoveCarFromCheck, 0x463910);
    RH_ScopedInstall(HasCarBeenUpsideDownForAWhile, 0x463940);
}

// 0x46A8C0
// NOTE: Seems like it has a `CScriptTrigger*` argument?
//       Something's really off with this one..
//       It can't belong to this class, because the loop in it does 70 iterations... (and the array is only 6 in size)
void CUpsideDownCarCheck::Init() {
    plugin::CallMethod<0x46A8C0>(this);
}

// 0x463830
bool CUpsideDownCarCheck::IsCarUpsideDown(/* const */ CVehicle* vehicle) {
    const auto GetNumContactWheels = [=]() -> uint32 {
        switch (vehicle->m_nVehicleType) {
        case eVehicleType::VEHICLE_TYPE_BIKE:
            return vehicle->AsBike()->m_nNumContactWheels;
        case eVehicleType::VEHICLE_TYPE_AUTOMOBILE:
            return vehicle->AsAutomobile()->m_nNumContactWheels;
        default:
            return 0u;
        }
    };
    if (!vehicle->CanPedStepOutCar(false)) {
        const auto up = vehicle->GetUp();
        return up.z < 0.3f && GetNumContactWheels() < 4  // Not totally up-side down
            || up.z < 0.f;                               // Literally up-side down
    }
    return false;
}

// Process
// 0x4655E0
void CUpsideDownCarCheck::UpdateTimers() {
    const auto delta = CTimer::GetTimeStepInMS();
    for (auto& car : m_aUpsideDownCars) {
        if (!car.m_nHandle)
            continue;

        if (const auto veh = CPools::GetVehicle(car.m_nHandle)) {
            if (IsCarUpsideDown(veh)) {
                car.m_nTime += delta;
            } else {
                car.m_nTime = 0;
            }
        } else {
            car.m_nHandle = 0;
        }
    }
}

// 0x4638A0, todo:: add code
// never used
bool CUpsideDownCarCheck::AreAnyCarsUpsideDown() {
    return false;
}

// 0x4638D0
void CUpsideDownCarCheck::AddCarToCheck(int32 carHandle) {
    const auto it = rng::find_if(m_aUpsideDownCars, [](auto&& car) { return car.m_nHandle < 0; });
    if (it != std::end(m_aUpsideDownCars)) {
        it->m_nHandle = carHandle;
        it->m_nTime = 0;
    }
}

// 0x463910
void CUpsideDownCarCheck::RemoveCarFromCheck(int32 carHandle) {
    for (auto& car : m_aUpsideDownCars) {
        if (car.m_nHandle == carHandle) {
            car.m_nHandle = -1;
            car.m_nTime = 0;
        }
    }
}

// 0x463940
bool CUpsideDownCarCheck::HasCarBeenUpsideDownForAWhile(int32 carHandle) {
    const auto it = rng::find_if(m_aUpsideDownCars, [=](auto&& car) { return car.m_nHandle == carHandle; });
    return it != std::end(m_aUpsideDownCars) ? it->m_nTime > 2000u : false;
}
