/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "CPed.h"
#include "CGangInfo.h"

enum eGangID {
    GANG_BALLAS = 0,
    GANG_GROVE = 1,
    GANG_VAGOS = 2,
    GANG_RIFA = 3,
    GANG_DANANGBOYS = 4,
    GANG_MAFIA = 5,
    GANG_TRIAD = 6,
    GANG_AZTECAS = 7,
    GANG_UNUSED1 = 8, //!< RUSSIAN_MAFIA
    GANG_UNUSED2 = 9  //!< BIKERS
};

class CGangs {
public:
    static bool (&GangAttackWithCops)[16]; // static bool GangAttackWithCops[16]
    static CGangInfo (&Gang)[10];          // static CGangInfo Gang[10]

public:
    static void InjectHooks();

    static void Initialise();

    static signed int ChooseGangPedModel(int16 gangID);
    //! unused
    static bool GetWillAttackPlayerWithCops(ePedType gangID);
    static void Load();
    static void Save();
    //! unused
    static void SetGangPedModelOverride(int16 gangID, signed char PedModelOverride);
    static void SetGangWeapons(int16 gangID, int32 weapID1, int32 weapID2, int32 weapID3);
    //! unused
    static void SetWillAttackPlayerWithCops(ePedType gangID, bool bAttackPlayerWithCops);
};
