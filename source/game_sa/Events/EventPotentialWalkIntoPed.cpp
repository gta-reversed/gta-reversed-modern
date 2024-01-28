#include "StdInc.h"

#include "EventPotentialWalkIntoPed.h"
#include "TaskComplexFollowPedFootsteps.h"

void CEventPotentialWalkIntoPed::InjectHooks()
{
    RH_ScopedClass(CEventPotentialWalkIntoPed);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x4AE6E0);
    RH_ScopedVirtualInstall(AffectsPed, 0x4AE800);
    RH_ScopedVirtualInstall(TakesPriorityOver, 0x4AE950);
}

// 0x4AE6E0
CEventPotentialWalkIntoPed::CEventPotentialWalkIntoPed(CPed* ped, const CVector& targetPoint, eMoveState moveState) :
    m_targetPoint{targetPoint},
    m_ped{ped},
    m_moveState{moveState}
{
    CEntity::SafeRegisterRef(m_ped);
}

CEventPotentialWalkIntoPed::~CEventPotentialWalkIntoPed() {
    CEntity::SafeCleanUpRef(m_ped);
}

// 0x4AE800
bool CEventPotentialWalkIntoPed::AffectsPed(CPed* ped) {
    return CEventPotentialWalkIntoPed::AffectsPed_Reversed(ped);
}

// 0x4AE950
bool CEventPotentialWalkIntoPed::TakesPriorityOver(const CEvent& refEvent) {
    return CEventPotentialWalkIntoPed::TakesPriorityOver_Reversed(refEvent);
}

bool CEventPotentialWalkIntoPed::AffectsPed_Reversed(CPed* ped) {
    if (!ped->IsAlive() || !m_ped || m_moveState == PEDMOVE_STILL) {
        return false;
    }

    if (ped->GetTaskManager().IsFirstFoundTaskMatching<TASK_COMPLEX_PARTNER_DEAL, TASK_COMPLEX_BE_IN_COUPLE, TASK_COMPLEX_PARTNER_GREET>(m_ped->GetTaskManager())) {
        return false;
    }

    if (const auto task = ped->GetTaskManager().Find<CTaskComplexFollowPedFootsteps>()) {
        if (task->m_targetPed == m_ped) {
            return false;
        }
    }

    if (const auto task = ped->GetTaskManager().Find<CTaskComplexKillPedOnFoot>()) {
        if (task->m_target == m_ped) {
            return false;
        }
    }

    if (const auto simplest = ped->GetTaskManager().GetSimplestActiveTask()) {
        if (CTask::IsGoToTask(simplest)) {
            return true;
        }
    }

    return false;
}

bool CEventPotentialWalkIntoPed::TakesPriorityOver_Reversed(const CEvent& refEvent) {
    return CEventHandler::IsTemporaryEvent(refEvent) ? true : CEvent::TakesPriorityOver(refEvent);
}

