#include "StdInc.h"

#include "TaskComplexGoToCarDoorAndStandStill.h"

void CTaskComplexGoToCarDoorAndStandStill::InjectHooks() {
    RH_ScopedClass(CTaskComplexGoToCarDoorAndStandStill);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x645780);
    RH_ScopedInstall(Destructor, 0x64A580);
    RH_ScopedInstall(IsVehicleInRange, 0x6458A0, { .reversed = false });
    RH_ScopedInstall(ComputeRouteToDoor, 0x645910, { .reversed = false });

    RH_ScopedVirtualInstall2(CreateSubTask, 0x64A5F0, { .reversed = false });
    RH_ScopedVirtualInstall2(Clone, 0x6498B0, { .reversed = false });
    RH_ScopedVirtualInstall2(MakeAbortable, 0x645840, { .reversed = false });
    RH_ScopedVirtualInstall2(CreateNextSubTask, 0x64D2B0, { .reversed = false });
    RH_ScopedVirtualInstall2(CreateFirstSubTask, 0x64D440, { .reversed = false });
    RH_ScopedVirtualInstall2(ControlSubTask, 0x64A820, { .reversed = false });
}

// 0x645780
CTaskComplexGoToCarDoorAndStandStill::CTaskComplexGoToCarDoorAndStandStill(CVehicle* vehicle, int32 moveState, bool a4, int32 a5, float radius, float a7, float a8, int32 a9) {
    m_Vehicle = vehicle;
    m_nMoveState = moveState;
    f14 = a4;
    m_fRadius = radius;
    f1C = a7;
    f20 = a8;
    f24 = a9;
    f28 = 0;
    f2C = 0.0f;
    f30 = false;
    m_nDoorId = 0;
    m_vecPositionToOpenCarDoor = CVector{};
    f44 = a5;
    f48 = false;
    f49 = false;
    m_PointRoute = nullptr;
    CEntity::SafeRegisterRef(m_Vehicle);
}

// 0x64A580
CTaskComplexGoToCarDoorAndStandStill::~CTaskComplexGoToCarDoorAndStandStill() {
    CEntity::SafeCleanUpRef(m_Vehicle);
    if (m_PointRoute) delete m_PointRoute; // allocated on the pool, a check is required
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
