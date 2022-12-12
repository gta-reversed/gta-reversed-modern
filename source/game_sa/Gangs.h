/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "ePedType.h"

class CPed;
class GangInfo;

class CGangs {
public:
    inline static std::array<bool, TOTAL_GANGS>& GangAttackWithCops = *reinterpret_cast<std::array<bool, 10>*>(0xC091D9);
    inline static std::array<CGangInfo, TOTAL_GANGS>& Gang = *reinterpret_cast<std::array<CGangInfo, 10>*>(0xC091F0);

public:
    static void InjectHooks();

    static void Initialise();

    static bool Load();
    static bool Save();
    static void SetGangWeapons(int16 gangId, int32 weapId1, int32 weapId2, int32 weapId3);
    static int32 ChooseGangPedModel(int16 gangId);

    static bool GetWillAttackPlayerWithCops(ePedType pedType);
    static void SetWillAttackPlayerWithCops(ePedType pedType, bool bAttackPlayerWithCops);
    static void SetGangPedModelOverride(int16 gangId, int8 PedModelOverride);
};
