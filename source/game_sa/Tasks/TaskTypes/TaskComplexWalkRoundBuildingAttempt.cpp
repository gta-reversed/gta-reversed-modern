#include "StdInc.h"

#include "TaskComplexWalkRoundBuildingAttempt.h"
#include "TaskSimpleAchieveHeading.h"
#include "TaskComplexFollowPointRoute.h"
#include "TaskSimpleGoToPoint.h"
#include "TaskSimpleStandStill.h"
#include "TaskSimpleHitWall.h"
#include "TaskSimpleScratchHead.h"
#include "TaskSimpleLookAbout.h"

void CTaskComplexWalkRoundBuildingAttempt::InjectHooks() {
    RH_ScopedVirtualClass(CTaskComplexWalkRoundBuildingAttempt, 0x86f334, 11);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x654740);
    RH_ScopedInstall(Destructor, 0x654950);

    RH_ScopedInstall(ComputeMoveDir, 0x654B80);
    RH_ScopedInstall(CreateSubTask, 0x654C80);
    RH_ScopedInstall(ComputeCrapRoute, 0x656F80);
    RH_ScopedInstall(ComputeRoute, 0x657BA0);

    RH_ScopedVMTInstall(Clone, 0x655B90);
    RH_ScopedVMTInstall(GetTaskType, 0x654830);
    RH_ScopedVMTInstall(MakeAbortable, 0x6549D0);
    RH_ScopedVMTInstall(CreateNextSubTask, 0x656E70);
    RH_ScopedVMTInstall(CreateFirstSubTask, 0x654A00);
    RH_ScopedVMTInstall(ControlSubTask, 0x658020);
}

// 0x654740
CTaskComplexWalkRoundBuildingAttempt::CTaskComplexWalkRoundBuildingAttempt(eMoveState moveState, CVector const& targetPos, CVector const& pos, CVector const& normal, bool flag_0x1) :
    m_target{targetPos},
    m_pos{pos},
    m_normal{normal},
    m_flag0x1{flag_0x1},
    m_moveState{(int8)moveState}
{
    m_normal.z = 0.f;
    m_normal.Normalise();
}

CTaskComplexWalkRoundBuildingAttempt::CTaskComplexWalkRoundBuildingAttempt(const CTaskComplexWalkRoundBuildingAttempt& o) :
    CTaskComplexWalkRoundBuildingAttempt{(eMoveState)o.m_moveState, o.m_target, o.m_pos, o.m_normal, o.m_flag0x1}
{
}

// 0x654950
CTaskComplexWalkRoundBuildingAttempt::~CTaskComplexWalkRoundBuildingAttempt() {
    for (auto route : { m_crapRoute, m_route }) {
        if (route) {
            delete route;
        }
    }
    CEntity::SafeCleanUpRef(m_entity);
}

// 0x654B80
void CTaskComplexWalkRoundBuildingAttempt::ComputeMoveDir(CPed const& ped, CVector& outDir) {
    const CVector2D normal{ m_normal };
    const CVector2D targetToPos = m_target - m_pos;
    outDir = CVector{ targetToPos - targetToPos.ProjectOnToNormal(normal), 0.f };
}

// 0x654C80
CTask* CTaskComplexWalkRoundBuildingAttempt::CreateSubTask(eTaskType taskType, CPed* ped) {
    switch (taskType) {
    case TASK_SIMPLE_ACHIEVE_HEADING:
        /*
        * Achieve heading to the first point of the point route
        */
        assert(approxEqual(
            (m_route->m_vecPoints[0] - ped->GetPosition()).Heading(),
            CGeneral::LimitRadianAngle(CGeneral::GetRadianAngleBetweenPoints({ m_route->m_vecPoints[0] - ped->GetPosition() }, {})),
            0.001f
        )); // TODO: Remove if doesn't assert
        return new CTaskSimpleAchieveHeading{
            (m_route->m_vecPoints[0] - ped->GetPosition()).Heading(),
            1.f,
            0.1f
        };
    case TASK_COMPLEX_FOLLOW_POINT_ROUTE:
        return new CTaskComplexFollowPointRoute{
            (eMoveState)m_moveState,
            *m_route,
            CTaskComplexFollowPointRoute::Mode::ONE_WAY,
            0.5f,
            0.5f,
            false,
            false,
            true
        };
    case TASK_SIMPLE_GO_TO_POINT:
        return new CTaskSimpleGoToPoint{
            (eMoveState)m_moveState,
            m_target,
            0.5f,
            false,
            false
        };
    case TASK_SIMPLE_STAND_STILL:
        return new CTaskSimpleStandStill{1000};
    case TASK_SIMPLE_HIT_WALL:
        return new CTaskSimpleHitWall{};
    case TASK_SIMPLE_SCRATCH_HEAD:
        return new CTaskSimpleScratchHead{};
    case TASK_SIMPLE_LOOK_ABOUT:
        return new CTaskSimpleLookAbout{1000};
    case TASK_FINISHED:
        return nullptr;
    default:
        NOTSA_UNREACHABLE();
    }
}

// 0x656F80
void CTaskComplexWalkRoundBuildingAttempt::ComputeCrapRoute(CPed const& ped) {
    // Added pre-condition to skip all of the calculation, instead of testing it at the very end.
    if (!m_crapRoute->IsFull()) {
        const auto& pedPos = ped.GetPosition() - CVector{ 0.f, 0.f, 0.5f }; // Ped's position is it's center, so adjust it to be on the ground
        const auto  right = CrossProduct(m_normal, CVector::ZAxisVector());
        const auto  target =
              pedPos 
            + right * CGeneral::GetRandomNumberInRange(-1.f, 1.f)  // => right or left
            + m_normal * CGeneral::GetRandomNumberInRange(1.f, 2.f);
        // ^^^ Original order of addition was: m_normal, right, pedPos

        CColPoint cp{};
        CEntity* hitEntity{};
        if (CWorld::ProcessLineOfSight(pedPos, target, cp, hitEntity, true, false, false, false, false, false, false, false)) {
            auto cpToPedDir = cp.m_vecPoint - pedPos;
            if (cpToPedDir.NormaliseAndMag() < 0.35f) {
                return;
            }
            m_crapRoute->AddPoints(cp.m_vecPoint - cpToPedDir * 0.35f);
        } else {
            m_crapRoute->AddPoints(target);
        }
    }

    m_crapRouteHasPoints = true;
}

// 0x657BA0
void CTaskComplexWalkRoundBuildingAttempt::ComputeRoute(CPed const& ped) {
    ++m_nAttempts;

    // If there were too many attempts just use crap route
    if (m_nAttempts + 1 >= 20) {
        if (!m_crapRouteHasPoints) {
            ComputeCrapRoute(ped);
        }
        *m_route = *m_crapRoute;
        m_routeHasPoints = true;
        return;
    }

    const auto normal2x = m_normal * 2.f;

    size_t numPointsGenerated{};
    for (int32 num{1}; num >= -1; numPointsGenerated++, num -= m_flag0x1 ? 2 : 3) {
        CVector moveDir{};
        ComputeMoveDir(ped, moveDir);
        moveDir *= CGeneral::GetRandomNumberInRange(-0.2f, 0.2f) + (float)m_nAttempts; // Apply some semi-random spread
        moveDir *= (float)num;
        moveDir += m_normal * 0.35f;

        const auto  pedPos = ped.GetPosition() - CVector{ 0.f, 0.f, 0.5f }; // Ped's position is it's center, so adjust it to be on the ground
        const auto& target = moveDir + pedPos;
        const auto  origin = target - Normalized(moveDir) * 0.7f;

        if (!CWorld::GetIsLineOfSightClear(pedPos, target, true, false, false, false, false, false, true)) {
            continue;
        }

        if (CWorld::GetIsLineOfSightClear(target, m_target, true, false, false, false, false, false, false)) {
            m_route->AddPoints(target);
            m_routeHasPoints = true;
            return;
        }

        const auto targetOffseted = target - normal2x;

        if (!CWorld::GetIsLineOfSightClear(target, targetOffseted, true, false, false, false, false, false, false)) {
            continue;
        }

        if (!CWorld::GetIsLineOfSightClear(origin, origin - normal2x, true, false, false, false, false, false, false)) {
            continue;
        }

        if (!m_crapRouteHasPoints) {
            m_crapRoute->MaybeAddPoints(
                target,
                targetOffseted
            );
            m_crapRouteHasPoints = true;
        }

        if (CWorld::GetIsLineOfSightClear(targetOffseted, m_target, true, false, false, false, false, false, false)) {
            m_route->MaybeAddPoints(target, targetOffseted);
            m_routeHasPoints = true;
        }
    }

    if (m_nAttempts == 1) { // Current is the first attempt
        if (numPointsGenerated == (m_flag0x1 ? 2 : 1)) {
            m_nAttempts = 20;
        }
    }
}

// 0x6549D0
bool CTaskComplexWalkRoundBuildingAttempt::MakeAbortable(CPed* ped, eAbortPriority priority, CEvent const* event) {
    if (m_pSubTask->MakeAbortable(ped, priority, event)) {
        ped->bIgnoreHeightCheckOnGotoPointTask = false;
        return true;
    }
    return false;
}

// 0x656E70
CTask* CTaskComplexWalkRoundBuildingAttempt::CreateNextSubTask(CPed* ped) {
    const auto TaskFinished = [ped, this] {
        ped->bIgnoreHeightCheckOnGotoPointTask = false;
        return CreateSubTask(TASK_FINISHED, ped);
    };

    if (m_justAbort) {
        return TaskFinished();
    }

    switch (m_pSubTask->GetTaskType()) {
    case TASK_SIMPLE_ACHIEVE_HEADING:
        return CreateSubTask(TASK_COMPLEX_FOLLOW_POINT_ROUTE, ped);
    case TASK_SIMPLE_GO_TO_POINT:
    case TASK_SIMPLE_SCRATCH_HEAD:
    case TASK_SIMPLE_LOOK_ABOUT:
    case TASK_SIMPLE_HIT_WALL:
        return CreateSubTask(m_routeHasPoints ? TASK_SIMPLE_ACHIEVE_HEADING : TASK_SIMPLE_LOOK_ABOUT, ped);
    case TASK_SIMPLE_STAND_STILL:
    case TASK_COMPLEX_FOLLOW_POINT_ROUTE:
        return TaskFinished();
    default:
        NOTSA_UNREACHABLE();
    }
}

// 0x654A00
CTask* CTaskComplexWalkRoundBuildingAttempt::CreateFirstSubTask(CPed* ped) {
    if (m_flag0x4) {
        if (!m_entity) {
            ped->bIgnoreHeightCheckOnGotoPointTask = false;
            return nullptr;
        }
        m_target = m_entity->GetMatrix() * m_offset;
    }

    ped->bIgnoreHeightCheckOnGotoPointTask = true;

    switch (m_moveState) {
    case PEDMOVE_STILL:
    case PEDMOVE_TURN_L:
    case PEDMOVE_TURN_R:
    case PEDMOVE_WALK:
        return new CTaskSimpleScratchHead{};
    case PEDMOVE_RUN:
    case PEDMOVE_SPRINT:
        return new CTaskSimpleHitWall{};
    default:
        ped->bIgnoreHeightCheckOnGotoPointTask = false;
        return nullptr;
    }
}

// 0x658020
CTask* CTaskComplexWalkRoundBuildingAttempt::ControlSubTask(CPed* ped) {
    if (m_flag0x4) {
        if (!m_entity || (m_entity->GetMatrix() * m_offset - m_target).SquaredMagnitude() >= sq(4.f)) {
            m_justAbort = true;
            return CreateSubTask(TASK_SIMPLE_STAND_STILL, ped);
        }
    }

    if (!m_routeHasPoints
     || m_isFollowingRouteNow
     || !m_pSubTask->MakeAbortable(ped, ABORT_PRIORITY_URGENT, nullptr)
    ) {
        if (!m_routeHasPoints) {
            ComputeRoute(*ped);
        }

        if (m_pSubTask->GetTaskType() != TASK_COMPLEX_FOLLOW_POINT_ROUTE
         || ped->GetIntelligence()->m_AnotherStaticCounter <= 30
         || !m_pSubTask->MakeAbortable(ped, ABORT_PRIORITY_URGENT, nullptr)
        ) {
            return m_pSubTask;
        }
    } else {
        m_isFollowingRouteNow = true;
        if (!m_route->IsEmpty()) {
            return CreateSubTask(TASK_COMPLEX_FOLLOW_POINT_ROUTE, ped);
        }
    }

    m_justAbort = true;
    return CreateSubTask(TASK_SIMPLE_HIT_WALL, ped);
}
