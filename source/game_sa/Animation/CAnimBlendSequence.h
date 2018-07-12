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
    union
    {
        uint16_t m_boneId; // IF m_hasBoneIdSet == TRUE
        uint32_t m_nHash;   // IF m_hasBoneIdSet == FALSE
    };
    unsigned short m_nFlags;
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
