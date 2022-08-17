#include "StdInc.h"

#include "TaskComplexDestroyCarMelee.h"

void CTaskComplexDestroyCarMelee::InjectHooks() {
    RH_ScopedClass(CTaskComplexDestroyCarMelee);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x621D10);
    RH_ScopedInstall(Destructor, 0x621DA0);
    RH_ScopedVirtualInstall2(Clone, 0x6235A0, { .enabled = false, .locked = true });
    RH_ScopedVirtualInstall2(GetTaskType, 0x621D90);
    RH_ScopedVirtualInstall2(MakeAbortable, 0x621E00, { .enabled = false, .locked = true });
    RH_ScopedVirtualInstall2(CreateNextSubTask, 0x62DC20, { .enabled = false, .locked = true });
    RH_ScopedVirtualInstall2(CreateFirstSubTask, 0x62DB20, { .enabled = false, .locked = true });
    RH_ScopedVirtualInstall2(ControlSubTask, 0x62DDB0, { .enabled = false, .locked = true });
    RH_ScopedInstall(CreateSubTask, 0x628A70, { .enabled = false, .locked = true });
    RH_ScopedInstall(CalculateSearchPositionAndRanges, 0x6289F0, { .enabled = false, .locked = true });
}

// 0x621D10
CTaskComplexDestroyCarMelee::CTaskComplexDestroyCarMelee(CVehicle* vehToDestroy) :
    CTaskComplex(),
    m_VehiclePos{},
    dword2C{ 0 },
    m_nTimeMs{ -1 }
{
    m_VehToDestroy = vehToDestroy;
    m_bNeedsToCreatefirstSubTask = false;
    byteD = false;
    m_MaxTargetFightDist = 0.0f;
    m_MaxFightCtrlRadius = 0.0f;
    CEntity::SafeRegisterRef(m_VehToDestroy);
}

// 0x621DA0
CTaskComplexDestroyCarMelee::~CTaskComplexDestroyCarMelee() {
    CEntity::SafeCleanUpRef(m_VehToDestroy);
}

// 0x621E00
bool CTaskComplexDestroyCarMelee::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) {
    switch (priority) {
    case ABORT_PRIORITY_IMMEDIATE:
        return m_pSubTask->MakeAbortable(ped, priority, event);
    case ABORT_PRIORITY_URGENT: {

        break;
    }
    case ABORT_PRIORITY_LEISURE: {
        m_bNeedsToCreatefirstSubTask = true;
        return false;
    }
    default:
        NOTSA_UNREACHABLE("Invalid priority");
    }
}

// 0x62DC20
CTask* CTaskComplexDestroyCarMelee::CreateNextSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x62DC20, CTaskComplexDestroyCarMelee*, CPed*>(this, ped);

    if (m_bNeedsToCreatefirstSubTask) {
        return nullptr;
    }

    switch (m_pSubTask->GetTaskType()) {
    case TASK_SIMPLE_PAUSE:
    case TASK_SIMPLE_FIGHT_CTRL: {
        if (ped->bStayInSamePlace) { // Inverted
            const auto finished = m_nTimeMs != -1 && CTimer::GetTimeInMS() - m_nTimeMs > 3000;
            return CreateSubTask(finished ? TASK_FINISHED : TASK_SIMPLE_PAUSE, ped);
        }
        CalculateSearchPositionAndRanges(ped);
        return CreateSubTask(TASK_COMPLEX_SEEK_ENTITY, ped);
    }
    case TASK_COMPLEX_GO_TO_POINT_AND_STAND_STILL: {
        CalculateSearchPositionAndRanges(ped);
        if (IsPointInSphere(ped->GetPosition(), m_VehToDestroy->GetPosition(), m_MaxTargetFightDist)) {
            return CreateSubTask(TASK_SIMPLE_FIGHT_CTRL, ped);
        }
        return CreateSubTask(ped->bStayInSamePlace ? TASK_SIMPLE_PAUSE : TASK_COMPLEX_SEEK_ENTITY, ped);
    }
    case TASK_COMPLEX_SEEK_ENTITY: {
        return CreateSubTask(TASK_SIMPLE_FIGHT_CTRL, ped);
    }
    default:
        return nullptr;
    }
}

// 0x62DB20
CTask* CTaskComplexDestroyCarMelee::CreateFirstSubTask(CPed* ped) {
    byteD = false;

    // CWeaponInfo::GetWeaponInfo(ped->GetActiveWeapon().m_nType); // unused

    CalculateSearchPositionAndRanges(ped);

    const auto& pedPos = ped->GetPosition();

    if (IsPointInSphere(pedPos, m_VehToDestroy->GetPosition(), m_MaxFightCtrlRadius)) {
        return CreateSubTask(ped->bStayInSamePlace ? TASK_SIMPLE_PAUSE : TASK_COMPLEX_SEEK_ENTITY, ped);
    }

    ped->m_fAimingRotation = CGeneral::GetRadianAngleBetweenPoints(m_VehiclePos, pedPos);
    return CreateSubTask(TASK_SIMPLE_FIGHT_CTRL, ped);
}

// 0x62DDB0
CTask* CTaskComplexDestroyCarMelee::ControlSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x62DDB0, CTaskComplexDestroyCarMelee*, CPed*>(this, ped);

    if (byteD) {
        return CreateFirstSubTask(ped);
    }

    if (m_VehToDestroy->m_fHealth <= 0.0f)
        return nullptr;

    switch (m_pSubTask->GetTaskType()) {
    case TASK_COMPLEX_SEEK_ENTITY:
    case TASK_COMPLEX_GO_TO_POINT_AND_STAND_STILL: {
        CalculateSearchPositionAndRanges(ped);
        if (DistanceBetweenPoints(ped->GetPosition(), m_VehToDestroy->GetPosition()) > sq(m_MaxTargetFightDist)) {
            return CreateSubTask(TASK_SIMPLE_FIGHT_CTRL, ped);
        }
        return m_pSubTask;
    }
    case TASK_SIMPLE_FIGHT_CTRL:
        CalculateSearchPositionAndRanges(ped);
        if (DistanceBetweenPoints(ped->GetPosition(), m_VehToDestroy->GetPosition()) > m_MaxTargetFightDist + 0.6f) {
            return CreateSubTask(TASK_COMPLEX_SEEK_ENTITY, ped);
        }
        // todo:
        return m_pSubTask;
    default:
        return nullptr;
    }
}

// 0x6289F0
void CTaskComplexDestroyCarMelee::CalculateSearchPositionAndRanges(CPed* ped) {
    DistanceBetweenPointsSquared(ped->GetPosition(), m_VehToDestroy->GetPosition());
    return plugin::CallMethodAndReturn<void, 0x6289F0, CTaskComplexDestroyCarMelee*, CPed*>(this, ped);
}

// 0x628A70
CTask* CTaskComplexDestroyCarMelee::CreateSubTask(eTaskType taskType, CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x628A70, CTaskComplexDestroyCarMelee*, eTaskType, CPed*>(this, taskType, ped);
}
