#include "StdInc.h"
#include "IKChainManager_c.h"
#include "TaskSimpleIKLookAt.h"

void CTaskSimpleIKLookAt::InjectHooks() {
    RH_ScopedVirtualClass(CTaskSimpleIKLookAt, 0x86E37C, 10);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x633E00);
    RH_ScopedOverloadedInstall(Destructor, "", 0x633EF0, CTaskSimpleIKLookAt * (CTaskSimpleIKLookAt::*)());

    RH_ScopedInstall(UpdateLookAtInfo, 0x634050);
    RH_ScopedInstall(GetLookAtEntity, 0x634120);
    RH_ScopedInstall(GetLookAtOffset, 0x634130);
    RH_ScopedVMTInstall(Clone, 0x633F00);
    RH_ScopedVMTInstall(GetTaskType, 0x633EE0);
    RH_ScopedVMTInstall(CreateIKChain, 0x633FC0);
}

// 0x633E00
CTaskSimpleIKLookAt::CTaskSimpleIKLookAt(Const char* name, CEntity* lookAtEntity, int32 time, ePedBones pedBoneID, CVector lookAtOffset, bool useTorso, float speed,
                                         int32 blendTime, int8 priority
)
    : CTaskSimpleIKChain{name, BONE_HEAD, { 0.f, 0.05f, 0.f }, BONE_NORMAL, lookAtEntity, pedBoneID, lookAtOffset, speed, time, blendTime}
{
    m_nPriority = priority;
    m_bUseTorso = useTorso;
}

// 0x633F00


CTaskSimpleIKLookAt* CTaskSimpleIKLookAt::Clone() const {
    auto* task = new CTaskSimpleIKLookAt("", m_Entity, m_Duration, m_OffsetBoneTag, m_OffsetPos, m_bUseTorso, m_Speed, m_BlendDuration, m_nPriority);
    if (m_IKChain) {
        task->m_Blend        = m_Blend;
        task->m_EndTime      = m_EndTime;
        task->m_TargetBlend  = m_TargetBlend;
        task->m_TargetTime   = m_TargetTime;
        task->m_PivotBoneTag = m_PivotBoneTag;
    }
    return task;
}

// 0x634050
void CTaskSimpleIKLookAt::UpdateLookAtInfo(const char* strPurpose, CPed* ped, CEntity* targetPed, int32 time, ePedBones pedBoneID, RwV3d lookAtOffset, bool useTorso, float fSpeed,
                                           int32 blendTime, int32 unused) {
    m_EntityExisted = !!targetPed;
    m_Entity = targetPed;

    m_OffsetBoneTag = pedBoneID;
    m_OffsetPos   = lookAtOffset;
    m_bUseTorso      = useTorso;
    m_Duration          = time;
    m_Speed         = fSpeed;
    m_BlendDuration     = blendTime;
    m_EndTime       = CTimer::GetTimeInMS() + time;
    m_TargetBlend   = 1.0f;
    m_TargetTime    = CTimer::GetTimeInMS() + blendTime;
    m_IsBlendingOut = false;

    // Update IK chain
    if (m_IKChain) {
        m_IKChain->UpdateEntity(m_Entity);
        m_IKChain->UpdateOffset(m_OffsetBoneTag, m_OffsetPos);
        m_IKChain->UpdateTarget(true);
    }
}

// 0x634120
CEntity* CTaskSimpleIKLookAt::GetLookAtEntity() {
    return m_Entity;
}

// 0x634130
CVector CTaskSimpleIKLookAt::GetLookAtOffset() { // We return a vector here.. Hopefully this is ABI compatible.
    return m_OffsetPos;
}

// 0x633FC0

// 0x0
bool CTaskSimpleIKLookAt::CreateIKChain(CPed* ped) {
    m_PivotBoneTag = BONE_NECK;
    m_IKChain = g_ikChainMan.AddIKChain("", BONE_NORMAL, ped, m_EffectorBoneTag, m_EffectorVec, BONE_NECK, m_Entity, m_OffsetBoneTag, m_OffsetPos, m_Speed, m_nPriority);
    if (m_IKChain) {
        m_IKChain->ClampLimits(BONE_HEAD, false, true, false, true);
        return true;
    }
    return false;
}

