/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "CVector.h"

class CColDisk {
public:
    CVector m_vecStart;
    float m_fStartRadius;
    unsigned char m_nMaterial;
    unsigned char m_nPiece;
    unsigned char m_nLighting;
private:
    char _pad13;
public:
    CVector m_vecEnd;
    float m_fEndRadius;

    void Set(float startRadius, CVector const& start, CVector const& end, float endRadius, unsigned char material, unsigned char pieceType, unsigned char lighting);
};

VALIDATE_SIZE(CColDisk, 0x24);