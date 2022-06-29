/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Vector.h"

struct tColLighting {
    union {
        struct {
            uint8 day : 4;
            uint8 night : 4;
        };
        uint8 value;
    };

    tColLighting() = default;
    constexpr explicit tColLighting(const uint8 ucLighting) {
        day = ucLighting & 0xF;
        night = (ucLighting >> 4) & 0xF;
    }

    [[nodiscard]] float GetCurrentLighting(float fScale = 0.5F) const;
};
VALIDATE_SIZE(tColLighting, 0x1);

class CColPoint {
public:
    /* https://github.com/multitheftauto/mtasa-blue/blob/master/Client/game_sa/CColPointSA.h */
    CVector      m_vecPoint;
    float        field_C;
    CVector      m_vecNormal;
    float        field_1C;
                                  // col shape 1 info
    eSurfaceType m_nSurfaceTypeA;
    uint8        m_nPieceTypeA;
    tColLighting m_nLightingA;
                                  // col shape 2 info
    eSurfaceType m_nSurfaceTypeB;
    uint8 m_nPieceTypeB;
    tColLighting m_nLightingB;

    char _align0x26[2];

    float m_fDepth;

public:
    CColPoint& operator=(CColPoint const&) = default;
};
VALIDATE_SIZE(CColPoint, 0x2C);
