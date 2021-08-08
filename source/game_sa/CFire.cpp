#include "StdInc.h"

void CFire::Extinguish()
{
    plugin::Call<0x5393F0>();
}

void CFire::Initialise() {
    return plugin::CallMethod<0x538B30, CFire*>(this);
}

void CFire::CreateFxSysForStrength(const CVector& point, RwMatrixTag* m) {
    return plugin::CallMethod<0x539360, CFire*, const CVector&, RwMatrixTag*>(this, point, m);
}

void CFire::Extinguish() {
    return plugin::CallMethod<0x5393F0, CFire*>(this);
}

void CFire::ProcessFire() {
    return plugin::CallMethod<0x53A570, CFire*>(this);
}

