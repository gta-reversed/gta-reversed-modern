#include "StdInc.h"

#include "CarFXRenderer.h"

RwTexture* (&CCarFXRenderer::ms_aDirtTextures)[NUM_DIRT_TEXTURES] = *(RwTexture*(*)[NUM_DIRT_TEXTURES])0xC02BD0;

void CCarFXRenderer::InjectHooks() {
    RH_ScopedClass(CCarFXRenderer);
    RH_ScopedCategory("Fx");


}

// 0x5D5AC0
bool CCarFXRenderer::Initialise() {
    return plugin::CallAndReturn<bool, 0x5D5AC0>();
}

// 0x5D5AD0
void CCarFXRenderer::Shutdown() {
    plugin::Call<0x5D5AD0>();
}

// 0x5D5B10
void CCarFXRenderer::PreRenderUpdate() {
    CCustomCarEnvMapPipeline::PreRenderUpdate();
}

bool CCarFXRenderer::IsCCPCPipelineAttached(RpAtomic* atomic)
{
    return plugin::CallAndReturn<bool, 0x5D5B80, RpAtomic*>(atomic);
}

void CCarFXRenderer::CustomCarPipeAtomicSetup(RpAtomic* atomic)
{
    plugin::Call<0x5D5B20, RpAtomic*>(atomic);
}

void CCarFXRenderer::CustomCarPipeClumpSetup(RpClump* clump)
{
    plugin::Call<0x5D5B40, RpClump*>(clump);
}

void CCarFXRenderer::InitialiseDirtTexture()
{
    plugin::Call<0x5D5BC0>();
}

RpAtomic* CCarFXRenderer::SetCustomFXAtomicRenderPipelinesVMICB(RpAtomic* atomic, void* data)
{
    return plugin::CallAndReturn<RpAtomic*, 0x5D5B60, RpAtomic*, void*>(atomic, data);
}

void CCarFXRenderer::SetFxEnvMapLightMult(float multiplier)
{
    plugin::Call<0x5D5BA0, float>(multiplier);
}

