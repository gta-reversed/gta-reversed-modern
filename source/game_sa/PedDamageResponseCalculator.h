#pragma once

#include "eWeaponType.h"

class CEntity;
class CPed;
class CPedDamageResponse;

class CPedDamageResponseCalculator {
public:
    CEntity *      m_pDamager;
    float          m_fDamageFactor;
    ePedPieceTypes m_bodyPart;
    eWeaponType    m_weaponType;
    bool           m_bSpeak;     // refers to a CPed::Say call (the dying scream?)

    static float& ms_damageFactor;

public:
    CPedDamageResponseCalculator(CEntity* entity, float fDamage, eWeaponType weaponType, ePedPieceTypes bodyPart, bool bSpeak);
    ~CPedDamageResponseCalculator() = default;

    void ComputeDamageResponse(CPed* ped, CPedDamageResponse* damageResponse, bool bSpeak);

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CPedDamageResponseCalculator* Constructor(CEntity* entity, float fDamage, eWeaponType weaponType, ePedPieceTypes bodyPart, bool bSpeak);
};

VALIDATE_SIZE(CPedDamageResponseCalculator, 0x14);
