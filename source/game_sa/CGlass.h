#pragma once
#include "CVector.h"

class CEntity;
class CObject;

class CGlass
{
public:
    static void WindowRespondsToCollision(CEntity* pEntity, float fDamageIntensity, CVector vecMoveSpeed, CVector vecPoint, int bUnknown);
    static void WindowRespondsToSoftCollision(CObject* pEntity, float fDamageIntensity);
    static void AskForObjectToBeRenderedInGlass(CEntity* pEntity);
};
