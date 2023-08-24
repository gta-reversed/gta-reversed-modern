#include "StdInc.h"

#include "TaskComplexEvasiveDiveAndGetUp.h"

#include "TaskSimpleAchieveHeading.h"
#include "TaskSimpleEvasiveDive.h"
#include "TaskSimplePause.h"
#include "TaskSimpleGetUp.h"

void CTaskComplexEvasiveDiveAndGetUp::InjectHooks() {
    RH_ScopedVirtualClass(CTaskComplexEvasiveDiveAndGetUp, 0x86f268, 11);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x6536B0);
    RH_ScopedInstall(Destructor, 0x653740);

    RH_ScopedInstall(CreateSubTask, 0x653820);

    RH_ScopedVMTInstall(Clone, 0x655940);
    RH_ScopedVMTInstall(GetTaskType, 0x653730);
    RH_ScopedVMTInstall(MakeAbortable, 0x6537A0);
    RH_ScopedVMTInstall(CreateNextSubTask, 0x656000);
    RH_ScopedVMTInstall(CreateFirstSubTask, 0x6560A0);
    RH_ScopedVMTInstall(ControlSubTask, 0x653810);
}

// 0x6536B0
CTaskComplexEvasiveDiveAndGetUp::CTaskComplexEvasiveDiveAndGetUp(CVehicle* target, int32 unconsciousTime, const CVector& diveDir, bool bAchieveHeadingFirst) :
    m_UnconsciousTime{unconsciousTime},
    m_TargetVeh{target},
    m_bAchieveHeadingFirst{bAchieveHeadingFirst},
    m_DiveDir{diveDir}
{
    CEntity::SafeRegisterRef(m_TargetVeh);
}

// 0x653740
CTaskComplexEvasiveDiveAndGetUp::~CTaskComplexEvasiveDiveAndGetUp() {
    CEntity::SafeCleanUpRef(m_TargetVeh);
}

// 0x653820
CTask* CTaskComplexEvasiveDiveAndGetUp::CreateSubTask(eTaskType tt) {
    switch (tt) {
    case TASK_SIMPLE_ACHIEVE_HEADING:
        return new CTaskSimpleAchieveHeading{m_DiveDir.Heading()};
    case TASK_SIMPLE_EVASIVE_DIVE:
        return new CTaskSimpleEvasiveDive{m_TargetVeh};
    case TASK_SIMPLE_PAUSE:
        return new CTaskSimplePause{m_UnconsciousTime};
    case TASK_SIMPLE_GET_UP:
        return new CTaskSimpleGetUp{};
    default:
        NOTSA_UNREACHABLE();
    }
}

// 0x6537A0
bool CTaskComplexEvasiveDiveAndGetUp::MakeAbortable(CPed* ped, eAbortPriority priority, CEvent const* event) {
    const auto isSubTaskAbortable = m_pSubTask->MakeAbortable(ped, priority, event);
    if (isSubTaskAbortable && priority == ABORT_PRIORITY_IMMEDIATE) {
        if (const auto a = RpAnimBlendClumpGetAssociation(ped->m_pRwClump, ANIM_ID_EV_DIVE)) {
            a->m_fBlendDelta = -1000.f;
        }
    }
    return isSubTaskAbortable;
}

// 0x656000
CTask* CTaskComplexEvasiveDiveAndGetUp::CreateNextSubTask(CPed* ped) {
    return CreateSubTask([this, ped] {
        switch (m_pSubTask->GetTaskType()) {
        case TASK_SIMPLE_ACHIEVE_HEADING:
            return TASK_SIMPLE_EVASIVE_DIVE;
        case TASK_SIMPLE_EVASIVE_DIVE:
            return TASK_SIMPLE_PAUSE;
        case TASK_SIMPLE_PAUSE: {
            ped->m_fCurrentRotation = ped->m_fAimingRotation = CGeneral::LimitRadianAngle(ped->m_fCurrentRotation - PI / 2.f);
            return TASK_SIMPLE_GET_UP;
        }
        case TASK_SIMPLE_GET_UP:
            return TASK_FINISHED;
        default:
            NOTSA_UNREACHABLE();
        }
    }());
}

// 0x6560A0
CTask* CTaskComplexEvasiveDiveAndGetUp::CreateFirstSubTask(CPed* ped) {
    return CreateSubTask(m_bAchieveHeadingFirst ? TASK_SIMPLE_ACHIEVE_HEADING : TASK_SIMPLE_EVASIVE_DIVE);
}
