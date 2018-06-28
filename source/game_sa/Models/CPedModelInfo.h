/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "CClumpModelInfo.h"

class  CPedModelInfo : public CClumpModelInfo {
public:
    int m_nAnimType;
    unsigned int m_nPedType;
    unsigned int m_nStatType;
    unsigned short m_nCarsCanDriveMask;
    unsigned short m_nPedFlags;
    CColModel *m_pHitColModel;
    unsigned char m_nRadio1;
    unsigned char m_nRadio2;
    unsigned char m_nRace;
private:
    char __pad;
public:
    short m_nPedAudioType;
    short m_nVoice1;
    short m_nVoice2;
    short m_nVoiceId;
};

VALIDATE_SIZE(CPedModelInfo, 0x44);