#pragma once
#include "CTaskComplex.h"

class CTaskComplexGoPickUpEntity : public CTaskComplex 
{
public:
    class CEntity* pEntity;
    CVector m_vecPosition;
    CVector m_vecPickupPosition;
    uint32 m_nTimePassedSinceLastSubTaskCreatedInMs;
    int32 m_nAnimGroupId;
    bool m_bAnimBlockReferenced;
    uint8 padding[3];
};

VALIDATE_SIZE(CTaskComplexGoPickUpEntity, 0x34);