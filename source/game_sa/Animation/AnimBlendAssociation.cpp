#include "StdInc.h"

#include "AnimBlendAssociation.h"

void CAnimBlendAssociation::InjectHooks() {
    RH_ScopedClass(CAnimBlendAssociation);
    RH_ScopedCategory("Animation");

    RH_ScopedOverloadedInstall(Constructor0, "", 0x4CE9B0, CAnimBlendAssociation*(CAnimBlendAssociation::*)());
    RH_ScopedOverloadedInstall(Constructor1, "clump_hier", 0x4CEFC0, CAnimBlendAssociation*(CAnimBlendAssociation::*)(RpClump*, CAnimBlendHierarchy*));
    RH_ScopedOverloadedInstall(Constructor2, "blend", 0x4CF020, CAnimBlendAssociation*(CAnimBlendAssociation::*)(CAnimBlendAssociation&));
    RH_ScopedOverloadedInstall(Constructor3, "static_blend", 0x4CF080, CAnimBlendAssociation*(CAnimBlendAssociation::*)(CAnimBlendStaticAssociation&));

    RH_ScopedOverloadedInstall(Init, "0", 0x4CED50, void(CAnimBlendAssociation::*)(RpClump*, CAnimBlendHierarchy*));
    RH_ScopedOverloadedInstall(Init, "1", 0x4CEE40, void(CAnimBlendAssociation::*)(CAnimBlendAssociation&));
    RH_ScopedOverloadedInstall(Init, "2", 0x4CEEC0, void(CAnimBlendAssociation::*)(CAnimBlendStaticAssociation&));
    RH_ScopedInstall(Start, 0x4CEB70);
    RH_ScopedInstall(AllocateAnimBlendNodeArray, 0x4CE9F0);
    RH_ScopedInstall(FreeAnimBlendNodeArray, 0x4CEA40);
    RH_ScopedInstall(SetBlend, 0x4CEBA0);
    RH_ScopedInstall(SetBlendTo, 0x4CEB80);
    RH_ScopedInstall(SetCurrentTime, 0x4CEA80);
    RH_ScopedInstall(SetDeleteCallback, 0x4CEBC0);
    RH_ScopedInstall(SetFinishCallback, 0x4CEBE0);
    RH_ScopedInstall(SyncAnimation, 0x4CEB40);
    RH_ScopedInstall(UpdateBlend, 0x4D1490);
    RH_ScopedInstall(UpdateTime, 0x4D13D0);
    RH_ScopedInstall(UpdateTimeStep, 0x4D13A0);
    RH_ScopedInstall(ReferenceAnimBlock, 0x4CEA50);
}

// 0x4CE9B0
CAnimBlendAssociation::CAnimBlendAssociation() {
    m_nAnimGroup = -1;
    m_pNodeArray = nullptr;
    m_pHierarchy = nullptr;
    m_fBlendAmount = 1.0f;
    m_fBlendDelta = 0.0f;
    m_fCurrentTime = 0.0f;
    m_fSpeed = 1.0f;
    m_fTimeStep = 0.0f;
    m_nAnimId = -1;
    m_nFlags = 0;
    m_nCallbackType = ANIM_BLEND_CALLBACK_NONE;
    // NOTSA
    m_pCallbackFunc = nullptr;
    m_pCallbackData = nullptr;
}

// 0x4CEFC0
CAnimBlendAssociation::CAnimBlendAssociation(RpClump* clump, CAnimBlendHierarchy* animHierarchy) : CAnimBlendAssociation() {
    Init(clump, animHierarchy);
}

// 0x4CF020
CAnimBlendAssociation::CAnimBlendAssociation(CAnimBlendAssociation& assoc) {
    m_pNodeArray = nullptr;
    m_fBlendAmount = 1.0f;
    m_fBlendDelta = 0.0f;
    m_fCurrentTime = 0.0f;
    m_fSpeed = 1.0f;
    m_fTimeStep = 0.0f;
    m_nCallbackType = ANIM_BLEND_CALLBACK_NONE;
    Init(assoc);
    if ((m_nFlags & ANIMATION_BLOCK_REFERENCED) == 0) {
        CAnimManager::AddAnimBlockRef(m_pHierarchy->m_nAnimBlockId);
        m_nFlags |= ANIMATION_BLOCK_REFERENCED;
    }
}

// 0x4CF080
CAnimBlendAssociation::CAnimBlendAssociation(CAnimBlendStaticAssociation& assoc) {
    m_pNodeArray = nullptr;
    m_fBlendAmount = 1.0f;
    m_fBlendDelta = 0.0f;
    m_fCurrentTime = 0.0f;
    m_fSpeed = 1.0f;
    m_fTimeStep = 0.0f;
    m_nCallbackType = ANIM_BLEND_CALLBACK_NONE;
    Init(assoc);
    if ((m_nFlags & ANIMATION_BLOCK_REFERENCED) == 0) {
        CAnimManager::AddAnimBlockRef(m_pHierarchy->m_nAnimBlockId);
        m_nFlags |= ANIMATION_BLOCK_REFERENCED;
    }
}

// 0x4CECF0
CAnimBlendAssociation::~CAnimBlendAssociation() {
    if (m_pNodeArray) {
        CMemoryMgr::FreeAlign(m_pNodeArray);
    }
    m_Link.Remove();
    if (m_nFlags & ANIMATION_BLOCK_REFERENCED) {
        CAnimManager::RemoveAnimBlockRef(m_pHierarchy->m_nAnimBlockId);
    }
}

// 0x4CED50
void CAnimBlendAssociation::Init(RpClump* clump, CAnimBlendHierarchy* animHierarchy) {
    CAnimBlendClumpData* animClumpData = RpClumpGetAnimBlendClumpData(clump);
    m_nNumBlendNodes = animClumpData->m_NumFrames;
    AllocateAnimBlendNodeArray(m_nNumBlendNodes);
    for (auto i = 0; i < m_nNumBlendNodes; i++) {
        m_pNodeArray[i].m_pAnimBlendAssociation = this;
    }

    m_pHierarchy = animHierarchy;
    for (auto& sequence : m_pHierarchy->GetSequences()) {
        AnimBlendFrameData* frame = nullptr;
        if (sequence.m_hasBoneIdSet) {
            frame = RpAnimBlendClumpFindBone(clump, sequence.m_boneId);
        } else {
            frame = RpAnimBlendClumpFindFrameFromHashKey(clump, sequence.m_hash);
        }
        if (frame && sequence.m_nFrameCount > 0) {
            m_pNodeArray[frame - animClumpData->m_Frames].m_pAnimSequence = &sequence;
        }
    }
}

// 0x4CEE40
void CAnimBlendAssociation::Init(CAnimBlendAssociation& assoc) {
    m_pHierarchy     = assoc.m_pHierarchy;
    m_nNumBlendNodes = assoc.m_nNumBlendNodes;
    m_nFlags         = assoc.m_nFlags;
    m_nAnimId        = assoc.m_nAnimId;
    m_nAnimGroup     = assoc.m_nAnimGroup;
    AllocateAnimBlendNodeArray(m_nNumBlendNodes);
    for (auto i = 0; i < m_nNumBlendNodes; i++) {
        m_pNodeArray[i] = assoc.m_pNodeArray[i];
        m_pNodeArray[i].m_pAnimBlendAssociation = this;
    }
}

// 0x4CEEC0
void CAnimBlendAssociation::Init(CAnimBlendStaticAssociation& assoc) {
    m_pHierarchy     = assoc.m_pHierarchy;
    m_nNumBlendNodes = assoc.m_nNumBlendNodes;
    m_nFlags         = assoc.m_nFlags;
    m_nAnimId        = assoc.m_nAnimId;
    m_nAnimGroup     = assoc.m_nAnimGroup;
    AllocateAnimBlendNodeArray(m_nNumBlendNodes);
    for (auto i = 0; i < m_nNumBlendNodes; i++) {
        m_pNodeArray[i].m_pAnimSequence = assoc.m_pSequenceArray[i];
        m_pNodeArray[i].m_pAnimBlendAssociation = this;
    }
}

// 0x4CEB70
void CAnimBlendAssociation::Start(float currentTime) {
    m_nFlags |= ANIMATION_STARTED;
    SetCurrentTime(currentTime);
}

uint32 CAnimBlendAssociation::GetHashKey() const noexcept {
    return m_pHierarchy->m_hashKey;
}

// 0x4CE9F0
void CAnimBlendAssociation::AllocateAnimBlendNodeArray(int32 count) {
    m_pNodeArray = (CAnimBlendNode*)CMemoryMgr::MallocAlign(count * sizeof(CAnimBlendNode), 64);
    for (auto& node : std::span{ m_pNodeArray, (size_t)count }) {
        node.Init();
    }
}

// 0x4CEA40
void CAnimBlendAssociation::FreeAnimBlendNodeArray() {
    if (m_pNodeArray) {
        CMemoryMgr::FreeAlign(m_pNodeArray);
    }
}

// 0x4CEBA0
void CAnimBlendAssociation::SetBlend(float blendAmount, float blendDelta) {
    m_fBlendAmount = blendAmount;
    m_fBlendDelta  = blendDelta;
}

// 0x4CEB80
void CAnimBlendAssociation::SetBlendTo(float blendAmount, float blendDelta) {
    m_fBlendDelta = (blendAmount - m_fBlendAmount) * blendDelta;
}

// 0x4CEA80
void CAnimBlendAssociation::SetCurrentTime(float currentTime) {
    for (m_fCurrentTime = currentTime; m_fCurrentTime >= m_pHierarchy->m_fTotalTime; m_fCurrentTime -= m_pHierarchy->m_fTotalTime) {
        if (!IsRepeating()) {
            m_fCurrentTime = m_pHierarchy->m_fTotalTime;
            break;
        }
    }

    CAnimManager::UncompressAnimation(m_pHierarchy);

    // ANIM_COMPRESSION strangely PC has this but android doesn't
    if (m_pHierarchy->m_bKeepCompressed) {
        for (auto i = 0; i < m_nNumBlendNodes; i++) {
            if (m_pNodeArray[i].m_pAnimSequence) {
                m_pNodeArray[i].SetupKeyFrameCompressed();
            }
        }
    } else {
        for (auto i = 0; i < m_nNumBlendNodes; i++) {
            if (m_pNodeArray[i].m_pAnimSequence) {
                m_pNodeArray[i].FindKeyFrame(m_fCurrentTime);
            }
        }
    }
}

// 0x4CEBC0
void CAnimBlendAssociation::SetDeleteCallback(void (*callback)(CAnimBlendAssociation*, void*), void* data) {
    m_nCallbackType = ANIM_BLEND_CALLBACK_DELETE;
    m_pCallbackFunc = callback;
    m_pCallbackData = data;
}

// 0x4CEBE0
void CAnimBlendAssociation::SetFinishCallback(void (*callback)(CAnimBlendAssociation*, void*), void* data) {
    m_nCallbackType = ANIM_BLEND_CALLBACK_FINISH;
    m_pCallbackFunc = callback;
    m_pCallbackData = data;
}

// 0x4CEB40
void CAnimBlendAssociation::SyncAnimation(CAnimBlendAssociation* syncWith) {
    const auto progress = syncWith->m_fCurrentTime / syncWith->m_pHierarchy->m_fTotalTime * m_pHierarchy->m_fTotalTime;
    SetCurrentTime(progress);
}

// 0x4D1490
bool CAnimBlendAssociation::UpdateBlend(float mult) {
    m_fBlendAmount += mult * m_fBlendDelta;
    if (m_fBlendAmount <= 0.0f && m_fBlendDelta < 0.0f) {
        // We're faded out and are not fading in
        m_fBlendAmount = 0.0f;
        m_fBlendDelta = std::max(0.0f, m_fBlendDelta);
        if (m_nFlags & ANIMATION_FREEZE_LAST_FRAME) {
            if (m_nCallbackType == ANIM_BLEND_CALLBACK_DELETE || m_nCallbackType == ANIM_BLEND_CALLBACK_FINISH) { // condition simplified
                m_pCallbackFunc(this, m_pCallbackData);
                SetFinishCallback(CDefaultAnimCallback::DefaultAnimCB, nullptr);
            }
            delete this;
            return false;
        }
    }

    if (m_fBlendAmount > 1.0f) {
        // Maximally faded in, clamp values
        m_fBlendAmount = 1.0f;
        m_fBlendDelta = std::min(0.0f, m_fBlendDelta);
    }

    return true;
}

// 0x4D13D0
bool CAnimBlendAssociation::UpdateTime(float a1, float a2) {
    UNUSED(a1);
    UNUSED(a2);

    if (!IsRunning())
        return true;

    if (m_fCurrentTime >= (double)m_pHierarchy->m_fTotalTime) {
        SetFlag(ANIMATION_STARTED, true);
        return true;
    }

    m_fCurrentTime += m_fTimeStep;
    if (m_fCurrentTime < m_pHierarchy->m_fTotalTime) {
        return true;
    }

    if (IsRepeating()) {
        m_fCurrentTime -= m_pHierarchy->m_fTotalTime;
        return true;
    }

    m_fCurrentTime = m_pHierarchy->m_fTotalTime;
    if (m_nFlags & ANIMATION_UNLOCK_LAST_FRAME) {
        SetFlag(ANIMATION_FREEZE_LAST_FRAME, true);
        m_fBlendDelta = -4.0f;
    }

    if (m_nCallbackType == ANIM_BLEND_CALLBACK_FINISH) {
        m_nCallbackType = ANIM_BLEND_CALLBACK_NONE;
        m_pCallbackFunc(this, m_pCallbackData);
        SetFinishCallback(CDefaultAnimCallback::DefaultAnimCB, nullptr);
    }
    return true;
}

// 0x4D13A0
void CAnimBlendAssociation::UpdateTimeStep(float speedMult, float timeMult) {
    if (IsRunning()) {
        if (IsMoving()) {
            m_fTimeStep = m_pHierarchy->m_fTotalTime * timeMult * speedMult;
        } else {
            m_fTimeStep = m_fSpeed * speedMult;
        }
    }
}

// 0x4CEA50
void CAnimBlendAssociation::ReferenceAnimBlock() {
    if (m_nFlags & ANIMATION_BLOCK_REFERENCED) {
        return;
    }
    CAnimManager::AddAnimBlockRef(m_pHierarchy->m_nAnimBlockId);
    SetFlag(ANIMATION_FREEZE_TRANSLATION, true);
}

// 0x4CEB60
CAnimBlendNode* CAnimBlendAssociation::GetNode(int32 nodeIndex) {
    return &m_pNodeArray[nodeIndex];
}

float SClumpAnimAssoc::GetTimeProgress() const {
    return m_fCurrentTime / m_pHierarchy->m_fTotalTime;
}
