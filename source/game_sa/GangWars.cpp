/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

#include "GangWars.h"
#include "GangWarsSaveStructure.h"
#include "ModelIndices.h"
#include "Tasks/TaskTypes/TaskComplexWander.h"
#include "Tasks/TaskTypes/TaskComplexKillPedOnFoot.h"
//#include "Tasks/TaskTypes/TaskComplexCarDriveWander.h"
#include "Tasks/TaskTypes/TaskSimpleCarDrive.h"
//#include "Tasks/TaskTypes/TaskComplexWanderGang.h"
#include <extensions/enumerate.hpp>

void CGangWars::InjectHooks() {
    RH_ScopedClass(CGangWars);
    RH_ScopedCategoryGlobal();

    // RH_ScopedInstall(Load, 0x5D3EB0);
    // RH_ScopedInstall(Save, 0x5D5530);
    RH_ScopedInstall(InitAtStartOfGame, 0x443920);
    RH_ScopedInstall(AddKillToProvocation, 0x443950);
    RH_ScopedInstall(AttackWaveOvercome, 0x445B30);
    RH_ScopedInstall(CalculateTimeTillNextAttack, 0x443DB0);
    RH_ScopedInstall(CanPlayerStartAGangWarHere, 0x443F80);
    RH_ScopedInstall(CheerVictory, 0x444040);
    RH_ScopedInstall(ClearSpecificZonesToTriggerGangWar, 0x443FF0);
    RH_ScopedInstall(ClearTheStreets, 0x4444B0);
    // RH_ScopedInstall(CreateAttackWave, 0x444810);
    RH_ScopedInstall(CreateDefendingGroup, 0x4453D0);
    RH_ScopedInstall(DoStuffWhenPlayerVictorious, 0x446400);
    RH_ScopedInstall(DontCreateCivilians, 0x4439C0);
    RH_ScopedInstall(EndGangWar, 0x4464C0);
    RH_ScopedInstall(GangWarFightingGoingOn, 0x443AC0);
    RH_ScopedInstall(GangWarGoingOn, 0x443AA0);
    RH_ScopedInstall(MakeEnemyGainInfluenceInZone, 0x445FD0);
    RH_ScopedInstall(MakePlayerGainInfluenceInZone, 0x445E80);
    RH_ScopedInstall(PedStreamedInForThisGang, 0x4439D0);
    // RH_ScopedInstall(PickStreamedInPedForThisGang, 0x443A20);
    RH_ScopedInstall(PickZoneToAttack, 0x443B00);
    RH_ScopedInstall(ReleaseCarsInAttackWave, 0x445E20);
    RH_ScopedInstall(ReleasePedsInAttackWave, 0x445C30);
    RH_ScopedInstall(SetGangWarsActive, 0x446570);
    RH_ScopedInstall(SetSpecificZoneToTriggerGangWar, 0x444010);
    RH_ScopedInstall(StartDefensiveGangWar, 0x444300);
    // RH_ScopedInstall(StartOffensiveGangWar, 0x446050);
    RH_ScopedInstall(StrengthenPlayerInfluenceInZone, 0x445F50);
    RH_ScopedInstall(SwitchGangWarsActive, 0x4465F0);
    // RH_ScopedInstall(TellGangMembersTo, 0x444530);
    RH_ScopedInstall(TellStreamingWhichGangsAreNeeded, 0x443D50);
    // RH_ScopedInstall(Update, 0x446610);
    RH_ScopedInstall(UpdateTerritoryUnderControlPercentage, 0x443DE0);
}

// 0x5D3EB0
void CGangWars::Load() {
    /*plugin::Call<0x5D3EB0>();

    size_t size;
    CGangWarsSaveStructure gwss;
    CGenericGameStorage::LoadDataFromWorkBuffer(&size, sizeof(size_t));
    CGenericGameStorage::LoadDataFromWorkBuffer(&gwss, sizeof(CGangWarsSaveStructure));
    gwss.Extract();*/
}

// 0x5D5530
void CGangWars::Save() {
    /*plugin::Call<0x5D5530>();

    CGangWarsSaveStructure gwss;
    gwss.Construct();
    CGenericGameStorage::SaveDataToWorkBuffer((void*)sizeof(CGangWarsSaveStructure), sizeof(size_t));
    CGenericGameStorage::SaveDataToWorkBuffer(&gwss, sizeof(CGangWarsSaveStructure));*/
}

// 0x443920
void CGangWars::InitAtStartOfGame() {
    State               = NOT_IN_WAR;
    State2              = NO_ATTACK;
    NumSpecificZones    = 0;
    Provocation         = 0.0f;
    bGangWarsActive     = false;
    bIsPlayerOnAMission = false;
}

// 0x443950
void CGangWars::AddKillToProvocation(ePedType pedType) {
    if (!bCanTriggerGangWarWhenOnAMission && CTheScripts::IsPlayerOnAMission())
        return;

    if (pedType != PED_TYPE_GANG1 && pedType != PED_TYPE_GANG3)
        return;

    if (NumSpecificZones == 0)
        Provocation += 1.0f;

    for (auto i = 0; i < NumSpecificZones; i++) {
        auto zoneInfo = CTheZones::GetZoneInfo(CTheZones::GetNavigationZone(aSpecificZones[i]));

        if (zoneInfo->GangDensity[pedType - PED_TYPE_GANG1] != 0)
            Provocation += 1.0f;
    }
}

// 0x445B30, untested
bool CGangWars::AttackWaveOvercome() {
    auto pedsNearPlayer = 0u, pedsLiving = 0u;

    for (auto i = 0; i < GetPedPool()->GetSize(); i++) {
        auto ped = GetPedPool()->GetAt(i);

        if (ped && ped->bPartOfAttackWave) {
            if (ped->IsStateDying()) {
                ped->bPartOfAttackWave = false;
                ped->SetCharCreatedBy(PED_GAME);

                continue;
            }

            pedsLiving++;
            if (DistanceBetweenPoints2D(ped->GetPosition2D(), FindPlayerCoors()) < 45.0f)
                pedsNearPlayer++;
        }
    }

    return pedsLiving <= 1 && pedsNearPlayer == 0;
}

// 0x443DB0
float CGangWars::CalculateTimeTillNextAttack() {
    return CGeneral::GetRandomNumberInRange(648'000.0f, 1'620'000.0f);
}

// 0x443F80
bool CGangWars::CanPlayerStartAGangWarHere(CZoneInfo* zoneInfo) {
    if (bTrainingMission)
        return zoneInfo == &CTheZones::ZoneInfoArray[ZoneInfoForTraining];

    if (NumSpecificZones == 0)
        return true;

    // inline?
    for (auto& zone : CTheZones::NavigationZoneArray) {
        if (zoneInfo == CTheZones::GetZoneInfo(&zone))
            return true;
    }

    return false;
}

// 0x444040
void CGangWars::CheerVictory() {
    auto& playerGroup = FindPlayerPed()->GetGroup();

    CPed* nearestMember = nullptr;
    playerGroup.FindDistanceToNearestMember(&nearestMember);

    if (!nearestMember)
        return;

    constexpr const char* zoneNames[] = {
        "CHC", "LFL", "EBE", "ELF", "JEF",
        "GLN", "IWD", "GAN", "LMEX", "LIND",
        "PLS", "SUN"
    };

    for (auto i = 0u; i < std::size(zoneNames); i++) {
        if (!_stricmp(pZoneToFightOver->m_szTextKey, zoneNames[i])) {
            nearestMember->Say(208 + i);
            break;
        }
    }
}

// 0x443FF0
void CGangWars::ClearSpecificZonesToTriggerGangWar() {
    NumSpecificZones = 0;
    CTheZones::FillZonesWithGangColours(false);
}

// 0x4444B0
void CGangWars::ClearTheStreets() {
    for (auto i = 0; i < GetPedPool()->GetSize(); i++) {
        auto ped = GetPedPool()->GetAt(i);

        if (ped && !ped->IsPlayer()) {
            auto type = ped->m_nPedType;

            if (type == PED_TYPE_CIVMALE || type == PED_TYPE_CIVFEMALE) {
                if (auto task = ped->GetTaskManager().Find<CTaskComplexWander>())
                    task->m_nMoveState = PEDMOVE_SPRINT;
            }
        }
    }
}

// 0x444810
bool CGangWars::CreateAttackWave(int32 warFerocity, int32 waveID) {
    return plugin::CallAndReturn<bool, 0x444810, int32, int32>(warFerocity, waveID);
}

// 0x4453D0
bool CGangWars::CreateDefendingGroup(int32 unused) {
    if (!PedStreamedInForThisGang(Gang1)) {
        auto group = CPopulation::GetPedGroupId((ePopcycleGroup)Gang1, 0);
        CStreaming::RequestModel(CPopulation::GetPedGroupModelId(group, 0), STREAMING_KEEP_IN_MEMORY);

        return false;
    }

    if (!ThePaths.AreNodesLoadedForArea(PointOfAttack.x, PointOfAttack.x, PointOfAttack.y, PointOfAttack.y))
        return false;

    auto node = ThePaths.FindNodeClosestToCoors(PointOfAttack, 0, 400.0f, 0, 0, 0, 0, 1);
    if (!node.IsAreaValid())
        return false;

    auto nodePos = ThePaths.GetPathNode(node)->GetNodeCoors();
    auto playerPos = FindPlayerCoors();
    if (DistanceBetweenPoints2D(nodePos, playerPos) <= 40.0f)
        return false;

    auto pedCount = static_cast<uint32>(10.0f * (0.4f * Difficulty + 0.6f));

    int32 outPedId;
    for (auto i = 0u; i < pedCount; i++) {
        if (!PickStreamedInPedForThisGang(Gang1, &outPedId))
            continue;

        auto angle = i * TWO_PI / pedCount;

        auto pedPos = CVector{
            nodePos.x + sin(angle) * ((rand() / 32767.0f) * 3.0f + 2.0f),
            nodePos.y + cos(angle) * ((rand() / 32767.0f) * 3.0f + 2.0f),
            nodePos.z + 2.0f
        };
        pedPos.z = CWorld::FindGroundZFor3DCoord(pedPos, nullptr, nullptr);

        auto ped = new CCivilianPed(static_cast<ePedType>(Gang1 + 7), outPedId);
        ped->SetPosn(pedPos);
        ped->m_fAimingRotation = angle;
        ped->m_fCurrentRotation = angle;
        ped->SetHeading(angle);
        ped->SetCharCreatedBy(PED_MISSION);
        CWorld::Add(ped);

        auto task = new CTaskComplexKillPedOnFoot(FindPlayerPed(), -1, 0, 0, 0, 2);
        CEventScriptCommand esc(3, task, false);
        ped->GetEventGroup().Add(&esc);

        ped->SetWeaponAccuracy(static_cast<uint8_t>(90.0f - Difficulty * 60.0f));
        ped->GetAcquaintance().SetAsAcquaintance(ACQUAINTANCE_HATE, CPedType::GetPedFlag(PED_TYPE_PLAYER1));

        eWeaponType weaponToGive{};
        switch (i % 4) {
        case 0:
            weaponToGive = WEAPON_PISTOL;
            break;
        case 1:
            weaponToGive = WEAPON_MICRO_UZI;
            break;
        case 2:
            weaponToGive = WEAPON_SHOTGUN;
            break;
        case 3:
            weaponToGive = WEAPON_MP5;
            break;
        }

        ped->GiveDelayedWeapon(weaponToGive, 5000);
        ped->SetCurrentWeapon(weaponToGive);
        ped->bPartOfAttackWave = true;
        ped->bClearRadarBlipOnDeath = true;

        auto color = GetGangColor(Gang1);
        auto blip = CRadar::SetEntityBlip(BLIP_CHAR, CPools::GetPedRef(ped), color, BLIP_DISPLAY_BLIPONLY);
        CRadar::ChangeBlipScale(blip, 2);
        CRadar::ChangeBlipColour(blip, color);
    }

    for (auto i = 0u; i < 3u; i++) {
        auto carNode = ThePaths.FindNthNodeClosestToCoors(PointOfAttack, 0, 100.0f, false, false, i, false, true, nullptr);
        auto carNodePos = ThePaths.GetPathNode(carNode)->GetNodeCoors();

        if (DistanceBetweenPoints2D(carNodePos, playerPos) <= 25.0f)
            continue;

        auto gangCarModel = CPopulation::PickGangCar(Gang1);
        if (gangCarModel >= 0 && CStreaming::GetInfo(gangCarModel).IsLoaded()) {
            auto fwd = carNodePos - nodePos;
            fwd.z = 0.0f;
            fwd.Normalise();

            auto car = CCarCtrl::CreateCarForScript(gangCarModel, carNodePos, false);
            car->m_matrix->GetForward() = fwd;
            car->m_matrix->GetRight() = CVector{fwd.y, -fwd.x, 0.0f};

            car->AsAutomobile()->PlaceOnRoadProperly();
            car->vehicleFlags.bIsLocked = false;
            car->SetVehicleCreatedBy(MISSION_VEHICLE);
            car->vehicleFlags.bPartOfAttackWave = true;
        }
    }

    auto pickupCoors = CVector{
        (rand() / 32767.0f) * 4.0f + nodePos.x - 2.0f,
        (rand() / 32767.0f) * 4.0f + nodePos.y - 2.0f,
        nodePos.z + 1.0f
    };
    pickupCoors.z = CWorld::FindGroundZFor3DCoord(pickupCoors, nullptr, nullptr) + 0.75f;

    ModelIndex pickupModel = ModelIndices::MI_PICKUP_BODYARMOUR;
    if (CGeneral::GetRandomNumberInRange(0, 2) == 1) {
        pickupModel = ModelIndices::MI_PICKUP_HEALTH;
    }

    CPickups::GenerateNewOne(pickupCoors, pickupModel, 5, 0, 0, false, nullptr);
    return true;
}

// 0x446400
void CGangWars::DoStuffWhenPlayerVictorious() {
    ReleasePedsInAttackWave(true, false);
    ReleaseCarsInAttackWave();
    CheerVictory();
    State = NOT_IN_WAR;
    CMessages::AddMessage(TheText.Get("GW_YRS"), 4500, 1, true);
    CMessages::AddToPreviousBriefArray(TheText.Get("GW_YRS"), -1, -1, -1, -1, -1, -1, nullptr);
    Provocation = 0.0f;
    TellGangMembersTo(true);
    CStats::IncrementStat(STAT_RESPECT, 45.0f);
    CTheZones::FillZonesWithGangColours(false);

    TimeTillNextAttack = std::min(TimeTillNextAttack - 240'000.0f, 30'000.0f);
}

// inlined
// 0x443AE0
bool CGangWars::DoesPlayerControlThisZone(CZoneInfo* zoneInfo) {
    auto enemyDensity = zoneInfo->GangDensity[GANG_BALLAS] + zoneInfo->GangDensity[GANG_VAGOS];

    return zoneInfo->GangDensity[GANG_GROVE] > enemyDensity;
}

// 0x4439C0
bool CGangWars::DontCreateCivilians() {
    return State != NOT_IN_WAR;
}

// 0x4464C0
void CGangWars::EndGangWar(bool end) {
    State = NOT_IN_WAR;

    if (State2 == WAR_NOTIFIED) {
        State2 = NO_ATTACK;
        TimeTillNextAttack = CalculateTimeTillNextAttack();

        uint32 releasedPeds = ReleasePedsInAttackWave(true, false);
        MakeEnemyGainInfluenceInZone(Gang1, 3 * releasedPeds);
    }

    Provocation = 0.0f;
    CTheZones::FillZonesWithGangColours(false);
    ReleasePedsInAttackWave(true, end);
    ReleaseCarsInAttackWave();
}

// 0x443AC0
bool CGangWars::GangWarFightingGoingOn() {
    return State != NOT_IN_WAR || State2 == PLAYER_CAME_TO_WAR;
}

// 0x443AA0
bool CGangWars::GangWarGoingOn() {
    return State != NOT_IN_WAR || State2 == WAR_NOTIFIED;
}

// 0x445FD0
void CGangWars::MakeEnemyGainInfluenceInZone(int32 gangId, int32 gangDensityIncreaser) {
    if (!pZoneInfoToFightOver)
        return;

    auto totalGangDensity = pZoneInfoToFightOver->GangDensity[GANG_BALLAS]
        + pZoneInfoToFightOver->GangDensity[GANG_GROVE]
        + pZoneInfoToFightOver->GangDensity[GANG_VAGOS];

    if (!totalGangDensity)
        return;

    pZoneInfoToFightOver->GangDensity[gangId] += gangDensityIncreaser;

    if (!DoesPlayerControlThisZone(pZoneInfoToFightOver))
        CStats::IncrementStat(STAT_TERRITORIES_LOST, 1.0f);
}

// 0x445E80
bool CGangWars::MakePlayerGainInfluenceInZone(float removeMult) {
    bool doesControlInitial = DoesPlayerControlThisZone(pZoneInfoToFightOver);
    uint8 totalEnemyDensity = 0u;

    for (auto i = 0u; i < 10u; i++) { // for all gangs except grove
        if (i != GANG_GROVE) {
            auto& density = pZoneInfoToFightOver->GangDensity[i];
            auto densityInitial = density;

            density = static_cast<uint8>((1.0f - removeMult) * density);

            if (density < 4u) {
                density = 0u;
            }

            pZoneInfoToFightOver->GangDensity[GANG_GROVE] += densityInitial - density;

            totalEnemyDensity += density;
        }
    }

    if (!doesControlInitial && DoesPlayerControlThisZone(pZoneInfoToFightOver)) {
        CStats::IncrementStat(STAT_TERRITORIES_TAKEN_OVER, 1.0f);
    }

    return totalEnemyDensity == 0u;
}

// 0x4439D0
bool CGangWars::PedStreamedInForThisGang(int32 gangId) {
    auto groupId = CPopulation::GetPedGroupId((ePopcycleGroup)gangId, 0);
    auto numPeds = CPopulation::GetNumPedsInGroup(groupId);

    if (numPeds <= 0)
        return false;

    for (auto i = 0; i < numPeds; i++) {
        if (!CStreaming::GetInfo(*CPopulation::m_PedGroups[i]).IsLoaded())
            return true;
    }

    return false;
}

// 0x443A20
bool CGangWars::PickStreamedInPedForThisGang(int32 gangId, int32* outPedId) {
    return plugin::CallAndReturn<bool, 0x443A20, int32, int32*>(gangId, outPedId);
}

// 0x443B00
bool CGangWars::PickZoneToAttack() {
    CCarCtrl::InitSequence(CTheZones::TotalNumberOfNavigationZones);
    CZone* enemyGangZone = nullptr;

    // choose a territory controlled that is by enemy gangs
    for (auto i = 0; i < CTheZones::TotalNumberOfNavigationZones; i++) {
        auto zone = CTheZones::GetNavigationZone(CCarCtrl::FindSequenceElement(i));
        auto zoneInfo = CTheZones::GetZoneInfo(zone);

        if (!zoneInfo)
            continue;

        if (zoneInfo->GangDensity[GANG_BALLAS] + zoneInfo->GangDensity[GANG_VAGOS] >= 20) {
            enemyGangZone = zone;
            break;
        }
    }

    if (!enemyGangZone) [[unlikely]]
        return false;

    // find a close territory that is controlled by the gsf
    for (auto i = 0; i < CTheZones::TotalNumberOfNavigationZones; i++) {
        auto zone = CTheZones::GetNavigationZone(CCarCtrl::FindSequenceElement(i));
        auto zoneInfo = CTheZones::GetZoneInfo(zone);

        if (!zoneInfo)
            continue;

        if ((float)zone->m_fX1 <= 2500.0f && (float)zone->m_fX2 >= 2500.0f && (float)zone->m_fY1 <= -1666.0f && (float)zone->m_fY2 >= -1666.0f)
            continue;

        if (zoneInfo->GangDensity[GANG_GROVE] <= 15)
            continue;

        if (CTheZones::Calc2DDistanceBetween2Zones(enemyGangZone, zone) < 10.0f) {
            pZoneToFightOver = zone;
            pZoneInfoToFightOver = zoneInfo;
            PointOfAttack = CVector{(float)(zone->m_fX1 + zone->m_fX2) / 2.0f, (float)(zone->m_fY1 + zone->m_fY2) / 2.0f, 10.0f};

            auto enemyGangZoneInfo = CTheZones::GetZoneInfo(enemyGangZone);
            Gang1 = (enemyGangZoneInfo->GangDensity[GANG_BALLAS] > enemyGangZoneInfo->GangDensity[GANG_VAGOS]) ? GANG_BALLAS : GANG_VAGOS;

            if (DistanceBetweenPoints2D(FindPlayerCoors(), PointOfAttack) > 60.0f)
                return true;
        }
    }

    return false;
}

// 0x445E20
void CGangWars::ReleaseCarsInAttackWave() {
    for (auto i = 0; i < GetVehiclePool()->GetSize(); i++) {
        auto vehicle = GetVehiclePool()->GetAt(i);

        if (vehicle && vehicle->vehicleFlags.bPartOfAttackWave) {
            vehicle->vehicleFlags.bPartOfAttackWave = false;
            vehicle->SetVehicleCreatedBy(1);
        }
    }
}

// Returns num of released peds
// 0x445C30
uint32 CGangWars::ReleasePedsInAttackWave(bool isEndOfWar, bool restoreGangPedsAcquaintance) {
    auto numReleasedPeds = 0u;

    for (auto i = 0; i < GetPedPool()->GetSize(); i++) {
        CPed* ped = GetPedPool()->GetAt(i);

        if (!ped)
            continue;

        if (ped->bPartOfAttackWave) {
            ped->bPartOfAttackWave = false;
            ped->SetCharCreatedBy(PED_GAME);
            numReleasedPeds++;
            CRadar::ClearBlipForEntity(BLIP_CHAR, i);
            ped->bClearRadarBlipOnDeath = false;

            if (restoreGangPedsAcquaintance) {
                auto taskWander = CTaskComplexWander::GetWanderTaskByPedType(ped);
                CEventScriptCommand esc(3, taskWander, false);
                ped->GetEventGroup().Add(&esc);
                ped->m_acquaintance = CPedType::GetPedTypeAcquaintances(ped->m_nPedType);
            }
        }

        if (isEndOfWar && ped->bClearRadarBlipOnDeath) {
            CRadar::ClearBlipForEntity(BLIP_CHAR, i);
            ped->bClearRadarBlipOnDeath = false;
        }
    }

    return numReleasedPeds;
}

// 0x446570
void CGangWars::SetGangWarsActive(bool active) {
    if (active != bGangWarsActive) {
        CTheZones::FillZonesWithGangColours(!active);
        TimeTillNextAttack = CalculateTimeTillNextAttack();

        if (!active)
            EndGangWar(false);
    }
    bGangWarsActive = active;
}

// 0x444010
void CGangWars::SetSpecificZoneToTriggerGangWar(int32 zoneId) {
    aSpecificZones[NumSpecificZones] = zoneId;
    NumSpecificZones++;

    CTheZones::FillZonesWithGangColours(false);
}

// 0x444300, untested
void CGangWars::StartDefensiveGangWar() {
    if (PickZoneToAttack()) {
        Difficulty = TerritoryUnderControlPercentage;
        CHud::SetHelpMessage(TheText.Get("GW_ATK"), true, false, true);
        State2 = WAR_NOTIFIED;
        FightTimer = static_cast<int32>(DistanceBetweenPoints2D(FindPlayerCoors(), PointOfAttack) * 200.0f + 240000.0f);
        RadarBlip = CRadar::SetCoordBlip(BLIP_COORD, PointOfAttack, GetGangColor(Gang1), BLIP_DISPLAY_BLIPONLY, nullptr);
        
        switch (Gang1) {
        case GANG_BALLAS:
            CRadar::SetBlipSprite(RadarBlip, RADAR_SPRITE_GANGP);
            break;
        case GANG_VAGOS:
        case GANG_DANANGBOYS:
            CRadar::SetBlipSprite(RadarBlip, RADAR_SPRITE_GANGY);
            break;
        case GANG_RIFA:
            CRadar::SetBlipSprite(RadarBlip, RADAR_SPRITE_GANGB);
            break;
        default:
            CRadar::SetBlipSprite(RadarBlip, RADAR_SPRITE_ENEMYATTACK);
            break;
        }

        bPlayerIsCloseby = false;
        pZoneInfoToFightOver->Flags1 = CGangWars::pZoneInfoToFightOver->Flags1 & 0x9F | 0x40;
        pZoneInfoToFightOver->ZoneColor = CRGBA{255, 0, 0, 160};
    } else {
        TimeTillNextAttack = (rand() / 32767.0f) * 0.9f * 1080000.0f + 648000.0f;
    }
}

// 0x446050
void CGangWars::StartOffensiveGangWar() {
    plugin::Call<0x446050>();
}

// 0x445F50, untested
void CGangWars::StrengthenPlayerInfluenceInZone(int32 groveDensityIncreaser) {
    auto& groveDensity = pZoneInfoToFightOver->GangDensity[GANG_GROVE];
    auto enemyDensity = pZoneInfoToFightOver->GangDensity[GANG_BALLAS] + pZoneInfoToFightOver->GangDensity[GANG_VAGOS];

    bool controlledBefore = groveDensity != 0 && groveDensity > enemyDensity;

    if (groveDensity < 55u) {
        groveDensity = std::min(groveDensity + groveDensityIncreaser, 55);
    }

    if (!controlledBefore && groveDensity != 0 && groveDensity > enemyDensity) {
        CStats::IncrementStat(STAT_TERRITORIES_TAKEN_OVER, 1.0f);
    }
}

// 0x4465F0
// unused
void CGangWars::SwitchGangWarsActive() {
    SetGangWarsActive(!bGangWarsActive);
}

// 0x444530
// TODO: CTaskComplexCarDriveWander, CTaskComplexCarDriveWander to be stubbed
void CGangWars::TellGangMembersTo(bool isGangWarEnding) {
    plugin::Call<0x444530, bool>(isGangWarEnding);

    for (auto i = 0; i < GetPedPool()->GetSize(); i++) {
        auto ped = GetPedPool()->GetAt(i);

        if (ped && !ped->IsPlayer()) {
            if (!ped->IsGangster() || ped->m_nPedType == PED_TYPE_GANG2)
                continue;

            if (!isGangWarEnding) {
                auto player = FindPlayerPed();
                auto task = new CTaskComplexKillPedOnFoot(player, -1, 0, 0, 0, 2);
                CEventScriptCommand esc(3, task, false);
                ped->GetEventGroup().Add(&esc);

                continue;
            }

            if (ped->IsInVehicle()) {
                CTask* task;
                if (!ped->IsInVehicleAsPassenger()) {
                    /*
                    task = new CTaskComplexCarDriveWander(ped->GetVehicleIfInOne(), 0, 10.0f);
                    */
                } else {
                    task = new CTaskSimpleCarDrive(ped->GetVehicleIfInOne());
                }

                CEventScriptCommand esc(3, task, false);
                ped->GetEventGroup().Add(&esc);
            }

            /*
            task = new CTaskComplexCarDriveWander(4, CGeneral::GetRandomNumberInRange(0, 8), 5000, 1, 0.5f);
            CEventScriptCommand esc(3, task, false);
            ped->GetEventGroup().Add(&esc);
            */
        }
    }
}

// fix_bugs: originally has int32 type, but changed to unsigned due possible UB 
// 0x443D50
void CGangWars::TellStreamingWhichGangsAreNeeded(uint32* gangsBitFlags) {
    if (State2 == NO_ATTACK)
        return;

    auto coors = FindPlayerCoors();
    CVector2D delta = { coors.x - PointOfAttack.x, coors.y - PointOfAttack.y };

    if (delta.Magnitude() < 150.0f)
        *gangsBitFlags |= 1 << Gang1;
}

// 0x446610
void CGangWars::Update() {
    plugin::Call<0x446610>();
}

// 0x443DE0
void CGangWars::UpdateTerritoryUnderControlPercentage() {
    auto ballasZones = 0u, groveZones = 0u, vagosZones = 0u;
    if (CTheZones::TotalNumberOfNavigationZones) {
        for (auto& zone : CTheZones::NavigationZoneArray) {
            auto zoneInfo = CTheZones::GetZoneInfo(&zone);
            if (!zoneInfo)
                continue;

            auto ballasDensity = zoneInfo->GangDensity[GANG_BALLAS],
                 groveDensity = zoneInfo->GangDensity[GANG_GROVE],
                 vagosDensity = zoneInfo->GangDensity[GANG_VAGOS];

            // there should be one liner solution for this, no?
            if (groveDensity > ballasDensity + vagosDensity) {
                groveZones++;
            } else if (ballasDensity > vagosDensity) {
                ballasZones++;
            } else if (vagosDensity > ballasDensity) {
                vagosZones++;
            }
        }
    }

    CStats::SetStatValue(STAT_TERRITORIES_HELD, static_cast<float>(groveZones));
    CStats::SetNewRecordStat(STAT_HIGHEST_NUMBER_OF_TERRITORIES_HELD, static_cast<float>(groveZones));

    auto allGangZones = groveZones + ballasZones + vagosZones;
    if (allGangZones) {
        GangRatings[GANG_GROVE] = 0;
        GangRatings[GANG_BALLAS] = 1;
        GangRatings[GANG_VAGOS] = 2;

        GangRatingStrength[0] = groveZones;
        GangRatingStrength[1] = ballasZones;
        GangRatingStrength[2] = vagosZones;

        TerritoryUnderControlPercentage = static_cast<float>(groveZones) / static_cast<float>(allGangZones);

        // NOTSA code
        struct GangRanking {
            eGangID gang;
            uint32 controlled;
        } ranking[3] = {
            {GANG_BALLAS, ballasZones},
            {GANG_GROVE, groveZones},
            {GANG_VAGOS, vagosZones}
        };
        std::sort(ranking, ranking + 3, [&](GangRanking a, GangRanking b) { return a.controlled > b.controlled; });

        for (auto&& [i, e] : notsa::enumerate(ranking)) {
            GangRatings[e.gang] = i;
            GangRatingStrength[i] = e.controlled;
        }
    } else {
        TerritoryUnderControlPercentage = 0.0f;
    }
}
