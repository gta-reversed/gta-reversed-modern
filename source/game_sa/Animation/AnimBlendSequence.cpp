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
    m_FramesNum = 0;
    m_Frames = nullptr;
    m_BoneID = BONE_UNKNOWN;
}

// 0x4D0C30
CAnimBlendSequence::~CAnimBlendSequence() {
    // If we allocated memory, clean it
    if (!m_bUsingExternalMemory && m_Frames) {
        CMemoryMgr::Free(m_Frames);
    }
}

// 0x4D0F40
void CAnimBlendSequence::CompressKeyframes(uint8* frameData) {
    if (m_FramesNum == 0) {
        return;
    }

    void* frames = (frameData ? frameData : CMemoryMgr::Malloc(GetDataSize(true)));

    if (m_bHasTranslation) {
        auto* kftc = (KeyFrameTransCompressed*)frames;
        auto* kf = (KeyFrameTrans*)m_Frames;
        for (auto i = 0; i < m_FramesNum; i++, kf++, kftc++) {
            kftc->SetRotation(kf->Rot);
            kftc->SetTime(kf->DeltaTime);
            kftc->SetTranslation(kf->Trans);
        }
    } else {
        auto* kfc = (KeyFrameCompressed*)frames;
        auto* kf = (KeyFrame*)m_Frames;
        for (auto i = 0; i < m_FramesNum; i++, kf++, kfc++) {
            kfc->SetRotation(kf->Rot);
            kfc->SetTime(kf->DeltaTime);
        }
    }

    if (!m_bUsingExternalMemory) {
        CMemoryMgr::Free(m_Frames);
    }

    m_Frames = frames;
    m_bUsingExternalMemory = frameData != nullptr;
    m_bIsCompressed = true;
}

// 0x4D12A0
void CAnimBlendSequence::RemoveUncompressedData(uint8* frameData) {
    if (m_FramesNum) {
        CompressKeyframes(frameData);
    }
}

// 0x4D0C90
size_t CAnimBlendSequence::GetDataSize(bool compressed) const {
    if (compressed) {
        return m_FramesNum * (m_bHasTranslation ? sizeof(KeyFrameTransCompressed) : sizeof(KeyFrameCompressed));
    } else {
        return m_FramesNum * (m_bHasTranslation ? sizeof(KeyFrameTrans) : sizeof(KeyFrame));
    }
}

// 0x4D1190
void CAnimBlendSequence::RemoveQuaternionFlips() const {
    if (m_FramesNum < 2) {
        return;
    }

    KeyFrame* frame = GetUncompressedFrame(0);
    CQuaternion last = frame->Rot;
    for (auto i = 1; i < m_FramesNum; i++) {
        frame = GetUncompressedFrame(i);
        if (DotProduct(last, frame->Rot) < 0.0f) {
            frame->Rot = -frame->Rot;
        }
        last = frame->Rot;
    }
}

// 0x4D0C50
void CAnimBlendSequence::SetName(const char* name) {
    m_FrameHashKey = CKeyGen::GetUppercaseKey(name);
}

// 0x4D0C70
void CAnimBlendSequence::SetBoneTag(int32 boneId) {
    if (boneId != BONE_UNKNOWN) {
        m_bUsingBones = true;
        m_BoneID = static_cast<ePedBones>(boneId);
    }
}

// 0x4D0CD0
void CAnimBlendSequence::SetNumFrames(int32 count, bool bHasTranslation, bool compressed, CAnimBlendSequence* frameData) {
    m_bHasTranslation = bHasTranslation;
    m_FramesNum = (uint16)count;
    m_Frames = frameData ? frameData : CMemoryMgr::Malloc(GetDataSize(compressed));
    m_bUsingExternalMemory = frameData != nullptr; // NOTSA
    m_bHasRotation = true;
    m_bIsCompressed = compressed; // condition has been removed
}

// 0x4D0D40
void CAnimBlendSequence::Uncompress(uint8* frameData) {
    if (m_FramesNum == 0) {
        return;
    }

    void* frames = (frameData ? frameData : CMemoryMgr::Malloc(GetDataSize(false)));
    if (m_bHasTranslation) {
        auto* kftc = (KeyFrameTransCompressed*)m_Frames;
        auto* kf = (KeyFrameTrans*)frames;
        for (auto i = 0; i < m_FramesNum; i++, kf++, kftc++) {
            kftc->GetRotation(&kf->Rot);
            kf->DeltaTime = kftc->GetDeltaTime();
            kftc->GetTranslation(&kf->Trans);
        }
    } else {
        auto* kfc = (KeyFrameCompressed*)m_Frames;
        auto* kf = (KeyFrame*)frames;
        for (auto i = 0; i < m_FramesNum; i++, kf++, kfc++) {
            kfc->GetRotation(&kf->Rot);
            kf->DeltaTime = kfc->GetDeltaTime();
        }
    }

    if (!m_bUsingExternalMemory) {
        CMemoryMgr::Free(m_Frames);
    }
    m_Frames = frames;
    m_bUsingExternalMemory = frameData != nullptr;
    m_bIsCompressed = false;
}

// 0x4D1150
bool CAnimBlendSequence::MoveMemory() {
    if (m_bUsingExternalMemory)
        return false;

    if (!m_Frames)
        return false;

    auto frames = (CAnimBlendSequence*)CMemoryMgr::MoveMemory(m_Frames);
    if (frames == m_Frames)
        return false;

    m_Frames = frames;
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
    if (m_bHasTranslation) {
        return &static_cast<KeyFrameTrans*>(m_Frames)[frame];
    }

    auto* data = static_cast<KeyFrame*>(m_Frames);
    return reinterpret_cast<KeyFrameTrans*>(&data[frame]);
}

// Can return child frame casted as root frame, the translation shouldn't be accessed then
// 0x4CF220
KeyFrameTransCompressed* CAnimBlendSequence::GetCompressedFrame(int32 frame) const {
    if (m_bHasTranslation) {
        return &static_cast<KeyFrameTransCompressed*>(m_Frames)[frame];
    }

    auto* data = static_cast<KeyFrameCompressed*>(m_Frames);
    return reinterpret_cast<KeyFrameTransCompressed*>(&data[frame]);
}
