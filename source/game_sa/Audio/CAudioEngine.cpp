#include "StdInc.h"

CAudioEngine& AudioEngine = *reinterpret_cast<CAudioEngine*>(0xB6BC90);

void CAudioEngine::ReportCollision(CEntity* pEntity1, CEntity* pEntity2, int surface1, int surface2, CColPoint* pColPoint, CVector* normal, float fCollisionImpact1, float fCollisionImpact2, int bOnlyPlayOneShotCollisionSound, bool bUnknown)
{
    return plugin::CallMethod<0x506EB0, CAudioEngine*, CEntity*, CEntity*, int, int, CColPoint*, CVector*, float, float, int, bool>(this,
        pEntity1, pEntity2, surface1, surface2, pColPoint, normal, fCollisionImpact1, fCollisionImpact2, bOnlyPlayOneShotCollisionSound, bUnknown);
}