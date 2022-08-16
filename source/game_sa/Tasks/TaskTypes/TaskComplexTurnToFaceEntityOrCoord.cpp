#include "StdInc.h"
#include "TaskComplexTurnToFaceEntityOrCoord.h"

void CTaskComplexTurnToFaceEntityOrCoord::InjectHooks() {
    RH_ScopedClass(CTaskComplexTurnToFaceEntityOrCoord);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedOverloadedInstall(Constructor, "Coords", 0x66B890, CTaskComplexTurnToFaceEntityOrCoord*(CTaskComplexTurnToFaceEntityOrCoord::*)(CEntity*, float, float));
    RH_ScopedOverloadedInstall(Constructor, "Entity", 0x66B910, CTaskComplexTurnToFaceEntityOrCoord*(CTaskComplexTurnToFaceEntityOrCoord::*)(CVector const&, float, float));
    RH_ScopedInstall(Destructor, 0x66B960);

    RH_ScopedInstall(ComputeTargetHeading, 0x66B9D0, {.enabled = false, .locked = true});

    RH_ScopedVirtualInstall2(Clone, 0x66D250, {.enabled = false, .locked = true});
    RH_ScopedVirtualInstall2(GetTaskType, 0x66B900, {.enabled = false, .locked = true});
    RH_ScopedVirtualInstall2(CreateNextSubTask, 0x66B9C0, {.enabled = false, .locked = true});
    RH_ScopedVirtualInstall2(CreateFirstSubTask, 0x670850, {.enabled = false, .locked = true});
    RH_ScopedVirtualInstall2(ControlSubTask, 0x670920, {.enabled = false, .locked = true});
}

// 0x66B890
CTaskComplexTurnToFaceEntityOrCoord::CTaskComplexTurnToFaceEntityOrCoord(CEntity* entity, float changeRateMult, float maxHeading) :
    m_entityToFace{entity},
    m_fChangeRateMult{changeRateMult},
    m_fMaxHeading{maxHeading},
    m_bFaceEntity{true}
{
    CEntity::SafeRegisterRef(m_entityToFace);
}

// 0x66B910
CTaskComplexTurnToFaceEntityOrCoord::CTaskComplexTurnToFaceEntityOrCoord(CVector const& coords, float changeRateMult, float maxHeading) :
    m_coordsToFace{coords},
    m_fChangeRateMult{changeRateMult},
    m_fMaxHeading{maxHeading},
    m_bFaceEntity{false}
{
}

// 0x66B960
CTaskComplexTurnToFaceEntityOrCoord::~CTaskComplexTurnToFaceEntityOrCoord() {
    CEntity::SafeCleanUpRef(m_entityToFace);
}

// 0x66B9D0
float CTaskComplexTurnToFaceEntityOrCoord::ComputeTargetHeading(CPed* ped) const {
    return plugin::CallMethodAndReturn<float, 0x66B9D0, const CTaskComplexTurnToFaceEntityOrCoord*, CPed*>(this, ped);
}

// 0x66D250
CTask* CTaskComplexTurnToFaceEntityOrCoord::Clone() {
    return plugin::CallMethodAndReturn<CTask*, 0x66D250, CTaskComplexTurnToFaceEntityOrCoord*>(this);
}

// 0x66B9C0
CTask* CTaskComplexTurnToFaceEntityOrCoord::CreateNextSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x66B9C0, CTaskComplexTurnToFaceEntityOrCoord*, CPed*>(this, ped);
}

// 0x670850
CTask* CTaskComplexTurnToFaceEntityOrCoord::CreateFirstSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x670850, CTaskComplexTurnToFaceEntityOrCoord*, CPed*>(this, ped);
}

// 0x670920
CTask* CTaskComplexTurnToFaceEntityOrCoord::ControlSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x670920, CTaskComplexTurnToFaceEntityOrCoord*, CPed*>(this, ped);
}
