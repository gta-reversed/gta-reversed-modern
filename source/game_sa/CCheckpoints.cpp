#include "StdInc.h"
#include "CCheckpoints.h"

uint32_t& CCheckpoints::NumActiveCPts = *(uint32_t*)0xC7C6D4;
CCheckpoint (&CCheckpoints::m_aCheckPtArray)[MAX_NUM_CHECKPOINTS] = *(CCheckpoint(*)[MAX_NUM_CHECKPOINTS])0xC7F158;

void CCheckpoints::InjectHooks() {
    // ReversibleHooks::Install("CCheckpoints", "Init", 0x722880, &CCheckpoints::Init);
    // ReversibleHooks::Install("CCheckpoints", "Shutdown", 0x7228F0, &CCheckpoints::Shutdown);
    // ReversibleHooks::Install("CCheckpoints", "UpdatePos", 0x722900, &CCheckpoints::UpdatePos);
    // ReversibleHooks::Install("CCheckpoints", "SetHeading", 0x722970, &CCheckpoints::SetHeading);
    // ReversibleHooks::Install("CCheckpoints", "Update", 0x7229C0, &CCheckpoints::Update);
    // ReversibleHooks::Install("CCheckpoints", "PlaceMarker", 0x722C40, &CCheckpoints::PlaceMarker);
    // ReversibleHooks::Install("CCheckpoints", "DeleteCP", 0x722FC0, &CCheckpoints::DeleteCP);
    // ReversibleHooks::Install("CCheckpoints", "Render", 0x726060, &CCheckpoints::Render);
}

// 0x722880
void CCheckpoints::Init() {
    plugin::Call<0x722880>();
}

// 0x7228F0
void CCheckpoints::Shutdown() {
    plugin::Call<0x7228F0>();
}

// 0x722900
void CCheckpoints::UpdatePos(uint32_t id, CVector& posn) {
    plugin::Call<0x722900, uint32_t, CVector&>(id, posn);
}

// 0x722970
void CCheckpoints::SetHeading(uint32_t id, float angle) {
    plugin::Call<0x722970, uint32_t, float>(id, angle);
}

// 0x7229C0
void CCheckpoints::Update() {
    plugin::Call<0x7229C0>();
}

// 0x722C40
CCheckpoint* CCheckpoints::PlaceMarker(uint32_t id, uint16_t type, CVector& posn, CVector& dir, float size, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha,
                                       uint16_t pulsePeriod, float pulseFraction, int16_t rotateRate) {
    return plugin::CallAndReturn<CCheckpoint*, 0x722C40, uint32_t, uint16_t, CVector&, CVector&, float, uint8_t, uint8_t, uint8_t, uint8_t, uint16_t, float, int16_t>(
        id, type, posn, dir, size, red, green, blue, alpha, pulsePeriod, pulseFraction, rotateRate);
}

// 0x722FC0
void CCheckpoints::DeleteCP(uint32_t id, uint16_t type) {
    plugin::Call<0x722FC0, uint32_t, uint16_t>(id, type);
}

// 0x726060
void CCheckpoints::Render() {
    plugin::Call<0x726060>();
}
