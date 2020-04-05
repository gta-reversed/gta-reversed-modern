#pragma once
#include "PluginBase.h"
#include "CTaskSimple.h"

enum eHoldEntityBoneFlags 
{
    HOLD_ENTITY_UPDATE_TRANSLATION_ONLY = 0x10
};

class CTaskSimpleHoldEntity : public CTaskSimple {
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

    static void InjectHooks();
    
public:
    CTaskSimpleHoldEntity(CEntity* pEntityToHold, CVector* pPosition, char boneFrameId, unsigned char boneFlags,
        int animId, int groupId, bool bDisAllowDroppingOnAnimEnd);
    CTaskSimpleHoldEntity(CEntity* pEntityToHold, CVector* pPosition, char boneFrameId, unsigned char boneFlags,
        char* pAnimName, char* pAnimBlockName, int animFlags);
    CTaskSimpleHoldEntity(CEntity* pEntityToHold, CVector* pPosition, char boneFrameId, unsigned char boneFlags,
        CAnimBlock* pAnimBlock, CAnimBlendHierarchy* pAnimHierarchy, int animFlags);
    ~CTaskSimpleHoldEntity();
private:
    CTaskSimpleHoldEntity* Constructor(CEntity* pEntityToHold, CVector* pPosition, char boneFrameId, unsigned char boneFlags,
        int animId, int groupId, bool bDisAllowDroppingOnAnimEnd);
    CTaskSimpleHoldEntity* Constructor(CEntity* pEntityToHold, CVector* pPosition, char boneFrameId, unsigned char boneFlags,
        char* pAnimName, char* pAnimBlockName, int animFlags);
    CTaskSimpleHoldEntity* Constructor(CEntity* pEntityToHold, CVector* pPosition, char boneFrameId, unsigned char boneFlags,
        CAnimBlock* pAnimBlock, CAnimBlendHierarchy* pAnimHierarchy, int animFlags);
public:
    // original virtual functions
    CTask* Clone() override;
    eTaskType GetId() override;
    bool MakeAbortable(class CPed* ped, eAbortPriority priority, class CEvent* _event) override;
    bool ProcessPed(class CPed* ped) override;
    bool SetPedPosition(class CPed* ped) override;

    // reversed virtual functions
    CTask* Clone_Reversed();
    eTaskType GetId_Reversed() { return TASK_SIMPLE_HOLD_ENTITY; };
    bool MakeAbortable_Reversed(class CPed* ped, eAbortPriority priority, class CEvent* _event);
    bool ProcessPed_Reversed(class CPed* ped);
    bool SetPedPosition_Reversed(class CPed* ped);

    void ReleaseEntity();
    bool CanThrowEntity();
    void PlayAnim(int groupId, int animId);
    static void FinishAnimHoldEntityCB(CAnimBlendAssociation* pAnimAssoc, void* pData);
    void StartAnim(CPed* pPed);
    void DropEntity(CPed* pPed, bool bAddEventSoundQuiet);
    void ChoosePutDownHeight(CPed* pPed);
};

VALIDATE_SIZE(CTaskSimpleHoldEntity, 0x3C);

