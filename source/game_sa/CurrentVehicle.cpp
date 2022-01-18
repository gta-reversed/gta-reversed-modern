#include "StdInc.h"

#include "CurrentVehicle.h"

void CCurrentVehicle::InjectHooks() {
    using namespace ReversibleHooks;
    Install("CCurrentVehicle", "Display", 0x571EA0, &CCurrentVehicle::Display);
    Install("CCurrentVehicle", "Process", 0x572040, &CCurrentVehicle::Process);
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
        auto modelInfo = static_cast<CVehicleModelInfo*>(CModelInfo::GetModelInfo(m_pVehicle->m_nModelIndex));
        CHud::SetVehicleName(TheText.Get(modelInfo->m_szGameName));
    } else {
        CHud::SetVehicleName(nullptr);
    }
}

// 0x572040
void CCurrentVehicle::Process() {
    m_pVehicle = FindPlayerVehicle(-1, false);
    Display();
}
