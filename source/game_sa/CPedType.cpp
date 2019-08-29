#include "StdInc.h"

unsigned int CPedType::GetPedFlag(ePedType pedType)
{
    return plugin::CallAndReturn<unsigned int, 0x608830, ePedType>(pedType);
}