/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CAnimationStyleDescriptor.h"
#include "CAnimBlendAssocGroup.h"
#include "CAnimBlendAssociation.h"
#include "CAnimBlock.h"


class  CAnimManager {
public:
    static void CAnimManager::InjectHooks();
    static CAnimBlock* GetAnimationBlock(std::int32_t animGroup) { return ms_aAnimAssocGroups[animGroup].m_pAnimBlock; }
    static std::uint32_t GetAnimationBlockIndex(std::uint32_t animGroup) { return GetAnimationBlock(animGroup) - ms_aAnimBlocks; }
	static CAnimBlock* GetAnimationBlock(char const* name);
    static std::uint32_t GetAnimationBlockIndex(char const* name);
	static int GetFirstAssocGroup(char const* basename);
	static CAnimBlendHierarchy* GetAnimation(unsigned int hash, CAnimBlock const* ifp);
	static CAnimBlendHierarchy* GetAnimation(char const* animName, CAnimBlock const* ifp);
	static char* GetAnimGroupName(int AssocGroupId);
	static char* GetAnimBlockName(int AssocGroupId);
	static CAnimBlendAssociation* CreateAnimAssociation(int AssocGroupId, int AnimationId);
	static CAnimBlendStaticAssociation* GetAnimAssociation(int AssocGroupId, int AnimationId);
	static CAnimBlendStaticAssociation* GetAnimAssociation(int AssocGroupId, char const* arg2);
	static CAnimBlendAssociation* AddAnimation(RpClump* clump, int AssocGroupId, int AnimationId);
	static CAnimBlendAssociation* AddAnimation(RpClump* clump, CAnimBlendHierarchy* pAnimBlendHier, int clumpAssocFlag);
	static CAnimBlendAssociation* AddAnimationAndSync(RpClump* clump, CAnimBlendAssociation* pAnimBlendAssoc, int AssocGroupId, int AnimationId);
	static CAnimationStyleDescriptor* AddAnimAssocDefinition(char const* groupName, char const* blockName, unsigned int arg3, unsigned int animsCount, void* pAnimDescriptor);
	static void* AddAnimToAssocDefinition(void* pAnimAssocDefinition, char const* arg2);
	static void CreateAnimAssocGroups();
	static int RegisterAnimBlock(char const* name);
	static void RemoveLastAnimFile();
	static void RemoveAnimBlock(int index);
	static void AddAnimBlockRef(int index);
	static void RemoveAnimBlockRef(int index);
	static void RemoveAnimBlockRefWithoutDelete(int index);
	static int GetNumRefsToAnimBlock(int index);
	static void Shutdown();
	static void UncompressAnimation(CAnimBlendHierarchy* pAnimBlendHier);
	static void RemoveFromUncompressedCache(CAnimBlendHierarchy* pAnimBlendHier);
	static CAnimBlendAssociation* BlendAnimation(RpClump* clump, CAnimBlendHierarchy* pAnimBlendHier, int flags, float clumpAssocBlendData);
	static CAnimBlendAssociation* BlendAnimation(RpClump* clump, int AssocGroupId, int AnimationId, float clumpAssocBlendData);
	static void LoadAnimFile(RwStream* stream, bool loadCompressed, char const(*uncompressedAnimations)[32]);
	static void LoadAnimFiles();
	static void ReadAnimAssociationDefinitions();
	static void Initialise();


	static CAnimationStyleDescriptor* ms_aAnimAssocDefinitions;		 // CAnimationStyleDescriptor CAnimManager__ms_aAnimAssocDefinitions[118];
	static CAnimBlendAssocGroup*& ms_aAnimAssocGroups;
	static CAnimBlendHierarchy* ms_aAnimations;							// CAnimBlendHierarchy CAnimManager__ms_aAnimations[2500];	
	static CAnimBlock* ms_aAnimBlocks;				                       // CAnimBlock CAnimManager__ms_aAnimBlocks[180];			
	static CAnimBlendHierarchy* ms_animCache;                        
	static int& ms_numAnimAssocDefinitions;
	static int& ms_numAnimBlocks;
	static int& ms_numAnimations;

};
