#include "StdInc.h"

float* CMaths::ms_SinTable = (float*)0xBB3DFC;

void CMaths::InjectHooks()
{
    ReversibleHooks::Install("CMaths", "InitMathsTables", 0x59AC90, &CMaths::InitMathsTables);
}

void CMaths::InitMathsTables()
{
    for (int32 i = 0; i < 256; ++i)
        CMaths::ms_SinTable[i] = sin(static_cast<float>(i) * PI / 128.0F);
}
