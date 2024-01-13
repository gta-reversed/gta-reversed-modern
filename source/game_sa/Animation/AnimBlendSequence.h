/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "AnimSequenceFrames.h"

//! The sequence of key-frames of one animated node (bone)
class CAnimBlendSequence {
public:
    //! The bone/frame this sequence is associated with
    //! Thanks to jte for some info
    union {
        ePedBones m_BoneID;         // IF m_bUsingBones == TRUE
        uint32    m_FrameHashKey;   // IF m_bUsingBones == FALSE
    };
    union {
        struct {
            uint16 m_bHasRotation : 1;
            uint16 m_bHasTranslation : 1;      // Root key frames have translation values (quaternion).
            uint16 m_bIsCompressed : 1;        // Compressed key frames.
            uint16 m_bUsingExternalMemory : 1; // When this flag is NOT set, you have to loop through all key frames in m_pFrames and free them separately.
            uint16 m_bUsingBones : 1;          // If `true` this sequence is for animating bones, otherwise frames.
        };
        uint16 m_nFlags;
    };
    uint16 m_FramesNum;
    void*  m_Frames;

public:
    static void InjectHooks();

    CAnimBlendSequence();
    ~CAnimBlendSequence();

    void CompressKeyframes(uint8* frameData);
    [[nodiscard]] size_t GetDataSize(bool compressed) const;
    bool MoveMemory();
    void Print();
    void RemoveQuaternionFlips() const;
    void RemoveUncompressedData(uint8* frameData);
    void SetBoneTag(int32 boneId);
    void SetName(const char* string);
    void SetNumFrames(uint32 count, bool bHasTranslation, bool compressed, void* frameData);
    void Uncompress(uint8* frameData);

    // Used to implement copy-paste functions
    template<bool AsCompressed>
    auto GetKeyFrame(size_t n) const {
        if constexpr (AsCompressed) {
            return GetCKeyFrame(n);
        } else {
            return GetUKeyFrame(n);
        }
    }

    KeyFrameTrans* GetUKeyFrame(size_t n) const { // `U` = Uncompressed
        assert(n < m_FramesNum);
        return static_cast<KeyFrameTrans*>(m_bHasTranslation ? // Lie a little by always casting to `KeyFrameTrans*` to make our lifes easier
            &((KeyFrameTrans*)m_Frames)[n] :
            &((KeyFrame*)m_Frames)[n]);
    }

    KeyFrameTransCompressed* GetCKeyFrame(size_t n) const { // `C` = Compressed
        assert(n < m_FramesNum);
        return static_cast<KeyFrameTransCompressed*>(m_bHasTranslation ? // Lie a little by always casting to `KeyFrameTransCompressed*` to make our lifes easier
            &((KeyFrameTransCompressed*)m_Frames)[n] :
            &((KeyFrameCompressed*)m_Frames)[n]);
    }

    CAnimBlendSequence* Constructor() { this->CAnimBlendSequence::CAnimBlendSequence(); return this; }
    CAnimBlendSequence* Destructor() { this->CAnimBlendSequence::~CAnimBlendSequence(); return this; }
};

VALIDATE_SIZE(CAnimBlendSequence, 0xC);
