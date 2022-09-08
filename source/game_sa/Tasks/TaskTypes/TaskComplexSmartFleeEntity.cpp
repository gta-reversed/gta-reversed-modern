#include "StdInc.h"

#include "TaskComplexSmartFleeEntity.h"
#include "TaskSimpleStandStill.h"
#include "TaskComplexSmartFleePoint.h"
#include "IKChainManager_c.h"
#include "InterestingEvents.h"
#include "EventSeenPanickedPed.h"

void CTaskComplexSmartFleeEntity::InjectHooks() {
    RH_ScopedVirtualClass(CTaskComplexSmartFleeEntity, 0x86f784, 11);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x65C430);
    RH_ScopedInstall(Destructor, 0x65C4D0);

    RH_ScopedVMTInstall(Clone, 0x65CF40);
    RH_ScopedVMTInstall(GetTaskType, 0x65C4C0);
    RH_ScopedVMTInstall(CreateNextSubTask, 0x65C680);
    RH_ScopedVMTInstall(CreateFirstSubTask, 0x65C6F0);
    RH_ScopedVMTInstall(ControlSubTask, 0x65C780);
}

// 0x65C430
CTaskComplexSmartFleeEntity::CTaskComplexSmartFleeEntity(
    CEntity* fleeEntity,
    bool scream,
    float safeDistance,
    int32 fleeTime,
    int32 posCheckPeriod,
    float posChangeTolerance
)  :

    m_entity{fleeEntity},
    m_pedScream{scream},
    m_safeDistance{safeDistance},
    m_time{fleeTime},
    m_posCheckPeriod{ posCheckPeriod },
    m_posChangeTolerance{ posChangeTolerance }
{
    CEntity::SafeRegisterRef(m_entity);
}

CTaskComplexSmartFleeEntity::CTaskComplexSmartFleeEntity(const CTaskComplexSmartFleeEntity& o) :
    CTaskComplexSmartFleeEntity{ o.m_entity, o.m_pedScream, o.m_safeDistance, o.m_time, o.m_posCheckPeriod, o.m_posChangeTolerance }
{
}

// 0x65C4D0
CTaskComplexSmartFleeEntity::~CTaskComplexSmartFleeEntity() {
    CEntity::SafeCleanUpRef(m_entity);
}

// 0x65C680
CTask* CTaskComplexSmartFleeEntity::CreateNextSubTask(CPed* ped) {
     return CreateSubTask([this] {
         switch (m_pSubTask->GetTaskType()) {
         case TASK_SIMPLE_STAND_STILL:
             return m_entity
                    ? TASK_COMPLEX_SMART_FLEE_POINT
                    : TASK_FINISHED;
         case TASK_COMPLEX_SMART_FLEE_POINT:
             return TASK_FINISHED;
         default:
             NOTSA_UNREACHABLE();
         }
    }());   
}

// 0x65C6F0
CTask* CTaskComplexSmartFleeEntity::CreateFirstSubTask(CPed* ped) {
    if (!m_entity) {
        return nullptr;
    }

    g_InterestingEvents.Add(CInterestingEvents::INTERESTING_EVENT_13, ped);

    if (!ped->bInVehicle && !g_ikChainMan.IsLooking(ped)) {
        g_ikChainMan.LookAt(
            "TaskSmartFleeEntity",
            ped,
            m_entity,
            3000,
            m_entity->m_nStatus == STATUS_PHYSICS
                ? BONE_HEAD
                : BONE_UNKNOWN,
            nullptr,
            true,
            0.25f,
            500,
            3,
            false
        );
    }

    return CreateSubTask(TASK_COMPLEX_SMART_FLEE_POINT);
}

// 0x65C780
CTask* CTaskComplexSmartFleeEntity::ControlSubTask(CPed* ped) {
    if (m_entity) {
        if (const auto fleePointTask = CTask::DynCast<CTaskComplexSmartFleePoint>(m_pSubTask)) {
            fleePointTask->m_moveState = m_moveState;

            // Check if position update timer is out of time, if so, update position (if outside tolerance)
            if (m_posCheckTimer.IsOutOfTime()) {
                m_posCheckTimer.Start(m_posCheckPeriod);

                const auto& currPos = m_entity->GetPosition();
                if ((currPos - m_pos).SquaredMagnitude() >= sq(m_posChangeTolerance)) {
                    m_pos = currPos;
                    fleePointTask->SetFleePosition(m_pos, m_safeDistance, m_pedScream);

                    switch (m_moveState) {
                    case PEDMOVE_JOG:
                    case PEDMOVE_RUN:
                    case PEDMOVE_SPRINT: {
                        GetEventGlobalGroup()->Add(CEventSeenPanickedPed{ ped });
                    }
                    }
                }
            }
        }
    } else {
        m_pSubTask->MakeAbortable(ped, ABORT_PRIORITY_LEISURE, nullptr);
    }

    return m_pSubTask;
}

// 0x65C530
CTask* CTaskComplexSmartFleeEntity::CreateSubTask(eTaskType taskType) {
    switch (taskType) {
    case TASK_SIMPLE_STAND_STILL:
        return new CTaskSimpleStandStill{ CGeneral::GetRandomNumberInRange(0, 50) };
    case TASK_COMPLEX_SMART_FLEE_POINT: {
        m_posCheckTimer.Start(m_posCheckPeriod);
        return new CTaskComplexSmartFleePoint{
            m_pos,
            m_pedScream,
            m_safeDistance,
            m_time
        };
    }
    case TASK_FINISHED:
        return nullptr;
    default:
        NOTSA_UNREACHABLE();
    }
}
