#include "StdInc.h"

CFireManager& gFireManager = *reinterpret_cast<CFireManager*>(0xB71F80);

CFire* CFireManager::FindNearestFire(CVector const& position, bool notBeingExtinguished, bool notScript)
{
    return plugin::CallMethodAndReturn<CFire*, 0x538F40, CFireManager*, CVector const&, bool, bool>(this, position, notBeingExtinguished, notScript);
}

CFire* CFireManager::StartFire(CEntity* target, CEntity* creator, _IGNORED_ float size, _IGNORED_ unsigned char arg3, unsigned int time, signed char numGenerations) {
    return plugin::CallMethodAndReturn<CFire*, 0x53A050, CFireManager*, CEntity*, CEntity*, float, unsigned char, unsigned int, signed char>(this, target, creator, size, arg3, time, numGenerations);
}
