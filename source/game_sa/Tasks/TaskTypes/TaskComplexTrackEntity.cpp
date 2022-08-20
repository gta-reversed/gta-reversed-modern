#include "StdInc.h"

#include "TaskComplexTrackEntity.h"
#include "TaskSimpleGoToPointFine.h"
#include "TaskSimpleStandStill.h"
#include "TaskComplexFollowNodeRoute.h"

void CTaskComplexTrackEntity::InjectHooks() {
    RH_ScopedClass(CTaskComplexTrackEntity);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x65F3B0);
    RH_ScopedInstall(Destructor, 0x65F460);

    RH_ScopedInstall(SetOffsetPos, 0x65F760, {.enabled = false, .locked = true});
    RH_ScopedInstall(CalcTargetPos, 0x65F780, {.enabled = false, .locked = true});
    RH_ScopedInstall(CalcMoveRatio, 0x65F930, {.enabled = false, .locked = true});

    RH_ScopedVirtualInstall2(Clone, 0x65F4E0);
    RH_ScopedVirtualInstall2(GetTaskType, 0x65F450);
    RH_ScopedVirtualInstall2(MakeAbortable, 0x65F4C0);
    RH_ScopedVirtualInstall2(CreateNextSubTask, 0x65F590);
    RH_ScopedVirtualInstall2(CreateFirstSubTask, 0x65F700);
    RH_ScopedVirtualInstall2(ControlSubTask, 0x663640, { .locked = true }); // Locked because it fucks up the stack and crashes
}

// 0x65F3B0
CTaskComplexTrackEntity::CTaskComplexTrackEntity(CEntity* entity, CVector offsetPos, bool useSprint, int32 giveUpTime, float nodeRouteDist, float giveUpDist, bool localOffset) :
    CTaskComplex(),
    m_OffsetPos{ offsetPos },
    m_UseSprint{ useSprint },
    m_GiveUpTime{ giveUpTime },
    m_NodeRouteDist{ nodeRouteDist },
    m_GiveUpDist{ giveUpDist },
    m_Entity{ entity },
    m_bLocalOffset{ localOffset },
    m_fMoveBlendRatio{ -1.0f }
{
    CEntity::RegisterReference(m_Entity);
}

// 0x65F460
CTaskComplexTrackEntity::~CTaskComplexTrackEntity() {
    CEntity::CleanUpOldReference(m_Entity);
}

// 0x65F760
void CTaskComplexTrackEntity::SetOffsetPos(CVector pos) {
    m_OffsetPos = pos;
}

// 0x65F780
void CTaskComplexTrackEntity::CalcTargetPos(CPed* ped) {
    plugin::CallMethod<0x65F780, CTaskComplexTrackEntity*, CPed*>(this, ped);
}

// 0x65F930
void CTaskComplexTrackEntity::CalcMoveRatio(CPed* ped) {
    plugin::CallMethod<0x65F930, CTaskComplexTrackEntity*, CPed*>(this, ped);
}

// 0x65F4C0
bool CTaskComplexTrackEntity::MakeAbortable(CPed* ped, eAbortPriority priority, CEvent const* event) {
    return m_pSubTask->MakeAbortable(ped, priority, event);
}

// 0x65F590
CTask* CTaskComplexTrackEntity::CreateNextSubTask(CPed* ped) {
    if (!m_Entity) {
        return nullptr;
    }

    if (!m_pSubTask || m_pSubTask->GetTaskType() != TASK_SIMPLE_STAND_STILL) {
        return new CTaskSimpleStandStill(50);
    }

    if (m_fDistToTargetSq < sq(m_NodeRouteDist)) {
        return new CTaskSimpleGoToPointFine(m_fMoveBlendRatio, m_TargetPos, 0.25f, nullptr);
    }

    return new CTaskComplexFollowNodeRoute(6, m_Entity->GetPosition(), 0.5f, 0.2f, 2.0f, false, -1, true);
}

// 0x65F700
CTask* CTaskComplexTrackEntity::CreateFirstSubTask(CPed* ped) {
    if (m_fMoveBlendRatio < 0.0f) {
        m_fMoveBlendRatio = [ped] {
            switch (ped->m_nMoveState) {
            case 1: return 0.0f;
            case 4: return 1.0f;
            case 6: return 2.0f;
            default: return 3.0f;
            }
        }();
    }
    return CreateNextSubTask(ped);
}

// 0x663640
CTask* CTaskComplexTrackEntity::ControlSubTask(CPed* ped) {
    const auto TryAbort = [this, ped] {
        return MakeAbortable(ped, ABORT_PRIORITY_URGENT, nullptr);
    };

    const auto TryAbortGetTask = [&, this] {
        return TryAbort() ? nullptr : m_pSubTask;
    };

    if (!m_Entity) {
        return TryAbortGetTask();
    }

    if (m_Timer.m_bStarted) {
        if (m_Timer.m_bStopped) {
            m_Timer.m_nStartTime = CTimer::GetTimeInMS();
            m_Timer.m_bStopped = false;
        }
        if (CTimer::GetTimeInMS() >= m_Timer.m_nStartTime + m_Timer.m_nInterval) {
            return TryAbortGetTask();
        }
    }

    CalcTargetPos(ped);

    switch (m_pSubTask->GetTaskType()) {
    case TASK_COMPLEX_FOLLOW_POINT_ROUTE: {
        // If we're totally out of range...
        if (m_fDistToTargetSq > sq(m_GiveUpDist)) {
            return nullptr;
        }

        // If we're now in range be a little more precise and create `TASK_SIMPLE_GO_TO_POINT_FINE`
        if (m_fDistToTargetSq < sq(m_NodeRouteDist) && TryAbort()) {
            return CreateNextSubTask(ped);
        }

        break;
    }
    case TASK_SIMPLE_GO_TO_POINT_FINE: {
        // Check if we're still in range, if not, abort and create `TASK_COMPLEX_FOLLOW_POINT_ROUTE`
        if (m_fDistToTargetSq >= sq(m_NodeRouteDist) && TryAbort()) {
            return CreateNextSubTask(ped);
        }

        CalcMoveRatio(ped);

        const auto gotoTask = static_cast<CTaskSimpleGoToPointFine*>(m_pSubTask);
        gotoTask->SetTargetPos(m_TargetPos);
        gotoTask->SetMoveRatio(m_fMoveBlendRatio);

        break;
    }
    default:
        return m_pSubTask;
    }
    return m_pSubTask;
}
