#pragma once
#include <cassert>

#include "PlayerInfo.h"
#include "World.h"
#include "CarGenerator.h"
#include "TheCarGenerators.h"
#include "CommandParser/Parser.hpp"
using namespace notsa::script;

/*!
* Various vehicle commands
*/

void ClearHeliOrientation(CHeli& heli) {
    heli.ClearHeliOrientation();
}
REGISTER_COMMAND_HANDLER(COMMAND_CLEAR_HELI_ORIENTATION, ClearHeliOrientation);

void RemoveRCBuggy() {
    FindPlayerInfo().BlowUpRCBuggy(false);
}
REGISTER_COMMAND_HANDLER(COMMAND_REMOVE_RC_BUGGY, RemoveRCBuggy);

void SetCarProofs(CVehicle& veh, bool bullet, bool fire, bool explosion, bool collision, bool melee) {
    auto& flags           = veh.physicalFlags;
    flags.bBulletProof    = bullet;
    flags.bFireProof      = fire;
    flags.bExplosionProof = explosion;
    flags.bCollisionProof = collision;
    flags.bMeleeProof     = melee;
}
REGISTER_COMMAND_HANDLER(COMMAND_SET_CAR_PROOFS, SetCarProofs);

void SwitchCarGenerator(int32 generatorId, int32 count) {
    const auto generator = CTheCarGenerators::Get(generatorId);
    if (count) {
        generator->SwitchOn();
        if (count <= 100) {
            generator->m_nGenerateCount = count;
        }
    } else {
        generator->SwitchOff();
    }
}
REGISTER_COMMAND_HANDLER(COMMAND_SWITCH_CAR_GENERATOR, SwitchCarGenerator);

void SetHasBeenOwnedForCarGenerator(int32 generatorId, bool alreadyOwned) {
    CTheCarGenerators::Get(generatorId)->bPlayerHasAlreadyOwnedCar = alreadyOwned;
}
REGISTER_COMMAND_HANDLER(COMMAND_SET_HAS_BEEN_OWNED_FOR_CAR_GENERATOR, SetHasBeenOwnedForCarGenerator);

float GetCarSpeed(CVehicle& veh) {
    return veh.m_vecMoveSpeed.Magnitude() * 50.f;
}
REGISTER_COMMAND_HANDLER(COMMAND_GET_CAR_SPEED, GetCarSpeed);

void SetCarDrivingStyle(CVehicle& veh, eCarDrivingStyle style) {
    veh.m_autoPilot.m_nCarDrivingStyle = style;
}
REGISTER_COMMAND_HANDLER(COMMAND_SET_CAR_DRIVING_STYLE, SetCarDrivingStyle);

bool IsFirstCarColor(CVehicle& veh, int32 color) {
    return veh.m_nPrimaryColor == color;
}
REGISTER_COMMAND_HANDLER(COMMAND_IS_FIRST_CAR_COLOUR, IsFirstCarColor);

bool IsSecondCarColor(CVehicle& veh, int32 color) {
    return veh.m_nSecondaryColor == color;
}
REGISTER_COMMAND_HANDLER(COMMAND_IS_SECOND_CAR_COLOUR, IsSecondCarColor);
MultiRet<uint8, uint8> GetExtraCarColors(CVehicle& veh) {
    return {veh.m_nTertiaryColor, veh.m_nQuaternaryColor};
}
REGISTER_COMMAND_HANDLER(COMMAND_GET_EXTRA_CAR_COLOURS, GetExtraCarColors);

void FixCar(CVehicle& vehicle) {
REGISTER_COMMAND_HANDLER(COMMAND_IMPROVE_CAR_BY_CHEATING, ImproveCarByCheating);

void PopCarBootUsingPhysics(CAutomobile& automobile) {
    automobile.PopBootUsingPhysics();
}
REGISTER_COMMAND_HANDLER(COMMAND_POP_CAR_BOOT_USING_PHYSICS, PopCarBootUsingPhysics);

void SkipToNextAllowedStation(CTrain& train) {
    CTrain::SkipToNextAllowedStation(&train);
}
REGISTER_COMMAND_HANDLER(COMMAND_SKIP_TO_NEXT_ALLOWED_STATION, SkipToNextAllowedStation);


void SetRailTrackResistanceMult(float value) {
    CVehicle::ms_fRailTrackResistance = CVehicle::ms_fRailTrackResistanceDefault * (value > 0.0f ? value : 1.0f);
}
REGISTER_COMMAND_HANDLER(COMMAND_SET_RAILTRACK_RESISTANCE_MULT, SetRailTrackResistanceMult);

void DisableHeliAudio(CVehicle& vehicle, bool enable) {
    if (enable) {
        vehicle.m_vehicleAudio.EnableHelicoptor();
    } else {
        vehicle.m_vehicleAudio.DisableHelicoptor();
    }
}
REGISTER_COMMAND_HANDLER(COMMAND_DISABLE_HELI_AUDIO, DisableHeliAudio);
