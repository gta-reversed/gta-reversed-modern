#include "StdInc.h"

#include "Gangs.h"

void CGangs::InjectHooks() {
    RH_ScopedClass(CGangs);
    RH_ScopedCategoryGlobal();

    // RH_ScopedInstall(Initialise, 0x5DE680);
    // RH_ScopedInstall(Load, 0x5D3A90);
    // RH_ScopedInstall(Save, 0x5D3A60);
}

// 0x5DE680
void CGangs::Initialise() {
    plugin::Call<0x5DE680>();
}

// 0x5D3A90
bool CGangs::Load() {
    return plugin::CallAndReturn<bool, 0x5D3A90>();
}

// 0x5D3A60
bool CGangs::Save() {
    return plugin::CallAndReturn<bool, 0x5D3A60>();
}
