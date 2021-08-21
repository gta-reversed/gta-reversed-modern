#include "StdInc.h"
#include "C3dMarkers.h"

uint8_t& C3dMarkers::m_colDiamond = *(uint8_t*)0x8D5D8B;
CRGBA& C3dMarkers::m_user3dMarkerColor = *(CRGBA*)0xC7C620;
int32_t& C3dMarkers::NumActiveMarkers = *(int32_t*)0xC7C6D8;
RpClump* (&C3dMarkers::m_pRpClumpArray)[e3dMarkerType::MARKER3D_NUM] = *(RpClump * (*)[e3dMarkerType::MARKER3D_NUM])0xC7C6DC;
float& C3dMarkers::m_angleDiamond = *(float*)0xC7C700;
bool& C3dMarkers::IgnoreRenderLimit = *(bool*)0xC7C704;
C3dMarker (&C3dMarkers::m_aMarkerArray)[MAX_NUM_3DMARKERS] = *(C3dMarker(*)[MAX_NUM_3DMARKERS])0xC7DD58;
tUser3dMarker (&C3dMarkers::ms_user3dMarkers)[MAX_NUM_USER_3DMARKERS] = *(tUser3dMarker(*)[MAX_NUM_USER_3DMARKERS])0xC80258;
tDirectionArrow (&C3dMarkers::ms_directionArrows)[MAX_NUM_DIRECTION_ARROWS] = *(tDirectionArrow(*)[MAX_NUM_DIRECTION_ARROWS])0xC802E8;

void C3dMarkers::InjectHooks() {
    // ReversibleHooks::Install("C3dMarkers", "LoadUser3dMarkers", 0x5D42E0, &C3dMarkers::LoadUser3dMarkers);
    // ReversibleHooks::Install("C3dMarkers", "PlaceMarker", 0x725120, &C3dMarkers::PlaceMarker);
    // ReversibleHooks::Install("C3dMarkers", "Render", 0x725040, &C3dMarkers::Render);
    // ReversibleHooks::Install("C3dMarkers", "Init", 0x724E40, &C3dMarkers::Init);
    // ReversibleHooks::Install("C3dMarkers", "User3dMarkersDraw", 0x723240, &C3dMarkers::User3dMarkersDraw);
    // ReversibleHooks::Install("C3dMarkers", "ForceRender", 0x722870, &C3dMarkers::ForceRender);
    // ReversibleHooks::Install("C3dMarkers", "LoadMarker", 0x722810, &C3dMarkers::LoadMarker);
    // ReversibleHooks::Install("C3dMarkers", "Update", 0x7227B0, &C3dMarkers::Update);
    // ReversibleHooks::Install("C3dMarkers", "Shutdown", 0x722710, &C3dMarkers::Shutdown);
    // ReversibleHooks::Install("C3dMarkers", "PlaceMarkerSet", 0x725BA0, &C3dMarkers::PlaceMarkerSet);
    // ReversibleHooks::Install("C3dMarkers", "DirectionArrowsDraw", 0x7211F0, &C3dMarkers::DirectionArrowsDraw);
    // ReversibleHooks::Install("C3dMarkers", "DirectionArrowFindFirstFreeSlot", 0x721120, &C3dMarkers::DirectionArrowFindFirstFreeSlot);
    // ReversibleHooks::Install("C3dMarkers", "DirectionArrowsInit", 0x721100, &C3dMarkers::DirectionArrowsInit);
    // ReversibleHooks::Install("C3dMarkers", "User3dMarkerAtomicCB", 0x7210D0, &C3dMarkers::User3dMarkerAtomicCB);
    // ReversibleHooks::Install("C3dMarkers", "User3dMarkerDeleteAll", 0x7210B0, &C3dMarkers::User3dMarkerDeleteAll);
    // ReversibleHooks::Install("C3dMarkers", "User3dMarkerDelete", 0x721090, &C3dMarkers::User3dMarkerDelete);
    // ReversibleHooks::Install("C3dMarkers", "User3dMarkerSet", 0x720FD0, &C3dMarkers::User3dMarkerSet);
    // ReversibleHooks::Install("C3dMarkers", "User3dMarkerFindFirstFreeSlot", 0x720FB0, &C3dMarkers::User3dMarkerFindFirstFreeSlot);
    // ReversibleHooks::Install("C3dMarkers", "SaveUser3dMarkers", 0x5D4300, &C3dMarkers::SaveUser3dMarkers);
    // ReversibleHooks::Install("C3dMarkers", "DirectionArrowSet", 0x721140, &C3dMarkers::DirectionArrowSet);
    // ReversibleHooks::Install("C3dMarkers", "PlaceMarkerCone", 0x726D40, &C3dMarkers::PlaceMarkerCone);
}

// 0x5D42E0
int32_t C3dMarkers::LoadUser3dMarkers() {
    return plugin::CallAndReturn<int32_t, 0x5D42E0>();
}

// 0x725120
C3dMarker* C3dMarkers::PlaceMarker(uint32_t id, uint16_t type, CVector& posn, float size, uint8_t r, uint8_t g, uint8_t b, uint8_t a, uint16_t pulsePeriod, float pulseFraction, uint16_t rotateRate, float nrm_x,
                                   float nrm_y, float nrm_z, bool zCheck) {
    return plugin::CallAndReturn<C3dMarker*, 0x725120, uint32_t, uint16_t, CVector&, float, uint8_t, uint8_t, uint8_t, uint8_t, uint16_t, float, uint16_t, float, float, float, bool>(
        id, type, posn, size, r, g, b, a, pulsePeriod, pulseFraction, rotateRate, nrm_x, nrm_y, nrm_z, zCheck);
}

// 0x725040
int32_t C3dMarkers::Render() {
    return plugin::CallAndReturn<int32_t, 0x725040>();
}

// 0x724E40
int32_t C3dMarkers::Init() {
    return plugin::CallAndReturn<int32_t, 0x724E40>();
}

// 0x723240
void C3dMarkers::User3dMarkersDraw() {
    plugin::Call<0x723240>();
}

// 0x722870
void C3dMarkers::ForceRender(uint8_t enable) {
    plugin::Call<0x722870, uint8_t>(enable);
}

// 0x722810
RpClump* C3dMarkers::LoadMarker(char const* name) {
    return plugin::CallAndReturn<RpClump*, 0x722810, char const*>(name);
}

// 0x7227B0
void C3dMarkers::Update() {
    plugin::Call<0x7227B0>();
}

// 0x722710
void C3dMarkers::Shutdown() {
    plugin::Call<0x722710>();
}

// 0x725BA0
void C3dMarkers::PlaceMarkerSet(uint32_t id, uint16_t type, CVector& posn, float size, uint8_t r, uint8_t g, uint8_t b, uint8_t a, uint16_t pulsePeriod, float pulseFraction) {
    plugin::Call<0x725BA0, uint32_t, uint16_t, CVector&, float, uint8_t, uint8_t, uint8_t, uint8_t, uint16_t, float>(id, type, posn, size, r, g, b, a, pulsePeriod, pulseFraction);
}

// 0x7211F0
void C3dMarkers::DirectionArrowsDraw() {
    plugin::Call<0x7211F0>();
}

// 0x721120
int32_t C3dMarkers::DirectionArrowFindFirstFreeSlot() {
    return plugin::CallAndReturn<int32_t, 0x721120>();
}

// 0x721100
void C3dMarkers::DirectionArrowsInit() {
    plugin::Call<0x721100>();
}

// 0x7210D0
RpAtomic* C3dMarkers::User3dMarkerAtomicCB(RpAtomic* a1) {
    return plugin::CallAndReturn<RpAtomic*, 0x7210D0, RpAtomic*>(a1);
}

// 0x7210B0
void C3dMarkers::User3dMarkerDeleteAll() {
    plugin::Call<0x7210B0>();
}

// 0x721090
void C3dMarkers::User3dMarkerDelete(int32_t a1) {
    plugin::Call<0x721090, int32_t>(a1);
}

// 0x720FD0
int32_t C3dMarkers::User3dMarkerSet(float x, float y, float z, int32_t color) {
    return plugin::CallAndReturn<int32_t, 0x720FD0, float, float, float, int32_t>(x, y, z, color);
}

// 0x720FB0
int32_t C3dMarkers::User3dMarkerFindFirstFreeSlot() {
    return plugin::CallAndReturn<int32_t, 0x720FB0>();
}

// 0x5D4300
int32_t C3dMarkers::SaveUser3dMarkers() {
    return plugin::CallAndReturn<int32_t, 0x5D4300>();
}

// 0x721140
void C3dMarkers::DirectionArrowSet(CVector posn, float size, int red, int green, int blue, int alpha, float dir_x, float dir_y, float dir_z) {
    plugin::Call<0x721140, CVector, float, int32_t, int32_t, int32_t, int32_t, float, float, float>(posn, size, red, green, blue, alpha, dir_x, dir_y, dir_z);
}

// 0x726D40
void C3dMarkers::PlaceMarkerCone(uint32_t id, CVector& posn, float size, uint8_t r, uint8_t g, uint8_t b, uint8_t alpha, uint16_t pulsePeriod, float pulseFraction, uint16_t type,
                                 uint8_t bEnableCollision) {
    plugin::Call<0x726D40, uint32_t, CVector&, float, uint8_t, uint8_t, uint8_t, uint8_t, uint16_t, float, uint16_t, uint8_t>(id, posn, size, r, g, b, alpha, pulsePeriod, pulseFraction, type,
                                                                                                       bEnableCollision);
}
