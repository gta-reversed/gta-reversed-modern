#include "StdInc.h"

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