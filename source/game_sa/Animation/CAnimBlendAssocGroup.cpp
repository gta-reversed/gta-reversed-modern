/*
Plugin-SDK (Grand Theft Auto San Andreas) header file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

// 0x4CDE70
CAnimBlendAssocGroup::CAnimBlendAssocGroup() {
    plugin::CallMethod<0x4CDE70, CAnimBlendAssocGroup*>(this);
}

// 0x4CE0B0
CAnimBlendAssociation* CAnimBlendAssocGroup::CopyAnimation(char const* AnimName) {
    return plugin::CallMethodAndReturn<CAnimBlendAssociation*, 0x4CE0B0, CAnimBlendAssocGroup*, char const*>(this, AnimName);
}

// 0x4CE130
CAnimBlendAssociation* CAnimBlendAssocGroup::CopyAnimation(uint32 ID) {
    return plugin::CallMethodAndReturn<CAnimBlendAssociation*, 0x4CE130, CAnimBlendAssocGroup*, uint32>(this, ID);
}

// 0x4CE220
void CAnimBlendAssocGroup::CreateAssociations(char const* szBlockName) {
    plugin::CallMethod<0x4CE220, CAnimBlendAssocGroup*, char const*>(this, szBlockName);
}

// 0x4CE6E0
void CAnimBlendAssocGroup::CreateAssociations(char const* AnimName, RpClump* pClump, char** arg3, int32 NumAnimations) {
    plugin::CallMethod<0x4CE6E0, CAnimBlendAssocGroup*, char const*, RpClump*, char**, int32>(this, AnimName, pClump, arg3, NumAnimations);
}

// 0x4CE3B0
void CAnimBlendAssocGroup::CreateAssociations(char const* AnimName, char const* arg2, char const* arg3, int32 arg4) {
    plugin::CallMethod<0x4CE3B0, CAnimBlendAssocGroup*, char const*, char const*, char const*, int32>(this, AnimName, arg2, arg3, arg4);
}

// Converted from thiscall void CAnimBlendAssocGroup::DestroyAssociations() 004CDFF0
void CAnimBlendAssocGroup::DestroyAssociations() {
    plugin::CallMethod<0x4CDFF0, CAnimBlendAssocGroup*>(this);
}

CAnimBlendStaticAssociation* CAnimBlendAssocGroup::GetAnimation(char const* AnimName) {
    return plugin::CallMethodAndReturn<CAnimBlendStaticAssociation*, 0x4CE040, CAnimBlendAssocGroup*, char const*>(this, AnimName);
}

CAnimBlendStaticAssociation* CAnimBlendAssocGroup::GetAnimation(uint32 ID) {
    return plugin::CallMethodAndReturn<CAnimBlendStaticAssociation*, 0x4CE090, CAnimBlendAssocGroup*, uint32>(this, ID);
}

// 0x4CE1B0
uint32 CAnimBlendAssocGroup::GetAnimationId(char const* AnimName) {
    return plugin::CallMethodAndReturn<uint32, 0x4CE1B0, CAnimBlendAssocGroup*, char const*>(this, AnimName);
}

// 0x4CDFB0
void CAnimBlendAssocGroup::InitEmptyAssociations(RpClump* pClump) {
    plugin::CallMethod<0x4CDFB0, CAnimBlendAssocGroup*, RpClump*>(this, pClump);
}

// 0x4CE1D0
CAnimBlendAssocGroup::~CAnimBlendAssocGroup() {
    plugin::CallMethod<0x4CE1D0, CAnimBlendAssocGroup*>(this);
}

