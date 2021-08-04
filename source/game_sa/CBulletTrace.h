/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "CVector.h"

class  CBulletTrace {
public:
    CVector       m_vecStart;
    CVector       m_vecEnd;
    bool          m_bExists;
private:
    char _pad19[3];
public:
    uint32_t           m_nCreationTime;
    unsigned int  m_nLifeTime;
    float         m_fRadius;
    unsigned char m_nTransparency;
private:
    char _pad29[3];
public:

    void Update();

    // NOTSA
    CVector GetDirection() const noexcept { return m_vecEnd - m_vecStart; }
    uint32_t GetRemainingLifetime() const noexcept { return CTimer::m_snTimeInMilliseconds - m_nCreationTime; }
};

VALIDATE_SIZE(CBulletTrace, 0x2C);
