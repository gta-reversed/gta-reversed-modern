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

class  CTheCarGenerators {
public:
     static unsigned char &GenerateEvenIfPlayerIsCloseCounter;
     static unsigned char &ProcessCounter;
     static unsigned int &NumOfCarGenerators;
     static CSpecialPlateHandler &m_SpecialPlateHandler;
     static CCarGenerator *CarGeneratorArray; // static CCarGenerator CarGeneratorArray[500]

    //! return index of CarGenerator in CTheCarGenerators::CarGeneratorArray
     static signed int CreateCarGenerator(float x, float y, float z, float angle, int modelId, short color1, short color2, unsigned char forceSpawn, unsigned char alarm_chances, unsigned char doorLock_chances, unsigned short minDelay, unsigned short maxDelay, unsigned char iplId, unsigned char bOwnedbyplayer);
     static void Init();
     static void Load();
     static void Process();
     static void RemoveCarGenerators(unsigned char IplID);
     static void Save();
};

//#include "meta/meta.CTheCarGenerators.h"
