#pragma once

#include "FxInfo.h"
#include "FxInterpInfoFloat.h"

class FxInfoEmPos_c : public FxInfo_c {
protected:
    FxInterpInfoFloat_c m_InterpInfo;

public:
    FxInfoEmPos_c();
    ~FxInfoEmPos_c() override = default; // 0x4A6D30

    void Load(FILESTREAM file, int32 version) override;
    void GetValue(float currentTime, float mult, float totalTime, float length, bool useConst, void* info) override;
};
