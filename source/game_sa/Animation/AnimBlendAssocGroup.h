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
    static void InjectHooks();

    CAnimBlendAssocGroup();
    ~CAnimBlendAssocGroup();

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

private: // Wrappers for hooks
    // 0x4CDE70
    CAnimBlendAssocGroup* Constructor() {
        this->CAnimBlendAssocGroup::CAnimBlendAssocGroup();
        return this;
    }

    // 0x4CE1D0
    CAnimBlendAssocGroup* Destructor() {
        this->CAnimBlendAssocGroup::~CAnimBlendAssocGroup();
        return this;
    }

private:
    CAnimBlock*                  m_AnimBlock{};
    CAnimBlendStaticAssociation* m_Associations{};
    uint32                       m_NumAnimsx{};
    int32                        m_IdOffset{};
    int32                        m_GroupID{-1};
};
VALIDATE_SIZE(CAnimBlendAssocGroup, 0x14);
