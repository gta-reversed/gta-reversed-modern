/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "AnimSequenceFrames.h"

// The sequence of key frames of one animated node
class CAnimBlendSequence {
public:
    // thanks to jte for some info
    union {
        ePedBones m_boneId; // IF m_hasBoneIdSet == TRUE
        uint32    m_hash;   // IF m_hasBoneIdSet == FALSE
    };
    union {
        struct {
            uint16 m_bHasRotation : 1;
            uint16 m_bHasTranslation : 1;     // Root key frames have translation values (quaternion).
            uint16 m_isCompressed : 1;        // Compressed key frames.
            uint16 m_usingExternalMemory : 1; // When this flag is NOT set, you have to loop through all key frames in m_pFrames and free them separately.
            uint16 m_hasBoneIdSet : 1;
        };
        uint16 m_nFlags;
    };
    uint16 m_nFrameCount;
    void*  m_pFrames;

public:
    static void InjectHooks();

    CAnimBlendSequence();
    ~CAnimBlendSequence();

    void CompressKeyframes(uint8* frameData);
    [[nodiscard]] size_t GetDataSize(bool compressed) const;
    bool MoveMemory();
    void Print();
    void RemoveQuaternionFlips();
    void RemoveUncompressedData(uint8* frameData);
    void SetBoneTag(int32 boneId);
    void SetName(const char* string);
    void SetNumFrames(int32 count, bool root, bool compressed, CAnimBlendSequence* frameData); // root -> isTranslated?
    void Uncompress(uint8* frameData);

    KeyFrame* GetKeyFrame(size_t n) const {
        return m_bHasTranslation ?
            &((KeyFrameTrans*)m_pFrames)[n] :
            &((KeyFrame*)m_pFrames)[n];
    }

    KeyFrameTrans* GetUncompressedFrame(int32 frame) const;
    KeyFrameTransCompressed* GetCompressedFrame(int32 frame) const;

    CAnimBlendSequence* Constructor() { this->CAnimBlendSequence::CAnimBlendSequence(); return this; }
    CAnimBlendSequence* Destructor() { this->CAnimBlendSequence::~CAnimBlendSequence(); return this; }
};

VALIDATE_SIZE(CAnimBlendSequence, 0xC);
