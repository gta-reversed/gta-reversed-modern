#include "StdInc.h"

CFireManager& gFireManager = *reinterpret_cast<CFireManager*>(0xB71F80);

CFire* CFireManager::FindNearestFire(CVector const& position, bool notBeingExtinguished, bool notScript)
{
    return plugin::CallMethodAndReturn<CFire*, 0x538F40, CFireManager*, CVector const&, bool, bool>(this, position, notBeingExtinguished, notScript);
}
