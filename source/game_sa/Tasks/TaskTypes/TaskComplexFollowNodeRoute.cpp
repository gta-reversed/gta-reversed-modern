#include "StdInc.h"

#include "Interior/InteriorManager_c.h"

#include "TaskComplexFollowNodeRoute.h"

#include "Tasks/TaskTypes/TaskSimpleGoToPointFine.h"
#include "Tasks/TaskTypes/TaskComplexGoToPointAndStandStill.h"
#include "Tasks/TaskTypes/TaskComplexLeaveCar.h"
#include "Tasks/TaskTypes/TaskSimpleGoToPoint.h"
#include "Tasks/TaskTypes/TaskSimpleStandStill.h"

void CTaskComplexFollowNodeRoute::InjectHooks() {
    RH_ScopedVirtualClass(CTaskComplexFollowNodeRoute, 0x8700a8, 11);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x66EA30);
    RH_ScopedInstall(Destructor, 0x66EB70);

    RH_ScopedInstall(CalcGoToTaskType, 0x66EBE0);
    RH_ScopedInstall(SetTarget, 0x671750);
    RH_ScopedInstall(CreateSubTask, 0x669690);
    RH_ScopedInstall(GetLastWaypoint, 0x6698E0);
    RH_ScopedInstall(GetNextWaypoint, 0x669980);
    RH_ScopedInstall(ComputeRoute, 0x6699E0, { .reversed = false });
    RH_ScopedInstall(CalcBlendRatio, 0x66EDC0);
    RH_ScopedInstall(CanGoStraightThere, 0x66EF20);
    RH_ScopedInstall(ComputePathNodes, 0x66EFA0);

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
        m_CurrPtIdx = std::min(m_CurrPtIdx, m_PtRoute->GetSize() - 1);

        // Original code used signed int for `m_CurrPtIdx`, but it's seemingly never set to a negative value in the code
        // Thus we can simplify the code a whole lot
        assert((int32)m_CurrPtIdx >= 0); // Check sign bit (cruel version)
        //if (m_CurrPtIdx < 0) {
        //    return TASK_SIMPLE_GO_TO_POINT;
        //}

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
bool CTaskComplexFollowNodeRoute::CanGoStraightThere(const CPed* ped, const CVector& from, const CVector& to, float maxDist) {
    if ((from - to).SquaredMagnitude() >= sq(maxDist)) {
        return false;
    }
    if (ped->bIgnoreHeightDifferenceFollowingNodes) {
        return true;
    }
    return CPedGeometryAnalyser::IsWanderPathClear(from, to, m_FollowNodeThresholdHeightChange, 4) == CPedGeometryAnalyser::WanderPathClearness::CLEAR;
}

// 0x671750
void CTaskComplexFollowNodeRoute::SetTarget(CPed* ped, const CVector& targetPt, float targetPtTolerance, float slowDownDistance, float followNodeThresholdHeightChange, bool bForce) {
    if (!bForce) {
        if (m_TargetPt == targetPt && m_TargetPtTolerance == targetPtTolerance && m_SlowDownDist == slowDownDistance && m_FollowNodeThresholdHeightChange == followNodeThresholdHeightChange) {
            return; // Nothing changed
        }
    }

    m_TargetPt                        = targetPt;
    m_TargetPtTolerance               = targetPtTolerance;
    m_SlowDownDist                    = slowDownDistance;
    m_FollowNodeThresholdHeightChange = followNodeThresholdHeightChange;

    if (m_bUseBlending) {
        m_SpeedDecreaseDist = m_SpeedIncreaseDist = 0.0;
        m_SpeedDecreaseAmt  = m_SpeedIncreaseAmt  = 0.f;
        m_bSlowingDown      = m_bSpeedingUp       = false;
    }

    ComputePathNodes(ped);
    ComputeRoute();

    m_bNewTarget = true;
}

// 0x669690
CTask* CTaskComplexFollowNodeRoute::CreateSubTask(eTaskType taskType, CPed* ped) const {
    switch (taskType) {
    case TASK_SIMPLE_GO_TO_POINT_FINE:
        return new CTaskSimpleGoToPointFine{ CTaskSimpleGoToPointFine::BaseRatio(m_MoveState), GetCurrentPt() };
    case TASK_COMPLEX_GO_TO_POINT_AND_STAND_STILL:
        return new CTaskComplexGoToPointAndStandStill{ m_MoveState, GetCurrentPt(), m_TargetPtTolerance, m_SlowDownDist };
    case TASK_COMPLEX_LEAVE_CAR:
        return new CTaskComplexLeaveCar{ ped->m_pVehicle, TARGET_DOOR_FRONT_LEFT, 0, true, false };
    case TASK_SIMPLE_GO_TO_POINT:
        return new CTaskSimpleGoToPoint{ m_MoveState, GetCurrentPt() };
    case TASK_SIMPLE_STAND_STILL: {
        ped->Teleport(m_TargetPt, false); // NOTE/TODO: I guess accidentally left in? Or hacky workaround?
        return new CTaskSimpleStandStill{};
    }
    case TASK_FINISHED:
        return nullptr;
    default:
        NOTSA_UNREACHABLE();
    }
}

// 0x6698E0
CVector CTaskComplexFollowNodeRoute::GetLastWaypoint(CPed* ped) {
    if (m_PtRoute->GetSize() == 1) {
        return (*m_PtRoute)[0];
    }
    return m_CurrPtIdx != 0
        ? (*m_PtRoute)[m_CurrPtIdx - 1]
        : ped->GetPosition();
}

// 0x669980
CVector CTaskComplexFollowNodeRoute::GetNextWaypoint(CPed* ped) {
    if (m_PtRoute->GetSize() == 1) {
        return (*m_PtRoute)[0];
    }
    const auto nextPt = m_CurrPtIdx + 1;
    return (*m_PtRoute)[nextPt < m_PtRoute->GetSize() ? nextPt : m_CurrPtIdx - 1];
}

// 0x66EFA0
void CTaskComplexFollowNodeRoute::ComputePathNodes(CPed const* ped) {
    // Make sure TargetPt.z is on the ground
    {
        bool hasTargetPtGroundZ;
        float targetPtGroundZ = CWorld::FindGroundZFor3DCoord(m_TargetPt + CVector{0.f, 0.f, 1.f}, &hasTargetPtGroundZ);
        if (hasTargetPtGroundZ) {
            m_TargetPt.z = targetPtGroundZ + 1.f;
        }
    }

    const CVector pedPos = ped->GetPosition();

    if (CanGoStraightThere(ped, pedPos, m_TargetPt, ped->GetIntelligence()->m_FollowNodeThresholdDist)) {
        ThePaths.ComputeRoute(
            PATH_TYPE_PED,
            ped->GetPosition(),
            m_TargetPt,
            m_StartNode,
            *m_NodeRoute
        );
        m_StartNode = {};
    }

    if (std::abs(pedPos.z - m_TargetPt.z) >= m_FollowNodeThresholdHeightChange || m_NodeRoute->IsEmpty() || m_bKeepNodesHeadingAwayFromTarget) { // 0x66F147
        if (!m_NodeRoute->IsEmpty() && !m_bKeepNodesHeadingAwayFromTarget && m_NodeRoute->GetAll()[0]) {
            const auto routeFirstNode = m_NodeRoute->GetAll()[0];
            if (ThePaths.IsAreaNodesAvailable(routeFirstNode)) {
                if ((m_TargetPt - pedPos).Magnitude2D() + 50.f < (ThePaths.GetPathNode(routeFirstNode)->GetPosition() - pedPos).Magnitude2D()) {
                    m_NodeRoute->Clear(); // 0x66F209
                }
            }
        }
    } else if (m_NodeRoute->GetAll()[0]) {
        const auto routeFirstNode = m_NodeRoute->GetAll()[0];
        if (ThePaths.IsAreaNodesAvailable(routeFirstNode)) {
            if ((m_TargetPt - pedPos).Magnitude2D() + 3.f < (ThePaths.GetPathNode(routeFirstNode)->GetPosition() - pedPos).Magnitude2D()) {
                m_NodeRoute->Clear(); // 0x66F139
            }
        }
    }

    if (g_interiorMan.GetPedsInteriorGroup(ped)) { // 0x66F216
        if (!m_NodeRoute->IsEmpty()) {
            const auto routeFirstNode = m_NodeRoute->GetAll()[0];
            if (routeFirstNode && ThePaths.IsAreaNodesAvailable(routeFirstNode)) {
                const auto pedInt = g_interiorMan.GetPedsInterior(ped); // 0x66F2EE

                auto routeFirstNodeCoors = ThePaths.GetPathNode(routeFirstNode)->GetPosition();
                routeFirstNodeCoors.z += 1.f;
                const auto routeFirstNodeInt = g_interiorMan.GetVectorsInterior(routeFirstNodeCoors); // 0x66F330

                if (pedInt) {
                    if (pedInt != routeFirstNodeInt) {
                        if (!ThePaths.These2NodesAreAdjacent(routeFirstNode, pedInt->GetNodeAddress())) {
                            m_NodeRoute->Clear();
                            ThePaths.ComputeRoute( // 0x66F38D
                                PATH_TYPE_PED,
                                ped->GetPosition(),
                                m_TargetPt,
                                pedInt->GetNodeAddress(),
                                *m_NodeRoute
                            );
                        }
                    }
                } else if (routeFirstNodeInt) {
                    if (!ThePaths.These2NodesAreAdjacent(routeFirstNode, routeFirstNodeInt->GetNodeAddress())) {
                        m_NodeRoute->Clear();
                        ThePaths.ComputeRoute( // 0x66F3E0
                            PATH_TYPE_PED,
                            ped->GetPosition(),
                            m_TargetPt,
                            pedInt->GetNodeAddress(),
                            *m_NodeRoute
                        );
                        m_NodeRoute->Reverse();
                    }
                }
            }
        }
    } else {
        // Make the route as short as possible by "cutting" down excess nodes
        for (const auto& [i, node] : notsa::enumerate(m_NodeRoute->GetAll())) {
            assert(node); // Original code checks for this too, but I don't think this is possible

            CVector nodePos;
            if (ThePaths.IsAreaNodesAvailable(node)) {
                nodePos = ThePaths.GetPathNode(node)->GetPosition();
            } else if (notsa::IsFixBugs()) {
                continue; 
            }
            nodePos.z += 1.f;
            if (CanGoStraightThere(ped, nodePos, m_TargetPt, ped->GetIntelligence()->m_FollowNodeThresholdDist)) {
                m_NodeRoute->ResizeTo(i + 1);
                break;
            }
        }
    }

    // 0x66F3F2
    m_CurrPtIdx = m_CurrNode
        ? notsa::indexof(m_NodeRoute->GetAll(), m_CurrNode, 0)
        : 0;
    if (!m_NodeRoute->IsEmpty()) {
        m_CurrNode = (*m_NodeRoute)[m_CurrPtIdx];
    }
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

