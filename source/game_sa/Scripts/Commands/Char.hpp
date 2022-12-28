#pragma once

#include "World.h"
#include <EntryExitManager.h>
#include <TimeCycle.h>
#include <ePedBones.h>

#include "CommandParser/Parser.hpp"

/*!
* Various utility commands
*/

auto IsCharInArea2D(CRunningScript& S, CPed& ped, CVector2D a, CVector2D b, bool drawSphere) -> notsa::script::CompareFlagUpdate {
    const auto Check = [&](const auto& e) { return e.IsWithinArea(a.x, a.y, b.x, b.y); };

    if (drawSphere) {
        CTheScripts::HighlightImportantArea(reinterpret_cast<int32>(&S) + reinterpret_cast<int32>(S.m_IP), a.x, a.y, b.x, b.y, -100.f);
    }

    return { ped.IsInVehicle() ? Check(*ped.m_pVehicle) : Check(ped) };
}
REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_IN_AREA_2D, IsCharInArea2D);

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

auto SetCharRotation(CPed& ped) {

}
REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_ROTATION, SetCharRotation);

auto SetCharAllowedToDuck(CPed& ped, CVector rotdeg) {
    CWorld::Remove(&ped);
    ped.SetOrientation(rotdeg * RWDEG2RAD(1.f)); // degrees => radians
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
    }
    return ped.GetPosition();
}
REGISTER_COMMAND_HANDLER(COMMAND_GET_DEAD_CHAR_COORDINATES, GetDeadCharCoordinates);
