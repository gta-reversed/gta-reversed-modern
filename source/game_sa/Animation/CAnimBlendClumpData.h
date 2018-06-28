/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "RenderWare.h"
#include "CVector.h"
#include "AnimBlendFrameData.h"

class  CAnimBlendClumpData {
public:
    RwLinkList m_associationsList;
    int m_nNumFrames;
    CVector *m_pvecPedPosition;
    AnimBlendFrameData *m_pFrames;

     CAnimBlendClumpData();

     ~CAnimBlendClumpData();

     void ForAllFrames(void(*callback)(AnimBlendFrameData *, void *), void *data);
    //! dummy function
     void ForAllFramesInSPR(void(*callback)(AnimBlendFrameData *, void *), void *data, unsigned int a3);
    //! dummy function
     void LoadFramesIntoSPR();
     void SetNumberOfBones(int numBones);
};

VALIDATE_SIZE(CAnimBlendClumpData, 0x14);

//#include "meta/meta.CAnimBlendClumpData.h"
