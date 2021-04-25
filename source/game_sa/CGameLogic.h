#pragma once

#include "CVector.h"

enum eGameState {
    GAME_STATE_INITIAL = 0,
    GAME_STATE_LOGO = 1,
    GAME_STATE_PLAYING_LOGO = 2,
    GAME_STATE_TITLE = 3,
    GAME_STATE_PLAYING_INTRO = 4,
    GAME_STATE_FRONTEND_LOADING = 5,
    GAME_STATE_FRONTEND_LOADED = 6,
    GAME_STATE_FRONTEND_IDLE = 7,
    GAME_STATE_LOADING_STARTED = 8,
    GAME_STATE_LOADING_FINISHED = 9,
};

class CPed;

class CGameLogic {
public:
    static int8_t& GameState;

    static void InjectHooks();

    static void InitAtStartOfGame();
    static float CalcDistanceToForbiddenTrainCrossing(CVector vecPoint, CVector vecMoveSpeed, bool somebool, CVector* pOutDistance);
    static bool IsPlayerAllowedToGoInThisDirection(CPed* pPed, float moveDirectionX, float moveDirectionY, float moveDirectionZ, float distanceLimit);
    static bool IsPlayerUse2PlayerControls(CPed* pPed);
    static bool IsCoopGameGoingOn();
    static void ClearSkip(bool a1);
    static bool LaRiotsActiveHere();
};
