#include "StdInc.h"

float& CCustomBuildingDNPipeline::m_fDNBalanceParam = *(float*)0x8D12C0;

void CCustomBuildingDNPipeline::PreRenderUpdate(RpAtomic* pAtomic, bool ignoreDNBalanceParam)
{
    plugin::Call<0x5D7200, RpAtomic*, bool>(pAtomic, ignoreDNBalanceParam);
}

RpAtomic* CCustomBuildingDNPipeline::PreRenderUpdateRpAtomicCB(RpAtomic* pAtomic, void* data)
{
    CCustomBuildingDNPipeline::PreRenderUpdate(pAtomic, static_cast<bool>(reinterpret_cast<intptr_t>(data)));
    return pAtomic;
}
