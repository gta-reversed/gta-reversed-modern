#include "StdInc.h"

void CUpsideDownCarCheck::InjectHooks() {
//    RH_ScopedInstall(Init, 0x46A8C0);
//    RH_ScopedInstall(IsCarUpsideDown, 0x463830);
//    RH_ScopedInstall(UpdateTimers, 0x4655E0);
//    RH_ScopedInstall(AddCarToCheck, 0x4638D0);
//    RH_ScopedInstall(RemoveCarFromCheck, 0x463910);
//    RH_ScopedInstall(HasCarBeenUpsideDownForAWhile, 0x463940);
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
void CUpsideDownCarCheck::AddCarToCheck(int32 carHandle) {
    plugin::CallMethod<0x4638D0, CUpsideDownCarCheck*, int32>(this, carHandle);
}

// 0x463910
void CUpsideDownCarCheck::RemoveCarFromCheck(int32 carHandle) {
    plugin::CallMethod<0x463910, CUpsideDownCarCheck*, int32>(this, carHandle);
}

// 0x463940
bool CUpsideDownCarCheck::HasCarBeenUpsideDownForAWhile(int32 carHandle) {
    return plugin::CallMethodAndReturn<bool, 0x463940, CUpsideDownCarCheck*, int32>(this, carHandle);
}
