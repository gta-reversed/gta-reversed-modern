#pragma once

#include "CTaskSimpleHoldEntity.h"

class CTaskSimplePickUpEntity : public CTaskSimpleHoldEntity {
public:
    float m_fMovePedUntilAnimProgress; // value can be 0.0 to 1.0. Ped Will stop moving when the current `m_fCurrentTime`
                                       // of `m_pAnimBlendAssociation` is equal or greater than this.
    CVector m_vecPickupPosition;

public:
    CTaskSimplePickUpEntity(CEntity* pEntityToHold, CVector* pPosition, char boneFrameId, uint8 boneFlags, CAnimBlock* pAnimBlock, CAnimBlendHierarchy* pAnimHierarchy, int animFlags, float fMovePedUntilAnimProgress);
    CTaskSimplePickUpEntity(CEntity* pEntityToHold, CVector* pPosition, char boneFrameId, uint8 boneFlags, AnimationId animId, AssocGroupId groupId, float fMovePedUntilAnimProgress);
    ~CTaskSimplePickUpEntity();

    CTask* Clone() override;
    eTaskType GetId() override;

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CTaskSimplePickUpEntity* Constructor(CEntity* pEntityToHold, CVector* pPosition, char boneFrameId, uint8 boneFlags, CAnimBlock* pAnimBlock, CAnimBlendHierarchy* pAnimHierarchy, int animFlags, float fMovePedUntilAnimProgress);
    CTaskSimplePickUpEntity* Constructor(CEntity* pEntityToHold, CVector* pPosition, char boneFrameId, uint8 boneFlags, AnimationId animId, AssocGroupId groupId, float fMovePedUntilAnimProgress);

    CTask* Clone_Reversed();
    eTaskType GetId_Reversed() { return TASK_SIMPLE_PICKUP_ENTITY; };
};

VALIDATE_SIZE(CTaskSimplePickUpEntity, 0x4C);