/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "AnimBlendSequence.h"

class CAnimBlendHierarchy {
public:
    uint32              m_hashKey;
    CAnimBlendSequence* m_pSequences;
    uint16              m_nSeqCount;
    bool                m_bRunningCompressed;
    char                field_B;
    int32               m_nAnimBlockId;
    float               m_fTotalTime;
    int32               field_14;

public:
    void* AllocSequenceBlock(bool arg1);
    CAnimBlendHierarchy();
    void CalcTotalTime();
    void CalcTotalTimeCompressed();
    void RemoveAnimSequences();
    void RemoveQuaternionFlips();
    void RemoveUncompressedData();
    void SetName(char const* string);
    void Shutdown();
    void Uncompress();
};

VALIDATE_SIZE(CAnimBlendHierarchy, 0x18);