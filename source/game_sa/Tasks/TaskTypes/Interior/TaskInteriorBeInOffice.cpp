#include "StdInc.h"
#include "TaskInteriorBeInOffice.h"

void CTaskInteriorBeInOffice::InjectHooks() {
    RH_ScopedVirtualClass(CTaskInteriorBeInOffice, 0x870218, 11);
    RH_ScopedCategory("Tasks/TaskTypes/Interior");

    RH_ScopedInstall(Constructor, 0x675220);

    RH_ScopedInstall(Destructor, 0x675260);

    RH_ScopedVMTInstall(Clone, 0x675270, { .reversed = false });
    RH_ScopedVMTInstall(GetTaskType, 0x675250, { .reversed = false });
    RH_ScopedVMTInstall(CreateNextSubTask, 0x676350, { .reversed = false });
    RH_ScopedVMTInstall(CreateFirstSubTask, 0x676400, { .reversed = false });
    RH_ScopedVMTInstall(ControlSubTask, 0x6752F0, { .reversed = false });
}

// 0x675220
CTaskInteriorBeInOffice::CTaskInteriorBeInOffice(InteriorGroup_c* ig) :
    m_InteriorGroup{ ig }
{
}

CTaskInteriorBeInOffice::CTaskInteriorBeInOffice(const CTaskInteriorBeInOffice& o) :
    CTaskInteriorBeInOffice{ o.m_InteriorGroup }
{
}

// 0x676350
CTask* CTaskInteriorBeInOffice::CreateNextSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x676350, CTaskInteriorBeInOffice*, CPed*>(this, ped); // TODO: Needs `CTaskInteriorUseInfo`
}

// 0x676400
CTask* CTaskInteriorBeInOffice::CreateFirstSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x676400, CTaskInteriorBeInOffice*, CPed*>(this, ped); // TODO: Needs `CTaskInteriorUseInfo`
}
