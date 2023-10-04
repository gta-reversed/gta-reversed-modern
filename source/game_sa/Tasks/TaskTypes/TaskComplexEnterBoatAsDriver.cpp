#include "StdInc.h"

#include "TaskComplexEnterBoatAsDriver.h"

void CTaskComplexEnterBoatAsDriver::InjectHooks() {
    RH_ScopedVirtualClass(CTaskComplexEnterBoatAsDriver, 0x86e7d0, 11);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x63B5E0);
    RH_ScopedInstall(Destructor, 0x63B650);

    RH_ScopedInstall(CreateSubTask, 0x63B6C0, { .reversed = false });

    RH_ScopedVMTInstall(Clone, 0x63D920);
    RH_ScopedVMTInstall(GetTaskType, 0x63B640);
    RH_ScopedVMTInstall(CreateNextSubTask, 0x640E60, { .reversed = false });
    RH_ScopedVMTInstall(CreateFirstSubTask, 0x640ED0, { .reversed = false });
    RH_ScopedVMTInstall(ControlSubTask, 0x63B6B0, { .reversed = false });
}

// 0x63B5E0
CTaskComplexEnterBoatAsDriver::CTaskComplexEnterBoatAsDriver(CVehicle* target) :
    m_EnterInto{target}
{
    CEntity::SafeRegisterRef(m_EnterInto);
}

// 0x63D920
CTaskComplexEnterBoatAsDriver::CTaskComplexEnterBoatAsDriver(const CTaskComplexEnterBoatAsDriver& o) :
    CTaskComplexEnterBoatAsDriver{ o.m_EnterInto }
{
}

// 0x63B650
CTaskComplexEnterBoatAsDriver::~CTaskComplexEnterBoatAsDriver() {
    CEntity::SafeCleanUpRef(m_EnterInto);
}

// 0x63B6C0
CTask* CTaskComplexEnterBoatAsDriver::CreateSubTask(eTaskType tt) {
    return plugin::CallMethodAndReturn<CTask*, 0x63B6C0, CTaskComplexEnterBoatAsDriver*, eTaskType>(this, tt);
}

// 0x640E60
CTask* CTaskComplexEnterBoatAsDriver::CreateNextSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x640E60, CTaskComplexEnterBoatAsDriver*, CPed*>(this, ped);
}

// 0x640ED0
CTask* CTaskComplexEnterBoatAsDriver::CreateFirstSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x640ED0, CTaskComplexEnterBoatAsDriver*, CPed*>(this, ped);
}

// 0x63B6B0
CTask* CTaskComplexEnterBoatAsDriver::ControlSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x63B6B0, CTaskComplexEnterBoatAsDriver*, CPed*>(this, ped);
}
