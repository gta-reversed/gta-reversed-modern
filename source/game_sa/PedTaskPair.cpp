#include "StdInc.h"
#include "PedTaskPair.h"

void CPedTaskPair::InjectHooks() {
    Install("CPedTaskPair", "Flush", 0x5E95B0, &CPedTaskPair::Flush);
}

// 0x5E95B0
void CPedTaskPair::Flush() {
    m_pPed = nullptr;
    if (m_pTask)
        delete m_pTask;
    m_pTask = nullptr;
    m_taskSlot = -1;
}
