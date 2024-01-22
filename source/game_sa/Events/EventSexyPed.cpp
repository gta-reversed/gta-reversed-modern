#include "StdInc.h"

#include "EventSexyPed.h"
#include "IKChainManager_c.h"

// 0x4AEDF0
CEventSexyPed::CEventSexyPed(CPed* ped) : CEventEditableResponse() {
    m_SexyPed = ped;
    CEntity::SafeRegisterRef(m_SexyPed);
}

// NOTSA
CEventSexyPed::CEventSexyPed(CPed* sexyPed, eTaskType taskType) :
    CEventSexyPed{sexyPed}
{
    m_taskId = (int16)taskType;
}

// 0x4AEEA0
CEventSexyPed::~CEventSexyPed() {
    CEntity::SafeCleanUpRef(m_SexyPed);
}

// 0x4AEF00
bool CEventSexyPed::AffectsPed(CPed* ped) {
    if (!ped->IsAlive())
        return false;

    if (!m_SexyPed)
        return false;

    if (!m_SexyPed->IsAlive())
        return false;

    if (g_ikChainMan.IsLooking(ped) && g_ikChainMan.GetLookAtEntity(ped) == m_SexyPed) {
        return false;
    }

    auto pedTaskMgr = ped->GetTaskManager();
    CTask* pedTask = nullptr;
    CTask* sexyPedTask = nullptr;
    if ((pedTask = pedTaskMgr.FindActiveTaskByType(TASK_COMPLEX_PARTNER_DEAL)) ||
        (pedTask = pedTaskMgr.FindActiveTaskByType(TASK_COMPLEX_BE_IN_COUPLE)) ||
        (pedTask = pedTaskMgr.FindActiveTaskByType(TASK_COMPLEX_PARTNER_GREET))) {
        auto sexyPedTaskMgr = m_SexyPed->GetTaskManager();
        if ((sexyPedTask = sexyPedTaskMgr.FindActiveTaskByType(TASK_COMPLEX_PARTNER_DEAL)) ||
            (sexyPedTask = sexyPedTaskMgr.FindActiveTaskByType(TASK_COMPLEX_BE_IN_COUPLE)) ||
            (sexyPedTask = sexyPedTaskMgr.FindActiveTaskByType(TASK_COMPLEX_PARTNER_GREET))) {
            if (pedTask && sexyPedTask && pedTask->GetTaskType() == sexyPedTask->GetTaskType()) {
                return false;
            }
        }
    }
    return true;
}
