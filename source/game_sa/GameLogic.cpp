#include "StdInc.h"
#include <enumerate.hpp>
#include <MBlur.h>
#include <EntryExitManager.h>
#include <Garages.h>
#include "PedClothesDesc.h"
#include "PostEffects.h"

//CGameLogic::SavedWeaponSlots
int32& CGameLogic::nPrintFocusHelpCounter = *reinterpret_cast<int32*>(0x96A8B8);
int32& CGameLogic::nPrintFocusHelpTimer = *reinterpret_cast<int32*>(0x96A8B4);
float& CGameLogic::f2PlayerStartHeading = *reinterpret_cast<float*>(0x96A840);
CVector& CGameLogic::vec2PlayerStartLocation = *reinterpret_cast<CVector*>(0x96A9AC);
bool& CGameLogic::bPlayersCanBeInSeparateCars = *reinterpret_cast<bool*>(0x96A8B3);
bool& CGameLogic::bPlayersCannotTargetEachOther = *reinterpret_cast<bool*>(0x96A8B2);

//CGameLogic::AfterDeathStartPointOrientations[16] = 0x96A850;
int32& CGameLogic::NumAfterDeathStartPoints = *reinterpret_cast<int32*>(0x96A890);

bool& CGameLogic::SkipToBeFinishedByScript = *reinterpret_cast<bool*>(0x96A894);
CVehicle*& CGameLogic::SkipVehicle = *reinterpret_cast<CVehicle**>(0x96A898);
uint32& CGameLogic::SkipTimer = *reinterpret_cast<uint32*>(0x96A89C);
eSkipState& CGameLogic::SkipState = *reinterpret_cast<eSkipState*>(0x96A8A0);
//CGameLogic::SkipDestinationOrientation
//CGameLogic::SkipDestination

bool& CGameLogic::bScriptCoopGameGoingOn = *reinterpret_cast<bool*>(0x96A8A8);
int32& CGameLogic::TimeOfLastEvent = *reinterpret_cast<int32*>(0x96A8AC);
eGameState& CGameLogic::GameState = *reinterpret_cast<eGameState*>(0x96A8B0);
int32& CGameLogic::ActivePlayers = *reinterpret_cast<int32*>(0x96A8B1);

bool& CGameLogic::bPenaltyForDeathApplies = *reinterpret_cast<bool*>(0x8A5E48);
bool& CGameLogic::bPenaltyForArrestApplies = *reinterpret_cast<bool*>(0x8A5E49);
bool& CGameLogic::bLimitPlayerDistance = *reinterpret_cast<bool*>(0x8A5E4A);
float& CGameLogic::MaxPlayerDistance = *reinterpret_cast<float*>(0x8A5E4C); // default 20.0
int32& CGameLogic::n2PlayerPedInFocus = *reinterpret_cast<int32*>(0x8A5E50); // default 2

static std::array<CWeapon, NUM_WEAPON_SLOTS>& s_SavedWeapons = *(std::array<CWeapon, NUM_WEAPON_SLOTS>*)0x96A9B8;

// 0x8A5E58; San Fierro
static const CVector town2ShapeVertices[] = {
    {28.0, -3000.0, 0.0},
    {-30.0, -1280.0, 0.0},
    {-148.0, -911.0, 0.0},
    {-487.0, -372.0, 0.0},
    {-1028.0, -424.0, 0.0},
    {-1145.0, 479.0, 0.0},
    {-1461.0, 1488.0, 0.0},
    {-3000.0, 1668.0, 0.0},
    {-3000.0, -3000.0, 0.0}
};

// 0x8A5EC8; Las Venturas
static const CVector town1ShapeVertices[] = {
    {3000.0f, 535.0f, 0.0f},
    {1759.0f, 576.0f, 0.0f},
    {989.0f, 693.0f, 0.0f},
    {-128.0f, 490.0f, 0.0f},
    {-845.0f, 707.0f, 0.0f},
    {-1477.0f, 1677.0f, 0.0f},
    {-2154.0f, 2497.0f, 0.0f},
    {-2971.0f, 2180.0f, 0.0f},
    {-3000.0f, 3000.0f, 0.0f},
    {3000.0f, 3000.0f, 0.0f}
};

void CGameLogic::InjectHooks() {
    RH_ScopedClass(CGameLogic);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(CalcDistanceToForbiddenTrainCrossing, 0x4418E0, { .reversed = false });
    RH_ScopedInstall(ClearSkip, 0x441560);
    RH_ScopedInstall(DoWeaponStuffAtStartOf2PlayerGame, 0x4428B0);
    RH_ScopedInstall(FindCityClosestToPoint, 0x441B70);
    RH_ScopedInstall(ForceDeathRestart, 0x441240);
    RH_ScopedInstall(InitAtStartOfGame, 0x441210);
    RH_ScopedInstall(IsCoopGameGoingOn, 0x441390);
    RH_ScopedInstall(IsPlayerAllowedToGoInThisDirection, 0x441E10, { .reversed = false });
    RH_ScopedInstall(IsPlayerUse2PlayerControls, 0x442020);
    RH_ScopedInstall(IsPointWithinLineArea, 0x4416E0);
    RH_ScopedInstall(IsSkipWaitingForScriptToFadeIn, 0x4416C0);
    RH_ScopedInstall(LaRiotsActiveHere, 0x441C10);
    RH_ScopedInstall(Save, 0x5D33C0, { .reversed = false });
    RH_ScopedInstall(Load, 0x5D3440, { .reversed = false });
    RH_ScopedInstall(PassTime, 0x4414C0);
    RH_ScopedInstall(Remove2ndPlayerIfPresent, 0x4413C0);
    RH_ScopedInstall(ResetStuffUponResurrection, 0x442980);
    RH_ScopedInstall(StorePedsWeapons, 0x441D00);
    RH_ScopedInstall(RestorePedsWeapons, 0x441D30);
    RH_ScopedInstall(RestorePlayerStuffDuringResurrection, 0x442060);
    RH_ScopedInstall(SetPlayerWantedLevelForForbiddenTerritories, 0x441770);
    RH_ScopedInstall(SetUpSkip, 0x4423C0);
    RH_ScopedInstall(SkipCanBeActivated, 0x4415C0);
    RH_ScopedInstall(SortOutStreamingAndMemory, 0x441440);
    RH_ScopedInstall(StopPlayerMovingFromDirection, 0x441290);
    RH_ScopedInstall(Update, 0x442AD0, { .reversed = false });
    RH_ScopedInstall(UpdateSkip, 0x442480, { .reversed = false });
}

// 0x4418E0
float CGameLogic::CalcDistanceToForbiddenTrainCrossing(CVector vecPoint, CVector vecMoveSpeed, bool someBool, CVector* pOutDistance) {
    return plugin::CallAndReturn<float, 0x4418E0, CVector, CVector, bool, CVector*>(vecPoint, vecMoveSpeed, someBool, pOutDistance);
}

// 0x441560
void CGameLogic::ClearSkip(bool a1) {
    if (a1 && SkipState == SKIP_STATE_4)
        return;

    if (SkipState == SKIP_STATE_2) {
        TheCamera.SetFadeColour(0, 0, 0);
        TheCamera.Fade(0.5f, eFadeFlag::FADE_OUT);
    }
    SkipState = SKIP_STATE_0;
    CPad::GetPad(0)->bCamera = false;
}

// 0x4428B0
void CGameLogic::DoWeaponStuffAtStartOf2PlayerGame(bool shareWeapons) {
    auto player1 = FindPlayerPed(PED_TYPE_PLAYER1);
    auto player2 = FindPlayerPed(PED_TYPE_PLAYER2);
    RestorePedsWeapons(player1);

    if (shareWeapons) {
        for (auto& weapon : player1->m_aWeapons) {
            if (weapon.m_nType == WEAPON_UNARMED)
                continue;

            player2->GiveWeapon(weapon, true);
        }
        player1->PickWeaponAllowedFor2Player();
        player1->m_pPlayerData->m_nChosenWeapon = player1->m_pPlayerData->m_nChosenWeapon;
    }
}

// 0x441B70
// 1 - Los Santos, 2 - San Fierro, 3 - Las Venturas
uint32 CGameLogic::FindCityClosestToPoint(CVector2D point) {
    constexpr CVector2D cityCoords[] = {
        { 1670.0f, -1137.0f}, // LS
        {-1810.0f,   884.0f}, // SF
        { 2161.0f,  2140.0f}, // Lv
    };
    std::pair<float, size_t> closest{FLT_MAX, 3};
    for (auto&& [i, d] : notsa::enumerate(cityCoords)) {
        if (const auto d = DistanceBetweenPoints2D(cityCoords[i], point); d < closest.first) {
            closest = {d, i};
        }
    }

    if (closest.second == 3) {
        NOTSA_UNREACHABLE();
    }

    return closest.second + 1;
}

// 0x441240
void CGameLogic::ForceDeathRestart() {
    CWorld::Players[CWorld::PlayerInFocus].m_nPlayerState = PLAYERSTATE_HAS_DIED;
    GameState = GAME_STATE_LOGO;
    TimeOfLastEvent = CTimer::GetTimeInMS() - 3001;
    TheCamera.SetFadeColour(0, 0, 0);
    TheCamera.Fade(4.0f, eFadeFlag::FADE_IN);
}

// 0x441210
void CGameLogic::InitAtStartOfGame() {
    ActivePlayers            = true;
    SkipState                = SKIP_STATE_0;
    NumAfterDeathStartPoints = 0;
    GameState                = GAME_STATE_INITIAL;
    TimeOfLastEvent          = 0;
    nPrintFocusHelpTimer     = 0;
    nPrintFocusHelpCounter   = 0;
    bScriptCoopGameGoingOn   = false;
}

// 2 players are playing
// 0x441390
bool CGameLogic::IsCoopGameGoingOn() {
    return FindPlayerPed(PED_TYPE_PLAYER1) && FindPlayerPed(PED_TYPE_PLAYER2);
}

// 0x441E10
bool CGameLogic::IsPlayerAllowedToGoInThisDirection(CPed* ped, float moveDirectionX, float moveDirectionY, float moveDirectionZ, float distanceLimit) {
    return plugin::CallAndReturn<bool, 0x441E10, CPed*, float, float, float, float>(ped, moveDirectionX, moveDirectionY, moveDirectionZ, distanceLimit);
}

// 0x442020
bool CGameLogic::IsPlayerUse2PlayerControls(CPed* ped) {
    if (!IsCoopGameGoingOn())
        return false;

    if (n2PlayerPedInFocus == PED_TYPE_PLAYER2)
        return true;

    return ped != CWorld::Players[n2PlayerPedInFocus].m_pPed;
}

// 0x4416E0
bool CGameLogic::IsPointWithinLineArea(const CVector* points, uint32 numPoints, float x, float y) {
    for (auto&& [i, point] : notsa::enumerate(std::span{points, numPoints})) {
        const auto nextPoint = (i != numPoints - 1) ? points[i + 1] : points[0];
        if (CCollision::Test2DLineAgainst2DLine(x, y, 1'000'000.0f, 0.0f, point.x, point.y, nextPoint.x - point.x, nextPoint.y - point.y))
            return true;
    }

    return false;
}

// 0x4416C0
bool CGameLogic::IsSkipWaitingForScriptToFadeIn() {
    if (CGameLogic::SkipState != SKIP_STATE_5) {
        return false;
    }
    CGameLogic::SkipState = SKIP_STATE_0;
    return true;
}

// 0x441C10
bool CGameLogic::LaRiotsActiveHere() {
    const auto coors = FindPlayerCoors();
    if (coors.z > 950.0f)
        return false;

    if (CCheat::IsActive(CHEAT_RIOT_MODE))
        return true;

    CRect rt1(1620.0f, -2178.0f, 2824.0f, -1067.0f),
          rt2(157.0f, -1950.0f, 1630.0f, -1192.0f);

    if (gbLARiots && (rt1.IsPointInside(coors) || rt2.IsPointInside(coors)))
        return true;

    return false;
}

// 0x5D33C0
void CGameLogic::Save() {
    plugin::Call<0x5D33C0>();

//    CGenericGameStorage::SaveDataToWorkBuffer(&CGameLogic::NumAfterDeathStartPoints, sizeof(int32));
//    CGenericGameStorage::SaveDataToWorkBuffer(&CGameLogic::bPenaltyForDeathApplies,  sizeof(bool));
//    CGenericGameStorage::SaveDataToWorkBuffer(&CGameLogic::bPenaltyForArrestApplies, sizeof(bool));
//    CGenericGameStorage::SaveDataToWorkBuffer(&CGameLogic::GameState,                sizeof(eGameState));
//    CGenericGameStorage::SaveDataToWorkBuffer(&CGameLogic::TimeOfLastEvent,          sizeof(uint32));
//    for (int32 i = 0; i < NumAfterDeathStartPoints; ++i) {
//        CGenericGameStorage::SaveDataToWorkBuffer(&CGameLogic::AfterDeathStartPoints[i],            sizeof(CVector));
//        CGenericGameStorage::SaveDataToWorkBuffer(&CGameLogic::AfterDeathStartPointOrientations[i], sizeof(float));
//    }
}

// 0x5D3440
void CGameLogic::Load() {
    plugin::Call<0x5D3440>();

//    CGenericGameStorage::LoadDataFromWorkBuffer(&CGameLogic::NumAfterDeathStartPoints, sizeof(int32));
//    CGenericGameStorage::LoadDataFromWorkBuffer(&CGameLogic::bPenaltyForDeathApplies,  sizeof(bool));
//    CGenericGameStorage::LoadDataFromWorkBuffer(&CGameLogic::bPenaltyForArrestApplies, sizeof(bool));
//    CGenericGameStorage::LoadDataFromWorkBuffer(&CGameLogic::GameState,                sizeof(eGameState));
//    CGenericGameStorage::LoadDataFromWorkBuffer(&CGameLogic::TimeOfLastEvent,          sizeof(uint32));
//    for (int32 i = 0; i < NumAfterDeathStartPoints; ++i) {
//        CGenericGameStorage::LoadDataFromWorkBuffer(&CGameLogic::AfterDeathStartPoints[i],            sizeof(CVector));
//        CGenericGameStorage::LoadDataFromWorkBuffer(&CGameLogic::AfterDeathStartPointOrientations[i], sizeof(float));
//    }
}

// 0x4414C0
void CGameLogic::PassTime(uint32 minutes) {
    auto weekDay = CClock::GetGameWeekDay();
    auto hours = CClock::GetGameClockHours();
    auto mins = minutes + CClock::GetGameClockMinutes();

    if (mins >= 60) {
        hours += mins / 60;
        mins %= 60;
    }

    if (hours >= 24) {
        auto days = hours / 24;
        hours %= 24;

        CStats::IncrementStat(STAT_DAYS_PASSED_IN_GAME, (float)days);
        weekDay += days;
        if (weekDay > 7) {
            weekDay = 1;
        }
    }

    CClock::SetGameClock(hours, mins, weekDay);
    CPickups::PassTime(minutes * 1000);
}

// 0x4413C0
void CGameLogic::Remove2ndPlayerIfPresent() {
    if (auto ped = FindPlayerPed(PED_TYPE_PLAYER2)) {
        CWorld::Remove(ped);
        delete ped;
        CWorld::Players[PED_TYPE_PLAYER2].m_pPed = nullptr;

        auto player1 = FindPlayerPed(PED_TYPE_PLAYER1);
        CClothes::RebuildPlayer(player1, false);
        player1->CantBeKnockedOffBike = false;
    }
    n2PlayerPedInFocus = 2;
}

// 0x442980
void CGameLogic::ResetStuffUponResurrection() {
    auto& player = CWorld::Players[CWorld::PlayerInFocus];
    auto playerPed = player.m_pPed;

    CMessages::ClearMessages(false);
    CCarCtrl::ClearInterestingVehicleList();
    CWorld::ClearExcitingStuffFromArea(player.GetPos(), 4000.0f, true);
    PassTime(12 * 60);
    RestorePlayerStuffDuringResurrection(playerPed, playerPed->GetPosition(), playerPed->m_fCurrentRotation * RadiansToDegrees(1.0f));
    SortOutStreamingAndMemory(playerPed->GetPosition(), playerPed->GetHeading());
    TheCamera.m_fCamShakeForce = 0.0;
    TheCamera.SetMotionBlur(0, 0, 0, 0, 0);
    CPad::GetPad(0)->StopShaking(0);
    CReferences::RemoveReferencesToPlayer();
    CCarCtrl::CountDownToCarsAtStart = 10;
    CPopulation::m_CountDownToPedsAtStart = 10;
    CPad::GetPad(CWorld::PlayerInFocus)->DisablePlayerControls = 0;

    playerPed->ClearWeapons();
    GameState = GAME_STATE_INITIAL;
    TimeOfLastEvent = 0;
}

// used in CGameLogic::DoWeaponStuffAtStartOf2PlayerGame
// 0x441D00
void CGameLogic::StorePedsWeapons(CPed* ped) {
    rng::copy(ped->m_aWeapons, s_SavedWeapons.begin());
}

// 0x441D30
void CGameLogic::RestorePedsWeapons(CPed* ped) {
    ped->ClearWeapons();
    for (auto& weapon : s_SavedWeapons) {
        const auto IsModelLoaded = [](int id) { return id == MODEL_INVALID || CStreaming::GetInfo(id).IsLoaded(); };

        if (rng::all_of(weapon.GetWeaponInfo().GetModels(), IsModelLoaded)) { // FIX_BUGS: They checked modelId1 twice
            ped->GiveWeapon(weapon.m_nType, weapon.m_nTotalAmmo, true);
        }
    }
}

// 0x442060
void CGameLogic::RestorePlayerStuffDuringResurrection(CPlayerPed* player, CVector posn, float playerStartHeading) {
    ClearSkip(false);

    if (player->m_fHealth <= 0.0f) {
        CStats::UpdateStatsOnRespawn();
    }
    auto playerData = player->m_pPlayerData;
    auto playerInfo = player->GetPlayerInfoForThisPlayerPed();

    player->physicalFlags.bDestroyed = false;
    player->m_fArmour = 0.0f;
    player->m_fHealth = static_cast<float>(playerInfo->m_nMaxHealth);
    player->m_bIsVisible = true;
    player->m_nDeathTime = 0;
    player->bDoBloodyFootprints = false;
    playerData->m_nDrunkenness = 0;
    playerData->m_nFadeDrunkenness = 0;
    CMBlur::ClearDrunkBlur();
    playerData->m_nDrugLevel = 0;
    player->ClearAdrenaline();
    player->ResetSprintEnergy();
    if (auto& fire = player->m_pFire) {
        fire->createdByScript = false;
        fire->Extinguish();
        fire = nullptr;
    }
    player->m_pedAudio.TurnOffJetPack();
    player->bInVehicle = false;
    if (auto vehicle = player->m_pVehicle) {
        vehicle->CleanUpOldReference((CEntity**)&vehicle);
    }
    player->m_pVehicle = nullptr;
    player->GetWanted()->Reset();
    player->RestartNonPartialAnims();
    playerInfo->MakePlayerSafe(false, 10'000.0f);
    player->m_bRemoveFromWorld = false;
    player->ClearWeaponTarget();
    player->SetInitialState(false);
    player->GetAcquaintance() = CPedType::GetPedTypeAcquaintances(player->m_nPedType);
    CCarCtrl::ClearInterestingVehicleList();

    player->Teleport(posn + CVector{0.0f, 0.0f, 1.0f}, false);
    player->m_fCurrentRotation = player->m_fAimingRotation = DegreesToRadians(playerStartHeading);
    player->SetHeading(player->m_fCurrentRotation);

    CTheScripts::ClearSpaceForMissionEntity(posn, player);
    CWorld::ClearExcitingStuffFromArea(posn, 4000.0, 1);
    player->RestoreHeadingRate();
    player->m_nAreaCode = AREA_CODE_NORMAL_WORLD;
    player->m_pEnex = 0;
    CEntryExitManager::ms_entryExitStackPosn = 0;
    CGame::currArea = AREA_CODE_NORMAL_WORLD;
    CPopulation::bInPoliceStation = 0;
    CStreaming::RemoveBuildingsNotInArea(AREA_CODE_NORMAL_WORLD);
    TheCamera.SetCameraDirectlyBehindForFollowPed_CamOnAString();
    TheCamera.RestoreWithJumpCut();
    CReferences::RemoveReferencesToPlayer();
    CGarages::PlayerArrestedOrDied();
    CStats::SetStatValue(STAT_KILLS_SINCE_LAST_CHECKPOINT, 0.0);
    CShopping::RemoveLoadedShop();
    CWorld::Remove(player);
    CWorld::Add(player);
    CHud::ResetWastedText();
    CStreaming::StreamZoneModels(posn);
    CPostEffects::m_smokeyEnable = false;
    CTimeCycle::StopExtraColour(0);
    CPostEffects::ScriptResetForEffects();

    if (auto clothesDesc = playerData->m_pPedClothesDesc; clothesDesc->m_anModelKeys[9]) {
        clothesDesc->SetTextureAndModel(nullptr, nullptr, CLOTHES_TEXTURE_SPECIAL);
        CClothes::RebuildPlayer(player, false);
    } else {
        CClothes::RebuildPlayerIfNeeded(player);
    }
    CAudioZones::Update(true, posn);
    AudioEngine.StopPoliceScanner(true);
    CWaterLevel::FindNearestWaterAndItsFlow();
    TheCamera.m_fDistanceToWater = 99999.898f;
}

// @brief Set wanted level to 4 if player is in a forbidden territory.
// @param immediately   Do position check without waiting for the frame counter.
// @addr 0x441770
void CGameLogic::SetPlayerWantedLevelForForbiddenTerritories(bool immediately) {
    const auto ped = FindPlayerPed();
    const auto coords = ped->GetPosition();

    if ((!immediately && (CTimer::GetFrameCounter() % 32) != 18) || coords.z > 950.0f)
        return;

    if (ped->m_pIntelligence->GetTaskSwim() || ped->GetWantedLevel() >= 4)
        return;

    const auto SetWantedIfInArea = [&](auto* vertices, size_t size) {
        if (IsPointWithinLineArea(vertices, size, coords.x, coords.y)) {
            ped->SetWantedLevel(4);
            if (immediately) {
                ped->GetWanted()->m_nLastTimeWantedLevelChanged = 0;
            }
        }
    };

    // LV
    if (CStats::GetStatValue(STAT_CITY_UNLOCKED) <= 1.0f) {
        SetWantedIfInArea(town1ShapeVertices, std::size(town1ShapeVertices));
    }

    // SF
    if (CStats::GetStatValue(STAT_CITY_UNLOCKED) <= 0.0f) {
        SetWantedIfInArea(town2ShapeVertices, std::size(town2ShapeVertices));
    }
}

// 0x4423C0
void CGameLogic::SetUpSkip(CVector coors, float angle, bool afterMission, CEntity* vehicle, bool finishedByScript) {
    if (SkipState == SKIP_STATE_2) {
        TheCamera.SetFadeColour(0, 0, 0);
        TheCamera.Fade(0.5f, eFadeFlag::FADE_OUT);
    }
    SkipState = SKIP_STATE_0;
    CPad::GetPad(0)->bCamera = false;
    AfterDeathStartPoints[0] = coors;

    SkipTimer = CTimer::GetTimeInMS();
    if (vehicle) {
        vehicle->RegisterReference(SkipVehicle);
    }
    SkipToBeFinishedByScript = finishedByScript;
}

// 0x4415C0
bool CGameLogic::SkipCanBeActivated() {
    if (!CGame::CanSeeOutSideFromCurrArea() || TheCamera.m_bFading || (SkipState != 1 && SkipState != 4))
        return false;

    if (auto vehicle = FindPlayerVehicle()) {
        switch (vehicle->m_nVehicleSubType) {
        case VEHICLE_TYPE_BIKE:
        case VEHICLE_TYPE_AUTOMOBILE:
        case VEHICLE_TYPE_MTRUCK:
        case VEHICLE_TYPE_QUAD:
        case VEHICLE_TYPE_BMX:
            if (!SkipVehicle || SkipVehicle == vehicle) {
                return true;
            }
            break;
        }
    }

    return SkipState == 4 && FindPlayerPed()->GetIntelligence()->GetTaskSwim();
}

// 0x441440
void CGameLogic::SortOutStreamingAndMemory(const CVector& translation, float angle) {
    CTimer::Stop();
    RwCameraSetFarClipPlane(TheCamera.m_pRwCamera, CTimeCycle::FindFarClipForCoors(translation));
    CStreaming::FlushRequestList();
    CStreaming::DeleteRwObjectsAfterDeath(translation);
    CStreaming::RemoveUnusedModelsInLoadedList();
    CGame::DrasticTidyUpMemory(true);
    CStreaming::LoadSceneCollision(translation);
    CRenderer::RequestObjectsInDirection(translation, angle, STREAMING_LOADING_SCENE);
    CStreaming::LoadScene(translation);
    CTimer::Update();
}

// 0x441290
void CGameLogic::StopPlayerMovingFromDirection(int32 playerId, CVector direction) {
    if (auto obj = [ped = FindPlayerPed(playerId)]() -> CPhysical* {
        if (ped->IsInVehicle()) {
            return ped->GetVehicleIfInOne();
        } else if (ped->bIsStanding || ped->m_pIntelligence->GetTaskJetPack()) {
            return ped;
        }

        return nullptr;
    }()) {
        direction.z = std::max(0.0f, direction.z);

        if (const auto mul = direction * obj->m_vecMoveSpeed; mul.ComponentwiseSum() < 0.0f) {
            obj->m_vecMoveSpeed -= mul * direction;
        }
    }
}

// 0x442AD0
void CGameLogic::Update() {
    plugin::Call<0x442AD0>();
}

// 0x442480
void CGameLogic::UpdateSkip() {
    plugin::Call<0x442480>();
}
