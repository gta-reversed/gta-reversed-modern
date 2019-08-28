#pragma once
#include "PluginBase.h"

class CPed;
class CGameLogic 
{
public:
    static bool IsPlayerAllowedToGoInThisDirection(CPed* pPed, float moveDirectionX, float moveDirectionY, float moveDirectionZ, float distanceLimit);
    static bool IsPlayerUse2PlayerControls(CPed* pPed);
    static bool IsCoopGameGoingOn();
};