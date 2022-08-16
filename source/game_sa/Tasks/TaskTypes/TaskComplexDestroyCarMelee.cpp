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
    m_nTime{ -1 }
{
    m_Vehicle = vehToDestroy;
    byteC = false;
    byteD = false;
    m_DistSq0 = 0.0f;
    m_DistSq1 = 0.0f;
    CEntity::SafeRegisterRef(m_Vehicle);
}

// 0x621DA0
CTaskComplexDestroyCarMelee::~CTaskComplexDestroyCarMelee() {
    CEntity::SafeCleanUpRef(m_Vehicle);
}

// 0x621E00
bool CTaskComplexDestroyCarMelee::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) {
    return plugin::CallMethodAndReturn<bool, 0x621E00, CTaskComplexDestroyCarMelee*, CPed*, eAbortPriority, CEvent const*>(this, ped, priority, event);
}

// 0x62DC20
CTask* CTaskComplexDestroyCarMelee::CreateNextSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x62DC20, CTaskComplexDestroyCarMelee*, CPed*>(this, ped);

    if (byteC)
        return nullptr;

    auto taskType = m_pSubTask->GetTaskType();

    // add missing code from 0x62DC3A to 0x62DC53

    if (taskType != TASK_COMPLEX_GO_TO_POINT_AND_STAND_STILL)
        return nullptr;

    CalculateSearchPositionAndRanges(ped);
    if (DistanceBetweenPointsSquared(ped->GetPosition(), m_Vehicle->GetPosition()) < sq(m_DistSq0)) {
        return CreateSubTask(TASK_SIMPLE_FIGHT_CTRL, ped);
    }
    return CreateSubTask(ped->bStayInSamePlace ? TASK_SIMPLE_PAUSE : TASK_COMPLEX_SEEK_ENTITY, ped);
}

// 0x62DB20
CTask* CTaskComplexDestroyCarMelee::CreateFirstSubTask(CPed* ped) {
    byteD = false;
    CWeaponInfo::GetWeaponInfo(ped->GetActiveWeapon().m_nType); // unused

    const auto& pedPos = ped->GetPosition();
    CalculateSearchPositionAndRanges(ped);
    if (DistanceBetweenPointsSquared(pedPos, m_Vehicle->GetPosition()) <= sq(m_DistSq1)) {
        return CreateSubTask(ped->bStayInSamePlace ? TASK_SIMPLE_PAUSE : TASK_COMPLEX_SEEK_ENTITY, ped);
    }

    ped->m_fAimingRotation = CGeneral::GetRadianAngleBetweenPoints(m_VehiclePos.x, m_VehiclePos.y, pedPos.x, pedPos.y);
    return CreateSubTask(TASK_SIMPLE_FIGHT_CTRL, ped);
}

// 0x62DDB0
CTask* CTaskComplexDestroyCarMelee::ControlSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x62DDB0, CTaskComplexDestroyCarMelee*, CPed*>(this, ped);

    if (byteD)
        return CreateFirstSubTask(ped);

    if (m_Vehicle->m_fHealth <= 0.0f)
        return nullptr;

    switch (m_pSubTask->GetTaskType()) {
    case TASK_COMPLEX_SEEK_ENTITY:
    case TASK_COMPLEX_GO_TO_POINT_AND_STAND_STILL:
        CalculateSearchPositionAndRanges(ped);
        if (DistanceBetweenPoints(ped->GetPosition(), m_Vehicle->GetPosition()) > sq(m_DistSq0)) {
            return CreateSubTask(TASK_SIMPLE_FIGHT_CTRL, ped);
        }
        return m_pSubTask;
    case TASK_SIMPLE_FIGHT_CTRL:
        CalculateSearchPositionAndRanges(ped);
        if (DistanceBetweenPoints(ped->GetPosition(), m_Vehicle->GetPosition()) > m_DistSq0 + 0.6f) {
            CreateSubTask(TASK_COMPLEX_SEEK_ENTITY, ped);
        }
        // todo:
        return m_pSubTask;
    default:
        return nullptr;
    }
}

// 0x6289F0
void CTaskComplexDestroyCarMelee::CalculateSearchPositionAndRanges(CPed* ped) {
    DistanceBetweenPointsSquared(ped->GetPosition(), m_Vehicle->GetPosition());
    return plugin::CallMethodAndReturn<void, 0x6289F0, CTaskComplexDestroyCarMelee*, CPed*>(this, ped);
}

// 0x628A70
CTask* CTaskComplexDestroyCarMelee::CreateSubTask(eTaskType taskType, CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x628A70, CTaskComplexDestroyCarMelee*, eTaskType, CPed*>(this, taskType, ped);
}
