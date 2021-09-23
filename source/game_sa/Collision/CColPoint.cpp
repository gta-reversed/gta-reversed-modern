#include "StdInc.h"

#include "CColPoint.h"

#include "CCustomBuildingDNPipeline.h"

float tColLighting::GetCurrentLighting(float fScale) const {
    const auto fDay = static_cast<float>(day) * fScale / 15.0F;
    const auto fNight = static_cast<float>(night) * fScale / 15.0F;
    return lerp(fDay, fNight, CCustomBuildingDNPipeline::m_fDNBalanceParam);
}
