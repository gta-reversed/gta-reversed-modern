/*
    Plugin-SDK (Grand Theft Auto San Andreas) file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Vector.h"

class CColDisk {
public:
    CVector m_vecStart;
    float   m_fStartRadius;
    uint8   m_nMaterial;
    uint8   m_nPiece;
    uint8   m_nLighting;
    char    _pad13;

public:
    CVector m_vecEnd;
    float   m_fEndRadius;

    void Set(float startRadius, CVector const& start, CVector const& end, float endRadius, uint8 material, uint8 pieceType, uint8 lighting);
};

VALIDATE_SIZE(CColDisk, 0x24);