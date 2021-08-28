#include "StdInc.h"

void CAnimBlendAssociation::InjectHooks() {
    HookInstall(0x4CEFC0, &CAnimBlendAssociation::Constructor);
}

void* CAnimBlendAssociation::operator new(unsigned int size) {
    return ((CAnimBlendAssociation * (__cdecl*)(unsigned int))0x82119A)(size);
}

void CAnimBlendAssociation::operator delete(void* object) {
    ((void(__cdecl*)(void*))0x8214BD)(object);
}

CAnimBlendAssociation::CAnimBlendAssociation(RpClump* pClump, CAnimBlendHierarchy* pAnimHierarchy) {
    m_fBlendAmount = 1.0f;
    m_fSpeed = 1.0f;
    m_pNodeArray = nullptr;
    m_fBlendDelta = 0.0f;
    m_fCurrentTime = 0.0f;
    m_fTimeStep = 0.0f;
    m_nFlags = 0;
    m_nCallbackType = ANIMBLENDCALLBACK_NONE;
    m_nAnimGroup = -1;
    m_nAnimId = -1;
    m_pNext = nullptr;
    m_pPrevious = nullptr;
    Init(pClump, pAnimHierarchy);
}

CAnimBlendAssociation::~CAnimBlendAssociation() {
    if (m_pNodeArray)
        CMemoryMgr::FreeAlign(m_pNodeArray);
    if (m_pPrevious)
        m_pPrevious->m_pNext = m_pNext;
    if (m_pNext)
        m_pNext->m_pPrevious = m_pPrevious;
    m_pNext = nullptr;
    m_pPrevious = nullptr;
    if (m_nFlags & ANIM_FLAG_BLOCK_REFERENCED)
        CAnimManager::RemoveAnimBlockRef(m_pHierarchy->m_nAnimBlockId);
}

CAnimBlendAssociation* CAnimBlendAssociation::Constructor(RpClump* pClump, CAnimBlendHierarchy* pAnimHierarchy) {
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CAnimBlendAssociation*, 0x4CEFC0, CAnimBlendAssociation*, RpClump*, CAnimBlendHierarchy*>(this, pClump, pAnimHierarchy);
#else
    this->CAnimBlendAssociation::CAnimBlendAssociation(pClump, pAnimHierarchy);
    return this;
#endif
}

void CAnimBlendAssociation::Init(RpClump* pClump, CAnimBlendHierarchy* pAnimHierarchy) {
    //#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethod<0x4CED50, CAnimBlendAssociation*, RpClump*, CAnimBlendHierarchy*>(this, pClump, pAnimHierarchy);
#if 0
    std::printf("\nCAnimBlendAssociation::Init1: called! pClump: %p | m_nSeqCount: %d\n\n", pClump, pAnimHierarchy->m_nSeqCount);
    CAnimBlendClumpData * pAnimClumpData = GetAnimClumpData(pClump); 
    m_nNumBlendNodes = pAnimClumpData->m_nNumFrames;
    AllocateAnimBlendNodeArray(m_nNumBlendNodes);
    for (size_t i = 0; i < m_nNumBlendNodes; i++)
    {
        m_pNodeArray[i].m_pAnimBlendAssociation = this; 
    }

    m_pHierarchy = pAnimHierarchy;
    for (size_t i = 0; i < pAnimHierarchy->m_nSeqCount; i++)
    {
        CAnimBlendSequence& sequence = pAnimHierarchy->m_pSequences[i];
        AnimBlendFrameData *pAnimFrameData = nullptr;

        // is bone id set?
        if (sequence.m_nFlags & 0x10)
        {
            pAnimFrameData = RpAnimBlendClumpFindBone(pClump, sequence.m_boneId);
        }
        else 
        {
            pAnimFrameData = RpAnimBlendClumpFindFrameFromHashKey(pClump, sequence.m_hash);
        }
        if (pAnimFrameData && sequence.m_nFrameCount > 0)
        {
            auto v11 = ((715827883i64 * ((DWORD)pAnimFrameData - (DWORD)pAnimClumpData->m_pFrames)) >> 32) >> 2;
            auto frameIndex = (v11 >> 31) + v11;
            std::cout << "i: " << i  <<" | frameIndex: " << frameIndex << " | boneid: " << sequence.m_boneId << "\n"; 
            m_pNodeArray[frameIndex].m_pAnimSequence = &sequence;
        }
    }
#endif
}

void CAnimBlendAssociation::Start(float currentTime) {
    plugin::CallMethod<0x4CEB70, CAnimBlendAssociation*, float>(this, currentTime);
}

void CAnimBlendAssociation::AllocateAnimBlendNodeArray(int count) {
    plugin::CallMethod<0x4CE9F0, CAnimBlendAssociation*, int>(this, count);
}

void CAnimBlendAssociation::SetBlend(float blendAmount, float blendDelta) {
    plugin::CallMethod<0x4CEBA0, CAnimBlendAssociation*, float, float>(this, blendAmount, blendDelta);
}

void CAnimBlendAssociation::SetCurrentTime(float currentTime) {
    plugin::CallMethod<0x4CEA80, CAnimBlendAssociation*, float>(this, currentTime);
}

void CAnimBlendAssociation::SetDeleteCallback(void (*callback)(CAnimBlendAssociation*, void*), void* data) {
    plugin::CallMethod<0x4CEBC0, CAnimBlendAssociation*, void (*)(CAnimBlendAssociation*, void*), void*>(this, callback, data);
}

void CAnimBlendAssociation::SetFinishCallback(void (*callback)(CAnimBlendAssociation*, void*), void* data) {
    plugin::CallMethod<0x4CEBE0, CAnimBlendAssociation*, void (*)(CAnimBlendAssociation*, void*), void*>(this, callback, data);
}
