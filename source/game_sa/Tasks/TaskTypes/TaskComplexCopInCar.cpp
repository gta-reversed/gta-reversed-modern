#include "StdInc.h"
#include "TaskComplexCopInCar.h"
#include "TaskSimpleCarDrive.h"
#include "TaskComplexLeaveCar.h"
#include "TaskComplexEnterCarAsDriver.h"
#include "TaskSimpleStandStill.h"
#include "TaskComplexEnterCarAsPassenger.h"
#include "TaskComplexPolicePursuit.h"
#include "TaskComplexWanderCop.h"
#include "TaskComplexCarDrive.h"

void CTaskComplexCopInCar::InjectHooks() {
    RH_ScopedClass(CTaskComplexCopInCar);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x68C7F0);
    RH_ScopedInstall(Destructor, 0x68C8C0);

    // RH_ScopedInstall(CreateSubTask, 0x68C9E0);

    // RH_ScopedInstall(Clone_Reversed, 0x68CEC0);
    // RH_ScopedInstall(GetTaskType_Reversed, 0x68C8B0);
    // RH_ScopedInstall(MakeAbortable_Reversed, 0x68C940);
    // RH_ScopedInstall(CreateNextSubTask_Reversed, 0x68FA50);
    // RH_ScopedInstall(CreateFirstSubTask_Reversed, 0x68FA10);
    // RH_ScopedInstall(ControlSubTask_Reversed, 0x68FD50);
}

// 0x68C7F0
CTaskComplexCopInCar::CTaskComplexCopInCar(CVehicle* vehicle, CPed* cop1, CPed* cop2, bool flag_0x1) :
    m_pVehicle{vehicle},
    m_pCop1{cop1},
    m_pCop2{cop2},
    m_flag0x1{flag_0x1}
{
    CEntity::SafeRegisterRef(m_pVehicle);
    CEntity::SafeRegisterRef(m_pCop1);
    CEntity::SafeRegisterRef(m_pCop2);
}

// 0x68C8C0
CTaskComplexCopInCar::~CTaskComplexCopInCar() {
    CEntity::SafeCleanUpRef(m_pVehicle);
    CEntity::SafeCleanUpRef(m_pCop1);
    CEntity::SafeCleanUpRef(m_pCop2);
}
 
// 0x68C9E0
CTask* CTaskComplexCopInCar::CreateSubTask(eTaskType taskType, CPed* copPed) {
    switch (taskType) {
    case TASK_SIMPLE_CAR_DRIVE:
        return new CTaskSimpleCarDrive{ m_pVehicle };
    case TASK_COMPLEX_LEAVE_CAR: {
        copPed->GetIntelligence()->SetPedDecisionMakerType(DM_EVENT_KNOCK_OFF_BIKE);
        return new CTaskComplexLeaveCar{ m_pVehicle, 0, 0, true, false };
    }
    case TASK_COMPLEX_ENTER_CAR_AS_DRIVER: {
        copPed->GetIntelligence()->SetPedDecisionMakerType(DM_EVENT_SHOT_FIRED);
        return new CTaskComplexEnterCarAsDriver{ m_pVehicle };
    }
    case TASK_SIMPLE_STAND_STILL:
        return tasksimplestand
    }
}

// 0x68CEC0
CTask* CTaskComplexCopInCar::Clone() {
    return plugin::CallMethodAndReturn<CTask*, 0x68CEC0, CTaskComplexCopInCar*>(this);
}

// 0x68C940
bool CTaskComplexCopInCar::MakeAbortable(CPed* ped, eAbortPriority priority, CEvent const* event) {
    return plugin::CallMethodAndReturn<bool, 0x68C940, CTaskComplexCopInCar*, CPed*, eAbortPriority, CEvent const*>(this, ped, priority, event);
}

// 0x68FA50
CTask* CTaskComplexCopInCar::CreateNextSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x68FA50, CTaskComplexCopInCar*, CPed*>(this, ped);
}

// 0x68FA10
CTask* CTaskComplexCopInCar::CreateFirstSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x68FA10, CTaskComplexCopInCar*, CPed*>(this, ped);
}

// 0x68FD50
CTask* CTaskComplexCopInCar::ControlSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x68FD50, CTaskComplexCopInCar*, CPed*>(this, ped);
}
