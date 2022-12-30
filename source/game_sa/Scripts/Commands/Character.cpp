#include <StdInc.h>

#include "./Commands.hpp"
#include <CommandParser/Parser.hpp>

#include <TaskTypes/TaskComplexDie.h>
#include <TaskTypes/TaskSimpleCarSetPedInAsDriver.h>

#include <World.h>
#include <EntryExitManager.h>
#include <TimeCycle.h>
#include <ePedBones.h>

/*!
* Various character (ped) commands
*/

//! Fix angles (in degrees) - Dont ask.
auto FixAngleDegrees(float deg) {
    if (deg < 0.f) {
        return deg + 360.f;
    }
    if (deg > 360.f) {
        return deg - 360.f;
    }
    return deg;
}

void FixPosZ(CVector& pos) {
    if (pos.z <= -100.f) {
        pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
    }
}

//! Get the ped or it's vehicle (if in one)
auto GetPedOrItsVehicle(CPed& ped) -> CPhysical& {
    if (ped.IsInVehicle()) {
        return *ped.m_pVehicle;
    }
    return ped;
}

void SetCharProofs(CPed& ped, bool bullet, bool fire, bool explosion, bool collision, bool melee) {
    auto& flags = ped.physicalFlags;
    flags.bBulletProof = bullet;
    flags.bFireProof = fire;
    flags.bExplosionProof = explosion;
    flags.bCollisionProof = collision;
    flags.bMeleeProof = melee;
}

auto SetCharVelocity(CPed& ped, CVector velocity) {
    ped.SetVelocity(velocity / 50.f);
}

auto GetCharVelocity(CPed& ped) {
    return ped.GetMoveSpeed();
}

auto SetCharRotation(CPed& ped, CVector angles) {
    ped.SetOrientation(angles * DegreesToRadians(1.0f)); // make euler angles from degrees
    CWorld::Add(&ped);
}

auto SetCharAllowedToDuck(CPed& ped, CVector rotdeg) {
    CWorld::Remove(&ped);
    ped.SetOrientation(rotdeg * DegreesToRadians(1.f)); // degrees => radians
    CWorld::Add(&ped);
}

auto SetCharAreaVisible(CPed& ped, eAreaCodes area) {
    ped.m_nAreaCode = area;
    if (area != AREA_CODE_NORMAL_WORLD) {
        return;
    }
    ped.m_pEnex = nullptr;
    if (!ped.IsPlayer()) {
        return;
    }
    CEntryExitManager::ms_entryExitStackPosn = 0;
    CTimeCycle::StopExtraColour(0);
}

auto SetCharDropsWeaponsWhenDead(CPed& ped, bool dropsWepsWhenDead) {
    ped.bDoesntDropWeaponsWhenDead = !dropsWepsWhenDead;
}

auto SetCharNeverLeavesGroup(CPed& ped, bool bNeverLeavesGroup) {
    ped.bNeverLeavesGroup = bNeverLeavesGroup;
}

auto AttachFxSystemToCharBone(tScriptEffectSystem& fx, CPed& ped, ePedBones bone) {
    fx.m_pFxSystem->AttachToBone(&ped, bone);
}

auto GetDeadCharCoordinates(CPed& ped) {
    if (ped.IsInVehicle()) {
        return ped.m_pVehicle->GetPosition();
    } else {
        return ped.GetBonePosition(BONE_PELVIS);
    }
}

auto GetCharCoordinates(CPed& ped) {
    if (ped.IsInVehicle()) {
        return ped.m_pVehicle->GetPosition();
    } else {
        return ped.GetPosition();
    }
}

auto SetCharCoordinates(CPed& ped, CVector coords) {
    CRunningScript::SetCharCoordinates(&ped, coords.x, coords.y, coords.z, true, true);
}

auto IsCharInArea2D(CRunningScript& S, CPed& ped, CVector2D a, CVector2D b, bool highlightArea) {
    if (highlightArea) {
        S.HighlightImportantArea(a, b);
    }

    const auto Check = [&](const auto& e) { return e.IsWithinArea(a.x, a.y, b.x, b.y); };
    return ped.IsInVehicle()
        ? Check(*ped.m_pVehicle)
        : Check(ped);
}

auto IsCharInArea3D(CRunningScript& S, CPed& ped, CVector a, CVector b, bool highlightArea) {
    if (highlightArea) {
        S.HighlightImportantArea(a, b);
    }

    const auto Check = [&](const auto& e) { return e.IsWithinArea(a.x, a.y, a.z, b.x, b.y, b.z); };
    return ped.IsInVehicle()
        ? Check(*ped.m_pVehicle)
        : Check(ped);
}

auto StoreCarCharIsIn(CRunningScript& S, CPed& ped) { // 0x469481
    const auto veh = ped.GetVehicleIfInOne();

    if (GetVehiclePool()->GetRef(veh) != CTheScripts::StoreVehicleIndex && S.m_bUseMissionCleanup) {
        // Unstore previous (If it still exists)
        if (const auto stored = GetVehiclePool()->GetAt(CTheScripts::StoreVehicleIndex)) {
            CCarCtrl::RemoveFromInterestingVehicleList(stored);
            if (stored->IsMissionVehicle() && CTheScripts::StoreVehicleWasRandom) {
                stored->SetVehicleCreatedBy(RANDOM_VEHICLE);
                stored->vehicleFlags.bIsLocked = false;
                CTheScripts::MissionCleanUp.RemoveEntityFromList(CTheScripts::StoreVehicleIndex, MISSION_CLEANUP_ENTITY_TYPE_VEHICLE);
            }
        }

        // Now store this vehicle
        CTheScripts::StoreVehicleIndex = GetVehiclePool()->GetRef(veh);
        switch (veh->GetCreatedBy()) {
        case RANDOM_VEHICLE:
        case PARKED_VEHICLE: {
            veh->SetVehicleCreatedBy(MISSION_VEHICLE);
            CTheScripts::StoreVehicleWasRandom = true;
            CTheScripts::MissionCleanUp.AddEntityToList(CTheScripts::StoreVehicleIndex, MISSION_CLEANUP_ENTITY_TYPE_VEHICLE);
            break;
        }
        case MISSION_VEHICLE:
        case PERMANENT_VEHICLE: {
            CTheScripts::StoreVehicleWasRandom = false;
            break;
        }
        }
    }

    return CTheScripts::StoreVehicleIndex;
}

auto IsCharInCar(CPed& ped, CVehicle& veh) {
    return ped.IsInVehicle() && ped.m_pVehicle == &veh;
}

auto IsCharInModel(CPed& ped, eModelID model) {
    return ped.IsInVehicle() && ped.m_pVehicle->m_nModelIndex == model;
}

auto IsCharInAnyCar(CPed& ped) {
    return ped.IsInVehicle();
}

//
// Locate[Stopped]Character(Any Means/On Foot/In Car)
//

//! Does the usual checks
bool DoLocateCharChecks(CPed& ped, bool mustBeInCar, bool mustBeOnFoot, bool mustBeStopped) {
    if (mustBeInCar && !ped.IsInVehicle()) {
        return false;
    }
    if (mustBeOnFoot && ped.IsInVehicle()) {
        return false;
    }
    if (mustBeStopped && !CTheScripts::IsPedStopped(&ped)) {
        return false;
    }
    return true;
}

//! Check is char within 3D area (with some restrictions)
bool LocateChar3D(CRunningScript& S, CPed& ped, CVector pos, CVector radius, bool highlightArea, bool mustBeInCar, bool mustBeOnFoot, bool mustBeStopped) {
    const CBox bb{ pos - radius, pos + radius };
    if (highlightArea) { // Highlight area every time
        S.HighlightImportantArea(bb.m_vecMin, bb.m_vecMax);
    }
    if (!DoLocateCharChecks(ped, mustBeOnFoot, highlightArea, mustBeStopped)) {
        return false;
    }
    return bb.IsPointInside(GetCharCoordinates(ped));
}

bool LocateChar2D(CRunningScript& S, CPed& ped, CVector2D pos, CVector2D radius, bool highlightArea, bool mustBeInCar, bool mustBeOnFoot, bool mustBeStopped) {
    const CRect rect{ pos - radius, pos + radius };
    if (highlightArea) { // Highlight area every time
        S.HighlightImportantArea(rect.GetTopLeft(), rect.GetBottomRight());
    }
    if (!DoLocateCharChecks(ped, mustBeOnFoot, highlightArea, mustBeStopped)) {
        return false;
    }
    if (CTheScripts::DbgFlag) {
        CTheScripts::DrawDebugSquare(rect);
    }
    return rect.IsPointInside(GetCharCoordinates(ped));
}

auto LocateCharAnyMeans2D(CRunningScript& S, CPed& ped, CVector2D pos, CVector2D radius, bool highlightArea) {
    return LocateChar2D(S, ped, pos, radius, highlightArea, false, false, false);
}

auto LocateCharOnFoot2D(CRunningScript& S, CPed& ped, CVector2D pos, CVector2D radius, bool highlightArea) {
    return LocateChar2D(S, ped, pos, radius, highlightArea, false, true, false);
}

auto LocateCharInCar2D(CRunningScript& S, CPed& ped, CVector2D pos, CVector2D radius, bool highlightArea) {
    return LocateChar2D(S, ped, pos, radius, highlightArea, true, false, false);
}

auto LocateStoppedCharAnyMeans2D(CRunningScript& S, CPed& ped, CVector2D pos, CVector2D radius, bool highlightArea) {
    return LocateChar2D(S, ped, pos, radius, highlightArea, false, false, true);
}

auto LocateStoppedCharOnFoot2D(CRunningScript& S, CPed& ped, CVector2D pos, CVector2D radius, bool highlightArea) {
    return LocateChar2D(S, ped, pos, radius, highlightArea, false, true, true);
}

auto LocateStoppedCharInCar2D(CRunningScript& S, CPed& ped, CVector2D pos, CVector2D radius, bool highlightArea) {
    return LocateChar2D(S, ped, pos, radius, highlightArea, true, false, true);
}

auto LocateCharAnyMeans3D(CRunningScript& S, CPed& ped, CVector pos, CVector radius, bool highlightArea) {
    return LocateChar3D(S, ped, pos, radius, highlightArea, false, false, false);
}

auto LocateCharOnFoot3D(CRunningScript& S, CPed& ped, CVector pos, CVector radius, bool highlightArea) {
    return LocateChar3D(S, ped, pos, radius, highlightArea, false, true, false);
}

auto LocateCharInCar3D(CRunningScript& S, CPed& ped, CVector pos, CVector radius, bool highlightArea) {
    return LocateChar3D(S, ped, pos, radius, highlightArea, true, false, false);
}

auto LocateStoppedCharAnyMeans3D(CRunningScript& S, CPed& ped, CVector pos, CVector radius, bool highlightArea) {
    return LocateChar3D(S, ped, pos, radius, highlightArea, false, false, true);
}

auto LocateStoppedCharOnFoot3D(CRunningScript& S, CPed& ped, CVector pos, CVector radius, bool highlightArea) {
    return LocateChar3D(S, ped, pos, radius, highlightArea, false, true, true);
}

auto LocateStoppedCharInCar3D(CRunningScript& S, CPed& ped, CVector pos, CVector radius, bool highlightArea) {
    return LocateChar3D(S, ped, pos, radius, highlightArea, true, false, true);
}

bool LocateCharChar2D(CRunningScript& S, CPed& ped1, CPed& ped2, CVector2D radius, bool highlightArea, bool mustBeInCar, bool mustBeOnFoot) {
    return LocateChar2D(S, ped1, ped2.GetPosition2D(), radius, highlightArea, mustBeInCar, mustBeOnFoot, false);
}

auto LocateCharAnyMeansChar2D(CRunningScript& S, CPed& ped1, CPed& ped2, CVector2D radius, bool highlightArea) {
    return LocateCharChar2D(S, ped1, ped2, radius, highlightArea, false, false);
}

auto LocateCharOnFootChar2D(CRunningScript& S, CPed& ped1, CPed& ped2, CVector2D radius, bool highlightArea) {
    return LocateCharChar2D(S, ped1, ped2, radius, highlightArea, false, true);
}

auto LocateCharInCarChar2D(CRunningScript& S, CPed& ped1, CPed& ped2, CVector2D radius, bool highlightArea) {
    return LocateCharChar2D(S, ped1, ped2, radius, highlightArea, true, false);
}

bool LocateCharChar3D(CRunningScript& S, CPed& ped1, CPed& ped2, CVector radius, bool highlightArea, bool mustBeInCar, bool mustBeOnFoot) {
    return LocateChar3D(S, ped1, ped2.GetPosition(), radius, highlightArea, mustBeInCar, mustBeOnFoot, false);
}

auto LocateCharAnyMeansChar3D(CRunningScript& S, CPed& ped1, CPed& ped2, CVector radius, bool highlightArea) {
    return LocateCharChar3D(S, ped1, ped2, radius, highlightArea, false, false);
}

auto LocateCharOnFootChar3D(CRunningScript& S, CPed& ped1, CPed& ped2, CVector radius, bool highlightArea) {
    return LocateCharChar3D(S, ped1, ped2, radius, highlightArea, false, true);
}

auto LocateCharInCarChar3D(CRunningScript& S, CPed& ped1, CPed& ped2, CVector radius, bool highlightArea) {
    return LocateCharChar3D(S, ped1, ped2, radius, highlightArea, true, false);
}

bool LocateCharCar2D(CRunningScript& S, CPed& ped, CVehicle& veh, CVector2D radius, bool highlightArea, bool mustBeInCar, bool mustBeOnFoot) {
    return LocateChar2D(S, ped, veh.GetPosition(), radius, highlightArea, mustBeInCar, mustBeOnFoot, false);
}

auto LocateCharAnyMeansCar2D(CRunningScript& S, CPed& ped, CVehicle& veh, CVector2D radius, bool highlightArea) {
    return LocateCharCar2D(S, ped, veh, radius, highlightArea, false, false);
}

auto LocateCharOnFootCar2D(CRunningScript& S, CPed& ped, CVehicle& veh, CVector2D radius, bool highlightArea) {
    return LocateCharCar2D(S, ped, veh, radius, highlightArea, false, true);
}

auto LocateCharInCarCar2D(CRunningScript& S, CPed& ped, CVehicle& veh, CVector2D radius, bool highlightArea) {
    return LocateCharCar2D(S, ped, veh, radius, highlightArea, true, false);
}

bool LocateCharCar3D(CRunningScript& S, CPed& ped, CVehicle& veh, CVector radius, bool highlightArea, bool mustBeInCar, bool mustBeOnFoot) {
    return LocateChar3D(S, ped, veh.GetPosition(), radius, highlightArea, mustBeInCar, mustBeOnFoot, false);
}

auto LocateCharAnyMeansCar3D(CRunningScript& S, CPed& ped, CVehicle& veh, CVector radius, bool highlightArea) {
    return LocateCharCar3D(S, ped, veh, radius, highlightArea, false, false);
}

auto LocateCharOnFootCar3D(CRunningScript& S, CPed& ped, CVehicle& veh, CVector radius, bool highlightArea) {
    return LocateCharCar3D(S, ped, veh, radius, highlightArea, false, true);
}

auto LocateCharInCarCar3D(CRunningScript& S, CPed& ped, CVehicle& veh, CVector radius, bool highlightArea) {
    return LocateCharCar3D(S, ped, veh, radius, highlightArea, true, false);
}

auto IsCharDead(CPed* ped) {
    return !ped || ped->IsStateDeadForScript();
}

// IS_CHAR_IN_ZONE
auto IsCharInZone(CPed& ped, std::string_view zoneName) {
    return CTheZones::FindZone(GetCharCoordinates(ped), zoneName, ZONE_TYPE_NAVI);
}

// GET_CHAR_HEADING
auto GetCharHeading(CPed& ped) {
    return FixAngleDegrees(RWRAD2DEG(GetPedOrItsVehicle(ped).GetHeading()));
}

// SET_CHAR_HEADING
auto SetCharHeading(CPed& ped, float deg) {
    if (ped.IsInVehicle()) {
        return;
    }

    const auto rad = RWDEG2RAD(FixAngleDegrees(deg));
    ped.m_fAimingRotation = ped.m_fCurrentRotation = rad;
    ped.SetHeading(rad);
    ped.UpdateRW();
}

// IS_CHAR_TOUCHING_OBJECT
auto IsCharTouchingObject(CPed& ped, CObject& obj) {
    return GetPedOrItsVehicle(ped).GetHasCollidedWith(&obj);
}

// SET_CHAR_AMMO
auto SetCharAmmo(CPed& ped, eWeaponType wep, int32 nammo) {
    ped.SetAmmo(wep, nammo);
}

// IS_CHAR_HEALTH_GREATER
auto IsCharHealthGreater(CPed& ped, float health) {
    return ped.m_fHealth >= health;
}

//! Creates a character in the driver's seat of the vehicle
CPed& CreateCharInsideCar(CRunningScript& S, CVehicle& veh, ePedType pedType, eModelID pedModel) {
    const auto ped = [&]() -> CPed* {
        uint32 typeSpecificModelId = (uint32)(pedModel);
        S.GetCorrectPedModelIndexForEmergencyServiceType(pedType, &typeSpecificModelId);
        switch (pedType) {
        case PED_TYPE_COP:      return new CCopPed{ typeSpecificModelId };
        case PED_TYPE_MEDIC:
        case PED_TYPE_FIREMAN:  return new CEmergencyPed{ pedType, typeSpecificModelId };
        default:                return new CCivilianPed{ pedType, typeSpecificModelId };
        }
    }();

    ped->SetCharCreatedBy(PED_MISSION);
    ped->bAllowMedicsToReviveMe = false;
    CTaskSimpleCarSetPedInAsDriver{ &veh, false }.ProcessPed(ped); // Make ped get into da car
    CPopulation::ms_nTotalMissionPeds++;

    if (S.m_bUseMissionCleanup) {
        CTheScripts::MissionCleanUp.AddEntityToList(*ped);
    }

    return *ped;
}

// SET_CHAR_HEALTH
auto SetCharHealth(CPed& ped, float health) {
    if (health != 0.f) {
        if (ped.IsPlayer()) {
            ped.m_fHealth = std::min(health, ped.m_fMaxHealth);
        } else {
            ped.m_fHealth = health;
            if (ped.m_fMaxHealth == 100.f) {
                ped.m_fMaxHealth = health;
            }
        }
    } else { // Otherwise kill ped
        ped.GetIntelligence()->m_eventGroup.Add(
            CEventScriptCommand{
                TASK_PRIMARY_PRIMARY,
                new CTaskComplexDie{
                    WEAPON_UNARMED,
                    ANIM_GROUP_DEFAULT,
                    ANIM_ID_KO_SHOT_FRONT_0
                },
                false
            }
        );
    }
}

// GET_CHAR_HEALTH
auto GetCharHealth(CPed& ped) {
    return ped.m_fHealth;
}

// IS_CHAR_TOUCHING_OBJECT_ON_FOOT
auto IsCharTouchingObjectOnFoot(CPed& ped, CObject& obj) {
    return !ped.IsInVehicle() && ped.GetHasCollidedWith(&obj);
}

// IS_CHAR_STOPPED
auto IsCharStopped(CPed& ped) {
    return CTheScripts::IsPedStopped(&ped);
}

// SET_CHAR_ONLY_DAMAGED_BY_PLAYER
auto SetCharOnlyDamagedByPlayer(CPed& ped, bool enabled) {
    ped.physicalFlags.bInvulnerable = enabled;
}

// GET_CLOSEST_CHAR_NODE
auto GetClosestCharNode(CVector pos) -> CVector {
    FixPosZ(pos);
    if (const auto node = ThePaths.FindNodeClosestToCoors(pos)) {
        return ThePaths.GetPathNode(node)->GetNodeCoors();
    }
    return {}; // Can't find anything nearby
}

// IS_CHAR_ON_SCREEN
auto IsCharOnScreen(CPed& ped) {
    return ped.GetIsOnScreen();
}

// IS_CHAR_SHOOTING_IN_AREA
auto IsCharShootingInArea(CRunningScript& S, CPed& ped, CRect area, bool highlightArea) {
    if (highlightArea) {
        S.HighlightImportantArea(area);
    }

    if (CTheScripts::DbgFlag) {
        CTheScripts::DrawDebugSquare(area);
    }

    return ped.bFiringWeapon && area.IsPointInside(ped.GetPosition2D());
}

// IS_CURRENT_CHAR_WEAPON
auto IsCurrentCharWeapon(CPed& ped, eWeaponType wep) {
    if (wep == WEAPON_ANYMELEE && ped.GetActiveWeapon().IsTypeMelee()) {
        return true;
    }
    return ped.GetActiveWeapon().m_nType == wep;
}

// GET_RANDOM_CHAR_IN_ZONE
auto GetRandomCharInZone(CRunningScript& S, std::string_view zoneName, bool civillian, bool gang, bool criminal) -> CPed* { // 0x04802D0
    const auto playerPosZ = FindPlayerCoors().z;
    for (auto& ped : GetPedPool()->GetAllValid()) {
        const auto pedHandle = GetPedPool()->GetRef(&ped);
        if (   pedHandle == CTheScripts::LastRandomPedId
            || !ped.IsCreatedBy(PED_GAME)
            || ped.m_bRemoveFromWorld
            || ped.bFadeOut
            || ped.IsStateDeadForScript()
            || ped.IsInVehicle()
            || !S.ThisIsAValidRandomPed(ped.m_nPedType, civillian, gang, criminal)
            || ped.GetGroup()
        ) {
            continue;
        }
        const auto pos = ped.GetPosition();
        if (!CTheZones::FindZone(ped.GetPosition(), zoneName, ZONE_TYPE_NAVI)) {
            continue;
        }
        if (playerPosZ - 5.f > pos.z || playerPosZ + 5.f < pos.z) {
            continue;
        }
        bool roofZFound{};
        (void)(CWorld::FindRoofZFor3DCoord(pos.x, pos.y, pos.z, &roofZFound));
        if (roofZFound) {
            continue;
        }
        CTheScripts::LastRandomPedId = pedHandle;
        ped.SetCharCreatedBy(PED_MISSION);
        CPopulation::ms_nTotalMissionPeds++;
        if (S.m_bUseMissionCleanup) {
            CTheScripts::MissionCleanUp.AddEntityToList(ped);
        }

        // They forgot to return here (did it instead after the loop), so let's do that
        return &ped;
    }
    return nullptr; // No suitable ped found
}

// IS_CHAR_SHOOTING
auto IsCharShooting(CPed& ped) {
    return ped.bFiringWeapon;
}

// SET_CHAR_ACCURACY
auto SetCharAccuracy(CPed& ped) {

}

// IS_CHAR_MODEL
auto IsCharModel(CPed& ped, int8 accuracy) {
    ped.m_nWeaponAccuracy = accuracy;
}

void notsa::script::commands::character::RegisterHandlers() {
    REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_PROOFS, SetCharProofs);
    REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_VELOCITY, SetCharVelocity);
    REGISTER_COMMAND_HANDLER(COMMAND_GET_CHAR_VELOCITY, GetCharVelocity);
    REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_ROTATION, SetCharRotation);
    REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_ALLOWED_TO_DUCK, SetCharAllowedToDuck);
    REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_AREA_VISIBLE, SetCharAreaVisible);
    REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_DROPS_WEAPONS_WHEN_DEAD, SetCharDropsWeaponsWhenDead);
    REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_NEVER_LEAVES_GROUP, SetCharNeverLeavesGroup);
    REGISTER_COMMAND_HANDLER(COMMAND_ATTACH_FX_SYSTEM_TO_CHAR_BONE, AttachFxSystemToCharBone);
    REGISTER_COMMAND_HANDLER(COMMAND_GET_DEAD_CHAR_COORDINATES, GetDeadCharCoordinates);
    REGISTER_COMMAND_HANDLER(COMMAND_GET_CHAR_COORDINATES, GetCharCoordinates);
    REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_COORDINATES, SetCharCoordinates);
    REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_IN_AREA_2D, IsCharInArea2D);
    REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_IN_AREA_3D, IsCharInArea3D);
    REGISTER_COMMAND_HANDLER(COMMAND_STORE_CAR_CHAR_IS_IN, StoreCarCharIsIn);
    REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_IN_CAR, IsCharInCar);
    REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_IN_MODEL, IsCharInModel);
    REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_IN_ANY_CAR, IsCharInAnyCar);

    REGISTER_COMMAND_HANDLER(COMMAND_LOCATE_CHAR_ANY_MEANS_2D, LocateCharAnyMeans2D);
    REGISTER_COMMAND_HANDLER(COMMAND_LOCATE_CHAR_ON_FOOT_2D, LocateCharOnFoot2D);
    REGISTER_COMMAND_HANDLER(COMMAND_LOCATE_CHAR_IN_CAR_2D, LocateCharInCar2D);
    REGISTER_COMMAND_HANDLER(COMMAND_LOCATE_STOPPED_CHAR_ANY_MEANS_2D, LocateStoppedCharAnyMeans2D);
    REGISTER_COMMAND_HANDLER(COMMAND_LOCATE_STOPPED_CHAR_ON_FOOT_2D, LocateStoppedCharOnFoot2D);
    REGISTER_COMMAND_HANDLER(COMMAND_LOCATE_STOPPED_CHAR_IN_CAR_2D, LocateStoppedCharInCar2D);
    REGISTER_COMMAND_HANDLER(COMMAND_LOCATE_CHAR_ANY_MEANS_3D, LocateCharAnyMeans3D);
    REGISTER_COMMAND_HANDLER(COMMAND_LOCATE_CHAR_ON_FOOT_3D, LocateCharOnFoot3D);
    REGISTER_COMMAND_HANDLER(COMMAND_LOCATE_CHAR_IN_CAR_3D, LocateCharInCar3D);
    REGISTER_COMMAND_HANDLER(COMMAND_LOCATE_STOPPED_CHAR_ANY_MEANS_3D, LocateStoppedCharAnyMeans3D);
    REGISTER_COMMAND_HANDLER(COMMAND_LOCATE_STOPPED_CHAR_ON_FOOT_3D, LocateStoppedCharOnFoot3D);
    REGISTER_COMMAND_HANDLER(COMMAND_LOCATE_STOPPED_CHAR_IN_CAR_3D, LocateStoppedCharInCar3D);
    REGISTER_COMMAND_HANDLER(COMMAND_LOCATE_CHAR_ANY_MEANS_CHAR_2D, LocateCharAnyMeansChar2D);
    REGISTER_COMMAND_HANDLER(COMMAND_LOCATE_CHAR_ON_FOOT_CHAR_2D, LocateCharOnFootChar2D);
    REGISTER_COMMAND_HANDLER(COMMAND_LOCATE_CHAR_IN_CAR_CHAR_2D, LocateCharInCarChar2D);
    REGISTER_COMMAND_HANDLER(COMMAND_LOCATE_CHAR_ANY_MEANS_CHAR_3D, LocateCharAnyMeansChar3D);
    REGISTER_COMMAND_HANDLER(COMMAND_LOCATE_CHAR_ON_FOOT_CHAR_3D, LocateCharOnFootChar3D);
    REGISTER_COMMAND_HANDLER(COMMAND_LOCATE_CHAR_IN_CAR_CHAR_3D, LocateCharInCarChar3D);
    REGISTER_COMMAND_HANDLER(COMMAND_LOCATE_CHAR_ANY_MEANS_CAR_2D, LocateCharAnyMeansCar2D);
    REGISTER_COMMAND_HANDLER(COMMAND_LOCATE_CHAR_ON_FOOT_CAR_2D, LocateCharOnFootCar2D);
    REGISTER_COMMAND_HANDLER(COMMAND_LOCATE_CHAR_IN_CAR_CAR_2D, LocateCharInCarCar2D);
    REGISTER_COMMAND_HANDLER(COMMAND_LOCATE_CHAR_ANY_MEANS_CAR_3D, LocateCharAnyMeansCar3D);
    REGISTER_COMMAND_HANDLER(COMMAND_LOCATE_CHAR_ON_FOOT_CAR_3D, LocateCharOnFootCar3D);
    REGISTER_COMMAND_HANDLER(COMMAND_LOCATE_CHAR_IN_CAR_CAR_3D, LocateCharInCarCar3D);

    REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_DEAD, IsCharDead);
    REGISTER_COMMAND_HANDLER(COMMAND_CREATE_CHAR_INSIDE_CAR, CreateCharInsideCar);
    REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_IN_ZONE, IsCharInZone);
    REGISTER_COMMAND_HANDLER(COMMAND_GET_CHAR_HEADING, GetCharHeading);
    REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_HEADING, SetCharHeading);
    REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_TOUCHING_OBJECT, IsCharTouchingObject);
    REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_AMMO, SetCharAmmo);
    REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_HEALTH_GREATER, IsCharHealthGreater);
    REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_HEALTH, SetCharHealth);
    REGISTER_COMMAND_HANDLER(COMMAND_GET_CHAR_HEALTH, GetCharHealth);
    REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_TOUCHING_OBJECT_ON_FOOT, IsCharTouchingObjectOnFoot);
    REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_STOPPED, IsCharStopped);
    REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_ONLY_DAMAGED_BY_PLAYER, SetCharOnlyDamagedByPlayer);
    REGISTER_COMMAND_HANDLER(COMMAND_GET_CLOSEST_CHAR_NODE, GetClosestCharNode);
    REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_ON_SCREEN, IsCharOnScreen);
    REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_SHOOTING_IN_AREA, IsCharShootingInArea);
    REGISTER_COMMAND_HANDLER(COMMAND_IS_CURRENT_CHAR_WEAPON, IsCurrentCharWeapon);
    REGISTER_COMMAND_HANDLER(COMMAND_GET_RANDOM_CHAR_IN_ZONE, GetRandomCharInZone);
    REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_SHOOTING, IsCharShooting);
    REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_ACCURACY, SetCharAccuracy);

    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_SET_CHAR_GRAPHIC_TYPE);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_STOP_CHAR_DRIVING);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_SET_CHAR_OCCUPATION);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_IS_CHAR_IN_GANG_ZONE);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_ADD_BLIP_FOR_CHAR_OLD);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_LOCATE_PLAYER_ANY_MEANS_CHAR_2D);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_IS_CHAR_STILL_ALIVE);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_LOCATE_PLAYER_ON_FOOT_CHAR_2D);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_LOCATE_PLAYER_IN_CAR_CHAR_2D);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_LOCATE_PLAYER_ANY_MEANS_CHAR_3D);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_LOCATE_PLAYER_ON_FOOT_CHAR_3D);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_LOCATE_PLAYER_IN_CAR_CHAR_3D);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_SET_CHAR_THREAT_SEARCH);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_SET_CHAR_THREAT_REACTION);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_SET_CHAR_OBJ_NO_OBJ);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_ORDER_CHAR_TO_DRIVE_CAR);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_HAS_CHAR_SPOTTED_PLAYER);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_ORDER_CHAR_TO_BACKDOOR);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_ADD_CHAR_TO_GANG);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_IS_CHAR_OBJECTIVE_PASSED);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_SET_CHAR_DRIVE_AGGRESSION);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_SET_CHAR_MAX_DRIVESPEED);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_MAKE_CHAR_DO_NOTHING);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_SET_CHAR_INVINCIBLE);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_SET_CHAR_OBJ_WAIT_ON_FOOT);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_SET_CHAR_OBJ_FLEE_ON_FOOT_TILL_SAFE);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_SET_CHAR_OBJ_GUARD_SPOT);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_SET_CHAR_OBJ_GUARD_AREA);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_SET_CHAR_OBJ_WAIT_IN_CAR);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_IS_CHAR_IN_AREA_ON_FOOT_2D);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_IS_CHAR_IN_AREA_IN_CAR_2D);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_IS_CHAR_STOPPED_IN_AREA_2D);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_IS_CHAR_STOPPED_IN_AREA_ON_FOOT_2D);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_IS_CHAR_STOPPED_IN_AREA_IN_CAR_2D);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_IS_CHAR_IN_AREA_ON_FOOT_3D);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_IS_CHAR_IN_AREA_IN_CAR_3D);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_IS_CHAR_STOPPED_IN_AREA_3D);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_IS_CHAR_STOPPED_IN_AREA_ON_FOOT_3D);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_IS_CHAR_STOPPED_IN_AREA_IN_CAR_3D);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_SET_CURRENT_CHAR_WEAPON);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_TURN_CHAR_TO_FACE_COORD);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_MARK_CHAR_AS_NO_LONGER_NEEDED);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_CREATE_CHAR_AS_PASSENGER);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_SET_CHAR_OBJ_KILL_CHAR_ON_FOOT);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_SET_CHAR_OBJ_KILL_PLAYER_ON_FOOT);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_SET_CHAR_OBJ_KILL_CHAR_ANY_MEANS);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_SET_CHAR_OBJ_KILL_PLAYER_ANY_MEANS);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_SET_CHAR_OBJ_FLEE_CHAR_ON_FOOT_TILL_SAFE);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_SET_CHAR_OBJ_FLEE_PLAYER_ON_FOOT_TILL_SAFE);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_SET_CHAR_OBJ_FLEE_CHAR_ON_FOOT_ALWAYS);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_SET_CHAR_OBJ_FLEE_PLAYER_ON_FOOT_ALWAYS);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_SET_CHAR_OBJ_GOTO_CHAR_ON_FOOT);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_SET_CHAR_OBJ_GOTO_PLAYER_ON_FOOT);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_SET_CHAR_OBJ_LEAVE_CAR);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_SET_CHAR_OBJ_ENTER_CAR_AS_PASSENGER);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_SET_CHAR_OBJ_ENTER_CAR_AS_DRIVER);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_SET_CHAR_OBJ_FOLLOW_CAR_IN_CAR);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_SET_CHAR_OBJ_FIRE_AT_OBJECT_FROM_VEHICLE);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_SET_CHAR_OBJ_DESTROY_OBJECT);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_SET_CHAR_OBJ_DESTROY_CAR);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_SET_CHAR_OBJ_GOTO_AREA_ON_FOOT);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_SET_CHAR_OBJ_GOTO_AREA_IN_CAR);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_SET_CHAR_OBJ_FOLLOW_CAR_ON_FOOT_WITH_OFFSET);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_SET_CHAR_OBJ_GUARD_ATTACK);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_SET_CHAR_AS_LEADER);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_SET_CHAR_OBJ_FOLLOW_ROUTE);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_CLEAR_CHAR_THREAT_SEARCH);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_TURN_CHAR_TO_FACE_CHAR);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_TURN_CHAR_TO_FACE_PLAYER);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_SET_CHAR_OBJ_GOTO_COORD_ON_FOOT);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_SET_CHAR_OBJ_GOTO_COORD_IN_CAR);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_CHAR_LOOK_AT_CHAR_ALWAYS);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_PLAYER_LOOK_AT_CHAR_ALWAYS);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_STOP_CHAR_LOOKING);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_SET_CHAR_OBJ_RUN_TO_AREA);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_SET_CHAR_OBJ_RUN_TO_COORD);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_SET_CHAR_PERSONALITY);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_SET_COLL_OBJ_KILL_CHAR_ON_FOOT);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_SET_COLL_OBJ_KILL_CHAR_ANY_MEANS);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_SET_COLL_OBJ_FLEE_CHAR_ON_FOOT_TILL_SAFE);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_SET_COLL_OBJ_FLEE_CHAR_ON_FOOT_ALWAYS);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_SET_COLL_OBJ_GOTO_CHAR_ON_FOOT);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_LOCATE_COLL_ANY_MEANS_CHAR_2D);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_LOCATE_COLL_ON_FOOT_CHAR_2D);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_LOCATE_COLL_IN_CAR_CHAR_2D);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_SET_CHAR_HEED_THREATS);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_SET_CHAR_OBJ_GOTO_AREA_ANY_MEANS);
    REGISTER_COMMAND_HANDLER_UNIMPLEMENTED(COMMAND_GET_RANDOM_CHAR_IN_AREA);
    //REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_MODEL, IsCharModel);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_OBJ_FOLLOW_CHAR_IN_FORMATION, SetCharObjFollowCharInFormation);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_RUNNING, SetCharRunning);
    //REGISTER_COMMAND_HANDLER(COMMAND_HAS_CHAR_BEEN_DAMAGED_BY_WEAPON, HasCharBeenDamagedByWeapon);
    //REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_IN_CHARS_GROUP, IsCharInCharsGroup);
    //REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_IN_PLAYERS_GROUP, IsCharInPlayersGroup);
    //REGISTER_COMMAND_HANDLER(COMMAND_EXPLODE_CHAR_HEAD, ExplodeCharHead);
    //REGISTER_COMMAND_HANDLER(COMMAND_START_CHAR_FIRE, StartCharFire);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_OBJ_CATCH_TRAIN, SetCharObjCatchTrain);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_BLEEDING, SetCharBleeding);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_VISIBLE, SetCharVisible);
    //REGISTER_COMMAND_HANDLER(COMMAND_REMOVE_CHAR_ELEGANTLY, RemoveCharElegantly);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_STAY_IN_SAME_PLACE, SetCharStayInSamePlace);
    //REGISTER_COMMAND_HANDLER(COMMAND_WARP_CHAR_FROM_CAR_TO_COORD, WarpCharFromCarToCoord);
    //REGISTER_COMMAND_HANDLER(COMMAND_HAS_CHAR_SPOTTED_CHAR, HasCharSpottedChar);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_OBJ_HAIL_TAXI, SetCharObjHailTaxi);
    //REGISTER_COMMAND_HANDLER(COMMAND_WARP_CHAR_INTO_CAR, WarpCharIntoCar);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_WAIT_STATE, SetCharWaitState);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_OBJ_STEAL_ANY_CAR, SetCharObjStealAnyCar);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_ANIM_SPEED, SetCharAnimSpeed);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_CANT_BE_DRAGGED_OUT, SetCharCantBeDraggedOut);
    //REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_MALE, IsCharMale);
    //REGISTER_COMMAND_HANDLER(COMMAND_STORE_CAR_CHAR_IS_IN_NO_SAVE, StoreCarCharIsInNoSave);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_OBJ_LEAVE_ANY_CAR, SetCharObjLeaveAnyCar);
    //REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_IN_CONTROL, IsCharInControl);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_STAYS_IN_CURRENT_LEVEL, SetCharStaysInCurrentLevel);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_MONEY, SetCharMoney);
    //REGISTER_COMMAND_HANDLER(COMMAND_INCREASE_CHAR_MONEY, IncreaseCharMoney);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_USE_PEDNODE_SEEK, SetCharUsePednodeSeek);
    //REGISTER_COMMAND_HANDLER(COMMAND_GET_AMMO_IN_CHAR_WEAPON, GetAmmoInCharWeapon);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_SAY, SetCharSay);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_AVOID_LEVEL_TRANSITIONS, SetCharAvoidLevelTransitions);
    //REGISTER_COMMAND_HANDLER(COMMAND_WARP_CHAR_INTO_CAR_AS_PASSENGER, WarpCharIntoCarAsPassenger);
    //REGISTER_COMMAND_HANDLER(COMMAND_GET_CHAR_IN_CAR_PASSENGER_SEAT, GetCharInCarPassengerSeat);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_IS_CHRIS_CRIMINAL, SetCharIsChrisCriminal);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_IGNORE_LEVEL_TRANSITIONS, SetCharIgnoreLevelTransitions);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_SUFFERS_CRITICAL_HITS, SetCharSuffersCriticalHits);
    //REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_SITTING_IN_CAR, IsCharSittingInCar);
    //REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_SITTING_IN_ANY_CAR, IsCharSittingInAnyCar);
    //REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_ON_FOOT, IsCharOnFoot);
    //REGISTER_COMMAND_HANDLER(COMMAND_ATTACH_CHAR_TO_CAR, AttachCharToCar);
    //REGISTER_COMMAND_HANDLER(COMMAND_DETACH_CHAR_FROM_CAR, DetachCharFromCar);
    //REGISTER_COMMAND_HANDLER(COMMAND_CLEAR_CHAR_LAST_WEAPON_DAMAGE, ClearCharLastWeaponDamage);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_OBJ_FLEE_CAR, SetCharObjFleeCar);
    //REGISTER_COMMAND_HANDLER(COMMAND_GET_CURRENT_CHAR_WEAPON, GetCurrentCharWeapon);
    //REGISTER_COMMAND_HANDLER(COMMAND_LOCATE_CHAR_ANY_MEANS_OBJECT_2D, LocateCharAnyMeansObject2D);
    //REGISTER_COMMAND_HANDLER(COMMAND_LOCATE_CHAR_ON_FOOT_OBJECT_2D, LocateCharOnFootObject2D);
    //REGISTER_COMMAND_HANDLER(COMMAND_LOCATE_CHAR_IN_CAR_OBJECT_2D, LocateCharInCarObject2D);
    //REGISTER_COMMAND_HANDLER(COMMAND_LOCATE_CHAR_ANY_MEANS_OBJECT_3D, LocateCharAnyMeansObject3D);
    //REGISTER_COMMAND_HANDLER(COMMAND_LOCATE_CHAR_ON_FOOT_OBJECT_3D, LocateCharOnFootObject3D);
    //REGISTER_COMMAND_HANDLER(COMMAND_LOCATE_CHAR_IN_CAR_OBJECT_3D, LocateCharInCarObject3D);
    //REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_ON_ANY_BIKE, IsCharOnAnyBike);
    //REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_LYING_DOWN, IsCharLyingDown);
    //REGISTER_COMMAND_HANDLER(COMMAND_CAN_CHAR_SEE_DEAD_CHAR, CanCharSeeDeadChar);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_CEASE_ATTACK_TIMER, SetCharCeaseAttackTimer);
    //REGISTER_COMMAND_HANDLER(COMMAND_SHUT_CHAR_UP, ShutCharUp);
    //REGISTER_COMMAND_HANDLER(COMMAND_REMOVE_ALL_CHAR_WEAPONS, RemoveAllCharWeapons);
    //REGISTER_COMMAND_HANDLER(COMMAND_HAS_CHAR_GOT_WEAPON, HasCharGotWeapon);
    //REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_FOOT_DOWN, IsCharFootDown);
    //REGISTER_COMMAND_HANDLER(COMMAND_GET_DEAD_CHAR_PICKUP_COORDS, GetDeadCharPickupCoords);
    //REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_IN_ANY_BOAT, IsCharInAnyBoat);
    //REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_IN_ANY_HELI, IsCharInAnyHeli);
    //REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_IN_ANY_PLANE, IsCharInAnyPlane);
    //REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_IN_WATER, IsCharInWater);
    //REGISTER_COMMAND_HANDLER(COMMAND_GET_CHAR_WEAPON_IN_SLOT, GetCharWeaponInSlot);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_OBJ_WALK_TO_CHAR, SetCharObjWalkToChar);
    //REGISTER_COMMAND_HANDLER(COMMAND_GET_OFFSET_FROM_CHAR_IN_WORLD_COORDS, GetOffsetFromCharInWorldCoords);
    //REGISTER_COMMAND_HANDLER(COMMAND_HAS_CHAR_BEEN_PHOTOGRAPHED, HasCharBeenPhotographed);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_OBJ_AIM_GUN_AT_CHAR, SetCharObjAimGunAtChar);
    //REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_IN_FLYING_VEHICLE, IsCharInFlyingVehicle);
    //REGISTER_COMMAND_HANDLER(COMMAND_GET_NTH_CLOSEST_CHAR_NODE, GetNthClosestCharNode);
    //REGISTER_COMMAND_HANDLER(COMMAND_FREEZE_CHAR_POSITION, FreezeCharPosition);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_DROWNS_IN_WATER, SetCharDrownsInWater);
    //REGISTER_COMMAND_HANDLER(COMMAND_GET_CHAR_ARMOUR, GetCharArmour);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_ARMOUR, SetCharArmour);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_OBJ_STEAL_ANY_CAR_EVEN_MISSION_CAR, SetCharObjStealAnyCarEvenMissionCar);
    //REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_WAITING_FOR_WORLD_COLLISION, IsCharWaitingForWorldCollision);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_SHUFFLE_INTO_DRIVERS_SEAT, SetCharShuffleIntoDriversSeat);
    //REGISTER_COMMAND_HANDLER(COMMAND_ATTACH_CHAR_TO_OBJECT, AttachCharToObject);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_AS_PLAYER_FRIEND, SetCharAsPlayerFriend);
    //REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_OBJ_NO_OBJ, IsCharObjNoObj);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_OBJ_SPRINT_TO_COORD, SetCharObjSprintToCoord);
    //REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_LEAVING_VEHICLE_TO_DIE, IsCharLeavingVehicleToDie);
    //REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_WANDER_PATH_CLEAR, IsCharWanderPathClear);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_CAN_BE_DAMAGED_BY_MEMBERS_OF_GANG, SetCharCanBeDamagedByMembersOfGang);
    //REGISTER_COMMAND_HANDLER(COMMAND_HAS_CHAR_BEEN_DAMAGED_BY_CHAR, HasCharBeenDamagedByChar);
    //REGISTER_COMMAND_HANDLER(COMMAND_HAS_CHAR_BEEN_DAMAGED_BY_CAR, HasCharBeenDamagedByCar);
    //REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_DROWNING_IN_WATER, IsCharDrowningInWater);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_STAY_IN_CAR_WHEN_JACKED, SetCharStayInCarWhenJacked);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_ANSWERING_MOBILE, SetCharAnsweringMobile);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_IN_PLAYERS_GROUP_CAN_FIGHT, SetCharInPlayersGroupCanFight);
    //REGISTER_COMMAND_HANDLER(COMMAND_CLEAR_CHAR_WAIT_STATE, ClearCharWaitState);
    //REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_TOUCHING_VEHICLE, IsCharTouchingVehicle);
    //REGISTER_COMMAND_HANDLER(COMMAND_CLEAR_CHAR_FOLLOW_PATH, ClearCharFollowPath);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_CAN_BE_SHOT_IN_VEHICLE, SetCharCanBeShotInVehicle);
    //REGISTER_COMMAND_HANDLER(COMMAND_CLEAR_CHAR_LAST_DAMAGE_ENTITY, ClearCharLastDamageEntity);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_OBJ_GOTO_CAR_ON_FOOT, SetCharObjGotoCarOnFoot);
    //REGISTER_COMMAND_HANDLER(COMMAND_CREATE_RANDOM_CHAR_AS_DRIVER, CreateRandomCharAsDriver);
    //REGISTER_COMMAND_HANDLER(COMMAND_CREATE_RANDOM_CHAR_AS_PASSENGER, CreateRandomCharAsPassenger);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_IGNORE_THREATS_BEHIND_OBJECTS, SetCharIgnoreThreatsBehindObjects);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_NEVER_TARGETTED, SetCharNeverTargetted);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_CROUCH_WHEN_THREATENED, SetCharCrouchWhenThreatened);
    //REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_IN_ANY_POLICE_VEHICLE, IsCharInAnyPoliceVehicle);
    //REGISTER_COMMAND_HANDLER(COMMAND_DOES_CHAR_EXIST, DoesCharExist);
    //REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_STUCK, IsCharStuck);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_STOP_SHOOT_DONT_SEEK_ENTITY, SetCharStopShootDontSeekEntity);
    //REGISTER_COMMAND_HANDLER(COMMAND_FREEZE_CHAR_POSITION_AND_DONT_LOAD_COLLISION, FreezeCharPositionAndDontLoadCollision);
    //REGISTER_COMMAND_HANDLER(COMMAND_CLEAR_ALL_CHAR_ANIMS, ClearAllCharAnims);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_OBJ_BUY_ICE_CREAM, SetCharObjBuyIceCream);
    //REGISTER_COMMAND_HANDLER(COMMAND_CLEAR_CHAR_ICE_CREAM_PURCHASE, ClearCharIceCreamPurchase);
    //REGISTER_COMMAND_HANDLER(COMMAND_HAS_CHAR_ATTEMPTED_ATTRACTOR, HasCharAttemptedAttractor);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_LOAD_COLLISION_FOR_CHAR_FLAG, SetLoadCollisionForCharFlag);
    //REGISTER_COMMAND_HANDLER(COMMAND_HAS_CHAR_BOUGHT_ICE_CREAM, HasCharBoughtIceCream);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_FRIGHTENED_IN_JACKED_CAR, SetCharFrightenedInJackedCar);
    //REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_DUCKING, IsCharDucking);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_IN_DISGUISE, SetCharInDisguise);
    //REGISTER_COMMAND_HANDLER(COMMAND_TASK_KILL_CHAR_ON_FOOT, TaskKillCharOnFoot);
    //REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_IN_ANGLED_AREA_2D, IsCharInAngledArea2D);
    //REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_IN_ANGLED_AREA_ON_FOOT_2D, IsCharInAngledAreaOnFoot2D);
    //REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_IN_ANGLED_AREA_IN_CAR_2D, IsCharInAngledAreaInCar2D);
    //REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_STOPPED_IN_ANGLED_AREA_2D, IsCharStoppedInAngledArea2D);
    //REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_STOPPED_IN_ANGLED_AREA_ON_FOOT_2D, IsCharStoppedInAngledAreaOnFoot2D);
    //REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_STOPPED_IN_ANGLED_AREA_IN_CAR_2D, IsCharStoppedInAngledAreaInCar2D);
    //REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_IN_ANGLED_AREA_3D, IsCharInAngledArea3D);
    //REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_IN_ANGLED_AREA_ON_FOOT_3D, IsCharInAngledAreaOnFoot3D);
    //REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_IN_ANGLED_AREA_IN_CAR_3D, IsCharInAngledAreaInCar3D);
    //REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_STOPPED_IN_ANGLED_AREA_3D, IsCharStoppedInAngledArea3D);
    //REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_STOPPED_IN_ANGLED_AREA_ON_FOOT_3D, IsCharStoppedInAngledAreaOnFoot3D);
    //REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_STOPPED_IN_ANGLED_AREA_IN_CAR_3D, IsCharStoppedInAngledAreaInCar3D);
    //REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_IN_TAXI, IsCharInTaxi);
    //REGISTER_COMMAND_HANDLER(COMMAND_LOAD_CHAR_DECISION_MAKER, LoadCharDecisionMaker);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_DECISION_MAKER, SetCharDecisionMaker);
    //REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_PLAYING_ANIM, IsCharPlayingAnim);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_ANIM_PLAYING_FLAG, SetCharAnimPlayingFlag);
    //REGISTER_COMMAND_HANDLER(COMMAND_GET_CHAR_ANIM_CURRENT_TIME, GetCharAnimCurrentTime);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_ANIM_CURRENT_TIME, SetCharAnimCurrentTime);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_COLLISION, SetCharCollision);
    //REGISTER_COMMAND_HANDLER(COMMAND_GET_CHAR_ANIM_TOTAL_TIME, GetCharAnimTotalTime);
    //REGISTER_COMMAND_HANDLER(COMMAND_CREATE_CHAR_AT_ATTRACTOR, CreateCharAtAttractor);
    //REGISTER_COMMAND_HANDLER(COMMAND_TASK_KILL_CHAR_ON_FOOT_WHILE_DUCKING, TaskKillCharOnFootWhileDucking);
    //REGISTER_COMMAND_HANDLER(COMMAND_TASK_TURN_CHAR_TO_FACE_CHAR, TaskTurnCharToFaceChar);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_THREAT_LIST, SetCharThreatList);
    //REGISTER_COMMAND_HANDLER(COMMAND_CLEAR_CHAR_THREATS, ClearCharThreats);
    //REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_AT_SCRIPTED_ATTRACTOR, IsCharAtScriptedAttractor);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_ZONE_DISTANCE, SetCharZoneDistance);
    //REGISTER_COMMAND_HANDLER(COMMAND_PLACE_CHAR_AT_ATTRACTOR, PlaceCharAtAttractor);
    //REGISTER_COMMAND_HANDLER(COMMAND_GET_CHAR_MODEL, GetCharModel);
    //REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_TOUCHING_ANY_OBJECT, IsCharTouchingAnyObject);
    //REGISTER_COMMAND_HANDLER(COMMAND_CREATE_FX_SYSTEM_ON_CHAR_WITH_DIRECTION, CreateFxSystemOnCharWithDirection);
    //REGISTER_COMMAND_HANDLER(COMMAND_GET_CHAR_AT_SCRIPTED_ATTRACTOR, GetCharAtScriptedAttractor);
    //REGISTER_COMMAND_HANDLER(COMMAND_ATTACH_CAMERA_TO_CHAR_LOOK_AT_VEHICLE, AttachCameraToCharLookAtVehicle);
    //REGISTER_COMMAND_HANDLER(COMMAND_ATTACH_CAMERA_TO_CHAR_LOOK_AT_CHAR, AttachCameraToCharLookAtChar);
    //REGISTER_COMMAND_HANDLER(COMMAND_CLEAR_CHAR_TASKS, ClearCharTasks);
    //REGISTER_COMMAND_HANDLER(COMMAND_CLEAR_CHAR_FRIENDS, ClearCharFriends);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_FRIEND_LIST, SetCharFriendList);
    //REGISTER_COMMAND_HANDLER(COMMAND_ATTACH_CAMERA_TO_CHAR_LOOK_AT_OBJECT, AttachCameraToCharLookAtObject);
    //REGISTER_COMMAND_HANDLER(COMMAND_ATTACH_CHAR_TO_BIKE, AttachCharToBike);
    //REGISTER_COMMAND_HANDLER(COMMAND_TASK_GOTO_CHAR_OFFSET, TaskGotoCharOffset);
    //REGISTER_COMMAND_HANDLER(COMMAND_HIDE_CHAR_WEAPON_FOR_SCRIPTED_CUTSCENE, HideCharWeaponForScriptedCutscene);
    //REGISTER_COMMAND_HANDLER(COMMAND_GET_CHAR_SPEED, GetCharSpeed);
    //REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_IN_SEARCHLIGHT, IsCharInSearchlight);
    //REGISTER_COMMAND_HANDLER(COMMAND_TASK_TURN_CHAR_TO_FACE_COORD, TaskTurnCharToFaceCoord);
    //REGISTER_COMMAND_HANDLER(COMMAND_REMOVE_CHAR_FROM_GROUP, RemoveCharFromGroup);
    //REGISTER_COMMAND_HANDLER(COMMAND_TASK_CHAR_ARREST_CHAR, TaskCharArrestChar);
    //REGISTER_COMMAND_HANDLER(COMMAND_CLEAR_CHAR_DECISION_MAKER_EVENT_RESPONSE, ClearCharDecisionMakerEventResponse);
    //REGISTER_COMMAND_HANDLER(COMMAND_ADD_CHAR_DECISION_MAKER_EVENT_RESPONSE, AddCharDecisionMakerEventResponse);
    //REGISTER_COMMAND_HANDLER(COMMAND_GET_CHAR_LIGHTING, GetCharLighting);
    //REGISTER_COMMAND_HANDLER(COMMAND_TASK_WARP_CHAR_INTO_CAR_AS_DRIVER, TaskWarpCharIntoCarAsDriver);
    //REGISTER_COMMAND_HANDLER(COMMAND_TASK_WARP_CHAR_INTO_CAR_AS_PASSENGER, TaskWarpCharIntoCarAsPassenger);
    //REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_HOLDING_OBJECT, IsCharHoldingObject);
    //REGISTER_COMMAND_HANDLER(COMMAND_GET_RANDOM_CHAR_IN_SPHERE, GetRandomCharInSphere);
    //REGISTER_COMMAND_HANDLER(COMMAND_HAS_CHAR_BEEN_ARRESTED, HasCharBeenArrested);
    //REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_RESPONDING_TO_EVENT, IsCharRespondingToEvent);
    //REGISTER_COMMAND_HANDLER(COMMAND_TASK_FLEE_CHAR_ANY_MEANS, TaskFleeCharAnyMeans);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_SPECIAL_EVENT, SetCharSpecialEvent);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_IS_TARGET_PRIORITY, SetCharIsTargetPriority);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_RELATIONSHIP, SetCharRelationship);
    //REGISTER_COMMAND_HANDLER(COMMAND_CLEAR_CHAR_RELATIONSHIP, ClearCharRelationship);
    //REGISTER_COMMAND_HANDLER(COMMAND_CLEAR_ALL_CHAR_RELATIONSHIPS, ClearAllCharRelationships);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_TYRES_CAN_BE_BURST, SetCharTyresCanBeBurst);
    //REGISTER_COMMAND_HANDLER(COMMAND_TASK_DRAG_CHAR_FROM_CAR, TaskDragCharFromCar);
    //REGISTER_COMMAND_HANDLER(COMMAND_CLEAR_CHAR_TASKS_IMMEDIATELY, ClearCharTasksImmediately);
    //REGISTER_COMMAND_HANDLER(COMMAND_ATTACH_CHAR_TO_ROPE_FOR_OBJECT, AttachCharToRopeForObject);
    //REGISTER_COMMAND_HANDLER(COMMAND_TASK_GOTO_CHAR_AIMING, TaskGotoCharAiming);
    //REGISTER_COMMAND_HANDLER(COMMAND_TASK_KILL_CHAR_ON_FOOT_TIMED, TaskKillCharOnFootTimed);
    //REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_IN_ANY_SEARCHLIGHT, IsCharInAnySearchlight);
    //REGISTER_COMMAND_HANDLER(COMMAND_TASK_KILL_CHAR_ON_FOOT_PATROL, TaskKillCharOnFootPatrol);
    //REGISTER_COMMAND_HANDLER(COMMAND_TASK_SET_CHAR_DECISION_MAKER, TaskSetCharDecisionMaker);
    //REGISTER_COMMAND_HANDLER(COMMAND_TASK_CHAR_SLIDE_TO_COORD, TaskCharSlideToCoord);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_SHOOT_RATE, SetCharShootRate);
    //REGISTER_COMMAND_HANDLER(COMMAND_COPY_CHAR_DECISION_MAKER, CopyCharDecisionMaker);
    //REGISTER_COMMAND_HANDLER(COMMAND_HAS_CHAR_SPOTTED_CAR, HasCharSpottedCar);
    //REGISTER_COMMAND_HANDLER(COMMAND_TASK_CHAR_SLIDE_TO_COORD_AND_PLAY_ANIM, TaskCharSlideToCoordAndPlayAnim);
    //REGISTER_COMMAND_HANDLER(COMMAND_GET_CHAR_BREATH, GetCharBreath);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_BREATH, SetCharBreath);
    //REGISTER_COMMAND_HANDLER(COMMAND_GET_CHAR_HIGHEST_PRIORITY_EVENT, GetCharHighestPriorityEvent);
    //REGISTER_COMMAND_HANDLER(COMMAND_GET_CAR_CHAR_IS_USING, GetCarCharIsUsing);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_KINDA_STAY_IN_SAME_PLACE, SetCharKindaStayInSamePlace);
    //REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_IN_AIR, IsCharInAir);
    //REGISTER_COMMAND_HANDLER(COMMAND_GET_CHAR_HEIGHT_ABOVE_GROUND, GetCharHeightAboveGround);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_WEAPON_SKILL, SetCharWeaponSkill);
    //REGISTER_COMMAND_HANDLER(COMMAND_GET_RANDOM_CHAR_IN_SPHERE_ONLY_DRUGS_BUYERS, GetRandomCharInSphereOnlyDrugsBuyers);
    //REGISTER_COMMAND_HANDLER(COMMAND_GET_CHAR_MAP_ATTRACTOR_STATUS, GetCharMapAttractorStatus);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_HAS_USED_ENTRY_EXIT, SetCharHasUsedEntryExit);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_MAX_HEALTH, SetCharMaxHealth);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_CAN_BE_KNOCKED_OFF_BIKE, SetCharCanBeKnockedOffBike);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_COORDINATES_DONT_WARP_GANG, SetCharCoordinatesDontWarpGang);
    //REGISTER_COMMAND_HANDLER(COMMAND_PICK_UP_CHAR_WITH_WINCH, PickUpCharWithWinch);
    //REGISTER_COMMAND_HANDLER(COMMAND_GET_RANDOM_CHAR_IN_SPHERE_NO_BRAIN, GetRandomCharInSphereNoBrain);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_BEEN_PHOTOGRAPHED_FLAG, SetCharBeenPhotographedFlag);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_BULLETPROOF_VEST, SetCharBulletproofVest);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_FIRE_DAMAGE_MULTIPLIER, SetCharFireDamageMultiplier);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_USES_UPPERBODY_DAMAGE_ANIMS_ONLY, SetCharUsesUpperbodyDamageAnimsOnly);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_SAY_CONTEXT, SetCharSayContext);
    //REGISTER_COMMAND_HANDLER(COMMAND_GET_NAME_OF_ENTRY_EXIT_CHAR_USED, GetNameOfEntryExitCharUsed);
    //REGISTER_COMMAND_HANDLER(COMMAND_GET_POSITION_OF_ENTRY_EXIT_CHAR_USED, GetPositionOfEntryExitCharUsed);
    //REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_TALKING, IsCharTalking);
    //REGISTER_COMMAND_HANDLER(COMMAND_DISABLE_CHAR_SPEECH, DisableCharSpeech);
    //REGISTER_COMMAND_HANDLER(COMMAND_ENABLE_CHAR_SPEECH, EnableCharSpeech);
    //REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_STUCK_UNDER_CAR, IsCharStuckUnderCar);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_KEEP_TASK, SetCharKeepTask);
    //REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_SWIMMING, IsCharSwimming);
    //REGISTER_COMMAND_HANDLER(COMMAND_GET_CHAR_SWIM_STATE, GetCharSwimState);
    //REGISTER_COMMAND_HANDLER(COMMAND_START_CHAR_FACIAL_TALK, StartCharFacialTalk);
    //REGISTER_COMMAND_HANDLER(COMMAND_STOP_CHAR_FACIAL_TALK, StopCharFacialTalk);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_COORDINATES_NO_OFFSET, SetCharCoordinatesNoOffset);
    //REGISTER_COMMAND_HANDLER(COMMAND_COPY_SHARED_CHAR_DECISION_MAKER, CopySharedCharDecisionMaker);
    //REGISTER_COMMAND_HANDLER(COMMAND_LOAD_SHARED_CHAR_DECISION_MAKER, LoadSharedCharDecisionMaker);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_FORCE_DIE_IN_CAR, SetCharForceDieInCar);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_USES_COLLISION_CLOSEST_OBJECT_OF_TYPE, SetCharUsesCollisionClosestObjectOfType);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_AIR_RESISTANCE_MULTIPLIER, SetCharAirResistanceMultiplier);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_DRUGGED_UP, SetCharDruggedUp);
    //REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_HEAD_MISSING, IsCharHeadMissing);
    //REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_IN_ANY_TRAIN, IsCharInAnyTrain);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_SIGNAL_AFTER_KILL, SetCharSignalAfterKill);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_WANTED_BY_POLICE, SetCharWantedByPolice);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_COORDINATES_DONT_WARP_GANG_NO_OFFSET, SetCharCoordinatesDontWarpGangNoOffset);
    //REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_USING_MAP_ATTRACTOR, IsCharUsingMapAttractor);
    //REGISTER_COMMAND_HANDLER(COMMAND_REMOVE_CHAR_FROM_CAR_MAINTAIN_POSITION, RemoveCharFromCarMaintainPosition);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_SAY_CONTEXT_IMPORTANT, SetCharSayContextImportant);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_SAY_SCRIPT, SetCharSayScript);
    //REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_CAN_CLIMB_OUT_WATER, SetCharCanClimbOutWater);
    //REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_GETTING_IN_TO_A_CAR, IsCharGettingInToACar);
    //REGISTER_COMMAND_HANDLER(COMMAND_GET_CHAR_AREA_VISIBLE, GetCharAreaVisible);
    //REGISTER_COMMAND_HANDLER(COMMAND_HAS_CHAR_SPOTTED_CHAR_IN_FRONT, HasCharSpottedCharInFront);
    //REGISTER_COMMAND_HANDLER(COMMAND_SHUT_CHAR_UP_FOR_SCRIPTED_SPEECH, ShutCharUpForScriptedSpeech);
    //REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_TOUCHING_CHAR, IsCharTouchingChar);
    //REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_ATTACHED_TO_ANY_CAR, IsCharAttachedToAnyCar);
    //REGISTER_COMMAND_HANDLER(COMMAND_STORE_CAR_CHAR_IS_ATTACHED_TO_NO_SAVE, StoreCarCharIsAttachedToNoSave);
    //REGISTER_COMMAND_HANDLER(COMMAND_GET_RANDOM_CHAR_IN_AREA_OFFSET_NO_SAVE, GetRandomCharInAreaOffsetNoSave);
}
