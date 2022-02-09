#include "StdInc.h"

#include "MonsterTruck.h"

float& CMonsterTruck::DUMPER_COL_ANGLEMULT = *(float*)0x8D33A8;
float& fWheelExtensionRate = *(float*)0x8D33AC;

void CMonsterTruck::InjectHooks() {
    RH_ScopedClass(CMonsterTruck);
    RH_ScopedCategory("Vehicle/Ped");

    // RH_ScopedInstall(ProcessEntityCollision, 0x6C8AE0);
    // RH_ScopedInstall(ProcessSuspension, 0x6C83A0);
    // RH_ScopedInstall(ProcessControlCollisionCheck, 0x6C8330);
    // RH_ScopedInstall(ProcessControl, 0x6C8250);
    // RH_ScopedInstall(SetupSuspensionLines, 0x6C7FB0);
    // RH_ScopedInstall(PreRender, 0x6C7DE0);
    // RH_ScopedInstall(ExtendSuspension, 0x6C7D80);
    // RH_ScopedInstall(ResetSuspension, 0x6C7D40);
    RH_ScopedInstall(BurstTyre_Reversed, 0x6C7D30);
    RH_ScopedInstall(SetUpWheelColModel_Reversed, 0x6C7D20);
}

// 0x6C8D60
CMonsterTruck::CMonsterTruck(int32 modelIndex, eVehicleCreatedBy createdBy) : CAutomobile(modelIndex, createdBy, false) {
    plugin::CallMethod<0x6C8D60, CMonsterTruck*, int32, eVehicleCreatedBy>(this, modelIndex, createdBy);
    return;

    std::ranges::fill(field_988, 1.0f);
    SetupSuspensionLines();
    ucNPCVehicleFlags |= 0x80u;
    m_nVehicleSubType = VEHICLE_TYPE_MTRUCK;
}

// 0x6C8AE0
int32 CMonsterTruck::ProcessEntityCollision(CEntity* entity, CColPoint* colPoint) {
    return plugin::CallMethodAndReturn<int32, 0x6C8AE0, CMonsterTruck*, CEntity*, CColPoint*>(this, entity, colPoint);
}

// 0x6C83A0
void CMonsterTruck::ProcessSuspension() {
    plugin::CallMethod<0x6C83A0, CMonsterTruck*>(this);
}

// 0x6C8330
void CMonsterTruck::ProcessControlCollisionCheck(bool applySpeed) {
    plugin::CallMethod<0x6C8330, CMonsterTruck*, bool>(this, applySpeed);
}

// 0x6C8250
void CMonsterTruck::ProcessControl() {
    plugin::CallMethod<0x6C8250, CMonsterTruck*>(this);
}

// 0x6C7FB0
void CMonsterTruck::SetupSuspensionLines() {
    plugin::CallMethod<0x6C7FB0, CMonsterTruck*>(this);
}

// 0x6C7DE0
void CMonsterTruck::PreRender() {
    plugin::CallMethod<0x6C7DE0, CMonsterTruck*>(this);
}

// 0x6C7D80
void CMonsterTruck::ExtendSuspension() {
    plugin::CallMethod<0x6C7D80, CMonsterTruck*>(this);
}

// 0x6C7D40
void CMonsterTruck::ResetSuspension() {
    plugin::CallMethod<0x6C7D40, CMonsterTruck*>(this);
}

// 0x6C7D30
bool CMonsterTruck::BurstTyre(uint8 tyreComponentId, bool bPhysicalEffect) {
    return false;
}

// 0x6C7D20
bool CMonsterTruck::SetUpWheelColModel(CColModel* colModel) {
    return false;
}
