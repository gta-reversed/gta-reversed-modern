#include "StdInc.h"

#include "TaskComplexGoToPointAnyMeans.h"

void CTaskComplexGoToPointAnyMeans::InjectHooks() {
    RH_ScopedClass(CTaskComplexGoToPointAnyMeans);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedOverloadedInstall(Constructor, "1", 0x66B720, CTaskComplexGoToPointAnyMeans*(CTaskComplexGoToPointAnyMeans::*)(int32, CVector const&, float, int32));
    RH_ScopedOverloadedInstall(Constructor, "2", 0x66B790, CTaskComplexGoToPointAnyMeans*(CTaskComplexGoToPointAnyMeans::*)(int32, CVector const&, CVehicle*, float, int32));
    RH_ScopedInstall(Destructor, 0x66B830);
    // RH_ScopedInstall(CreateSubTask, 0x6705D0);
    // RH_ScopedInstall(CreateNextSubTask, 0x6728A0);
    // RH_ScopedInstall(CreateFirstSubTask, 0x6729C0);
    // RH_ScopedInstall(ControlSubTask, 0x672A50);
}

// 0x66B720
CTaskComplexGoToPointAnyMeans::CTaskComplexGoToPointAnyMeans(int32 a2, const CVector& posn, float a4, int32 a5) : CTaskComplex() {
    m_Pos = posn;
    m_fRadius = a4;
    m_Vehicle = 0;
    m_MoveState = static_cast<eMoveState>(a2);
    dword2C = a5;
    m_nStartTimeInMs = 0;
    m_nTimeOffsetInMs = 0;
    byte32 = 0;
    m_bResetStartTime = 0;
}

// 0x66B790
CTaskComplexGoToPointAnyMeans::CTaskComplexGoToPointAnyMeans(int32 moveState, const CVector& posn, CVehicle* vehicle, float radius, int32 a6) : CTaskComplex() {
    m_Pos = posn;
    m_fRadius = radius;
    m_MoveState = static_cast<eMoveState>(moveState);
    m_Vehicle = vehicle;
    dword2C = a6;
    m_nStartTimeInMs = 0;
    m_nTimeOffsetInMs = 0;
    byte32 = 0;
    m_bResetStartTime = 0;
    CEntity::SafeRegisterRef(m_Vehicle);
}

// 0x66B830
CTaskComplexGoToPointAnyMeans::~CTaskComplexGoToPointAnyMeans() {
    CEntity::SafeCleanUpRef(m_Vehicle);
}

// 0x6705D0
CTask* CTaskComplexGoToPointAnyMeans::CreateSubTask(int32 taskType, CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x6705D0, CTaskComplexGoToPointAnyMeans*, int32, CPed*>(this, taskType, ped);
}

// 0x6728A0
CTask* CTaskComplexGoToPointAnyMeans::CreateNextSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x6728A0, CTaskComplexGoToPointAnyMeans*, CPed*>(this, ped);
}

// 0x6729C0
CTask* CTaskComplexGoToPointAnyMeans::CreateFirstSubTask(CPed* ped) {
    if (m_Vehicle) {
        if (ped->m_pVehicle && ped->bInVehicle)
            return CreateSubTask(TASK_COMPLEX_CAR_DRIVE_TO_POINT, ped);
        else
            return CreateSubTask(TASK_COMPLEX_ENTER_CAR_AS_DRIVER, ped);
    } else {
        if (ped->m_pVehicle && ped->bInVehicle && ped->m_pVehicle->IsDriver(ped))
            return CreateSubTask(TASK_COMPLEX_CAR_DRIVE_TO_POINT, ped);
        else
            return CreateSubTask(TASK_COMPLEX_FOLLOW_NODE_ROUTE, ped);
    }
}

// 0x672A50
CTask* CTaskComplexGoToPointAnyMeans::ControlSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x672A50, CTaskComplexGoToPointAnyMeans*, CPed*>(this, ped);
}
