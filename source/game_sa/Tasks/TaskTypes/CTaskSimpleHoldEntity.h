#pragma once

#include "CTaskSimple.h"

enum eHoldEntityBoneFlags {
    HOLD_ENTITY_FLAG_1 = 0x1,
    HOLD_ENTITY_UPDATE_TRANSLATION_ONLY = 0x10
};

class CEntity;
class CAnimBlock;
class CAnimBlendHierarchy;
class CAnimBlendAssociation;

class CTaskSimpleHoldEntity : public CTaskSimple {
public:
    CEntity*               m_pEntityToHold;
    CVector                m_vecPosition;
    uint8                  m_nBoneFrameId; // see ePedNode
    uint8                  m_bBoneFlags;
    bool                   field_1A[2];
    float                  m_fRotation;
    AnimationId            m_nAnimId;
    AssocGroupId           m_nAnimGroupId;
    int32                  m_animFlags; // see eAnimationFlags
    CAnimBlock*            m_pAnimBlock;
    CAnimBlendHierarchy*   m_pAnimBlendHierarchy; // If set, m_animID and m_groupID are ignored in StartAnim method
    bool                   m_bEntityDropped;
    bool                   m_bEntityRequiresProcessing;
    bool                   m_bDisallowDroppingOnAnimEnd;
    bool                   field_37;
    CAnimBlendAssociation* m_pAnimBlendAssociation;

public:
    CTaskSimpleHoldEntity(CEntity* entityToHold, CVector* posn, uint8 boneFrameId, uint8 boneFlags, AnimationId animId, AssocGroupId groupId, bool bDisAllowDroppingOnAnimEnd);
    CTaskSimpleHoldEntity(CEntity* entityToHold, CVector* posn, uint8 boneFrameId, uint8 boneFlags, const char* animName, const char* animBlockName, eAnimationFlags animFlags);
    CTaskSimpleHoldEntity(CEntity* entityToHold, CVector* posn, uint8 boneFrameId, uint8 boneFlags, CAnimBlock* animBlock, CAnimBlendHierarchy* animHierarchy, eAnimationFlags animFlags);
    ~CTaskSimpleHoldEntity();

    // original virtual functions
    CTask* Clone() override;
    eTaskType GetTaskType() override;
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;
    bool ProcessPed(CPed* ped) override;
    bool SetPedPosition(CPed* ped) override;

    void ReleaseEntity();
    bool CanThrowEntity();
    void PlayAnim(AnimationId groupId, AssocGroupId animId);
    static void FinishAnimHoldEntityCB(CAnimBlendAssociation* pAnimAssoc, void* pData);
    void StartAnim(CPed* ped);
    void DropEntity(CPed* ped, bool bAddEventSoundQuiet);
    void ChoosePutDownHeight(CPed* ped);

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CTaskSimpleHoldEntity* Constructor(CEntity* entityToHold, CVector* posn, uint8 boneFrameId, uint8 boneFlags, AnimationId animId, AssocGroupId groupId, bool bDisAllowDroppingOnAnimEnd);
    CTaskSimpleHoldEntity* Constructor(CEntity* entityToHold, CVector* posn, uint8 boneFrameId, uint8 boneFlags, const char* animName, const char* animBlockName, eAnimationFlags animFlags);
    CTaskSimpleHoldEntity* Constructor(CEntity* entityToHold, CVector* posn, uint8 boneFrameId, uint8 boneFlags, CAnimBlock* animBlock, CAnimBlendHierarchy* animHierarchy, eAnimationFlags animFlags);

    CTask* Clone_Reversed();
    eTaskType GetId_Reversed() { return TASK_SIMPLE_HOLD_ENTITY; };
    bool MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, const CEvent* event);
    bool ProcessPed_Reversed(CPed* ped);
    bool SetPedPosition_Reversed(CPed* ped);
};

VALIDATE_SIZE(CTaskSimpleHoldEntity, 0x3C);

