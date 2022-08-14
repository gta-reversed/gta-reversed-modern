#include "StdInc.h"
#include "TaskComplexGoToCarDoorAndStandStill.h"

void CTaskComplexGoToCarDoorAndStandStill::InjectHooks() {
    RH_ScopedClass(CTaskComplexGoToCarDoorAndStandStill);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x645780);
    RH_ScopedInstall(Destructor, 0x64A580);

    // RH_ScopedInstall(IsVehicleInRange, 0x6458A0);
    // RH_ScopedInstall(ComputeRouteToDoor, 0x645910);
    // RH_ScopedInstall(CreateSubTask, 0x64A5F0);

    // RH_ScopedInstall(Clone, 0x6498B0);
    RH_ScopedInstall(GetTaskType, 0x645830);
    // RH_ScopedInstall(MakeAbortable, 0x645840);
    // RH_ScopedInstall(CreateNextSubTask, 0x64D2B0);
    // RH_ScopedInstall(CreateFirstSubTask, 0x64D440);
    // RH_ScopedInstall(ControlSubTask, 0x64A820);
}

// 0x645780
CTaskComplexGoToCarDoorAndStandStill::CTaskComplexGoToCarDoorAndStandStill(CVehicle* vehicle, int32 a3, bool a4, int32 a5, float a6, float a7, float a8, int32 a9) {}

// 0x64A580
CTaskComplexGoToCarDoorAndStandStill::~CTaskComplexGoToCarDoorAndStandStill() {}

// 0x6458A0
BOOL CTaskComplexGoToCarDoorAndStandStill::IsVehicleInRange(int32 a2) {
    return plugin::CallMethodAndReturn<BOOL, 0x6458A0, CTaskComplexGoToCarDoorAndStandStill*, int32>(this, a2);
}

// 0x645910
CVector* CTaskComplexGoToCarDoorAndStandStill::ComputeRouteToDoor(CPed const& ped) {
    return plugin::CallMethodAndReturn<CVector*, 0x645910, CTaskComplexGoToCarDoorAndStandStill*, CPed const&>(this, ped);
}

// 0x64A5F0
void* CTaskComplexGoToCarDoorAndStandStill::CreateSubTask(eTaskType taskType, const CPed* a3) {
    return plugin::CallMethodAndReturn<void*, 0x64A5F0, CTaskComplexGoToCarDoorAndStandStill*, eTaskType, const CPed*>(this, taskType, a3);
}

// 0x6498B0
CTask* CTaskComplexGoToCarDoorAndStandStill::Clone() {
    return plugin::CallMethodAndReturn<CTask*, 0x6498B0, CTaskComplexGoToCarDoorAndStandStill*>(this);
}

// 0x645840
bool CTaskComplexGoToCarDoorAndStandStill::MakeAbortable(CPed* ped, int32 priority, CEvent const* event) {
    return plugin::CallMethodAndReturn<bool, 0x645840, CTaskComplexGoToCarDoorAndStandStill*, CPed*, int32, CEvent const*>(this, ped, priority, event);
}

// 0x64D2B0
CTask* CTaskComplexGoToCarDoorAndStandStill::CreateNextSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x64D2B0, CTaskComplexGoToCarDoorAndStandStill*, CPed*>(this, ped);
}

// 0x64D440
CTask* CTaskComplexGoToCarDoorAndStandStill::CreateFirstSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x64D440, CTaskComplexGoToCarDoorAndStandStill*, CPed*>(this, ped);
}

// 0x64A820
CTask* CTaskComplexGoToCarDoorAndStandStill::ControlSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x64A820, CTaskComplexGoToCarDoorAndStandStill*, CPed*>(this, ped);
}
