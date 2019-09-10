#pragma once
#include "CTaskComplex.h"

class CTaskComplexGoPickUpEntity : public CTaskComplex 
{
public:
    class CEntity* pEntity;
    CVector m_vecPosition;
    CVector m_vecPickupPosition;
    unsigned int m_nTimePassedSinceLastSubTaskCreatedInMs;
    int m_nAnimGroupId;
    bool m_bAnimBlockReferenced;
    unsigned char padding[3];
};

VALIDATE_SIZE(CTaskComplexGoPickUpEntity, 0x34);