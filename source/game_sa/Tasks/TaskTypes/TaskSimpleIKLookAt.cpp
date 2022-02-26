#include "StdInc.h"
#include "IKChainManager_c.h"
#include "TaskSimpleIKLookAt.h"

void CTaskSimpleIKLookAt::InjectHooks() {
    RH_ScopedClass(CTaskSimpleIKLookAt);
    RH_ScopedCategoryGlobal(); // TODO: Change this to the appropriate category!

    RH_ScopedInstall(Constructor, 0x633E00);
    RH_ScopedOverloadedInstall(Destructor, "", 0x633EF0, CTaskSimpleIKLookAt*(CTaskSimpleIKLookAt::*)());

    RH_ScopedInstall(UpdateLookAtInfo, 0x634050);
    RH_ScopedInstall(GetLookAtEntity, 0x634120);
    RH_ScopedInstall(GetLookAtOffset, 0x634130);
    RH_ScopedInstall(Clone_Reversed, 0x633F00);
    RH_ScopedInstall(GetTaskType_Reversed, 0x633EE0);
    RH_ScopedInstall(CreateIKChain_Reversed, 0x633FC0);
}

// 0x633E00
CTaskSimpleIKLookAt::CTaskSimpleIKLookAt(const char* name, CEntity* lookAtEntity, int32 time, ePedBones pedBoneID, CVector lookAtOffset, bool useTorso, float speed, uint32 blendTime, uint8 priority) :
    CTaskSimpleIKChain{ name, BONE_HEAD, {0.f, 0.05f, 0.f}, BONE_NORMAL, lookAtEntity, pedBoneID, lookAtOffset, speed, time, blendTime},
    m_nPriority{priority},
    m_bUseTorso{useTorso}
{
}

// 0x633E00
CTaskSimpleIKLookAt* CTaskSimpleIKLookAt::Constructor(char* name, CEntity* lookAtEntity, int32 time, ePedBones pedBoneID, RwV3d lookAtOffset, uint8 useTorso, float fSpeed, int32 blendTime,
                                                      int32 priority) {
    this->CTaskSimpleIKLookAt::CTaskSimpleIKLookAt(name, lookAtEntity, time, pedBoneID, lookAtOffset, useTorso, fSpeed, blendTime, priority);
    return this;
}

// 0x633EF0
CTaskSimpleIKLookAt::~CTaskSimpleIKLookAt() {}

// 0x633EF0
CTaskSimpleIKLookAt* CTaskSimpleIKLookAt::Destructor() {
    this->CTaskSimpleIKLookAt::~CTaskSimpleIKLookAt();
    return this;
}

// 0x634050
void CTaskSimpleIKLookAt::UpdateLookAtInfo(const char* strPurpose, CPed* ped, CEntity* targetPed, int32 time, ePedBones pedBoneID, RwV3d lookAtOffset, bool useTorso, float fSpeed,
                                           int32 blendTime, int32 unused) {
    m_bEntityExist = !!targetPed;
    CEntity::ChangeEntityReference(m_pEntity, targetPed);

    m_nOffsetBoneTag = pedBoneID;
    m_vecOffsetPos = lookAtOffset;
    m_bUseTorso = useTorso;
    m_nTime = time;
    m_fSpeed = fSpeed;
    m_nBlendTime = blendTime;
    m_nEndTime = CTimer::GetTimeInMS() + time;
    m_fTargetBlend = 1.f;
    m_nTargetTime = CTimer::GetTimeInMS() + blendTime;
    m_bIsBlendingOut = false;

    // Update IK chain
    if (m_pIKChain) {
        m_pIKChain->UpdateEntity(m_pEntity);
        m_pIKChain->UpdateOffset(m_nOffsetBoneTag, m_vecOffsetPos);
        m_pIKChain->UpdateTarget(1u);
    }
}

// 0x634120
CEntity* CTaskSimpleIKLookAt::GetLookAtEntity() {
    return m_pEntity;
}

// 0x634130
CVector CTaskSimpleIKLookAt::GetLookAtOffset() { // We return a vector here.. Hopefully this is ABI compatible.
    return m_vecOffsetPos;
}

// 0x633FC0
bool CTaskSimpleIKLookAt::CreateIKChain(CPed* ped) {
    m_nPivotBoneTag = BONE_NECK;
    m_pIKChain = g_ikChainMan.AddIKChain("", BONE_NORMAL, ped, m_nEffectorBoneTag, m_vecEffectorVec, BONE_NECK, m_pEntity, m_nOffsetBoneTag, m_vecOffsetPos, m_fSpeed, m_nPriority);
    if (m_pIKChain) {
        m_pIKChain->ClampLimits(5, 0, 1u, 0, 1);
        return true;
    }
    return false;
}
