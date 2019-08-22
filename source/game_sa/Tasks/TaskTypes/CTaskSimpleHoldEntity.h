#pragma once
#include "PluginBase.h"
#include "CTaskSimple.h"

class  CTaskSimpleHoldEntity : public CTaskSimple {
protected:
    CTaskSimpleHoldEntity(plugin::dummy_func_t a) : CTaskSimple(a) {}
public:
    class CObject* m_pObjectToHold;
    float m_posX; // posX, posY, and posZ might not be float. We need to confirm it
    float m_posY;
    float m_posZ; 
    bool field_18;
    bool field_19; 
    bool field_1A[6];
    int m_groupID;
    int m_animID;
    int m_animFlags; // m_pAnimBlendAssociation flags
    class CAnimBlock* m_pAnimBlock; 
    class CAnimBlendHierarchy* m_pAnimBlendHierarchy; // If set, m_animID and m_groupID are ignored in StartAnim method
    bool m_bEntityDropped; 
    bool field_35;
    bool field_36;
    bool field_37;
    class CAnimBlendAssociation* m_pAnimBlendAssociation; 
    float m_fPutDownHeightZ;
};

VALIDATE_SIZE(CTaskSimpleHoldEntity, 0x40);

