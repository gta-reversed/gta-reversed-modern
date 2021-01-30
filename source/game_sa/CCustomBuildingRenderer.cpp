#include "StdInc.h"

bool CCustomBuildingRenderer::IsCBPCPipelineAttached(RpAtomic* pAtomic)
{
    return plugin::CallAndReturn<bool, 0x5D7F40, RpAtomic*>(pAtomic);
}

void CCustomBuildingRenderer::AtomicSetup(RpAtomic* pAtomic)
{
    plugin::Call<0x5D7F00, RpAtomic*>(pAtomic);
}
