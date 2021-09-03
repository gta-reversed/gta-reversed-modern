#pragma once

#include "CTaskSimple.h"

enum eHoldEntityBoneFlags 
{
    HOLD_ENTITY_FLAG_1 = 0x1,
    HOLD_ENTITY_UPDATE_TRANSLATION_ONLY = 0x10
};

class CEntity;
class CAnimBlock;
class CAnimBlendHierarchy;
class CAnimBlendAssociation;

class CTaskSimpleHoldEntity : public CTaskSimple {
public:
    CEntity* m_pEntityToHold;
    CVector m_vecPosition;
    char    m_bBoneFrameId; // see ePedNode
    uint8   m_bBoneFlags;
    bool field_1A [2];
    float m_fRotation;
    AnimationId  m_nAnimId;
    AssocGroupId m_nAnimGroupId;
    int32 m_animFlags; // m_pAnimBlendAssociation flags
    CAnimBlock* m_pAnimBlock;
    CAnimBlendHierarchy* m_pAnimBlendHierarchy; // If set, m_animID and m_groupID are ignored in StartAnim method
    bool m_bEntityDropped; 
    bool m_bEntityRequiresProcessing;
    bool m_bDisallowDroppingOnAnimEnd;
    bool field_37;
    CAnimBlendAssociation* m_pAnimBlendAssociation;

public:
    CTaskSimpleHoldEntity(CEntity* pEntityToHold, CVector* pPosition, char boneFrameId, uint8 boneFlags, AnimationId animId, AssocGroupId groupId, bool bDisAllowDroppingOnAnimEnd);
    CTaskSimpleHoldEntity(CEntity* pEntityToHold, CVector* pPosition, char boneFrameId, uint8 boneFlags, char* pAnimName, char* pAnimBlockName, int32 animFlags);
    CTaskSimpleHoldEntity(CEntity* pEntityToHold, CVector* pPosition, char boneFrameId, uint8 boneFlags, CAnimBlock* pAnimBlock, CAnimBlendHierarchy* pAnimHierarchy, int32 animFlags);
    ~CTaskSimpleHoldEntity();

    // original virtual functions
    CTask* Clone() override;
    eTaskType GetId() override;
    bool MakeAbortable(class CPed* ped, eAbortPriority priority, const CEvent* event) override;
    bool ProcessPed(class CPed* ped) override;
    bool SetPedPosition(class CPed* ped) override;

    void ReleaseEntity();
    bool CanThrowEntity();
    void PlayAnim(AnimationId groupId, AssocGroupId animId);
    static void FinishAnimHoldEntityCB(CAnimBlendAssociation* pAnimAssoc, void* pData);
    void StartAnim(CPed* pPed);
    void DropEntity(CPed* pPed, bool bAddEventSoundQuiet);
    void ChoosePutDownHeight(CPed* pPed);

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CTaskSimpleHoldEntity* Constructor(CEntity* pEntityToHold, CVector* pPosition, char boneFrameId, uint8 boneFlags, AnimationId animId, AssocGroupId groupId, bool bDisAllowDroppingOnAnimEnd);
    CTaskSimpleHoldEntity* Constructor(CEntity* pEntityToHold, CVector* pPosition, char boneFrameId, uint8 boneFlags, char* pAnimName, char* pAnimBlockName, int32 animFlags);
    CTaskSimpleHoldEntity* Constructor(CEntity* pEntityToHold, CVector* pPosition, char boneFrameId, uint8 boneFlags, CAnimBlock* pAnimBlock, CAnimBlendHierarchy* pAnimHierarchy, int32 animFlags);

    // reversed virtual functions
    CTask* Clone_Reversed();
    eTaskType GetId_Reversed() { return TASK_SIMPLE_HOLD_ENTITY; };
    bool MakeAbortable_Reversed(class CPed* ped, eAbortPriority priority, const CEvent* event);
    bool ProcessPed_Reversed(class CPed* ped);
    bool SetPedPosition_Reversed(class CPed* ped);
};

VALIDATE_SIZE(CTaskSimpleHoldEntity, 0x3C);

