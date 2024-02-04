#include "StdInc.h"
#include "TaskSimpleIKChain.h"
#include "IKChainManager_c.h"

void CTaskSimpleIKChain::InjectHooks() {
    RH_ScopedVirtualClass(CTaskSimpleIKChain, 0x86DB48, 10);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x6339C0);
    RH_ScopedInstall(Destructor, 0x633A90);

    RH_ScopedInstall(BlendOut, 0x633C40);
    RH_ScopedInstall(GetIKChain, 0x633C70);
    RH_ScopedVMTInstall(Clone, 0x633B00);
    RH_ScopedVMTInstall(GetTaskType, 0x62EC30);
    RH_ScopedVMTInstall(MakeAbortable, 0x639450);
    RH_ScopedVMTInstall(ProcessPed, 0x633C80);
    RH_ScopedVMTInstall(CreateIKChain, 0x633BD0);
}

// 0x6339C0
CTaskSimpleIKChain::CTaskSimpleIKChain(
    const char* name,
    ePedBones effectorBoneTag,
    CVector effectorPos,
    ePedBones pivotBoneTag,
    CEntity* entity,
    ePedBones offsetBoneTag,
    CVector offsetPos,
    float speed,
    int32 time,
    int32 blendTime
) :
    m_EffectorBoneTag{ effectorBoneTag },
    m_Duration{ time },
    m_BlendDuration{ blendTime },
    m_EffectorVec{ effectorPos },
    m_OffsetPos{ offsetPos },
    m_PivotBoneTag{ pivotBoneTag },
    m_Entity{ entity },
    m_EntityExisted{ !!entity },
    m_Speed{ speed }
{
}

// 0x633A90
CTaskSimpleIKChain::~CTaskSimpleIKChain() {
    if (m_IKChain) {
        g_ikChainMan.RemoveIKChain(m_IKChain);
    }
}

// 0x633B00
CTask* CTaskSimpleIKChain::Clone() const {
    auto* task = new CTaskSimpleIKChain("", m_EffectorBoneTag, m_EffectorVec, m_PivotBoneTag, m_Entity, m_OffsetBoneTag, m_OffsetPos, m_Speed, m_Duration, m_BlendDuration);
    if (m_IKChain) {
        task->m_Blend       = m_Blend;
        task->m_EndTime     = m_EndTime;
        task->m_TargetBlend = m_TargetBlend;
        task->m_TargetTime  = m_TargetTime;
    }
    return task;
}

// 0x633C40
void CTaskSimpleIKChain::BlendOut(int32 blendOutTime) {
    if (!m_IsBlendingOut) {
        if (m_Duration == -1) {
            m_Duration = 0;
        }
        m_EndTime = CTimer::GetTimeInMS() + blendOutTime;
        m_IsBlendingOut = true;
    }
}

// 0x633C70
IKChain_c* CTaskSimpleIKChain::GetIKChain() const {
    return m_IKChain;
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
    if (!m_IKChain) {
        if (!m_EntityExisted || m_Entity) {
            if (CreateIKChain(ped)) {
                if (m_Duration == -1) {
                    m_EndTime = -1;
                } else {
                    m_EndTime = CTimer::GetTimeInMS() + m_Duration;
                }
                m_TargetTime = CTimer::GetTimeInMS() + m_BlendDuration;
                m_TargetBlend = 1.f;
                m_IKChain->SetBlend(m_Blend);
                return false;
            }
        }
        return true;
    }

    // 0x633D2B
    if (m_Duration == -1 && (int32)CTimer::GetTimeInMS() > m_EndTime) {
        g_ikChainMan.RemoveIKChain(m_IKChain);
        m_IKChain = nullptr;
        return true;
    }

    // Deal with blending

    // 0x633D50
    if (m_EntityExisted && !m_Entity) {
        m_EntityExisted = false;
        m_IKChain->UpdateTarget(false);
        BlendOut();
    }

    // 0x633D75
    if (m_Duration != -1) {
        if ((int32)CTimer::GetTimeInMS() >= m_EndTime - m_BlendDuration) {
            m_TargetBlend = 0.f;
            m_TargetTime = m_EndTime;
        }
    }

    // 0x633D98
    if ((int32)CTimer::GetTimeInMS() <= m_TargetTime) {
        m_Blend += (m_TargetBlend - m_Blend) * std::min(1.0f, CTimer::GetTimeStepInMS() / (float)(m_TargetTime - CTimer::GetTimeStepInMS() - CTimer::GetTimeInMS()));
    } else {
        m_Blend = m_TargetBlend;
    }

    m_IKChain->SetBlend(m_Blend);
    return false;
}

// 0x633BD0
bool CTaskSimpleIKChain::CreateIKChain(CPed* ped) {
    m_IKChain = g_ikChainMan.AddIKChain("", 3, ped, m_EffectorBoneTag, m_EffectorVec, m_PivotBoneTag, m_Entity, m_OffsetBoneTag, m_OffsetPos, m_Speed, 3);
    return m_IKChain != nullptr;
}

