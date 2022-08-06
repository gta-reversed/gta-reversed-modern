#include "StdInc.h"

#include "ColPoint.h"

#include "CustomBuildingDNPipeline.h"

// 0x59F0C0
float tColLighting::GetCurrentLighting(float fScale) const {
    const auto fDay = static_cast<float>(day) * fScale / 15.0F;
    const auto fNight = static_cast<float>(night) * fScale / 15.0F;
    return lerp(fDay, fNight, CCustomBuildingDNPipeline::m_fDNBalanceParam);
}
