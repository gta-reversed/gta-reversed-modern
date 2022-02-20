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
    RH_ScopedClass(C3dMarkers);
    RH_ScopedCategoryGlobal();

    // RH_ScopedInstall(LoadUser3dMarkers, 0x5D42E0);
    // RH_ScopedInstall(PlaceMarker, 0x725120);
    // RH_ScopedInstall(Render, 0x725040);
    // RH_ScopedInstall(Init, 0x724E40);
    // RH_ScopedInstall(User3dMarkersDraw, 0x723240);
    // RH_ScopedInstall(ForceRender, 0x722870);
    // RH_ScopedInstall(LoadMarker, 0x722810);
    // RH_ScopedInstall(Update, 0x7227B0);
    // RH_ScopedInstall(Shutdown, 0x722710);
    // RH_ScopedInstall(PlaceMarkerSet, 0x725BA0);
    // RH_ScopedInstall(DirectionArrowsDraw, 0x7211F0);
    // RH_ScopedInstall(DirectionArrowFindFirstFreeSlot, 0x721120);
    // RH_ScopedInstall(DirectionArrowsInit, 0x721100);
    // RH_ScopedInstall(User3dMarkerAtomicCB, 0x7210D0);
    // RH_ScopedInstall(User3dMarkerDeleteAll, 0x7210B0);
    // RH_ScopedInstall(User3dMarkerDelete, 0x721090);
    // RH_ScopedInstall(User3dMarkerSet, 0x720FD0);
    // RH_ScopedInstall(User3dMarkerFindFirstFreeSlot, 0x720FB0);
    // RH_ScopedInstall(SaveUser3dMarkers, 0x5D4300);
    // RH_ScopedInstall(DirectionArrowSet, 0x721140);
    // RH_ScopedInstall(PlaceMarkerCone, 0x726D40);
}

// 0x5D42E0
int32_t C3dMarkers::LoadUser3dMarkers() {
    return plugin::CallAndReturn<int32 0x5D42E0>();
}

// 0x725120
C3dMarker* C3dMarkers::PlaceMarker(uint32_t id, uint16_t type, CVector& posn, float size, uint8_t r, uint8_t g, uint8_t b, uint8_t a, uint16_t pulsePeriod, float pulseFraction, uint16_t rotateRate, float nrm_x,
                                   float nrm_y, float nrm_z, bool zCheck) {
    return plugin::CallAndReturn<C3dMarker*, 0x725120, uint32 uint16 CVector&, float, uint8 uint8 uint8 uint8 uint16 float, uint16 float, float, float, bool>(
        id, type, posn, size, r, g, b, a, pulsePeriod, pulseFraction, rotateRate, nrm_x, nrm_y, nrm_z, zCheck);
}

// 0x725040
int32_t C3dMarkers::Render() {
    return plugin::CallAndReturn<int32 0x725040>();
}

// 0x724E40
int32_t C3dMarkers::Init() {
    return plugin::CallAndReturn<int32 0x724E40>();
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
    plugin::Call<0x725BA0, uint32 uint16 CVector&, float, uint8 uint8 uint8 uint8 uint16 float>(id, type, posn, size, r, g, b, a, pulsePeriod, pulseFraction);
}

// 0x7211F0
void C3dMarkers::DirectionArrowsDraw() {
    plugin::Call<0x7211F0>();
}

// 0x721120
int32_t C3dMarkers::DirectionArrowFindFirstFreeSlot() {
    return plugin::CallAndReturn<int32 0x721120>();
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
    return plugin::CallAndReturn<int32 0x720FD0, float, float, float, int32_t>(x, y, z, color);
}

// 0x720FB0
int32_t C3dMarkers::User3dMarkerFindFirstFreeSlot() {
    return plugin::CallAndReturn<int32 0x720FB0>();
}

// 0x5D4300
int32_t C3dMarkers::SaveUser3dMarkers() {
    return plugin::CallAndReturn<int32 0x5D4300>();
}

// 0x721140
void C3dMarkers::DirectionArrowSet(CVector posn, float size, int red, int green, int blue, int alpha, float dir_x, float dir_y, float dir_z) {
    plugin::Call<0x721140, CVector, float, int32 int32 int32 int32 float, float, float>(posn, size, red, green, blue, alpha, dir_x, dir_y, dir_z);
}

// 0x726D40
void C3dMarkers::PlaceMarkerCone(uint32_t id, CVector& posn, float size, uint8_t r, uint8_t g, uint8_t b, uint8_t alpha, uint16_t pulsePeriod, float pulseFraction, uint16_t type,
                                 uint8_t bEnableCollision) {
    plugin::Call<0x726D40, uint32 CVector&, float, uint8 uint8 uint8 uint8 uint16 float, uint16 uint8_t>(id, posn, size, r, g, b, alpha, pulsePeriod, pulseFraction, type,
                                                                                                       bEnableCollision);
}
