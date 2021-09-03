/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

struct tMusicTrackHistory {
    char m_indices[20];
};

class CAERadioTrackManager {
public:
    char   field_0;
    char   field_1;
    char   field_2;
    char   field_3;
    char   field_4;
    char   field_5;
    char   field_6;
    bool   m_bRadioAutoSelect;
    char   field_8[14];
    uint8  m_nMonthDay;
    uint8  m_nClockHours;
    int32  m_anPlayerStats[14];
    int32  field_50;
    uint32 m_nTimeToDisplayRadioName;
    int32  field_58;
    int32  field_5C;
    int32  field_60;
    int32  field_64;
    int32  field_68;
    int32  m_nStationsListed;
    int32  m_nStationsListDown;
    int32  field_74;
    int32  field_78;
    int32  field_7C;
    int32  field_80;
    int32  field_84;
    char   field_88;
    char   field_89[19];
    int32  field_9C;
    int32  field_A0;
    int32  field_A4;
    int32  field_A8;
    char   field_AC;
    char   m_nCurrentRadioStation;
    char   field_AE;
    char   field_AF[10];
    char   field_B9;
    char   field_BA;
    char   field_BB[5];
    char   field_C0;
    char   field_C1;
    char   field_C2[2];
    char   field_C4;
    char   field_C5[25];
    char   field_DE[10];
    char   field_E8;
    char   m_nRadioStationState;
    bool   m_bStereoActive;
    char   field_EB;
    int32  field_EC;
    char   field_F0;
    char   field_F1;
    char   field_F2;
    char   field_F3[5];
    char   field_F8;
    char   field_F9[15];
    char   field_108;
    char   field_109[3];
    int32  field_10C[143];
    char   field_348[32];
    int32  field_368;
    char   field_36C;
    char   field_36D[3];

public:
    bool  IsVehicleRadioActive();
    char* GetRadioStationName(int8 id);

    // 11 structures
    static tMusicTrackHistory* m_nMusicTrackIndexHistory;
};

VALIDATE_SIZE(CAERadioTrackManager, 0x370);
