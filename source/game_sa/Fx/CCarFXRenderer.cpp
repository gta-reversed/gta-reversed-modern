#include "StdInc.h"

bool CCarFXRenderer::IsCCPCPipelineAttached(RpAtomic* pAtomic)
{
    return plugin::CallAndReturn<bool, 0x5D5B80, RpAtomic*>(pAtomic);
}

void CCarFXRenderer::CustomCarPipeAtomicSetup(RpAtomic* pAtomic)
{
    plugin::Call<0x5D5B20, RpAtomic*>(pAtomic);
}

void CCarFXRenderer::CustomCarPipeClumpSetup(RpClump* pClump)
{
    plugin::Call<0x5D5B40, RpClump*>(pClump);
}

void CCarFXRenderer::InitialiseDirtTexture()
{
    plugin::Call<0x5D5BC0>();
}

RpAtomic* CCarFXRenderer::SetCustomFXAtomicRenderPipelinesVMICB(RpAtomic* pAtomic, void* data)
{
    return plugin::CallAndReturn<RpAtomic*, 0x5D5B60, RpAtomic*, void*>(pAtomic, data);
}

void CCarFXRenderer::SetFxEnvMapLightMult(float multiplier)
{
    plugin::Call<0x5D5BA0, float>(multiplier);
}
