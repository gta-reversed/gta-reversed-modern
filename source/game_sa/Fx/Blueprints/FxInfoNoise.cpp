#include "StdInc.h"

#include "FxInfoNoise.h"

FxInfoNoise_c::FxInfoNoise_c() : FxInfo_c() {
    m_nType = FX_INFO_NOISE_DATA;
    m_InterpInfo.Allocate(1);
}

void FxInfoNoise_c::Load(FILESTREAM file, int32 version) {
    m_InterpInfo.Load(file);
}

// 0x4A5300
void FxInfoNoise_c::GetValue(float currentTime, float mult, float totalTime, float a5, bool bConstTimeSet, void* info) {
    auto& movement = *static_cast<MovementInfo_t*>(info);
    if (!m_bTimeModeParticle) {
        mult = currentTime / a5;
    }
    
    float value;
    m_InterpInfo.GetVal(&value, mult);

    CVector in((float)(CGeneral::GetRandomNumber() % 10000) / 5000.0f - 1.0f);
    in.Normalise();
    in *= value * totalTime;

    auto length = movement.m_v1.Magnitude();
    movement.m_v1 += in;

    if (movement.m_v1.Magnitude() > 0.0f) {
        movement.m_v1.Normalise();
    }

    movement.m_v1 *= length;
}
