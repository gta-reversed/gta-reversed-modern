#include "StdInc.h"

#include "FxInfoEmSize.h"

// 0x4A4C20
FxInfoEmSize_c::FxInfoEmSize_c() : FxInfo_c() {
    m_nType = FX_INFO_EMSIZE_DATA;
    m_InterpInfo.Allocate(7);
}

// 0x4A4C90
void FxInfoEmSize_c::Load(FILESTREAM file, int32 version) {
    m_InterpInfo.Load(file);
}

// 0x4A4CB0
void FxInfoEmSize_c::GetValue(float currentTime, float mult, float totalTime, float length, bool bConstTimeSet, void* info) {
    float values[7];
    m_InterpInfo.GetVal(values, currentTime);

    auto& emission = *static_cast<EmissionInfo_t*>(info);
    emission.m_fRadius = values[0];

    emission.m_Min.x = values[1];
    emission.m_Min.y = values[3];
    emission.m_Min.z = values[5];

    emission.m_Max.x = values[2];
    emission.m_Max.y = values[4];
    emission.m_Max.z = values[6];
}
