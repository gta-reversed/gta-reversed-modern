#pragma once
#include "PluginBase.h"
#include "CVector.h"

enum eGameState
{
    GAME_STATE_0 = 0,
};

class CPed;
class CGameLogic 
{
public:
    static int8_t& GameState;

    static void InitAtStartOfGame();
    static float CalcDistanceToForbiddenTrainCrossing(CVector vecPoint, CVector vecMoveSpeed, bool somebool, CVector* pOutDistance);
    static bool IsPlayerAllowedToGoInThisDirection(CPed* pPed, float moveDirectionX, float moveDirectionY, float moveDirectionZ, float distanceLimit);
    static bool IsPlayerUse2PlayerControls(CPed* pPed);
    static bool IsCoopGameGoingOn();
    static void ClearSkip(bool a1);
    static bool LaRiotsActiveHere();
};
