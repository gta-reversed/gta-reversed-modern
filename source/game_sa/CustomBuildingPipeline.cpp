#include "StdInc.h"

#include "CustomBuildingPipeline.h"

RxPipeline*& CCustomBuildingPipeline::ObjPipeline = *(RxPipeline**)0xC02C68;

void CCustomBuildingPipeline::InjectHooks() {
    RH_ScopedClass(CCustomBuildingPipeline);
    RH_ScopedCategoryRoot();

    // RH_ScopedInstall(CreatePipe, 0x5D7D90);
    // RH_ScopedInstall(DestroyPipe, 0x5D7380);
    // RH_ScopedInstall(CustomPipeAtomicSetup, 0x5D7E50);
    // RH_ScopedInstall(CreateCustomObjPipe, 0x5D7AA0);
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
