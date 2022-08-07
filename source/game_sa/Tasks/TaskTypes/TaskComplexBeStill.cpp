#include "StdInc.h"

#include "TaskComplexBeStill.h"
#include "TaskSimpleCarDrive.h"
#include "TaskSimpleStandStill.h"

// 0x62F8D0
CTask* CTaskComplexBeStill::CreateNextSubTask(CPed* ped) {
    auto taskType = m_pSubTask->GetTaskType();
    if (taskType == TASK_SIMPLE_STAND_STILL || taskType == TASK_SIMPLE_CAR_DRIVE)
        return CreateFirstSubTask(ped);
    else
        return nullptr;
}

// 0x62F910
CTask* CTaskComplexBeStill::CreateFirstSubTask(CPed* ped) {
    if (ped->bInVehicle) {
        return new CTaskSimpleCarDrive(ped->m_pVehicle, nullptr, false);
    }
    return new CTaskSimpleStandStill(0, true, false, 8.0f);
}

// 0x62F9F0
CTask* CTaskComplexBeStill::ControlSubTask(CPed* ped) {
    return m_pSubTask;
}
