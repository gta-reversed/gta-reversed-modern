/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

#include "AnimBlendAssocGroup.h"

// 0x4CDE70
CAnimBlendAssocGroup::CAnimBlendAssocGroup() {
    plugin::CallMethod<0x4CDE70, CAnimBlendAssocGroup*>(this);
}

// 0x4CE0B0
CAnimBlendAssociation* CAnimBlendAssocGroup::CopyAnimation(const char* AnimName) {
    return plugin::CallMethodAndReturn<CAnimBlendAssociation*, 0x4CE0B0, CAnimBlendAssocGroup*, const char*>(this, AnimName);
}

// 0x4CE130
CAnimBlendAssociation* CAnimBlendAssocGroup::CopyAnimation(uint32 ID) {
    return plugin::CallMethodAndReturn<CAnimBlendAssociation*, 0x4CE130, CAnimBlendAssocGroup*, uint32>(this, ID);
}

// 0x4CE220
void CAnimBlendAssocGroup::CreateAssociations(const char* szBlockName) {
    plugin::CallMethod<0x4CE220, CAnimBlendAssocGroup*, const char*>(this, szBlockName);
}

// 0x4CE6E0
void CAnimBlendAssocGroup::CreateAssociations(const char* AnimName, RpClump* clump, char** arg3, int32 NumAnimations) {
    plugin::CallMethod<0x4CE6E0, CAnimBlendAssocGroup*, const char*, RpClump*, char**, int32>(this, AnimName, clump, arg3, NumAnimations);
}

// 0x4CE3B0
void CAnimBlendAssocGroup::CreateAssociations(const char* AnimName, const char* arg2, const char* arg3, uint32 strStorageSz) {
    plugin::CallMethod<0x4CE3B0, CAnimBlendAssocGroup*, const char*, const char*, const char*, int32>(this, AnimName, arg2, arg3, strStorageSz);
}

// 0x4CDFF0
void CAnimBlendAssocGroup::DestroyAssociations() {
    plugin::CallMethod<0x4CDFF0, CAnimBlendAssocGroup*>(this);
}

CAnimBlendStaticAssociation* CAnimBlendAssocGroup::GetAnimation(const char* AnimName) {
    return plugin::CallMethodAndReturn<CAnimBlendStaticAssociation*, 0x4CE040, CAnimBlendAssocGroup*, const char*>(this, AnimName);
}

CAnimBlendStaticAssociation* CAnimBlendAssocGroup::GetAnimation(uint32 ID) {
    return plugin::CallMethodAndReturn<CAnimBlendStaticAssociation*, 0x4CE090, CAnimBlendAssocGroup*, uint32>(this, ID);
}

// 0x4CE1B0
uint32 CAnimBlendAssocGroup::GetAnimationId(const char* AnimName) {
    return plugin::CallMethodAndReturn<uint32, 0x4CE1B0, CAnimBlendAssocGroup*, const char*>(this, AnimName);
}

// 0x4CDFB0
void CAnimBlendAssocGroup::InitEmptyAssociations(RpClump* clump) {
    plugin::CallMethod<0x4CDFB0, CAnimBlendAssocGroup*, RpClump*>(this, clump);
}

// 0x4CE1D0
CAnimBlendAssocGroup::~CAnimBlendAssocGroup() {
    plugin::CallMethod<0x4CE1D0, CAnimBlendAssocGroup*>(this);
}

