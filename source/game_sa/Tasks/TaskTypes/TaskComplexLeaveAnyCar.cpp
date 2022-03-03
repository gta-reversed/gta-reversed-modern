#include "StdInc.h"
#include "TaskComplexLeaveAnyCar.h"

void CTaskComplexLeaveAnyCar::InjectHooks() {
    RH_ScopedClass(CTaskComplexLeaveAnyCar);
    RH_ScopedCategory("Tasks/TaskTypes");

    // Constructors (1x)
    RH_ScopedInstall(Constructor, 0x421150);
    RH_ScopedInstall(Destructor, 0x421270);

    RH_ScopedInstall(Clone_Reversed, 0x4211C0);
    RH_ScopedInstall(GetTaskType_Reversed, 0x421240);
    //RH_ScopedInstall(CreateNextSubTask_Reversed, 0x63BCD0);
    //RH_ScopedInstall(CreateFirstSubTask_Reversed, 0x63BCE0);
    //RH_ScopedInstall(ControlSubTask_Reversed, 0x63BDC0);
}

// 0x421150
CTaskComplexLeaveAnyCar::CTaskComplexLeaveAnyCar(int32 delayTime, bool sensibleLeaveCar, bool forceGetOut) :
    m_sensibleLeaveCar{sensibleLeaveCar},
    m_delayTime{delayTime},
    m_forceGetOut{forceGetOut}
{
}

// 0x63BCD0
CTask* CTaskComplexLeaveAnyCar::CreateNextSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x63BCD0, CTaskComplexLeaveAnyCar*, CPed*>(this, ped);
}

// 0x63BCE0
CTask* CTaskComplexLeaveAnyCar::CreateFirstSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x63BCE0, CTaskComplexLeaveAnyCar*, CPed*>(this, ped);
}

// 0x63BDC0
CTask* CTaskComplexLeaveAnyCar::ControlSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x63BDC0, CTaskComplexLeaveAnyCar*, CPed*>(this, ped);
}
