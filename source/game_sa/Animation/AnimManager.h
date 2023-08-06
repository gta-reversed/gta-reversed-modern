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

#include <extensions/ci_string.hpp>

constexpr auto MAX_ANIM_BLOCK_NAME = 16;
constexpr auto NUM_ANIM_ASSOC_GROUPS = 118;
constexpr auto NUM_ANIM_BLOCKS = 180;

class CAnimManager {
public:
    static std::array<AnimAssocDefinition, NUM_ANIM_ASSOC_GROUPS> ms_aAnimAssocDefinitionsX; // replacement
    static inline AnimAssocDefinition (&ms_aAnimAssocDefinitions)[NUM_ANIM_ASSOC_GROUPS] = *(AnimAssocDefinition(*)[NUM_ANIM_ASSOC_GROUPS])0x8AA5A8; // std::array - see SurfaceInfos_c
    static inline uint32& ms_numAnimAssocDefinitions = *(uint32*)0xB4EA28;

    static inline CAnimBlendAssocGroup*& ms_aAnimAssocGroups = *(CAnimBlendAssocGroup**)0xB4EA34;
    static inline uint32& ms_numAnimBlocks = *(uint32*)0xB4EA30;

    static inline std::array<CAnimBlendHierarchy, 2500>& ms_aAnimations = *(std::array<CAnimBlendHierarchy, 2500>*)0xB4EA40;
    static inline int32& ms_numAnimations = *(int32*)0xB4EA2C;

    static inline std::array<CAnimBlock, NUM_ANIM_BLOCKS>& ms_aAnimBlocks = *(std::array<CAnimBlock, NUM_ANIM_BLOCKS>*)0xB5D4A0;
    static inline CLinkList<CAnimBlendHierarchy*>& ms_animCache = *(CLinkList<CAnimBlendHierarchy*>*)0xB5EB20;

public:
    static void InjectHooks();

    static void Initialise();
    static void Shutdown();

    static void LoadAnimFiles();
    static void LoadAnimFile(RwStream* stream, bool loadCompressed, const char (*uncompressedAnimations)[32] = nullptr);
    static void ReadAnimAssociationDefinitions();

    static CAnimBlock* GetAnimationBlock(AssocGroupId animGroup);
    static CAnimBlock* GetAnimationBlock(const char* name);

    static int32 GetAnimationBlockIndex(AssocGroupId animGroup);
    static int32 GetAnimationBlockIndex(CAnimBlock* animBlock);
    static int32 GetAnimationBlockIndex(const char* name);

    static AssocGroupId GetFirstAssocGroup(const char* name);
    static CAnimBlendHierarchy* GetAnimation(uint32 hash, const CAnimBlock* animBlock);
    static CAnimBlendHierarchy* GetAnimation(const char* animName, const CAnimBlock* animBlock);
    static const char* GetAnimGroupName(AssocGroupId groupId);
    static const char* GetAnimBlockName(AssocGroupId groupId);
    static AssocGroupId GetAnimationGroupIdByName(notsa::ci_string_view name);
    static CAnimBlendStaticAssociation* GetAnimAssociation(AssocGroupId groupId, AnimationId animId);
    static CAnimBlendStaticAssociation* GetAnimAssociation(AssocGroupId groupId, const char* animName);
    static CAnimBlendAssociation* AddAnimationToClump(RpClump* clump, CAnimBlendAssociation* anim); // NOTSA - Internal
    static int32 GetNumRefsToAnimBlock(int32 index);

    static CAnimBlendAssociation* CreateAnimAssociation(AssocGroupId groupId, AnimationId animId);

    static CAnimBlendAssociation* AddAnimation(RpClump* clump, AssocGroupId groupId, AnimationId animId);
    static CAnimBlendAssociation* AddAnimation(RpClump* clump, CAnimBlendHierarchy* hier, int32 clumpAssocFlag);
    static CAnimBlendAssociation* AddAnimationAndSync(RpClump* clump, CAnimBlendAssociation* animBlendAssoc, AssocGroupId groupId, AnimationId animId);
    static AnimAssocDefinition* AddAnimAssocDefinition(const char* groupName, const char* blockName, uint32 modelIndex, uint32 animsCount, AnimDescriptor* descriptor);
    static void AddAnimToAssocDefinition(AnimAssocDefinition* definition, const char* animName);
    static void AddAnimBlockRef(int32 index);

    static void CreateAnimAssocGroups();
    static int32 RegisterAnimBlock(const char* name);
    static void RemoveLastAnimFile();
    static void RemoveAnimBlock(int32 index);
    static void RemoveAnimBlockRef(int32 index);
    static void RemoveAnimBlockRefWithoutDelete(int32 index);
    static void RemoveFromUncompressedCache(CAnimBlendHierarchy* hier);
    static void UncompressAnimation(CAnimBlendHierarchy* hier);
    static CAnimBlendAssociation* BlendAnimation(RpClump* clump, CAnimBlendHierarchy* animBlendHier, int32 flags, float clumpAssocBlendData = 8.f);
    static CAnimBlendAssociation* BlendAnimation(RpClump* clump, AssocGroupId groupId, AnimationId animId, float clumpAssocBlendData = 8.f);

    /// NOTSA. Get random gangtalk anim
    static AnimationId GetRandomGangTalkAnim();

    static auto GetAnimBlocks() { return ms_aAnimBlocks | rng::views::take(ms_numAnimBlocks); }
    static auto GetAssocGroups() { return std::span{ms_aAnimAssocGroups, ms_numAnimAssocDefinitions}; }
    static auto GetAssocGroupDefs() { return std::span{ms_aAnimAssocDefinitions, ms_numAnimAssocDefinitions}; }
private:
    static void LoadAnimFile_ANPK(RwStream* stream, bool compress, const char (*uncompressedAnims)[32]);
    static void LoadAnimFile_ANP23(RwStream* stream, bool compress, bool isANP3);
};
