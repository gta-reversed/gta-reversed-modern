#include "StdInc.h"

#include "SetPieces.h"

void CSetPieces::InjectHooks() {
    RH_ScopedClass(CSetPieces);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(AddOne, 0x499500);
    RH_ScopedInstall(Init, 0x4994F0);
    RH_ScopedInstall(Load, 0x5D3CA0);
    RH_ScopedInstall(Save, 0x5D3C70);
    RH_ScopedInstall(Update, 0x49AA00);
}

// 0x499500
void CSetPieces::AddOne(uint8 type, CVector2D cornerA, CVector2D cornerB, CVector2D spawnCoord1, CVector2D targetCoord1, CVector2D spawnCoord2, CVector2D targetCoord2) {
    if (NumSetPieces >= MAX_SET_PIECES) {
        return;
    }

    auto& sp = aSetPieces[NumSetPieces++];
    sp.m_AreaRect.left   = (cornerA.x >= cornerB.x) ? cornerB.x : cornerA.x;
    sp.m_AreaRect.top    = (cornerA.y >= cornerB.y) ? cornerB.y : cornerA.y;
    sp.m_AreaRect.right  = (cornerA.x <= cornerB.x) ? cornerB.x : cornerA.x;
    sp.m_AreaRect.bottom = (cornerA.x <= cornerB.x) ? cornerB.x : cornerA.x;
    sp.m_SpawnCoord1     = spawnCoord1;
    sp.m_SpawnCoord2     = spawnCoord2;
    sp.m_TargetCoord1    = targetCoord1;
    sp.m_TargetCoord2    = targetCoord2;
}

// 0x4994F0
void CSetPieces::Init() {
    NumSetPieces = 0;
    bDebug       = false;
}

// 0x5D3CA0
bool CSetPieces::Load() {
    LoadDataFromWorkBuffer(NumSetPieces);
    LoadDataFromWorkBuffer(aSetPieces);
    return true;
}

// 0x5D3C70
bool CSetPieces::Save() {
    SaveDataToWorkBuffer(NumSetPieces);
    SaveDataToWorkBuffer(aSetPieces);
    return true;
}

// 0x49AA00
void CSetPieces::Update() {
    ZoneScoped;

    const auto f = CTimer::GetFrameCounter() % 8;
    const auto beg = f * NumSetPieces / 8;
    const auto end = (f + 1) * NumSetPieces / 8;

    for (auto i = beg; i < end; i++) {
        aSetPieces[i].Update();
    }
}
