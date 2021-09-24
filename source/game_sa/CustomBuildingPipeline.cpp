#include "StdInc.h"

#include "CCustomBuildingPipeline.h"

RxPipeline*& CCustomBuildingPipeline::ObjPipeline = *(RxPipeline**)0xC02C68;

void CCustomBuildingPipeline::InjectHooks() {
    using namespace ReversibleHooks;
    // Install("CCustomBuildingPipeline", "CreatePipe", 0x5D7D90, &CCustomBuildingPipeline::CreatePipe);
    // Install("CCustomBuildingPipeline", "DestroyPipe", 0x5D7380, &CCustomBuildingPipeline::DestroyPipe);
    // Install("CCustomBuildingPipeline", "CustomPipeAtomicSetup", 0x5D7E50, &CCustomBuildingPipeline::CustomPipeAtomicSetup);
    // Install("CCustomBuildingPipeline", "CreateCustomObjPipe", 0x5D7AA0, &CCustomBuildingPipeline::CreateCustomObjPipe);
}

// 0x5D7D90
bool CCustomBuildingPipeline::CreatePipe() {
    ObjPipeline = CreateCustomObjPipe();
    return ObjPipeline != nullptr;
}

// 0x5D7380
void CCustomBuildingPipeline::DestroyPipe() {
    plugin::Call<0x5D7380>();
}

// dunno about return type, may be unnecessary
// 0x5D7E50
RpAtomic* CCustomBuildingPipeline::CustomPipeAtomicSetup(RpAtomic* atomic) {
    return plugin::CallAndReturn<RpAtomic*, 0x5D7E50, RpAtomic*>(atomic);
}

// 0x5D7AA0
RxPipeline* CCustomBuildingPipeline::CreateCustomObjPipe() {
    return plugin::CallAndReturn<RxPipeline*, 0x5D7AA0>();
}
