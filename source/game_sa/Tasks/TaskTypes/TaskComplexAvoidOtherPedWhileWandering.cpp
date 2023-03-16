#include "StdInc.h"

#include <IKChainManager_c.h>

#include "TaskSimpleStandStill.h"
#include "TaskComplexGangFollower.h"
#include "TaskSimpleGoToPoint.h"
#include "TaskComplexAvoidOtherPedWhileWandering.h"

void CTaskComplexAvoidOtherPedWhileWandering::InjectHooks() {
    RH_ScopedVirtualClass(CTaskComplexAvoidOtherPedWhileWandering, 0x86fec4, 11);
    RH_ScopedCategory("Tasks/TaskTypes"); // TODO: Change this to the appropriate category!

    RH_ScopedInstall(Constructor, 0x66A100);
    RH_ScopedInstall(Destructor, 0x66A1D0);

    RH_ScopedInstall(QuitIK, 0x66A230, { .reversed = false });
    RH_ScopedInstall(ComputeSphere, 0x66A320, { .reversed = false });
    RH_ScopedInstall(ComputeRouteRoundSphere, 0x66A7B0, { .reversed = false });
    RH_ScopedInstall(SetUpIK, 0x66A850, { .reversed = false });
    RH_ScopedInstall(NearbyPedsInSphere, 0x671FE0, { .reversed = false });
    RH_ScopedInstall(ComputeAvoidSphere, 0x672080, { .reversed = false });
    RH_ScopedInstall(ComputeDetourTarget, 0x672180, { .reversed = false });

    RH_ScopedVMTInstall(Clone, 0x66D050);
    RH_ScopedVMTInstall(GetTaskType, 0x66A1C0);
    RH_ScopedVMTInstall(MakeAbortable, 0x66A260);
    RH_ScopedVMTInstall(CreateNextSubTask, 0x66A2C0, { .reversed = false });
    RH_ScopedVMTInstall(CreateFirstSubTask, 0x674610, { .reversed = false });
    RH_ScopedVMTInstall(ControlSubTask, 0x6721B0);
}

// 0x66A100
CTaskComplexAvoidOtherPedWhileWandering::CTaskComplexAvoidOtherPedWhileWandering(
    CPed* pedToAvoid,
    const CVector& targetPoint,
    eMoveState moveState
) :
    m_PedToAvoid{pedToAvoid},
    m_TargetPt{targetPoint},
    m_DetourTargetPt{targetPoint}
{
    CEntity::SafeRegisterRef(m_PedToAvoid);
}

CTaskComplexAvoidOtherPedWhileWandering::CTaskComplexAvoidOtherPedWhileWandering(const CTaskComplexAvoidOtherPedWhileWandering& o) :
    CTaskComplexAvoidOtherPedWhileWandering{m_PedToAvoid, m_TargetPt, m_moveState}
{
    m_bMovingTarget = o.m_bMovingTarget;
}

// 0x66A1D0
CTaskComplexAvoidOtherPedWhileWandering::~CTaskComplexAvoidOtherPedWhileWandering() {
    CEntity::SafeCleanUpRef(m_PedToAvoid);
}

CTask* CTaskComplexAvoidOtherPedWhileWandering::ControlSubTask(CPed* ped) {
    // Pirulax: Yes, I know, using goto's isn't necessary.
    // Alternative is to nest it.

    if (!m_PedToAvoid) {
    quitik_and_end:
        QuitIK(ped);
    end:
        ped->bIgnoreHeightCheckOnGotoPointTask = false;
        return nullptr;
    }

    if (m_bWantsToQuit && m_pSubTask->MakeAbortable(ped, ABORT_PRIORITY_URGENT, nullptr)) {
        goto end;
    }

    m_Timer.StartIfNotAlready(200);

    SetUpIK(ped);

    if (m_pSubTask->GetTaskType() == TASK_SIMPLE_STAND_STILL) {
        return m_pSubTask;
    }

    if (ped->GetIntelligence()->m_AnotherStaticCounter > 30) {
        QuitIK(ped);
        return new CTaskSimpleStandStill{ CGeneral::GetRandomNumberInRange(500, 2500) };
    }

    const auto &pedPos        = ped->GetPosition(),
               &pedToAvoidPos = m_PedToAvoid->GetPosition();
    if (std::abs(pedToAvoidPos.z - pedPos.z) >= 3.f) {
        goto quitik_and_end;
    }

    const auto pedToAvoidDist2DSq = (pedPos - pedToAvoidPos).SquaredMagnitude2D();
    const auto pedSimplestTask = ped->GetTaskManager().GetSimplestActiveTask();
    if (   pedSimplestTask
        && CTask::IsGoToTask(pedSimplestTask)
        && m_DontQuitYetTimer.IsOutOfTime()
        && ped->GetForward().Dot(m_PedToAvoid->GetForward()) >= 0.923 // 22 and change degrees
        && (ped->GetMoveSpeed() * CTimer::TIMESTEP_PER_SECOND).SquaredMagnitude2D() <= (m_PedToAvoid->GetMoveSpeed() * CTimer::TIMESTEP_PER_SECOND).SquaredMagnitude2D() + sq(0.5f)
        && pedToAvoidDist2DSq >= sq(1.f)
    ) {
        goto quitik_and_end;
    }

    if (pedToAvoidDist2DSq >= sq(2.5f) + 1.f) {
        goto quitik_and_end;
    }

    if (!m_Timer.IsOutOfTime()) {
        return m_pSubTask;
    }

    m_Timer.Start(200);

    if (!m_bMovingTarget) {
        goto quitik_and_end;
    }

    if (const auto followerTask = CTask::DynCast<CTaskComplexGangFollower>(ped->GetIntelligence()->FindTaskByType(TASK_COMPLEX_GANG_FOLLOWER))) {
        if (followerTask->m_Leader) {
            m_TargetPt = followerTask->m_Leader->GetPosition() + followerTask->CalculateOffsetPosition();
        }
    }

    if (ComputeDetourTarget(ped)) {
        CTask::Cast<CTaskSimpleGoToPoint>(m_pSubTask)->UpdatePoint(m_TargetPt);
        return m_pSubTask;
    }

    goto quitik_and_end;
}

bool CTaskComplexAvoidOtherPedWhileWandering::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) {
    const bool subTaskAborted = m_pSubTask->MakeAbortable(ped, priority, event);
    if (subTaskAborted) {
        QuitIK(ped);
        ped->bIgnoreHeightCheckOnGotoPointTask = false;
    }
    return subTaskAborted;
}

CTask* CTaskComplexAvoidOtherPedWhileWandering::CreateNextSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x66A2C0, CTaskComplexAvoidOtherPedWhileWandering*, CPed*>(this, ped);
}

CTask* CTaskComplexAvoidOtherPedWhileWandering::CreateFirstSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x674610, CTaskComplexAvoidOtherPedWhileWandering*, CPed*>(this, ped);
}

void CTaskComplexAvoidOtherPedWhileWandering::QuitIK(CPed* ped) {
    return plugin::CallMethod<0x66A230, CTaskComplexAvoidOtherPedWhileWandering*, CPed*>(this, ped);
}

bool CTaskComplexAvoidOtherPedWhileWandering::NearbyPedsInSphere(CColSphere* colSphere, CPed* ped) {
    return plugin::CallMethodAndReturn<uint8, 0x66A320, CTaskComplexAvoidOtherPedWhileWandering*, CColSphere*, CPed*>(this, colSphere, ped);
}

void CTaskComplexAvoidOtherPedWhileWandering::SetUpIK(CPed* ped) {
    return plugin::CallMethod<0x66A850, CTaskComplexAvoidOtherPedWhileWandering*, CPed*>(this, ped);
}

bool CTaskComplexAvoidOtherPedWhileWandering::ComputeSphere(CPed* ped, CColSphere* colSphere, CPed** pedsToCheck, CPed** pedsInSphere) {
    return plugin::CallMethodAndReturn<bool, 0x671FE0, CTaskComplexAvoidOtherPedWhileWandering*, CPed*, CColSphere*, CPed**, CPed**>(this, ped, colSphere, pedsToCheck, pedsInSphere);
}

void CTaskComplexAvoidOtherPedWhileWandering::ComputeAvoidSphere(CPed* ped, CColSphere* colSphere) {
    return plugin::CallMethod<0x672080, CTaskComplexAvoidOtherPedWhileWandering*, CPed*, CColSphere*>(this, ped, colSphere);
}

bool CTaskComplexAvoidOtherPedWhileWandering::ComputeRouteRoundSphere(CPed* ped, CColSphere* colSphere) {
    return plugin::CallMethodAndReturn<bool, 0x66A7B0, CTaskComplexAvoidOtherPedWhileWandering*, CPed*, CColSphere*>(this, ped, colSphere);
}

bool CTaskComplexAvoidOtherPedWhileWandering::ComputeDetourTarget(CPed* ped) {
    return plugin::CallMethodAndReturn<bool, 0x672180, CTaskComplexAvoidOtherPedWhileWandering*, CPed*>(this, ped);
}
