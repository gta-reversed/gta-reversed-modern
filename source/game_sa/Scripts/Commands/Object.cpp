#include <StdInc.h>

#include "./Commands.hpp"
#include <CommandParser/Parser.hpp>

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

void AddBigGunFlash(CVector origin, CVector target) {
    CPointLights::AddLight(ePointLightType::PLTYPE_POINTLIGHT, origin, {}, 5.0f, 1.0f, 0.8f, 0.0f, 0, false, nullptr);
    g_fx.TriggerGunshot(nullptr, origin, (target - origin).Normalized(), true);
}

void EnableDisabledAttractorOnObject(CObject& object, bool enabled) {
    object.objectFlags.bEnableDisabledAttractors = enabled; // todo: rename obj->objectFlags.b0x1000000
}

//
// Animation
//

void SetObjectAnimSpeed(CObject& obj, const char* animName, float speed) {
    if (const auto anim = RpAnimBlendClumpGetAssociation(obj.m_pRwClump, animName)) {
        anim->m_fSpeed = speed;
    }
}

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

auto GetObjectAnimCurrentTime(CObject& obj, const char* animName) {
    if (const auto anim = RpAnimBlendClumpGetAssociation(obj.m_pRwClump, animName)) {
        return anim->m_fCurrentTime / anim->m_pHierarchy->m_fTotalTime;
    }
    return 0.f;
}

auto SetObjectAnimCurrentTime(CObject& obj, const char* animName, float progress) {
    if (const auto anim = RpAnimBlendClumpGetAssociation(obj.m_pRwClump, animName)) {
        anim->SetCurrentTime(anim->m_fSpeed * progress);
    }
}



void notsa::script::commands::object::RegisterHandlers() {
    REGISTER_COMMAND_HANDLER(COMMAND_ADD_SET_PIECE, CSetPieces::AddOne);
    REGISTER_COMMAND_HANDLER(COMMAND_DRAW_LIGHT, DrawLight);
    REGISTER_COMMAND_HANDLER(COMMAND_ADD_BIG_GUN_FLASH, AddBigGunFlash);
    REGISTER_COMMAND_HANDLER(COMMAND_ENABLE_DISABLED_ATTRACTORS_ON_OBJECT, EnableDisabledAttractorOnObject);
    REGISTER_COMMAND_HANDLER(COMMAND_SET_OBJECT_ANIM_SPEED, SetObjectAnimSpeed);
    REGISTER_COMMAND_HANDLER(COMMAND_IS_OBJECT_PLAYING_ANIM, IsObjectPlayingAnim);
    REGISTER_COMMAND_HANDLER(COMMAND_GET_OBJECT_ANIM_CURRENT_TIME, GetObjectAnimCurrentTime);
    REGISTER_COMMAND_HANDLER(COMMAND_SET_OBJECT_ANIM_CURRENT_TIME, SetObjectAnimCurrentTime);
}
