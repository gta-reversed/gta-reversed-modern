/*
    Plugin-SDK (Grand Theft Auto San Andreas) file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "AnimSequenceFrames.h"

class CAnimBlendSequence {
public:
    CAnimBlendSequence();
    ~CAnimBlendSequence();

public:
    // thanks to jte for some info
    union {
        uint16 m_boneId; // IF m_hasBoneIdSet == TRUE
        uint32 m_hash;   // IF m_hasBoneIdSet == FALSE
    };
    union {
        struct {
            uint16 m_numFramesSet : 1;
            uint16 m_isRoot : 1;              // Root key frames have translation values (quaternion).
            uint16 m_isCompressed : 1;        // Compressed key frames.
            uint16 m_usingExternalMemory : 1; // When this flag is NOT set, you have to loop through all key frames in m_pFrames and free them separately.
            uint16 m_hasBoneIdSet : 1;

            // These remaining flags don't seem to be used anywhere, not even in CAnimBlendNode functions.
            uint16 m_bf6 : 1;
            uint16 m_bf7 : 1;
            uint16 m_b78 : 1;

            uint16 m_bf9 : 1;
            uint16 m_bf10 : 1;
            uint16 m_b11 : 1;
            uint16 m_bf12 : 1;
            uint16 m_bf13 : 1;
            uint16 m_b714 : 1;
            uint16 m_bf15 : 1;
            uint16 m_bf16 : 1;
        };
        uint16 m_nFlags;
    };
    uint16 m_nFrameCount;
    void*  m_pFrames;

public:
    static void InjectHooks();

    //funcs
    void CompressKeyframes(uint8* arg1);
    int32 GetDataSize(bool arg1);
    bool MoveMemorY();
    int32 RemoveQuaternionFlips();
    void RemoveUncompressedData(uint8* arg1);
    void SetBoneTag(int32 hash);
    void SetName(char const* string);
    void SetNumFrames(int32 count, bool arg2, bool arg3, uint8* arg4);
    void Uncompress(uint8* arg1);

    CAnimSequenceRootFrameUncompressed* GetUncompressedFrame(int32 iFrame); // Can return child frame casted as root frame, the translation shouldn't be accessed then
    CAnimSequenceRootFrameCompressed* GetCompressedFrame(int32 iFrame); // Can return child frame casted as root frame, the translation shouldn't be accessed then
};

VALIDATE_SIZE(CAnimBlendSequence, 0xC);
