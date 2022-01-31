/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
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
    CAnimBlendLink link;
    int32 numFrames;
    union {
        CVector2D* velocity2d;
        CVector* velocity3d;
    };
    AnimBlendFrameData* frames;

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
