/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

class CColTriangle {
public:
    union {
        struct {
            uint16 m_nVertA; // vertex index in vertices array
            uint16 m_nVertB; // vertex index in vertices array
            uint16 m_nVertC; // vertex index in vertices array
        };
        uint16 m_vertIndices[3];
    };
    uint8 m_nMaterial;
    uint8 m_nLight;
};

VALIDATE_SIZE(CColTriangle, 8);
