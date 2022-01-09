#include "StdInc.h"

#include "QuadBike.h"

void CQuadBike::InjectHooks() {
//    ReversibleHooks::Install("CQuadBike", "CQuadBike", 0x6CE370, &CQuadBike::Constructor);
//    ReversibleHooks::Install("CQuadBike", "CQuadBike", 0x6CDC30, &CQuadBike::Destructor);
//    ReversibleHooks::Install("CQuadBike", "Fix", 0x6CE2B0, &CQuadBike::Fix_Reversed);
    ReversibleHooks::Install("CQuadBike", "GetRideAnimData", 0x6CDC90, &CQuadBike::GetRideAnimData_Reversed);
//    ReversibleHooks::Install("CQuadBike", "PreRender", 0x6CEAD0, &CQuadBike::PreRender_Reversed);
//    ReversibleHooks::Install("CQuadBike", "ProcessAI", 0x6CE460, &CQuadBike::ProcessAI_Reversed);
//    ReversibleHooks::Install("CQuadBike", "ProcessControl", 0x6CDCC0, &CQuadBike::ProcessControl_Reversed);
//    ReversibleHooks::Install("CQuadBike", "ProcessControlInputs", 0x6CE020, &CQuadBike::ProcessControlInputs_Reversed);
//    ReversibleHooks::Install("CQuadBike", "ProcessDrivingAnims", 0x6CE280, &CQuadBike::ProcessDrivingAnims_Reversed);
    ReversibleHooks::Install("CQuadBike", "ProcessSuspension", 0x6CE270, &CQuadBike::ProcessSuspension_Reversed);
    ReversibleHooks::Install("CQuadBike", "ResetSuspension", 0x6CDCB0, &CQuadBike::ResetSuspension_Reversed);
    ReversibleHooks::Install("CQuadBike", "SetupDamageAfterLoad", 0x6CE340, &CQuadBike::SetupDamageAfterLoad_Reversed);
    ReversibleHooks::Install("CQuadBike", "SetupSuspensionLines", 0x6CDCA0, &CQuadBike::SetupSuspensionLines_Reversed);
}

// 0x6CE370
CQuadBike::CQuadBike(int32 modelIndex, eVehicleCreatedBy createdBy) :CAutomobile(plugin::dummy) {
    plugin::CallMethod<0x6CE370, CQuadBike*, int32, eVehicleCreatedBy>(this, modelIndex, createdBy);
}

// 0x6CDC30
CQuadBike::~CQuadBike() {
    plugin::CallMethod<0x6CDC30, CQuadBike*>(this);
}

// 0x6CE2B0
void CQuadBike::Fix() {
    Fix_Reversed();
}

void CQuadBike::Fix_Reversed() {
    plugin::CallMethod<0x6CE2B0, CQuadBike*>(this);
}

// 0x6CDC90
CRideAnimData* CQuadBike::GetRideAnimData() {
    return GetRideAnimData_Reversed();
}

CRideAnimData* CQuadBike::GetRideAnimData_Reversed() {
    return &m_sRideAnimData;
}

// 0x6CEAD0
void CQuadBike::PreRender() {
    PreRender_Reversed();
}

void CQuadBike::PreRender_Reversed() {
    plugin::CallMethod<0x6CEAD0, CQuadBike*>(this);
}

// 0x6CE460
bool CQuadBike::ProcessAI(uint32& extraHandlingFlags) {
    return ProcessAI_Reversed(extraHandlingFlags);
}

bool CQuadBike::ProcessAI_Reversed(uint32& extraHandlingFlags) {
    return plugin::CallMethodAndReturn<bool, 0x6CE460, CQuadBike*, uint32>(this, extraHandlingFlags);
}

// 0x6CDCC0
void CQuadBike::ProcessControl() {
    ProcessControl_Reversed();
}

void CQuadBike::ProcessControl_Reversed() {
    plugin::CallMethod<0x6CDCC0, CQuadBike*>(this);
}

// 0x6CE020
void CQuadBike::ProcessControlInputs(uint8 playerNum) {
    ProcessControlInputs_Reversed(playerNum);
}

void CQuadBike::ProcessControlInputs_Reversed(uint8 playerNum) {
    plugin::CallMethod<0x6CE020, CQuadBike*, uint8>(this, playerNum);
}

// 0x6CE280
void CQuadBike::ProcessDrivingAnims(CPed* driver, uint8 bBlend) {
    ProcessDrivingAnims_Reversed(driver, bBlend);
}

void CQuadBike::ProcessDrivingAnims_Reversed(CPed* driver, uint8 bBlend) {
    plugin::CallMethod<0x6CE280, CQuadBike*, CPed*, uint8>(this, driver, bBlend);
}

// 0x6CE270
void CQuadBike::ProcessSuspension() {
    ProcessSuspension_Reversed();
}

void CQuadBike::ProcessSuspension_Reversed() {
    CAutomobile::ProcessSuspension();
}

// 0x6CDCB0
void CQuadBike::ResetSuspension() {
    ResetSuspension_Reversed();
}

void CQuadBike::ResetSuspension_Reversed() {
    CAutomobile::ResetSuspension();
}

// 0x6CE340
void CQuadBike::SetupDamageAfterLoad() {
    SetupDamageAfterLoad_Reversed();
}

void CQuadBike::SetupDamageAfterLoad_Reversed() {
    if (m_aCarNodes[QUAD_BODY_FRONT])
        CAutomobile::SetBumperDamage(FRONT_BUMPER, false);

    if (m_aCarNodes[QUAD_BODY_REAR])
        CAutomobile::SetDoorDamage(DOOR_BONNET, false);
}

// 0x6CDCA0
void CQuadBike::SetupSuspensionLines() {
    SetupSuspensionLines_Reversed();
}

void CQuadBike::SetupSuspensionLines_Reversed() {
    field_9A8 = 1.0f;
    CAutomobile::SetupSuspensionLines();
}
