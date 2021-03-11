#include "StdInc.h"


void CTaskSimplePutDownEntity::InjectHooks() {
    HookInstall(0x691990, &CTaskSimplePutDownEntity::Constructor);
    HookInstall(0x692B70, &CTaskSimplePutDownEntity::Clone_Reversed);
    HookInstall(0x691900, &CTaskSimplePutDownEntity::GetId_Reversed);
}

CTaskSimplePutDownEntity::CTaskSimplePutDownEntity() : CTaskSimpleHoldEntity(nullptr, nullptr, PED_NODE_RIGHT_HAND, HOLD_ENTITY_FLAG_1, ANIM_ID_NO_ANIMATION_SET, 0, false) {
    m_fPutDownHeightZ = 0.6f;
}

CTaskSimplePutDownEntity::CTaskSimplePutDownEntity(CEntity* pEntityToHold, CVector* pPosition, char boneFrameId, unsigned char boneFlags,
    int animId, int groupId, bool bDisAllowDroppingOnAnimEnd, float fPutDownHeightZ) : CTaskSimpleHoldEntity(pEntityToHold, pPosition, boneFrameId, boneFlags, animId, groupId, bDisAllowDroppingOnAnimEnd) {
    m_fPutDownHeightZ = fPutDownHeightZ;
}

CTaskSimplePutDownEntity::CTaskSimplePutDownEntity(CEntity* pEntityToHold, CVector* pPosition, char boneFrameId, unsigned char boneFlags,
    char* pAnimName, char* pAnimBlockName, int animFlags, float fPutDownHeightZ) : CTaskSimpleHoldEntity(pEntityToHold, pPosition, boneFrameId, boneFlags, pAnimName, pAnimBlockName, animFlags) {
    m_fPutDownHeightZ = fPutDownHeightZ;
}

CTaskSimplePutDownEntity::CTaskSimplePutDownEntity(CEntity* pEntityToHold, CVector* pPosition, char boneFrameId, unsigned char boneFlags,
    CAnimBlock* pAnimBlock, CAnimBlendHierarchy* pAnimHierarchy, int animFlags, float fPutDownHeightZ) : CTaskSimpleHoldEntity(pEntityToHold, pPosition, boneFrameId, boneFlags, pAnimBlock, pAnimHierarchy, animFlags) {
    m_fPutDownHeightZ = fPutDownHeightZ;
}

CTaskSimplePutDownEntity::~CTaskSimplePutDownEntity() {
    // nothing here
}

CTaskSimplePutDownEntity* CTaskSimplePutDownEntity::Constructor() {
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CTaskSimplePutDownEntity*, 0x691990, CTaskSimplePutDownEntity*>(this);
#else
    this->CTaskSimplePutDownEntity::CTaskSimplePutDownEntity();
    return this;
#endif
}

CTask* CTaskSimplePutDownEntity::Clone() {
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CTask*, 0x692B70, CTask*>(this);
#else
    return CTaskSimplePutDownEntity::Clone_Reversed();
#endif
}

eTaskType CTaskSimplePutDownEntity::GetId() {
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn <eTaskType, 0x691900, CTask*>(this);
#else
    return CTaskSimplePutDownEntity::GetId_Reversed();
#endif
}

CTask* CTaskSimplePutDownEntity::Clone_Reversed() {
    if (m_pAnimBlendHierarchy) {
        return new CTaskSimplePutDownEntity(m_pEntityToHold, &m_vecPosition, m_bBoneFrameId, m_bBoneFlags, m_pAnimBlock, 
            m_pAnimBlendHierarchy, m_animFlags, m_fPutDownHeightZ);
    }
    else {
        return new CTaskSimplePutDownEntity(m_pEntityToHold, &m_vecPosition, m_bBoneFrameId, m_bBoneFlags, m_nAnimId, m_nAnimGroupId, 
            false, m_fPutDownHeightZ);
    }
    return nullptr;
}

