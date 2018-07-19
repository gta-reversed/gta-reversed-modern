#pragma once
#include "PluginBase.h"

class CPedDamageResponse
{
public:
    
    float       fDamageHealth;
    float       fDamageArmor;
    bool        bUnk;
    bool        bForceDeath;
    bool        bDamageCalculated;
    bool        bUnk3;
};

VALIDATE_SIZE(CPedDamageResponse, 0xC);