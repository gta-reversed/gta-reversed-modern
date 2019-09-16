#pragma once
#include "CTaskSimpleHoldEntity.h"

class CTaskSimplePutDownEntity : public CTaskSimpleHoldEntity
{
protected:
    CTaskSimplePutDownEntity(plugin::dummy_func_t a) :CTaskSimpleHoldEntity(a) {}
public:
    float m_fPutDownHeightZ;

    CTaskSimplePutDownEntity* Constructor();
};

VALIDATE_SIZE(CTaskSimplePutDownEntity, 0x40);