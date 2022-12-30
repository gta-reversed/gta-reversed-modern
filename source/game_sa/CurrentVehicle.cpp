#include "StdInc.h"

#include "CurrentVehicle.h"
#include "Hud.h"

void CCurrentVehicle::InjectHooks() {
    RH_ScopedClass(CCurrentVehicle);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(Display, 0x571EA0);
    RH_ScopedInstall(Process, 0x572040);
}

CCurrentVehicle::CCurrentVehicle() {
    Init();
}

// 0x572030
void CCurrentVehicle::Init() {
    m_pVehicle = nullptr;
}

// 0x571EA0
void CCurrentVehicle::Display() const {
    if (m_pVehicle) {
        auto* mi = m_pVehicle->GetVehicleModelInfo();
        CHud::SetVehicleName(TheText.Get(mi->m_szGameName));
    } else {
        CHud::SetVehicleName(nullptr);
    }
}

// 0x572040
void CCurrentVehicle::Process() {
    m_pVehicle = FindPlayerVehicle();
    Display();
}
