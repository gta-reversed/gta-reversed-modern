#include "StdInc.h"

unsigned int CPedType::GetPedFlag(ePedType pedType)
{
    return plugin::CallAndReturn<unsigned int, 0x608830, ePedType>(pedType);
}

bool CPedType::PoliceDontCareAboutCrimesAgainstPedType(ePedType pedType) {
    return plugin::CallAndReturn<int, 0x608A40, ePedType>(pedType);
}