/*
Plugin-SDK (Grand Theft Auto San Andreas) header file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CSpecialPlateHandler.h"
#include "CCarGenerator.h"

static constexpr int NUM_CAR_GENERATORS = 500;

class  CTheCarGenerators {
public:
    static unsigned char& GenerateEvenIfPlayerIsCloseCounter;
    static unsigned char& ProcessCounter;
    static unsigned int& NumOfCarGenerators;
    static CSpecialPlateHandler& m_SpecialPlateHandler;
    static CCarGenerator(&CarGeneratorArray)[NUM_CAR_GENERATORS];


    static void InjectHooks();
    //! return index of CarGenerator in CTheCarGenerators::CarGeneratorArray
    static signed int CreateCarGenerator(CVector posn, float angle, int modelId, short color1, short color2, unsigned char forceSpawn, unsigned char alarmChances, unsigned char doorLockChances, unsigned short minDelay, unsigned short maxDelay, unsigned char iplId, unsigned char bIgnorePopulationLimit);
    static void Init();
    static void Load();
    static void Process();
    static void RemoveCarGenerators(unsigned char IplID);
    static void Save();

    //! unused
    static CCarGenerator* Get(unsigned short index);
    static int GetIndex(CCarGenerator* pCarGen);
};



//#include "meta/meta.CTheCarGenerators.h"
