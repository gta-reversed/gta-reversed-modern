#include "StdInc.h"

#include "TaskComplexGoToPointAndStandStillTimed.h"
#include "PedPlacement.h"

void CTaskComplexGoToPointAndStandStillTimed::InjectHooks() {
    RH_ScopedClass(CTaskComplexGoToPointAndStandStillTimed);
    RH_ScopedCategory("Tasks/TaskTypes");
    RH_ScopedInstall(Constructor, 0x6685E0);
    RH_ScopedVirtualInstall(Clone, 0x66CF30);
    RH_ScopedVirtualInstall(StopTimer, 0x6686A0);
    RH_ScopedVirtualInstall(MakeAbortable, 0x668640);
    RH_ScopedVirtualInstall(CreateFirstSubTask, 0x66DC90);
    RH_ScopedVirtualInstall(ControlSubTask, 0x66DCE0);
}

CTaskComplexGoToPointAndStandStillTimed::CTaskComplexGoToPointAndStandStillTimed(eMoveState moveState, const CVector& targetPoint, float fRadius, float fMoveStateRadius, int32 time)
    : CTaskComplexGoToPointAndStandStill(moveState, targetPoint, fRadius, fMoveStateRadius, false, false)
{
    m_nTime = time;
}

CTaskComplexGoToPointAndStandStillTimed::~CTaskComplexGoToPointAndStandStillTimed() {
    // nothing here
}

// 0x66CF30
CTask* CTaskComplexGoToPointAndStandStillTimed::Clone() const {
    return CTaskComplexGoToPointAndStandStillTimed::Clone_Reversed();
}

// 0x6686A0
void CTaskComplexGoToPointAndStandStillTimed::StopTimer(const CEvent* event) {
    return CTaskComplexGoToPointAndStandStillTimed::StopTimer_Reversed(event);
}

// 0x668640
bool CTaskComplexGoToPointAndStandStillTimed::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) {
    return CTaskComplexGoToPointAndStandStillTimed::MakeAbortable_Reversed(ped, priority, event);
}

// 0x66DC90
CTask* CTaskComplexGoToPointAndStandStillTimed::CreateFirstSubTask(CPed* ped) {
    return CTaskComplexGoToPointAndStandStillTimed::CreateFirstSubTask_Reversed(ped);
}

// 0x66DCE0
CTask* CTaskComplexGoToPointAndStandStillTimed::ControlSubTask(CPed* ped) {
    return CTaskComplexGoToPointAndStandStillTimed::ControlSubTask_Reversed(ped);
}

CTask* CTaskComplexGoToPointAndStandStillTimed::Clone_Reversed() const {
    return new CTaskComplexGoToPointAndStandStillTimed(m_moveState, m_vecTargetPoint, m_fRadius, m_fMoveStateRadius, m_nTime);
}

void CTaskComplexGoToPointAndStandStillTimed::StopTimer_Reversed(const CEvent* event) {
    if (!CEventHandler::IsTemporaryEvent(*event))
        m_timer.Pause();
}

bool CTaskComplexGoToPointAndStandStillTimed::MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, const CEvent* event) {
    bool bSubTaskAbortable = m_pSubTask->MakeAbortable(ped, priority, event);
    if (bSubTaskAbortable && priority == ABORT_PRIORITY_URGENT && (!event || !CEventHandler::IsTemporaryEvent(*event)))
        m_timer.Pause();

    return bSubTaskAbortable;
}

CTask* CTaskComplexGoToPointAndStandStillTimed::CreateFirstSubTask_Reversed(CPed* ped) {
    m_timer.Start(m_nTime);
    m_bTargetPointUpdated = false;
    if (ped->bInVehicle)
        return CTaskComplexGoToPointAndStandStill::CreateFirstSubTask(TASK_COMPLEX_LEAVE_CAR, ped)
;
    return CTaskComplexGoToPointAndStandStill::CreateFirstSubTask(TASK_SIMPLE_GO_TO_POINT, ped);
}

CTask* CTaskComplexGoToPointAndStandStillTimed::ControlSubTask_Reversed(CPed* ped) {
    if (m_timer.Reset()) {
        if (m_timer.IsOutOfTime() && m_pSubTask->GetTaskType() != TASK_SIMPLE_STAND_STILL && CPedPlacement::FindZCoorForPed(m_vecTargetPoint)) {
            ped->SetPosn(m_vecTargetPoint);
        }
    }
    return CTaskComplexGoToPointAndStandStill::ControlSubTask(ped);
}
