#include "StdInc.h"

void CCustomBuildingDNPipeline::PreRenderUpdate(RpAtomic* pAtomic, bool ignoreDNBalanceParam)
{
    plugin::Call<0x5D7200, RpAtomic*, bool>(pAtomic, ignoreDNBalanceParam);
}
