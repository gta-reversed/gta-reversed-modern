#include "StdInc.h"
#include "TaskSimpleIKPointArm.h"
#include "IKChain_c.h"
#include "IKChainManager_c.h"

void CTaskSimpleIKPointArm::InjectHooks() {
    RH_ScopedVirtualClass(CTaskSimpleIKPointArm, 0x86E3A4, 10);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x634150);
    RH_ScopedInstall(Destructor, 0x634240);
    RH_ScopedInstall(UpdatePointArmInfo, 0x634370);
    RH_ScopedVMTInstall(Clone, 0x634250);
    RH_ScopedVMTInstall(GetTaskType, 0x634230);
    RH_ScopedVMTInstall(CreateIKChain, 0x6342F0);
}

// 0x634150
CTaskSimpleIKPointArm::CTaskSimpleIKPointArm(const char* purpose, int32 hand, CEntity* targetEntity, ePedBones bone, CVector offsetPos, float speed, int32 blendTime) :
    CTaskSimpleIKChain{
        purpose,
        hand ? BONE_L_HAND : BONE_R_HAND,
        CVector{ 0.f, 0.05f, 0.f },
        BONE_NORMAL,
        targetEntity,
        bone,
        offsetPos,
        speed,
        999'999,
        blendTime
    }
{
    m_Hand = hand;
}

// 0x634250
CTask* CTaskSimpleIKPointArm::Clone() const {
    const auto task = new CTaskSimpleIKPointArm("", m_Hand, m_Entity, m_OffsetBoneTag, m_OffsetPos, m_Speed, m_BlendDuration);
    if (m_IKChain) {
        task->m_Blend       = m_Blend;
        task->m_EndTime     = m_EndTime;
        task->m_TargetBlend = m_TargetBlend;
        task->m_TargetTime  = m_TargetTime;
    }
    return task;
}

// 0x634370
void CTaskSimpleIKPointArm::UpdatePointArmInfo(const char* purpose, CEntity* entity, ePedBones bone, CVector posn, float speed, int32 timeOffset) {
    m_EntityExisted = !!entity;
    m_Entity        = entity;
    m_OffsetBoneTag = bone;
    m_OffsetPos     = posn;
    m_Speed         = speed;
    m_BlendDuration = timeOffset;
    m_EndTime       = CTimer::GetTimeInMS() + 999'999;
    m_TargetBlend   = 1.f;
    m_TargetTime    = CTimer::GetTimeInMS() + timeOffset;
    m_IsBlendingOut = false;

    if (m_IKChain) {
        m_IKChain->UpdateEntity(m_Entity);
        m_IKChain->UpdateOffset(m_OffsetBoneTag, m_OffsetPos);
        m_IKChain->UpdateTarget(true);
    }
}

// 0x6342F0
bool CTaskSimpleIKPointArm::CreateIKChain(CPed* ped) {
    m_PivotBoneTag = BONE_NECK;
    m_IKChain = g_ikChainMan.AddIKChain("", m_Hand ? 2 : 1, ped, m_EffectorBoneTag, m_EffectorVec, BONE_NECK, m_Entity, m_OffsetBoneTag, m_OffsetPos, m_Speed, 3);
    return m_IKChain != nullptr;
}
