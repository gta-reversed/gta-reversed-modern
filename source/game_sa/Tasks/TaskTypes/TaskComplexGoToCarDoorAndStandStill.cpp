#include "StdInc.h"

#include "TaskComplexGoToCarDoorAndStandStill.h"

void CTaskComplexGoToCarDoorAndStandStill::InjectHooks() {
    RH_ScopedVirtualClass(CTaskComplexGoToCarDoorAndStandStill, 0x86ec4c, 11);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x645780);
    RH_ScopedInstall(Destructor, 0x64A580);

    RH_ScopedInstall(IsVehicleInRange, 0x6458A0, { .reversed = false });
    RH_ScopedInstall(ComputeRouteToDoor, 0x645910, { .reversed = false });
    RH_ScopedInstall(CreateSubTask, 0x64A5F0, { .reversed = false });

    RH_ScopedVMTInstall(Clone, 0x6498B0, { .reversed = false });
    RH_ScopedVMTInstall(GetTaskType, 0x645830, { .reversed = false });
    RH_ScopedVMTInstall(MakeAbortable, 0x645840);
    RH_ScopedVMTInstall(CreateNextSubTask, 0x64D2B0, { .reversed = false });
    RH_ScopedVMTInstall(CreateFirstSubTask, 0x64D440, { .reversed = false });
    RH_ScopedVMTInstall(ControlSubTask, 0x64A820, { .reversed = false });
}

// 0x645780
CTaskComplexGoToCarDoorAndStandStill::CTaskComplexGoToCarDoorAndStandStill(
    CVehicle*  vehicle,
    eMoveState moveState,
    bool       bIsDriver,
    int32      targetSeat,
    float      targetRadius,
    float      slowDownDist,
    float      maxSeekDist,
    int32      maxSeekTime
) :
    m_Vehicle{vehicle},
    m_MoveState{moveState},
    m_bIsDriver{bIsDriver},
    m_TargetRadius{targetRadius},
    m_SlowDownDist{slowDownDist},
    m_MaxSeekDist{maxSeekDist},
    m_MaxSeekTime{maxSeekTime},
    m_TargetSeat{targetSeat}
{
    CEntity::SafeRegisterRef(m_Vehicle);
}

// 0x6498B0
CTaskComplexGoToCarDoorAndStandStill::CTaskComplexGoToCarDoorAndStandStill(const CTaskComplexGoToCarDoorAndStandStill& o) :
    CTaskComplexGoToCarDoorAndStandStill{ o.m_Vehicle, o.m_MoveState, o.m_bIsDriver, o.m_TargetSeat, o.m_TargetRadius, o.m_SlowDownDist, o.m_MaxSeekDist, o.m_MaxSeekTime }
{
}

// 0x64A580
CTaskComplexGoToCarDoorAndStandStill::~CTaskComplexGoToCarDoorAndStandStill() {
    CEntity::SafeCleanUpRef(m_Vehicle);
    delete m_RouteToDoor;
}

// 0x645840
bool CTaskComplexGoToCarDoorAndStandStill::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) {
    if (m_bTryingToEnterInWater) {
        if (m_pSubTask && m_pSubTask->GetTaskType() == TASK_SIMPLE_PAUSE) {
            if (event && notsa::contains({ EVENT_IN_WATER, EVENT_IN_AIR }, event->GetEventType())) {
                return false;
            }
        }
    }
    return m_pSubTask->MakeAbortable(ped, priority, event);
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
