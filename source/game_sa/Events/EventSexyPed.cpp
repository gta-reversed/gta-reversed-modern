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

    if (ped->GetTaskManager().IsFirstFoundTaskMatching<TASK_COMPLEX_PARTNER_DEAL, TASK_COMPLEX_BE_IN_COUPLE, TASK_COMPLEX_PARTNER_GREET>(m_SexyPed->GetTaskManager())) {
        return false;
    }

    return true;
}
