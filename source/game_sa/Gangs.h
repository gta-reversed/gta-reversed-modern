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

enum eGangID {
    GANG_BALLAS = 0,
    GANG_GROVE = 1,
    GANG_VAGOS = 2,
    GANG_RIFA = 3,
    GANG_DANANGBOYS = 4,
    GANG_MAFIA = 5,
    GANG_TRIAD = 6,
    GANG_AZTECAS = 7,
    GANG_UNUSED1 = 8, // RUSSIAN_MAFIA
    GANG_UNUSED2 = 9, // BIKERS

    TOTAL_GANGS
};

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
