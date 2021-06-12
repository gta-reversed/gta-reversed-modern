#pragma once
#include "CPed.h"

class CAccident
{
public:
    CPed* m_pPed;
    unsigned char m_bIsTreated;
    unsigned char m_bIsRevived;
    unsigned char _pad6[2];

    CAccident();
    bool IsFree();
};

VALIDATE_SIZE(CAccident, 0x8);
