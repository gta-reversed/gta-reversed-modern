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
    CFire * FindNearestFire(CVector const& point, bool bCheckWasExtinguished, bool bCheckWasCreatedByScript);
    bool PlentyFiresAvailable();
    void ExtinguishPoint(CVector point, float fRadiusSq);
    bool ExtinguishPointWithWater(CVector point, float fRadiusSq, float fFireSize);
    bool IsScriptFireExtinguished(short id);
    void RemoveScriptFire(short fireID);
    void RemoveAllScriptFires();
    void ClearAllScriptFireFlags();
    void SetScriptFireAudio(short fireID, bool bFlag);
    const CVector& GetScriptFireCoords(short fireID);
    uint32_t GetNumFiresInRange(const CVector& point, float fRadiusSq);
    uint32_t GetNumFiresInArea(float minX, float minY, float minZ, float maxX, float maxY, float maxZ);
    void DestroyAllFxSystems();
    int8_t CreateAllFxSystems();
    void Shutdown();
    CFire * GetNextFreeFire(uint8_t bUnused);
    CFire * StartFire(CVector pos, float size, uint8_t unused, CEntity * creator, uint time, signed char numGenerations, uint8_t unused_);
    CFire * StartFire(CEntity * target, CEntity * creator, float size, uint8_t unused, uint lifetime, signed char numGenerations);
    int32_t StartScriptFire(CVector const& pos, CEntity * pTarget, float _fUnused, uint8_t _nUnused, signed char nAllowedGenerations, int32_t nStrength);
    void Update();
};
VALIDATE_SIZE(CFireManager, 0x964);

extern CFireManager& gFireManager;
