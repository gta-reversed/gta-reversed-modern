/*
    Plugin-SDK file
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
    bool                m_bIsCompressed;
    bool                m_bKeepCompressed;
    int32               m_nAnimBlockId;
    float               m_fTotalTime;
    CLink<CAnimBlendHierarchy*>* m_Link;

public:
    CAnimBlendHierarchy();
    ~CAnimBlendHierarchy();

    void Shutdown();

    uint8* AllocSequenceBlock(bool compressed);

    void CalcTotalTime();
    void CalcTotalTimeCompressed();

    void RemoveAnimSequences();
    void RemoveQuaternionFlips();
    void RemoveUncompressedData();

    void SetName(const char* string);
    void Uncompress();

    CAnimBlendSequence* FindSequence(const char* name);
    void* GetSequenceBlock();
    void CompressKeyframes();
    void MoveMemory();
    void Print();

    auto GetSequences() const { return std::span{ m_pSequences, (size_t)m_nSeqCount }; }

private:
    friend void InjectHooksMain();
    static void InjectHooks();
    CAnimBlendHierarchy* Constructor() { this->CAnimBlendHierarchy::CAnimBlendHierarchy(); return this; }
    CAnimBlendHierarchy* Destructor() { this->CAnimBlendHierarchy::~CAnimBlendHierarchy(); return this; }
};

VALIDATE_SIZE(CAnimBlendHierarchy, 0x18);

