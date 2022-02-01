/*
    Plugin-SDK (Grand Theft Auto San Andreas) file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

class CQueuedMode {
public:
    uint16 m_nMode;
    float  m_fDuration;
    uint16 m_nMinZoom;
    uint16 m_nMaxZoom;
};

VALIDATE_SIZE(CQueuedMode, 0xC);
