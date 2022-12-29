#pragma once

#include "World.h"
#include <EntryExitManager.h>
#include <TimeCycle.h>
#include <ePedBones.h>

#include <Commands/Utility.hpp>

#include "CommandParser/Parser.hpp"
#include <TaskSimpleCarSetPedInAsDriver.h>

/*!
* Various character (ped) commands
*/

void SetCharProofs(CPed& ped, bool bullet, bool fire, bool explosion, bool collision, bool melee) {
    auto& flags = ped.physicalFlags;
    flags.bBulletProof = bullet;
    flags.bFireProof = fire;
    flags.bExplosionProof = explosion;
    flags.bCollisionProof = collision;
    flags.bMeleeProof = melee;
}
REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_PROOFS, SetCharProofs);

auto SetCharVelocity(CPed& ped, CVector velocity) {
    ped.SetVelocity(velocity / 50.f);
}
REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_VELOCITY, SetCharVelocity);

auto GetCharVelocity(CPed& ped) {
    return ped.GetMoveSpeed();
}
REGISTER_COMMAND_HANDLER(COMMAND_GET_CHAR_VELOCITY, GetCharVelocity);

auto SetCharRotation(CPed& ped, CVector angles) {
    ped.SetOrientation(angles * DegreesToRadians(1.0f)); // make euler angles from degrees
    CWorld::Add(&ped);
}
REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_ROTATION, SetCharRotation);

auto SetCharAllowedToDuck(CPed& ped, CVector rotdeg) {
    CWorld::Remove(&ped);
    ped.SetOrientation(rotdeg * DegreesToRadians(1.f)); // degrees => radians
    CWorld::Add(&ped);
}
REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_ALLOWED_TO_DUCK, SetCharAllowedToDuck);

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
REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_AREA_VISIBLE, SetCharAreaVisible);

auto SetCharDropsWeaponsWhenDead(CPed& ped, bool dropsWepsWhenDead) {
    ped.bDoesntDropWeaponsWhenDead = !dropsWepsWhenDead;
}
REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_DROPS_WEAPONS_WHEN_DEAD, SetCharDropsWeaponsWhenDead);

auto SetCharNeverLeavesGroup(CPed& ped, bool bNeverLeavesGroup) {
    ped.bNeverLeavesGroup = bNeverLeavesGroup;
}
REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_NEVER_LEAVES_GROUP, SetCharNeverLeavesGroup);

auto AttachFxSystemToCharBone(tScriptEffectSystem& fx, CPed& ped, ePedBones bone) {
    fx.m_pFxSystem->AttachToBone(&ped, bone);
}
REGISTER_COMMAND_HANDLER(COMMAND_ATTACH_FX_SYSTEM_TO_CHAR_BONE, AttachFxSystemToCharBone);

auto GetDeadCharCoordinates(CPed& ped) {
    if (ped.IsInVehicle()) {
        return ped.m_pVehicle->GetPosition();
    } else {
        return ped.GetBonePosition(BONE_PELVIS);
    }
}
REGISTER_COMMAND_HANDLER(COMMAND_GET_DEAD_CHAR_COORDINATES, GetDeadCharCoordinates);

auto GetCharCoordinates(CPed& ped) {
    if (ped.IsInVehicle()) {
        return ped.m_pVehicle->GetPosition();
    } else {
        return ped.GetPosition();
    }
}
REGISTER_COMMAND_HANDLER(COMMAND_GET_CHAR_COORDINATES, GetCharCoordinates);

auto SetCharCoordinates(CPed& ped, CVector coords) {
    CRunningScript::SetCharCoordinates(&ped, coords.x, coords.y, coords.z, true, true);
}
REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_COORDINATES, SetCharCoordinates);

auto IsCharStillAlive(CPed& ped) {
    return ::notsa::script::detail::NotImplemented(); // I can't find the code
}
REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_STILL_ALIVE, IsCharStillAlive);

auto IsCharInArea2D(CRunningScript& S, CPed& ped, CVector2D a, CVector2D b, bool highlightArea) {
    if (highlightArea) {
        CTheScripts::HighlightImportantArea(reinterpret_cast<int32>(&S) + reinterpret_cast<int32>(S.m_IP), a.x, a.y, b.x, b.y, -100.f);
    }

    const auto Check = [&](const auto& e) { return e.IsWithinArea(a.x, a.y, b.x, b.y); };
    return ped.IsInVehicle()
        ? Check(*ped.m_pVehicle)
        : Check(ped);
}
REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_IN_AREA_2D, IsCharInArea2D);

auto IsCharInArea3D(CRunningScript& S, CPed& ped, CVector a, CVector b, bool highlightArea) {
    if (highlightArea) {
        CTheScripts::HighlightImportantArea(reinterpret_cast<int32>(&S) + reinterpret_cast<int32>(S.m_IP), a.x, a.y, b.x, b.y, (a.z + b.z) / 2.f);
    }

    const auto Check = [&](const auto& e) { return e.IsWithinArea(a.x, a.y, a.z, b.x, b.y, b.z); };
    return ped.IsInVehicle()
        ? Check(*ped.m_pVehicle)
        : Check(ped);
}
REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_IN_AREA_3D, IsCharInArea3D);

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
REGISTER_COMMAND_HANDLER(COMMAND_STORE_CAR_CHAR_IS_IN, StoreCarCharIsIn);

auto IsCharInCar(CPed& ped, CVehicle& veh) {
    return ped.IsInVehicle() && ped.m_pVehicle == &veh;
}
REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_IN_CAR, IsCharInCar);

auto IsCharInModel(CPed& ped, eModelID model) {
    return ped.IsInVehicle() && ped.m_pVehicle->m_nModelIndex == model;
}
REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_IN_MODEL, IsCharInModel);

auto IsCharInAnyCar(CPed& ped) {
    return ped.IsInVehicle();
}
REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_IN_ANY_CAR, IsCharInAnyCar);

auto LocatePlayerAnyMeansChar2D() {
    return ::notsa::script::detail::NotImplemented(); // Can't find code
}
REGISTER_COMMAND_HANDLER(COMMAND_LOCATE_PLAYER_ANY_MEANS_CHAR_2D, LocatePlayerAnyMeansChar2D);

auto LocatePlayerOnFootChar2D(CPed& ped) {
    return ::notsa::script::detail::NotImplemented(); // Can't find code
}
REGISTER_COMMAND_HANDLER(COMMAND_LOCATE_PLAYER_ON_FOOT_CHAR_2D, LocatePlayerOnFootChar2D);

auto LocatePlayerInCarChar2D(CPed& ped) {
    return ::notsa::script::detail::NotImplemented(); // Can't find code
}
REGISTER_COMMAND_HANDLER(COMMAND_LOCATE_PLAYER_IN_CAR_CHAR_2D, LocatePlayerInCarChar2D);

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
        HighlightImportantArea(S, bb.m_vecMin, bb.m_vecMax);
    }
    if (!DoLocateCharChecks(ped, mustBeOnFoot, highlightArea, mustBeStopped)) {
        return false;
    }
    return bb.IsPointInside(GetCharCoordinates(ped));
}

bool LocateChar2D(CRunningScript& S, CPed& ped, CVector2D pos, CVector2D radius, bool highlightArea, bool mustBeInCar, bool mustBeOnFoot, bool mustBeStopped) {
    const CRect rect{ pos - radius, pos + radius };
    if (highlightArea) { // Highlight area every time
        HighlightImportantArea(S, rect.GetTopLeft(), rect.GetBottomRight());
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
REGISTER_COMMAND_HANDLER(COMMAND_LOCATE_CHAR_ANY_MEANS_2D, LocateCharAnyMeans2D);

auto LocateCharOnFoot2D(CRunningScript& S, CPed& ped, CVector2D pos, CVector2D radius, bool highlightArea) {
    return LocateChar2D(S, ped, pos, radius, highlightArea, false, true, false);
}
REGISTER_COMMAND_HANDLER(COMMAND_LOCATE_CHAR_ON_FOOT_2D, LocateCharOnFoot2D);

auto LocateCharInCar2D(CRunningScript& S, CPed& ped, CVector2D pos, CVector2D radius, bool highlightArea) {
    return LocateChar2D(S, ped, pos, radius, highlightArea, true, false, false);
}
REGISTER_COMMAND_HANDLER(COMMAND_LOCATE_CHAR_IN_CAR_2D, LocateCharInCar2D);

auto LocateStoppedCharAnyMeans2D(CRunningScript& S, CPed& ped, CVector2D pos, CVector2D radius, bool highlightArea) {
    return LocateChar2D(S, ped, pos, radius, highlightArea, false, false, true);
}
REGISTER_COMMAND_HANDLER(COMMAND_LOCATE_STOPPED_CHAR_ANY_MEANS_2D, LocateStoppedCharAnyMeans2D);

auto LocateStoppedCharOnFoot2D(CRunningScript& S, CPed& ped, CVector2D pos, CVector2D radius, bool highlightArea) {
    return LocateChar2D(S, ped, pos, radius, highlightArea, false, true, true);
}
REGISTER_COMMAND_HANDLER(COMMAND_LOCATE_STOPPED_CHAR_ON_FOOT_2D, LocateStoppedCharOnFoot2D);

auto LocateStoppedCharInCar2D(CRunningScript& S, CPed& ped, CVector2D pos, CVector2D radius, bool highlightArea) {
    return LocateChar2D(S, ped, pos, radius, highlightArea, true, false, true);
}
REGISTER_COMMAND_HANDLER(COMMAND_LOCATE_STOPPED_CHAR_IN_CAR_2D, LocateStoppedCharInCar2D);

auto LocateCharAnyMeans3D(CRunningScript& S, CPed& ped, CVector pos, CVector radius, bool highlightArea) {
    return LocateChar3D(S, ped, pos, radius, highlightArea, false, false, false);
}
REGISTER_COMMAND_HANDLER(COMMAND_LOCATE_CHAR_ANY_MEANS_3D, LocateCharAnyMeans3D);

auto LocateCharOnFoot3D(CRunningScript& S, CPed& ped, CVector pos, CVector radius, bool highlightArea) {
    return LocateChar3D(S, ped, pos, radius, highlightArea, false, true, false);
}
REGISTER_COMMAND_HANDLER(COMMAND_LOCATE_CHAR_ON_FOOT_3D, LocateCharOnFoot3D);

auto LocateCharInCar3D(CRunningScript& S, CPed& ped, CVector pos, CVector radius, bool highlightArea) {
    return LocateChar3D(S, ped, pos, radius, highlightArea, true, false, false);
}
REGISTER_COMMAND_HANDLER(COMMAND_LOCATE_CHAR_IN_CAR_3D, LocateCharInCar3D);

auto LocateStoppedCharAnyMeans3D(CRunningScript& S, CPed& ped, CVector pos, CVector radius, bool highlightArea) {
    return LocateChar3D(S, ped, pos, radius, highlightArea, false, false, true);
}
REGISTER_COMMAND_HANDLER(COMMAND_LOCATE_STOPPED_CHAR_ANY_MEANS_3D, LocateStoppedCharAnyMeans3D);

auto LocateStoppedCharOnFoot3D(CRunningScript& S, CPed& ped, CVector pos, CVector radius, bool highlightArea) {
    return LocateChar3D(S, ped, pos, radius, highlightArea, false, true, true);
}
REGISTER_COMMAND_HANDLER(COMMAND_LOCATE_STOPPED_CHAR_ON_FOOT_3D, LocateStoppedCharOnFoot3D);

auto LocateStoppedCharInCar3D(CRunningScript& S, CPed& ped, CVector pos, CVector radius, bool highlightArea) {
    return LocateChar3D(S, ped, pos, radius, highlightArea, true, false, true);
}
REGISTER_COMMAND_HANDLER(COMMAND_LOCATE_STOPPED_CHAR_IN_CAR_3D, LocateStoppedCharInCar3D);

auto LocatePlayerAnyMeansChar3D(CRunningScript& S, CPed& ped, CVector pos, CVector radius, bool highlightArea) {
    return ::notsa::script::detail::NotImplemented(); // Can't find code
}
REGISTER_COMMAND_HANDLER(COMMAND_LOCATE_PLAYER_ANY_MEANS_CHAR_3D, LocatePlayerAnyMeansChar3D);

auto LocatePlayerOnFootChar3D(CPed& ped, CVector pos, CVector radius, bool highlightArea) {
    return ::notsa::script::detail::NotImplemented(); // Can't find code
}
REGISTER_COMMAND_HANDLER(COMMAND_LOCATE_PLAYER_ON_FOOT_CHAR_3D, LocatePlayerOnFootChar3D);

auto LocatePlayerInCarChar3D(CRunningScript& S, CPed& ped, CVector pos, CVector radius, bool highlightArea) {
    return ::notsa::script::detail::NotImplemented(); // Can't find code
}
REGISTER_COMMAND_HANDLER(COMMAND_LOCATE_PLAYER_IN_CAR_CHAR_3D, LocatePlayerInCarChar3D);

bool LocateCharChar2D(CRunningScript& S, CPed& ped1, CPed& ped2, CVector2D radius, bool highlightArea, bool mustBeInCar, bool mustBeOnFoot) {
    return LocateChar2D(S, ped1, ped2.GetPosition2D(), radius, highlightArea, mustBeInCar, mustBeOnFoot, false);
}

auto LocateCharAnyMeansChar2D(CRunningScript& S, CPed& ped1, CPed& ped2, CVector2D radius, bool highlightArea) {
    return LocateCharChar2D(S, ped1, ped2, radius, highlightArea, false, false);
}
REGISTER_COMMAND_HANDLER(COMMAND_LOCATE_CHAR_ANY_MEANS_CHAR_2D, LocateCharAnyMeansChar2D);

auto LocateCharOnFootChar2D(CRunningScript& S, CPed& ped1, CPed& ped2, CVector2D radius, bool highlightArea) {
    return LocateCharChar2D(S, ped1, ped2, radius, highlightArea, false, true);
}
REGISTER_COMMAND_HANDLER(COMMAND_LOCATE_CHAR_ON_FOOT_CHAR_2D, LocateCharOnFootChar2D);

auto LocateCharInCarChar2D(CRunningScript& S, CPed& ped1, CPed& ped2, CVector2D radius, bool highlightArea) {
    return LocateCharChar2D(S, ped1, ped2, radius, highlightArea, true, false);
}
REGISTER_COMMAND_HANDLER(COMMAND_LOCATE_CHAR_IN_CAR_CHAR_2D, LocateCharInCarChar2D);

bool LocateCharChar3D(CRunningScript& S, CPed& ped1, CPed& ped2, CVector radius, bool highlightArea, bool mustBeInCar, bool mustBeOnFoot) {
    return LocateChar3D(S, ped1, ped2.GetPosition(), radius, highlightArea, mustBeInCar, mustBeOnFoot, false);
}

auto LocateCharAnyMeansChar3D(CRunningScript& S, CPed& ped1, CPed& ped2, CVector radius, bool highlightArea) {
    return LocateCharChar3D(S, ped1, ped2, radius, highlightArea, false, false);
}
REGISTER_COMMAND_HANDLER(COMMAND_LOCATE_CHAR_ANY_MEANS_CHAR_3D, LocateCharAnyMeansChar3D);

auto LocateCharOnFootChar3D(CRunningScript& S, CPed& ped1, CPed& ped2, CVector radius, bool highlightArea) {
    return LocateCharChar3D(S, ped1, ped2, radius, highlightArea, false, true);
}
REGISTER_COMMAND_HANDLER(COMMAND_LOCATE_CHAR_ON_FOOT_CHAR_3D, LocateCharOnFootChar3D);

auto LocateCharInCarChar3D(CRunningScript& S, CPed& ped1, CPed& ped2, CVector radius, bool highlightArea) {
    return LocateCharChar3D(S, ped1, ped2, radius, highlightArea, true, false);
}
REGISTER_COMMAND_HANDLER(COMMAND_LOCATE_CHAR_IN_CAR_CHAR_3D, LocateCharInCarChar3D);

auto IsCharDead(CPed* ped) {
    return !ped || ped->IsStateDeadForScript();
}
REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_DEAD, IsCharDead);

auto SetCharThreatSearch(CPed& ped) {

}
REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_THREAT_SEARCH, SetCharThreatSearch);

auto SetCharThreatReaction(CPed& ped) {
    return ::notsa::script::detail::NotImplemented();
}
REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_THREAT_REACTION, SetCharThreatReaction);

auto SetCharObjNoObj(CPed& ped) {
    return ::notsa::script::detail::NotImplemented();
}
REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_OBJ_NO_OBJ, SetCharObjNoObj);

auto OrderCharToDriveCar(CPed& ped) {
    return ::notsa::script::detail::NotImplemented();
}
REGISTER_COMMAND_HANDLER(COMMAND_ORDER_CHAR_TO_DRIVE_CAR, OrderCharToDriveCar);

auto HasCharSpottedPlayer(CPed& ped) {
    return ::notsa::script::detail::NotImplemented();
}
REGISTER_COMMAND_HANDLER(COMMAND_HAS_CHAR_SPOTTED_PLAYER, HasCharSpottedPlayer);

auto OrderCharToBackdoor(CPed& ped) {
    return ::notsa::script::detail::NotImplemented();
}
REGISTER_COMMAND_HANDLER(COMMAND_ORDER_CHAR_TO_BACKDOOR, OrderCharToBackdoor);

auto AddCharToGang(CPed& ped) {
    return ::notsa::script::detail::NotImplemented();
}
REGISTER_COMMAND_HANDLER(COMMAND_ADD_CHAR_TO_GANG, AddCharToGang);

auto IsCharObjectivePassed(CPed& ped) {
    return ::notsa::script::detail::NotImplemented();
}
REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_OBJECTIVE_PASSED, IsCharObjectivePassed);

auto SetCharDriveAggression(CPed& ped) {
    return ::notsa::script::detail::NotImplemented();
}
REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_DRIVE_AGGRESSION, SetCharDriveAggression);

auto SetCharMaxDrivespeed(CPed& ped) {
    return ::notsa::script::detail::NotImplemented();
}
REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_MAX_DRIVESPEED, SetCharMaxDrivespeed);

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
REGISTER_COMMAND_HANDLER(COMMAND_CREATE_CHAR_INSIDE_CAR, CreateCharInsideCar);

//auto MakeCharDoNothing(CPed& ped) {
//
//}
//REGISTER_COMMAND_HANDLER(COMMAND_MAKE_CHAR_DO_NOTHING, MakeCharDoNothing);

//auto SetCharInvincible(CPed& ped) {
//
//}
//REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_INVINCIBLE, SetCharInvincible);
