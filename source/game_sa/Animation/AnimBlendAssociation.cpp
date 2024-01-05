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
    m_AnimGroupId = ANIM_GROUP_NONE;
    m_BlendNodes = nullptr;
    m_BlendHier = nullptr;
    m_BlendAmount = 1.0f;
    m_BlendDelta = 0.0f;
    m_CurrentTime = 0.0f;
    m_Speed = 1.0f;
    m_TimeStep = 0.0f;
    m_AnimId = ANIM_ID_UNDEFINED;
    m_Flags = 0;
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
    m_BlendNodes = nullptr;
    m_BlendAmount = 1.0f;
    m_BlendDelta = 0.0f;
    m_CurrentTime = 0.0f;
    m_Speed = 1.0f;
    m_TimeStep = 0.0f;
    m_nCallbackType = ANIM_BLEND_CALLBACK_NONE;
    Init(assoc);
    if ((m_Flags & ANIMATION_BLOCK_REFERENCED) == 0) {
        CAnimManager::AddAnimBlockRef(m_BlendHier->m_nAnimBlockId);
        m_Flags |= ANIMATION_BLOCK_REFERENCED;
    }
}

// 0x4CF080
CAnimBlendAssociation::CAnimBlendAssociation(CAnimBlendStaticAssociation& assoc) {
    m_BlendNodes = nullptr;
    m_BlendAmount = 1.0f;
    m_BlendDelta = 0.0f;
    m_CurrentTime = 0.0f;
    m_Speed = 1.0f;
    m_TimeStep = 0.0f;
    m_nCallbackType = ANIM_BLEND_CALLBACK_NONE;
    Init(assoc);
    if ((m_Flags & ANIMATION_BLOCK_REFERENCED) == 0) {
        CAnimManager::AddAnimBlockRef(m_BlendHier->m_nAnimBlockId);
        m_Flags |= ANIMATION_BLOCK_REFERENCED;
    }
}

// 0x4CECF0
CAnimBlendAssociation::~CAnimBlendAssociation() {
    if (m_BlendNodes) {
        CMemoryMgr::FreeAlign(m_BlendNodes);
    }
    m_Link.Remove();
    if (m_Flags & ANIMATION_BLOCK_REFERENCED) {
        CAnimManager::RemoveAnimBlockRef(m_BlendHier->m_nAnimBlockId);
    }
}

// 0x4CED50
void CAnimBlendAssociation::Init(RpClump* clump, CAnimBlendHierarchy* animHierarchy) {
    CAnimBlendClumpData* animClumpData = RpClumpGetAnimBlendClumpData(clump);
    m_NumBlendNodes = animClumpData->m_NumFrames;
    AllocateAnimBlendNodeArray(m_NumBlendNodes);
    for (auto i = 0; i < m_NumBlendNodes; i++) {
        m_BlendNodes[i].m_BlendAssoc = this;
    }

    m_BlendHier = animHierarchy;
    for (auto& sequence : m_BlendHier->GetSequences()) {
        AnimBlendFrameData* frame = nullptr;
        if (sequence.m_bUsingBones) {
            frame = RpAnimBlendClumpFindBone(clump, sequence.m_BoneID);
        } else {
            frame = RpAnimBlendClumpFindFrameFromHashKey(clump, sequence.m_FrameHashKey);
        }
        if (frame && sequence.m_FramesNum > 0) {
            m_BlendNodes[frame - animClumpData->m_Frames].m_BlendSeq = &sequence;
        }
    }
}

// 0x4CEE40
void CAnimBlendAssociation::Init(CAnimBlendAssociation& assoc) {
    m_BlendHier     = assoc.m_BlendHier;
    m_NumBlendNodes = assoc.m_NumBlendNodes;
    m_Flags         = assoc.m_Flags;
    m_AnimId        = assoc.m_AnimId;
    m_AnimGroupId     = assoc.m_AnimGroupId;
    AllocateAnimBlendNodeArray(m_NumBlendNodes);
    for (auto i = 0; i < m_NumBlendNodes; i++) {
        m_BlendNodes[i] = assoc.m_BlendNodes[i];
        m_BlendNodes[i].m_BlendAssoc = this;
    }
}

// 0x4CEEC0
void CAnimBlendAssociation::Init(CAnimBlendStaticAssociation& assoc) {
    m_BlendHier     = assoc.m_BlendHier;
    m_NumBlendNodes = assoc.m_NumBlendNodes;
    m_Flags         = assoc.m_Flags;
    m_AnimId        = assoc.m_AnimId;
    m_AnimGroupId    = assoc.m_AnimGroupId;
    AllocateAnimBlendNodeArray(m_NumBlendNodes);
    for (auto i = 0; i < m_NumBlendNodes; i++) {
        m_BlendNodes[i].m_BlendSeq = assoc.m_BlendSeqs[i];
        m_BlendNodes[i].m_BlendAssoc = this;
    }
}

// 0x4CEB70
void CAnimBlendAssociation::Start(float currentTime) {
    m_Flags |= ANIMATION_STARTED;
    SetCurrentTime(currentTime);
}

uint32 CAnimBlendAssociation::GetHashKey() const noexcept {
    return m_BlendHier->m_hashKey;
}

// 0x4CE9F0
void CAnimBlendAssociation::AllocateAnimBlendNodeArray(int32 count) {
    m_BlendNodes = (CAnimBlendNode*)CMemoryMgr::MallocAlign(count * sizeof(CAnimBlendNode), 64);
    for (auto& node : std::span{ m_BlendNodes, (size_t)count }) {
        node.Init();
    }
}

// 0x4CEA40
void CAnimBlendAssociation::FreeAnimBlendNodeArray() {
    if (m_BlendNodes) {
        CMemoryMgr::FreeAlign(m_BlendNodes);
    }
}

// 0x4CEBA0
void CAnimBlendAssociation::SetBlend(float blendAmount, float blendDelta) {
    m_BlendAmount = blendAmount;
    m_BlendDelta  = blendDelta;
}

// 0x4CEB80
void CAnimBlendAssociation::SetBlendTo(float blendAmount, float blendDelta) {
    m_BlendDelta = (blendAmount - m_BlendAmount) * blendDelta;
}

// 0x4CEA80
void CAnimBlendAssociation::SetCurrentTime(float currentTime) {
    for (m_CurrentTime = currentTime; m_CurrentTime >= m_BlendHier->m_fTotalTime; m_CurrentTime -= m_BlendHier->m_fTotalTime) {
        if (!IsRepeating()) {
            m_CurrentTime = m_BlendHier->m_fTotalTime;
            break;
        }
    }

    CAnimManager::UncompressAnimation(m_BlendHier);

    // ANIM_COMPRESSION strangely PC has this but android doesn't
    if (m_BlendHier->m_bKeepCompressed) {
        for (auto i = 0; i < m_NumBlendNodes; i++) {
            if (m_BlendNodes[i].m_BlendSeq) {
                m_BlendNodes[i].SetupKeyFrameCompressed();
            }
        }
    } else {
        for (auto i = 0; i < m_NumBlendNodes; i++) {
            if (m_BlendNodes[i].m_BlendSeq) {
                m_BlendNodes[i].FindKeyFrame(m_CurrentTime);
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
    const auto progress = syncWith->m_CurrentTime / syncWith->m_BlendHier->m_fTotalTime * m_BlendHier->m_fTotalTime;
    SetCurrentTime(progress);
}

// 0x4D1490
bool CAnimBlendAssociation::UpdateBlend(float mult) {
    m_BlendAmount += mult * m_BlendDelta;
    if (m_BlendAmount <= 0.0f && m_BlendDelta < 0.0f) {
        // We're faded out and are not fading in
        m_BlendAmount = 0.0f;
        m_BlendDelta = std::max(0.0f, m_BlendDelta);
        if (m_Flags & ANIMATION_FREEZE_LAST_FRAME) {
            if (m_nCallbackType == ANIM_BLEND_CALLBACK_DELETE || m_nCallbackType == ANIM_BLEND_CALLBACK_FINISH) { // condition simplified
                m_pCallbackFunc(this, m_pCallbackData);
                SetFinishCallback(CDefaultAnimCallback::DefaultAnimCB, nullptr);
            }
            delete this;
            return false;
        }
    }

    if (m_BlendAmount > 1.0f) {
        // Maximally faded in, clamp values
        m_BlendAmount = 1.0f;
        m_BlendDelta = std::min(0.0f, m_BlendDelta);
    }

    return true;
}

// 0x4D13D0
bool CAnimBlendAssociation::UpdateTime(float a1, float a2) {
    UNUSED(a1);
    UNUSED(a2);

    if (!IsRunning())
        return true;

    if (m_CurrentTime >= (double)m_BlendHier->m_fTotalTime) {
        SetFlag(ANIMATION_STARTED, true);
        return true;
    }

    m_CurrentTime += m_TimeStep;
    if (m_CurrentTime < m_BlendHier->m_fTotalTime) {
        return true;
    }

    if (IsRepeating()) {
        m_CurrentTime -= m_BlendHier->m_fTotalTime;
        return true;
    }

    m_CurrentTime = m_BlendHier->m_fTotalTime;
    if (m_Flags & ANIMATION_UNLOCK_LAST_FRAME) {
        SetFlag(ANIMATION_FREEZE_LAST_FRAME, true);
        m_BlendDelta = -4.0f;
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
            m_TimeStep = m_BlendHier->m_fTotalTime * timeMult * speedMult;
        } else {
            m_TimeStep = m_Speed * speedMult;
        }
    }
}

// 0x4CEA50
void CAnimBlendAssociation::ReferenceAnimBlock() {
    if (m_Flags & ANIMATION_BLOCK_REFERENCED) {
        return;
    }
    CAnimManager::AddAnimBlockRef(m_BlendHier->m_nAnimBlockId);
    SetFlag(ANIMATION_FREEZE_TRANSLATION, true);
}

// 0x4CEB60
CAnimBlendNode* CAnimBlendAssociation::GetNode(int32 nodeIndex) {
    return &m_BlendNodes[nodeIndex];
}

float SClumpAnimAssoc::GetTimeProgress() const {
    return m_CurrentTime / m_BlendHier->m_fTotalTime;
}
