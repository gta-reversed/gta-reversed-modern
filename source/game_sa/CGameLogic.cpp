#include "StdInc.h"

int8_t& CGameLogic::GameState = *reinterpret_cast<int8_t*>(0x96A8B0);

void CGameLogic::InjectHooks() {
//    ReversibleHooks::Install("CGameLogic", "InitAtStartOfGame", 0x441210, &CGameLogic::InitAtStartOfGame);
//    ReversibleHooks::Install("CGameLogic", "CalcDistanceToForbiddenTrainCrossing", 0x4418E0, &CGameLogic::CalcDistanceToForbiddenTrainCrossing);
//    ReversibleHooks::Install("CGameLogic", "IsPlayerAllowedToGoInThisDirection", 0x441E10, &CGameLogic::IsPlayerAllowedToGoInThisDirection);
//    ReversibleHooks::Install("CGameLogic", "IsPlayerUse2PlayerControls", 0x442020, &CGameLogic::IsPlayerUse2PlayerControls);
//    ReversibleHooks::Install("CGameLogic", "IsCoopGameGoingOn", 0x441390, &CGameLogic::IsCoopGameGoingOn);
//    ReversibleHooks::Install("CGameLogic", "ClearSkip", 0x441560, &CGameLogic::ClearSkip);
//    ReversibleHooks::Install("CGameLogic", "LaRiotsActiveHere", 0x441C10, &CGameLogic::LaRiotsActiveHere);
}

// 0x441210
void CGameLogic::InitAtStartOfGame()
{
    plugin::Call<0x441210>();
}

// 0x4418E0
float CGameLogic::CalcDistanceToForbiddenTrainCrossing(CVector vecPoint, CVector vecMoveSpeed, bool somebool, CVector* pOutDistance)
{
    return plugin::CallAndReturn<float, 0x4418E0, CVector, CVector, bool, CVector*>(vecPoint, vecMoveSpeed, somebool, pOutDistance);
}

// 0x441E10
bool CGameLogic::IsPlayerAllowedToGoInThisDirection(CPed* pPed, float moveDirectionX, float moveDirectionY, float moveDirectionZ, float distanceLimit)
{
    return plugin::CallAndReturn<bool, 0x441E10, CPed*, float, float, float, float>(pPed, moveDirectionX, moveDirectionY, moveDirectionZ, distanceLimit);
}

// 0x442020
bool CGameLogic::IsPlayerUse2PlayerControls(CPed* pPed)
{
    return plugin::CallAndReturn<bool, 0x442020, CPed*>(pPed);
}

// 0x441390
bool CGameLogic::IsCoopGameGoingOn()
{
    return plugin::CallAndReturn<bool, 0x441390>();
}

// 0x441560
void CGameLogic::ClearSkip(bool a1)
{
    return plugin::Call<0x441560, bool>(a1);
}

// 0x441C10
bool CGameLogic::LaRiotsActiveHere()
{
    return plugin::CallAndReturn<bool, 0x441C10>();
}
