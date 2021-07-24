#include "StdInc.h"

#include "CWaterCannons.h"
#include "CWaterCannon.h"

CWaterCannon (&CWaterCannons::aCannons)[3] = *(CWaterCannon (*)[3])0xC80740;

void CWaterCannons::InjectHooks() {
    ReversibleHooks::Install("CWaterCannons", "Init", 0x728C80, &CWaterCannons::Init);
    ReversibleHooks::Install("CWaterCannons", "UpdateOne", 0x728CB0, &CWaterCannons::UpdateOne);
    ReversibleHooks::Install("CWaterCannons", "Update", 0x72A3C0, &CWaterCannons::Update);
    ReversibleHooks::Install("CWaterCannons", "Render", 0x729B30, &CWaterCannons::Render);
}

// 0x728C80
void CWaterCannons::Init() {
    for (auto& cannon : aCannons) {
        cannon.Init();
    }
}

// 0x728CB0
void CWaterCannons::UpdateOne(unsigned int pVehicle, CVector* start, CVector* end) {
    for (auto& cannon : aCannons) {
        if (cannon.m_nId == pVehicle) {
            cannon.Update_NewInput(start, end);
            return;
        }
    }

    // find free slot and update
    auto i = 0;
    while (aCannons[i].m_nId) {
        if (++i >= MAX_WATER_CANNONS)
            return;
    }

    auto& cannon = aCannons[i];
    cannon.Init();
    cannon.m_nId = pVehicle;
    cannon.Update_NewInput(start, end);
}

// 0x72A3C0
void CWaterCannons::Update() {
    short index = 0;
    for (auto& cannon : aCannons) {
        cannon.m_audio.Service();
        if (cannon.m_nId > 0) {
            cannon.Update_OncePerFrame(index);
        }
        ++index;
    }
}

// 0x729B30
void CWaterCannons::Render() {
    for (auto& cannon : aCannons) {
        cannon.Render();
    }
}
