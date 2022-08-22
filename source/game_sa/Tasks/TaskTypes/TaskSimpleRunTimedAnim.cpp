#include "StdInc.h"

#include "TaskSimpleRunTimedAnim.h"

void CTaskSimpleRunTimedAnim::InjectHooks() {
    RH_ScopedVirtualClass(CTaskSimpleRunTimedAnim, 0x86d570, 9);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedOverloadedInstall(Constructor, "1", 0x61AB70, CTaskSimpleRunTimedAnim * (CTaskSimpleRunTimedAnim::*)(AssocGroupId, AnimationId, float, float, uint32, bool));
    RH_ScopedOverloadedInstall(Constructor, "2", 0x61ABE0, CTaskSimpleRunTimedAnim * (CTaskSimpleRunTimedAnim::*)(AssocGroupId, AnimationId, float, float, uint32, uint32, const char*, bool));
    RH_ScopedInstall(Destructor, 0x48E090);
    RH_ScopedInstall(StartAnim, 0x61AC50);
    RH_ScopedVMTInstall(Clone, 0x61B810);
    RH_ScopedVMTInstall(GetTaskType, 0x48E0E0);
    RH_ScopedVMTInstall(ProcessPed, 0x61BBE0);
}

// 0x61AB70
CTaskSimpleRunTimedAnim::CTaskSimpleRunTimedAnim(AssocGroupId groupId, AnimationId animId, float blendDelta, float unused1, int32 durationMs, bool holdLastFrame) :
    CTaskSimpleAnim{ holdLastFrame },
    m_fBlendDelta{ blendDelta },
    m_fBlendOutDelta{ unused1},
    m_nDurationMs{ durationMs },
    m_AnimId{ animId },
    m_AnimGroup{groupId}
{
}

// 0x61ABE0
CTaskSimpleRunTimedAnim::CTaskSimpleRunTimedAnim(AssocGroupId groupId, AnimationId animId, float blendDelta, float unused1, int32 durationMs, uint32 taskId, const char* unused2, bool holdLastFrame) :
    CTaskSimpleAnim{ holdLastFrame },
    m_fBlendDelta{ blendDelta },
    m_fBlendOutDelta{ unused1 },
    m_nDurationMs{ durationMs },
    m_AnimId{ animId },
    m_AnimGroup{ groupId}
{
}

// 0x61AC50
void CTaskSimpleRunTimedAnim::StartAnim(CPed* ped) {
    m_pAnim = CAnimManager::BlendAnimation(ped->m_pRwClump, m_AnimGroup, m_AnimId, m_fBlendDelta);
}

// 0x61BBE0
bool CTaskSimpleRunTimedAnim::ProcessPed(CPed* ped) {
    if (m_bIsFinished) {
        return true;
    }

    if (m_Timer.IsOutOfTime()) {
        MakeAbortable(ped, ABORT_PRIORITY_LEISURE, nullptr);
    }

    if (!m_pAnim && !RpAnimBlendClumpGetAssociation(ped->m_pRwClump, (uint32)m_AnimId)) {
        m_Timer.Start((int32)m_nDurationMs);
        StartAnim(ped);
    }

    return m_bIsFinished;
}
