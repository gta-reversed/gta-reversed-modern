/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "CompressedVector.h"

#include "CVector.h"

struct CFileCarGenerator {
    CVector m_vecPosn;
    float   m_fAngle;
    int     m_nModelId;
    int     m_nPrimaryColor;
    int     m_nSecondaryColor;
    union {
        struct {
            unsigned int m_bForceSpawn : 1;            // & 1
            unsigned int m_bIgnorePopulationLimit : 1; // & 2
        };
        unsigned int m_nFlags;
    };
    int     m_nAlarmChance;
    int     m_nDoorLockChance;
    int     m_nMinDelay;
    int     m_nMaxDelay;
};

VALIDATE_SIZE(CFileCarGenerator, 0x30);

class CCarGenerator {
public:
    signed short     m_nModelId;
    signed char      m_nPrimaryColor;
    signed char      m_nSecondaryColor;
    CompressedVector m_vecPosn;
    char             m_nAngle;
    unsigned char    m_nAlarmChance;    // in percentage 0-100
    unsigned char    m_nDoorLockChance; // in percentage 0-100

    union {
        struct {
            unsigned char bWaitUntilFarFromPlayer : 1;
            unsigned char bHighPriority : 1;
            unsigned char bActive : 1;
            unsigned char bPlayerHasAlreadyOwnedCar : 1;
            unsigned char bIgnorePopulationLimit : 1;
        };
        unsigned char m_nFlags;
    };
    unsigned short   m_nMinDelay;
    unsigned short   m_nMaxDelay;
    // char             _pad12[2];
    unsigned int     m_nNextGenTime;
    signed short     m_nVehicleHandle;
    signed short     m_nGenerateCount; // (0) Don't Spawn , (1 - 32767) Spawn X number of times , (-1) Always Spawn.
    unsigned char    m_nIplId;
    bool             m_bIsUsed;
    // char             _pad1E[2];

public:
    static bool& m_bHotdogVendorPositionOffsetInitialized;
    static CVector& m_HotdogVendorPositionOffset;

public:
    static void InjectHooks();

    bool CheckForBlockage(int modelId);
    bool CheckIfWithinRangeOfAnyPlayers();
    void DoInternalProcessing();
    void Process();
    void Setup(const CVector& posn, float angle, int modelId, short color1, short color2, uint8_t bForceSpawn,
               uint8_t alarmChance, uint8_t doorLockChance, uint16_t minDelay, uint16_t maxDelay,
               uint8_t iplId, bool ignorePopulationLimit);
    void SwitchOff();
    void SwitchOn();

    static unsigned int CalcNextGen();
};

VALIDATE_SIZE(CCarGenerator, 0x20);
