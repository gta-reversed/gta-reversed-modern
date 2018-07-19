#include "StdInc.h"

void CEventDamage::InjectHooks()
{

}

CEventDamage* CEventDamage::Constructor1(CEntity * pEntity, unsigned int i_1, eWeaponType weaponType, ePedPieceTypes hitZone, unsigned char uc_2, bool b_3, bool b_4)
{
    return plugin::CallMethodAndReturn<CEventDamage*, 0x4AD830, CEventDamage*, CEntity *, unsigned int, eWeaponType, ePedPieceTypes, unsigned char, bool, bool>(this, pEntity, i_1, weaponType, hitZone,uc_2, b_3, b_4);
}

void CEventDamage::Destructor1()
{
    plugin::CallMethod<0x4AD960, CEventDamage*>(this);
}

bool CEventDamage::AffectsPed(CPed * pPed)
{
    return plugin::CallMethodAndReturn<bool, 0x4B35A0, CEventDamage*, CPed *>(this, pPed);
}