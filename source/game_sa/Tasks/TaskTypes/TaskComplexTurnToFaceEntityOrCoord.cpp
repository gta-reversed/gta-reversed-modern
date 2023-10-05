#include "StdInc.h"

#include "TaskComplexTurnToFaceEntityOrCoord.h"
#include "TaskSimpleAchieveHeading.h"

void CTaskComplexTurnToFaceEntityOrCoord::InjectHooks() {
    RH_ScopedClass(CTaskComplexTurnToFaceEntityOrCoord);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedOverloadedInstall(Constructor, "Coords", 0x66B890, CTaskComplexTurnToFaceEntityOrCoord*(CTaskComplexTurnToFaceEntityOrCoord::*)(CEntity*, float, float));
    RH_ScopedOverloadedInstall(Constructor, "Entity", 0x66B910, CTaskComplexTurnToFaceEntityOrCoord*(CTaskComplexTurnToFaceEntityOrCoord::*)(CVector const&, float, float));
    RH_ScopedInstall(Destructor, 0x66B960);
    RH_ScopedInstall(ComputeTargetHeading, 0x66B9D0);
    RH_ScopedVirtualInstall2(ControlSubTask, 0x670920, { .reversed = false });
}

// 0x66B890
CTaskComplexTurnToFaceEntityOrCoord::CTaskComplexTurnToFaceEntityOrCoord(CEntity* entity, float changeRateMult, float maxHeading) :
    CTaskComplex(),
    m_EntityToFace{ entity },
    m_fChangeRateMult{ changeRateMult },
    m_fMaxHeading{ maxHeading },
    m_bFaceEntity{ true }
{
    assert((uintptr_t)entity != (uintptr_t)-1);
    CEntity::SafeRegisterRef(m_EntityToFace);
}

// 0x66B910
CTaskComplexTurnToFaceEntityOrCoord::CTaskComplexTurnToFaceEntityOrCoord(CVector const& coords, float changeRateMult, float maxHeading) :
    CTaskComplex(),
    m_CoordsToFace{ coords },
    m_fChangeRateMult{ changeRateMult },
    m_fMaxHeading{ maxHeading },
    m_bFaceEntity{ false }
{
}

// 0x66B960
CTaskComplexTurnToFaceEntityOrCoord::~CTaskComplexTurnToFaceEntityOrCoord() {
    CEntity::SafeCleanUpRef(m_EntityToFace);
}

// 0x66D250
CTask* CTaskComplexTurnToFaceEntityOrCoord::Clone() const {
    if (m_bFaceEntity) {
        return new CTaskComplexTurnToFaceEntityOrCoord(m_EntityToFace, m_fChangeRateMult, m_fMaxHeading);
    } else {
        return new CTaskComplexTurnToFaceEntityOrCoord(m_CoordsToFace, m_fChangeRateMult, m_fMaxHeading);
    }
}

// 0x66B9D0
float CTaskComplexTurnToFaceEntityOrCoord::ComputeTargetHeading(CPed* ped) const {
    CVector pos = [&] {
        if (m_bFaceEntity) {
            return m_EntityToFace->GetPosition();
        } else {
            return m_CoordsToFace;
        }
    }();

    pos = pos - ped->GetPosition();
    pos.Normalise();
    return CGeneral::GetRadianAngleBetweenPoints(pos.x, pos.y, 0.0f, 0.0f);
}

// 0x670850
CTask* CTaskComplexTurnToFaceEntityOrCoord::CreateFirstSubTask(CPed* ped) {
    if (m_bFaceEntity && !m_EntityToFace)
        return nullptr;

    return new CTaskSimpleAchieveHeading(ComputeTargetHeading(ped), m_fChangeRateMult, m_fMaxHeading);
}

// 0x670920
CTask* CTaskComplexTurnToFaceEntityOrCoord::ControlSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x670920, CTaskComplexTurnToFaceEntityOrCoord*, CPed*>(this, ped);

    if (!m_bFaceEntity)
        return m_pSubTask;

    auto subTask = static_cast<CTaskSimpleAchieveHeading*>(m_pSubTask);
    auto heading = ComputeTargetHeading(ped);

    if (m_EntityToFace) {
        if (subTask->m_fAngle == heading && subTask->m_fChangeRateMult == m_fChangeRateMult) {
            if (subTask->m_fMaxHeading != m_fMaxHeading) {
                subTask->m_fAngle          = heading;
                subTask->m_fChangeRateMult = m_fChangeRateMult;
                subTask->m_fMaxHeading     = m_fMaxHeading;
                return m_pSubTask;
            }
            return m_pSubTask;
        }
        subTask->m_fAngle          = heading;
        subTask->m_fChangeRateMult = m_fChangeRateMult;
        subTask->m_fMaxHeading     = m_fMaxHeading;
        return m_pSubTask;
    }

    if (subTask->m_fAngle == ped->m_fCurrentRotation &&
        subTask->m_fChangeRateMult == m_fChangeRateMult &&
        subTask->m_fMaxHeading == m_fMaxHeading
    ) {
        return m_pSubTask;
    }

    subTask->m_fAngle          = heading;
    subTask->m_fChangeRateMult = m_fChangeRateMult;
    subTask->m_fMaxHeading     = m_fMaxHeading;
    return m_pSubTask;
}
