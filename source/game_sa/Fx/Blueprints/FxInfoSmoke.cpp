#include "StdInc.h"

#include "FxInfoSmoke.h"

// 0x4A68E0
FxInfoSmoke_c::FxInfoSmoke_c() : FxInfo_c() {
    m_nType = FX_INFO_SMOKE_DATA;
    m_InterpInfo.Allocate(8);
}

// 0x4A6950
void FxInfoSmoke_c::Load(FILESTREAM file, int32 version) {
    m_InterpInfo.Load(file);
}

// 0x4A6970
void FxInfoSmoke_c::GetValue(float currentTime, float mult, float totalTime, float length, bool bConstTimeSet, void* info) {
    if (!m_bTimeModeParticle) {
        mult = currentTime / length;
    }

    float values[8];
    m_InterpInfo.GetVal(values, mult);

    auto& render = *static_cast<RenderInfo_t*>(info);

    render.m_nSmokeCount = static_cast<int8>(values[0]);
    render.m_ColR = values[1];
    render.m_ColG = values[2];
    render.m_ColB = values[3];
    render.m_ColA = values[4];
    render.field_98 = values[5];
    render.m_PrtSize = values[6];
    render.m_Lifetime = values[7];
}
