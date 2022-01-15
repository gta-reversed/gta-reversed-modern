#include "StdInc.h"
#include "Garages.h"

void CGarages::InjectHooks() {
    // Static functions (21x)
    // ReversibleHooks::Install("CGarages", "Init", 0x447120, &CGarages::Init);
    // ReversibleHooks::Install("CGarages", "CloseHideOutGaragesBeforeSave", 0x44A170, &CGarages::CloseHideOutGaragesBeforeSave);
    // ReversibleHooks::Install("CGarages", "PlayerArrestedOrDied", 0x449E60, &CGarages::PlayerArrestedOrDied);
    // ReversibleHooks::Install("CGarages", "Init_AfterRestart", 0x448B60, &CGarages::Init_AfterRestart);
    // ReversibleHooks::Install("CGarages", "AllRespraysCloseOrOpen", 0x448B30, &CGarages::AllRespraysCloseOrOpen);
    // ReversibleHooks::Install("CGarages", "IsModelIndexADoor", 0x448AF0, &CGarages::IsModelIndexADoor);
    // ReversibleHooks::Install("CGarages", "FindSafeHouseIndexForGarageType", 0x4489F0, &CGarages::FindSafeHouseIndexForGarageType);
    // ReversibleHooks::Install("CGarages", "IsPointWithinHideOutGarage", 0x448900, &CGarages::IsPointWithinHideOutGarage);
    // ReversibleHooks::Install("CGarages", "isGarageDoorClosed", 0x447D30, &CGarages::isGarageDoorClosed);
    // ReversibleHooks::Install("CGarages", "Update", 0x44C8C0, &CGarages::Update);
    // ReversibleHooks::Install("CGarages", "activateGarage", 0x447CD0, &CGarages::activateGarage);
    // ReversibleHooks::Install("CGarages", "setTargetCar", 0x447C40, &CGarages::setTargetCar);
    // ReversibleHooks::Install("CGarages", "TriggerMessage", 0x447B80, &CGarages::TriggerMessage);
    // ReversibleHooks::Install("CGarages", "IsCarSprayable", 0x4479A0, &CGarages::IsCarSprayable);
    // ReversibleHooks::Install("CGarages", "PrintMessages", 0x447790, &CGarages::PrintMessages);
    // ReversibleHooks::Install("CGarages", "setGarageType", 0x4476D0, &CGarages::setGarageType);
    // ReversibleHooks::Install("CGarages", "AddOne", 0x4471E0, &CGarages::AddOne);
    // ReversibleHooks::Install("CGarages", "Shutdown", 0x4471B0, &CGarages::Shutdown);
    // ReversibleHooks::Install("CGarages", "deactivateGarage", 0x447CB0, &CGarages::deactivateGarage);
    // ReversibleHooks::Install("CGarages", "Save", 0x5D3160, &CGarages::Save);
    // ReversibleHooks::Install("CGarages", "getGarageNumberByName", 0x447680, &CGarages::getGarageNumberByName);
}

// Static functions
// 0x447120
void CGarages::Init() {
    plugin::Call<0x447120>();
}

// 0x44A170
void CGarages::CloseHideOutGaragesBeforeSave() {
    plugin::Call<0x44A170>();
}

// 0x449E60
void CGarages::PlayerArrestedOrDied() {
    return plugin::Call<0x449E60>();
}

// 0x448B60
void CGarages::Init_AfterRestart() {
    return plugin::Call<0x448B60>();
}

// 0x448B30
void CGarages::AllRespraysCloseOrOpen(bool state) {
    plugin::Call<0x448B30, bool>(state);
}

// 0x448AF0
bool CGarages::IsModelIndexADoor(int32 model) {
    return plugin::CallAndReturn<bool, 0x448AF0, int32>(model);
}

// 0x4489F0
int32 CGarages::FindSafeHouseIndexForGarageType(int32 gtype) {
    return plugin::CallAndReturn<int32, 0x4489F0, int32>(gtype);
}

// 0x448900
bool CGarages::IsPointWithinHideOutGarage(const CVector & point) {
    return plugin::CallAndReturn < bool, 0x448900, const CVector&> (point);
}

// 0x447D30
bool CGarages::isGarageDoorClosed(int16 garageId) {
    return plugin::CallAndReturn<bool, 0x447D30, int16>(garageId);
}

// 0x44C8C0
void CGarages::Update() {
    plugin::Call<0x44C8C0>();
}

// 0x447CD0
void CGarages::ActivateGarage(int16 a1) {
    return plugin::Call<0x447CD0, int16>(a1);
}

// 0x447C40
void CGarages::SetTargetCar(int16 garageId, CVehicle* veh) {
    plugin::Call<0x447C40, int16, CVehicle*>(garageId, veh);
}

// 0x447B80
void CGarages::TriggerMessage(const char * tagMsg, int16 msgMin, uint16 time, int16 msgMax) {
    return plugin::Call<0x447B80, const char*, int16, uint16, int16>(tagMsg, msgMin, time, msgMax);
}

// 0x4479A0
bool CGarages::IsCarSprayable(CVehicle* veh) {
    return plugin::CallAndReturn<bool, 0x4479A0, CVehicle*>(veh);
}

// 0x447790
void CGarages::PrintMessages() {
    plugin::Call<0x447790>();
}

// 0x4476D0
void CGarages::SetGarageType(int16 garageId, eGarageType type, int32 unused) {
    plugin::Call<0x4476D0, int16, eGarageType, int32>(garageId, type, unused);
}

// 0x4471E0
// Garage flags
// 0x1	door opens up and rotate
// 0x2	door goes in
// 0x4	camera follow players
void CGarages::AddOne(float x1, float y1, float z1, float frontX, float frontY, float x2, float y2, float z2, uint8 type, uint32 a10, char* name, uint32 argFlags) {
    return plugin::Call<0x4471E0, float, float, float, float, float, float, float, float, uint8, uint32, char*, uint32>(x1, y1, z1, frontX, frontY, x2, y2, z2,
                                                                                                                                        type, a10, name, argFlags);
}

// 0x4471B0
void CGarages::Shutdown() {
    return plugin::Call<0x4471B0>();
}

// 0x447CB0
void CGarages::DeactivateGarage(int16 grgIdx) {
    plugin::Call<0x447CB0>(grgIdx);
}

// 0x5D3160
bool CGarages::Save() {
    return plugin::CallAndReturn<bool, 0x5D3160>();
}

bool CGarages::Load() {
    return plugin::CallAndReturn<bool, 0x5D3270>();
}

int16 CGarages::FindGarageForObject(CObject* obj) {
    return plugin::CallAndReturn<int16, 0x44A240>(obj);
}

// 0x447680
int16 CGarages::GetGarageNumberByName(const char* name) {
    return plugin::CallAndReturn<int16, 0x447680>(name);
}
