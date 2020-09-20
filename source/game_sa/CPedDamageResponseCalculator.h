#pragma once
#include "CPedDamageResponse.h"
#include "eWeaponType.h"
#include "CPed.h"

class CPedDamageResponseCalculator
{
public:
    CEntity *      m_pDamager;
    float          m_fDamageFactor;
    ePedPieceTypes m_bodyPart;
    eWeaponType    m_weaponType;
    bool           m_bSpeak;     // refers to a CPed::Say call (the dying scream?)

    static float& ms_damageFactor;

    static void InjectHooks();
    CPedDamageResponseCalculator(CEntity* pEntity, float fDamage, eWeaponType weaponType, ePedPieceTypes bodyPart, bool bSpeak);
    ~CPedDamageResponseCalculator();
private:
    CPedDamageResponseCalculator* Constructor(CEntity * pEntity, float fDamage, eWeaponType weaponType, ePedPieceTypes bodyPart, bool bSpeak);
public:

    void ComputeDamageResponse(CPed * pPed, CPedDamageResponse * pDamageResponse, bool bSpeak);
    
};

VALIDATE_SIZE(CPedDamageResponseCalculator, 0x14);
