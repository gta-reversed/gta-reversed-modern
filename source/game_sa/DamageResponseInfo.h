#pragma once

class  CDamageResponseInfo { 
public:
    float damageHealth{};
    float damageArmor{};
    bool  bHealthZero{};
    bool  bForceDeath{};
    bool  bDamageCalculated{};
    bool  bCheckIfAffectsPed{};
};
