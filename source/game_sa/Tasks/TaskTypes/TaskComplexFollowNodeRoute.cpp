#include "StdInc.h"

#include "TaskComplexFollowNodeRoute.h"

#include "Tasks/TaskTypes/TaskSimpleGoToPointFine.h"

void CTaskComplexFollowNodeRoute::InjectHooks() {
    RH_ScopedVirtualClass(CTaskComplexFollowNodeRoute, 0x8700a8, 11);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x66EA30);
    RH_ScopedInstall(Destructor, 0x66EB70);

    RH_ScopedInstall(CalcGoToTaskType, 0x66EBE0);
    RH_ScopedInstall(SetTarget, 0x671750, { .reversed = false });
    RH_ScopedInstall(CreateSubTask, 0x669690, { .reversed = false });
    RH_ScopedInstall(GetLastWaypoint, 0x6698E0, { .reversed = false });
    RH_ScopedInstall(GetNextWaypoint, 0x669980, { .reversed = false });
    RH_ScopedInstall(ComputeRoute, 0x6699E0, { .reversed = false });
    RH_ScopedInstall(CalcBlendRatio, 0x66EDC0);
    RH_ScopedInstall(CanGoStraightThere, 0x66EF20);
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
eTaskType CTaskComplexFollowNodeRoute::CalcGoToTaskType(CPed* ped, eTaskType subTaskType) {
    if (subTaskType != TASK_SIMPLE_GO_TO_POINT) {
        return subTaskType;
    }

    m_SpeedIncreaseAmt = m_SpeedDecreaseAmt;
    m_bWillSlowDown    = false;

    if (m_MoveState >= PEDMOVE_JOG) {
        m_CurrPt = std::min(m_CurrPt, (int32)m_PtRoute->GetNumPt() - 1);

        if (m_CurrPt < 0) {
            return TASK_SIMPLE_GO_TO_POINT;
        }

        const auto& currPt                     = GetCurrentPt();
        const auto  cosAngleBetweenRoutePoints = (currPt - GetLastWaypoint(ped)).Normalized().Dot((GetNextWaypoint(ped) - currPt).Normalized()); // I'm pretty sure they're missing an `abs` here
        if (m_bWillSlowDown = cosAngleBetweenRoutePoints <= COS_45) { // Keep in mind that the angles are inverted, so `<= COS_45` means "angle is more than 45"
            const auto sprint   = m_MoveState == PEDMOVE_SPRINT;
            m_SpeedIncreaseDist = m_SpeedDecreaseDist = sprint ? 5.f : 4.f;
            m_SpeedDecreaseAmt  = std::clamp(1.f - (cosAngleBetweenRoutePoints + 1.f) / (COS_45 + 1.f), 0.f, 1.f) * (sprint ? 3.f : 1.5f); 
        }
    }

    if (m_bSlowingDown) {
        m_bSlowingDown = false;
        m_bSpeedingUp  = true;
        return TASK_SIMPLE_GO_TO_POINT_FINE;
    } else {
        m_bSpeedingUp  = false;
        m_bSlowingDown = false;
        return TASK_SIMPLE_GO_TO_POINT;
    }
}

// 0x66EDC0
float CTaskComplexFollowNodeRoute::CalcBlendRatio(CPed* ped, bool slowing) {
    const auto spdChangeDistSq = sq(slowing ? m_SpeedDecreaseDist : m_SpeedIncreaseDist);
    const auto distToPtSq      = ((slowing ? GetCurrentPt() : GetLastWaypoint(ped)) - ped->GetPosition()).SquaredMagnitude();
    if (distToPtSq >= spdChangeDistSq) {
        return -1.f;
    }
    const auto spdChangeAmt   = slowing ? m_SpeedDecreaseAmt : m_SpeedIncreaseAmt;
    const auto spdChangeRatio = std::cos(std::clamp(distToPtSq / spdChangeDistSq, 0.f, 1.f) * PI) * 0.5f + 0.5f; // NOTE/BUG: Not sure how well diving squared values will work out :D
    return std::max(
        CTaskSimpleGoToPointFine::BaseRatio(PEDMOVE_WALK) + 0.75f,
        CTaskSimpleGoToPointFine::BaseRatio(m_MoveState) - spdChangeRatio * spdChangeAmt
    );
}

// 0x66EF20
bool CTaskComplexFollowNodeRoute::CanGoStraightThere(CPed* ped, const CVector& from, const CVector& to, float maxDist) {
    if ((from - to).SquaredMagnitude() >= sq(maxDist)) {
        return false;
    }
    if (ped->bIgnoreHeightDifferenceFollowingNodes) {
        return true;
    }
    return CPedGeometryAnalyser::IsWanderPathClear(from, to, m_FollowNodeThresholdHeightChange, 4) == CPedGeometryAnalyser::WanderPathClearness::CLEAR;
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
    return plugin::CallMethodAndReturn<CVector, 0x6698E0>(this, ped);
}

// 0x669980
CVector CTaskComplexFollowNodeRoute::GetNextWaypoint(CPed* ped) {
    return plugin::CallMethodAndReturn<CVector, 0x669980>(this, ped);
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

