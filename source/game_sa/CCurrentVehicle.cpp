#include "StdInc.h"

#include "CCurrentVehicle.h"

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
    char* name = nullptr;
    if (m_pVehicle) {
        auto modelInfo = static_cast<CVehicleModelInfo*>(CModelInfo::GetModelInfo(m_pVehicle->m_nModelIndex));
        auto gameName = modelInfo->m_szGameName;
        name = TheText.Get(gameName);
    }
    CHud::SetVehicleName(name);
}

// 0x572040
void CCurrentVehicle::Process() {
    auto player = FindPlayerPed();
    if (player->bInVehicle) {
        m_pVehicle = player->m_pVehicle;
    } else {
        m_pVehicle = nullptr;
    }

    Display();
}
