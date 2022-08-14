#include "StdInc.h"

#include "FxInfoAttractLine.h"

// 0x4A57C0
FxInfoAttractLine_c::FxInfoAttractLine_c() : FxInfo_c() {
    m_nType = FX_INFO_ATTRACTLINE_DATA;
    m_InterpInfo.Allocate(7);
}

// 0x4A5830
void FxInfoAttractLine_c::Load(FILESTREAM file, int32 version) {
    m_InterpInfo.Load(file);
}

// 0x4A4880
void FindClosestPtOnLine(CVector& out, CVector& a2, CVector& a3, CVector& a4) {
    return plugin::Call<0x4A4880, CVector&, CVector&, CVector&, CVector&>(out, a2, a3, a4);

    const auto a = DistanceBetweenPoints(a4, a2);
    const auto b = DistanceBetweenPoints(a3, a2);
    const auto a3m2 = a3 - a2;
    const auto a4m2 = a4 - a2;
    float v9 = DotProduct(a4m2, a3m2) / a3m2.SquaredMagnitude();
    out = a3m2 * std::clamp(v9, 0.0f, 1.0f) + a2;
}

// 0x4A5850
void FxInfoAttractLine_c::GetValue(float currentTime, float mult, float totalTime, float length, bool bConstTimeSet, void* info) {
    float values[7];
    if (m_bTimeModeParticle) {
        m_InterpInfo.GetVal(values, mult);
    } else {
        m_InterpInfo.GetVal(values, currentTime / length);
    }

    CVector out;
    auto& v13 = *(CVector*)&values[0];
    auto& v12 = *(CVector*)&values[3];

    auto& movement = *static_cast<MovementInfo_t*>(info);
    FindClosestPtOnLine(out, v13, v12, movement.m_v0);
    CVector in = out - movement.m_v0;
    auto dist = in.Magnitude();

    if (dist > 0.0f) {
        in.Normalise();
    }

    if (dist > 0.1f) {
        movement.m_v1 += in * values[6] * totalTime;
    }
}
