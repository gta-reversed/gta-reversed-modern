#include "StdInc.h"

void CPedDamageResponseCalculator::InjectHooks()
{

}

CPedDamageResponseCalculator* CPedDamageResponseCalculator::Constructor1(CEntity * pEntity, float fDamage, eWeaponType weaponType, ePedPieceTypes bodyPart, bool b_1)
{
    return plugin::CallMethodAndReturn<CPedDamageResponseCalculator*, 0x4AD3F0, CPedDamageResponseCalculator*, CEntity *, float, eWeaponType, ePedPieceTypes, bool>(this, pEntity, fDamage, weaponType, bodyPart, b_1);
}

void CPedDamageResponseCalculator::Destructor1()
{
    plugin::CallMethod<0x4AD420, CPedDamageResponseCalculator*>(this);
}

void CPedDamageResponseCalculator::ComputeDamageResponse(CPed * pPed, CPedDamageResponse * pDamageResponse, bool bSpeak)
{
    plugin::CallMethod<0x4B5AC0, CPedDamageResponseCalculator*, CPed *, CPedDamageResponse *, bool>(this, pPed, pDamageResponse, bSpeak);
}