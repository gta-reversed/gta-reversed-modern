#include "StdInc.h"

#include "Trailer.h"

static float& TRAILER_TOWED_MINRATIO = *(float*)0x8D346C;       // 0.9f
static float& RELINK_TRAILER_DIFF_LIMIT_XY = *(float*)0x8D3470; // 0.4f
static float& RELINK_TRAILER_DIFF_LIMIT_Z = *(float*)0x8D3474;  // 1.0f
static float& m_fTrailerSuspensionForce = *(float*)0x8D3464;    // 1.5f
static float& m_fTrailerDampingForce = *(float*)0x8D3468;       // 0.1f

void CTrailer::InjectHooks() {
    RH_ScopedClass(CTrailer);
    RH_ScopedCategory("Vehicle");

    RH_ScopedInstall(Constructor, 0x6D03A0);
    // RH_ScopedInstall(SetupSuspensionLines, 0x6CF1A0);
    // RH_ScopedInstall(SetTowLink, 0x6CFDF0);
    // RH_ScopedInstall(ScanForTowLink, 0x6CF030);
    RH_ScopedInstall(ResetSuspension, 0x6CEE50);
    // RH_ScopedInstall(ProcessSuspension, 0x6CF6A0);
    // RH_ScopedInstall(ProcessEntityCollision, 0x6CFFD0);
    // RH_ScopedInstall(ProcessControl, 0x6CED20);
    // RH_ScopedInstall(ProcessAI, 0x6CF590);
    // RH_ScopedInstall(PreRender, 0x6CFAC0);
    // RH_ScopedInstall(GetTowHitchPos, 0x6CEEA0);
    // RH_ScopedInstall(GetTowBarPos, 0x6CFD60);
    // RH_ScopedInstall(BreakTowLink, 0x6CEFB0);
}

// 0x6D03A0
CTrailer::CTrailer(int32 modelIndex, eVehicleCreatedBy createdBy) : CAutomobile(modelIndex, createdBy, false) {
    m_fTrailerColPointValue1 = 1.0f;
    m_fTrailerColPointValue2 = 1.0f;
    m_fTrailerTowedRatio     = 1.0f;
    m_fTrailerTowedRatio2    = 1.0f;

    m_nVehicleSubType = VEHICLE_TYPE_TRAILER;

    if (m_nModelIndex == MODEL_BAGBOXA || m_nModelIndex == MODEL_BAGBOXB)
        m_fTrailerTowedRatio = -1000.0f;

    SetupSuspensionLines();

    m_nStatus = eEntityStatus::STATUS_ABANDONED;
}

// 0x6CF1A0
void CTrailer::SetupSuspensionLines() {
    plugin::CallMethod<0x6CF1A0, CTrailer*>(this);
}

// 0x6CFDF0
bool CTrailer::SetTowLink(CVehicle* tractor, bool setMyPosToTowBar) {
    return plugin::CallMethodAndReturn<bool, 0x6CFDF0, CTrailer*, CVehicle*, bool>(this, tractor, setMyPosToTowBar);
}

// 0x6CF030
void CTrailer::ScanForTowLink() {
    plugin::CallMethod<0x6CF030, CTrailer*>(this);
}

// 0x6CEE50
void CTrailer::ResetSuspension() {
    CAutomobile::ResetSuspension();
    m_fTrailerColPointValue1 = 1.0f;
    m_fTrailerColPointValue2 = 1.0f;
    if (m_pTractor && m_fTrailerTowedRatio > -1000.0f)
        m_fTrailerTowedRatio = 0.0f;
    else
        m_fTrailerTowedRatio = 1.0f;
}

// 0x6CF6A0
void CTrailer::ProcessSuspension() {
    plugin::CallMethod<0x6CF6A0, CTrailer*>(this);
}

// 0x6CFFD0
int32 CTrailer::ProcessEntityCollision(CEntity* entity, CColPoint* colPoint) {
    return plugin::CallMethodAndReturn<int32, 0x6CFFD0, CTrailer*, CEntity*, CColPoint*>(this, entity, colPoint);
}

// 0x6CED20
void CTrailer::ProcessControl() {
    plugin::CallMethod<0x6CED20, CTrailer*>(this);
}

// 0x6CF590
bool CTrailer::ProcessAI(uint32& extraHandlingFlags) {
    return plugin::CallMethodAndReturn<bool, 0x6CF590, CTrailer*, uint32&>(this, extraHandlingFlags);
}

// 0x6CFAC0
void CTrailer::PreRender() {
    plugin::CallMethod<0x6CFAC0, CTrailer*>(this);
}

// 0x6CEEA0
bool CTrailer::GetTowHitchPos(CVector& outPos, bool bCheckModelInfo, CVehicle* vehicle) {
    return plugin::CallMethodAndReturn<bool, 0x6CEEA0, CTrailer*, CVector&, bool, CVehicle*>(this, outPos, bCheckModelInfo, vehicle);
}

// 0x6CFD60
bool CTrailer::GetTowBarPos(CVector& outPos, bool bCheckModelInfo, CVehicle* vehicle) {
    return plugin::CallMethodAndReturn<bool, 0x6CFD60, CTrailer*, CVector&, bool, CVehicle*>(this, outPos, bCheckModelInfo, vehicle);
}

// 0x6CEFB0
bool CTrailer::BreakTowLink() {
    return plugin::CallMethodAndReturn<bool, 0x6CEFB0, CTrailer*>(this);
}
