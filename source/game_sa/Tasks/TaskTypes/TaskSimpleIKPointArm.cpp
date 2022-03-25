#include "StdInc.h"
#include "TaskSimpleIKPointArm.h"
#include "IKChain_c.h"
#include "IKChainManager_c.h"

void CTaskSimpleIKPointArm::InjectHooks() {
    RH_ScopedClass(CTaskSimpleIKPointArm);
    RH_ScopedCategoryGlobal(); // TODO: Change this to the appropriate category!

    RH_ScopedInstall(Constructor, 0x634150);
    RH_ScopedInstall(Destructor, 0x634240);

    RH_ScopedInstall(UpdatePointArmInfo, 0x634370);
    RH_ScopedInstall(Clone_Reversed, 0x634250);
    RH_ScopedInstall(GetTaskType_Reversed, 0x634230);
    RH_ScopedInstall(CreateIKChain_Reversed, 0x6342F0);
}

// 0x634150
CTaskSimpleIKPointArm::CTaskSimpleIKPointArm(const char* purpose, int32 arm, CEntity* targetEntity, ePedBones offsetBone, RwV3d offsetPosn, float speed, int32 blendTime)
    : CTaskSimpleIKChain{purpose, arm ? BONE_L_HAND : BONE_R_HAND, CVector{0.f, 0.05f, 0.f}, BONE_NORMAL, targetEntity, offsetBone, offsetPosn, speed, 999'999, blendTime},
      m_hand{arm} {}

// 0x634240
CTaskSimpleIKPointArm::~CTaskSimpleIKPointArm() {}

CTaskSimpleIKPointArm* CTaskSimpleIKPointArm::Constructor(const char* purpose, int32 hand, CEntity* targetEntity, ePedBones bone, RwV3d offsetPosn, float speed, int32 blendTime) {
    this->CTaskSimpleIKPointArm::CTaskSimpleIKPointArm(purpose, hand, targetEntity, bone, offsetPosn, speed, blendTime);
    return this;
}

// 0x634240
CTaskSimpleIKPointArm* CTaskSimpleIKPointArm::Destructor() {
    this->CTaskSimpleIKPointArm::~CTaskSimpleIKPointArm();
    return this;
}

// 0x634370
void CTaskSimpleIKPointArm::UpdatePointArmInfo(const char* name, CEntity* entity, ePedBones offsetBoneTag, RwV3d posn, float speed, int32 blendTime) {
    m_bEntityExist = !!entity;
    CEntity::ChangeEntityReference(m_pEntity, entity);

    m_nOffsetBoneTag = offsetBoneTag;
    m_vecOffsetPos = posn;
    m_fSpeed = speed;
    m_nBlendTime = blendTime;
    m_nEndTime = CTimer::GetTimeInMS() + 999'999;
    m_fTargetBlend = 1.f;
    m_nTargetTime = CTimer::GetTimeInMS() + blendTime;
    m_bIsBlendingOut = false;

    // Update IK chain
    if (m_pIKChain) {
        m_pIKChain->UpdateEntity(m_pEntity);
        m_pIKChain->UpdateOffset(m_nOffsetBoneTag, m_vecOffsetPos);
        m_pIKChain->UpdateTarget(true);
    }
}

// 0x6342F0
bool CTaskSimpleIKPointArm::CreateIKChain(CPed* ped) {
    m_pIKChain = g_ikChainMan.AddIKChain("", m_hand ? BONE_SPINE : BONE_PELVIS, ped, m_nEffectorBoneTag, m_vecEffectorVec, BONE_NECK, m_pEntity, m_nOffsetBoneTag, m_vecOffsetPos, m_fSpeed, 3);
    return !!m_pIKChain;
}
