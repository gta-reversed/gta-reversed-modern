#include "StdInc.h"

#include "PedDamageResponseCalculator.h"

float& CPedDamageResponseCalculator::ms_damageFactor = *(float*)0x8A6260; // 5555.5498

void CPedDamageResponseCalculator::InjectHooks()
{
    RH_ScopedClass(CPedDamageResponseCalculator);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(Constructor, 0x4AD3F0);
}

CPedDamageResponseCalculator::CPedDamageResponseCalculator(CEntity* entity, float fDamage, eWeaponType weaponType, ePedPieceTypes bodyPart, bool bSpeak)
{
    m_pDamager = entity;
    m_fDamageFactor = fDamage;
    m_bodyPart = bodyPart;
    m_weaponType = weaponType;
    m_bSpeak = bSpeak;
}

// 0x4AD3F0
CPedDamageResponseCalculator* CPedDamageResponseCalculator::Constructor(CEntity * entity, float fDamage, eWeaponType weaponType, ePedPieceTypes bodyPart, bool bSpeak)
{
    this->CPedDamageResponseCalculator::CPedDamageResponseCalculator(entity, fDamage, weaponType, bodyPart, bSpeak);
    return this;
}

void CPedDamageResponseCalculator::ComputeDamageResponse(CPed * ped, CPedDamageResponse * pDamageResponse, bool bSpeak)
{
    plugin::CallMethod<0x4B5AC0, CPedDamageResponseCalculator*, CPed *, CPedDamageResponse *, bool>(this, ped, pDamageResponse, bSpeak);
}
