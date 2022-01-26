#include "StdInc.h"

#include "PlayerInfo.h"
#include "FireManager.h"

void CPlayerInfo::InjectHooks() {
    using namespace ReversibleHooks;
    // RH_ScopedInstall(Constructor, 0x571920); hooking ctor will produce bugs with weapons, you will never give weapon through cheat or something
    RH_ScopedInstall(CancelPlayerEnteringCars, 0x56E860);
    // RH_ScopedInstall(FindObjectToSteal, 0x56DBD0);
    RH_ScopedInstall(EvaluateCarPosition, 0x56DAD0);
    // RH_ScopedInstall(Process, 0x56F8D0);
    // RH_ScopedInstall(FindClosestCarSectorList, 0x56F4E0);
    RH_ScopedInstall(Clear, 0x56F330);
    RH_ScopedInstall(StreamParachuteWeapon, 0x56EB30);
    RH_ScopedInstall(AddHealth, 0x56EAB0);
    RH_ScopedInstall(ArrestPlayer, 0x56E5D0);
    RH_ScopedInstall(SetPlayerSkin, 0x5717F0);
    RH_ScopedInstall(LoadPlayerSkin, 0x56F7D0);
    RH_ScopedInstall(DeletePlayerSkin, 0x56EA80);
    RH_ScopedInstall(BlowUpRCBuggy, 0x56EA30);
    RH_ScopedInstall(MakePlayerSafe, 0x56E870);
    RH_ScopedInstall(PlayerFailedCriticalMission, 0x56E830);
    RH_ScopedInstall(WorkOutEnergyFromHunger, 0x56E610);
    RH_ScopedInstall(KillPlayer, 0x56E580);
    RH_ScopedInstall(IsRestartingAfterMissionFailed, 0x56E570);
    RH_ScopedInstall(IsRestartingAfterArrest, 0x56E560);
    RH_ScopedInstall(IsRestartingAfterDeath, 0x56E550);
    RH_ScopedInstall(IsPlayerInRemoteMode, 0x56DAB0);
    RH_ScopedInstall(GetPos_Hook, 0x56DFB0);
    RH_ScopedInstall(GetSpeed_Hook, 0x56DF50);
    RH_ScopedInstall(GivePlayerParachute, 0x56EC40);
    RH_ScopedInstall(SetLastTargetVehicle, 0x56DA80);
    RH_ScopedInstall(Load, 0x5D3B00);
    RH_ScopedInstall(Save, 0x5D3AC0);
}

// 0x571920
CPlayerInfo::CPlayerInfo() {
    plugin::CallMethod<0x571920, CPlayerInfo*>(this); // see hook
    return;

    m_PlayerData = CPlayerPedData();

    m_pSkinTexture = nullptr;
    m_bParachuteReferenced = false;
    m_nRequireParachuteTimer = 0;
}

// 0x571920
CPlayerInfo* CPlayerInfo::Constructor() {
    this->CPlayerInfo::CPlayerInfo();
    return this;
}

CVector* CPlayerInfo::GetSpeed_Hook(CVector* out) {
    *out = GetSpeed();
    return out;
}

CVector* CPlayerInfo::GetPos_Hook(CVector* outPos) {
    *outPos = GetPos();
    return outPos;
}

// 0x56E860
void CPlayerInfo::CancelPlayerEnteringCars(CVehicle* vehicle) {
    // NOP
}

// 0x56DBD0
CEntity* CPlayerInfo::FindObjectToSteal(CPed* ped) {
    return plugin::CallAndReturn<CEntity*, 0x56DBD0, CPed*>(ped);
}

// 0x56DAD0
void CPlayerInfo::EvaluateCarPosition(CEntity* car, CPed* ped, float pedToVehDist, float* outDistance, CVehicle** outVehicle) {
    const auto& carPosn = car->GetPosition();
    const auto& pedPosn = ped->GetPosition();
    const auto& forward = ped->GetForward();

    // Find our rotation (so that is, at which angle the forward vector is)
    const auto angleFront = CGeneral::GetATanOfXY(forward.x, forward.y);

    // Find car angle, not relative to our rotation
    const auto carAngle = CGeneral::GetATanOfXY(carPosn.x - pedPosn.x, carPosn.y - pedPosn.y);

    // Make car's angle relative to our rotation (notice: it's an abs value)
    // Basically, we calculate how much the car is in our FOV.
    const auto carAngleFromFront = std::abs(CGeneral::LimitRadianAngle(angleFront - carAngle));

    // Calculate imaginary distance based on the car's angle: The higher the angle the greater the distance
    const auto distance = (1.0f - carAngleFromFront / TWO_PI) * (10.0f - pedToVehDist);
    if (distance >= *outDistance) {
        *outDistance = distance;
        *outVehicle = car->AsVehicle();
    }
}

// 0x56F7D0
void CPlayerInfo::LoadPlayerSkin() {
    DeletePlayerSkin();
    m_pSkinTexture = CPlayerSkin::GetSkinTexture(m_szSkinName);
}

// 0x56EA80
void CPlayerInfo::DeletePlayerSkin() {
    if (m_pSkinTexture) {
        RwTextureDestroy(m_pSkinTexture);
        m_pSkinTexture = nullptr;
    }
}

// 0x5717F0
void CPlayerInfo::SetPlayerSkin(const char* name) {
    strcpy_s(m_szSkinName, name); // NOTSA: They used `strcpy`, we use `_s` for safety
    LoadPlayerSkin();
}

// 0x56DA80
void CPlayerInfo::SetLastTargetVehicle(CVehicle* vehicle) {
    if (m_pLastTargetVehicle)
        m_pLastTargetVehicle->CleanUpOldReference(reinterpret_cast<CEntity**>(&m_pLastTargetVehicle));

    m_pLastTargetVehicle = vehicle;
    if (vehicle)
        vehicle->RegisterReference(reinterpret_cast<CEntity**>(&m_pLastTargetVehicle));
}

// 0x56F8D0
void CPlayerInfo::Process(uint32 playerIndex) {
    plugin::CallMethod<0x56F8D0, CPlayerInfo*, uint32>(this, playerIndex);
}

// 0x56F4E0
void CPlayerInfo::FindClosestCarSectorList(CPtrList& ptrList, CPed* ped, float minX, float minY, float maxX, float maxY, float* outVehDist, CVehicle** outVehicle) {
    plugin::CallMethod<0x56F4E0, CPlayerInfo*, CPtrList&, CPed*, float, float, float, float, float*, CVehicle**>(this, ptrList, ped, minX, minY, maxX, maxY, outVehDist, outVehicle);
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
    m_fRoadDensityAroundPlayer = 1.0f;
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
    m_fCarTwoWheelDist = 0.0f;
    m_nCarLess3WheelCounter = 0;
    m_nBikeRearWheelCounter = 0;
    m_fBikeRearWheelDist = 0.0f;
    m_nBikeFrontWheelCounter = 0;
    m_fBikeFrontWheelDist = 0.0f;
    m_nTempBufferCounter = 0;
    m_nBestCarTwoWheelsTimeMs = 0;
    m_fBestCarTwoWheelsDistM = 0.0f;
    m_nBestBikeWheelieTimeMs = 0;
    m_fBestBikeWheelieDistM = 0.0f;
    m_nBestBikeStoppieTimeMs = 0;
    m_fBestBikeStoppieDistM = 0.0f;
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
    m_fCurrentChaseValue = 0.0f;
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
            m_pPed->GiveWeapon(WEAPON_PARACHUTE, 1, true);
            m_pPed->SetSavedWeapon(WEAPON_PARACHUTE);
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
                if (veh->IsSubPlane() || veh->IsSubHeli()) {
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
void CPlayerInfo::AddHealth(int32 amount) {
    const auto newValue = std::min((float)m_nMaxHealth, m_pPed->m_fHealth + (float)amount); // Clamp to m_nMaxHealth
    m_pPed->m_fHealth = std::max(newValue, m_pPed->m_fHealth); // Don't change health to a lower value
}

// 0x56EA30
void CPlayerInfo::BlowUpRCBuggy(bool bExplode) {
    if (m_pRemoteVehicle && !m_pRemoteVehicle->m_bRemoveFromWorld) {
        CRemote::TakeRemoteControlledCarFromPlayer(bExplode);
        if (bExplode)
            m_pRemoteVehicle->BlowUpCar(m_pPed, false); // todo: CWorld::Players[CWorld::PlayerInFocus].m_pPed instead m_pPed
    }
}

// 0x56E870
void CPlayerInfo::MakePlayerSafe(bool enable, float radius) {
    // Not quite SA, but this is the way to do it (instead of copy pasting it twice)
    auto& flags = m_pPed->physicalFlags;
    flags.bInvulnerable = enable;
    flags.bBulletProof = enable;
    flags.bFireProof = enable;
    flags.bExplosionProof = enable;
    flags.bCollisionProof = enable;
    flags.bMeeleProof = enable;
    m_PlayerData.m_bCanBeDamaged = !enable;
    m_PlayerData.m_pWanted->m_bEverybodyBackOff = enable;
    m_pPed->GetPadFromPlayer()->bPlayerSafe = enable;
    CWorld::SetAllCarsCanBeDamaged(!enable);

    if (enable) {
        CWorld::StopAllLawEnforcersInTheirTracks();
        // todo: CPad::StopPadsShaking();

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
    if (m_nPlayerState == PLAYERSTATE_PLAYING) {
        m_nPlayerState = PLAYERSTATE_FAILED_MISSION;
        CGameLogic::GameState = GAME_STATE_TITLE;
        CGameLogic::TimeOfLastEvent = CTimer::GetTimeInMS();
        CDarkel::ResetOnPlayerDeath();
    }
}

// 0x56E610
void CPlayerInfo::WorkOutEnergyFromHunger() {
    static int8 s_lastTimeHungryStateProcessed = CClock::GetGameClockHours(); // 0xB9B8F2
    static int8 s_LastHungryState;                                            // 0xB9B8F1
    static bool s_bHungryMessageShown;                                        // 0xB9B8F0

    if (CCheat::m_aCheatsActive[CHEAT_NEVER_GET_HUNGRY]) {
        return;
    }

    auto pad = CPad::GetPad(0);
    if (   pad->DisablePlayerControls
        || CMenuSystem::num_menus_in_use
        || TheCamera.m_bWideScreenOn
        || CCutsceneMgr::ms_running
        || CGameLogic::IsCoopGameGoingOn()
        || m_pRemoteVehicle
    ) {
        return;
    }

    if (!m_pPed)
        return;

    if (m_pPed->m_pAttachedTo)
        return;

    if (CClock::GetGameClockHours() != s_lastTimeHungryStateProcessed) {
        if (!m_nNumHoursDidntEat)
            s_LastHungryState = 0;
        m_nNumHoursDidntEat += 1;
    }

    if (m_nNumHoursDidntEat <= 48) {
        s_bHungryMessageShown = false;
    } else {
        if (CClock::GetGameClockHours() == s_lastTimeHungryStateProcessed)
            return;

        m_pPed->Say(337);
        pad->StartShake(400, 110u, 0);

        if (s_bHungryMessageShown) {
            bool bDecreaseHealth{};
            if (CStats::GetStatValue(STAT_FAT) > 0.0f) {
                CStats::DecrementStat(STAT_FAT, 25.0f);
                CStats::DisplayScriptStatUpdateMessage(0, STAT_FAT, 25.0f);
                bDecreaseHealth = true;
                if (!s_LastHungryState)
                    s_LastHungryState = m_nNumHoursDidntEat + 24;
            }

            if (CStats::GetStatValue(STAT_MUSCLE) <= 0.0f || m_nNumHoursDidntEat <= s_LastHungryState && s_LastHungryState) {
                if (!bDecreaseHealth)
                    m_pPed->m_fHealth -= 2.0f;
            } else {
                CStats::DecrementStat(STAT_MUSCLE, 25.0);
                CStats::DisplayScriptStatUpdateMessage(0, STAT_MUSCLE, 25.0f);
            }
        } else {
            CHud::SetHelpMessage(TheText.Get("NOTEAT"), true, false, true);
            s_bHungryMessageShown = true;
        }
    }

    if (CClock::GetGameClockHours() != s_lastTimeHungryStateProcessed)
        s_lastTimeHungryStateProcessed = CClock::GetGameClockHours();
    
}

// 0x56E5D0
void CPlayerInfo::ArrestPlayer() {
    if (m_nPlayerState == PLAYERSTATE_PLAYING) {
        m_nPlayerState = PLAYERSTATE_HAS_BEEN_ARRESTED;
        m_nBustedAudioStatus = 0;
        CDarkel::ResetOnPlayerDeath();
        CStats::IncrementStat(STAT_TIMES_BUSTED, 1.0f);
        CGangWars::EndGangWar(false);
    }
}

// 0x56E580
void CPlayerInfo::KillPlayer() {
    if (m_nPlayerState == PLAYERSTATE_PLAYING) {
        m_nPlayerState = PLAYERSTATE_HAS_DIED;
        CDarkel::ResetOnPlayerDeath();
        CMessages::AddBigMessage(TheText.Get("DEAD"), 4000, STYLE_WHITE_MIDDLE);
        CStats::IncrementStat(STAT_NUMBER_OF_HOSPITAL_VISITS, 1.0f);
        CGangWars::EndGangWar(0);
    }
}

// 0x56E570
bool CPlayerInfo::IsRestartingAfterMissionFailed() {
    return m_nPlayerState == PLAYERSTATE_FAILED_MISSION;
}

// 0x56E560
bool CPlayerInfo::IsRestartingAfterArrest() {
    return m_nPlayerState == PLAYERSTATE_HAS_BEEN_ARRESTED;
}

// 0x56E550
bool CPlayerInfo::IsRestartingAfterDeath() {
    return m_nPlayerState == PLAYERSTATE_HAS_DIED;
}

// 0x56DAB0
bool CPlayerInfo::IsPlayerInRemoteMode() {
    return m_pRemoteVehicle || m_bAfterRemoteVehicleExplosion;
}

// 0x56DFB0
// Return occupied vehicle's (if in any) or player's ped position
CVector CPlayerInfo::GetPos() {
    if (m_pPed->bInVehicle && m_pPed->m_pVehicle)
        return m_pPed->m_pVehicle->GetPosition();
    return m_pPed->GetPosition();
}

// 0x56DF50
// Return occupied vehicle's (if in any) or player's ped move speed
CVector CPlayerInfo::GetSpeed() {
    if (m_pPed->bInVehicle && m_pPed->m_pVehicle)
        return m_pPed->m_pVehicle->m_vecMoveSpeed;
    return m_pPed->m_vecMoveSpeed;
}

// 0x5D3B00
bool CPlayerInfo::Load() {
    int32 dataSize;
    CPlayerInfoSaveStructure data;
    CGenericGameStorage::LoadDataFromWorkBuffer(&dataSize, sizeof(dataSize));
    CGenericGameStorage::LoadDataFromWorkBuffer(&data, sizeof(CPlayerInfoSaveStructure));
    data.Extract(this);
    return true;
}

// 0x5D3AC0
bool CPlayerInfo::Save() {
    int32 dataSize{ sizeof(CPlayerInfoSaveStructure) };
    CPlayerInfoSaveStructure data;
    data.Construct(this);
    CGenericGameStorage::SaveDataToWorkBuffer(&dataSize, sizeof(dataSize));
    CGenericGameStorage::SaveDataToWorkBuffer(&data, sizeof(data));
    return true;
}
