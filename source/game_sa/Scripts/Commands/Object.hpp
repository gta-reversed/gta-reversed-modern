#pragma once

#include "Object.h"
#include "SetPieces.h"
#include "Fx.h"
#include "PointLights.h"
#include "CommandParser/Parser.hpp"

/*!
* Various object commands
*/
REGISTER_COMMAND_HANDLER(COMMAND_ADD_SET_PIECE, CSetPieces::AddOne);

void DrawLight(CVector pos, CVector color) {
    color /= 255.0f;
    CPointLights::AddLight(ePointLightType::PLTYPE_POINTLIGHT, pos, {}, 12.0f, color.x, color.y, color.z, 0, false, nullptr);
}
REGISTER_COMMAND_HANDLER(COMMAND_DRAW_LIGHT, DrawLight);

void AddBigGunFlash(CVector origin, CVector target) {
    CPointLights::AddLight(ePointLightType::PLTYPE_POINTLIGHT, origin, {}, 5.0f, 1.0f, 0.8f, 0.0f, 0, false, nullptr);
    g_fx.TriggerGunshot(nullptr, origin, (target - origin).Normalized(), true);
}
REGISTER_COMMAND_HANDLER(COMMAND_ADD_BIG_GUN_FLASH, AddBigGunFlash);

void EnableDisabledAttractorOnObject(CObject& object, bool enabled) {
    object.objectFlags.bEnableDisabledAttractors = enabled; // todo: rename obj->objectFlags.b0x1000000
}
REGISTER_COMMAND_HANDLER(COMMAND_ENABLE_DISABLED_ATTRACTORS_ON_OBJECT, EnableDisabledAttractorOnObject);

//
// Animation
//

void SetObjectAnimSpeed(CObject& obj, const char* animName, float speed) {
    if (const auto anim = RpAnimBlendClumpGetAssociation(obj.m_pRwClump, animName)) {
        anim->m_fSpeed = speed;
    }
}
REGISTER_COMMAND_HANDLER(COMMAND_SET_OBJECT_ANIM_SPEED, SetObjectAnimSpeed);

bool IsObjectPlayingAnim(CObject& obj, const char* animName) {
    if (!obj.m_pRwClump) {
        return false;
    }
    if (RwObjectGetType(obj.m_pRwClump) != rpCLUMP) {
        return false;
    }
    if (!RpAnimBlendClumpIsInitialized(obj.m_pRwClump)) {
        return false;
    }
    return RpAnimBlendClumpGetAssociation(obj.m_pRwClump, animName) != nullptr; 
}
REGISTER_COMMAND_HANDLER(COMMAND_IS_OBJECT_PLAYING_ANIM, IsObjectPlayingAnim);

auto GetObjectAnimCurrentTime(CObject& obj, const char* animName) {
    if (const auto anim = RpAnimBlendClumpGetAssociation(obj.m_pRwClump, animName)) {
        return anim->m_fCurrentTime / anim->m_pHierarchy->m_fTotalTime;
    }
    return 0.f;
}
REGISTER_COMMAND_HANDLER(COMMAND_GET_OBJECT_ANIM_CURRENT_TIME, GetObjectAnimCurrentTime);

auto SetObjectAnimCurrentTime(CObject& obj, const char* animName, float progress) {
    if (const auto anim = RpAnimBlendClumpGetAssociation(obj.m_pRwClump, animName)) {
        anim->SetCurrentTime(anim->m_fSpeed * progress);
    }
}
REGISTER_COMMAND_HANDLER(COMMAND_SET_OBJECT_ANIM_CURRENT_TIME, SetObjectAnimCurrentTime);


