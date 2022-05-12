/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

class FxInfoManager_c {
public:
    uint32 m_nNumInfos;
    void*  m_pInfos;
    uint8  m_nFirstMovementInfo;
    uint8  m_nFirstRenderInfo;
    char   _padA[2];
    int16  m_nLodStart;
    int16  m_nLodEnd;
    bool   m_bHasFlatParticleEmitter;
    bool   m_bHasHeatHazeParticleEmitter;
    char   field_12;
    char   field_13;
};

VALIDATE_SIZE(FxInfoManager_c, 0x14);