#pragma once

#include "Ped.h"

class CAccident {
public:
    CPed* m_pPed;
    uint8 m_bIsTreated;
    uint8 m_bIsRevived;
    uint8 _pad6[2];

    CAccident();
    bool IsFree();
};

VALIDATE_SIZE(CAccident, 0x8);
