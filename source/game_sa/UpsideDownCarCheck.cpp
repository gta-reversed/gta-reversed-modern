#include "StdInc.h"

void CUpsideDownCarCheck::InjectHooks() {
//    ReversibleHooks::Install("CUpsideDownCarCheck", "Init", 0x46A8C0, &CUpsideDownCarCheck::Init);
    ReversibleHooks::Install("CUpsideDownCarCheck", "IsCarUpsideDown", 0x463830, &CUpsideDownCarCheck::IsCarUpsideDown);
    ReversibleHooks::Install("CUpsideDownCarCheck", "UpdateTimers", 0x4655E0, &CUpsideDownCarCheck::UpdateTimers);
    ReversibleHooks::Install("CUpsideDownCarCheck", "AddCarToCheck", 0x4638D0, &CUpsideDownCarCheck::AddCarToCheck);
    ReversibleHooks::Install("CUpsideDownCarCheck", "RemoveCarFromCheck", 0x463910, &CUpsideDownCarCheck::RemoveCarFromCheck);
    ReversibleHooks::Install("CUpsideDownCarCheck", "HasCarBeenUpsideDownForAWhile", 0x463940, &CUpsideDownCarCheck::HasCarBeenUpsideDownForAWhile);
}

// 0x46A8C0
// NOTE: Seems like it has a `CScriptTrigger*` argument?
//       Something's really off with this one..
//       It can't belong to this class, because the loop in it does 70 iterations... (and the array is only 6 in size)
void CUpsideDownCarCheck::Init() {
    plugin::CallMethod<0x46A8C0>(this);
}

// 0x463830
bool CUpsideDownCarCheck::IsCarUpsideDown(CVehicle* vehicle) {
    const auto GetNumContactWheels = [=]() -> uint32 {
        switch (vehicle->m_vehicleType) {
        case eVehicleType::VEHICLE_BIKE:
            return vehicle->AsBike()->m_nNumContactWheels;
        case eVehicleType::VEHICLE_AUTOMOBILE:
            return vehicle->AsAutomobile()->m_nNumContactWheels;
        default:
            return 0u;
        }
    };
    const auto up = vehicle->GetUp();
    return ((up.z < 0.3f && GetNumContactWheels() < 4) || (up.z < 0.f)) && vehicle->CanPedStepOutCar(false);
}

// Process
// 0x4655E0
void CUpsideDownCarCheck::UpdateTimers() {
    const auto delta = CTimer::GetTimeStepInMS();
    for (auto& v : m_aUpsideDownCars) {
        if (!v.m_nCarHandle)
            continue;

        if (const auto veh = CPools::GetVehicle(v.m_nCarHandle)) {
            if (IsCarUpsideDown(veh)) {
                v.m_nTime += delta;
            } else {
                v.m_nTime = 0;
            }
        } else {
            v.m_nCarHandle = 0;
        }
    }
}

//! never used
bool CUpsideDownCarCheck::AreAnyCarsUpsideDown() {
    return false;
}

// 0x4638D0
void CUpsideDownCarCheck::AddCarToCheck(int32 carHandle) {
    const auto it = std::ranges::find_if(m_aUpsideDownCars, [](const auto& en) {return en.m_nCarHandle < 0; });
    if (it != std::end(m_aUpsideDownCars)) {
        it->m_nCarHandle = carHandle;
        it->m_nTime = 0;
    }
}

// 0x463910
void CUpsideDownCarCheck::RemoveCarFromCheck(int32 carHandle) {
    for (auto& v : m_aUpsideDownCars) {
        if (v.m_nCarHandle == carHandle) {
            v.m_nCarHandle = -1;
            v.m_nTime = 0;
        }
    }
}

// 0x463940
bool CUpsideDownCarCheck::HasCarBeenUpsideDownForAWhile(int32 carHandle) {
    const auto it = std::ranges::find_if(m_aUpsideDownCars, [=](const auto& en) {return en.m_nCarHandle == carHandle; });
    if (it != std::end(m_aUpsideDownCars))
        return it->m_nTime > 2000u;
    return false;
}
