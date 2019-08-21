#include "StdInc.h"

void CPad::SetTouched()
{
    plugin::CallMethod<0x53F200, CPad*>(this);
}

unsigned int CPad::GetTouchedTimeDelta()
{
    return plugin::CallMethodAndReturn<unsigned int, 0x53F210, CPad*>(this);
}