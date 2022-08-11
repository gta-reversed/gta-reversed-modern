/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

class CGangInfo {
public:
    int8  m_nPedModelOverride;
    std::array<int32, 3> m_nGangWeapons;

    CGangInfo() { // 0x5DE520
        m_nPedModelOverride = -1;
        m_nGangWeapons.fill(0);
    };
    ~CGangInfo() = default; // 0x5DE540
};

VALIDATE_SIZE(CGangInfo, 0x10);
