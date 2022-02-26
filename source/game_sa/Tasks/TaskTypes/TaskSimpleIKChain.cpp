#include "StdInc.h"
#include "TaskSimpleIKChain.h"
#include "IKChainManager_c.h"

void CTaskSimpleIKChain::InjectHooks() {
    RH_ScopedClass(CTaskSimpleIKChain);
    RH_ScopedCategoryGlobal(); // TODO: Change this to the appropriate category!

    RH_ScopedInstall(Constructor, 0x6339C0);
    RH_ScopedOverloadedInstall(Destructor, "", 0x633A90, CTaskSimpleIKChain*(CTaskSimpleIKChain::*)());

    //RH_ScopedInstall(BlendOut, 0x633C40);
    //RH_ScopedInstall(GetIKChain, 0x633C70);
    //RH_ScopedInstall(Clone_Reversed, 0x633B00);
    //RH_ScopedInstall(GetTaskType_Reversed, 0x62EC30);
    //RH_ScopedInstall(MakeAbortable_Reversed, 0x639450);
    //RH_ScopedInstall(ProcessPed_Reversed, 0x633C80);
    //RH_ScopedInstall(CreateIKChain_Reversed, 0x633BD0);

}

// 0x6339C0
CTaskSimpleIKChain::CTaskSimpleIKChain(const char* name, int16 effectorBoneTag, RwV3d effectorVec, int16 pivotBoneTag, CEntity* entity, int32 offsetBoneTag, RwV3d offsetPos, float speed, int32 time, int32 blendTime) :
    m_nEffectorBoneTag{ effectorBoneTag },
    m_nTime{ time },
    m_nBlendTime{ blendTime },
    m_vecEffectorVec{ effectorVec },
    m_vecOffsetPos{ offsetPos },
    m_nPivotBoneTag{ pivotBoneTag },
    m_pEntity{ entity },
    m_bEntityExist{ !!entity },
    m_fSpeed{ speed }
{
    if (m_pEntity) {
        m_pEntity->RegisterReference(&m_pEntity);
    }
}

// 0x6339C0
CTaskSimpleIKChain* CTaskSimpleIKChain::Constructor(char* name, int32 effectorBoneTag, RwV3d effectorVec, int32 pivotBoneTag, CEntity* a6, int32 offsetBoneTag, RwV3d offsetPos, float speed, int32 time, int32 blendTime) {
    this->CTaskSimpleIKChain::CTaskSimpleIKChain(name, effectorBoneTag, effectorVec, pivotBoneTag, a6, offsetBoneTag, offsetPos, speed, time, blendTime);
    return this;
}

// 0x633A90
CTaskSimpleIKChain::~CTaskSimpleIKChain() {
    if (m_pIKChain) {
        g_ikChainMan.RemoveIKChain(m_pIKChain);
    }
    CEntity::ClearReference(m_pEntity);
}

// 0x633A90
CTaskSimpleIKChain* CTaskSimpleIKChain::Destructor() {
    this->CTaskSimpleIKChain::~CTaskSimpleIKChain();
    return this;
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
CTaskSimpleIKChain* CTaskSimpleIKChain::GetIKChain() {
    return plugin::CallMethodAndReturn<CTaskSimpleIKChain*, 0x633C70, CTaskSimpleIKChain*>(this);
}

// 0x633B00
CTaskSimpleIKChain* CTaskSimpleIKChain::Clone() {
    return plugin::CallMethodAndReturn< CTaskSimpleIKChain*, 0x633B00, CTaskSimpleIKChain*>(this);
}

// 0x639450
bool CTaskSimpleIKChain::MakeAbortable(CPed* ped, eAbortPriority priority, CEvent const* event) {
    return plugin::CallMethodAndReturn<bool, 0x639450, CTaskSimpleIKChain*, CPed*, eAbortPriority, CEvent const*>(this, ped, priority, event);
}

// 0x633C80
bool CTaskSimpleIKChain::ProcessPed(CPed* ped) {
    return plugin::CallMethodAndReturn<bool, 0x633C80, CTaskSimpleIKChain*, CPed*>(this, ped);
}

// 0x633BD0
bool CTaskSimpleIKChain::CreateIKChain(CPed* ped) {
    return plugin::CallMethodAndReturn<bool, 0x633BD0, CTaskSimpleIKChain*, CPed*>(this, ped);
}

