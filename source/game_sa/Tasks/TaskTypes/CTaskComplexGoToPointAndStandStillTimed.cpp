#include "StdInc.h"

void CTaskComplexGoToPointAndStandStillTimed::InjectHooks()
{
    ReversibleHooks::Install("CTaskComplexGoToPointAndStandStillTimed", "CTaskComplexGoToPointAndStandStillTimed", 0x6685E0, &CTaskComplexGoToPointAndStandStillTimed::Constructor);
    ReversibleHooks::Install("CTaskComplexGoToPointAndStandStillTimed", "Clone", 0x66CF30, &CTaskComplexGoToPointAndStandStillTimed::Clone_Reversed);
    ReversibleHooks::Install("CTaskComplexGoToPointAndStandStillTimed", "StopTimer", 0x6686A0, &CTaskComplexGoToPointAndStandStillTimed::StopTimer_Reversed);
    ReversibleHooks::Install("CTaskComplexGoToPointAndStandStillTimed", "MakeAbortable", 0x668640, &CTaskComplexGoToPointAndStandStillTimed::MakeAbortable_Reversed);
    ReversibleHooks::Install("CTaskComplexGoToPointAndStandStillTimed", "CreateFirstSubTask", 0x66DC90, &CTaskComplexGoToPointAndStandStillTimed::CreateFirstSubTask_Reversed);
    ReversibleHooks::Install("CTaskComplexGoToPointAndStandStillTimed", "ControlSubTask", 0x66DCE0, &CTaskComplexGoToPointAndStandStillTimed::ControlSubTask_Reversed);
}

CTaskComplexGoToPointAndStandStillTimed::CTaskComplexGoToPointAndStandStillTimed(int moveState, const CVector& targetPoint, float fRadius, float fMoveStateRadius, int time)
    : CTaskComplexGoToPointAndStandStill(moveState, targetPoint, fRadius, fMoveStateRadius, false, false)
{
    m_nTime = time;
}

CTaskComplexGoToPointAndStandStillTimed::~CTaskComplexGoToPointAndStandStillTimed()
{
    // nothing here
}

CTaskComplexGoToPointAndStandStillTimed* CTaskComplexGoToPointAndStandStillTimed::Constructor(int moveState, const CVector& targetPoint, float fRadius, float fMoveStateRadius, int time)
{
#ifdef USE_DEFAULT_FUNCTIONS 
    return plugin::CallMethodAndReturn<CTaskComplexGoToPointAndStandStillTimed*, 0x6685E0, CTask*, int, const CVector&, float, float, int>
        (this, moveState, targetPoint, fRadius, fMoveStateRadius, time);
#else
    this->CTaskComplexGoToPointAndStandStillTimed::CTaskComplexGoToPointAndStandStillTimed(moveState,  targetPoint, fRadius, fMoveStateRadius, time);
    return this;
#endif
}

CTask* CTaskComplexGoToPointAndStandStillTimed::Clone()
{
#ifdef USE_DEFAULT_FUNCTIONS 
    return plugin::CallMethodAndReturn<CTask*, 0x66CF30, CTask*>(this);
#else
    return CTaskComplexGoToPointAndStandStillTimed::Clone_Reversed();
#endif
}

// 0x6686A0
void CTaskComplexGoToPointAndStandStillTimed::StopTimer(const CEvent* event)
{
    return CTaskComplexGoToPointAndStandStillTimed::StopTimer_Reversed(event);
}

// 0x668640
bool CTaskComplexGoToPointAndStandStillTimed::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event)
{
    return CTaskComplexGoToPointAndStandStillTimed::MakeAbortable_Reversed(ped, priority, event);
}

CTask* CTaskComplexGoToPointAndStandStillTimed::CreateFirstSubTask(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS 
    return plugin::CallMethodAndReturn<CTask*, 0x66DC90, CTask*, CPed*>(this, ped);
#else
    return CTaskComplexGoToPointAndStandStillTimed::CreateFirstSubTask_Reversed(ped);
#endif
}

CTask* CTaskComplexGoToPointAndStandStillTimed::ControlSubTask(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS 
    return plugin::CallMethodAndReturn<CTask*, 0x66DCE0, CTask*, CPed*>(this, ped);
#else
    return CTaskComplexGoToPointAndStandStillTimed::ControlSubTask_Reversed(ped);
#endif
}

CTask* CTaskComplexGoToPointAndStandStillTimed::Clone_Reversed()
{
    return new CTaskComplexGoToPointAndStandStillTimed(m_moveState, m_vecTargetPoint, m_fRadius, m_fMoveStateRadius, m_nTime);
}


void CTaskComplexGoToPointAndStandStillTimed::StopTimer_Reversed(const CEvent* event)
{
    if (!CEventHandler::IsTemporaryEvent(*event))
        m_timer.Stop();
}

bool CTaskComplexGoToPointAndStandStillTimed::MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, const CEvent* event)
{
    bool bSubTaskAbortable = m_pSubTask->MakeAbortable(ped, priority, event);
    if (bSubTaskAbortable && priority == ABORT_PRIORITY_URGENT && (!event || !CEventHandler::IsTemporaryEvent(*event)))
        m_timer.Stop();
    return bSubTaskAbortable;
}

CTask* CTaskComplexGoToPointAndStandStillTimed::CreateFirstSubTask_Reversed(CPed* ped)
{
    m_timer.Start(m_nTime);
    m_bTargetPointUpdated = false;
    if (ped->bInVehicle)
        return CTaskComplexGoToPointAndStandStill::CreateFirstSubTask(TASK_COMPLEX_LEAVE_CAR, ped);
    return CTaskComplexGoToPointAndStandStill::CreateFirstSubTask(TASK_SIMPLE_GO_TO_POINT, ped);
}

CTask* CTaskComplexGoToPointAndStandStillTimed::ControlSubTask_Reversed(CPed* ped)
{
    if (m_timer.Reset()) {
        if (m_timer.IsOutOfTime() && 
            m_pSubTask->GetId() != TASK_SIMPLE_STAND_STILL && CPedPlacement::FindZCoorForPed(&m_vecTargetPoint)) {            
            ped->SetPosn(m_vecTargetPoint);
        }
    }
    return CTaskComplexGoToPointAndStandStill::ControlSubTask(ped);
}
