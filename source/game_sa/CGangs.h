/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CPed.h"
#include "CGangInfo.h"

enum  eGangID {
    GANG_BALLAS = 0,
    GANG_GROVE = 0x1,
    GANG_VAGOS = 0x2,
    GANG_RIFA = 0x3,
    GANG_DANANGBOYS = 0x4,
    GANG_MAFIA = 0x5,
    GANG_TRIAD = 0x6,
    GANG_AZTECAS = 0x7,
    GANG_UNUSED1 = 0x8, //!< RUSSIAN_MAFIA
    GANG_UNUSED2 = 0x9 //!< BIKERS
};

class  CGangs {
public:
     static bool(&GangAttackWithCops)[16]; // static bool GangAttackWithCops[16]
     static CGangInfo(&Gang)[10]; // static CGangInfo Gang[10]

     static signed int ChooseGangPedModel(short gangID);
    //! unused
     static bool GetWillAttackPlayerWithCops(ePedType gangID);
     static void Initialise();
     static void Load();
     static void Save();
    //! unused
     static void SetGangPedModelOverride(short gangID, signed char PedModelOverride);
     static void SetGangWeapons(short gangID, int weapID1, int weapID2, int weapID3);
    //! unused
     static void SetWillAttackPlayerWithCops(ePedType gangID, bool bAttackPlayerWithCops);
};

//#include "meta/meta.CGangs.h"
