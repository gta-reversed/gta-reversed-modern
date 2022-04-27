#include "StdInc.h"

#include "CustomCarEnvMapPipeline.h"

// 0x5D8870
void CCustomCarEnvMapPipeline::PreRenderUpdate() {
    plugin::Call<0x5D8870>();
}

// 0x5DA020
bool CCustomCarEnvMapPipeline::CreatePipe() {
    return plugin::CallAndReturn<bool, 0x5DA020>();
}

// 0x5DA130
void CCustomCarEnvMapPipeline::DestroyPipe() {
    plugin::Call<0x5DA130>();
}

// 0x5DA450
bool CCustomCarEnvMapPipeline::RegisterPlugin() {
    return plugin::CallAndReturn<bool, 0x5DA450>();
}

// 0x5DA610
RpAtomic* CCustomCarEnvMapPipeline::CustomPipeAtomicSetup(RpAtomic* atomic) {
    return plugin::CallAndReturn<RpAtomic*, 0x5DA610, RpAtomic*>(atomic);
}
