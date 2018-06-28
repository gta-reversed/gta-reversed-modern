/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CVector.h"

#pragma pack(push, 1)
class  CFileCarGenerator {
public:
    CVector m_vecPosn;
    float m_fAngle;
    unsigned int m_nModelId;
    unsigned short m_nColor1;
private:
    unsigned char _pad16[2];
public:
    unsigned short m_nColor2;
private:
    unsigned char _pad1A[2];
public:
    unsigned char m_nFlags;
private:
    unsigned char _pad1D[3];
public:
    unsigned char m_nAlarm;
private:
    unsigned char _pad21[3];
public:
    unsigned char m_nDoorLock;
private:
    unsigned char _pad25[3];
public:
    unsigned short m_nMinDelay;
private:
    unsigned char _pad2A[2];
public:
    unsigned short m_nMaxDelay;
};
#pragma pack(pop)

VALIDATE_SIZE(CFileCarGenerator, 0x2E);
