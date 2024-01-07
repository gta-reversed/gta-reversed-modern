/*
Plugin-SDK file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

#include <extensions/ci_string.hpp>

#include "AnimManager.h"
#include "AnimAssocDescriptions.h"

void CAnimManager::InjectHooks() {
    RH_ScopedClass(CAnimManager);
    RH_ScopedCategory("Animation");

    RH_ScopedInstall(Initialise, 0x5BF6B0);
    RH_ScopedInstall(ReadAnimAssociationDefinitions, 0x5BC910);
    RH_ScopedInstall(Shutdown, 0x4D4130);
    RH_ScopedOverloadedInstall(GetAnimationBlock, "", 0x4D3940, CAnimBlock*(*)(const char*));
    RH_ScopedOverloadedInstall(GetAnimationBlockIndex, "by-name", 0x4D3990, int32(*)(const char*));
    RH_ScopedInstall(GetFirstAssocGroup, 0x4D39B0);
    RH_ScopedOverloadedInstall(GetAnimation, "0", 0x4D39F0, CAnimBlendHierarchy*(*)(uint32, const CAnimBlock*));
    RH_ScopedOverloadedInstall(GetAnimation, "1", 0x4D42F0, CAnimBlendHierarchy*(*)(const char*, const CAnimBlock*));
    RH_ScopedInstall(GetAnimGroupName, 0x4D3A20);
    RH_ScopedInstall(GetAnimBlockName, 0x4D3A30);
    RH_ScopedInstall(CreateAnimAssociation, 0x4D3A40);
    RH_ScopedOverloadedInstall(GetAnimAssociation, "by-id", 0x4D3A60, CAnimBlendStaticAssociation*(*)(AssocGroupId, AnimationId));
    RH_ScopedOverloadedInstall(GetAnimAssociation, "by-name", 0x4D3A80, CAnimBlendStaticAssociation*(*)(AssocGroupId, const char*));
    RH_ScopedOverloadedInstall(AddAnimation, "id", 0x4D3AA0, CAnimBlendAssociation*(*)(RpClump*, AssocGroupId, AnimationId));
    RH_ScopedOverloadedInstall(AddAnimation, "hier", 0x4D4330, CAnimBlendAssociation*(*)(RpClump*, CAnimBlendHierarchy*, int32));
    RH_ScopedInstall(AddAnimationAndSync, 0x4D3B30);
    RH_ScopedInstall(AddAnimAssocDefinition, 0x4D3BA0);
    RH_ScopedInstall(AddAnimToAssocDefinition, 0x4D3C80);
    RH_ScopedInstall(CreateAnimAssocGroups, 0x4D3CC0);
    RH_ScopedInstall(RegisterAnimBlock, 0x4D3E50);
    RH_ScopedInstall(RemoveLastAnimFile, 0x4D3ED0);
    RH_ScopedInstall(RemoveAnimBlock, 0x4D3F40);
    RH_ScopedInstall(AddAnimBlockRef, 0x4D3FB0);
    RH_ScopedInstall(RemoveAnimBlockRefWithoutDelete, 0x4D3FF0);
    RH_ScopedInstall(GetNumRefsToAnimBlock, 0x4D4010);
    RH_ScopedInstall(UncompressAnimation, 0x4D41C0);
    RH_ScopedInstall(RemoveFromUncompressedCache, 0x4D42A0);
    RH_ScopedOverloadedInstall(BlendAnimation, "id", 0x4D4610, CAnimBlendAssociation*(*)(RpClump*, AssocGroupId, AnimationId, float), { .reversed = false });
    RH_ScopedOverloadedInstall(BlendAnimation, "hier", 0x4D4410, CAnimBlendAssociation*(*)(RpClump*, CAnimBlendHierarchy*, int32, float), { .reversed = false });
    RH_ScopedInstall(LoadAnimFiles, 0x4D5620);
    RH_ScopedInstall(LoadAnimFile, 0x4D47F0);
}

// 0x5BF6B0
void CAnimManager::Initialise() {
    ZoneScoped;

    ms_numAnimations = 0;
    ms_numAnimBlocks = 0;
    ms_numAnimAssocDefinitions = 118; // ANIM_TOTAL_GROUPS aka NUM_ANIM_ASSOC_GROUPS
    ms_animCache.Init(50);
    ReadAnimAssociationDefinitions();
    RegisterAnimBlock("ped");
}

// 0x5BC910
void CAnimManager::ReadAnimAssociationDefinitions() {
    char name[32], block[32], type[32];
    bool                 isAnimSection = false;
    AnimAssocDefinition* animStyle;
    uint32               animCount;

    CFileMgr::SetDir("");
    const auto f = CFileMgr::OpenFile("DATA\\ANIMGRP.DAT", "rb");
    for (;;) {
        const auto l = CFileLoader::LoadLine(f);
        if (!l) {
            break;
        }
        if (!*l || *l == '#') {
            continue;
        }
        if (isAnimSection) {
            if (sscanf_s(l, "%s", SCANF_S_STR(name)) == 1) {
                if (!memcmp(name, "end", 4)) {
                    isAnimSection = false;
                } else {
                    AddAnimToAssocDefinition(animStyle, name);
                }
            }
        } else {
            VERIFY(sscanf_s(l, "%s %s %s %d", SCANF_S_STR(name), SCANF_S_STR(block), SCANF_S_STR(type), &animCount) == 4);
            animStyle = AddAnimAssocDefinition(name, block, MODEL_MALE01, animCount, aStdAnimDescs);
            isAnimSection = true;
        }
    }
    CFileMgr::CloseFile(f);
}

// 0x4D4130
void CAnimManager::Shutdown() {
    for (auto i = 0; i < NUM_ANIM_BLOCKS; i++) {
        CStreaming::RemoveModel(IFPToModelId(i));
    }

    for (auto i = 0; i < ms_numAnimations; i++) {
        ms_aAnimations[i].Shutdown();
    }

    ms_animCache.Shutdown();
    delete[] ms_aAnimAssocGroups;
}

CAnimBlock* CAnimManager::GetAnimationBlock(AssocGroupId animGroup) {
    return ms_aAnimAssocGroups[animGroup].m_AnimBlock;
}

// 0x4D3940
CAnimBlock* CAnimManager::GetAnimationBlock(const char* name) {
    const auto namesv = notsa::ci_string_view{ name };
    for (auto& ab : GetAnimBlocks()) {
        if (namesv == ab.Name) {
            return &ab;
        }
    }
    return nullptr;
}

int32 CAnimManager::GetAnimationBlockIndex(AssocGroupId animGroup) {
    return GetAnimationBlock(animGroup) - ms_aAnimBlocks.data();
}

int32 CAnimManager::GetAnimationBlockIndex(CAnimBlock* animBlock) {
    return animBlock - ms_aAnimBlocks.data();
}

// 0x4D3990
int32 CAnimManager::GetAnimationBlockIndex(const char* name) {
    const auto b = GetAnimationBlock(name);
    return b
        ? (int32)(std::distance(ms_aAnimBlocks.data(), b))
        : -1;
}

// 0x4D39B0
AssocGroupId CAnimManager::GetFirstAssocGroup(const char* name) {
    const auto namesv = notsa::ci_string_view{ name };
    for (auto i = 0; i < ANIM_GROUP_MAN; i++) {
        if (ms_aAnimAssocDefinitions[i].blockName == namesv) {
            return static_cast<AssocGroupId>(i);
        }
    }
    return ANIM_GROUP_MAN;
}

// 0x4D39F0
CAnimBlendHierarchy* CAnimManager::GetAnimation(uint32 hash, const CAnimBlock* animBlock) {
    auto h = &ms_aAnimations[animBlock->FirstAnimId];
    for (auto i = animBlock->NumAnims; i-- > 0; h++) {
        if (h->m_hashKey == hash) {
            return h;
        }
    }
    return nullptr;
}

// 0x4D42F0
CAnimBlendHierarchy* CAnimManager::GetAnimation(const char* animName, const CAnimBlock* animBlock) {
    return GetAnimation(CKeyGen::GetUppercaseKey(animName), animBlock);
}

// notsa
CAnimBlendHierarchy& CAnimManager::GetAnimation(AnimationId id) {
    return ms_aAnimations[(size_t)id];
}

// 0x4D3A20
const char* CAnimManager::GetAnimGroupName(AssocGroupId groupId) {
    return ms_aAnimAssocDefinitions[groupId].groupName;
}

// 0x4D3A30
const char* CAnimManager::GetAnimBlockName(AssocGroupId groupId) {
    return ms_aAnimAssocDefinitions[groupId].blockName;
}

// NOTSA
AssocGroupId CAnimManager::GetAnimationGroupIdByName(notsa::ci_string_view name) {
    for (const auto& [i, gd] : notsa::enumerate(GetAssocGroupDefs())) {
        if (gd.groupName == name) {
            return (AssocGroupId)i;
        }
    }
    return AssocGroupId::ANIM_GROUP_DEFAULT;
}

// 0x4D3A40
CAnimBlendAssociation* CAnimManager::CreateAnimAssociation(AssocGroupId groupId, AnimationId animId) {
    return ms_aAnimAssocGroups[groupId].CopyAnimation(animId);
}

// 0x4D3A60
CAnimBlendStaticAssociation* CAnimManager::GetAnimAssociation(AssocGroupId groupId, AnimationId animId) {
    return ms_aAnimAssocGroups[groupId].GetAnimation(animId);
}

// 0x4D3A80
CAnimBlendStaticAssociation* CAnimManager::GetAnimAssociation(AssocGroupId groupId, const char* animName) {
    return ms_aAnimAssocGroups[groupId].GetAnimation(animName);
}

CAnimBlendAssociation* CAnimManager::AddAnimationToClump(RpClump* clump, CAnimBlendAssociation* anim) {
    const auto clumpAnims = &RpClumpGetAnimBlendClumpData(clump)->m_Associations;
    const auto syncWith = [&]() -> CAnimBlendAssociation* {
        if (anim->IsMoving()) {
            for (auto l = clumpAnims->next; l; l = l->next) {
                const auto a = CAnimBlendAssociation::FromLink(l);
                if (a->IsMoving()) {
                    return a;
                }
            }
        }
        return nullptr;
        }();
        if (syncWith) {
            anim->SyncAnimation(syncWith);
            anim->m_Flags |= ANIMATION_STARTED;
        } else {
            anim->Start(0.0f);
        }
        clumpAnims->Prepend(&anim->m_Link);
        return anim;
}

// 0x4D3AA0
CAnimBlendAssociation* CAnimManager::AddAnimation(RpClump* clump, AssocGroupId groupId, AnimationId animId) {
    return AddAnimationToClump(clump, CreateAnimAssociation(groupId, animId));
}

// 0x4D4330
CAnimBlendAssociation* CAnimManager::AddAnimation(RpClump* clump, CAnimBlendHierarchy* hier, int32 clumpAssocFlag) {
    const auto anim = new CAnimBlendAssociation(clump, hier);
    anim->m_Flags |= clumpAssocFlag;
    anim->ReferenceAnimBlock();
    UncompressAnimation(hier);
    return AddAnimationToClump(clump, anim);
}

// 0x4D3B30
CAnimBlendAssociation* CAnimManager::AddAnimationAndSync(RpClump* clump, CAnimBlendAssociation* animBlendAssoc, AssocGroupId groupId, AnimationId animId) {
    const auto a          = CreateAnimAssociation(groupId, animId);
    const auto clumpAnims = RpClumpGetAnimBlendClumpData(clump);
    if (a->IsMoving() && animBlendAssoc) {
        a->SyncAnimation(animBlendAssoc);
        a->m_Flags |= ANIMATION_STARTED;
    } else {
        a->Start(0.0f);
    }
    clumpAnims->m_Associations.Prepend(&a->m_Link);
    return a;
}

// 0x4D3BA0
AnimAssocDefinition* CAnimManager::AddAnimAssocDefinition(const char* groupName, const char* blockName, uint32 modelIndex, uint32 animsCount, AnimDescriptor* descriptor) {
    const auto d = &ms_aAnimAssocDefinitions[ms_numAnimAssocDefinitions++];

    strcpy_s(d->groupName, groupName);
    strcpy_s(d->blockName, blockName);

    d->modelIndex = modelIndex;
    d->animsCount = animsCount;
    d->animDesc   = descriptor;

    d->animNames     = new const char*[animsCount];
    const auto bufsz = AnimAssocDefinition::ANIM_NAME_BUF_SZ * animsCount;
    const auto buf   = new char[bufsz];
    memset(buf, 0, bufsz);
    for (auto i = animsCount; i-->0;) {
        d->animNames[i] = buf + i * 24;
    }

    return d;
}

// 0x4D3C80
void CAnimManager::AddAnimToAssocDefinition(AnimAssocDefinition* def, const char* animName) {
    int32 i = 0;
    for (; *def->animNames[i]; i++) {
        assert(i < def->animsCount);
    }
    // `const_cast` is fine here, because it's heap allocated [presumeably]
    strcpy_s(const_cast<char*>(def->animNames[i]), AnimAssocDefinition::ANIM_NAME_BUF_SZ, animName);
}

// 0x4D3CC0
void CAnimManager::CreateAnimAssocGroups() {
    for (auto&& [i, group] : notsa::enumerate(GetAssocGroups())) {
        const auto def   = &ms_aAnimAssocDefinitions[i];
        const auto block = GetAnimationBlock(def->blockName);
        if (block == nullptr || !block->IsLoaded || group.m_Anims) {
            continue;
        }

        RpClump* clump = nullptr;
        if (def->modelIndex != MODEL_INVALID) {
            clump = (RpClump*)CModelInfo::GetModelInfo(def->modelIndex)->CreateInstance();
            RpAnimBlendClumpInit(clump);
        }

        group.m_GroupID = (AssocGroupId)i;
        group.m_IdOffset = def->animDesc->animId;
        group.CreateAssociations(def->blockName, clump, def->animNames, def->animsCount);
        for (auto j = 0u; j < group.m_NumAnims; j++) {
            group.GetAnimation(def->animDesc[j].animId)->m_Flags |= def->animDesc[j].flags;
        }

        if (clump) {
#ifdef SA_SKINNED_PEDS
            if (IsClumpSkinned(clump)) {
                RpClumpForAllAtomics(clump, AtomicRemoveAnimFromSkinCB, nullptr);
            }
#endif
            RpClumpDestroy(clump);
        }
    }
}

// 0x4D3E50
int32 CAnimManager::RegisterAnimBlock(const char* name) {
    CAnimBlock* ab = GetAnimationBlock(name);
    if (ab == nullptr) { // Initialize a new anim block
        ab = &ms_aAnimBlocks[ms_numAnimBlocks++];
        strncpy_s(ab->Name, name, MAX_ANIM_BLOCK_NAME);
        ab->NumAnims = 0;
        ab->GroupId = GetFirstAssocGroup(name);
        assert(ab->RefCnt == 0);
    }

    return GetAnimationBlockIndex(ab);
}

// 0x4D3ED0
void CAnimManager::RemoveLastAnimFile() {
    const auto ab = &GetAnimBlocks()[--ms_numAnimBlocks];
    ms_numAnimations = ab->FirstAnimId;
    for (auto i = 0u; i < ab->NumAnims; i++) { // Remove related animations too
        ms_aAnimations[ab->FirstAnimId + i].Shutdown();
    }
    ab->IsLoaded = false;
}

// 0x4D3F40
void CAnimManager::RemoveAnimBlock(int32 index) {
    const auto ab = &GetAnimBlocks()[index];

    for (auto& g : GetAssocGroups()) {
        if (g.m_AnimBlock == ab) {
            g.DestroyAssociations();
        }
    }

    for (auto i = 0u; i < ab->NumAnims; i++) { // Remove related animations too
        ms_aAnimations[ab->FirstAnimId + i].Shutdown();
    }

    ab->IsLoaded = false;
    ab->RefCnt  = 0;
}

// 0x4D3FB0
void CAnimManager::AddAnimBlockRef(int32 index) {
    GetAnimBlocks()[index].RefCnt++;
}

// 0x4D3FD0
void CAnimManager::RemoveAnimBlockRef(int32 index) {
    GetAnimBlocks()[index].RefCnt--;
    /* see RemoveAnimBlockRefWithoutDelete, logically here should be called RemoveModel or something
    if (--ms_aAnimBlocks[index].usRefs == 0) {
    CStreaming::RemoveModel(IFPToModelId(index));
    }
    */
}

// 0x4D3FF0
void CAnimManager::RemoveAnimBlockRefWithoutDelete(int32 index) {
    ms_aAnimBlocks[index].RefCnt--;
}

// 0x4D4010
int32 CAnimManager::GetNumRefsToAnimBlock(int32 index) {
    return ms_aAnimBlocks[index].RefCnt;
}

// 0x4D41C0
void CAnimManager::UncompressAnimation(CAnimBlendHierarchy* h) {
    if (h->m_bKeepCompressed) {
        if (h->m_fTotalTime == 0.f) {
            h->CalcTotalTimeCompressed();
        }
    } else if (h->m_bIsCompressed) {
        auto l = ms_animCache.Insert(h);
        if (!l) { // Not more free links?
            // Remove least recently added item
            const auto llr = ms_animCache.GetTail();
            llr->data->RemoveUncompressedData();
            RemoveFromUncompressedCache(llr->data);

            // Now try again, this time it should succeed
            VERIFY(l = ms_animCache.Insert(h));
        }
        h->m_Link = l;
        h->Uncompress();
    } else if (h->m_Link) { // Already uncompressed, add to cache
        h->m_Link->Insert(ms_animCache.GetHead());
    }
}

// 0x4D42A0
void CAnimManager::RemoveFromUncompressedCache(CAnimBlendHierarchy* h) {
    if (const auto l = h->m_Link) {
        l->data->m_Link = nullptr;
        ms_animCache.Remove(l);
    }
}

// 0x4D4410
CAnimBlendAssociation* CAnimManager::BlendAnimation(RpClump* clump, CAnimBlendHierarchy* animBlendHier, int32 flags, float clumpAssocBlendData) {
    return plugin::CallAndReturn<CAnimBlendAssociation*, 0x4D4410, RpClump*, CAnimBlendHierarchy*, int32, float>(clump, animBlendHier, flags, clumpAssocBlendData);

    /*
    CAnimBlendClumpData* clumpData = RpClumpGetAnimBlendClumpData(clump);
    bool isPartial = (flags & ANIMATION_PARTIAL) == 0;
    int removePrevAnim = 0;
    CAnimBlendLink* link;
    CAnimBlendAssociation *anim, *found = nullptr;
    for (link = clumpData->m_Associations.next; link; link = link->next) {
    anim = CAnimBlendAssociation::FromLink(link);
    if (anim->m_pHierarchy == animBlendHier) {
    found = anim;
    } else if (isPartial == anim->IsPartial()) {
    if (anim->m_fBlendAmount > 0.0f) {
    float blendDelta = -delta * anim->m_fBlendAmount;
    if (blendDelta < anim->m_fBlendDelta || !isPartial) { // || (anim->m_pHierarchy->animBlockId == animBlendHier->animBlockId && anim->m_pHierarchy->animBlockId)) {
    if (blendDelta > -0.05f) {
    blendDelta = -0.05f;
    }
    anim->m_fBlendDelta = blendDelta;
    }
    } else {
    anim->m_fBlendDelta = -1.0f;
    }
    anim->m_nFlags |= ANIMATION_FREEZE_LAST_FRAME;
    removePrevAnim = 1;
    }
    }

    if (found) {
    found->m_fBlendDelta = (1.0f - found->m_fBlendAmount) * delta;
    if (found->m_fCurrentTime == found->m_pHierarchy->m_fTotalTime) { // !found->IsRunning() && ...
    found->Start(0.0f);
    }
    } else {
    found = new CAnimBlendAssociation(clump, animBlendHier);
    found->m_nFlags |= flags;
    found->ReferenceAnimBlock();
    UncompressAnimation(animBlendHier);
    clumpData->m_Associations.Prepend(&found->m_Associations);
    found->Start(0.0f);
    if (!removePrevAnim && !isPartial) {
    found->m_fBlendAmount = 1.0f;
    return found;
    }
    found->m_fBlendAmount = 0.0f;
    found->m_fBlendDelta = delta;
    }
    UncompressAnimation(found->m_pHierarchy);
    return found;
    */
}

// 0x4D4610
CAnimBlendAssociation* CAnimManager::BlendAnimation(RpClump* clump, AssocGroupId groupId, AnimationId animId, float clumpAssocBlendData) {
    return plugin::CallAndReturn<CAnimBlendAssociation*, 0x4D4610, RpClump*, AssocGroupId, AnimationId, float>(clump, groupId, animId, clumpAssocBlendData);

    /*
    auto removePrevAnim = false;
    CAnimBlendClumpData* clumpData = RpClumpGetAnimBlendClumpData(clump);
    CAnimBlendStaticAssociation* animProps = GetAnimAssociation(groupId, animId);
    CAnimBlendAssociation* anim;
    bool isMovement = animProps->IsMovement();
    bool isPartial = animProps->IsPartial();
    bool isIndestructible = animProps->IsIndestructible();
    CAnimBlendLink* link;
    CAnimBlendAssociation *found = nullptr, *movementAnim = nullptr;
    for (link = clumpData->link.next; link; link = link->next) {
    anim = CAnimBlendAssociation::FromLink(link);
    if (isMovement && anim->IsMovement())
    movementAnim = anim;
    if (anim->m_nAnimId == animId && anim->m_nAnimGroup == groupId)
    found = anim;
    else {
    if (isPartial == anim->IsPartial() && isIndestructible == anim->IsIndestructible()) {
    if (anim->m_fBlendAmount > 0.0f) {
    float blendDelta = -delta * anim->m_fBlendAmount;
    if (blendDelta < anim->m_fBlendDelta || !isPartial) {
    if (blendDelta > -0.05f)
    blendDelta = -0.05f;
    anim->m_fBlendDelta = blendDelta;
    }
    } else {
    anim->m_fBlendDelta = -1.0f;
    }
    anim->flags |= ANIMATION_FREEZE_LAST_FRAME;
    removePrevAnim = true;
    }
    }
    }

    if (found) {
    found->m_fBlendDelta = (1.0f - found->m_fBlendAmount) * delta;
    if (!found->IsRunning() && found->currentTime == found->hierarchy->m_fTotalTime)
    found->Start(0.0f);
    } else {
    found = AddAnimationAndSync(clump, movementAnim, groupId, animId);
    if (!removePrevAnim && !isPartial) {
    found->m_fBlendAmount = 1.0f;
    return found;
    }
    found->m_fBlendAmount = 0.0f;
    found->m_fBlendDelta = delta;
    }
    UncompressAnimation(found->hierarchy);
    return found;
    */
}

// 0x4D5620
void CAnimManager::LoadAnimFiles() {
    RwStream* stream = RwStreamOpen(rwSTREAMFILENAME, rwSTREAMREAD, "ANIM\\PED.IFP");
    assert(stream);
    LoadAnimFile(stream, true);
    RwStreamClose(stream, nullptr);

    ms_aAnimAssocGroups = new CAnimBlendAssocGroup[ms_numAnimAssocDefinitions];
    CreateAnimAssocGroups();
}

struct IFPSectionHeader {
    union {
        char   IDFourCC[4];
        uint32 ID;
    };
    uint32 Size;
};

//! @notsa - Helper
auto CAnimManager::GetOrCreateAnimBlock(const char* name, uint32 numAnims) {
    CAnimBlock* ablock;
    if (ablock = GetAnimationBlock(name)) { // Block already exists
        if (!ablock->NumAnims) {
            ablock->NumAnims = numAnims;
            ablock->FirstAnimId = ms_numAnimations;
        }
    } else { // Create block
        const auto id = ms_numAnimations++;

        ablock = &ms_aAnimBlocks[id];

        VERIFY(strncpy_s(ablock->Name, name, MAX_ANIM_BLOCK_NAME) == 0);
        ablock->NumAnims = numAnims;
        ablock->FirstAnimId = ms_numAnimations;
        ablock->GroupId = GetFirstAssocGroup(ablock->Name);
    }
    ablock->IsLoaded = true;
    return std::make_tuple(ablock, GetAnimationBlockIndex(ablock));
}

// 0x4D47F0
void CAnimManager::LoadAnimFile(RwStream* stream, bool loadCompressed, char const(*uncompressedAnimations)[32]) {
    IFPSectionHeader h;
    RwStreamRead(stream, &h, sizeof(h));
    switch (h.ID) {
    case MakeFourCC("ANP3"):
    case MakeFourCC("ANP2"):
        return LoadAnimFile_ANP23(stream, h, loadCompressed, h.ID == MakeFourCC("ANP3"));
    case MakeFourCC("ANPK"):
        return LoadAnimFile_ANPK(stream, h, loadCompressed, uncompressedAnimations);
    default:
        NOTSA_UNREACHABLE("Unknown ANPK: {:x}", h.ID);
    }
}

namespace ANPK {
    template<size_t MaxNameLen>
    struct Info {
        uint32 Num;
        char   Name[MaxNameLen];
    };

    template<size_t MaxLen>
    struct TString {
        char Data[MaxLen];
    };

    //! Round number to 4 byte boundary
    auto RoundTo4(auto num) {
        return num % 4
            ? num + 4 - (num % 4)
            : num;
    }

    template<typename T>
    auto ReadSection(RwStream* stream) {
        auto h = RwStreamRead<IFPSectionHeader>(stream);
        h.Size = RoundTo4(h.Size);
        struct Ret { T v; IFPSectionHeader h; };
        return Ret{RwStreamRead<T>(stream, h.Size), h};
    }
};

// Code from 0x4D4863
// NOTE:
// This code was written based off the docs on gtamods
// I didn't manage to find any ANPK anims, thus this function is untested so far
inline void CAnimManager::LoadAnimFile_ANPK(RwStream* s, const IFPSectionHeader& h, bool bLoadCompressed, const char (*pLoadUncompressed)[32]) {
    using namespace ANPK;

    const auto hBlockInfo = RwStreamRead<IFPSectionHeader>(s);
    const auto blockInfo = RwStreamRead<Info<MAX_ANIM_BLOCK_NAME>>(s, RoundTo4(hBlockInfo.Size));

    const auto [ablock, ablockIdx] = GetOrCreateAnimBlock(blockInfo.Name, blockInfo.Num);

    /** TAnimation - Each entry represents an animation
    * AnimName : NAME
    * AnimData : DGAN
    **/

    // Read TAnimation's for this block
    for (size_t animN = 0; animN < blockInfo.Num; animN++) {
        const auto hier = &ms_aAnimations[ablock->FirstAnimId + animN];

        // Read and set name
        {
            char name[64];
            const auto header = RwStreamRead<IFPSectionHeader>(s);
            assert(header.ID == MakeFourCC("NAME"));
            RwStreamRead(s, name, RoundTo4(header.Size));
            hier->SetName(name);
            NOTSA_LOG_DEBUG("Reading animation {}", name);
        }

        // Check if this animation is compressed
        bool isCompressed = bLoadCompressed;
        for (size_t k = 0; pLoadUncompressed[k][0]; k++) {
            if (CKeyGen::GetUppercaseKey(pLoadUncompressed[k]) == hier->GetHashKey()) {
                isCompressed = false;
                break; // fix_bugs
            }
        }
        hier->m_nAnimBlockId    = ablockIdx;
        hier->m_bIsCompressed   = isCompressed;
        hier->m_bKeepCompressed = false;

        // Read DGAN header
        const auto hDGAN = RwStreamRead<IFPSectionHeader>(s);
        assert(hDGAN.ID == MakeFourCC("DGAN"));

        // Read DGAN struct
        const auto hInfoCPAN = RwStreamRead<IFPSectionHeader>(s); // INFO<CPAN> header
        assert(hInfoCPAN.ID == MakeFourCC("CPAN"));

        const auto infoCPAN  = RwStreamRead<Info<64>>(s, RoundTo4(hInfoCPAN.Size));  // INFO<CPAN>

        hier->m_nSeqCount  = infoCPAN.Num;
        hier->m_pSequences = new CAnimBlendSequence[hier->m_nSeqCount]; // Yes, they used `new`

        // Read `INFO<CPAN>` entries (The Sequences)
        for (size_t seqN = 0; seqN < infoCPAN.Num; seqN++) {
            const auto seq = &hier->m_pSequences[seqN];

            const auto hCPAN = RwStreamRead<IFPSectionHeader>(s); // CPAN header
            assert(hCPAN.ID == MakeFourCC("CPAN"));

            // Read the anim data
            struct Anim {
                char   Name[28];    // 00 - Name of this sequence
                uint32 NumFrames;   // 28 - Number of (key)frames
                uint32 Next;        // 32 - Next sibling
                uint32 Prev;        // 36 - Previous sibling
                uint32 BoneTag;     // 40 - Only present if `Header.Size == 44`
            };
            const auto [anim, hAnim] = ReadSection<Anim>(s);
            assert(hAnim.ID == MakeFourCC("ANIM"));

            // Set sequence name
            seq->SetName(anim.Name);

            // Set bone tag if available
            if (hAnim.Size == sizeof(Anim)) {
                seq->SetBoneTag(anim.BoneTag);
            }

            //
            // Read frames now (if any)
            //

            if (!anim.NumFrames) {
                continue;
            }

            // Frame data header
            const auto hKfrm = RwStreamRead<IFPSectionHeader>(s);
            assert(hKfrm.ID == MakeFourCC("KFRM"));

            // NOTE: Only KR00, KRT0, KRTS are valid, other combinations are not.
            switch (hKfrm.ID) {
            case MakeFourCC("KRTS"):
            case MakeFourCC("KRT0"):
            case MakeFourCC("KR00"):
                break;
            default:
                NOTSA_UNREACHABLE("Invalid ({}) kf type!", hKfrm.ID);
            }

            // Frame properties
            const auto hasRotation    = hKfrm.IDFourCC[1] == 'R';
            const auto hasTranslation = hKfrm.IDFourCC[2] == 'T';
            const auto hasScale       = hKfrm.IDFourCC[3] == 'S';

            /* Frame data layout (In stream):
            * float      DeltaTime;
            * CQuaterion Rot;
            * 
            * if hasTranslate:
            *     CVector Translate;
            * 
            *     if hasScale:
            *         CVector Scale;
            */

            // Allocate frame data
            seq->SetNumFrames(anim.NumFrames, hasRotation, isCompressed, nullptr);

            // Read frame data from the stream
            for (size_t kfN = 0; kfN < anim.NumFrames; kfN++) {
                const auto SetKF = [&](auto* kf) {
                    kf->SetDeltaTime(RwStreamRead<float>(s));
                    kf->Rot = RwStreamRead<CQuaternion>(s).Conjugated();
                    if (hasTranslation) {
                        kf->Trans = RwStreamRead<CVector>(s);
                        if (hasScale) {
                            RwStreamSkip(s, sizeof(CVector)); // Scale ignored
                        }
                    }
                };
                if (isCompressed) {
                    SetKF(seq->GetCKeyFrame(kfN));
                } else {
                    SetKF(seq->GetUKeyFrame(kfN));
                }
            }
        }
    }
    ms_numAnimations = std::max<int32>(ablock->FirstAnimId + blockInfo.Num, ms_numAnimations);
}

// NOTE:
// This code was written based off the docs on gtamods, but it does seem to work
inline void CAnimManager::LoadAnimFile_ANP23(RwStream* s, const IFPSectionHeader& h, bool bLoadCompressed, bool isANP3) {
    char blockName[24];
    RwStreamRead(s, blockName, sizeof(blockName));
    const auto numAnims = RwStreamRead<uint32>(s);

    const auto [ablock, ablockId] = GetOrCreateAnimBlock(blockName, numAnims);

    NOTSA_LOG_DEBUG("Reading block ({})", blockName);

    for (size_t animN = 0; animN < numAnims; animN++) {
        const auto hier = &ms_aAnimations[ablock->FirstAnimId + animN];

        // Animation name
        char aname[24];
        RwStreamRead(s, aname, sizeof(aname));
        hier->SetName(aname);

        // Number of sequences
        const auto numSeq = RwStreamRead<uint32>(s);

        // In ANP3 a big chunk of memory is allocated for all frames
        // instead of allocating lots of small chunks
        char* frames = nullptr;

        if (isANP3) {
            const auto size  = RwStreamRead<uint32>(s);
            const auto flags = RwStreamRead<uint32>(s);

            hier->m_bIsCompressed = flags & 1;

            frames = (char*)CMemoryMgr::Malloc(size);
        }

        hier->m_nAnimBlockId    = ablockId;
        hier->m_bKeepCompressed = false;

        // Allocate sequences - TODO: MSVC garbage
        hier->m_nSeqCount  = numSeq;
        hier->m_pSequences = new CAnimBlendSequence[numSeq]; // Yes, they used `new`

        // Read sequences
        for (size_t seqN = 0; seqN < numSeq; seqN++) {
            const auto seq = &hier->m_pSequences[seqN];

            char seqName[24];
            RwStreamRead(s, seqName, sizeof(seqName));
            const auto frameType = RwStreamRead<uint32>(s);
            const auto numFrames = RwStreamRead<uint32>(s);
            const auto boneTag   = RwStreamRead<uint32>(s);

            seq->SetName(seqName);
            seq->SetBoneTag(boneTag);

            // Read frames
            const auto ReadFrames = [&](size_t kfSize, bool hasTranslation, bool compressed) {
                seq->SetNumFrames(numFrames, hasTranslation, compressed, frames);

                const auto memSz = kfSize * numFrames;
                RwStreamRead(s, seq->m_Frames, memSz);
                if (isANP3) {
                    frames += memSz;
                }
            };

            switch (frameType) {
            case 1:
                ReadFrames(sizeof(KeyFrame), false, false); break;
            case 2:
                ReadFrames(sizeof(KeyFrameTrans), true, false); break;
            case 3:
                ReadFrames(sizeof(KeyFrameCompressed), false, true); break;
            case 4:
                ReadFrames(sizeof(KeyFrameTransCompressed), true, true); break;
            default:
                NOTSA_UNREACHABLE("Invalid FrameType ({})", frameType);
            }

            if (isANP3) {
                seq->m_bUsingExternalMemory = true;
            }
        }

        if (!hier->m_bIsCompressed) {
            hier->RemoveQuaternionFlips();
            hier->CalcTotalTime();
        }
    }

    ms_numAnimations = std::max<int32>(ablock->FirstAnimId + numAnims, ms_numAnimations);
}

AnimationId CAnimManager::GetRandomGangTalkAnim() {
    constexpr AnimationId gangTalkAnims[]{
        ANIM_ID_PRTIAL_GNGTLKA,
        ANIM_ID_PRTIAL_GNGTLKB,
        ANIM_ID_PRTIAL_GNGTLKC,
        ANIM_ID_PRTIAL_GNGTLKD,

        ANIM_ID_PRTIAL_GNGTLKE,
        ANIM_ID_PRTIAL_GNGTLKF,
        ANIM_ID_PRTIAL_GNGTLKG,
        ANIM_ID_PRTIAL_GNGTLKH,
    };
    return CGeneral::RandomChoice(gangTalkAnims);
}
