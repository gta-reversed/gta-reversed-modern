#include "StdInc.h"

void CTaskSimplePickUpEntity::InjectHooks() {
    HookInstall(0x691870, (CTaskSimplePickUpEntity*(CTaskSimplePickUpEntity::*)(CEntity*, CVector*, char, uint8, CAnimBlock*, CAnimBlendHierarchy*, int, float)) & CTaskSimplePickUpEntity::Constructor);
    HookInstall(0x6917B0, (CTaskSimplePickUpEntity * (CTaskSimplePickUpEntity::*)(CEntity*, CVector*, char, uint8, AnimationId, AssocGroupId, float)) & CTaskSimplePickUpEntity::Constructor);
    HookInstall(0x692A90, &CTaskSimplePickUpEntity::Clone_Reversed);
    HookInstall(0x691810, &CTaskSimplePickUpEntity::GetId_Reversed);
}

CTaskSimplePickUpEntity::CTaskSimplePickUpEntity(CEntity* pEntityToHold, CVector* pPosition, char boneFrameId, uint8 boneFlags,
    CAnimBlock* pAnimBlock, CAnimBlendHierarchy* pAnimHierarchy, int animFlags, float fMovePedUntilAnimProgress) : CTaskSimpleHoldEntity(pEntityToHold, pPosition, boneFrameId, boneFlags, pAnimBlock, pAnimHierarchy, animFlags) {
    m_fMovePedUntilAnimProgress = fMovePedUntilAnimProgress;
} 

CTaskSimplePickUpEntity::CTaskSimplePickUpEntity(CEntity* pEntityToHold, CVector* pPosition, char boneFrameId, uint8 boneFlags,
    AnimationId animId, AssocGroupId groupId, float fMovePedUntilAnimProgress) : CTaskSimpleHoldEntity(pEntityToHold, pPosition, boneFrameId, boneFlags, animId, groupId, false) {
    m_fMovePedUntilAnimProgress = fMovePedUntilAnimProgress;
} 

CTaskSimplePickUpEntity::~CTaskSimplePickUpEntity() {
    // nothing here
}

// 0x691870
CTaskSimplePickUpEntity* CTaskSimplePickUpEntity::Constructor(CEntity* pEntityToHold, CVector* pPosition, char boneFrameId, uint8 boneFlags, CAnimBlock* pAnimBlock, CAnimBlendHierarchy* pAnimHierarchy, int animFlags, float fMovePedUntilAnimProgress) {
    this->CTaskSimplePickUpEntity::CTaskSimplePickUpEntity(pEntityToHold, pPosition, boneFrameId, boneFlags, pAnimBlock, pAnimHierarchy, animFlags, fMovePedUntilAnimProgress);
    return this;
}

// 0x6917B0
CTaskSimplePickUpEntity* CTaskSimplePickUpEntity::Constructor(CEntity* pEntityToHold, CVector* pPosition, char boneFrameId, uint8 boneFlags, AnimationId animId, AssocGroupId groupId, float fMovePedUntilAnimProgress){
    this->CTaskSimplePickUpEntity::CTaskSimplePickUpEntity(pEntityToHold, pPosition, boneFrameId, boneFlags, animId, groupId, fMovePedUntilAnimProgress);
    return this;
}

// 0x692A90
CTask* CTaskSimplePickUpEntity::Clone() {
    return CTaskSimplePickUpEntity::Clone_Reversed();
}

// 0x691810
eTaskType CTaskSimplePickUpEntity::GetId() {
    return CTaskSimplePickUpEntity::GetId_Reversed();
}

// reversed virtual functions
CTask* CTaskSimplePickUpEntity::Clone_Reversed() {
    if (m_pAnimBlendHierarchy) {
        return new CTaskSimplePickUpEntity(
            m_pEntityToHold,
            &m_vecPosition,
            m_bBoneFrameId,
            m_bBoneFlags,
            m_pAnimBlock, 
            m_pAnimBlendHierarchy,
            m_animFlags,
            m_fMovePedUntilAnimProgress
        );
    }
    else {
        return new CTaskSimplePickUpEntity(
            m_pEntityToHold,
            &m_vecPosition,
            m_bBoneFrameId,
            m_bBoneFlags,
            m_nAnimId,
            m_nAnimGroupId, 
            m_fMovePedUntilAnimProgress
        );
    }
}
