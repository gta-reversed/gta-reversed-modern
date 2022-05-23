#include "StdInc.h"

#include "FxInfoRotSpeed.h"
#include "MovementInfo.h"

// 0x4A5CB0
FxInfoRotSpeed_c::FxInfoRotSpeed_c() : FxInfo_c() {
    m_nType = FX_INFO_ROTSPEED_DATA;
    m_InterpInfo.Allocate(4);
}

// 0x4A5D20
void FxInfoRotSpeed_c::Load(FILESTREAM file, int32 version) {
    m_InterpInfo.Load(file);
}

// 0x4A5D40
void FxInfoRotSpeed_c::GetValue(float currentTime, float mult, float totalTime, float length, bool bConstTimeSet, void* info) {
    if (!m_bTimeModeParticle) {
        mult = currentTime / length;
    }

    float values[4];
    m_InterpInfo.GetVal(values, mult);

    auto& movement = *static_cast<MovementInfo_t*>(info);
    movement.m_fMinCW  = values[0];
    movement.m_fMaxCW  = values[1];
    movement.m_fMinCCW = values[2];
    movement.m_fMaxCCW = values[3];
}
