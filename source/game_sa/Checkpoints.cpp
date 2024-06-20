#include "StdInc.h"

#include "Checkpoints.h"
#include "Checkpoint.h"

void CCheckpoints::InjectHooks() {
    RH_ScopedClass(CCheckpoints);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(Init, 0x722880);
    RH_ScopedInstall(Shutdown, 0x7228F0);
    RH_ScopedInstall(Update, 0x7229C0);
    RH_ScopedInstall(Render, 0x726060);
    RH_ScopedInstall(PlaceMarker, 0x722C40, { .reversed = false });
    RH_ScopedInstall(DeleteCP, 0x722FC0);
    RH_ScopedInstall(SetHeading, 0x722970);
    RH_ScopedInstall(UpdatePos, 0x722900);
}

// 0x722880
void CCheckpoints::Init() {
    for (auto& checkpoint : m_aCheckPtArray) {
        checkpoint.Init();
    }
    NumActiveCPts = 0;
}

// 0x7228F0
void CCheckpoints::Shutdown() {
    // NOP
}

// NOTSA
CCheckpoint* CCheckpoints::FindById(uint32 id) {
    for (auto& checkpoint : m_aCheckPtArray) {
        if (checkpoint.m_ID == id) {
            return &checkpoint;
        }
    }
    return nullptr;
}

// 0x722970
void CCheckpoints::SetHeading(uint32 id, float angle) {
    if (auto* checkpoint = FindById(id)) {
        checkpoint->m_Fwd.x = std::cos(DegreesToRadians(angle));
        checkpoint->m_Fwd.y = std::sin(DegreesToRadians(angle));
        checkpoint->m_Fwd.Normalise();
    }
}

// 0x7229C0
void CCheckpoints::Update() {
    rng::for_each(m_aCheckPtArray, &CCheckpoint::Update);
}

// 0x722C40
CCheckpoint* CCheckpoints::PlaceMarker(uint32 id, uint16 type,
                                       CVector& posn, CVector& direction,
                                       float size,
                                       uint8 red, uint8 green, uint8 blue, uint8 alpha,
                                       uint16 pulsePeriod,
                                       float pulseFraction, int16 rotateRate
) {
    return plugin::CallAndReturn<CCheckpoint*, 0x722C40, uint32, uint16, CVector&, CVector&, float, uint8, uint8, uint8, uint8, uint16, float, uint16>(id, type, posn, direction, size, red, green, blue, alpha, pulsePeriod, pulseFraction, rotateRate);
}

// 0x722900
void CCheckpoints::UpdatePos(uint32 id, CVector& posn) {
    if (const auto cp = FindById(id)) {
        cp->SetPosition(posn);
    }
}

// 0x722FC0
void CCheckpoints::DeleteCP(uint32 id, uint16 type) {
    for (auto& cp : m_aCheckPtArray) {
        if (cp.m_IsUsed && cp.m_ID == id && cp.m_Type == (eCheckpointType)type) {
            cp.MarkAsDeleted();
        }
    }
}

// 0x726060
void CCheckpoints::Render() {
    ZoneScoped;

    for (auto& checkpoint : m_aCheckPtArray) {
        if (checkpoint.m_IsUsed) {
            checkpoint.Render();
        }
    }
    RwRenderStateSet(rwRENDERSTATECULLMODE, RWRSTATE(rwCULLMODECULLBACK));
}
