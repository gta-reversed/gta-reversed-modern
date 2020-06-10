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

enum eAnimationFlags
{
    ANIM_FLAG_STARTED = 0x1,
    ANIM_FLAG_LOOPED = 0x2,
    ANIM_FLAG_FREEZE_LAST_FRAME = 0x4,
    ANIM_FLAG_UNLOCK_LAST_FRAME = 0x8, // Animation will be stuck on last frame, if not set
    ANIM_FLAG_PARTIAL = 0x10,
    ANIM_FLAG_MOVEMENT = 0x20,
    ANIM_FLAG_TRANLSATE_Y = 0x40,
    ANIM_FLAG_TRANLSATE_X = 0x80,
    ANIM_FLAG_100 = 0x100,
    ANIM_FLAG_200 = 0x200,
    ANIM_FLAG_400 = 0x400,
    ANIM_FLAG_800 = 0x800,
    ANIM_FLAG_1000 = 0x1000,
    ANIM_FLAG_FREEZE_TRANSLATION = 0x2000,
    ANIM_FLAG_BLOCK_REFERENCED = 0x4000,
    ANIM_FLAG_INDESTRUCTIBLE = 0x8000 // the animation is never destroyed if this flag is set, NO MATTER WHAT
};

class CDefaultAnimCallback {
public:
    static void DefaultAnimCB(class CAnimBlendAssociation* pAnimAssoc, void* something) {
        // nothing here
    }
};

struct SClumpAnimAssoc
{
    SClumpAnimAssoc* m_pNext;
    SClumpAnimAssoc* m_pPrevious;
    std::uint16_t m_nNumBlendNodes;
    std::int16_t m_nAnimGroup;
    CAnimBlendNode* m_pNodeArray;
    CAnimBlendHierarchy* m_pHierarchy;
    float m_fBlendAmount;
    float m_fBlendDelta;
    float m_fCurrentTime;
    float m_fSpeed;
    float m_fTimeStep;
    std::int16_t m_nAnimId;
    std::uint16_t m_nFlags;
};

class CAnimBlendAssociation : public SClumpAnimAssoc
{
public:
    eAnimBlendCallbackType m_nCallbackType;

    void(*m_pCallbackFunc)(CAnimBlendAssociation *, void *);
    void *m_pCallbackData;

    void* operator new(unsigned int size);
    void operator delete(void* object);

    static void InjectHooks();
    CAnimBlendAssociation(RpClump* pClump, CAnimBlendHierarchy* pAnimHierarchy);
    virtual ~CAnimBlendAssociation();
private:
    CAnimBlendAssociation* Constructor(RpClump* pClump, CAnimBlendHierarchy* pAnimHierarchy);
public:
    void AllocateAnimBlendNodeArray(int count);
    void FreeAnimBlendNodeArray();
    CAnimBlendNode* GetNode(int nodeIndex);
    void Init(RpClump* clump, CAnimBlendHierarchy* hierarchy);
    void Init(CAnimBlendAssociation& source);
    //void Init(CAnimBlendStaticAssociation &source);
    void ReferenceAnimBlock();
    void SetBlend(float blendAmount, float blendDelta);
    void SetBlendTo(float blendAmount, float blendDelta);
    void SetCurrentTime(float currentTime);
    void SetDeleteCallback(void(*callback)(CAnimBlendAssociation*, void*), void* data);
    void SetFinishCallback(void(*callback)(CAnimBlendAssociation*, void*), void* data);
    void Start(float currentTime);
    void SyncAnimation(CAnimBlendAssociation* syncWith);
    bool UpdateBlend(float blendDeltaMult);
    bool UpdateTime(float unused1, float unused2);
    void UpdateTimeStep(float speedMult, float timeMult);
};

//VTABLE_DESC(CAnimBlendAssociation, 0x85C6D0, 1);
VALIDATE_SIZE(CAnimBlendAssociation, 0x3C);

//#include "meta/meta.CAnimBlendAssociation.h"
