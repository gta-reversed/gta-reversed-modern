#pragma once
#include "PluginBase.h"
#include "CFire.h"


class CFireManager {
public:
    CFire m_aFires[60];
    uint32_t m_nMaxFireGenerationsAllowed;

public:
    static void InjectHooks();

    CFireManager();
    ~CFireManager();

public:
    CFireManager* Destructor();
    CFireManager* Constructor();
public:
    void Init();
    uint32_t GetNumOfNonScriptFires();
    uint32_t GetNumOfFires();
    CFire * FindNearestFire(CVector const& point, bool bCheckWasExtinguished, bool bCheckWasCreatedByScript);
    bool PlentyFiresAvailable();
    void ExtinguishPoint(CVector point, float fRadiusSq);
    bool ExtinguishPointWithWater(CVector point, float fRadiusSq, float fFireSize);
    bool IsScriptFireExtinguished(short id);
    void RemoveScriptFire(uint16_t fireID);
    void RemoveAllScriptFires();
    void ClearAllScriptFireFlags();
    void SetScriptFireAudio(short fireID, bool bFlag);
    const CVector& GetScriptFireCoords(short fireID);
    uint32_t GetNumFiresInRange(const CVector& point, float fRadiusSq);
    uint32_t GetNumFiresInArea(float minX, float minY, float minZ, float maxX, float maxY, float maxZ);
    void DestroyAllFxSystems();
    void CreateAllFxSystems();
    void Shutdown();
    CFire * GetNextFreeFire(bool bMayUseScriptFire);
    CFire * StartFire(CVector pos, float size, uint8_t unused, CEntity * creator, uint32_t nTimeToBurn, uint8_t nGenerations, uint8_t unused_);
    CFire * StartFire(CEntity * target, CEntity * creator, float size, uint8_t unused, uint32_t lifetime, uint8_t numGenerations);
    int32_t StartScriptFire(CVector const& pos, CEntity * pTarget, float _fUnused, uint8_t _nUnused, uint8_t nGenerations, int32_t nStrength);
    void Update();
    CFire& Get(size_t idx) { return m_aFires[idx]; }
    auto GetIndexOf(CFire const* pFire) const { return std::distance(std::begin(m_aFires), pFire); }
};
VALIDATE_SIZE(CFireManager, 0x964);

extern CFireManager& gFireManager;
