#include "StdInc.h"

#include "TaskSimpleClearLookAt.h"
#include "IKChainManager_c.h"

// 0x6346C0
bool CTaskSimpleClearLookAt::ProcessPed(CPed* ped) {
    if (g_ikChainMan.IsLooking(ped)) {
        g_ikChainMan.AbortLookAt(ped, 500u);
    }
    return true;
}
