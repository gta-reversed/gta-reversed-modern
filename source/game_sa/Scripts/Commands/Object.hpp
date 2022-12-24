#pragma once
#include "Object.h"
#include "SetPieces.h"
#include "Fx.h"
#include "PointLights.h"
#include "CommandParser/Parser.hpp"

/*!
* Various object commands
*/

void DrawLight(CVector pos, CVector color) {
    color /= 255.0f;
    CPointLights::AddLight(ePointLightType::PLTYPE_POINTLIGHT, pos, {}, 12.0f, color.x, color.y, color.z, 0, false, nullptr);
}
REGISTER_COMMAND_HANDLER(COMMAND_DRAW_LIGHT, DrawLight);

void AddSetPiece(uint8 type, CVector cornerA, CVector cornerB, CVector spawnCoord1, CVector targetCoord1,
    CVector spawnCoord2, CVector targetCoord2) {
    CSetPieces::AddOne(type, cornerA, cornerB, spawnCoord1, targetCoord1, spawnCoord2, targetCoord2);
}
REGISTER_COMMAND_HANDLER(COMMAND_ADD_SET_PIECE, AddSetPiece);

void AddBigGunFlash(CVector origin, CVector target) {
    CPointLights::AddLight(ePointLightType::PLTYPE_POINTLIGHT, origin, {}, 5.0f, 1.0f, 0.8f, 0.0f, 0, false, nullptr);
    g_fx.TriggerGunshot(nullptr, origin, (target - origin).Magnitude(), true);
}
REGISTER_COMMAND_HANDLER(COMMAND_ADD_BIG_GUN_FLASH, AddBigGunFlash);

void EnableDisabledAttractorOnObject(CObject& object, bool enabled) {
    object.objectFlags.b0x1000000 = enabled; // todo: rename obj->objectFlags.b0x1000000
}
REGISTER_COMMAND_HANDLER(COMMAND_ENABLE_DISABLED_ATTRACTORS_ON_OBJECT, EnableDisabledAttractorOnObject);
