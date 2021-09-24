/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Vector.h"

class CCreepingFire {
public:
    // 32x32 map areas
    static uint8(*m_aFireStatus)[32]; // static uint8 m_aFireStatus[32][32]

    static bool TryToStartFireAtCoors(CVector posn, int8 numGenerations, _IGNORED_ bool arg2, bool scriptFire, float zDistance);
    static void SetReadyToBurn();
    static void Update();
};
