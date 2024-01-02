#include "StdInc.h"

#include "TaskComplexLeaveAnyCar.h"
#include "TaskComplexLeaveCar.h"
#include "TaskSimpleNone.h"

void CTaskComplexLeaveAnyCar::InjectHooks() {
    RH_ScopedClass(CTaskComplexLeaveAnyCar);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x421150);
    RH_ScopedInstall(Destructor, 0x421270);
    RH_ScopedVirtualInstall(Clone, 0x4211C0);
    RH_ScopedVirtualInstall(GetTaskType, 0x421240);
    RH_ScopedVirtualInstall(CreateNextSubTask, 0x63BCD0);
    RH_ScopedVirtualInstall(CreateFirstSubTask, 0x63BCE0);
    RH_ScopedVirtualInstall(ControlSubTask, 0x63BDC0);
}

// 0x421150
CTaskComplexLeaveAnyCar::CTaskComplexLeaveAnyCar(int32 delayTime, bool sensibleLeaveCar, bool forceGetOut) :
    CTaskComplex(),
    m_sensibleLeaveCar{ sensibleLeaveCar },
    m_nDelayTime{ delayTime },
    m_forceGetOut{ forceGetOut }
{
}

// 0x63BCE0
CTask* CTaskComplexLeaveAnyCar::CreateFirstSubTask(CPed* ped) {
    if (ped->IsInVehicle()) {
        return new CTaskComplexLeaveCar(ped->m_pVehicle, TARGET_DOOR_FRONT_LEFT, m_nDelayTime, m_sensibleLeaveCar, m_forceGetOut);
    }
    return new CTaskSimpleNone();
}
