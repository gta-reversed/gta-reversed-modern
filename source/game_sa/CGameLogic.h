#pragma once
#include "PluginBase.h"
#include "CVector.h"

class CPed;
class CGameLogic 
{
public:
    static double CalcDistanceToForbiddenTrainCrossing(CVector vecPoint, CVector vecMoveSpeed, bool somebool, CVector* pOutDistance);
    static bool IsPlayerAllowedToGoInThisDirection(CPed* pPed, float moveDirectionX, float moveDirectionY, float moveDirectionZ, float distanceLimit);
    static bool IsPlayerUse2PlayerControls(CPed* pPed);
    static bool IsCoopGameGoingOn();
    static void ClearSkip(bool a1);
};
