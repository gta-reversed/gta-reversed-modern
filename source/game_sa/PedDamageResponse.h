#pragma once

class CPedDamageResponse {
public:
    float m_fDamageHealth;
    float m_fDamageArmor;
    bool  m_bHealthZero;
    bool  m_bForceDeath;
    bool  m_bDamageCalculated;
    bool  m_bCheckIfAffectsPed;
};

VALIDATE_SIZE(CPedDamageResponse, 0xC);