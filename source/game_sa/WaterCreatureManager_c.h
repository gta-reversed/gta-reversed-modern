#pragma once
#include "WaterCreature_c.h"

struct WaterCreatureInfo
{
    uint16_t* m_pModelId;
    uint8_t m_nMinCreated;
    uint8_t m_nMaxCreated;
    uint16_t m_wUnkn;
    float m_fMinSpawnDepth;
    float m_fMinDistFromSameCreature;
    float m_fMinDistFromFollowed;
    float m_fMaxDistFromFollowed;
    float m_fMinSpeed;
    float m_fMaxSpeed;
    float m_fMaxHeadingChange;
    float m_fChanceToRandomizeRotation;
    float m_fSpeed;
};
VALIDATE_SIZE(WaterCreatureInfo, 0x2C);

class WaterCreatureManager_c
{
public:
    WaterCreatureManager_c();

public:
    static constexpr int NUM_WATER_CREATURES = 128;
    WaterCreature_c m_aCreatures[NUM_WATER_CREATURES];
    TList_c<WaterCreature_c> m_freeList;
    TList_c<WaterCreature_c> m_createdList;
    int m_nLastCreationCheckTime;

public:
    static void InjectHooks();

    bool Init();
    void Exit();
    int GetRandomWaterCreatureId();
    void TryToFreeUpWaterCreatures(int numToFree);
    bool CanAddWaterCreatureAtPos(int nCreatureType, CVector vecPos);
    void TryToExitGroup(WaterCreature_c* pCreature);
    void Update(float fTimestep);

public:
    static const WaterCreatureInfo& GetCreatureInfo(int nType) { return ms_waterCreatureInfos[nType]; }

public:
    static constexpr int NUM_WATER_CREATURE_INFOS = 7;
    static WaterCreatureInfo(&ms_waterCreatureInfos)[NUM_WATER_CREATURE_INFOS]; // Access using GetCreatureInfo()
    static constexpr float ms_fMaxWaterCreaturesDrawDistance = 60.0F;
    static constexpr float ms_fMaxWaterCreaturesDrawDistanceSquared = ms_fMaxWaterCreaturesDrawDistance * ms_fMaxWaterCreaturesDrawDistance;
};

extern WaterCreatureManager_c& g_waterCreatureMan;
