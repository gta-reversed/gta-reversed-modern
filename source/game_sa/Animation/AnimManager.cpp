/*
Plugin-SDK (Grand Theft Auto) source file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

#include "AnimManager.h"

CAnimationStyleDescriptor* CAnimManager::ms_aAnimAssocDefinitions = (CAnimationStyleDescriptor*)0x8AA5A8;
CAnimBlendAssocGroup*& CAnimManager::ms_aAnimAssocGroups = *(CAnimBlendAssocGroup**)0xB4EA34;
CAnimBlendHierarchy* CAnimManager::ms_aAnimations = (CAnimBlendHierarchy*)0xB4EA40;
CAnimBlock* CAnimManager::ms_aAnimBlocks = (CAnimBlock*)0xB5D4A0;
CAnimBlendHierarchy* CAnimManager::ms_animCache = (CAnimBlendHierarchy*)0xB5EB20;
int32& CAnimManager::ms_numAnimAssocDefinitions = *(int32*)0xB4EA28;
int32& CAnimManager::ms_numAnimBlocks = *(int32*)0xB4EA30;
int32& CAnimManager::ms_numAnimations = *(int32*)0xB4EA2C;

void CAnimManager::InjectHooks() {
    CAnimBlendAssociation::InjectHooks();
}

// 0x5BF6B0
void CAnimManager::Initialise() {
    plugin::Call<0x5BF6B0>();
}

// 0x4D4130
void CAnimManager::Shutdown() {
    plugin::Call<0x4D4130>();
}

// 0x4D3940
CAnimBlock* CAnimManager::GetAnimationBlock(const char* name) {
    return plugin::CallAndReturn<CAnimBlock*, 0x4D3940, const char*>(name);
}

// 0x4D3990
uint32 CAnimManager::GetAnimationBlockIndex(const char* name) {
    return plugin::CallAndReturn<int32, 0x4D3990, const char*>(name);
}

// 0x4D39B0
int32 CAnimManager::GetFirstAssocGroup(const char* basename) {
    return plugin::CallAndReturn<int32, 0x4D39B0, const char*>(basename);
}

// 0x4D39F0
CAnimBlendHierarchy* CAnimManager::GetAnimation(uint32 hash, CAnimBlock const* ifp) {
    return plugin::CallAndReturn<CAnimBlendHierarchy*, 0x4D39F0, uint32, CAnimBlock const*>(hash, ifp);
}

// 0x4D42F0
CAnimBlendHierarchy* CAnimManager::GetAnimation(const char* animName, CAnimBlock const* ifp) {
    return plugin::CallAndReturn<CAnimBlendHierarchy*, 0x4D42F0, const char*, CAnimBlock const*>(animName, ifp);
}

// 0x4D3A20
char* CAnimManager::GetAnimGroupName(AssocGroupId groupId) {
    return plugin::CallAndReturn<char*, 0x4D3A20, AssocGroupId>(groupId);
}

// 0x4D3A30
char* CAnimManager::GetAnimBlockName(AssocGroupId groupId) {
    return plugin::CallAndReturn<char*, 0x4D3A30, AssocGroupId>(groupId);
}

// 0x4D3A40
CAnimBlendAssociation* CAnimManager::CreateAnimAssociation(AssocGroupId groupId, AnimationId animId) {
    return plugin::CallAndReturn<CAnimBlendAssociation*, 0x4D3A40, AssocGroupId, AnimationId>(groupId, animId);
}

// 0x4D3A60
CAnimBlendStaticAssociation* CAnimManager::GetAnimAssociation(AssocGroupId groupId, AnimationId animId) {
    return plugin::CallAndReturn<CAnimBlendStaticAssociation*, 0x4D3A60, AssocGroupId, AnimationId>(groupId, animId);
}

// 0x4D3A80
CAnimBlendStaticAssociation* CAnimManager::GetAnimAssociation(AssocGroupId groupId, const char* arg2) {
    return plugin::CallAndReturn<CAnimBlendStaticAssociation*, 0x4D3A80, AssocGroupId, const char*>(groupId, arg2);
}

// 0x4D3AA0
CAnimBlendAssociation* CAnimManager::AddAnimation(RpClump* clump, AssocGroupId groupId, AnimationId animId) {
    return plugin::CallAndReturn<CAnimBlendAssociation*, 0x4D3AA0, RpClump*, AssocGroupId, AnimationId>(clump, groupId, animId);
}

// 0x4D4330
CAnimBlendAssociation* CAnimManager::AddAnimation(RpClump* clump, CAnimBlendHierarchy* pAnimBlendHier, int32 clumpAssocFlag) {
    return plugin::CallAndReturn<CAnimBlendAssociation*, 0x4D4330, RpClump*, CAnimBlendHierarchy*, int32>(clump, pAnimBlendHier, clumpAssocFlag);
}

// 0x4D3B30
CAnimBlendAssociation* CAnimManager::AddAnimationAndSync(RpClump* clump, CAnimBlendAssociation* animBlendAssoc, AssocGroupId groupId, AnimationId animId) {
    return plugin::CallAndReturn<CAnimBlendAssociation*, 0x4D3B30, RpClump*, CAnimBlendAssociation*, AssocGroupId, AnimationId>(clump, animBlendAssoc, groupId, animId);
}

// 0x4D3BA0
CAnimationStyleDescriptor* CAnimManager::AddAnimAssocDefinition(const char* groupName, const char* blockName, uint32 arg3, uint32 animsCount, void* pAnimDescriptor) {
    return plugin::CallAndReturn<CAnimationStyleDescriptor*, 0x4D3BA0, const char*, const char*, uint32, uint32, void*>(groupName, blockName, arg3, animsCount, pAnimDescriptor);
}

// 0x4D3C80
void* CAnimManager::AddAnimToAssocDefinition(void* pAnimAssocDefinition, const char* arg2) {
    return plugin::CallAndReturn<void*, 0x4D3C80, void*, const char*>(pAnimAssocDefinition, arg2);
}

// 0x4D3CC0
void CAnimManager::CreateAnimAssocGroups() {
    plugin::Call<0x4D3CC0>();
}

// 0x4D3E50
int32 CAnimManager::RegisterAnimBlock(const char* name) {
    return plugin::CallAndReturn<int32, 0x4D3E50, const char*>(name);
}

// 0x4D3ED0
void CAnimManager::RemoveLastAnimFile() {
    plugin::Call<0x4D3ED0>();
}

// 0x4D3F40
void CAnimManager::RemoveAnimBlock(int32 index) {
    plugin::Call<0x4D3F40, int32>(index);
}

// 0x4D3FB0
void CAnimManager::AddAnimBlockRef(int32 index) {
    plugin::Call<0x4D3FB0, int32>(index);
}

// 0x4D3FD0
void CAnimManager::RemoveAnimBlockRef(int32 index) {
    plugin::Call<0x4D3FD0, int32>(index);
}

// 0x4D3FF0
void CAnimManager::RemoveAnimBlockRefWithoutDelete(int32 index) {
    plugin::Call<0x4D3FF0, int32>(index);
}

// 0x4D4010
int32 CAnimManager::GetNumRefsToAnimBlock(int32 index) {
    return plugin::CallAndReturn<int32, 0x4D4010, int32>(index);
}

// 0x4D41C0
void CAnimManager::UncompressAnimation(CAnimBlendHierarchy* pAnimBlendHier) {
    plugin::Call<0x4D41C0, CAnimBlendHierarchy*>(pAnimBlendHier);
}

// 0x4D42A0
void CAnimManager::RemoveFromUncompressedCache(CAnimBlendHierarchy* pAnimBlendHier) {
    plugin::Call<0x4D42A0, CAnimBlendHierarchy*>(pAnimBlendHier);
}

// 0x4D4410
CAnimBlendAssociation* CAnimManager::BlendAnimation(RpClump* clump, CAnimBlendHierarchy* animBlendHier, int32 flags, float clumpAssocBlendData) {
    return plugin::CallAndReturn<CAnimBlendAssociation*, 0x4D4410, RpClump*, CAnimBlendHierarchy*, int32, float>(clump, animBlendHier, flags, clumpAssocBlendData);
}

// 0x4D4610
CAnimBlendAssociation* CAnimManager::BlendAnimation(RpClump* clump, AssocGroupId groupId, AnimationId animId, float clumpAssocBlendData) {
    return plugin::CallAndReturn<CAnimBlendAssociation*, 0x4D4610, RpClump*, AssocGroupId, AnimationId, float>(clump, groupId, animId, clumpAssocBlendData);
}

// 0x4D47F0
void CAnimManager::LoadAnimFile(RwStream* stream, bool loadCompressed, char const(*uncompressedAnimations)[32]) {
    plugin::Call<0x4D47F0, RwStream*, bool, char const(*)[32]>(stream, loadCompressed, uncompressedAnimations);
}

// 0x4D5620
void CAnimManager::LoadAnimFiles() {
    plugin::Call<0x4D5620>();
}

// 0x5BC910
void CAnimManager::ReadAnimAssociationDefinitions() {
    plugin::Call<0x5BC910>();
}


