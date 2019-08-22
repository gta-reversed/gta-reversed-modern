#include "StdInc.h"

CTaskComplexJump* CTaskComplexJump::Constructor(unsigned int jumpType)
{
    return plugin::CallMethodAndReturn<CTaskComplexJump*, 0x67A030, CTaskComplexJump*, unsigned int>(this, jumpType);
}