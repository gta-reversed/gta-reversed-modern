/*
Plugin-SDK (Grand Theft Auto) source file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

void CAnimManager::InjectHooks()
{
    CAnimBlendAssociation::InjectHooks();
}

CAnimationStyleDescriptor* CAnimManager::ms_aAnimAssocDefinitions = (CAnimationStyleDescriptor*)0x8AA5A8;
CAnimBlendAssocGroup*& CAnimManager::ms_aAnimAssocGroups = *(CAnimBlendAssocGroup**)0xB4EA34;
CAnimBlendHierarchy* CAnimManager::ms_aAnimations = (CAnimBlendHierarchy*)0xB4EA40;
CAnimBlock* CAnimManager::ms_aAnimBlocks = (CAnimBlock*)0xB5D4A0;
CAnimBlendHierarchy* CAnimManager::ms_animCache = (CAnimBlendHierarchy*)0xB5EB20;
int& CAnimManager::ms_numAnimAssocDefinitions = *(int*)0xB4EA28;
int& CAnimManager::ms_numAnimBlocks = *(int*)0xB4EA30;
int& CAnimManager::ms_numAnimations = *(int*)0xB4EA2C;

// Converted from cdecl CAnimBlock* CAnimManager::GetAnimationBlock(char const* name) 0x4D3940
CAnimBlock* CAnimManager::GetAnimationBlock(char const* name) {
    return plugin::CallAndReturn<CAnimBlock*, 0x4D3940, char const*>(name);
}

// Converted from cdecl int CAnimManager::GetAnimationBlockIndex(char const* name) 0x4D3990
std::uint32_t CAnimManager::GetAnimationBlockIndex(char const* name) {
    return plugin::CallAndReturn<int, 0x4D3990, char const*>(name);
}

// Converted from cdecl int CAnimManager::GetFirstAssocGroup(char const* basename) 0x4D39B0
int CAnimManager::GetFirstAssocGroup(char const* basename) {
    return plugin::CallAndReturn<int, 0x4D39B0, char const*>(basename);
}

// Converted from cdecl CAnimBlendHierarchy* CAnimManager::GetAnimation(uint hash,CAnimBlock const* ifp) 0x4D39F0
CAnimBlendHierarchy* CAnimManager::GetAnimation(unsigned int hash, CAnimBlock const* ifp) {
    return plugin::CallAndReturn<CAnimBlendHierarchy*, 0x4D39F0, unsigned int, CAnimBlock const*>(hash, ifp);
}

// Converted from cdecl CAnimBlendHierarchy* CAnimManager::GetAnimation(char const* animName,CAnimBlock const* ifp) 0x4D42F0
CAnimBlendHierarchy* CAnimManager::GetAnimation(char const* animName, CAnimBlock const* ifp) {
    return plugin::CallAndReturn<CAnimBlendHierarchy*, 0x4D42F0, char const*, CAnimBlock const*>(animName, ifp);
}

// Converted from cdecl char* CAnimManager::GetAnimGroupName(int AssocGroupId) 0x4D3A20
char* CAnimManager::GetAnimGroupName(int AssocGroupId) {
    return plugin::CallAndReturn<char*, 0x4D3A20, int>(AssocGroupId);
}

// Converted from cdecl char* CAnimManager::GetAnimBlockName(int AssocGroupId) 0x4D3A30
char* CAnimManager::GetAnimBlockName(int AssocGroupId) {
    return plugin::CallAndReturn<char*, 0x4D3A30, int>(AssocGroupId);
}

// Converted from cdecl CAnimBlendAssociation* CAnimManager::CreateAnimAssociation(int AssocGroupId,int AnimationId) 0x4D3A40
CAnimBlendAssociation* CAnimManager::CreateAnimAssociation(int AssocGroupId, int AnimationId) {
    return plugin::CallAndReturn<CAnimBlendAssociation*, 0x4D3A40, int, int>(AssocGroupId, AnimationId);
}

// Converted from cdecl CAnimBlendStaticAssociation* CAnimManager::GetAnimAssociation(int AssocGroupId, int AnimationId) 0x4D3A60
CAnimBlendStaticAssociation* CAnimManager::GetAnimAssociation(int AssocGroupId, int AnimationId) {
    return plugin::CallAndReturn<CAnimBlendStaticAssociation*, 0x4D3A60, int, int>(AssocGroupId, AnimationId);
}

// Converted from cdecl CAnimBlendStaticAssociation* CAnimManager::GetAnimAssociation(int AssocGroupId,char const* arg2) 0x4D3A80
CAnimBlendStaticAssociation* CAnimManager::GetAnimAssociation(int AssocGroupId, char const* arg2) {
    return plugin::CallAndReturn<CAnimBlendStaticAssociation*, 0x4D3A80, int, char const*>(AssocGroupId, arg2);
}

// Converted from cdecl CAnimBlendAssociation* CAnimManager::AddAnimation(RpClump * clump,int AssocGroupId,int AnimationId) 0x4D3AA0
CAnimBlendAssociation* CAnimManager::AddAnimation(RpClump* clump, int AssocGroupId, int AnimationId) {
    return plugin::CallAndReturn<CAnimBlendAssociation*, 0x4D3AA0, RpClump*, int, int>(clump, AssocGroupId, AnimationId);
}

// Converted from cdecl CAnimBlendAssociation* CAnimManager::AddAnimation(RpClump * clump,CAnimBlendHierarchy * pAnimBlendHier,int clumpAssocFlag) 0x4D4330
CAnimBlendAssociation* CAnimManager::AddAnimation(RpClump* clump, CAnimBlendHierarchy* pAnimBlendHier, int clumpAssocFlag) {
    return plugin::CallAndReturn<CAnimBlendAssociation*, 0x4D4330, RpClump*, CAnimBlendHierarchy*, int>(clump, pAnimBlendHier, clumpAssocFlag);
}

// Converted from cdecl CAnimBlendAssociation* CAnimManager::AddAnimationAndSync(RpClump * clump,CAnimBlendAssociation * pAnimBlendAssoc,int AssocGroupId,int AnimationId) 0x4D3B30
CAnimBlendAssociation* CAnimManager::AddAnimationAndSync(RpClump* clump, CAnimBlendAssociation* pAnimBlendAssoc, int AssocGroupId, int AnimationId) {
    return plugin::CallAndReturn<CAnimBlendAssociation*, 0x4D3B30, RpClump*, CAnimBlendAssociation*, int, int>(clump, pAnimBlendAssoc, AssocGroupId, AnimationId);
}

// Converted from cdecl CAnimationStyleDescriptor* CAnimManager::AddAnimAssocDefinition(char const* groupName,char const* blockName,uint arg3,uint animsCount,void* pAnimDescriptor) 0x4D3BA0
CAnimationStyleDescriptor* CAnimManager::AddAnimAssocDefinition(char const* groupName, char const* blockName, unsigned int arg3, unsigned int animsCount, void* pAnimDescriptor) {
    return plugin::CallAndReturn<CAnimationStyleDescriptor*, 0x4D3BA0, char const*, char const*, unsigned int, unsigned int, void*>(groupName, blockName, arg3, animsCount, pAnimDescriptor);
}

// Converted from cdecl void* CAnimManager::AddAnimToAssocDefinition(void* pAnimAssocDefinition,char const* arg2) 0x4D3C80
void* CAnimManager::AddAnimToAssocDefinition(void* pAnimAssocDefinition, char const* arg2) {
    return plugin::CallAndReturn<void*, 0x4D3C80, void*, char const*>(pAnimAssocDefinition, arg2);
}

// Converted from cdecl void CAnimManager::CreateAnimAssocGroups(void) 0x4D3CC0
void CAnimManager::CreateAnimAssocGroups() {
    plugin::Call<0x4D3CC0>();
}

// Converted from cdecl int CAnimManager::RegisterAnimBlock(char const* name) 0x4D3E50
int CAnimManager::RegisterAnimBlock(char const* name) {
    return plugin::CallAndReturn<int, 0x4D3E50, char const*>(name);
}

// Converted from cdecl void CAnimManager::RemoveLastAnimFile(void) 0x4D3ED0
void CAnimManager::RemoveLastAnimFile() {
    plugin::Call<0x4D3ED0>();
}

// Converted from cdecl void CAnimManager::RemoveAnimBlock(int index) 0x4D3F40
void CAnimManager::RemoveAnimBlock(int index) {
    plugin::Call<0x4D3F40, int>(index);
}

// Converted from cdecl void CAnimManager::AddAnimBlockRef(int index) 0x4D3FB0
void CAnimManager::AddAnimBlockRef(int index) {
    plugin::Call<0x4D3FB0, int>(index);
}

// Converted from cdecl void CAnimManager::RemoveAnimBlockRef(int index) 0x4D3FD0
void CAnimManager::RemoveAnimBlockRef(int index) {
    plugin::Call<0x4D3FD0, int>(index);
}

// Converted from cdecl void CAnimManager::RemoveAnimBlockRefWithoutDelete(int index) 0x4D3FF0
void CAnimManager::RemoveAnimBlockRefWithoutDelete(int index) {
    plugin::Call<0x4D3FF0, int>(index);
}

// Converted from cdecl int CAnimManager::GetNumRefsToAnimBlock(int index) 0x4D4010
int CAnimManager::GetNumRefsToAnimBlock(int index) {
    return plugin::CallAndReturn<int, 0x4D4010, int>(index);
}

// Converted from cdecl void CAnimManager::Shutdown(void) 0x4D4130
void CAnimManager::Shutdown() {
    plugin::Call<0x4D4130>();
}

// Converted from cdecl void CAnimManager::UncompressAnimation(CAnimBlendHierarchy * pAnimBlendHier) 0x4D41C0
void CAnimManager::UncompressAnimation(CAnimBlendHierarchy* pAnimBlendHier) {
    plugin::Call<0x4D41C0, CAnimBlendHierarchy*>(pAnimBlendHier);
}

// Converted from cdecl void CAnimManager::RemoveFromUncompressedCache(CAnimBlendHierarchy *pAnimBlendHier) 0x4D42A0
void CAnimManager::RemoveFromUncompressedCache(CAnimBlendHierarchy* pAnimBlendHier) {
    plugin::Call<0x4D42A0, CAnimBlendHierarchy*>(pAnimBlendHier);
}

// Converted from cdecl CAnimBlendAssociation* CAnimManager::BlendAnimation(RpClump * clump,CAnimBlendHierarchy *pAnimBlendHier,int flags,float clumpAssocBlendData) 0x4D4410
CAnimBlendAssociation* CAnimManager::BlendAnimation(RpClump* clump, CAnimBlendHierarchy* pAnimBlendHier, int flags, float clumpAssocBlendData) {
    return plugin::CallAndReturn<CAnimBlendAssociation*, 0x4D4410, RpClump*, CAnimBlendHierarchy*, int, float>(clump, pAnimBlendHier, flags, clumpAssocBlendData);
}

// Converted from cdecl CAnimBlendAssociation* CAnimManager::BlendAnimation(RpClump * clump,int AssocGroupId,int AnimationId,float clumpAssocBlendData) 0x4D4610
CAnimBlendAssociation* CAnimManager::BlendAnimation(RpClump* clump, int AssocGroupId, int AnimationId, float clumpAssocBlendData) {
    return plugin::CallAndReturn<CAnimBlendAssociation*, 0x4D4610, RpClump*, int, int, float>(clump, AssocGroupId, AnimationId, clumpAssocBlendData);
}

// Converted from cdecl void CAnimManager::LoadAnimFile(RwStream * stream,bool arg1,char const* string) 0x4D47F0
void CAnimManager::LoadAnimFile(RwStream* stream, bool loadCompressed, char const(*uncompressedAnimations)[32]) {
    plugin::Call<0x4D47F0, RwStream*, bool, char const(*)[32]>(stream, loadCompressed, uncompressedAnimations);
}

// Converted from cdecl void CAnimManager::LoadAnimFiles(void) 0x4D5620
void CAnimManager::LoadAnimFiles() {
    plugin::Call<0x4D5620>();
}

// Converted from cdecl void CAnimManager::ReadAnimAssociationDefinitions(void) 0x5BC910
void CAnimManager::ReadAnimAssociationDefinitions() {
    plugin::Call<0x5BC910>();
}

// Converted from cdecl void CAnimManager::Initialise(void) 0x5BF6B0
void CAnimManager::Initialise() {
    plugin::Call<0x5BF6B0>();
}

