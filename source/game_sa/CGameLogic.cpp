#include "StdInc.h"

int8_t& CGameLogic::GameState = *reinterpret_cast<int8_t*>(0x96A8B0);

void CGameLogic::InitAtStartOfGame()
{
    plugin::Call<0x441210>();
}

float CGameLogic::CalcDistanceToForbiddenTrainCrossing(CVector vecPoint, CVector vecMoveSpeed, bool somebool, CVector* pOutDistance)
{
    return plugin::CallAndReturn<float, 0x4418E0, CVector, CVector, bool, CVector*>(vecPoint, vecMoveSpeed, somebool, pOutDistance);
}

bool CGameLogic::IsPlayerAllowedToGoInThisDirection(CPed* pPed, float moveDirectionX, float moveDirectionY, float moveDirectionZ, float distanceLimit)
{
    return plugin::CallAndReturn<bool, 0x441E10, CPed*, float, float, float, float>(pPed, moveDirectionX, moveDirectionY, moveDirectionZ, distanceLimit);
}

bool CGameLogic::IsPlayerUse2PlayerControls(CPed* pPed)
{
    return plugin::CallAndReturn<bool, 0x442020, CPed*>(pPed);
}

bool CGameLogic::IsCoopGameGoingOn()
{
    return plugin::CallAndReturn<bool, 0x441390>();
}

void CGameLogic::ClearSkip(bool a1)
{
    return plugin::Call<0x441560, bool>(a1);
}

bool CGameLogic::LaRiotsActiveHere()
{
    return plugin::CallAndReturn<bool, 0x441C10>();
}
