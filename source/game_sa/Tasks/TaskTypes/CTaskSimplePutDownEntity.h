#pragma once
#include "CTaskSimpleHoldEntity.h"

class CTaskSimplePutDownEntity : public CTaskSimpleHoldEntity
{
public:
    float m_fPutDownHeightZ;

    CTaskSimplePutDownEntity* Constructor();
};

VALIDATE_SIZE(CTaskSimplePutDownEntity, 0x40);