#include "StdInc.h"

#include "TaskComplexGoToPointAndStandStill.h"

#include "TaskSimpleGoToPoint.h"
#include "TaskComplexLeaveCar.h"
#include "TaskSimplePause.h"
#include "TaskSimpleStandStill.h"

void CTaskComplexGoToPointAndStandStill::InjectHooks() {
    ReversibleHooks::Install("CTaskComplexGoToPointAndStandStill", "CTaskComplexGoToPointAndStandStill", 0x668120, &CTaskComplexGoToPointAndStandStill::Constructor);
    ReversibleHooks::Install("CTaskComplexGoToPointAndStandStill", "Clone", 0x66CEA0, &CTaskComplexGoToPointAndStandStill::Clone_Reversed);
    ReversibleHooks::Install("CTaskComplexGoToPointAndStandStill", "CreateNextSubTask", 0x66DBA0, &CTaskComplexGoToPointAndStandStill::CreateNextSubTask_Reversed);
    ReversibleHooks::Install("CTaskComplexGoToPointAndStandStill", "CreateFirstSubTask", 0x66DC40, &CTaskComplexGoToPointAndStandStill::CreateFirstSubTask_Reversed);
    ReversibleHooks::Install("CTaskComplexGoToPointAndStandStill", "CreateFirstSubTask_ped", 0x6682D0, static_cast<CTask * (CTaskComplexGoToPointAndStandStill::*)(int32, CPed*)>(&CTaskComplexGoToPointAndStandStill::CreateFirstSubTask));
    ReversibleHooks::Install("CTaskComplexGoToPointAndStandStill", "ControlSubTask", 0x668570, &CTaskComplexGoToPointAndStandStill::ControlSubTask_Reversed);
    ReversibleHooks::Install("CTaskComplexGoToPointAndStandStill", "GoToPoint", 0x46FE60, &CTaskComplexGoToPointAndStandStill::GoToPoint);
    ReversibleHooks::Install("CTaskComplexGoToPointAndStandStill", "SelectMoveState", 0x668250, &CTaskComplexGoToPointAndStandStill::SelectMoveState);
}

// 0x668120
CTaskComplexGoToPointAndStandStill::CTaskComplexGoToPointAndStandStill(int32 moveState, const CVector& targetPoint, float fRadius, float fMoveStateRadius, bool bUnknown, bool bGoToPoint) : CTaskComplex() {
    m_moveState           = moveState;
    m_nFlags              = 0;
    m_b01                 = bUnknown;
    m_bTargetPointUpdated = true;
    m_bGoToPoint          = bGoToPoint;

    if (m_vecTargetPoint != targetPoint || m_fMoveStateRadius != fMoveStateRadius) {
        m_vecTargetPoint = targetPoint;
        m_fRadius = fRadius;
        m_fMoveStateRadius = fMoveStateRadius;
        m_bTargetPointUpdated = true;
    }

    if (m_bGoToPoint) {
        m_b01 = false;
        if (moveState <= PEDMOVE_WALK) {
            if (m_fRadius < 0.5f) {
                m_fRadius = 0.5f;
                m_fMoveStateRadius = 0.0f;
                return;
            }
        } else if (m_fRadius < 1.0f) {
            m_fRadius = 1.0f;
            m_fMoveStateRadius = 0.0f;
            return;
        }
        m_fMoveStateRadius = 0.0f;
    }
}

CTaskComplexGoToPointAndStandStill::~CTaskComplexGoToPointAndStandStill() {
    // NOP
}

// 0x668120
CTaskComplexGoToPointAndStandStill* CTaskComplexGoToPointAndStandStill::Constructor(int32 moveState, const CVector& targetPoint, float fRadius, float fMoveStateRadius, bool bUnknown, bool bGoToPoint) {
    this->CTaskComplexGoToPointAndStandStill::CTaskComplexGoToPointAndStandStill(moveState, targetPoint, fRadius, fMoveStateRadius, bUnknown, bGoToPoint);
    return this;
}

// 0x66CEA0
CTask* CTaskComplexGoToPointAndStandStill::Clone() {
    return CTaskComplexGoToPointAndStandStill::Clone_Reversed();
}

// 0x66DBA0
CTask* CTaskComplexGoToPointAndStandStill::CreateNextSubTask(CPed* ped) {
    return CTaskComplexGoToPointAndStandStill::CreateNextSubTask_Reversed(ped);
}

// 0x66DC40
CTask* CTaskComplexGoToPointAndStandStill::CreateFirstSubTask(CPed* ped) {
    return CTaskComplexGoToPointAndStandStill::CreateFirstSubTask_Reversed(ped);
}

// 0x668570
CTask* CTaskComplexGoToPointAndStandStill::ControlSubTask(CPed* ped) {
    return CTaskComplexGoToPointAndStandStill::ControlSubTask_Reversed(ped);
}

CTask* CTaskComplexGoToPointAndStandStill::Clone_Reversed() {
    return new CTaskComplexGoToPointAndStandStill(m_moveState, m_vecTargetPoint, m_fRadius, m_fMoveStateRadius, m_b01, m_bGoToPoint);
}

CTask* CTaskComplexGoToPointAndStandStill::CreateNextSubTask_Reversed(CPed* ped) {
    switch (m_pSubTask->GetTaskType()) {
    case TASK_SIMPLE_STAND_STILL:
        return CreateFirstSubTask(TASK_FINISHED, ped);
    case TASK_COMPLEX_LEAVE_CAR:
        if (ped->bInVehicle)
            return CreateFirstSubTask(TASK_FINISHED, ped);
        return CreateFirstSubTask(TASK_SIMPLE_GO_TO_POINT, ped);
    case TASK_SIMPLE_GO_TO_POINT:
        m_b05 = static_cast<CTaskSimpleGoToPoint*>(m_pSubTask)->gotoPointFlags.m_b03;
        return CreateFirstSubTask(TASK_SIMPLE_STAND_STILL, ped);
        break;
    }
    return nullptr;
}

CTask* CTaskComplexGoToPointAndStandStill::CreateFirstSubTask_Reversed(CPed* ped) {
    m_bTargetPointUpdated = false;
    if (ped->bInVehicle)
        return CreateFirstSubTask(TASK_COMPLEX_LEAVE_CAR, ped);

    return CreateFirstSubTask(TASK_SIMPLE_GO_TO_POINT, ped);
}

CTask* CTaskComplexGoToPointAndStandStill::ControlSubTask_Reversed(CPed* ped) {
    if (m_bTargetPointUpdated) {
        if (m_pSubTask->MakeAbortable(ped, ABORT_PRIORITY_URGENT, nullptr))
            return CreateFirstSubTask(ped);

    } else if (m_pSubTask->GetTaskType() == TASK_SIMPLE_GO_TO_POINT) {
        auto gotoPointTask = static_cast<CTaskSimpleGoToPoint*>(m_pSubTask);
        if (m_moveState == PEDMOVE_RUN) {
            SelectMoveState(gotoPointTask, ped, m_fMoveStateRadius, 100000000.0f);
        } else if (m_moveState == PEDMOVE_SPRINT) {
            SelectMoveState(gotoPointTask, ped, m_fMoveStateRadius, 10.0f);
        }
        return m_pSubTask;
    }
    return m_pSubTask;
}

// 0x46FE60
void CTaskComplexGoToPointAndStandStill::GoToPoint(const CVector& targetPoint, float fRadius, float fMoveStateRadius, bool bUpdateTargetEvenIfItsTheSame) {
    if (bUpdateTargetEvenIfItsTheSame || m_vecTargetPoint != targetPoint || m_fMoveStateRadius != fMoveStateRadius) {
        m_vecTargetPoint = targetPoint;
        m_fRadius = fRadius;
        m_fMoveStateRadius = fMoveStateRadius;
        m_bTargetPointUpdated = true;
    }
}

// 0x668250
void CTaskComplexGoToPointAndStandStill::SelectMoveState(CTaskSimpleGoToPoint* gotoPointTask, CPed* ped, float fMoveStateRadius, float fRunOrSprintRadius) {
    CVector2D   vecDistance = ped->GetPosition() - gotoPointTask->m_vecTargetPoint;
    const float fSquaredMagnitude = vecDistance.SquaredMagnitude();
    if (fSquaredMagnitude >= fMoveStateRadius * fMoveStateRadius) {
        if (fSquaredMagnitude >= fRunOrSprintRadius * fRunOrSprintRadius)
            gotoPointTask->m_moveState = PEDMOVE_SPRINT;
        else
            gotoPointTask->m_moveState = PEDMOVE_RUN;
    } else {
        gotoPointTask->m_moveState = PEDMOVE_WALK;
    }
}

// 0x6682D0
CTask* CTaskComplexGoToPointAndStandStill::CreateFirstSubTask(int32 taskId, CPed* ped) {
    if (taskId > TASK_COMPLEX_LEAVE_CAR) {
        if (taskId != TASK_SIMPLE_GO_TO_POINT)
            return nullptr;

        auto* gotoPointTask = new CTaskSimpleGoToPoint(m_moveState, m_vecTargetPoint, m_fRadius, false, m_b01);
        if (m_b04)
            gotoPointTask->gotoPointFlags.m_b05 = true;

        if (m_moveState == PEDMOVE_RUN)
            SelectMoveState(gotoPointTask, ped, m_fMoveStateRadius, 100000000.0f);

        else if (m_moveState == PEDMOVE_SPRINT)
            SelectMoveState(gotoPointTask, ped, m_fMoveStateRadius, 10.0f);

        return gotoPointTask;
    }

    switch (taskId) {
    case TASK_COMPLEX_LEAVE_CAR: {
        return new CTaskComplexLeaveCar(ped->m_pVehicle, 0, 0, true, false);
    }
    case TASK_SIMPLE_PAUSE:
        return new CTaskSimplePause(1);
    case TASK_SIMPLE_STAND_STILL: {
        if (m_bGoToPoint && m_pSubTask && m_pSubTask->GetTaskType() == TASK_SIMPLE_GO_TO_POINT) {
            CVector vecDistance = m_vecTargetPoint - ped->GetPosition();
            float   fDotProduct = DotProduct(&vecDistance, &ped->GetForward());
            float   fBlendDelta = 8.0f;
            if (ped->m_vecAnimMovingShiftLocal.y >= 0.01f) {
                fBlendDelta = 50.0f / ((fDotProduct / (ped->m_vecAnimMovingShiftLocal.y * 0.5f) - 1.0f) * CTimer::GetTimeStep());
                if (fDotProduct <= 0.01f || fBlendDelta > 16.0f)
                    fBlendDelta = 16.0f;
            }
            return new CTaskSimpleStandStill(2000, false, true, fBlendDelta);
        }
        return new CTaskSimpleStandStill(1, false, false, 8.0f);
    }
    }
    return nullptr;
}
