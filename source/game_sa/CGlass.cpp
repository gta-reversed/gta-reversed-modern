#include "StdInc.h"

void CGlass::WindowRespondsToCollision(CEntity* pEntity, float fDamageIntensity, CVector vecMoveSpeed, CVector vecPoint, int bUnknown)
{
    return plugin::Call<0x71BC40, CEntity*, float, CVector, CVector, int>(pEntity, fDamageIntensity, vecMoveSpeed, vecPoint, bUnknown);
}

void CGlass::WindowRespondsToSoftCollision(CObject* pEntity, float fDamageIntensity)
{
    return plugin::Call<0x71AF70, CObject*, float>(pEntity, fDamageIntensity);
}

void CGlass::AskForObjectToBeRenderedInGlass(CEntity* pEntity)
{
    plugin::Call<0x71ACD0, CEntity*>(pEntity);
}
