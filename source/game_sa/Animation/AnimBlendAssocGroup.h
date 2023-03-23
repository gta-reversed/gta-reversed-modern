/*
    Plugin-SDK file
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
    CAnimBlendAssociation*       CopyAnimation(const char* AnimName);
    CAnimBlendAssociation*       CopyAnimation(uint32 ID);
    void                         CreateAssociations(const char* szBlockName);
    void                         CreateAssociations(const char* AnimName, RpClump* clump, char** arg3, int32 NumAnimations);
    void                         CreateAssociations(const char* AnimName, const char* arg2, const char* arg3, uint32 arg4);
    void                         DestroyAssociations();
    CAnimBlendStaticAssociation* GetAnimation(const char* AnimName);
    CAnimBlendStaticAssociation* GetAnimation(uint32 ID);
    uint32                       GetAnimationId(const char* AnimName);
    void                         InitEmptyAssociations(RpClump* clump);
    ~CAnimBlendAssocGroup();
};

VALIDATE_SIZE(CAnimBlendAssocGroup, 0x14);
