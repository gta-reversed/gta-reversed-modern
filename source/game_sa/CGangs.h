/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "ePedType.h"
#include "CGangInfo.h"

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
