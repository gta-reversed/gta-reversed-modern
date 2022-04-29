#include "StdInc.h"

void CBmx::InjectHooks() {
    RH_ScopedClass(CBmx);
    RH_ScopedCategory("Vehicle");

    RH_ScopedVirtualInstall(SetUpWheelColModel, 0x6BF9B0);
    RH_ScopedVirtualInstall(BurstTyre, 0x6BF9C0);
    RH_ScopedVirtualInstall(FindWheelWidth, 0x6C0550);
}

CBmx::CBmx(int32 modelIndex, eVehicleCreatedBy createdBy) : CBike(plugin::dummy) {
    plugin::CallMethod<0x6BF820, CBmx*, int32, eVehicleCreatedBy>(this, modelIndex, createdBy);
}

// 0x6BF9D0
CBmx::~CBmx() {
    m_vehicleAudio.Terminate();
}

// 0x6BF9B0
bool CBmx::SetUpWheelColModel(CColModel* wheelCol) {
    return false;
}

// 0x6BF9C0
bool CBmx::BurstTyre(uint8 tyreComponentId, bool bPhysicalEffect) {
    return false;
}

// 0x6BFA30
void CBmx::ProcessControl() {
    plugin::CallMethod<0x6BFA30, CBmx*>(this);
}

// 0x6BFB50
void CBmx::ProcessDrivingAnims(CPed* driver, uint8 bBlend) {
    plugin::CallMethod<0x6BFB50, CBmx*, CPed*, uint8>(this, driver, bBlend);
}

// 0x6C0390
void CBmx::LaunchBunnyHopCB(CAnimBlendAssociation* blendAssoc, void* data) {
    plugin::Call<0x6C0390, CAnimBlendAssociation*, void*>(blendAssoc, data);
}

// 0x6C0500 | inlined | see 0x6C11F3
void CBmx::GetFrameOffset(float& a1, float& a2) {
    const auto d1 = m_aWheelFrontPosition - m_aWheelBaseFrontPosition;
    const auto d2 = m_aWheelRearPosition - m_aWheelBaseRearPosition;

    a1 = (1.0f - m_f830) * d1 + d2 * m_f830;
    a2 = atan2(d1 - d2, m_fWheelsBalance);
}

// 0x6C0550
float CBmx::FindWheelWidth(bool bRear) {
    return 0.07f;
}

// 0x6C0560
void CBmx::BlowUpCar(CEntity* damager, uint8 bHideExplosion) {
    // NOP
}

// 0x6C0590
void CBmx::ProcessBunnyHop() {
    plugin::CallMethod<0x6C0590, CBmx*>(this);
}

// 0x6C0810
void CBmx::PreRender() {
    plugin::CallMethod<0x6C0810, CBmx*>(this);
}

// 0x6C1470
bool CBmx::ProcessAI(uint32& extraHandlingFlags) {
    return plugin::CallMethodAndReturn<bool, 0x6C1470, CBmx*, uint32>(this, extraHandlingFlags);
}
