/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "CCheckpoint.h"

#define MAX_NUM_CHECKPOINTS 32

class CCheckpoints {
public:
    static uint32_t& NumActiveCPts; // not used, only initialised (0)
    static CCheckpoint(&m_aCheckPtArray)[MAX_NUM_CHECKPOINTS];

public:
    static void InjectHooks();

    static void Init();
    static void Shutdown();
    static void UpdatePos(uint32_t id, CVector& posn);
    static void SetHeading(uint32_t id, float angle);
    static void Update();
    static CCheckpoint* PlaceMarker(uint32_t id, uint16_t type, CVector& posn, CVector& dir, float size, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha, uint16_t pulsePeriod, float pulseFraction, int16_t rotateRate);
    static void DeleteCP(uint32_t id, uint16_t type);
    static void Render();
};
