#include "StdInc.h"

#include "TaskComplexFollowNodeRoute.h"

void CTaskComplexFollowNodeRoute::InjectHooks() {
    RH_ScopedClass(CTaskComplexFollowNodeRoute);
    RH_ScopedCategory("Tasks/TaskTypes");

    //RH_ScopedInstall(CTaskComplexFollowNodeRoute, 0x66EA30, { .reversed = false }); // TODO: Constructor
    //RH_ScopedInstall(CTaskComplexFollowNodeRoute, 0x66EB70, { .reversed = false }); // TODO: Constructor
    RH_ScopedInstall(Clone, 0x6713E0, { .reversed = false });
    RH_ScopedInstall(StopTimer, 0x6694E0, { .reversed = false });
    RH_ScopedInstall(MakeAbortable, 0x669520, { .reversed = false });
    RH_ScopedInstall(CreateSubTask, 0x669690, { .reversed = false });
    //RH_ScopedInstall(ComputeRoute, 0x6699E0, { .reversed = false });
    RH_ScopedInstall(CalcGoToTaskType, 0x66EBE0, { .reversed = false });
    //RH_ScopedInstall(CalcBlendRatio, 0x66EDC0, { .reversed = false });
    //RH_ScopedInstall(CanGoStraightThere, 0x66EF20, { .reversed = false });
    RH_ScopedInstall(ComputePathNodes, 0x66EFA0, { .reversed = false });
    RH_ScopedInstall(SetTarget, 0x671750, { .reversed = false });
    RH_ScopedInstall(CreateFirstSubTask, 0x671800, { .reversed = false });
    RH_ScopedInstall(CreateNextSubTask, 0x6718D0, { .reversed = false });
    RH_ScopedInstall(ControlSubTask, 0x671AB0, { .reversed = false });
}

// 0x66EA30
CTaskComplexFollowNodeRoute::CTaskComplexFollowNodeRoute(int32 mode, const CVector& targetPos, float radius, float fUnkn1, float fUnkn2, bool bUnknFlag, int32 time, bool bUnknFlag2) : CTaskComplex() {
    plugin::CallMethod<0x66EA30, CTaskComplexFollowNodeRoute*, int32, const CVector&, float, float, float, bool, int32, bool>(this, mode, targetPos, radius, fUnkn1, fUnkn2, bUnknFlag, time, bUnknFlag2);
}

// 0x66EB70
CTaskComplexFollowNodeRoute::~CTaskComplexFollowNodeRoute() {
    delete m_pPointRoute;
    delete m_pNodeRoute;
}

// 0x6713E0
CTask* CTaskComplexFollowNodeRoute::Clone() const {
    auto* task = new CTaskComplexFollowNodeRoute(m_nMode, m_vecTargetPos, m_fRadius, m_fUnkn1, m_fUnkn2, m_bUnknFlag0x1, m_nTime, m_bUnknFlag0x8);
    task->m_nodeAddress1 = m_nodeAddress1;
    return task;
}

// 0x6694E0
void CTaskComplexFollowNodeRoute::StopTimer(const CEvent* event) {
    plugin::CallMethod<0x6694E0, CTaskComplexFollowNodeRoute*, const CEvent*>(this, event);
    return;
    if (!CEventHandler::IsTemporaryEvent(*event) && bUnkn1) {
        m_bStoppedMaybe = true;
        m_nTimeStopped = m_nTimeStopped - (CTimer::GetTimeInMS() - m_nTimeStarted);
    }
}

// 0x66EBE0
eTaskType CTaskComplexFollowNodeRoute::CalcGoToTaskType(CPed* ped, eTaskType taskType) {
    return plugin::CallMethodAndReturn<eTaskType, 0x66EBE0, CTaskComplexFollowNodeRoute*, CPed*, eTaskType>(this, ped, taskType);
}

// 0x671750
void CTaskComplexFollowNodeRoute::SetTarget(CPed* ped, const CVector& target, float radius, float fUnkn1, float fUnkn2, bool bForce) {
    return plugin::CallMethodAndReturn<void, 0x671750, CTaskComplexFollowNodeRoute*, CPed const*, CVector const&, float, float, float, bool>(this, ped, target, radius, fUnkn1, fUnkn2, bForce);
}

// 0x669690
CTask* CTaskComplexFollowNodeRoute::CreateSubTask(eTaskType taskType, CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x669690, CTaskComplexFollowNodeRoute*, int32, CPed*>(this, taskType, ped);
}

// 0x6698E0
CVector CTaskComplexFollowNodeRoute::GetLastWaypoint(CPed* ped) {
    NOTSA_UNREACHABLE(); // This shit is RVO'd => I'm lazy to fix it
}

// 0x66EFA0
void CTaskComplexFollowNodeRoute::ComputePathNodes(CPed const* ped) {
    return plugin::CallMethodAndReturn<void, 0x66EFA0, CTaskComplexFollowNodeRoute*, CPed const*>(this, ped);
}

// 0x669520
bool CTaskComplexFollowNodeRoute::MakeAbortable(CPed* ped, eAbortPriority priority, CEvent const* event) {
    return plugin::CallMethodAndReturn<bool, 0x669520, CTaskComplexFollowNodeRoute*, CPed*, eAbortPriority, CEvent const*>(this, ped, priority, event);
}

// 0x6718D0
CTask* CTaskComplexFollowNodeRoute::CreateNextSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn< CTask*, 0x6718D0, CTaskComplexFollowNodeRoute*, CPed*>(this, ped);
}

// 0x671800
CTask* CTaskComplexFollowNodeRoute::CreateFirstSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn< CTask*, 0x671800, CTaskComplexFollowNodeRoute*, CPed*>(this, ped);
}

// 0x671AB0
CTask* CTaskComplexFollowNodeRoute::ControlSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn< CTask*, 0x671AB0, CTaskComplexFollowNodeRoute*, CPed*>(this, ped);
}

