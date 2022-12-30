#include "StdInc.h"

#include "EventSexyPed.h"
#include "IKChainManager_c.h"

// 0x4AEDF0
CEventSexyPed::CEventSexyPed(CPed* ped) : CEventEditableResponse() {
    m_Ped = ped;
    CEntity::SafeRegisterRef(m_Ped);
}

// 0x4AEEA0
CEventSexyPed::~CEventSexyPed() {
    CEntity::SafeCleanUpRef(m_Ped);
}

// 0x4AEF00
bool CEventSexyPed::AffectsPed(CPed* ped) {
    return plugin::CallMethodAndReturn<bool, 0x4AEF00, CEventSexyPed*, CPed*>(this, ped);

    if (!ped->IsAlive())
        return false;

    if (!m_Ped)
        return false;

    if (!m_Ped->IsAlive())
        return false;

    if (g_ikChainMan.IsLooking(ped) && g_ikChainMan.GetLookAtEntity(ped) == m_Ped) {
        return false;
    }

    /*
    // todo:
    if (((task = ped->GetTaskManager().FindActiveTaskByType(TASK_COMPLEX_PARTNER_DEAL)) != 0 ||
         (task = ped->GetTaskManager().FindActiveTaskByType(TASK_COMPLEX_BE_IN_COUPLE)) != 0 ||
         (task = ped->GetTaskManager().FindActiveTaskByType(TASK_COMPLEX_PARTNER_GREET)) != 0) &&
        ((v5 = m_Ped->GetTaskManager().FindActiveTaskByType(TASK_COMPLEX_PARTNER_DEAL)) != 0 ||
         (v5 = m_Ped->GetTaskManager().FindActiveTaskByType(TASK_COMPLEX_BE_IN_COUPLE)) != 0 ||
         (v5 = m_Ped->GetTaskManager().FindActiveTaskByType(TASK_COMPLEX_PARTNER_GREET)) != 0) &&
        (task->GetTaskType() == v5->GetTaskType())) {
        return false;
    }
    */
    return true;
}
