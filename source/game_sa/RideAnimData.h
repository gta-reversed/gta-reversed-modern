/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

class CRideAnimData {
public:
    uint32 m_nAnimGroup;
    float  m_fSteerAngle;
    float  m_fAnimLean;
    int32  dwordC;
    float  dword10;
    float  m_fHandlebarsAngle;
    float  m_fAnimPercentageState;

    CRideAnimData(uint32 animGroup) :
        m_nAnimGroup(animGroup)
    {}

    CRideAnimData() = default;
};

VALIDATE_SIZE(CRideAnimData, 0x1C);
