#include "StdInc.h"

#include "TaskComplexGoToPointAiming.h"

void CTaskComplexGoToPointAiming::InjectHooks() {
    RH_ScopedClass(CTaskComplexGoToPointAiming);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x668790);
    RH_ScopedInstall(Destructor, 0x668870);
    // RH_ScopedInstall(CreateSubTask, 0x6688D0);
    // RH_ScopedInstall(Clone, 0x66CD80);
    // RH_ScopedInstall(CreateFirstSubTask, 0x66DDB0);
    // RH_ScopedInstall(ControlSubTask, 0x6689E0);
}

// 0x668790
CTaskComplexGoToPointAiming::CTaskComplexGoToPointAiming(int32 a1, const CVector& p1, CEntity* entity, CVector p2, float a6, float a7) : CTaskComplex() {
    v14 = p2;
    dwordC = a1;
    m_Entity = entity;
    CEntity::SafeRegisterRef(m_Entity);

    if (v20 != p1 || float2C != a6 || float30 != a7) {
        v20 = p1;
        float2C = a6;
        float30 = a7;
        m_Flags = m_Flags | 1;
    }
}

// 0x668870
CTaskComplexGoToPointAiming::~CTaskComplexGoToPointAiming() {
    CEntity::SafeCleanUpRef(m_Entity);
}

// 0x6688D0
CTask* CTaskComplexGoToPointAiming::CreateSubTask(eTaskType taskType) {
    return plugin::CallMethodAndReturn<CTask*, 0x6688D0, CTaskComplexGoToPointAiming*, int32>(this, taskType);
}

// 0x66DD70
CTask* CTaskComplexGoToPointAiming::CreateNextSubTask(CPed* ped) {
    switch (m_pSubTask->GetTaskType()) {
    case TASK_COMPLEX_GO_TO_POINT_AND_STAND_STILL:
    case TASK_SIMPLE_GUN_CTRL:
        return CreateSubTask(TASK_FINISHED);
    default:
        return nullptr;
    }
}

// 0x66DDB0
CTask* CTaskComplexGoToPointAiming::CreateFirstSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x66DDB0, CTaskComplexGoToPointAiming*, CPed*>(this, ped);
}

// 0x6689E0
CTask* CTaskComplexGoToPointAiming::ControlSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x6689E0, CTaskComplexGoToPointAiming*, CPed*>(this, ped);
}
