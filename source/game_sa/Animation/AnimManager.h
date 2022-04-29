/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "AnimationStyleDescriptor.h"
#include "AnimBlendAssocGroup.h"
#include "AnimBlendAssociation.h"
#include "AnimBlock.h"

class CAnimManager {
public:
    static CAnimationStyleDescriptor* ms_aAnimAssocDefinitions; // CAnimationStyleDescriptor CAnimManager__ms_aAnimAssocDefinitions[118];
    static CAnimBlendAssocGroup*& ms_aAnimAssocGroups;
    static CAnimBlendHierarchy* ms_aAnimations; // CAnimBlendHierarchy CAnimManager__ms_aAnimations[2500];
    static CAnimBlock* ms_aAnimBlocks;          // CAnimBlock CAnimManager__ms_aAnimBlocks[180];
    static CAnimBlendHierarchy* ms_animCache;
    static int32& ms_numAnimAssocDefinitions;
    static int32& ms_numAnimBlocks;
    static int32& ms_numAnimations;

public:
    static void InjectHooks();

    static void Initialise();
    static void Shutdown();

    static void LoadAnimFile(RwStream* stream, bool loadCompressed, const char (*uncompressedAnimations)[32]);
    static void LoadAnimFiles();
    static void ReadAnimAssociationDefinitions();

    static CAnimBlock* GetAnimationBlock(int32 animGroup) { return ms_aAnimAssocGroups[animGroup].m_pAnimBlock; }
    static uint32 GetAnimationBlockIndex(uint32 animGroup) { return GetAnimationBlock(animGroup) - ms_aAnimBlocks; }
    static CAnimBlock* GetAnimationBlock(const char* name);
    static int32 GetAnimationBlockIndex(const char* name);
    static int32 GetFirstAssocGroup(const char* basename);
    static CAnimBlendHierarchy* GetAnimation(uint32 hash, const CAnimBlock* ifp);
    static CAnimBlendHierarchy* GetAnimation(const char* animName, const CAnimBlock* ifp);
    static char* GetAnimGroupName(AssocGroupId groupId);
    static char* GetAnimBlockName(AssocGroupId groupId);
    static AssocGroupId GetAnimationGroupId(const char* name);
    static CAnimBlendStaticAssociation* GetAnimAssociation(AssocGroupId groupId, AnimationId animId);
    static CAnimBlendStaticAssociation* GetAnimAssociation(AssocGroupId groupId, const char* arg2);
    static int32 GetNumRefsToAnimBlock(int32 index);

    static CAnimBlendAssociation* CreateAnimAssociation(AssocGroupId groupId, AnimationId animId);

    static CAnimBlendAssociation* AddAnimation(RpClump* clump, AssocGroupId groupId, AnimationId animId);
    static CAnimBlendAssociation* AddAnimation(RpClump* clump, CAnimBlendHierarchy* pAnimBlendHier, int32 clumpAssocFlag);
    static CAnimBlendAssociation* AddAnimationAndSync(RpClump* clump, CAnimBlendAssociation* animBlendAssoc, AssocGroupId groupId, AnimationId animId);
    static CAnimationStyleDescriptor* AddAnimAssocDefinition(const char* groupName, const char* blockName, uint32 arg3, uint32 animsCount, void* pAnimDescriptor);
    static void* AddAnimToAssocDefinition(void* pAnimAssocDefinition, const char* arg2);
    static void AddAnimBlockRef(int32 index);

    static void CreateAnimAssocGroups();
    static int32 RegisterAnimBlock(const char* name);
    static void RemoveLastAnimFile();
    static void RemoveAnimBlock(int32 index);
    static void RemoveAnimBlockRef(int32 index);
    static void RemoveAnimBlockRefWithoutDelete(int32 index);
    static void RemoveFromUncompressedCache(CAnimBlendHierarchy* pAnimBlendHier);
    static void UncompressAnimation(CAnimBlendHierarchy* pAnimBlendHier);
    static CAnimBlendAssociation* BlendAnimation(RpClump* clump, CAnimBlendHierarchy* animBlendHier, int32 flags, float clumpAssocBlendData);
    static CAnimBlendAssociation* BlendAnimation(RpClump* clump, AssocGroupId groupId, AnimationId animId, float clumpAssocBlendData);
};
