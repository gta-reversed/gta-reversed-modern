#pragma once
#include "CTaskSimpleHoldEntity.h"

class CTaskSimplePickUpEntity : public CTaskSimpleHoldEntity
{
public:
    float m_fMovePedUntilAnimProgress; // value can be 0.0 to 1.0. Ped Will stop moving when the current `m_fCurrentTime` 
                                       // of `m_pAnimBlendAssociation` is equal or greater than this.
    CVector m_vecPickupPosition;
};

VALIDATE_SIZE(CTaskSimplePickUpEntity, 0x4C);