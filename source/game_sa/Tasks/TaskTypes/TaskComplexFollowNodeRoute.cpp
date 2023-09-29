#include "StdInc.h"

#include "TaskComplexFollowNodeRoute.h"

void CTaskComplexFollowNodeRoute::InjectHooks() {
    RH_ScopedVirtualClass(CTaskComplexFollowNodeRoute, 0x8700a8, 11);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x66EA30);
    RH_ScopedInstall(Destructor, 0x66EB70);

    RH_ScopedInstall(CalcGoToTaskType, 0x66EBE0, { .reversed = false });
    RH_ScopedInstall(SetTarget, 0x671750, { .reversed = false });
    RH_ScopedInstall(CreateSubTask, 0x669690, { .reversed = false });
    RH_ScopedInstall(GetLastWaypoint, 0x6698E0, { .reversed = false });
    RH_ScopedInstall(ComputeRoute, 0x6699E0, { .reversed = false });
    RH_ScopedInstall(CalcBlendRatio, 0x66EDC0, { .reversed = false });
    RH_ScopedInstall(CanGoStraightThere, 0x66EF20, { .reversed = false });
    RH_ScopedInstall(ComputePathNodes, 0x66EFA0, { .reversed = false });

    RH_ScopedVMTInstall(Clone, 0x6713E0);
    RH_ScopedVMTInstall(GetTaskType, 0x66EB60);
    RH_ScopedVMTInstall(StopTimer, 0x6694E0);
    RH_ScopedVMTInstall(MakeAbortable, 0x669520, { .reversed = false });
    RH_ScopedVMTInstall(CreateNextSubTask, 0x6718D0, { .reversed = false });
    RH_ScopedVMTInstall(CreateFirstSubTask, 0x671800, { .reversed = false });
    RH_ScopedVMTInstall(ControlSubTask, 0x671AB0, { .reversed = false });
}

// 0x66EA30
CTaskComplexFollowNodeRoute::CTaskComplexFollowNodeRoute(
    eMoveState     moveState,
    const CVector& targetPt,
    float          targetPtTolerance,
    float          slowDownDist,
    float          followNodeThresholdHeightChange,
    bool           bKeepNodesHeadingAwayFromTarget,
    int32          time,
    bool           bUseBlending
) :
    m_MoveState{moveState},
    m_TargetPt{targetPt},
    m_TargetPtTolerance{targetPtTolerance},
    m_SlowDownDist{slowDownDist},
    m_FollowNodeThresholdHeightChange{followNodeThresholdHeightChange},
    m_bKeepNodesHeadingAwayFromTarget{bKeepNodesHeadingAwayFromTarget},
    m_Time{time},
    m_bUseBlending{bUseBlending},
    m_NodeRoute{new CNodeRoute{}},
    m_PtRoute{new CPointRoute{}}
{
}

// 0x6713E0
CTaskComplexFollowNodeRoute::CTaskComplexFollowNodeRoute(const CTaskComplexFollowNodeRoute& o) :
    CTaskComplexFollowNodeRoute{
        o.m_MoveState,
        o.m_TargetPt,
        o.m_TargetPtTolerance,
        o.m_SlowDownDist,
        o.m_FollowNodeThresholdHeightChange,
        o.m_bKeepNodesHeadingAwayFromTarget,
        o.m_Time,
        o.m_bUseBlending
    }
{
    m_StartNode = o.m_StartNode;
}

// 0x66EB70
CTaskComplexFollowNodeRoute::~CTaskComplexFollowNodeRoute() {
    delete m_PtRoute;
    delete m_NodeRoute;
}

// 0x6694E0
void CTaskComplexFollowNodeRoute::StopTimer(const CEvent* event) {
    if (!CEventHandler::IsTemporaryEvent(*event)) {
        m_Timer.Stop();
    }
}

// 0x6699E0
void CTaskComplexFollowNodeRoute::ComputeRoute() {
    return plugin::CallMethodAndReturn<void, 0x6699E0, CTaskComplexFollowNodeRoute*>(this);
}

// 0x66EBE0
eTaskType CTaskComplexFollowNodeRoute::CalcGoToTaskType(CPed* ped, eTaskType taskType) {
    return plugin::CallMethodAndReturn<eTaskType, 0x66EBE0, CTaskComplexFollowNodeRoute*, CPed*, eTaskType>(this, ped, taskType);
}

// 0x66EDC0
float CTaskComplexFollowNodeRoute::CalcBlendRatio(CPed* ped, bool bUsePointRoute) {
    return plugin::CallMethodAndReturn<float, 0x66EDC0, CTaskComplexFollowNodeRoute*, CPed *, bool>(this, ped, bUsePointRoute);
}

// 0x66EF20
bool CTaskComplexFollowNodeRoute::CanGoStraightThere(CPed* ped, const CVector& from, const CVector& to, float maxDist) {
    return plugin::CallMethodAndReturn<bool, 0x66EF20, CTaskComplexFollowNodeRoute*, CPed const&, CVector const&, CVector const&, float>(this, *ped, from, to, maxDist);
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

