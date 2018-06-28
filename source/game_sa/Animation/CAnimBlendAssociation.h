/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "AnimAssociationData.h"
#include "eAnimBlendCallbackType.h"
#include "RenderWare.h"

class CAnimBlendNode;
class CAnimBlendHierarchy;
class CAnimBlendStaticAssociation;

class  CAnimBlendAssociation : public AnimAssociationData {
    PLUGIN_NO_DEFAULT_CONSTRUCTION_VIRTUALBASE(CAnimBlendAssociation)

public:
    eAnimBlendCallbackType m_nCallbackType;
    void(*m_pCallbackFunc)(CAnimBlendAssociation *, void *);
    void *m_pCallbackData;

    // vtable function #0 (destructor)

     void AllocateAnimBlendNodeArray(int count);
     void FreeAnimBlendNodeArray();
     CAnimBlendNode *GetNode(int nodeIndex);
     void Init(RpClump *clump, CAnimBlendHierarchy *hierarchy);
     void Init(CAnimBlendAssociation &source);
     void Init(CAnimBlendStaticAssociation &source);
     void ReferenceAnimBlock();
     void SetBlend(float blendAmount, float blendDelta);
     void SetBlendTo(float blendAmount, float blendDelta);
     void SetCurrentTime(float currentTime);
     void SetDeleteCallback(void(*callback)(CAnimBlendAssociation *, void *), void *data);
     void SetFinishCallback(void(*callback)(CAnimBlendAssociation *, void *), void *data);
     void Start(float currentTime);
     void SyncAnimation(CAnimBlendAssociation *syncWith);
     bool UpdateBlend(float blendDeltaMult);
     bool UpdateTime(float unused1, float unused2);
     void UpdateTimeStep(float speedMult, float timeMult);
};

VTABLE_DESC(CAnimBlendAssociation, 0x85C6D0, 1);
VALIDATE_SIZE(CAnimBlendAssociation, 0x3C);

//#include "meta/meta.CAnimBlendAssociation.h"
