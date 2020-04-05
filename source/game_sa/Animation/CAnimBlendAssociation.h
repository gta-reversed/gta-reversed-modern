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
    ANIMATION_STARTED = 0x1,
    ANIMATION_LOOPED = 0x2,
    ANIMATION_FREEZE_LAST_FRAME = 0x4,
    ANIMATION_UNLOCK_LAST_FRAME = 0x8, // Animation will be stuck on last frame, if not set
    ANIMATION_PARTIAL = 0x10,
    ANIMATION_MOVEMENT = 0x20,
    ANIMATION_TRANLSATE_X = 0x40,
    ANIMATION_TRANLSATE_Y = 0x80,
    ANIMATION_UNUSED_1 = 0x100,
    ANIMATION_UNUSED_2 = 0x200,
    ANIMATION_ADD_TO_BLEND = 0x400,
    ANIMATION_UNUSED_3 = 0x800,
    ANIMATION_UNUSED_4 = 0x1000,
    ANIMATION_FREEZE_TRANSLATION = 0x2000,
    ANIMATION_BLOCK_REFERENCED = 0x4000,
    ANIMATION_INDESTRUCTIBLE = 0x8000
};

class CDefaultAnimCallback {
public:
    static void DefaultAnimCB(class CAnimBlendAssociation* pAnimAssoc, void* something) {
        // nothing here
    }
};

class CAnimBlendAssociation {
    DWORD * m_vTable;
    //virtual ~CAnimBlendAssociation() = delete; //PLUGIN_NO_DEFAULT_CONSTRUCTION_VIRTUALBASE(CAnimBlendAssociation)

public:
    RwLLLink m_link;
    unsigned short m_nNumBlendNodes;
    unsigned short m_nAnimGroup;
    CAnimBlendNode *m_pNodeArray;
    CAnimBlendHierarchy *m_pHierarchy;
    float m_fBlendAmount;
    float m_fBlendDelta;
    float m_fCurrentTime;
    float m_fSpeed;
    float m_fTimeStep;
    short m_nAnimId;
    union {
        struct {
            unsigned short m_bPlaying : 1;                   // Animation will stop playing if flag is not set       
            unsigned short m_bLooped : 1;                    // Animation will always restart when it completes 
            unsigned short m_bFreezeLastFrame : 1;           // Animation will freeze on last frame           
            unsigned short m_bLockLastFrame : 1;             // When this flag is Set, IF m_bLooped == false, m_bPlaying == true, and anim progress >= total anim time
                                                             // THEN m_bFreezeLastFrame is set to TRUE and m_fBlendDelta is set to -4.0.
                                                             // Result: https://i.imgur.com/idw0jsX.png
                                                      
            unsigned short m_bPartial : 1;                   // Partial animations run along other animations, like 
            unsigned short m_bEnableMovement : 1;            // blends all playing animations together if set

            // Camera will not move with ped, and ped will go back to the initial position when animation is over 
            unsigned short m_bLockLastX : 1;                          
            unsigned short m_bLockLastY : 1;                 // only applies if m_bLockLastX is set             

            unsigned short m_bf9 : 1;                        // doesn't seem to be used  
            unsigned short m_bf10 : 1;                       // doesn't seem to be used  
            unsigned short m_bAddAnimBlendToTotalBlend : 1;  // If set to TRUE, then result:
                                                             // Before = https://i.imgur.com/c8T7xNK.png | AFTER = https://i.imgur.com/4gqlA4n.png
            unsigned short m_bf12 : 1;                       // doesn't seem to be used  
            unsigned short m_bSecondaryTaskAnim : 1;         // doesn't seem to be used          
            unsigned short m_bFreezeTranslation : 1;         // Animation will play. Translation values will be ignored for animation (m_bEnableTranslation is ignored if set), and
                                                             // it only applies to some animations though
            unsigned short m_bBlockReferenced : 1;           // Animation block can't be unloaded if it's referenced by an animation.  
            unsigned short m_bIndestructible : 1;            // Animation will not be destroyed. It will be played simultaneously with other animations (multiple animations at once)
                                                             // if you set this flag while sitting in a car, you'll still be seated even if you exit the vehicle or play other animations,
                                                             // like walking, running, crouching, etc, like this: https://i.imgur.com/VgWn5fl.png
        };
        unsigned short m_nFlags;
    };

    eAnimBlendCallbackType m_nCallbackType;

    void(*m_pCallbackFunc)(CAnimBlendAssociation *, void *);
    void *m_pCallbackData;

    // vtable function #0 (destructor)
    static void InjectHooks();
    CAnimBlendAssociation* Constructor1(RpClump *pClump, CAnimBlendHierarchy * pAnimHierarchy);
     void AllocateAnimBlendNodeArray(int count);
     void FreeAnimBlendNodeArray();
     CAnimBlendNode *GetNode(int nodeIndex);
     void Init1(RpClump *clump, CAnimBlendHierarchy *hierarchy);
     void Init(CAnimBlendAssociation &source);
     //void Init(CAnimBlendStaticAssociation &source);
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

//VTABLE_DESC(CAnimBlendAssociation, 0x85C6D0, 1);
VALIDATE_SIZE(CAnimBlendAssociation, 0x3C);

//#include "meta/meta.CAnimBlendAssociation.h"
