#pragma once

#include "FxInterpInfo.h"

class FxInterpInfoFloat_c : public FxInterpInfo_c {
protected:
    float** m_pValues;

public:
    FxInterpInfoFloat_c();
    ~FxInterpInfoFloat_c() = default; // 0x4A8460

    virtual void Load(FILESTREAM file);

    void Allocate(int32 count);
    float GetVal(int32 a1, float time, float a3);
    void GetVal(float* outValues, float delta);
};
