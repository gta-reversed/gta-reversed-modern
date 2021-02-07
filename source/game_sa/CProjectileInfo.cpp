#include "StdInc.h"

bool CProjectileInfo::AddProjectile(CEntity* creator, eWeaponType eWeaponType, CVector posn, float force,
    CVector* direction, CEntity* victim)
{
    return plugin::CallAndReturn<bool, 0x737C80, CEntity*, uint32_t, CVector, float, CVector*, CEntity*>
        (creator, eWeaponType, posn, force, direction, victim);
}

void CProjectileInfo::RemoveAllProjectiles()
{
    plugin::Call<0x7399B0>();
}

bool CProjectileInfo::RemoveIfThisIsAProjectile(CObject* object)
{
    return plugin::CallAndReturn<bool, 0x739A40, CObject*>(object);
}
