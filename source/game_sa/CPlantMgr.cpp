#include "StdInc.h"

void CPlantMgr::InjectHooks() {

}

// 0x5DD910
bool CPlantMgr::Initialise() {
    return plugin::CallAndReturn<bool, 0x5DD910>();
}

// 0x5DCFA0
void CPlantMgr::Update(CVector& cameraPosition) {
    return plugin::Call<0x5DCFA0, CVector&>(cameraPosition);
}
