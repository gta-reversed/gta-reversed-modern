#include "StdInc.h"

#include "Maths.h"

float (&CMaths::ms_SinTable)[256] = *(float(*)[256])0xBB3DFC;

void CMaths::InjectHooks()
{
    RH_ScopedClass(CMaths);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(InitMathsTables, 0x59AC90);
}

void CMaths::InitMathsTables() {
    ZoneScoped;

    for (int32 i = 0; i < 256; ++i)
        ms_SinTable[i] = sin(static_cast<float>(i) * PI / 128.0F);
}
