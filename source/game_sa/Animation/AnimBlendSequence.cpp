#include "StdInc.h"

#include "AnimBlendSequence.h"

void CAnimBlendSequence::InjectHooks() {
    RH_ScopedClass(CAnimBlendSequence);
    RH_ScopedCategory("Animation");

    RH_ScopedInstall(Constructor, 0x4D0C10);
    RH_ScopedInstall(Destructor, 0x4D0C30);
    RH_ScopedInstall(SetName, 0x4D0C50);
    RH_ScopedInstall(SetBoneTag, 0x4D0C70);
    RH_ScopedInstall(GetDataSize, 0x4D0C90);
    RH_ScopedInstall(SetNumFrames, 0x4D0CD0);
    RH_ScopedInstall(Uncompress, 0x4D0D40);
    RH_ScopedInstall(CompressKeyframes, 0x4D0F40);
    RH_ScopedInstall(MoveMemory, 0x4D1150);
    RH_ScopedInstall(Print, 0x4D1180);
    RH_ScopedInstall(RemoveQuaternionFlips, 0x4D1190);
    RH_ScopedInstall(RemoveUncompressedData, 0x4D12A0);
    RH_ScopedInstall(GetUncompressedFrame, 0x4CF1F0);
    RH_ScopedInstall(GetCompressedFrame, 0x4CF220);
}

// 0x4D0C10
CAnimBlendSequence::CAnimBlendSequence() {
    m_nFlags = 0;
    m_nFrameCount = 0;
    m_pFrames = nullptr;
    m_boneId = BONE_UNKNOWN;
}

// 0x4D0C30
CAnimBlendSequence::~CAnimBlendSequence() {
    // If we allocated memory, clean it
    if (!m_usingExternalMemory && m_pFrames) {
        CMemoryMgr::Free(m_pFrames);
    }
}

// 0x4D0F40
void CAnimBlendSequence::CompressKeyframes(uint8* frameData) {
    if (m_nFrameCount == 0) {
        return;
    }

    void* frames = (frameData ? frameData : CMemoryMgr::Malloc(GetDataSize(true)));
    if (m_isRoot) {
        auto* kftc = (KeyFrameTransCompressed*)frames;
        auto* kf = (KeyFrameTrans*)m_pFrames;
        for (auto i = 0; i < m_nFrameCount; i++, kf++, kftc++) {
            kftc->SetRotation(kf->rotation);
            kftc->SetTime(kf->deltaTime);
            kftc->SetTranslation(kf->translation);
        }
    } else {
        auto* kfc = (KeyFrameCompressed*)frames;
        auto* kf = (KeyFrame*)m_pFrames;
        for (auto i = 0; i < m_nFrameCount; i++, kf++, kfc++) {
            kfc->SetRotation(kf->rotation);
            kfc->SetTime(kf->deltaTime);
        }
    }

    if (!m_usingExternalMemory) {
        CMemoryMgr::Free(m_pFrames);
    }
    m_pFrames = frames;
    m_usingExternalMemory = frameData != nullptr;
    m_isCompressed = true;
}

// 0x4D12A0
void CAnimBlendSequence::RemoveUncompressedData(uint8* frameData) {
    if (m_nFrameCount) {
        CompressKeyframes(frameData);
    }
}

// 0x4D0C90
size_t CAnimBlendSequence::GetDataSize(bool compressed) const {
    if (compressed) {
        return m_nFrameCount * (m_isRoot ? sizeof(KeyFrameTransCompressed) : sizeof(KeyFrameCompressed));
    } else {
        return m_nFrameCount * (m_isRoot ? sizeof(KeyFrameTrans) : sizeof(KeyFrame));
    }
}

// 0x4D1190
void CAnimBlendSequence::RemoveQuaternionFlips() {
    if (m_nFrameCount < 2) {
        return;
    }

    KeyFrame* frame = GetUncompressedFrame(0);
    CQuaternion last = frame->rotation;
    for (auto i = 1; i < m_nFrameCount; i++) {
        frame = GetUncompressedFrame(i);
        if (DotProduct(last, frame->rotation) < 0.0f) {
            frame->rotation = -frame->rotation;
        }
        last = frame->rotation;
    }
}

// 0x4D0C50
void CAnimBlendSequence::SetName(const char* name) {
    m_hash = CKeyGen::GetUppercaseKey(name);
}

// 0x4D0C70
void CAnimBlendSequence::SetBoneTag(int32 boneId) {
    if (boneId != BONE_UNKNOWN) {
        m_hasBoneIdSet = true;
        m_boneId = static_cast<ePedBones>(boneId);
    }
}

// 0x4D0CD0
void CAnimBlendSequence::SetNumFrames(int32 count, bool root, bool compressed, CAnimBlendSequence* frameData) {
    m_isRoot = root;
    m_nFrameCount = (uint16)count;
    m_pFrames = frameData ? frameData : CMemoryMgr::Malloc(GetDataSize(compressed));
    m_usingExternalMemory = frameData != nullptr; // NOTSA
    m_numFramesSet = true;
    m_isCompressed = compressed; // condition has been removed
}

// 0x4D0D40
void CAnimBlendSequence::Uncompress(uint8* frameData) {
    if (m_nFrameCount == 0) {
        return;
    }

    void* frames = (frameData ? frameData : CMemoryMgr::Malloc(GetDataSize(false)));
    if (m_isRoot) {
        auto* kftc = (KeyFrameTransCompressed*)m_pFrames;
        auto* kf = (KeyFrameTrans*)frames;
        for (auto i = 0; i < m_nFrameCount; i++, kf++, kftc++) {
            kftc->GetRotation(&kf->rotation);
            kf->deltaTime = kftc->GetDeltaTime();
            kftc->GetTranslation(&kf->translation);
        }
    } else {
        auto* kfc = (KeyFrameCompressed*)m_pFrames;
        auto* kf = (KeyFrame*)frames;
        for (auto i = 0; i < m_nFrameCount; i++, kf++, kfc++) {
            kfc->GetRotation(&kf->rotation);
            kf->deltaTime = kfc->GetDeltaTime();
        }
    }

    if (!m_usingExternalMemory) {
        CMemoryMgr::Free(m_pFrames);
    }
    m_pFrames = frames;
    m_usingExternalMemory = frameData != nullptr;
    m_isCompressed = false;
}

// 0x4D1150
bool CAnimBlendSequence::MoveMemory() {
    if (m_usingExternalMemory)
        return false;

    if (!m_pFrames)
        return false;

    auto frames = (CAnimBlendSequence*)CMemoryMgr::MoveMemory(m_pFrames);
    if (frames == m_pFrames)
        return false;

    m_pFrames = frames;
    return true;
}

// 0x4D1180
void CAnimBlendSequence::Print() {
#ifndef FINAL

#endif
}

// Can return child frame casted as root frame, the translation shouldn't be accessed then
// 0x4CF1F0
KeyFrameTrans* CAnimBlendSequence::GetUncompressedFrame(int32 frame) const {
    if (m_isRoot) {
        return &static_cast<KeyFrameTrans*>(m_pFrames)[frame];
    }

    auto* data = static_cast<KeyFrame*>(m_pFrames);
    return reinterpret_cast<KeyFrameTrans*>(&data[frame]);
}

// Can return child frame casted as root frame, the translation shouldn't be accessed then
// 0x4CF220
KeyFrameTransCompressed* CAnimBlendSequence::GetCompressedFrame(int32 frame) const {
    if (m_isRoot) {
        return &static_cast<KeyFrameTransCompressed*>(m_pFrames)[frame];
    }

    auto* data = static_cast<KeyFrameCompressed*>(m_pFrames);
    return reinterpret_cast<KeyFrameTransCompressed*>(&data[frame]);
}
