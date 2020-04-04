#pragma once
#include "PluginBase.h"
#include "CTaskSimple.h"

enum eHoldEntityBoneFlags 
{
    HOLD_ENTITY_UPDATE_BONE_TRANSLATION_ONLY = 0x16
};

class CTaskSimpleHoldEntity : public CTaskSimple {
    CTaskSimpleHoldEntity() = delete;
public:
    class CEntity* m_pEntityToHold;
    CVector m_vecPosition;
    char m_bBoneFrameId;
    unsigned char m_bBoneFlags;
    bool field_1A [2];
    float m_fRotation;
    int m_nAnimId;
    int m_nAnimGroupId;
    int m_animFlags; // m_pAnimBlendAssociation flags
    class CAnimBlock* m_pAnimBlock; 
    class CAnimBlendHierarchy* m_pAnimBlendHierarchy; // If set, m_animID and m_groupID are ignored in StartAnim method
    bool m_bEntityDropped; 
    bool m_bEntityRequiresProcessing;
    bool m_bDisallowDroppingOnAnimEnd;
    bool field_37;
    class CAnimBlendAssociation* m_pAnimBlendAssociation; 

    // original virtual functions
    CTask* Clone() override;
    eTaskType GetId() override;
    bool MakeAbortable(class CPed* ped, eAbortPriority priority, class CEvent* _event) override;
    bool ProcessPed(class CPed* ped) override;
    bool SetPedPosition(class CPed* ped) override;

    // reversed virtual functions
    eTaskType GetId_Reversed();
    bool ProcessPed_Reversed(class CPed* ped);

    CTaskSimpleHoldEntity* Constructor(CEntity* pEntityToHold, CVector* pPosition, char boneFrameId, unsigned char boneFlags, 
                                       int animId, int groupId, bool bDisAllowDroppingOnAnimEnd);
    CTaskSimpleHoldEntity* Constructor(CEntity* pEntityToHold, CVector* pPosition, char boneFrameId, unsigned char boneFlags, 
                                      char* pAnimName, int animBlockId, int animFlags);
    CTaskSimpleHoldEntity* Constructor(CEntity* pEntityToHold, CVector* pPosition, char boneFrameId, unsigned char boneFlags,
                                       CAnimBlock* pAnimBlock, CAnimBlendHierarchy* pAnimHierarchy, int animFlags);

    CTaskSimpleHoldEntity* Destructor();
    void ReleaseEntity();
    bool CanThrowEntity();
    void PlayAnim(int groupId, int animId);
    static void FinishAnimHoldEntityCB(CAnimBlendAssociation* pAnimAssoc, CTaskSimpleHoldEntity* pTaskHoldEntity);
    void StartAnim(CPed* pPed);
    void DropEntity(CPed* pPed, bool bAddEventSoundQuiet);
    void ChoosePutDownHeight(CPed* pPed);
};

VALIDATE_SIZE(CTaskSimpleHoldEntity, 0x3C);

