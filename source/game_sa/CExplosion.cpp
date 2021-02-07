#include "StdInc.h"

bool CExplosion::AddExplosion(CEntity* victim, CEntity* creator, eExplosionType explosionType, CVector posn, unsigned int time, bool bMakeSound, float camShake, bool bHideExplosion)
{
    return plugin::CallAndReturn<bool, 0x736A50, CEntity*, CEntity*, eExplosionType, CVector, unsigned int, bool, float, bool>(victim, creator, explosionType, posn, time, bMakeSound, camShake, bHideExplosion);
}
