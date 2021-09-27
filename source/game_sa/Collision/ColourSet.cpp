#include "StdInc.h"

bool CCreepingFire::TryToStartFireAtCoors(CVector pos, int8 numGenerations, bool a5, bool scriptFire, float zDistance) {
    return plugin::CallAndReturn<bool, 0x53A450, CVector, int8, bool, bool, float>(pos, numGenerations, a5, scriptFire, zDistance);
}
