#include "StdInc.h"

CFireManager& gFireManager = *reinterpret_cast<CFireManager*>(0xB71F80);

void CFireManager::InjectHooks() {
    //ReversibleHooks::Install("CFireManager", "Constructor", 0x539DA0, &CFireManager::Constructor);
    //ReversibleHooks::Install("CFireManager", "Destructor", 0x538BB0, &CFireManager::Destructor);
    ReversibleHooks::Install("CFireManager", "Init", 0x538BC0, &CFireManager::Init);
    ReversibleHooks::Install("CFireManager", "GetNumOfNonScriptFires", 0x538F10, &CFireManager::GetNumOfNonScriptFires);
    ReversibleHooks::Install("CFireManager", "FindNearestFire", 0x538F40, &CFireManager::FindNearestFire);
    ReversibleHooks::Install("CFireManager", "PlentyFiresAvailable", 0x539340, &CFireManager::PlentyFiresAvailable);
    //ReversibleHooks::Install("CFireManager", "ExtinguishPoint", 0x539450, &CFireManager::ExtinguishPoint);
    //ReversibleHooks::Install("CFireManager", "ExtinguishPointWithWater", 0x5394C0, &CFireManager::ExtinguishPointWithWater);
    //ReversibleHooks::Install("CFireManager", "IsScriptFireExtinguished", 0x5396E0, &CFireManager::IsScriptFireExtinguished);
    ReversibleHooks::Install("CFireManager", "RemoveScriptFire", 0x539700, &CFireManager::RemoveScriptFire);
    ReversibleHooks::Install("CFireManager", "RemoveAllScriptFires", 0x539720, &CFireManager::RemoveAllScriptFires);
    ReversibleHooks::Install("CFireManager", "ClearAllScriptFireFlags", 0x5397A0, &CFireManager::ClearAllScriptFireFlags);
    ReversibleHooks::Install("CFireManager", "SetScriptFireAudio", 0x5397B0, &CFireManager::SetScriptFireAudio);
    ReversibleHooks::Install("CFireManager", "GetScriptFireCoords", 0x5397E0, &CFireManager::GetScriptFireCoords);
    ReversibleHooks::Install("CFireManager", "GetNumFiresInRange", 0x5397F0, &CFireManager::GetNumFiresInRange);
    ReversibleHooks::Install("CFireManager", "GetNumFiresInArea", 0x539860, &CFireManager::GetNumFiresInArea);
    ReversibleHooks::Install("CFireManager", "DestroyAllFxSystems", 0x539D10, &CFireManager::DestroyAllFxSystems);
    ReversibleHooks::Install("CFireManager", "CreateAllFxSystems", 0x539D50, &CFireManager::CreateAllFxSystems);
    ReversibleHooks::Install("CFireManager", "Shutdown", 0x539DD0, &CFireManager::Shutdown);
    ReversibleHooks::Install("CFireManager", "GetNextFreeFire", 0x539E50, &CFireManager::GetNextFreeFire);
    //ReversibleHooks::Install("CFireManager", "StartFire", 0x539F00, &CFireManager::StartFire);
    //ReversibleHooks::Install("CFireManager", "StartFire", 0x53A050, &CFireManager::StartFire);
    //ReversibleHooks::Install("CFireManager", "StartScriptFire", 0x53A270, &CFireManager::StartScriptFire);
    //ReversibleHooks::Install("CFireManager", "Update", 0x53AF00, &CFireManager::Update);
}

CFireManager::CFireManager() {
}

CFireManager::~CFireManager() {
}

CFireManager* CFireManager::Destructor() {
    this->CFireManager::~CFireManager();
    return this;
}

CFireManager* CFireManager::Constructor() {
    this->CFireManager::CFireManager();
    return this;
}

void CFireManager::Init() {
    for (auto& fire : m_aFires) {
        fire.Initialise();
    }
    m_nMaxFireGenerationsAllowed = 1'000'000 - 1;
}

uint32_t CFireManager::GetNumOfNonScriptFires() {
    uint32_t c = 0;
    for (auto& fire : m_aFires)
        if (fire.m_nFlags.bActive && !fire.m_nFlags.bCreatedByScript)
            c++;
    return c;
}

CFire * CFireManager::FindNearestFire(CVector const& point, bool bCheckIsBeingExtinguished, bool bCheckWasCreatedByScript) {
    float fNearestDist2DSq = std::numeric_limits<float>::max();
    CFire* pNearestFire;
    for (auto& fire : m_aFires) {
        if (!fire.IsActive())
            continue;
        if (bCheckWasCreatedByScript && fire.IsScript())
            continue;
        if (bCheckIsBeingExtinguished && fire.IsBeingExtinguished())
            continue;
        if (fire.m_pEntityTarget && fire.m_pEntityTarget->IsPed())
            continue;
        const float fDist2DSq = (fire.m_vecPosition - point).SquaredMagnitude2D();
        if (fDist2DSq < fNearestDist2DSq) {
            fNearestDist2DSq = fDist2DSq;
            pNearestFire = &fire;
        }
    }
    return pNearestFire;
}

bool CFireManager::PlentyFiresAvailable() {
    uint32_t c = 0;
    for (auto& fire : m_aFires) {
        if (fire.m_nFlags.bActive) 
            c++;
        if (c >= 6)
            return true;
    }
    return false;
}

void CFireManager::ExtinguishPoint(CVector point, float fRadiusSq) {
    return plugin::CallMethod<0x539450, CFireManager*, CVector, float>(this, point, fRadiusSq);
}

bool CFireManager::ExtinguishPointWithWater(CVector point, float fRadiusSq, float fFireSize) {
    return plugin::CallMethodAndReturn<bool, 0x5394C0, CFireManager*, CVector, float, float>(this, point, fRadiusSq, fFireSize);
}

bool CFireManager::IsScriptFireExtinguished(short id) {
    return plugin::CallMethodAndReturn<bool, 0x5396E0, CFireManager*, short>(this, id);
}

void CFireManager::RemoveScriptFire(uint16_t fireID) {
    CFire& fire = Get(fireID);
    if (fire.m_nFlags.bCreatedByScript) {
        fire.m_nFlags.bCreatedByScript = false;
        fire.Extinguish();
    }
}

void CFireManager::RemoveAllScriptFires() {
    for (auto& fire : m_aFires) {
        if (fire.m_nFlags.bCreatedByScript) {
            fire.m_nFlags.bCreatedByScript = false;
            fire.Extinguish();
        }
    }
}

void CFireManager::ClearAllScriptFireFlags() {
    for (auto& fire : m_aFires) {
        fire.m_nFlags.bCreatedByScript = false;
    }
}

void CFireManager::SetScriptFireAudio(short fireID, bool bFlag) {
    Get(fireID).m_nFlags.bMakesNoise = bFlag;
}

const CVector& CFireManager::GetScriptFireCoords(short fireID) {
    return Get(fireID).m_vecPosition;
}

uint32_t CFireManager::GetNumFiresInRange(const CVector& point, float fRadius) {
    uint32_t c = 0;
    for (auto& fire : m_aFires) {
        if (fire.IsActive() && !fire.IsScript()) {
            if ((fire.m_vecPosition - point).Magnitude2D() <= fRadius) {
                c++;
            }
        }
    }
    return c;
}

uint32_t CFireManager::GetNumFiresInArea(float minX, float minY, float minZ, float maxX, float maxY, float maxZ) {
    CBoundingBox boundingBox{
        {minX, minY, minZ},
        {maxX, maxY, maxZ}
    };
    uint32_t c = 0;
    for (auto& fire : m_aFires) {
        if (fire.IsActive() && !fire.IsScript()) {
            if (boundingBox.IsPointWithin(fire.m_vecPosition)) {
                c++;
            }
        }
    }
    return c;
}
 
void CFireManager::DestroyAllFxSystems() {
    for (auto& fire : m_aFires) {
        if (fire.IsActive()) {
            fire.DestroyFx();
        }
    }
}

void CFireManager::CreateAllFxSystems() {
    for (auto& fire : m_aFires) {
        if (fire.IsActive()) {
            fire.CreateFxSysForStrength(fire.m_vecPosition, nullptr);
        }
    }
}

void CFireManager::Shutdown() {
    for (auto& fire : m_aFires) {
        fire.m_nFlags.bCreatedByScript = false;
        if (fire.IsActive()) {
            fire.Extinguish();
        }
    }
}

CFire * CFireManager::GetNextFreeFire(uint8_t bUnused) {
    if (!bUnused) /* called unused, because the only place this is called from doesn't use it  */
        return nullptr;
    for (auto& fire : m_aFires) {
        if (!fire.IsActive() && !fire.IsScript()) {
            return &fire;
        }
    }

    // At this point there are no inactive fires in the pool 
    // Must recycle a script / first generation fire         
    CFire* pFire = std::begin(m_aFires);
    for (;;) {
        if (pFire->IsFirstGen() || pFire->IsScript())
            break; /* found */
        if (pFire == std::end(m_aFires))
            return nullptr;
    }
    pFire->m_nFlags.bCreatedByScript = false;
    pFire->Extinguish();
    return pFire;
}

CFire * CFireManager::StartFire(CVector pos, float size, uint8_t unused, CEntity * creator, uint time, signed char numGenerations, uint8_t unused_) {
    return plugin::CallMethodAndReturn<CFire *, 0x539F00, CFireManager*, CVector, float, uint8_t, CEntity *, uint, signed char, uint8_t>(this, pos, size, unused, creator, time, numGenerations, unused_);
}

CFire * CFireManager::StartFire(CEntity * target, CEntity * creator, float size, uint8_t unused, uint lifetime, signed char numGenerations) {
    return plugin::CallMethodAndReturn<CFire *, 0x53A050, CFireManager*, CEntity *, CEntity *, float, uint8_t, uint, signed char>(this, target, creator, size, unused, lifetime, numGenerations);
}

int32_t CFireManager::StartScriptFire(CVector const& pos, CEntity * pTarget, float _fUnused, uint8_t _nUnused, signed char nAllowedGenerations, int32_t nStrength) {
    return plugin::CallMethodAndReturn<int32_t, 0x53A270, CFireManager*, CVector const&, CEntity *, float, uint8_t, signed char, int32_t>(this, pos, pTarget, _fUnused, _nUnused, nAllowedGenerations, nStrength);
}

void CFireManager::Update() {
    return plugin::CallMethod<0x53AF00, CFireManager*>(this);
}
