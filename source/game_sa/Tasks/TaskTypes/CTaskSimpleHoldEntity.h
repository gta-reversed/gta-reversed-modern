#pragma once
#include "PluginBase.h"
#include "CTaskSimple.h"

class  CTaskSimpleHoldEntity : public CTaskSimple {
protected:
    CTaskSimpleHoldEntity(plugin::dummy_func_t a) : CTaskSimple(a) {}
public:
    class CObject* m_pObjectToHold;
    CVector m_vecPosition;
    bool m_bBoneFrameId;
    bool m_bBoneFlags;
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
};

VALIDATE_SIZE(CTaskSimpleHoldEntity, 0x3C);

