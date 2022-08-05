#pragma once

#include "TaskSimpleHoldEntity.h"

class CTaskSimplePickUpEntity : public CTaskSimpleHoldEntity {
public:
    float m_fMovePedUntilAnimProgress; // value can be 0.0 to 1.0. Ped Will stop moving when the current `m_fCurrentTime`
                                       // of `m_pAnimBlendAssociation` is equal or greater than this.
    CVector m_vecPickuposn;

public:
    static constexpr auto Type = TASK_SIMPLE_PICKUP_ENTITY;

    CTaskSimplePickUpEntity(CEntity* entityToHold, CVector* posn, uint8 boneFrameId, uint8 boneFlags, CAnimBlock* animBlock, CAnimBlendHierarchy* animHierarchy, eAnimationFlags animFlags, float fMovePedUntilAnimProgress);
    CTaskSimplePickUpEntity(CEntity* entityToHold, CVector* posn, uint8 boneFrameId, uint8 boneFlags, AnimationId animId, AssocGroupId groupId, float fMovePedUntilAnimProgress);
    ~CTaskSimplePickUpEntity() override = default;

    CTask* Clone() override;
    eTaskType GetTaskType() override;

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CTaskSimplePickUpEntity* Constructor(CEntity* entityToHold, CVector* posn, uint8 boneFrameId, uint8 boneFlags, CAnimBlock* animBlock, CAnimBlendHierarchy* animHierarchy, eAnimationFlags animFlags, float fMovePedUntilAnimProgress);
    CTaskSimplePickUpEntity* Constructor(CEntity* entityToHold, CVector* posn, uint8 boneFrameId, uint8 boneFlags, AnimationId animId, AssocGroupId groupId, float fMovePedUntilAnimProgress);

    CTask* Clone_Reversed();
    eTaskType GetId_Reversed() { return TASK_SIMPLE_PICKUP_ENTITY; };
};

VALIDATE_SIZE(CTaskSimplePickUpEntity, 0x4C);