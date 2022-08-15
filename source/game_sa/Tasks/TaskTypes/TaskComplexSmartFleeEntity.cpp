#include "StdInc.h"

#include "TaskComplexSmartFleeEntity.h"
#include "TaskSimpleStandStill.h"
// #include "TaskComplexSmartFleePoint.h"
#include "IKChainManager_c.h"
#include "InterestingEvents.h"

void CTaskComplexSmartFleeEntity::InjectHooks() {
    RH_ScopedClass(CTaskComplexSmartFleeEntity);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x65C430);
    RH_ScopedInstall(Destructor, 0x65C4D0);
    // RH_ScopedInstall(CreateNextSubTask_Reversed, 0x65C680);
    // RH_ScopedInstall(CreateFirstSubTask_Reversed, 0x65C6F0);
    // RH_ScopedInstall(ControlSubTask_Reversed, 0x65C780);
}

// 0x65C430
CTaskComplexSmartFleeEntity::CTaskComplexSmartFleeEntity(CEntity* entity_1, bool a3, float a4, int32 a5, int32 a6, float a7) : CTaskComplex() {
    m_Entity = entity_1;
    m_dword1C = a5;
    m_dword20 = a4;
    m_byte24 = a3;
    m_dword28 = a6;
    m_dword2C = a7;
    m_dword30 = PEDMOVE_SPRINT;
    m_nTime = 0;
    m_dword38 = 0;
    m_byte3C = false;
    m_byte3D = 0;
    CEntity::SafeRegisterRef(m_Entity);
}

// 0x65C4D0
CTaskComplexSmartFleeEntity::~CTaskComplexSmartFleeEntity() {
    CEntity::SafeCleanUpRef(m_Entity);
}

// 0x65CF40
CTask* CTaskComplexSmartFleeEntity::Clone() {
    auto task = new CTaskComplexSmartFleeEntity(m_Entity, m_byte24, m_dword20, m_dword1C, m_dword28, m_dword2C);
    task->m_dword30 = m_dword30;
    return task;
}

// 0x65C680
CTask* CTaskComplexSmartFleeEntity::CreateNextSubTask(CPed* ped) {
    switch (m_pSubTask->GetTaskType()) {
    case TASK_SIMPLE_STAND_STILL:
        return CreateSubTask(m_Entity ? TASK_COMPLEX_SMART_FLEE_POINT : TASK_FINISHED);
    case TASK_COMPLEX_SMART_FLEE_POINT:
        return CreateSubTask(TASK_FINISHED);
    default:
        return nullptr;
    }
}

// 0x65C6F0
CTask* CTaskComplexSmartFleeEntity::CreateFirstSubTask(CPed* ped) {
    if (!m_Entity)
        return nullptr;

    g_InterestingEvents.Add(CInterestingEvents::INTERESTING_EVENT_13, ped);
    if (!ped->bInVehicle && !g_ikChainMan.IsLooking(ped)) {
        auto bone = m_Entity->m_nStatus == STATUS_PHYSICS ? BONE_HEAD : BONE_UNKNOWN;
        g_ikChainMan.LookAt("TaskSmartFleeEntity", ped, m_Entity, 3000, bone, nullptr, true, 0.25f, 500, 3, false);
    }
    return CreateSubTask(TASK_COMPLEX_SMART_FLEE_POINT);
}

// 0x65C780
CTask* CTaskComplexSmartFleeEntity::ControlSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x65C780, CTaskComplexSmartFleeEntity*, CPed*>(this, ped);
}

// 0x65C530
CTask* CTaskComplexSmartFleeEntity::CreateSubTask(eTaskType taskType) {
    return plugin::CallMethodAndReturn<CTask*, 0x65C530, CTaskComplexSmartFleeEntity*, eTaskType>(this, taskType);

    switch (taskType) {
    case TASK_SIMPLE_STAND_STILL:
        return new CTaskSimpleStandStill(CGeneral::GetRandomNumberInRange(0, 50));
    case TASK_COMPLEX_SMART_FLEE_POINT:
    case TASK_FINISHED:
        m_nTime = CTimer::GetTimeInMS();
        m_dword38 = m_dword28;
        m_byte3C = true;

        m_Pos = m_Entity->GetPosition();
        // return new CTaskComplexSmartFleePoint(m_Pos, m_byte24, m_dword20, m_dword1C);
    default:
        return nullptr;
    }
}
