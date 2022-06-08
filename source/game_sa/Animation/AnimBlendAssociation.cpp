#include "StdInc.h"

#include "AnimBlendAssociation.h"

void CAnimBlendAssociation::InjectHooks() {
    RH_ScopedClass(CAnimBlendAssociation);
    RH_ScopedCategory("Animation");

    RH_ScopedInstall(Constructor, 0x4CEFC0);
}

// 0x82119A
void* CAnimBlendAssociation::operator new(unsigned size) {
    return ((CAnimBlendAssociation * (__cdecl*)(uint32))0x82119A)(size);
}

// 0x8214BD
void CAnimBlendAssociation::operator delete(void* object) {
    ((void(__cdecl*)(void*))0x8214BD)(object);
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
    m_nCallbackType = ANIMBLENDCALLBACK_NONE;
    m_pNext = nullptr;
    m_pPrevious = nullptr;
}

// 0x4CEFC0
CAnimBlendAssociation::CAnimBlendAssociation(RpClump* clump, CAnimBlendHierarchy* animHierarchy) {
    CAnimBlendAssociation();
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
    m_nCallbackType = ANIMBLENDCALLBACK_NONE;
    m_pNext = nullptr;
    m_pPrevious = nullptr;
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
    m_nCallbackType = ANIMBLENDCALLBACK_NONE;
    m_pNext = nullptr;
    m_pPrevious = nullptr;
    Init(assoc);
    if ((m_nFlags & ANIMATION_BLOCK_REFERENCED) == 0) {
        CAnimManager::AddAnimBlockRef(m_pHierarchy->m_nAnimBlockId);
        m_nFlags |= ANIMATION_BLOCK_REFERENCED;
    }
}

// 0x4CECF0
CAnimBlendAssociation::~CAnimBlendAssociation() {
    if (m_pNodeArray)
        CMemoryMgr::FreeAlign(m_pNodeArray);
    if (m_pPrevious)
        m_pPrevious->m_pNext = m_pNext;
    if (m_pNext)
        m_pNext->m_pPrevious = m_pPrevious;
    m_pNext = nullptr;
    m_pPrevious = nullptr;
    if (m_nFlags & ANIMATION_BLOCK_REFERENCED) {
        CAnimManager::RemoveAnimBlockRef(m_pHierarchy->m_nAnimBlockId);
    }
}

CAnimBlendAssociation* CAnimBlendAssociation::Constructor(RpClump* clump, CAnimBlendHierarchy* animHierarchy) {
    this->CAnimBlendAssociation::CAnimBlendAssociation(clump, animHierarchy);
    return this;
}

// 0x4CED50
void CAnimBlendAssociation::Init(RpClump* clump, CAnimBlendHierarchy* animHierarchy) {
    return plugin::CallMethod<0x4CED50, CAnimBlendAssociation*, RpClump*, CAnimBlendHierarchy*>(this, clump, animHierarchy);

#if 0
    std::printf("\nCAnimBlendAssociation::Init1: called! clump: %p | m_nSeqCount: %d\n\n", clump, animHierarchy->m_nSeqCount);
    CAnimBlendClumpData* animClumpData = RpClumpGetAnimBlendClumpData(clump);
    m_nNumBlendNodes = animClumpData->m_NumFrames;
    AllocateAnimBlendNodeArray(m_nNumBlendNodes);
    for (auto i = 0; i < m_nNumBlendNodes; i++) {
        m_pNodeArray[i].m_pAnimBlendAssociation = this;
    }

    m_pHierarchy = animHierarchy;
    for (auto i = 0; i < animHierarchy->m_nSeqCount; i++) {
        CAnimBlendSequence& sequence = animHierarchy->m_pSequences[i];
        AnimBlendFrameData* animFrameData = nullptr;

        // is bone id set?
        if (sequence.m_hasBoneIdSet) {
            animFrameData = RpAnimBlendClumpFindBone(clump, sequence.m_boneId);
        } else {
            animFrameData = RpAnimBlendClumpFindFrameFromHashKey(clump, sequence.m_hash);
        }

        if (animFrameData && sequence.m_nFrameCount > 0) {
            auto v11 = ((715827883i64 * ((DWORD)animFrameData - (DWORD)animClumpData->m_Frames)) >> 32) >> 2;
            auto frameIndex = (v11 >> 31) + v11;
            std::cout << "i: " << i << " | frameIndex: " << frameIndex << " | boneid: " << sequence.m_boneId << "\n";
            m_pNodeArray[frameIndex].m_pAnimSequence = &sequence;
        }
    }
#endif
}

// 0x4CEE40
void CAnimBlendAssociation::Init(CAnimBlendAssociation& source) {
    plugin::CallMethod<0x4CEE40, CAnimBlendAssociation*, CAnimBlendAssociation&>(this, source);
}

// 0x4CEEC0
void CAnimBlendAssociation::Init(CAnimBlendStaticAssociation& source) {
    plugin::CallMethod<0x4CEEC0, CAnimBlendAssociation*, CAnimBlendStaticAssociation&>(this, source);
}

// 0x4CEB70
void CAnimBlendAssociation::Start(float currentTime) {
    plugin::CallMethod<0x4CEB70, CAnimBlendAssociation*, float>(this, currentTime);
}

uint32 CAnimBlendAssociation::GetHashKey() const noexcept {
    return m_pHierarchy->m_hashKey;
}

// 0x4CE9F0
void CAnimBlendAssociation::AllocateAnimBlendNodeArray(int32 count) {
    plugin::CallMethod<0x4CE9F0, CAnimBlendAssociation*, int32>(this, count);
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
    plugin::CallMethod<0x4CEA80, CAnimBlendAssociation*, float>(this, currentTime);
}

// 0x4CEBC0
void CAnimBlendAssociation::SetDeleteCallback(void (*callback)(CAnimBlendAssociation*, void*), void* data) {
    m_nCallbackType = ANIMBLENDCALLBACK_DELETE;
    m_pCallbackFunc = callback;
    m_pCallbackData = data;
}

// 0x4CEBE0
void CAnimBlendAssociation::SetFinishCallback(void (*callback)(CAnimBlendAssociation*, void*), void* data) {
    m_nCallbackType = ANIMBLENDCALLBACK_FINISH;
    m_pCallbackFunc = callback;
    m_pCallbackData = data;
}

// 0x4CEB40
void CAnimBlendAssociation::SyncAnimation(CAnimBlendAssociation* syncWith) {
    const auto progress = syncWith->m_fCurrentTime / syncWith->m_pHierarchy->m_fTotalTime * m_pHierarchy->m_fTotalTime;
    SetCurrentTime(progress);
}
