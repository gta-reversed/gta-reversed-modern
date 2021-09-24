#pragma once

#include "CTaskComplex.h"

class CEntity;

class CTaskComplexGoPickUpEntity : public CTaskComplex {
public:
    CEntity* pEntity;
    CVector  m_vecPosition;
    CVector  m_vecPickupPosition;
    uint32   m_nTimePassedSinceLastSubTaskCreatedInMs;
    int32    m_nAnimGroupId;
    bool     m_bAnimBlockReferenced;
    char     _pad[3];
};

VALIDATE_SIZE(CTaskComplexGoPickUpEntity, 0x34);