#include "StdInc.h"
#include "TaskComplexLeaveAnyCar.h"
#include "TaskComplexLeaveCar.h"
#include "TaskSimpleNone.h"
#include "Enums/eTargetDoor.h"

void CTaskComplexLeaveAnyCar::InjectHooks() {
    RH_ScopedClass(CTaskComplexLeaveAnyCar);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x421150);
    RH_ScopedInstall(Destructor, 0x421270);

    RH_ScopedInstall(Clone_Reversed, 0x4211C0);
    RH_ScopedInstall(GetTaskType_Reversed, 0x421240);
    RH_ScopedInstall(CreateNextSubTask_Reversed, 0x63BCD0);
    RH_ScopedInstall(CreateFirstSubTask_Reversed, 0x63BCE0);
    RH_ScopedInstall(ControlSubTask_Reversed, 0x63BDC0);
}

// 0x421150
CTaskComplexLeaveAnyCar::CTaskComplexLeaveAnyCar(int32 delayTime, bool sensibleLeaveCar, bool forceGetOut) :
    m_sensibleLeaveCar{sensibleLeaveCar},
    m_delayTime{delayTime},
    m_forceGetOut{forceGetOut}
{
}

// 0x63BCE0
CTask* CTaskComplexLeaveAnyCar::CreateFirstSubTask(CPed* ped) {
    if (ped->IsInVehicle()) {
        return new CTaskComplexLeaveCar{ ped->m_pVehicle, TARGET_DOOR_FRONT_LEFT, m_delayTime, m_sensibleLeaveCar, m_forceGetOut };
    }
    return new CTaskSimpleNone{};
}
