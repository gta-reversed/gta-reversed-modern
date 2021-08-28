#include "StdInc.h"

void CTaskSimplePickUpEntity::InjectHooks() {
    ReversibleHooks::Install(0x691870, (CTaskSimplePickUpEntity*(CTaskSimplePickUpEntity::*)(CEntity*, CVector*, char, unsigned char, CAnimBlock*, CAnimBlendHierarchy*, int, float)) & CTaskSimplePickUpEntity::Constructor);
    ReversibleHooks::Install(0x6917B0, (CTaskSimplePickUpEntity * (CTaskSimplePickUpEntity::*)(CEntity*, CVector*, char, unsigned char, int, int, float)) & CTaskSimplePickUpEntity::Constructor);
    ReversibleHooks::Install(0x692A90, &CTaskSimplePickUpEntity::Clone_Reversed);
    ReversibleHooks::Install(0x691810, &CTaskSimplePickUpEntity::GetId_Reversed);
}

CTaskSimplePickUpEntity::CTaskSimplePickUpEntity(CEntity* pEntityToHold, CVector* pPosition, char boneFrameId, unsigned char boneFlags,
    CAnimBlock* pAnimBlock, CAnimBlendHierarchy* pAnimHierarchy, int animFlags, float fMovePedUntilAnimProgress) : CTaskSimpleHoldEntity(pEntityToHold, pPosition, boneFrameId, boneFlags, pAnimBlock, pAnimHierarchy, animFlags) {
    m_fMovePedUntilAnimProgress = fMovePedUntilAnimProgress;
} 

CTaskSimplePickUpEntity::CTaskSimplePickUpEntity(CEntity* pEntityToHold, CVector* pPosition, char boneFrameId, unsigned char boneFlags,
    int animId, int groupId, float fMovePedUntilAnimProgress) : CTaskSimpleHoldEntity(pEntityToHold, pPosition, boneFrameId, boneFlags, animId, groupId, false) {
    m_fMovePedUntilAnimProgress = fMovePedUntilAnimProgress;
} 

CTaskSimplePickUpEntity::~CTaskSimplePickUpEntity() {
    // nothing here
}

CTaskSimplePickUpEntity* CTaskSimplePickUpEntity::Constructor(CEntity* pEntityToHold, CVector* pPosition, char boneFrameId, unsigned char boneFlags,
    CAnimBlock* pAnimBlock, CAnimBlendHierarchy* pAnimHierarchy, int animFlags, float fMovePedUntilAnimProgress) {
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CTaskSimplePickUpEntity*, 0x691870, CTask*, CEntity*, CVector*, char, unsigned char, CAnimBlock*, CAnimBlendHierarchy *, int, float>
        (this, pEntityToHold, pPosition, boneFrameId, boneFlags, pAnimBlock, pAnimHierarchy, animFlags, fMovePedUntilAnimProgress);
#else
    this->CTaskSimplePickUpEntity::CTaskSimplePickUpEntity(pEntityToHold, pPosition, boneFrameId, boneFlags, pAnimBlock, pAnimHierarchy, animFlags, fMovePedUntilAnimProgress);
    return this;
#endif
}

CTaskSimplePickUpEntity* CTaskSimplePickUpEntity::Constructor(CEntity* pEntityToHold, CVector* pPosition, char boneFrameId, unsigned char boneFlags,
    int animId, int groupId, float fMovePedUntilAnimProgress){
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CTaskSimplePickUpEntity*, 0x6917B0, CTask*, CEntity*, CVector*, char, unsigned char, int, int, float>
        (this, pEntityToHold, pPosition, boneFrameId, boneFlags, animId, groupId, fMovePedUntilAnimProgress);
#else
    this->CTaskSimplePickUpEntity::CTaskSimplePickUpEntity(pEntityToHold, pPosition, boneFrameId, boneFlags, animId, groupId, fMovePedUntilAnimProgress);
    return this;
#endif
}

CTask* CTaskSimplePickUpEntity::Clone() {
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CTaskSimpleHoldEntity*, 0x692A90, CTaskSimpleHoldEntity*>(this);
#else
    return CTaskSimplePickUpEntity::Clone_Reversed();
#endif
}

eTaskType CTaskSimplePickUpEntity::GetId() {
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<eTaskType, 0x691810, CTaskSimpleHoldEntity*>(this);
#else
    return CTaskSimplePickUpEntity::GetId_Reversed();
#endif
}

// reversed virtual functions
CTask* CTaskSimplePickUpEntity::Clone_Reversed() {
    if (m_pAnimBlendHierarchy) {
        return new CTaskSimplePickUpEntity(m_pEntityToHold, &m_vecPosition, m_bBoneFrameId, m_bBoneFlags, m_pAnimBlock, 
            m_pAnimBlendHierarchy, m_animFlags, m_fMovePedUntilAnimProgress);
    }
    else {
        return new CTaskSimplePickUpEntity(m_pEntityToHold, &m_vecPosition, m_bBoneFrameId, m_bBoneFlags, m_nAnimId, m_nAnimGroupId, 
            m_fMovePedUntilAnimProgress);
    }
    return nullptr;
}
