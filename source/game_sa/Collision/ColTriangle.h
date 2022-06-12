/*
    Plugin-SDK file
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
    uint8 m_nMaterial; // todo: material aka eSurfaceType
    uint8 m_nLight;

    CColTriangle() = default;
    CColTriangle(uint16 a, uint16 b, uint16 c, uint8 material, uint8 light) :
        m_nVertA(a),
        m_nVertB(b),
        m_nVertC(c),
        m_nMaterial(material),
        m_nLight(light)
    {
    }
};

VALIDATE_SIZE(CColTriangle, 8);
