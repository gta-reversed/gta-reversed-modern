/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"

class  CQueuedMode {
public:
    unsigned short m_nMode;
    float m_fDuration;
    unsigned short m_nMinZoom;
    unsigned short m_nMaxZoom;
};

VALIDATE_SIZE(CQueuedMode, 0xC);
