#include "StdInc.h"

#include "CTaskSimplePutDownEntity.h"

void CTaskSimplePutDownEntity::InjectHooks() {
    ReversibleHooks::Install("CTaskSimplePutDownEntity", "CTaskSimplePutDownEntity", 0x691990, &CTaskSimplePutDownEntity::Constructor);
    ReversibleHooks::Install("CTaskSimplePutDownEntity", "Clone", 0x692B70, &CTaskSimplePutDownEntity::Clone_Reversed);
    ReversibleHooks::Install("CTaskSimplePutDownEntity", "GetId", 0x691900, &CTaskSimplePutDownEntity::GetId_Reversed);
}

CTaskSimplePutDownEntity::CTaskSimplePutDownEntity() : CTaskSimpleHoldEntity(nullptr, nullptr, PED_NODE_RIGHT_HAND, HOLD_ENTITY_FLAG_1, ANIM_ID_NO_ANIMATION_SET, ANIM_GROUP_DEFAULT, false) {
    m_fPutDownHeightZ = 0.6f;
}

CTaskSimplePutDownEntity::CTaskSimplePutDownEntity(CEntity* pEntityToHold, CVector* pPosition, char boneFrameId, unsigned char boneFlags, AnimationId animId, AssocGroupId groupId, bool bDisAllowDroppingOnAnimEnd, float fPutDownHeightZ) : CTaskSimpleHoldEntity(pEntityToHold, pPosition, boneFrameId, boneFlags, animId, groupId, bDisAllowDroppingOnAnimEnd) {
    m_fPutDownHeightZ = fPutDownHeightZ;
}

CTaskSimplePutDownEntity::CTaskSimplePutDownEntity(CEntity* pEntityToHold, CVector* pPosition, char boneFrameId, unsigned char boneFlags, char* pAnimName, char* pAnimBlockName, int animFlags, float fPutDownHeightZ) : CTaskSimpleHoldEntity(pEntityToHold, pPosition, boneFrameId, boneFlags, pAnimName, pAnimBlockName, animFlags) {
    m_fPutDownHeightZ = fPutDownHeightZ;
}

CTaskSimplePutDownEntity::CTaskSimplePutDownEntity(CEntity* pEntityToHold, CVector* pPosition, char boneFrameId, unsigned char boneFlags, CAnimBlock* pAnimBlock, CAnimBlendHierarchy* pAnimHierarchy, int animFlags, float fPutDownHeightZ) : CTaskSimpleHoldEntity(pEntityToHold, pPosition, boneFrameId, boneFlags, pAnimBlock, pAnimHierarchy, animFlags) {
    m_fPutDownHeightZ = fPutDownHeightZ;
}

CTaskSimplePutDownEntity::~CTaskSimplePutDownEntity() {
    // nothing here
}

// 0x691990
CTaskSimplePutDownEntity* CTaskSimplePutDownEntity::Constructor() {
    this->CTaskSimplePutDownEntity::CTaskSimplePutDownEntity();
    return this;
}

// 0x692B70
CTask* CTaskSimplePutDownEntity::Clone() {
    return CTaskSimplePutDownEntity::Clone_Reversed();
}

// 0x691900
eTaskType CTaskSimplePutDownEntity::GetId() {
    return CTaskSimplePutDownEntity::GetId_Reversed();
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

