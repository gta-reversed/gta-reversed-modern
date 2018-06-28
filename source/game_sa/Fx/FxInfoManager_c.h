/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"

class FxInfoManager_c {
public:
    unsigned int m_nNumInfos;
    void *m_pInfos;
    unsigned char m_nFirstMovementInfo;
    unsigned char m_nFirstRenderInfo;
private:
    char _padA[2];
public:
    short m_nLodStart;
    short m_nLodEnd;
    bool m_bHasFlatParticleEmitter;
    bool m_bHasHeatHazeParticleEmitter;
    char field_12;
    char field_13;
};

VALIDATE_SIZE(FxInfoManager_c, 0x14);