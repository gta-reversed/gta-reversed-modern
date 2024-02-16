/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "AnimBlendSequence.h"

/*!
* @brief The animation object. It contains `CAnimBlendSequence`'s each of which are the animation for one bone (node).
* 
* The sequence/frames data is copied from it to `CAnimBlendAssociation` when a clump requests an animation.
* It is never destroyed and stays in memory unless `CStreaming` forces the IFP to unload to create space in memory.
*/
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

    uint8* AllocSequenceBlock(bool compressed) const;

    //! @addr 0x4CF2F0
    void CalcTotalTime() { ICalcTotalTime<false>(); }

    //! @addr 0x4CF3E0
    void CalcTotalTimeCompressed() { ICalcTotalTime<true>(); }

    void RemoveAnimSequences();
    void RemoveQuaternionFlips() const;
    void RemoveUncompressedData();

    void SetName(const char* string);
    void Uncompress();

    CAnimBlendSequence* FindSequence(const char* name) const;
    void* GetSequenceBlock() const;
    void CompressKeyframes() const;
    void MoveMemory();
    void Print();

    auto GetSequences() const { return std::span{ m_pSequences, (size_t)m_nSeqCount }; }
    auto GetHashKey() const { return m_hashKey; }
    auto GetTotalTime() const { return m_fTotalTime; }

private: // Function implementations
    template<bool Compressed>
    void ICalcTotalTime() {
        m_fTotalTime = 0.0f;
        for (auto& sequence : GetSequences()) {
            if (sequence.m_FramesNum == 0) { // FIX_BUGS by Mitchell Tobass
                continue;
            }
            m_fTotalTime = std::max<float>(m_fTotalTime, sequence.GetKeyFrame<Compressed>(sequence.m_FramesNum - 1)->DeltaTime);
            for (auto j = sequence.m_FramesNum - 1; j >= 1; j--) {
                const auto kf1 = sequence.GetKeyFrame<Compressed>(j);
                const auto kf2 = sequence.GetKeyFrame<Compressed>(j - 1);
                kf1->DeltaTime = kf1->DeltaTime - kf2->DeltaTime; // TODO/NOTE: With `FixedFloat` this has unncesessary conversions float <=> int
            }
        }
    }

private:
    friend void InjectHooksMain();
    static void InjectHooks();
    CAnimBlendHierarchy* Constructor() { this->CAnimBlendHierarchy::CAnimBlendHierarchy(); return this; }
    CAnimBlendHierarchy* Destructor() { this->CAnimBlendHierarchy::~CAnimBlendHierarchy(); return this; }
};

VALIDATE_SIZE(CAnimBlendHierarchy, 0x18);

