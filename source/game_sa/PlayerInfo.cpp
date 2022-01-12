#include "StdInc.h"
#include "PlayerInfo.h"

void CPlayerInfo::InjectHooks() {
    // Constructors (1x)
    // ReversibleHooks::Install("CPlayerInfo", "CPlayerInfo", 0x571920, &CPlayerInfo::Constructor);

    // Static functions (3x)
    // ReversibleHooks::Install("CPlayerInfo", "CancelPlayerEnteringCars", 0x56E860, &CPlayerInfo::CancelPlayerEnteringCars);
    // ReversibleHooks::Install("CPlayerInfo", "FindObjectToSteal", 0x56DBD0, &CPlayerInfo::FindObjectToSteal);
    // ReversibleHooks::Install("CPlayerInfo", "EvaluateCarPosition", 0x56DAD0, &CPlayerInfo::EvaluateCarPosition);

    // Methods (24x)
    // ReversibleHooks::Install("CPlayerInfo", "destructor", 0x45B110, &CPlayerInfo::destructor);
    ReversibleHooks::Install("CPlayerInfo", "SetPlayerSkin", 0x5717F0, &CPlayerInfo::SetPlayerSkin);
    // ReversibleHooks::Install("CPlayerInfo", "Process", 0x56F8D0, &CPlayerInfo::Process);
    // ReversibleHooks::Install("CPlayerInfo", "LoadPlayerSkin", 0x56F7D0, &CPlayerInfo::LoadPlayerSkin);
    // ReversibleHooks::Install("CPlayerInfo", "FindClosestCarSectorList", 0x56F4E0, &CPlayerInfo::FindClosestCarSectorList);
    // ReversibleHooks::Install("CPlayerInfo", "Clear", 0x56F330, &CPlayerInfo::Clear);
    // ReversibleHooks::Install("CPlayerInfo", "GivePlayerParachute", 0x56EC40, &CPlayerInfo::GivePlayerParachute);
    // ReversibleHooks::Install("CPlayerInfo", "StreamParachuteWeapon", 0x56EB30, &CPlayerInfo::StreamParachuteWeapon);
    // ReversibleHooks::Install("CPlayerInfo", "AddHealth", 0x56EAB0, &CPlayerInfo::AddHealth);
    // ReversibleHooks::Install("CPlayerInfo", "DeletePlayerSkin", 0x56EA80, &CPlayerInfo::DeletePlayerSkin);
    // ReversibleHooks::Install("CPlayerInfo", "BlowUpRCBuggy", 0x56EA30, &CPlayerInfo::BlowUpRCBuggy);
    // ReversibleHooks::Install("CPlayerInfo", "MakePlayerSafe", 0x56E870, &CPlayerInfo::MakePlayerSafe);
    // ReversibleHooks::Install("CPlayerInfo", "PlayerFailedCriticalMission", 0x56E830, &CPlayerInfo::PlayerFailedCriticalMission);
    // ReversibleHooks::Install("CPlayerInfo", "WorkOutEnergyFromHunger", 0x56E610, &CPlayerInfo::WorkOutEnergyFromHunger);
    // ReversibleHooks::Install("CPlayerInfo", "ArrestPlayer", 0x56E5D0, &CPlayerInfo::ArrestPlayer);
    // ReversibleHooks::Install("CPlayerInfo", "KillPlayer", 0x56E580, &CPlayerInfo::KillPlayer);
    // ReversibleHooks::Install("CPlayerInfo", "IsRestartingAfterMissionFailed", 0x56E570, &CPlayerInfo::IsRestartingAfterMissionFailed);
    // ReversibleHooks::Install("CPlayerInfo", "IsRestartingAfterArrest", 0x56E560, &CPlayerInfo::IsRestartingAfterArrest);
    // ReversibleHooks::Install("CPlayerInfo", "IsRestartingAfterDeath", 0x56E550, &CPlayerInfo::IsRestartingAfterDeath);
    // ReversibleHooks::Install("CPlayerInfo", "GetPos", 0x56DFB0, &CPlayerInfo::GetPos);
    // ReversibleHooks::Install("CPlayerInfo", "GetSpeed", 0x56DF50, &CPlayerInfo::GetSpeed);
    // ReversibleHooks::Install("CPlayerInfo", "IsPlayerInRemoteMode", 0x56DAB0, &CPlayerInfo::IsPlayerInRemoteMode);
    // ReversibleHooks::Install("CPlayerInfo", "SetLastTargetVehicle", 0x56DA80, &CPlayerInfo::SetLastTargetVehicle);
    // ReversibleHooks::Install("CPlayerInfo", "Save", 0x5D3AC0, &CPlayerInfo::Save);
}

// 0x571920
CPlayerInfo::CPlayerInfo() {}

CVector* CPlayerInfo::GetSpeed_Hook(CVector* out) {
    *out = GetSpeed();
    return out;
}

CVector* CPlayerInfo::GetPos_Hook(CVector* outPos)
{
    *outPos = GetPos();
    return outPos;
}

// 0x571920
CPlayerInfo* CPlayerInfo::Constructor() {
    this->CPlayerInfo::CPlayerInfo();
    return this;
}

// Static functions
// 0x56E860
void CPlayerInfo::CancelPlayerEnteringCars(CVehicle* a1) {
    plugin::Call<0x56E860, CVehicle*>(a1);
}

// 0x56DBD0
CEntity* CPlayerInfo::FindObjectToSteal(CPed* this_mpPed) {
    return plugin::CallAndReturn<CEntity*, 0x56DBD0, CPed*>(this_mpPed);
}

// 0x56DAD0
void CPlayerInfo::EvaluateCarPosition(CEntity* car, CPed* this_mpPed, float pedToVehDist, float* outDistance, CVehicle** outVehicle) {
    plugin::Call<0x56DAD0, CEntity*, CPed*, float, float*, CVehicle**>(car, this_mpPed, pedToVehDist, outDistance, outVehicle);
}

// Methods
// 0x45B110
void CPlayerInfo::Destructor() {
    plugin::CallMethod<0x45B110, CPlayerInfo*>(this);
}

// 0x5717F0
void CPlayerInfo::SetPlayerSkin(char const* name) {
    strcpy_s(m_szSkinName, name); // NOTSA: They used `strcpy`, we use `_s` for safety
    if (m_pSkinTexture) {
        RwTextureDestroy(m_pSkinTexture);
        m_pSkinTexture = nullptr;
    }
    m_pSkinTexture = CPlayerSkin::GetSkinTexture(name);
}

// 0x56F8D0
void CPlayerInfo::Process(uint32 playerIndex) {
    plugin::CallMethod<0x56F8D0, CPlayerInfo*, uint32>(this, playerIndex);
}

// 0x56F7D0
void CPlayerInfo::LoadPlayerSkin() {
    plugin::CallMethod<0x56F7D0, CPlayerInfo*>(this);
}

// 0x56F4E0
void CPlayerInfo::FindClosestCarSectorList(CPtrList& ptrList, CPed* this_mp_Ped, float minX, float minY, float maxX, float maxY, float* outVehDist, CVehicle** outVehicle) {
    plugin::CallMethod<0x56F4E0, CPlayerInfo*, CPtrList&, CPed*, float, float, float, float, float*, CVehicle**>(this, ptrList, this_mp_Ped, minX, minY, maxX, maxY, outVehDist,
                                                                                                                 outVehicle);
}

// 0x56F330
void CPlayerInfo::Clear() {
    plugin::CallMethod<0x56F330, CPlayerInfo*>(this);
}

// 0x56EC40
void CPlayerInfo::GivePlayerParachute() {
    plugin::CallMethod<0x56EC40, CPlayerInfo*>(this);
}

// 0x56EB30
void CPlayerInfo::StreamParachuteWeapon(bool a2) {
    plugin::CallMethod<0x56EB30, CPlayerInfo*, bool>(this, a2);
}

// 0x56EAB0
void CPlayerInfo::AddHealth(int32_t amount) {
    plugin::CallMethod<0x56EAB0, CPlayerInfo*, int32_t>(this, amount);
}

// 0x56EA80
void CPlayerInfo::DeletePlayerSkin() {
    plugin::CallMethod<0x56EA80, CPlayerInfo*>(this);
}

// 0x56EA30
void CPlayerInfo::BlowUpRCBuggy(bool bExplode) {
    plugin::CallMethod<0x56EA30, CPlayerInfo*, bool>(this, bExplode);
}

// 0x56E870
void CPlayerInfo::MakePlayerSafe(bool canMove, float radius) {
    plugin::CallMethod<0x56E870, CPlayerInfo*, bool>(this, canMove, radius);
}

// 0x56E830
void CPlayerInfo::PlayerFailedCriticalMission() {
    plugin::CallMethod<0x56E830, CPlayerInfo*>(this);
}

// 0x56E610
void CPlayerInfo::WorkOutEnergyFromHunger() {
    plugin::CallMethod<0x56E610, CPlayerInfo*>(this);
}

// 0x56E5D0
void CPlayerInfo::ArrestPlayer() {
    plugin::CallMethod<0x56E5D0, CPlayerInfo*>(this);
}

// 0x56E580
void CPlayerInfo::KillPlayer() {
    plugin::CallMethod<0x56E580, CPlayerInfo*>(this);
}

// 0x56E570
bool CPlayerInfo::IsRestartingAfterMissionFailed() {
    return plugin::CallMethodAndReturn<bool, 0x56E570, CPlayerInfo*>(this);
}

// 0x56E560
bool CPlayerInfo::IsRestartingAfterArrest() {
    return plugin::CallMethodAndReturn<bool, 0x56E560, CPlayerInfo*>(this);
}

// 0x56E550
bool CPlayerInfo::IsRestartingAfterDeath() {
    return plugin::CallMethodAndReturn<bool, 0x56E550, CPlayerInfo*>(this);
}

// 0x56DFB0
CVector CPlayerInfo::GetPos() {
    CVector result{};
    plugin::CallMethodAndReturn<CVector*, 0x56DFB0, CPlayerInfo*, CVector*>(this, &result);
    return result;
}

// 0x56DF50
CVector CPlayerInfo::GetSpeed() {
    CVector result{};
    plugin::CallMethodAndReturn<CVector*, 0x56DF50, CPlayerInfo*, CVector*>(this, &result);
    return result;
}

// 0x56DAB0
bool CPlayerInfo::IsPlayerInRemoteMode() {
    return plugin::CallMethodAndReturn<bool, 0x56DAB0, CPlayerInfo*>(this);
}

// 0x56DA80
void CPlayerInfo::SetLastTargetVehicle(CVehicle* targetveh) {
    plugin::CallMethod<0x56DA80, CPlayerInfo*, CVehicle*>(this, targetveh);
}

// 0x5D3AC0
int8_t CPlayerInfo::Save() {
    return plugin::CallMethodAndReturn<int8_t, 0x5D3AC0, CPlayerInfo*>(this);
}
