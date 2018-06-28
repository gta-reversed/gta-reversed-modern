/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "CCheckpoint.h"

extern unsigned int MAX_NUM_CHECKPOINTS; // default 32

class  CCheckpoints {
public:
    static unsigned int &NumActiveCPts; // not used, only initialised (0)
    static CCheckpoint *m_aCheckPtArray; // static CCheckpoint m_aCheckPtArray[32]

    static void DeleteCP(unsigned int id, unsigned short type);
    static void Init();
    static CCheckpoint* PlaceMarker(unsigned int id, unsigned short type, CVector& posn, CVector& direction, float size, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha, unsigned short pulsePeriod, float pulseFraction, short rotateRate);
    static void Render();
    static void SetHeading(unsigned int id, float angle);
    // dummy function
    static void Shutdown();
    static void Update();
    static void UpdatePos(unsigned int id, CVector& posn);
};