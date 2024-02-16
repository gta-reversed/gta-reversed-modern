/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "RenderWare.h"
#include "Vector.h"
#include "AnimBlendFrameData.h"

class CAnimBlendClumpData {
public:
    CAnimBlendLink      m_AnimList;        //!< List of `CAnimBlendAssociation` - List of anims that are being played on this clump
    uint32              m_NumFrames;
    CVector*            m_PedPosition;
    AnimBlendFrameData* m_Frames;

public:
    static void InjectHooks();

    CAnimBlendClumpData();
    ~CAnimBlendClumpData();
    CAnimBlendClumpData* Constructor() { this->CAnimBlendClumpData::CAnimBlendClumpData(); return this; }
    CAnimBlendClumpData* Destructor()  { this->CAnimBlendClumpData::~CAnimBlendClumpData(); return this; }

    void ForAllFrames(void (*callback)(AnimBlendFrameData*, void*), void* data);

    /*!
     * @notsa
     * @brief Iterate all frames (Using a functor, usually a lambda) 
     * @param Fn The functor to be called
    */
    template<typename Functor>
    void ForAllFramesF(Functor&& Fn) {
        for (auto& frame : std::span{ m_Frames, m_NumFrames }) {
            std::invoke(Fn, &frame);
        }
    }

    void ForAllFramesInSPR(void (*callback)(AnimBlendFrameData*, void*), void* data, uint32 a3);
    void LoadFramesIntoSPR();
    void SetNumberOfBones(uint32 numBones);
};

VALIDATE_SIZE(CAnimBlendClumpData, 0x14);
