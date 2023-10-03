#include "StdInc.h"

#include "TaskComplexGoToCarDoorAndStandStill.h"
#include "TaskSimpleCarGoToPointNearDoorUntilDoorNotInUse.h"
#include "TaskSimplePause.h"
#include "TaskSimpleStandStill.h"
#include "TaskSimpleCarWaitForDoorNotToBeInUse.h"
#include "TaskComplexFollowPointRoute.h"
#include "TaskSimpleGoToPoint.h"

void CTaskComplexGoToCarDoorAndStandStill::InjectHooks() {
    RH_ScopedVirtualClass(CTaskComplexGoToCarDoorAndStandStill, 0x86ec4c, 11);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x645780);
    RH_ScopedInstall(Destructor, 0x64A580);

    RH_ScopedInstall(IsVehicleInRange, 0x6458A0, { .reversed = false });
    RH_ScopedInstall(ComputeRouteToDoor, 0x645910, { .reversed = false });
    RH_ScopedInstall(CreateSubTask, 0x64A5F0);

    RH_ScopedVMTInstall(Clone, 0x6498B0);
    RH_ScopedVMTInstall(GetTaskType, 0x645830);
    RH_ScopedVMTInstall(MakeAbortable, 0x645840);
    RH_ScopedVMTInstall(CreateNextSubTask, 0x64D2B0);
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
CTask* CTaskComplexGoToCarDoorAndStandStill::CreateSubTask(eTaskType taskType, CPed* ped) {
    switch (taskType) {
    case TASK_SIMPLE_GO_TO_POINT_NEAR_CAR_DOOR_UNTIL_DOOR_NOT_IN_USE:
        return new CTaskSimpleCarGoToPointNearDoorUntilDoorNotInUse{ m_Vehicle, m_TargetDoor, m_TargetPt, m_MoveState };
    case TASK_SIMPLE_PAUSE:
        return new CTaskSimplePause{ 1 };
    case TASK_SIMPLE_STAND_STILL:
        return new CTaskSimpleStandStill{ 1 };
    case TASK_SIMPLE_CAR_WAIT_FOR_DOOR_NOT_TO_BE_IN_USE:
        return new CTaskSimpleCarWaitForDoorNotToBeInUse{ m_Vehicle, (uint32)m_TargetDoor };
    case TASK_COMPLEX_FOLLOW_POINT_ROUTE:
        return new CTaskComplexFollowPointRoute{ m_MoveState, *m_RouteToDoor };
    case TASK_SIMPLE_GO_TO_POINT: {
        ped->bHasJustLeftCar = true;
        return new CTaskSimpleGoToPoint{ m_MoveState, m_TargetPt, m_TargetRadius };
    }
    default:
        NOTSA_UNREACHABLE();
    }
}

// 0x64D2B0
CTask* CTaskComplexGoToCarDoorAndStandStill::CreateNextSubTask(CPed* ped) {
    switch (const auto tt = m_pSubTask->GetTaskType()) {
    case TASK_COMPLEX_FOLLOW_POINT_ROUTE: { // 0x64D3B8
        m_TargetPt = CCarEnterExit::GetPositionToOpenCarDoor(m_Vehicle, m_TargetDoor);
        return CreateSubTask(TASK_SIMPLE_GO_TO_POINT, ped);
    }
    case TASK_SIMPLE_GO_TO_POINT: { // 0x64D3E9
        m_bAchievedTargetDoor |= static_cast<CTaskSimpleGoToPoint*>(m_pSubTask)->WasTaskSuccessful(ped);
        return CreateSubTask(TASK_FINISHED, ped);
    }
    case TASK_SIMPLE_GO_TO_POINT_NEAR_CAR_DOOR_UNTIL_DOOR_NOT_IN_USE: // 0x64D387
        return CreateSubTask(TASK_SIMPLE_CAR_WAIT_FOR_DOOR_NOT_TO_BE_IN_USE, ped);
    case TASK_SIMPLE_CAR_WAIT_FOR_DOOR_NOT_TO_BE_IN_USE: // 0x64D2EB
        return CreateFirstSubTask(ped); 
    case TASK_SIMPLE_STAND_STILL: // 0x64D420
        return CreateSubTask(TASK_FINISHED, ped);
    case TASK_SIMPLE_PAUSE: { // 0x64D314
        if (m_bTryingToEnterInWater) {
            m_bAchievedTargetDoor |= (ped->GetPosition() - m_TargetPt).SquaredMagnitude2D() <= sq(0.5f);
        }
        return CreateSubTask(TASK_FINISHED, ped);
    }
    default:
        NOTSA_UNREACHABLE("SubTaskType: {}", (int)tt);
    }
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
