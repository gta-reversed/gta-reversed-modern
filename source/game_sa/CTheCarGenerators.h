/*
Plugin-SDK (Grand Theft Auto San Andreas) header file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "CSpecialPlateHandler.h"
#include "CCarGenerator.h"

static constexpr int NUM_CAR_GENERATORS = 500;

class CTheCarGenerators {
public:
    static unsigned char& GenerateEvenIfPlayerIsCloseCounter;
    static unsigned char& ProcessCounter;
    static unsigned int& NumOfCarGenerators;
    static CSpecialPlateHandler& m_SpecialPlateHandler;
    static CCarGenerator(&CarGeneratorArray)[NUM_CAR_GENERATORS];

public:
    static void InjectHooks();

    static signed int CreateCarGenerator(CVector posn, float angle, int modelId, short color1, short color2, uchar forceSpawn, uchar alarmChances, uchar doorLockChances,
                                         ushort minDelay, ushort maxDelay, uchar iplId, bool ignorePopulationLimit);
    static void Init();
    static void Load();
    static void Process();
    static void RemoveCarGenerators(unsigned char IplID);
    static void Save();

    static CCarGenerator* Get(unsigned short index);
    static int GetIndex(CCarGenerator* pCarGen);
};
