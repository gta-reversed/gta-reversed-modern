#include "StdInc.h"

#include "TaskSimpleIKManager.h"

// 0x6337F0
CTaskSimpleIKManager::CTaskSimpleIKManager() {
    std::ranges::fill(m_pIKChainTasks, nullptr);
    m_bAborting = false;
}
