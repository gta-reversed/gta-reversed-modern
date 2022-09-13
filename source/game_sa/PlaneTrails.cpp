#include "StdInc.h"

#include "PlaneTrails.h"

CPlaneTrail (&CPlaneTrails::aArray)[NUM_PLANE_TRAILS] = *(CPlaneTrail(*)[NUM_PLANE_TRAILS])0xC713A8;

void CPlaneTrails::InjectHooks() {
    RH_ScopedClass(CPlaneTrails);
    RH_ScopedCategoryGlobal();

    // using namespace ReversibleHooks;
    RH_ScopedInstall(Init, 0x717370, { .reversed = false });
    RH_ScopedInstall(Render, 0x7173A0, { .reversed = false });
    RH_ScopedInstall(RegisterPoint, 0x7174C0, { .reversed = false });
    RH_ScopedInstall(Update, 0x7174F0, { .reversed = false });
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
