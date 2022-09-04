#pragma once

#include "TheCarGenerators.h"

/*!
* Various utility commands
*/

void SetCarProofs(CVehicle& veh, bool bullet, bool fire, bool explosion, bool collision, bool melee) {
    auto& flags = veh.physicalFlags;
    flags.bBulletProof = bullet;
    flags.bFireProof = fire;
    flags.bExplosionProof = explosion;
    flags.bCollisionProof = collision;
    flags.bMeleeProof = melee;
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

float GetCarSpeed(CVehicle& veh) {
    return veh.m_vecMoveSpeed.Magnitude() * 50.f;
}
REGISTER_COMMAND_HANDLER(COMMAND_GET_CAR_SPEED, GetCarSpeed);

void SetCarDrivingStyle(CVehicle& veh, eCarDrivingStyle style) {
    veh.m_autoPilot.m_nCarDrivingStyle = style;
}
REGISTER_COMMAND_HANDLER(COMMAND_SET_CAR_DRIVING_STYLE, SetCarDrivingStyle);
