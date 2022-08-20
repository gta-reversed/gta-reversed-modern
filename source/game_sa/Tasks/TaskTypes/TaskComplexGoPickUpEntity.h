#pragma once

#include "TaskComplex.h"

class CEntity;

class CTaskComplexGoPickUpEntity : public CTaskComplex {
public:
    static constexpr auto Type = TASK_COMPLEX_GO_PICKUP_ENTITY;

    CEntity* m_pEntity;
    CVector  m_vecPosition;
    CVector  m_vecPickupPosition;
    uint32   m_nTimePassedSinceLastSubTaskCreatedInMs;
    int32    m_nAnimGroupId;
    bool     m_bAnimBlockReferenced;
    char     _pad[3];
};

VALIDATE_SIZE(CTaskComplexGoPickUpEntity, 0x34);