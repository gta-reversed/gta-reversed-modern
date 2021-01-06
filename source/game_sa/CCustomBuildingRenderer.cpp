#include "StdInc.h"

bool CCustomBuildingRenderer::IsCBPCPipelineAttached(RpAtomic* pAtomic)
{
    return plugin::CallAndReturn<bool, 0x5D7F40, RpAtomic*>(pAtomic);
}
