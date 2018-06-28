/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"

struct  tMusicTrackHistory {
    char m_indices[20];
};

class  CAERadioTrackManager {
public:
    char field_0;
    char field_1;
    char field_2;
    char field_3;
    char field_4;
    char field_5;
    char field_6;
    bool          m_bRadioAutoSelect;
    char field_8[14];
    unsigned char m_nMonthDay;
    unsigned char m_nClockHours;
    int           m_anPlayerStats[14];
    int field_50;
    unsigned int  m_nTimeToDisplayRadioName;
    int field_58;
    int field_5C;
    int field_60;
    int field_64;
    int field_68;
    int           m_nStationsListed;
    int           m_nStationsListDown;
    int field_74;
    int field_78;
    int field_7C;
    int field_80;
    int field_84;
    char field_88;
    char field_89[19];
    int field_9C;
    int field_A0;
    int field_A4;
    int field_A8;
    char field_AC;
    char          m_nCurrentRadioStation;
    char field_AE;
    char field_AF[10];
    char field_B9;
    char field_BA;
    char field_BB[5];
    char field_C0;
    char field_C1;
    char field_C2[2];
    char field_C4;
    char field_C5[25];
    char field_DE[10];
    char field_E8;
    char          m_nRadioStationState;
    bool          m_bStereoActive;
    char field_EB;
    int field_EC;
    char field_F0;
    char field_F1;
    char field_F2;
    char field_F3[5];
    char field_F8;
    char field_F9[15];
    char field_108;
    char field_109[3];
    int field_10C[143];
    char field_348[32];
    int field_368;
    char field_36C;
    char field_36D[3];

    bool IsVehicleRadioActive();
    char *GetRadioStationName(signed char id);

    // 11 structures
    static tMusicTrackHistory *m_nMusicTrackIndexHistory;
};

VALIDATE_SIZE(CAERadioTrackManager, 0x370);
