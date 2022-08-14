#include "StdInc.h"

#include "TaskComplexGoToCarDoorAndStandStill.h"

void CTaskComplexGoToCarDoorAndStandStill::InjectHooks() {
    RH_ScopedClass(CTaskComplexGoToCarDoorAndStandStill);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x645780);
    RH_ScopedInstall(Destructor, 0x64A580);
    // RH_ScopedInstall(IsVehicleInRange, 0x6458A0);
    // RH_ScopedInstall(ComputeRouteToDoor, 0x645910);
    // RH_ScopedInstall(CreateSubTask_Reversed, 0x64A5F0);
    // RH_ScopedInstall(Clone_Reversed, 0x6498B0);
    // RH_ScopedInstall(MakeAbortable_Reversed, 0x645840);
    // RH_ScopedInstall(CreateNextSubTask_Reversed, 0x64D2B0);
    // RH_ScopedInstall(CreateFirstSubTask_Reversed, 0x64D440);
    // RH_ScopedInstall(ControlSubTask_Reversed, 0x64A820);
}

// 0x645780
CTaskComplexGoToCarDoorAndStandStill::CTaskComplexGoToCarDoorAndStandStill(CVehicle* vehicle, int32 a3, bool a4, int32 a5, float a6, float a7, float a8, int32 a9) {
    m_pVehicle = vehicle;
    f4 = a3;
    f14 = a4;
    f18 = a6;
    f1C = a7;
    f20 = a8;
    f24 = a9;
    f28 = 0.0f;
    f2C = 0.0f;
    f30 = 0;
    m_nDoorId = 0;
    m_vecPositionToOpenCarDoor = CVector{};
    f44 = a5;
    f48 = 0;
    f49 = 0;
    f4C = nullptr;
    CEntity::SafeRegisterRef(m_pVehicle);
}

// 0x64A580
CTaskComplexGoToCarDoorAndStandStill::~CTaskComplexGoToCarDoorAndStandStill() {
    CEntity::SafeCleanUpRef(m_pVehicle);
    delete f4C;
}

// 0x645840
bool CTaskComplexGoToCarDoorAndStandStill::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) {
    return plugin::CallMethodAndReturn<bool, 0x645840, CTaskComplexGoToCarDoorAndStandStill*, CPed*, int32, CEvent const*>(this, ped, priority, event);
}

// 0x64A5F0
CTask* CTaskComplexGoToCarDoorAndStandStill::CreateSubTask(eTaskType taskType, const CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x64A5F0, CTaskComplexGoToCarDoorAndStandStill*, eTaskType, const CPed*>(this, taskType, ped);
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

// 0x6458A0
bool CTaskComplexGoToCarDoorAndStandStill::IsVehicleInRange(const CPed& ped) {
    return plugin::CallMethodAndReturn<bool, 0x6458A0, CTaskComplexGoToCarDoorAndStandStill*, const CPed&>(this, ped);
}

// 0x645910
CVector* CTaskComplexGoToCarDoorAndStandStill::ComputeRouteToDoor(const CPed& ped) {
    return plugin::CallMethodAndReturn<CVector*, 0x645910, CTaskComplexGoToCarDoorAndStandStill*, CPed const&>(this, ped);
}
