/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "AnimBlendAssociation.h"
#include "RenderWare.h"
#include "AnimBlock.h"

class CAnimBlendStaticAssociation;

class CAnimBlendAssocGroup {
public:
    CAnimBlock*                  m_pAnimBlock;
    CAnimBlendStaticAssociation* m_pAssociations;
    uint32                       m_nNumAnimations;
    int32                        m_nIdOffset;
    int32                        m_nGroupID;

public:
    CAnimBlendAssocGroup();
    CAnimBlendAssociation*       CopyAnimation(char const* AnimName);
    CAnimBlendAssociation*       CopyAnimation(uint32 ID);
    void                         CreateAssociations(char const* szBlockName);
    void                         CreateAssociations(char const* AnimName, RpClump* pClump, char** arg3, int32 NumAnimations);
    void                         CreateAssociations(char const* AnimName, char const* arg2, char const* arg3, int32 arg4);
    void                         DestroyAssociations();
    CAnimBlendStaticAssociation* GetAnimation(char const* AnimName);
    CAnimBlendStaticAssociation* GetAnimation(uint32 ID);
    uint32                       GetAnimationId(char const* AnimName);
    void                         InitEmptyAssociations(RpClump* pClump);
    ~CAnimBlendAssocGroup();
};

VALIDATE_SIZE(CAnimBlendAssocGroup, 0x14);
