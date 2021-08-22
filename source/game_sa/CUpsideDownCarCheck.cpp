#include "StdInc.h"

void CUpsideDownCarCheck::InjectHooks() {
//    ReversibleHooks::Install("CUpsideDownCarCheck", "Init", 0x46A8C0, &CUpsideDownCarCheck::Init);
//    ReversibleHooks::Install("CUpsideDownCarCheck", "IsCarUpsideDown", 0x463830, &CUpsideDownCarCheck::IsCarUpsideDown);
//    ReversibleHooks::Install("CUpsideDownCarCheck", "UpdateTimers", 0x4655E0, &CUpsideDownCarCheck::UpdateTimers);
//    ReversibleHooks::Install("CUpsideDownCarCheck", "AddCarToCheck", 0x4638D0, &CUpsideDownCarCheck::AddCarToCheck);
//    ReversibleHooks::Install("CUpsideDownCarCheck", "RemoveCarFromCheck", 0x463910, &CUpsideDownCarCheck::RemoveCarFromCheck);
//    ReversibleHooks::Install("CUpsideDownCarCheck", "HasCarBeenUpsideDownForAWhile", 0x463940, &CUpsideDownCarCheck::HasCarBeenUpsideDownForAWhile);
}

// 0x46A8C0
void CUpsideDownCarCheck::Init() {
    plugin::CallMethod<0x46A8C0>(this);
}

// 0x463830
bool CUpsideDownCarCheck::IsCarUpsideDown(CVehicle const* vehicle) {
    return plugin::CallAndReturn<bool, 0x463830, CVehicle const*>(vehicle);
}

// Process
// 0x4655E0
void CUpsideDownCarCheck::UpdateTimers() {
    plugin::CallMethod<0x4655E0>(this);
}

//! never used
bool CUpsideDownCarCheck::AreAnyCarsUpsideDown() {
    return false;
}

// 0x4638D0
void CUpsideDownCarCheck::AddCarToCheck(int carHandle) {
    plugin::CallMethod<0x4638D0, int>(carHandle);
}

// 0x463910
void CUpsideDownCarCheck::RemoveCarFromCheck(int carHandle) {
    plugin::CallMethod<0x463910, int>(carHandle);
}

// 0x463940
bool CUpsideDownCarCheck::HasCarBeenUpsideDownForAWhile(int carHandle) {
    return plugin::CallMethodAndReturn<bool, 0x463940, CUpsideDownCarCheck*, int>(this, carHandle);
}