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
    ReversibleHooks::Install("CPlayerInfo", "LoadPlayerSkin", 0x56F7D0, &CPlayerInfo::LoadPlayerSkin);
    // ReversibleHooks::Install("CPlayerInfo", "FindClosestCarSectorList", 0x56F4E0, &CPlayerInfo::FindClosestCarSectorList);
    ReversibleHooks::Install("CPlayerInfo", "Clear", 0x56F330, &CPlayerInfo::Clear);
    ReversibleHooks::Install("CPlayerInfo", "GivePlayerParachute", 0x56EC40, &CPlayerInfo::GivePlayerParachute);
    ReversibleHooks::Install("CPlayerInfo", "StreamParachuteWeapon", 0x56EB30, &CPlayerInfo::StreamParachuteWeapon);
    ReversibleHooks::Install("CPlayerInfo", "AddHealth", 0x56EAB0, &CPlayerInfo::AddHealth);
    ReversibleHooks::Install("CPlayerInfo", "DeletePlayerSkin", 0x56EA80, &CPlayerInfo::DeletePlayerSkin);
    ReversibleHooks::Install("CPlayerInfo", "BlowUpRCBuggy", 0x56EA30, &CPlayerInfo::BlowUpRCBuggy);
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
    LoadPlayerSkin();
}

// 0x56F8D0
void CPlayerInfo::Process(uint32 playerIndex) {
    plugin::CallMethod<0x56F8D0, CPlayerInfo*, uint32>(this, playerIndex);
}

// 0x56F7D0
void CPlayerInfo::LoadPlayerSkin() {
    DeletePlayerSkin();
    m_pSkinTexture = CPlayerSkin::GetSkinTexture(m_szSkinName);
}

// 0x56F4E0
void CPlayerInfo::FindClosestCarSectorList(CPtrList& ptrList, CPed* this_mp_Ped, float minX, float minY, float maxX, float maxY, float* outVehDist, CVehicle** outVehicle) {
    plugin::CallMethod<0x56F4E0, CPlayerInfo*, CPtrList&, CPed*, float, float, float, float, float*, CVehicle**>(this, ptrList, this_mp_Ped, minX, minY, maxX, maxY, outVehDist,
                                                                                                                 outVehicle);
}

// 0x56F330
void CPlayerInfo::Clear() {
    // TODO: This should just use the constructor and `swap`,
    // like to just swap ourselves to a default constructed object
    // and do all the cleanup in the destructor

    m_pPed = nullptr;
    m_pRemoteVehicle = nullptr;
    if (m_pSpecCar) {
        m_pSpecCar->physicalFlags.bAddMovingCollisionSpeed = false;
        m_pSpecCar = nullptr;
    }
    m_nDisplayMoney = 0;
    m_nMoney = 0;
    m_nPlayerState = PLAYERSTATE_PLAYING;
    m_nCarDensityForCurrentZone = 0;
    m_fRoadDensityAroundPlayer = 1.0;
    m_bAfterRemoteVehicleExplosion = 0;
    m_bCreateRemoteVehicleExplosion = 0;
    m_bFadeAfterRemoteVehicleExplosion = 0;
    m_bTryingToExitCar = 0;
    m_bTaxiTimerScore = 0;
    m_nTaxiTimer = 0;
    m_nVehicleTimeCounter = CTimer::m_snTimeInMilliseconds;
    m_nMaxArmour = 100;
    m_nMaxHealth = 100;
    m_bCanDoDriveBy = 1;
    m_nCollectablesPickedUp = 0;
    m_nTotalNumCollectables = 3;
    m_nLastTimeEnergyLost = 0;
    m_nLastTimeArmourLost = 0;
    m_nLastTimeBigGunFired = 0;
    m_nTimesStuckInARow = 0;
    m_nTimesUpsideDownInARow = 0;
    m_nCarTwoWheelCounter = 0;
    m_fCarTwoWheelDist = 0.0;
    m_nCarLess3WheelCounter = 0;
    m_nBikeRearWheelCounter = 0;
    m_fBikeRearWheelDist = 0.0;
    m_nBikeFrontWheelCounter = 0;
    m_fBikeFrontWheelDist = 0.0;
    m_nTempBufferCounter = 0;
    m_nBestCarTwoWheelsTimeMs = 0;
    m_fBestCarTwoWheelsDistM = 0.0;
    m_nBestBikeWheelieTimeMs = 0;
    m_fBestBikeWheelieDistM = 0.0;
    m_nBestBikeStoppieTimeMs = 0;
    m_fBestBikeStoppieDistM = 0.0;
    m_bDoesNotGetTired = 0;
    m_bFastReload = 0;
    m_bFireProof = 0;
    m_bGetOutOfJailFree = 0;
    m_bFreeHealthCare = 0;
    m_nTimeOfLastCarExplosionCaused = 0;
    m_nExplosionMultiplier = 0;
    m_nHavocCaused = 0;
    CWorld::Players[CWorld::PlayerInFocus].m_nNumHoursDidntEat = 0;
    m_nLastBustMessageNumber = 1;
    m_fCurrentChaseValue = 0.0;
    m_nBustedAudioStatus = 0;
    m_nCrosshairActivated = 0;

    m_nRequireParachuteTimer = 0;

    if (m_bParachuteReferenced) {
        CGameLogic::IsCoopGameGoingOn();
        if (m_bParachuteReferenced) {
            CStreaming::SetModelIsDeletable(MODEL_GUN_PARA);
            m_bParachuteReferenced = 0;
            m_nRequireParachuteTimer = 0;
        }
    }
}

// 0x56EC40
void CPlayerInfo::GivePlayerParachute() {
    if (m_nRequireParachuteTimer) {
        if (CStreaming::IsModelLoaded(MODEL_GUN_PARA)) {
            m_pPed->GiveWeapon(WEAPON_PARACHUTE, 1, false);
            m_pPed->m_nSavedWeapon = WEAPON_PARACHUTE;
        }
    }
}

// 0x56EB30
void CPlayerInfo::StreamParachuteWeapon(bool unk) {
    if (CGameLogic::IsCoopGameGoingOn()) {
        if (unk)
            return;
    } else {
        if (m_pPed) {
            if (const auto veh = m_pPed->m_pVehicle; veh && m_pPed->bInVehicle) {
                if (veh->IsPlane() || veh->IsHeli()) {
                    if (m_nRequireParachuteTimer <= CTimer::GetTimeStepInMS()) {
                        const auto vehToGroundZDist = veh->GetPosition().z - TheCamera.CalculateGroundHeight(eGroundHeightType::ENTITY_BOUNDINGBOX_BOTTOM);
                        m_nRequireParachuteTimer = (vehToGroundZDist <= 50.f) ? 0 : 5000;
                    } else {
                        m_nRequireParachuteTimer -= CTimer::GetTimeStepInMS();
                    }
                }
            }
        }

        if (m_nRequireParachuteTimer) {
            CStreaming::RequestModel(MODEL_GUN_PARA, STREAMING_MISSION_REQUIRED);
            m_bParachuteReferenced = true;
            return;
        }
    }

    if (m_bParachuteReferenced) {
        CStreaming::SetModelIsDeletable(MODEL_GUN_PARA);
        m_bParachuteReferenced = 0;
        m_nRequireParachuteTimer = 0;
    }
}

// 0x56EAB0
void CPlayerInfo::AddHealth(int32_t amount) {
    const auto newValue = std::min((float)m_nMaxHealth, m_pPed->m_fHealth + (float)amount); // Clamp to m_nMaxHealth
    m_pPed->m_fHealth = std::max(newValue, m_pPed->m_fHealth); // Don't change health to a lower value
}

// 0x56EA80
void CPlayerInfo::DeletePlayerSkin() {
    if (m_pSkinTexture)
    {
        RwTextureDestroy(m_pSkinTexture);
        m_pSkinTexture = nullptr;
    }
}

// 0x56EA30
void CPlayerInfo::BlowUpRCBuggy(bool bExplode) {
    if (m_pRemoteVehicle && !m_pRemoteVehicle->m_bRemoveFromWorld) {
        CRemote::TakeRemoteControlledCarFromPlayer(bExplode);
        if (bExplode)
            m_pRemoteVehicle->BlowUpCar(m_pPed, false);
    }
}

// 0x56E870
void CPlayerInfo::MakePlayerSafe(bool enable, float radius) {
    // Not quite SA, but this is the way to do it (instead of copy pasting it twice)
    auto& phyFlags = m_pPed->physicalFlags;
    phyFlags.bInvulnerable = enable;
    phyFlags.bBulletProof = enable;
    phyFlags.bFireProof = enable;
    phyFlags.bExplosionProof = enable;
    phyFlags.bCollisionProof = enable;
    phyFlags.bMeeleProof = enable;
    m_PlayerData.m_bCanBeDamaged = !enable;
    m_PlayerData.m_pWanted->m_bEverybodyBackOff = enable;
    m_pPed->GetPadFromPlayer()->bPlayerSafe = enable;
    CWorld::SetAllCarsCanBeDamaged(enable);

    if (enable) {
        CWorld::StopAllLawEnforcersInTheirTracks();

        m_pPed->ClearAdrenaline();
        m_PlayerData.m_fTimeCanRun = std::max(m_PlayerData.m_fTimeCanRun, 0.f);
        m_pPed->GetIntelligence()->ClearTasks(true, false);

        gFireManager.ExtinguishPoint(GetPos(), radius);
        CExplosion::RemoveAllExplosionsInArea(GetPos(), 4000.f);
        CProjectileInfo::RemoveAllProjectiles();
        CWorld::ExtinguishAllCarFiresInArea(GetPos(), radius);
        CReplay::DisableReplays();
        m_pPed->ClearWeaponTarget();
    } else {
        CReplay::EnableReplays();
    }
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
