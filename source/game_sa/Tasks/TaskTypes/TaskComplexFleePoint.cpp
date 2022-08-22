#include "StdInc.h"

#include "TaskComplexFleePoint.h"
#include "TaskComplexGoToPointAndStandStill.h"
#include "TaskSimpleGoToPoint.h"
#include "TaskComplexLeaveAnyCar.h"
#include "TaskComplexSequence.h"
#include "TaskSimpleRunAnim.h"
#include "TaskSimpleTired.h"
#include "IKChainManager_c.h"

void CTaskComplexFleePoint::InjectHooks() {
    RH_ScopedVirtualClass(CTaskComplexFleePoint, 0x86f6cc, 11);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x65B390);
    RH_ScopedInstall(Destructor, 0x65B410);
    RH_ScopedInstall(CreateSubTask, 0x65B460);
    RH_ScopedInstall(SetFleePosition, 0x65B7B0);
    RH_ScopedInstall(ComputeTargetPoint, 0x65B820);
    RH_ScopedVMTInstall(Clone, 0x65CDE0);
    RH_ScopedVMTInstall(GetTaskType, 0x65B400);
    RH_ScopedVMTInstall(MakeAbortable, 0x65B420);
    RH_ScopedVMTInstall(CreateNextSubTask, 0x65D150);
    RH_ScopedVMTInstall(CreateFirstSubTask, 0x65D100);
    RH_ScopedVMTInstall(ControlSubTask, 0x65B660);
}

// 0x65B390
CTaskComplexFleePoint::CTaskComplexFleePoint(const CVector& fleePos, bool bScream, float fSafeDistance, int32 fleeTime) :
      m_vFleePos{fleePos},
      m_bScream{ bScream },
      m_fSafeDistance{ fSafeDistance },
      m_nFleeTime{ fleeTime }
{
    m_Timer.Start(fleeTime);
}

// 0x65B460
CTask* CTaskComplexFleePoint::CreateSubTask(eTaskType taskType) {
    switch (taskType) {
    case TASK_COMPLEX_GO_TO_POINT_AND_STAND_STILL:
        return new CTaskComplexGoToPointAndStandStill{ PEDMOVE_SPRINT, m_vTargetPoint, 0.5f, 2.f, false, false };
    case TASK_SIMPLE_GO_TO_POINT:
        return new CTaskSimpleGoToPoint{ PEDMOVE_SPRINT, m_vTargetPoint, 0.5f, false, false };
    case TASK_COMPLEX_LEAVE_ANY_CAR:
        return new CTaskComplexLeaveAnyCar{ 0, true, false };
    case TASK_COMPLEX_SEQUENCE: {
        const auto seq = new CTaskComplexSequence{};
        seq->AddTask(new CTaskSimpleRunAnim{ ANIM_GROUP_DEFAULT, ANIM_ID_FLEE_LKAROUND_01, 4.0f, false });
        seq->AddTask(new CTaskSimpleTired{ 2000u });
        return seq;
    }
    case TASK_FINISHED:
        return nullptr;
    default:
        NOTSA_UNREACHABLE("Invalid taskType: {}", (int)taskType);
        return nullptr;
    }
}

/*!
* @addr 0x65B7B0
* @brief Set a new flee position
*/
void CTaskComplexFleePoint::SetFleePosition(CVector const& fleePos, float safeDistance, bool scream) {
    if (m_vFleePos != fleePos) {
        m_vFleePos = fleePos;
        m_fSafeDistance = safeDistance;
        m_bNewFleePoint = true;
    }
    m_bScream = scream;
}

/*!
* @addr 0x65B820
* @brief Compute random `m_fleeToPos`
*/
void CTaskComplexFleePoint::ComputeTargetPoint(CPed const* ped) {
    // https://www.desmos.com/calculator/o793zwzy5f

    const auto pedPos   = ped->GetPosition();
    const auto angleRad = CGeneral::GetRandomNumberInRange(-0.33f, 0.33f); // TODO: Seemingly magic numbers?
    const auto dir      = Normalized2D(CVector2D{ pedPos - m_vFleePos}) * CVector2D{ std::cos(angleRad), std::sin(angleRad) };
    const auto spread   = CGeneral::GetRandomNumberInRange(3, 6);

    m_vTargetPoint = pedPos;

    m_vTargetPoint.x += (dir.x + dir.y) * spread;
    m_vTargetPoint.y += (dir.x - dir.y) * spread;
}

 // 0x65B420
bool CTaskComplexFleePoint::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) {
    if (priority == ABORT_PRIORITY_LEISURE) {
        m_nFleeTime = -1;

        // Leads to running `TASK_SEQUENCE` => `TASK_FINISHED`
        // TODO: Below is probably something inlined, so unline it...
        m_Timer.m_nStartTime = CTimer::GetTimeInMS();
        m_Timer.m_nInterval = -1;
        m_Timer.m_bStarted = 1;
    }
    return m_pSubTask->MakeAbortable(ped, priority, event);
}

// 0x65D150
CTask* CTaskComplexFleePoint::CreateNextSubTask(CPed* ped) {
    switch (m_pSubTask->GetTaskType()) {
    case TASK_COMPLEX_GO_TO_POINT_AND_STAND_STILL:
        return CreateSubTask(TASK_COMPLEX_SEQUENCE);
    case TASK_COMPLEX_SEQUENCE:
        return CreateSubTask(TASK_FINISHED);
    case TASK_COMPLEX_LEAVE_ANY_CAR:
        return CreateSubTask(TASK_SIMPLE_GO_TO_POINT);
    case TASK_SIMPLE_GO_TO_POINT: {
        ComputeTargetPoint(ped);
        return CreateSubTask(
            IsPointInSphere(ped->GetPosition(), m_vTargetPoint, m_fSafeDistance) // Still in danger zone?
                ? TASK_SIMPLE_GO_TO_POINT                  // Go to `m_fleeToPos`
                : TASK_COMPLEX_GO_TO_POINT_AND_STAND_STILL // This will eventually create a `TASK_COMPLEX_SEQUENCE` which then leads to `TASK_FINISHED`
        );
    }
    default:
        return nullptr;
    }
}

// 0x65D100
CTask* CTaskComplexFleePoint::CreateFirstSubTask(CPed* ped) {
    if (ped->IsInVehicle()) {
        return CreateSubTask(TASK_COMPLEX_LEAVE_ANY_CAR);
    }

    ComputeTargetPoint(ped);
    return CreateSubTask(TASK_SIMPLE_GO_TO_POINT);
}

// 0x65B660
CTask* CTaskComplexFleePoint::ControlSubTask(CPed* ped) {
    switch (m_pSubTask->GetTaskType()) {
    case TASK_SIMPLE_GO_TO_POINT:
    case TASK_COMPLEX_GO_TO_POINT_AND_STAND_STILL:
        break;
    default: {
        g_ikChainMan.AbortLookAt(ped); // Dropped redundant `IsLooking` check (As task existence is checked by `AbortLookAt` as well.
        return m_pSubTask;
    }
    }

    if (m_bScream) {
        ped->Say(347, 0, 0.1f);
    }

    // Moved this here for simplicity, logic unchanged
    if (!g_ikChainMan.IsLooking(ped)) {
        if (CGeneral::GetRandomNumberInRange(0, 100) <= 5) { // TODO: CGeneral::DoCoinFlip()
            g_ikChainMan.LookAt("TaskFleePoint", ped, nullptr, 2000, ePedBones::BONE_UNKNOWN, &m_vFleePos, false, 0.25f, 500, 3, false);
        }
    }

    if (m_bNewFleePoint) {
        m_bNewFleePoint = false;
        m_Timer.Start(m_nFleeTime);
        return CreateFirstSubTask(ped); // Do it all over again :D
    } else if (m_Timer.IsOutOfTime()) {
        return CreateSubTask(TASK_COMPLEX_SEQUENCE);
    }

    return m_pSubTask;
}
