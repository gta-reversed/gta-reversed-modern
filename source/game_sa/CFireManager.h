#pragma once

#include "CFire.h"

class CFireManager {
public:
    CFire  m_aFires[60];
    uint32 m_nMaxFireGenerationsAllowed;

public:
    CFireManager();
    ~CFireManager();

    void Init();
    void Shutdown();

    uint32 GetNumOfNonScriptFires();
    uint32 GetNumOfFires();
    CFire* FindNearestFire(const CVector& point, bool bCheckWasExtinguished, bool bCheckWasCreatedByScript);
    bool PlentyFiresAvailable();

    void ExtinguishPoint(CVector point, float fRadiusSq);
    bool ExtinguishPointWithWater(CVector point, float fRadiusSq, float fFireSize);

    bool IsScriptFireExtinguished(int16 id);

    void RemoveScriptFire(uint16_t fireID);
    void RemoveAllScriptFires();
    void ClearAllScriptFireFlags();

    void SetScriptFireAudio(int16 fireID, bool bFlag);
    const CVector& GetScriptFireCoords(int16 fireID);
    uint32 GetNumFiresInRange(const CVector& point, float fRadiusSq);
    uint32 GetNumFiresInArea(float minX, float minY, float minZ, float maxX, float maxY, float maxZ);

    void DestroyAllFxSystems();
    void CreateAllFxSystems();

    CFire* GetNextFreeFire(bool bMayUseScriptFire);
    CFire* StartFire(CVector pos, float size, uint8 unused, CEntity* creator, uint32 nTimeToBurn, int8 nGenerations, uint8 unused_);
    CFire* StartFire(CEntity* target, CEntity* creator, float size, uint8 unused, uint32 lifetime, int8 numGenerations);
    int32 StartScriptFire(const CVector& pos, CEntity* pTarget, float _fUnused, uint8 _nUnused, int8 nGenerations, int32 nStrength);

    void Update();

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CFireManager* Destructor();
    CFireManager* Constructor();

    // NOTSA
    CFire& Get(size_t idx) { return m_aFires[idx]; }
    auto GetIndexOf(CFire const* fire) const { return std::distance(std::begin(m_aFires), fire); }
};
VALIDATE_SIZE(CFireManager, 0x964);

extern CFireManager& gFireManager;
