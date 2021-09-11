#include "StdInc.h"

void CTaskComplexGoToPointAndStandStill::InjectHooks()
{
    ReversibleHooks::Install("CTaskComplexGoToPointAndStandStill", "CTaskComplexGoToPointAndStandStill", 0x668120, &CTaskComplexGoToPointAndStandStill::Constructor);
    ReversibleHooks::Install("CTaskComplexGoToPointAndStandStill", "Clone", 0x66CEA0, &CTaskComplexGoToPointAndStandStill::Clone_Reversed);
    ReversibleHooks::Install("CTaskComplexGoToPointAndStandStill", "CreateNextSubTask", 0x66DBA0, &CTaskComplexGoToPointAndStandStill::CreateNextSubTask_Reversed);
    ReversibleHooks::Install("CTaskComplexGoToPointAndStandStill", "CreateFirstSubTask", 0x66DC40, &CTaskComplexGoToPointAndStandStill::CreateFirstSubTask_Reversed);
    ReversibleHooks::Install("CTaskComplexGoToPointAndStandStill", "CreateFirstSubTask_ped", 0x6682D0, (CTask*(CTaskComplexGoToPointAndStandStill::*)(int32, CPed*)) & CTaskComplexGoToPointAndStandStill::CreateFirstSubTask);
    ReversibleHooks::Install("CTaskComplexGoToPointAndStandStill", "ControlSubTask", 0x668570, &CTaskComplexGoToPointAndStandStill::ControlSubTask_Reversed);
    ReversibleHooks::Install("CTaskComplexGoToPointAndStandStill", "GoToPoint", 0x46FE60, &CTaskComplexGoToPointAndStandStill::GoToPoint);
    ReversibleHooks::Install("CTaskComplexGoToPointAndStandStill", "SelectMoveState", 0x668250, &CTaskComplexGoToPointAndStandStill::SelectMoveState);
}

CTaskComplexGoToPointAndStandStill::CTaskComplexGoToPointAndStandStill(int32 moveState, const CVector& targetPoint, float fRadius, float fMoveStateRadius, bool bUnknown, bool bGoToPoint)
{
    m_moveState = moveState;
    m_nFlags = 0;
    m_b01 = bUnknown;
    m_bTargetPointUpdated = true;
    m_bGoToPoint = bGoToPoint;
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
        }
        else if (m_fRadius < 1.0f)
        {
            m_fRadius = 1.0f;
            m_fMoveStateRadius = 0.0f;
            return;
        }
        m_fMoveStateRadius = 0.0f;
    }
}

CTaskComplexGoToPointAndStandStill::~CTaskComplexGoToPointAndStandStill()
{
    // nothing here
}

CTaskComplexGoToPointAndStandStill* CTaskComplexGoToPointAndStandStill::Constructor(int32 moveState, const CVector& targetPoint, float fRadius, float fMoveStateRadius, bool bUnknown, bool bGoToPoint)
{
#ifdef USE_DEFAULT_FUNCTIONS 
    return plugin::CallMethodAndReturn< CTaskComplexGoToPointAndStandStill*, 0x668120, CTask*, int32, const CVector &, float, float, bool, bool>
        (this, moveState, targetPoint, fRadius, fMoveStateRadius, bUnknown, bGoToPoint);
#else
    this->CTaskComplexGoToPointAndStandStill::CTaskComplexGoToPointAndStandStill(moveState, targetPoint, fRadius, fMoveStateRadius, bUnknown, bGoToPoint);
    return this;
#endif
}

CTask* CTaskComplexGoToPointAndStandStill::Clone()
{
#ifdef USE_DEFAULT_FUNCTIONS 
    return plugin::CallMethodAndReturn<CTask*, 0x66CEA0, CTask*>(this);
#else
    return CTaskComplexGoToPointAndStandStill::Clone_Reversed();
#endif
}

CTask* CTaskComplexGoToPointAndStandStill::CreateNextSubTask(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS 
    return plugin::CallMethodAndReturn<CTask*, 0x66DBA0, CTask*, CPed*>(this, ped);
#else
    return CTaskComplexGoToPointAndStandStill::CreateNextSubTask_Reversed(ped);
#endif
}

CTask* CTaskComplexGoToPointAndStandStill::CreateFirstSubTask(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS 
    return plugin::CallMethodAndReturn<CTask*, 0x66DC40, CTask*, CPed*>(this, ped);
#else
    return CTaskComplexGoToPointAndStandStill::CreateFirstSubTask_Reversed(ped);
#endif
}

CTask* CTaskComplexGoToPointAndStandStill::ControlSubTask(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS 
    return plugin::CallMethodAndReturn<CTask*, 0x668570, CTask*, CPed*>(this, ped);
#else
    return CTaskComplexGoToPointAndStandStill::ControlSubTask_Reversed(ped);
#endif
}

CTask* CTaskComplexGoToPointAndStandStill::Clone_Reversed()
{
    return new CTaskComplexGoToPointAndStandStill(m_moveState, m_vecTargetPoint, m_fRadius, m_fMoveStateRadius, m_b01, m_bGoToPoint);
}

CTask* CTaskComplexGoToPointAndStandStill::CreateNextSubTask_Reversed(CPed* ped)
{
    switch (m_pSubTask->GetTaskType())
    {
    case TASK_SIMPLE_STAND_STILL:
        return CreateFirstSubTask(TASK_FINISHED, ped);
    case TASK_COMPLEX_LEAVE_CAR:
        if (ped->bInVehicle)
            return CreateFirstSubTask(TASK_FINISHED, ped);
        return CreateFirstSubTask(TASK_SIMPLE_GO_TO_POINT,ped);
    case TASK_SIMPLE_GO_TO_POINT:
        m_b05 = static_cast<CTaskSimpleGoToPoint*>(m_pSubTask)->gotoPointFlags.m_b03;
        return CreateFirstSubTask(TASK_SIMPLE_STAND_STILL, ped);
        break;
    }
    return nullptr;
}

CTask* CTaskComplexGoToPointAndStandStill::CreateFirstSubTask_Reversed(CPed* ped)
{
    m_bTargetPointUpdated = false;
    if (ped->bInVehicle)
        return CreateFirstSubTask(TASK_COMPLEX_LEAVE_CAR, ped);
    return CreateFirstSubTask(TASK_SIMPLE_GO_TO_POINT, ped);
}

CTask* CTaskComplexGoToPointAndStandStill::ControlSubTask_Reversed(CPed* ped)
{
    if (m_bTargetPointUpdated) {
        if (m_pSubTask->MakeAbortable(ped, ABORT_PRIORITY_URGENT, nullptr))
            return CreateFirstSubTask(ped);
    }
    else if (m_pSubTask->GetTaskType() == TASK_SIMPLE_GO_TO_POINT) {
        auto pGotoPointTask = static_cast<CTaskSimpleGoToPoint*>(m_pSubTask);
        if (m_moveState == PEDMOVE_RUN)
            SelectMoveState(pGotoPointTask, ped, m_fMoveStateRadius, 100000000.0f);
        else if (m_moveState == PEDMOVE_SPRINT)
            SelectMoveState(pGotoPointTask, ped, m_fMoveStateRadius, 10.0f);
        return m_pSubTask;
    }
    return m_pSubTask;
}

void CTaskComplexGoToPointAndStandStill::GoToPoint(const CVector& targetPoint, float fRadius, float fMoveStateRadius, bool bUpdateTargetEvenIfItsTheSame)
{
#ifdef USE_DEFAULT_FUNCTIONS 
    plugin::CallMethod<0x46FE60, CTask*, const CVector &, float, float, bool>(this, targetPoint, fRadius, fMoveStateRadius, bUpdateTargetEvenIfItsTheSame);
#else
    if (bUpdateTargetEvenIfItsTheSame || m_vecTargetPoint != targetPoint || m_fMoveStateRadius != fMoveStateRadius) {
        m_vecTargetPoint = targetPoint;
        m_fRadius = fRadius;
        m_fMoveStateRadius = fMoveStateRadius;
        m_bTargetPointUpdated = true;
    }
#endif
}

void CTaskComplexGoToPointAndStandStill::SelectMoveState(CTaskSimpleGoToPoint* pGotoPointTask, CPed* ped, float fMoveStateRadius, float fRunOrSprintRadius)
{
#ifdef USE_DEFAULT_FUNCTIONS 
    plugin::CallMethod <0x668250, CTask*, CTaskSimpleGoToPoint *, CPed *, float, float>(this, pGotoPointTask, ped, fMoveStateRadius, fRunOrSprintRadius);
#else
    CVector2D vecDistance = ped->GetPosition() - pGotoPointTask->m_vecTargetPoint;
    const float fSquaredMagnitude = vecDistance.SquaredMagnitude();
    if (fSquaredMagnitude >= fMoveStateRadius * fMoveStateRadius) {
        if (fSquaredMagnitude >= fRunOrSprintRadius * fRunOrSprintRadius)
            pGotoPointTask->m_moveState = PEDMOVE_SPRINT;
        else
            pGotoPointTask->m_moveState = PEDMOVE_RUN;
    }
    else {
        pGotoPointTask->m_moveState = PEDMOVE_WALK;
    }
#endif
}

CTask* CTaskComplexGoToPointAndStandStill::CreateFirstSubTask(int32 taskId, CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS 
    return plugin::CallMethodAndReturn <CTask*, 0x6682D0, CTask*, int32, CPed *>(this, taskId, ped);
#else
    if (taskId > TASK_COMPLEX_LEAVE_CAR) {
        if (taskId != TASK_SIMPLE_GO_TO_POINT)
            return nullptr;
        CTaskSimpleGoToPoint* pGotoPointTask = new CTaskSimpleGoToPoint(m_moveState, m_vecTargetPoint, m_fRadius, false, m_b01);
        if (m_b04)
            pGotoPointTask->gotoPointFlags.m_b05 = true;
        if (m_moveState == PEDMOVE_RUN)
            SelectMoveState(pGotoPointTask, ped, m_fMoveStateRadius, 100000000.0f);
        else if (m_moveState == PEDMOVE_SPRINT)
            SelectMoveState(pGotoPointTask, ped, m_fMoveStateRadius, 10.0f);
        return pGotoPointTask;
    }
    switch (taskId)
    {
    case TASK_COMPLEX_LEAVE_CAR: {
        auto pTaskLeaveCar = (CTaskComplexLeaveCar*)CTask::operator new(0x34);
        if (!pTaskLeaveCar)
            return nullptr;
        return pTaskLeaveCar->Constructor(ped->m_pVehicle, 0, 0, true, false);
    }
    case TASK_SIMPLE_PAUSE:
        return new CTaskSimplePause(1);
    case TASK_SIMPLE_STAND_STILL: {
        if (m_bGoToPoint && m_pSubTask && m_pSubTask->GetTaskType() == TASK_SIMPLE_GO_TO_POINT) {
            CVector vecDistance = m_vecTargetPoint - ped->GetPosition(); 
            float fDotProduct = DotProduct(&vecDistance, &ped->GetForward());
            float fBlendDelta = 8.0f;
            if (ped->m_vecAnimMovingShiftLocal.y >= 0.01f) {
                fBlendDelta = 50.0f / ((fDotProduct / (ped->m_vecAnimMovingShiftLocal.y * 0.5f) - 1.0f) * CTimer::ms_fTimeStep);
                if (fDotProduct <= 0.01f || fBlendDelta > 16.0f)
                    fBlendDelta = 16.0f;
            }
            return new CTaskSimpleStandStill(2000, false, true, fBlendDelta);
        }
        return new CTaskSimpleStandStill(1, false, false, 8.0f);
    }
    }
    return nullptr;
#endif
}
