#pragma once

#include "TaskSimpleHoldEntity.h"

class CTaskSimplePutDownEntity : public CTaskSimpleHoldEntity {
public:
    float m_fPutDownHeightZ;

public:
    CTaskSimplePutDownEntity();
    CTaskSimplePutDownEntity(CEntity* entityToHold, CVector* posn, uint8 boneFrameId, uint8 boneFlags, AnimationId animId, AssocGroupId groupId, bool bDisAllowDroppingOnAnimEnd, float fPutDownHeightZ);
    CTaskSimplePutDownEntity(CEntity* entityToHold, CVector* posn, uint8 boneFrameId, uint8 boneFlags, const char* animName, const char* animBlockName, eAnimationFlags animFlags, float fPutDownHeightZ);
    CTaskSimplePutDownEntity(CEntity* entityToHold, CVector* posn, uint8 boneFrameId, uint8 boneFlags, CAnimBlock* pAnimBlock, CAnimBlendHierarchy* animHierarchy, eAnimationFlags animFlags, float fPutDownHeightZ);
    ~CTaskSimplePutDownEntity() override = default;

public:
    static constexpr auto Type = TASK_SIMPLE_PUTDOWN_ENTITY;

    CTask*    Clone() override;
    eTaskType GetTaskType() override;

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CTaskSimplePutDownEntity* Constructor();

    CTask*    Clone_Reversed();
    eTaskType GetId_Reversed() { return TASK_SIMPLE_PUTDOWN_ENTITY; };
};

VALIDATE_SIZE(CTaskSimplePutDownEntity, 0x40);