/*
    Plugin-SDK (Grand Theft Auto San Andreas) file
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
    RwLinkList          m_associationsList;
    int32               m_nNumFrames;
    CVector*            m_pvecPedPosition;
    AnimBlendFrameData* m_pFrames;

public:
    CAnimBlendClumpData();

    ~CAnimBlendClumpData();

    void ForAllFrames(void (*callback)(AnimBlendFrameData*, void*), void* data);
    //! dummy function
    void ForAllFramesInSPR(void (*callback)(AnimBlendFrameData*, void*), void* data, uint32 a3);
    //! dummy function
    void LoadFramesIntoSPR();
    void SetNumberOfBones(int32 numBones);
};

VALIDATE_SIZE(CAnimBlendClumpData, 0x14);
