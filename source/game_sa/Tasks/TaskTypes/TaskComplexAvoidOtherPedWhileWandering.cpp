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
    RH_ScopedInstall(ComputeSphere, 0x66A320);
    RH_ScopedInstall(ComputeRouteRoundSphere, 0x66A7B0, { .reversed = false });
    RH_ScopedInstall(SetUpIK, 0x66A850);
    RH_ScopedInstall(NearbyPedsInSphere, 0x671FE0);
    RH_ScopedInstall(ComputeAvoidSphere, 0x672080);
    RH_ScopedInstall(ComputeDetourTarget, 0x672180, { .reversed = false });

    RH_ScopedVMTInstall(Clone, 0x66D050);
    RH_ScopedVMTInstall(GetTaskType, 0x66A1C0);
    RH_ScopedVMTInstall(MakeAbortable, 0x66A260);
    RH_ScopedVMTInstall(CreateNextSubTask, 0x66A2C0);
    RH_ScopedVMTInstall(CreateFirstSubTask, 0x674610);
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
    CTaskComplexAvoidOtherPedWhileWandering{m_PedToAvoid, m_TargetPt, m_MoveState}
{
    m_bMovingTarget = o.m_bMovingTarget;
}

// 0x66A1D0
CTaskComplexAvoidOtherPedWhileWandering::~CTaskComplexAvoidOtherPedWhileWandering() {
    CEntity::SafeCleanUpRef(m_PedToAvoid);
}

// 0x6721B0
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
        goto end; // maybe this is just a mistake? And they wanted to do `goto quitik_and_end`?
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
    if (m_pSubTask->GetTaskType() == TASK_SIMPLE_STAND_STILL) {
        return m_pSubTask->AsComplex()->CreateFirstSubTask(ped);
    }
    QuitIK(ped);
    ped->bIgnoreHeightCheckOnGotoPointTask = false;
    return nullptr;
}

CTask* CTaskComplexAvoidOtherPedWhileWandering::CreateFirstSubTask(CPed* ped) {
    if (m_PedToAvoid) {
        m_StartPt = ped->GetPosition();

        CColSphere avoidSph;
        ComputeAvoidSphere(ped, &avoidSph);
        if (ComputeRouteRoundSphere(ped, &avoidSph)) {
            ped->bIgnoreHeightCheckOnGotoPointTask = true;
            m_DontQuitYetTimer.Start(2000);
            return new CTaskSimpleGoToPoint{ m_MoveState, m_DetourTargetPt };
        } else {
            QuitIK(ped);
        }
    }
    ped->bIgnoreHeightCheckOnGotoPointTask = false;
    return nullptr;
}

void CTaskComplexAvoidOtherPedWhileWandering::QuitIK(CPed* ped) {
    if (m_bDoingIK && g_ikChainMan.IsLooking(ped)) {
        g_ikChainMan.AbortLookAt(ped);
    }
}

// Calculate minimum bounding sphere of all peds in `accountedPeds`
CColSphere CTaskComplexAvoidOtherPedWhileWandering::ComputeSphere(PedsToAvoidArray& accountedPeds) {
    // Step 1: Find center
    CVector center{};
    size_t numPeds{};
    for (CPed* ped : accountedPeds) {
        if (!ped) {
            continue;
        }
        numPeds++;
        center += ped->GetPosition();
    }
    center /= (float)numPeds;

    // Step 2: Find max 2D[!] distance [this is going to be the radius]
    float maxDist2DSq{FLT_MIN};
    for (CPed* ped : accountedPeds) {
        if (!ped) {
            continue;
        }
        const auto dist2DSq = (center - ped->GetPosition()).SquaredMagnitude2D();
        if (dist2DSq <= maxDist2DSq) {
            continue;
        }
        maxDist2DSq = dist2DSq;
    }

    // Step 3: Construct sphere from it
    return CSphere{ center, std::sqrt(maxDist2DSq) };
}

void CTaskComplexAvoidOtherPedWhileWandering::SetUpIK(CPed* ped) {
    assert(ped);
    if (ped == FindPlayerPed() && !CPad::GetPad()->DisablePlayerControls) {
        return;
    }
    if (m_bDoingIK) {
        return;
    }
    if (!ped->GetIsOnScreen()) {
        return;
    }
    if (!g_ikChainMan.GetLookAtEntity(ped)) {
        return;
    }
    if (!ped->GetTaskManager().GetTaskSecondary(TASK_SECONDARY_IK)) {
        return;
    }
    switch (m_pParentTask->GetTaskType()) {
    case TASK_COMPLEX_AVOID_OTHER_PED_WHILE_WANDERING:
    case TASK_COMPLEX_AVOID_ENTITY:
        return;
    }
    const auto pedToTarget = m_TargetPt - ped->GetPosition();
    const auto pedToTargetDistSq = pedToTarget.SquaredMagnitude();
    if (pedToTargetDistSq <= sq(3.f)) {
        return;
    }
    const auto pedToTargetDir = pedToTarget / std::sqrt(pedToTargetDistSq); // Normalize
    if (ped->GetForward().Dot(pedToTargetDir) >= CTaskSimpleGoTo::ms_fLookAtThresholdDotProduct) {
        return;
    }
    CVector lookAt = m_TargetPt + pedToTargetDir * 2.f;
    lookAt.z += 0.61f;
    g_ikChainMan.LookAt("TaskAvoidOthPed", ped, 0, 5000, BONE_UNKNOWN, &lookAt, false, 0.25f, 500, 3, false);
    m_bDoingIK = true;
}

bool CTaskComplexAvoidOtherPedWhileWandering::NearbyPedsInSphere(CPed* ped, const CColSphere& colSphere, PedsToAvoidArray& pedsToCheck, PedsToAvoidArray& pedsInSphere) {
    bool anyInSphere = false;
    for (auto&& [i, pedToCheck] : notsa::enumerate(pedsToCheck)) {
        if (!pedToCheck) {
            continue;
        }

        if (!colSphere.IntersectSphere(CSphere{ pedToCheck->GetPosition(), 1.05f })) {
            continue;
        }

        // Find where to insert
        const auto insertAt = rng::find(pedsInSphere, nullptr);
        if (insertAt == pedsInSphere.end()) {
            return anyInSphere; // No space
        }

        // Insert it
        pedToCheck  = nullptr;    // Null out array entry
        *insertAt   = pedToCheck; 
        anyInSphere = true;
    }
    return anyInSphere;
}

// 0x672080
void CTaskComplexAvoidOtherPedWhileWandering::ComputeAvoidSphere(CPed* ped, CColSphere& outSp) {
    PedsToAvoidArray pedsToCheck{};
    for (auto&& [i, entityToCheck] : notsa::enumerate(ped->GetIntelligence()->GetPedScanner().m_apEntities)) { // Can't use GetEntities<CPed>() because it filters null entries
        const auto pedToCheck = entityToCheck->AsPed();
        pedsToCheck[i] = pedToCheck != m_PedToAvoid && !CPedGroups::AreInSameGroup(ped, pedToCheck) // Inverted
            ? pedToCheck
            : nullptr;
    }

    PedsToAvoidArray pedsInSphere{m_PedToAvoid};
    outSp = CColSphere{ m_PedToAvoid->GetPosition(), 1.05f };
    while (NearbyPedsInSphere(ped, outSp, pedsToCheck, pedsInSphere)) {
        outSp = ComputeSphere(pedsInSphere);
    }
}

bool CTaskComplexAvoidOtherPedWhileWandering::ComputeRouteRoundSphere(CPed* ped, CColSphere* colSphere) {
    return plugin::CallMethodAndReturn<bool, 0x66A7B0, CTaskComplexAvoidOtherPedWhileWandering*, CPed*, CColSphere*>(this, ped, colSphere);
}

bool CTaskComplexAvoidOtherPedWhileWandering::ComputeDetourTarget(CPed* ped) {
    return plugin::CallMethodAndReturn<bool, 0x672180, CTaskComplexAvoidOtherPedWhileWandering*, CPed*>(this, ped);
}
