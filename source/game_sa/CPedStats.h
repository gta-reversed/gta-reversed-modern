#pragma once

#include "ePedStats.h"

struct CPedStat {
    unsigned int   m_nId;
    char           m_acName[24];
    float          m_fFleeDistance;
    float          m_fHeadingChangeRate;
    unsigned char  m_nFear;
    unsigned char  m_nTemper;
    unsigned char  m_nLawfulness;
    unsigned char  m_nSexiness;
    float          m_fAttackStrength;
    float          m_fDefendWeakness;
    short          m_wShootingRate;
    char           m_nDefaultDecisionMaker;
    char           _pad;
};

VALIDATE_SIZE(CPedStat, 0x34);

class CPedStats {
public:
    static CPedStat*& ms_apPedStats;

public:
    static void InjectHooks();

    static void Initialise();
    static void Shutdown();
    static void LoadPedStats();
    static ePedStats GetPedStatType(const char* statName);
    static CPedStat* GetPedStatInfo(const char* statName);
    static CPedStat* GetPedStatByArrayIndex(unsigned int statIndex);
    static void FindIndexWithPedStat(void* a1);
};
