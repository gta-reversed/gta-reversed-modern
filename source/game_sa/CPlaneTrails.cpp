#include "StdInc.h"

#include "CPlaneTrails.h"

CPlaneTrail (&CPlaneTrails::aArray)[NUM_PLANE_TRAILS] = *(CPlaneTrail(*)[NUM_PLANE_TRAILS])0xC713A8;

void CPlaneTrails::InjectHooks() {
    // using namespace ReversibleHooks;
    // Install("CPlaneTrails", "Init", 0x717370, &CPlaneTrails::Init);
    // Install("CPlaneTrails", "Render", 0x7173A0, &CPlaneTrails::Render);
    // Install("CPlaneTrails", "RegisterPoint", 0x7174C0, &CPlaneTrails::RegisterPoint);
    // Install("CPlaneTrails", "Update", 0x7174F0, &CPlaneTrails::Update);
}

void CPlaneTrails::Init() {
    plugin::Call<0x717370>();
}

void CPlaneTrails::Render() {
    plugin::Call<0x7173A0>();
}

void CPlaneTrails::RegisterPoint(CVector point, uint32 trailIndex) {
    plugin::Call<0x7174C0, CVector, uint32>(point, trailIndex);
}

void CPlaneTrails::Update() {
    plugin::Call<0x7174F0>();
}
