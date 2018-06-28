/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CVector.h"

class  CCreepingFire {
public:
    // 32x32 map areas
    static unsigned char(*m_aFireStatus)[32]; // static unsigned char m_aFireStatus[32][32]

    static bool TryToStartFireAtCoors(CVector posn, signed char numGenerations, _IGNORED_ bool arg2, bool scriptFire, float zDistance);
    static void SetReadyToBurn();
    static void Update();
};