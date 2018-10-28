#include "StdInc.h"

void CAnimBlendAssociation::InjectHooks()
{
    InjectHook(0x4CEFC0, &CAnimBlendAssociation::Constructor1, PATCH_JUMP);
}

CAnimBlendAssociation* CAnimBlendAssociation::Constructor1(RpClump *pClump, CAnimBlendHierarchy * pAnimHierarchy)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CAnimBlendAssociation*, 0x4CEFC0, CAnimBlendAssociation*, RpClump *, CAnimBlendHierarchy *>(this, pClump, pAnimHierarchy);
#else
    m_fBlendAmount = 1.0;
    m_fSpeed = 1.0;
    m_pNodeArray = 0;
    m_fBlendDelta = 0.0;
    m_fCurrentTime = 0.0;
    m_fTimeStep = 0.0;
    m_nFlags = 0;
    m_nCallbackType = static_cast <eAnimBlendCallbackType> (0);
    m_vTable = reinterpret_cast <DWORD*>(0x85C6D0);
    m_nAnimGroup = -1;
    m_nAnimId = -1;
    m_link.prev = 0;
    m_link.next = 0;

    Init1(pClump, pAnimHierarchy);
    return this;
#endif
}

void CAnimBlendAssociation::Init1(RpClump *pClump, CAnimBlendHierarchy * pAnimHierarchy)
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethodDynGlobal<CAnimBlendAssociation *, RpClump *, CAnimBlendHierarchy *>(0x4CED50, this, pClump, pAnimHierarchy);
#else
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
            pAnimFrameData = RpAnimBlendClumpFindFrameFromHashKey(pClump, sequence.m_nHash);
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
    plugin::CallMethodDynGlobal<CAnimBlendAssociation *, float>(0x4CEB70, this, currentTime);
}

void CAnimBlendAssociation::AllocateAnimBlendNodeArray(int count) {
    plugin::CallMethodDynGlobal<CAnimBlendAssociation *, int>(0x4CE9F0, this, count);
}