#pragma once
#include "Object.h"
#include "PointLights.h"
#include "CommandParser/Parser.hpp"


/*!
* Various object commands
*/

float DrawLight(CVector pos, CVector color) {
    color /= 255.0f;
    CPointLights::AddLight(ePointLightType::PLTYPE_POINTLIGHT, pos, {}, 12.0f, color.x, color.y, color.z, 0, false, nullptr);
}
REGISTER_COMMAND_HANDLER(COMMAND_DRAW_LIGHT, DrawLight);

void EnableDisabledAttractorOnObject(CObject& object, bool enabled) {
    object.objectFlags.b0x1000000 = enabled; // todo: rename obj->objectFlags.b0x1000000
}
REGISTER_COMMAND_HANDLER(COMMAND_ENABLE_DISABLED_ATTRACTORS_ON_OBJECT, EnableDisabledAttractorOnObject);
