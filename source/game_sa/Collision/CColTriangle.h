/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"

class CColTriangle {
public:
    union {
        struct {
            uint16_t m_nVertA; // vertex index in vertices array
            uint16_t m_nVertB; // vertex index in vertices array
            uint16_t m_nVertC; // vertex index in vertices array
        };
        uint16_t m_vertIndices[3];
    };
    uint8_t m_nMaterial;
    uint8_t m_nLight;
};

VALIDATE_SIZE(CColTriangle, 8);
