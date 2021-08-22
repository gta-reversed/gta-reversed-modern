#pragma once

#include <windows.h>

class CVector;

class CSimpleVariablesSaveStructure {
public:
    unsigned int        m_nVersionId;
    char                m_szSaveName[100];
    bool                m_bMissionPackGame;
    char                _pad69[3];
    int                 m_nCurrLevel;
    CVector             m_vecCamPosn;
    unsigned int        m_nMsPerMinute;
    unsigned int        m_nLastClockTick;
    unsigned char       m_nGameMonth;
    unsigned char       m_nGameDays;
    unsigned char       m_nGameHours;
    unsigned char       m_nGameMinutes;
    unsigned char       m_nGameDayOfWeek;
    unsigned char       m_nStoredGameMonth;
    unsigned char       m_nStoredGameMonthDay;
    unsigned char       m_nStoredGameHours;
    unsigned char       m_nStoredGameMinutes;
    bool                m_bClockHasBeenStored;
    short               m_nPadMode;
    bool                m_bHasPlayerCheated;
    char                _pad91[3];
    unsigned int        m_nTimeInMilliseconds;
    float               m_fTimeScale;
    float               m_fTimeStep;
    float               m_fTimeStepNonClipped;
    unsigned int        m_nFrameCounter;
    eWeatherType        m_nOldWeatherType;
    eWeatherType        m_nNewWeatherType;
    eWeatherType        m_nForcedWeatherType;
    char                _padAE[2];
    float               m_fWeatherInterpolationValue;
    unsigned int        m_nWeatherTypeInList;
    float               m_fWeatherRain;
    unsigned int        m_nCameraCarZoom;
    unsigned int        m_nCameraPedZoom;
    int                 m_nCurrArea;
    bool                m_bInvertLook4Pad;
    char                _padC9[3];
    int                 m_nExtraColour;
    bool                m_bExtraColourOn;
    char                _padD1[3];
    int                 m_fExtraColourInter;
    int                 m_nExtraColourWeatherType;
    unsigned int        m_nWaterConfiguration;
    bool                m_bLARiots;
    bool                m_bLARiots_NoPoliceCar;
    char                _padE2[2];
    unsigned int        m_nMaximumWantedLevel;
    unsigned int        m_nMaxChaos;
    bool                m_bFrenchGame;
    bool                m_bGermanGame;
    bool                m_bNastyGame;
    char                _padEF[45];
    char                m_bCineyCamMessageDisplayed;
    char                _pad11D[1];
    SYSTEMTIME          m_systemTime;
    char                _pad12E[2];
    int                 m_nTargetBlipIndex;
    bool                m_bHasDisplayedPlayerQuitEnterCarHelpText;
    bool                m_bAllTaxisNitro;
    bool                m_bProstitutesPayYou;
    char                _pad137;

public:
    static void InjectHooks();

    void Construct();
    void Extract(unsigned int& versionId) const;

};

VALIDATE_SIZE(CSimpleVariablesSaveStructure, 0x138);