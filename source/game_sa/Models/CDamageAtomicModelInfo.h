#pragma once
#include "CAtomicModelInfo.h"

class CDamageAtomicModelInfo : CAtomicModelInfo
{
public:
    RpAtomic* m_pDamagedAtomic;

public:
    static bool& ms_bCreateDamagedVersion;
};

VALIDATE_SIZE(CDamageAtomicModelInfo, 0x24);
