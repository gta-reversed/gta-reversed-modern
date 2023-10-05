#include "StdInc.h"
#include "TaskSimpleIKChain.h"
#include "IKChainManager_c.h"

void CTaskSimpleIKChain::InjectHooks() {
    RH_ScopedClass(CTaskSimpleIKChain);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x6339C0);
    RH_ScopedInstall(Destructor, 0x633A90);

    RH_ScopedInstall(BlendOut, 0x633C40);
    RH_ScopedInstall(GetIKChain, 0x633C70);
    RH_ScopedInstall(Clone_Reversed, 0x633B00);
    RH_ScopedInstall(GetTaskType_Reversed, 0x62EC30);
    RH_ScopedInstall(MakeAbortable_Reversed, 0x639450);
    RH_ScopedInstall(ProcessPed_Reversed, 0x633C80);
    RH_ScopedInstall(CreateIKChain_Reversed, 0x633BD0);
}

// 0x6339C0
CTaskSimpleIKChain::CTaskSimpleIKChain(const char* name, ePedBones effectorBoneTag, CVector effectorPos, ePedBones pivotBoneTag, CEntity* entity, ePedBones offsetBoneTag,
                                       CVector offsetPos, float speed, int32 time, int32 blendTime) : CTaskSimple()
{
    m_nEffectorBoneTag = effectorBoneTag;
    m_nTime            = time;
    m_nBlendTime       = blendTime;
    m_vecEffectorVec   = effectorPos;
    m_vecOffsetPos     = offsetPos;
    m_nPivotBoneTag    = pivotBoneTag;
    m_pIKChain         = nullptr;
    m_pEntity          = entity;
    m_bEntityExist     = !!entity;
    m_fSpeed           = speed;
    CEntity::SafeRegisterRef(m_pEntity);
    m_bIsBlendingOut   = false;
}

// 0x633A90
CTaskSimpleIKChain::~CTaskSimpleIKChain() {
    if (m_pIKChain) {
        g_ikChainMan.RemoveIKChain(m_pIKChain);
    }
    CEntity::ClearReference(m_pEntity);
}

// 0x633B00
CTask* CTaskSimpleIKChain::Clone() const {
    auto* task = new CTaskSimpleIKChain("", m_nEffectorBoneTag, m_vecEffectorVec, m_nPivotBoneTag, m_pEntity, m_nOffsetBoneTag, m_vecOffsetPos, m_fSpeed, m_nTime, m_nBlendTime);
    if (m_pIKChain) {
        task->m_fBlend       = m_fBlend;
        task->m_nEndTime     = m_nEndTime;
        task->m_fTargetBlend = m_fTargetBlend;
        task->m_nTargetTime  = m_nTargetTime;
    }
    return task;
}

// 0x633C40
void CTaskSimpleIKChain::BlendOut(int32 blendOutTime) {
    if (!m_bIsBlendingOut) {
        if (m_nTime == -1) {
            m_nTime = 0;
        }
        m_nEndTime = CTimer::GetTimeInMS() + blendOutTime;
        m_bIsBlendingOut = true;
    }
}

// 0x633C70
IKChain_c* CTaskSimpleIKChain::GetIKChain() {
    return m_pIKChain;
}

// 0x639450
bool CTaskSimpleIKChain::MakeAbortable(CPed* ped, eAbortPriority priority, CEvent const* event) {
    if (priority == eAbortPriority::ABORT_PRIORITY_IMMEDIATE) {
        return true;
    }
    BlendOut(250);
    return false;
}

// 0x633C80
bool CTaskSimpleIKChain::ProcessPed(CPed* ped) {
    // If IK chain doesn't exist, try creating and early out
    if (!m_pIKChain) {
        if (!m_bEntityExist || m_pEntity) {
            if (CreateIKChain(ped)) {
                if (m_nTime == -1) {
                    m_nEndTime = -1;
                } else {
                    m_nEndTime = CTimer::GetTimeInMS() + m_nTime;
                }
                m_nTargetTime = CTimer::GetTimeInMS() + m_nBlendTime;
                m_fTargetBlend = 1.f;
                m_pIKChain->SetBlend(m_fBlend);
                return false;
            }
        }
        return true;
    }

    // 0x633D2B
    if (m_nTime == -1 && (int32)CTimer::GetTimeInMS() > m_nEndTime) {
        g_ikChainMan.RemoveIKChain(m_pIKChain);
        m_pIKChain = nullptr;
        return true;
    }

    // Deal with blending

    // 0x633D50
    if (m_bEntityExist && !m_pEntity) {
        m_bEntityExist = false;
        m_pIKChain->UpdateTarget(false);
        BlendOut();
    }

    // 0x633D75
    if (m_nTime != -1) {
        if ((int32)CTimer::GetTimeInMS() >= m_nEndTime - m_nBlendTime) {
            m_fTargetBlend = 0.f;
            m_nTargetTime = m_nEndTime;
        }
    }

    // 0x633D98
    if ((int32)CTimer::GetTimeInMS() <= m_nTargetTime) {
        m_fBlend += (m_fTargetBlend - m_fBlend) * std::min(1.0f, CTimer::GetTimeStepInMS() / (float)(m_nTargetTime - CTimer::GetTimeStepInMS() - CTimer::GetTimeInMS()));
    } else {
        m_fBlend = m_fTargetBlend;
    }

    m_pIKChain->SetBlend(m_fBlend);
    return false;
}

// 0x633BD0
bool CTaskSimpleIKChain::CreateIKChain(CPed* ped) {
    m_pIKChain = g_ikChainMan.AddIKChain("", 3, ped, m_nEffectorBoneTag, m_vecEffectorVec, m_nPivotBoneTag, m_pEntity, m_nOffsetBoneTag, m_vecOffsetPos, m_fSpeed, 3);
    return m_pIKChain != nullptr;
}
