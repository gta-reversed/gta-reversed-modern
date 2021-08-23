#include "StdInc.h"

RpClump* (&C3dMarkers::m_pRpClumpArray)[NUM_MARKER_TYPES] = *(RpClump*(*)[NUM_MARKER_TYPES])0xC7C6DC;


void C3dMarkers::InjectHooks() {
//  ReversibleHooks::Install("C3dMarkers", "Init", 0x724E40, &C3dMarkers::Init);
//  ReversibleHooks::Install("C3dMarkers", "Update", 0x7227B0, &C3dMarkers::Update);
//  ReversibleHooks::Install("C3dMarkers", "Shutdown", 0x722710, &C3dMarkers::Shutdown);

//  ReversibleHooks::Install("C3dMarkers", "Render", 0x725040, &C3dMarkers::Render);
}

// 0x724E40
void C3dMarkers::Init() {
  plugin::Call<0x724E40>();
}

// 0x7227B0
void C3dMarkers::Update() {
  plugin::Call<0x7227B0>();
}

// 0x722710
void C3dMarkers::Shutdown() {
  plugin::Call<0x722710>();
}

// 0x725040
void C3dMarkers::Render() {
  plugin::Call<0x725040>();
}

RpClump* C3dMarkers::GetClumpForType(e3dMarkerType type) {
    switch (type) {
    case e3dMarkerType::MARKER3D_TUBE:
        return m_pRpClumpArray[1];
    case e3dMarkerType::MARKER3D_ARROW2:
        return m_pRpClumpArray[0];
    default:
        return m_pRpClumpArray[(unsigned)type];
    }
}

RpAtomic* MarkerAtomicCB(RpAtomic* atomic, void* data) {
    *reinterpret_cast<RpAtomic**>(data) = atomic;
    return atomic;
}

RpAtomic* C3dMarkers::GetClonedAtomicForType(e3dMarkerType type) {
    RpAtomic* atomic = nullptr;
    RpClumpForAllAtomics(GetClumpForType(type), MarkerAtomicCB, (void*)&atomic);
    return RpAtomicClone(atomic);
}
