#include "StdInc.h"

#include "MonsterTruck.h"

float& CMonsterTruck::DUMPER_COL_ANGLEMULT = *(float*)0x8D33A8;
float& fWheelExtensionRate = *(float*)0x8D33AC;

void CMonsterTruck::InjectHooks() {
    RH_ScopedClass(CMonsterTruck);
    RH_ScopedCategory("Vehicle");

    RH_ScopedInstall(Constructor, 0x6C8D60);
    RH_ScopedInstall(ProcessEntityCollision, 0x6C8AE0, { .reversed = false });
    RH_ScopedInstall(ProcessSuspension, 0x6C83A0, { .reversed = false });
    RH_ScopedInstall(ProcessControlCollisionCheck, 0x6C8330, { .reversed = false });
    RH_ScopedInstall(ProcessControl, 0x6C8250, { .reversed = false });
    RH_ScopedInstall(SetupSuspensionLines, 0x6C7FB0, { .reversed = false });
    RH_ScopedInstall(PreRender, 0x6C7DE0);
    RH_ScopedInstall(ExtendSuspension, 0x6C7D80, { .reversed = false });
    RH_ScopedInstall(ResetSuspension, 0x6C7D40, { .reversed = false });
    RH_ScopedVirtualInstall(BurstTyre, 0x6C7D30);
    RH_ScopedVirtualInstall(SetUpWheelColModel, 0x6C7D20);
}

// 0x6C8D60
CMonsterTruck::CMonsterTruck(int32 modelIndex, eVehicleCreatedBy createdBy) : CAutomobile(modelIndex, createdBy, false) {
    std::ranges::fill(field_988, 1.0f);
    SetupSuspensionLines(); // V1053 Calling the 'SetupSuspensionLines' virtual function in the constructor may lead to unexpected result at runtime.
    npcFlags.bSoftSuspension = true;
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
    for (auto i = 0; i < 4; i++) {
        m_wheelPosition[i] = std::min(m_wheelPosition[i], m_aSuspensionSpringLength[i]);
    }

    CAutomobile::PreRender();

    const auto mi = GetVehicleModelInfo();
    CMatrix mat;
    CVector pos;

    mi->GetWheelPosn(CAR_WHEEL_FRONT_LEFT, pos, false);
    SetTransmissionRotation(m_aCarNodes[MONSTER_TRANSMISSION_F], m_wheelPosition[CAR_WHEEL_FRONT_LEFT], m_wheelPosition[CAR_WHEEL_FRONT_RIGHT], pos, true);

    mi->GetWheelPosn(CAR_WHEEL_REAR_LEFT, pos, false);
    SetTransmissionRotation(m_aCarNodes[MONSTER_TRANSMISSION_R], m_wheelPosition[CAR_WHEEL_REAR_LEFT], m_wheelPosition[CAR_WHEEL_REAR_RIGHT], pos, false);

    if (m_nModelIndex == MODEL_DUMPER && m_aCarNodes[MONSTER_MISC_A]) {
        SetComponentRotation(m_aCarNodes[MONSTER_MISC_A], AXIS_X, (float)m_wMiscComponentAngle * DUMPER_COL_ANGLEMULT, true);
    }
}

// 0x6C7D80
void CMonsterTruck::ExtendSuspension() {
    plugin::CallMethod<0x6C7D80, CMonsterTruck*>(this);
}

// 0x6C7D40
void CMonsterTruck::ResetSuspension() {
    return plugin::CallMethod<0x6C7D40, CMonsterTruck*>(this);
    CAutomobile::ResetSuspension();
    std::ranges::fill(m_wheelPosition, 1.0f);
}

// 0x6C7D30
bool CMonsterTruck::BurstTyre(uint8 tyreComponentId, bool bPhysicalEffect) {
    return false;
}

// 0x6C7D20
bool CMonsterTruck::SetUpWheelColModel(CColModel* colModel) {
    return false;
}
