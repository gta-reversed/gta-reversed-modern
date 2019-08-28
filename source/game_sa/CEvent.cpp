#include "StdInc.h"

void* CEvent::operator_new()
{
    return plugin::CallAndReturn<void*, 0x4B5620>();
}