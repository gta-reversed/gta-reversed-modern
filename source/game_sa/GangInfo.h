/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

class CGangInfo {
    PLUGIN_NO_DEFAULT_CONSTRUCTION(CGangInfo)

public:
    int8 m_nPedModelOverride;
    int32       m_nGangWeapons[3];
};

VALIDATE_SIZE(CGangInfo, 0x10);
