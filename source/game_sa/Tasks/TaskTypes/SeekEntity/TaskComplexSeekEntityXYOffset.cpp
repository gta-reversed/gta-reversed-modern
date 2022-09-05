#include "StdInc.h"
#include "TaskComplexSeekEntityXYOffset.h"

void CTaskComplexSeekEntityXYOffset::InjectHooks() {
    RH_ScopedVirtualClass(CTaskComplexSeekEntityXYOffset, 0x86FBB4, 11);
    RH_ScopedCategory("Tasks/TaskTypes/SeekEntity");

    RH_ScopedInstall(Constructor, 0x661DC0);
    RH_ScopedInstall(Destructor, 0x661F30);

    RH_ScopedInstall(CreateSubTask, 0x496270);

    RH_ScopedVMTInstall(Clone, 0x664AF0);
    RH_ScopedVMTInstall(GetTaskType, 0x661EA0);
    RH_ScopedVMTInstall(MakeAbortable, 0x661EB0);
    RH_ScopedVMTInstall(CreateNextSubTask, 0x665080);
    RH_ScopedVMTInstall(CreateFirstSubTask, 0x665600);
    RH_ScopedVMTInstall(ControlSubTask, 0x665760);
}
