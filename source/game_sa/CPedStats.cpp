#include "StdInc.h"

constexpr unsigned short PED_STATS_COUNT = 43;

CPedStat*& CPedStats::ms_apPedStats = *(CPedStat**)0xC0BBEC;

void CPedStats::InjectHooks() {
    ReversibleHooks::Install("CPedStats", "Initialise", 0x5BF9D0, &CPedStats::Initialise);
    ReversibleHooks::Install("CPedStats", "Shutdown", 0x608850, &CPedStats::Shutdown);
    ReversibleHooks::Install("CPedStats", "LoadPedStats", 0x5BB890, &CPedStats::LoadPedStats);
    ReversibleHooks::Install("CPedStats", "GetPedStatType", 0x6088D0, &CPedStats::GetPedStatType);
}

// 0x5BF9D0
void CPedStats::Initialise() {
    ms_apPedStats = new CPedStat[PED_STATS_COUNT]();
    for (unsigned short statIndex = 0; statIndex < PED_STATS_COUNT; statIndex++) {
        ms_apPedStats[statIndex].m_nId = 0;
        ms_apPedStats[statIndex].m_fFleeDistance = 20.0f;
        ms_apPedStats[statIndex].m_fHeadingChangeRate = 15.0f;
        ms_apPedStats[statIndex].m_nFear = 50;
        ms_apPedStats[statIndex].m_nTemper = 50;
        ms_apPedStats[statIndex].m_nLawfulness = 50;
        ms_apPedStats[statIndex].m_nSexiness = 50;
        ms_apPedStats[statIndex].m_fAttackStrength = 1.0f;
        ms_apPedStats[statIndex].m_fDefendWeakness = 1.0f;
        ms_apPedStats[statIndex].m_wShootingRate = 0;
        ms_apPedStats[statIndex].m_nDefaultDecisionMaker = 0;
    }
    LoadPedStats();
    CDecisionMakerTypesFileLoader::LoadDefaultDecisionMaker();
}

// 0x608850
void CPedStats::Shutdown() {
    delete[] ms_apPedStats;
}

// 0x5BB890
void CPedStats::LoadPedStats() {
    unsigned short statIndex = 0;
    FILESTREAM file = CFileMgr::OpenFile("DATA\\PEDSTATS.DAT", "r");
    for (char* line = CFileLoader::LoadLine(file); line; line = CFileLoader::LoadLine(file)) {
        if (!*line || *line == '#') {
            continue;
        }

        char   name[24];
        float  fleeDistance;
        float  headingChangeRate;
        int    fear;
        int    temper;
        int    lawfulness;
        int    sexiness;
        float  attackStrength;
        float  defendWeakness;
        int    shootingRate;
        int    defaultDecisionMaker;

        sscanf(
            line,
            "%s %f %f %d %d %d %d %f %f %d %d",
            name,
            &fleeDistance,
            &headingChangeRate,
            &fear,
            &temper,
            &lawfulness,
            &sexiness,
            &attackStrength,
            &defendWeakness,
            &shootingRate,
            &defaultDecisionMaker
        );

        ms_apPedStats[statIndex].m_nId = statIndex;
        strcpy(ms_apPedStats[statIndex].m_acName, name);
        ms_apPedStats[statIndex].m_fFleeDistance = fleeDistance;
        ms_apPedStats[statIndex].m_fHeadingChangeRate = headingChangeRate;
        ms_apPedStats[statIndex].m_nFear = fear;
        ms_apPedStats[statIndex].m_nTemper = temper;
        ms_apPedStats[statIndex].m_nLawfulness = lawfulness;
        ms_apPedStats[statIndex].m_nSexiness = sexiness;
        ms_apPedStats[statIndex].m_fAttackStrength = attackStrength;
        ms_apPedStats[statIndex].m_fDefendWeakness = defendWeakness;
        ms_apPedStats[statIndex].m_wShootingRate = shootingRate;
        ms_apPedStats[statIndex].m_nDefaultDecisionMaker = defaultDecisionMaker;

        statIndex++;
    }
    CFileMgr::CloseFile(file);
}

// 0x6088D0
ePedStats CPedStats::GetPedStatType(const char* statName) {
  unsigned short statIndex = 0;
  while (strcmp(ms_apPedStats[statIndex].m_acName, statName) != 0) {
    if (++statIndex >= PED_STATS_COUNT)
      return ePedStats::SENSIBLE_GUY;
  }
  return static_cast<ePedStats>(statIndex);
}

// unused
// 0x608860
CPedStat* CPedStats::GetPedStatInfo(const char* statName) {
    for (unsigned short statIndex = 0; statIndex < PED_STATS_COUNT; statIndex++) {
        if (strcmp(ms_apPedStats[statIndex].m_acName, statName) != 0) {
            return &ms_apPedStats[statIndex];
        }
    }
    return nullptr;
}

// unused
// 0x5DE7C0
CPedStat* CPedStats::GetPedStatByArrayIndex(unsigned int statIndex) {
    return &ms_apPedStats[statIndex];
}

// unused
// 0x608940
void CPedStats::FindIndexWithPedStat(void* a1) {
    plugin::Call<0x608940>();
}
