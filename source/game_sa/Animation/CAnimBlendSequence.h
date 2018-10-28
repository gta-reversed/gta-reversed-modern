/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"

class  CAnimBlendSequence {
public:
    // thanks to jte for some info
    union
    {
        uint16_t m_boneId; // IF m_hasBoneIdSet == TRUE
        uint32_t m_hash; // IF m_hasBoneIdSet == FALSE
    };
    union {
        struct {
            uint16_t m_numFramesSet : 1;
            uint16_t m_isRoot : 1;              // Root key frames have translation values (quaternion).
            uint16_t m_isCompressed : 1;        // Compressed key frames.
            uint16_t m_usingExternalMemory : 1; // When this flag is NOT set, you have to loop through all key frames in m_pFrames and free them separately. 
            uint16_t m_hasBoneIdSet : 1;

            // These remaining flags don't seem to be used anywhere, not even in CAnimBlendNode functions.
            uint16_t m_bf6 : 1;
            uint16_t m_bf7 : 1;
            uint16_t m_b78: 1;

            uint16_t m_bf9 : 1;
            uint16_t m_bf10 : 1;
            uint16_t m_b11 : 1;
            uint16_t m_bf12 : 1;
            uint16_t m_bf13 : 1;
            uint16_t m_b714 : 1;
            uint16_t m_bf15 : 1;
            uint16_t m_bf16 : 1;
        };
        uint16_t m_nFlags;
    };
    unsigned short m_nFrameCount;
    void *m_pFrames;

    //funcs
    CAnimBlendSequence();
    void CompressKeyframes(unsigned char* arg1);
    int GetDataSize(bool arg1);
    bool MoveMemorY();
    int RemoveQuaternionFlips();
    void RemoveUncompressedData(unsigned char* arg1);
    void SetBoneTag(int hash);
    void SetName(char const* string);
    void SetNumFrames(int count, bool arg2, bool arg3, unsigned char* arg4);
    void Uncompress(unsigned char* arg1);
    ~CAnimBlendSequence();

};

VALIDATE_SIZE(CAnimBlendSequence, 0xC);
