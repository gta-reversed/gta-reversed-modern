#include "StdInc.h"

void CCustomBuildingDNPipeline::PreRenderUpdate(RpAtomic* pAtomic, bool ignoreDNBalanceParam)
{
    plugin::Call<0x5D7200, RpAtomic*, bool>(pAtomic, ignoreDNBalanceParam);
}

RpAtomic* CCustomBuildingDNPipeline::PreRenderUpdateRpAtomicCB(RpAtomic* pAtomic, void* data)
{
    CCustomBuildingDNPipeline::PreRenderUpdate(pAtomic, reinterpret_cast<bool>(data));
    return pAtomic;
}
