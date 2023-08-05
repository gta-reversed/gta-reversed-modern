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
    RH_ScopedInstall(LoadAnimFile, 0x4D47F0, {.reversed = false});
}

struct IfpHeader {
    uint32 ident;
    uint32 size;
} header;

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
    return ms_aAnimAssocGroups[animGroup].m_pAnimBlock;
}

// 0x4D3940
CAnimBlock* CAnimManager::GetAnimationBlock(const char* name) {
    const auto namesv = notsa::ci_string_view{ name };
    for (auto& ab : GetAnimBlocks()) {
        if (namesv == ab.szName) {
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
    auto h = &ms_aAnimations[animBlock->startAnimation];
    for (auto i = animBlock->animationCount; i-- > 0; h++) {
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
        anim->m_nFlags |= ANIMATION_STARTED;
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
    anim->m_nFlags |= clumpAssocFlag;
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
        a->m_nFlags |= ANIMATION_STARTED;
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

// 0x4C4DC0
bool IsClumpSkinned(RpClump *clump) {
    const auto a = GetFirstAtomic(clump);
    return a && RpSkinGeometryGetSkin(RpAtomicGetGeometry(a));
}

// 0x4D3CC0
void CAnimManager::CreateAnimAssocGroups() {
    for (auto&& [i, group] : notsa::enumerate(GetAssocGroups())) {
        const auto def   = &ms_aAnimAssocDefinitions[i];
        const auto block = GetAnimationBlock(def->blockName);
        if (block == nullptr || !block->bLoaded || group.m_pAssociations) {
            continue;
        }

        RpClump* clump = nullptr;
        if (def->modelIndex != MODEL_INVALID) {
            clump = (RpClump*)CModelInfo::GetModelInfo(def->modelIndex)->CreateInstance();
            RpAnimBlendClumpInit(clump);
        }

        group.m_nGroupID = i;
        group.m_nIdOffset = def->animDesc->animId;
        group.CreateAssociations(def->blockName, clump, const_cast<char**>(def->animNames), def->animsCount); // todo: remove const_cast
        for (auto j = 0u; j < group.m_nNumAnimations; j++) {
            group.GetAnimation(def->animDesc[j].animId)->m_nFlags |= def->animDesc[j].flags;
        }

        if (clump) {
            if (IsClumpSkinned(clump)) {
                RpClumpForAllAtomics(clump, AtomicRemoveAnimFromSkinCB, nullptr);
            }
            RpClumpDestroy(clump);
        }
    }
}

// 0x4D3E50
int32 CAnimManager::RegisterAnimBlock(const char* name) {
    CAnimBlock* ab = GetAnimationBlock(name);
    if (ab == nullptr) { // Initialize a new anim block
        ab = &ms_aAnimBlocks[ms_numAnimBlocks++];
        strncpy_s(ab->szName, name, MAX_ANIM_BLOCK_NAME);
        ab->animationCount = 0;
        ab->animationStyle = GetFirstAssocGroup(name);
        assert(ab->usRefs == 0);
    }

    return GetAnimationBlockIndex(ab);
}

// 0x4D3ED0
void CAnimManager::RemoveLastAnimFile() {
    const auto ab = &GetAnimBlocks()[--ms_numAnimBlocks];
    ms_numAnimations = ab->startAnimation;
    for (auto i = 0; i < ab->animationCount; i++) { // Remove related animations too
        ms_aAnimations[ab->startAnimation + i].Shutdown();
    }
    ab->bLoaded = false;
}

// 0x4D3F40
void CAnimManager::RemoveAnimBlock(int32 index) {
    const auto ab = &GetAnimBlocks()[index];

    for (auto& g : GetAssocGroups()) {
        if (g.m_pAnimBlock == ab) {
            g.DestroyAssociations();
        }
    }
    
    for (auto i = 0; i < ab->animationCount; i++) { // Remove related animations too
        ms_aAnimations[ab->startAnimation + i].Shutdown();
    }

    ab->bLoaded = false;
    ab->usRefs  = 0;
}

// 0x4D3FB0
void CAnimManager::AddAnimBlockRef(int32 index) {
    GetAnimBlocks()[index].usRefs++;
}

// 0x4D3FD0
void CAnimManager::RemoveAnimBlockRef(int32 index) {
    GetAnimBlocks()[index].usRefs--;
    /* see RemoveAnimBlockRefWithoutDelete, logically here should be called RemoveModel or something
    if (--ms_aAnimBlocks[index].usRefs == 0) {
        CStreaming::RemoveModel(IFPToModelId(index));
    }
    */
}

// 0x4D3FF0
void CAnimManager::RemoveAnimBlockRefWithoutDelete(int32 index) {
    ms_aAnimBlocks[index].usRefs--;
}

// 0x4D4010
int32 CAnimManager::GetNumRefsToAnimBlock(int32 index) {
    return ms_aAnimBlocks[index].usRefs;
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

// 0x4D47F0
void CAnimManager::LoadAnimFile(RwStream* stream, bool loadCompressed, char const(*uncompressedAnimations)[32]) {
    RwStreamRead(stream, &header, sizeof(IfpHeader));
    if (header.ident == '3PNA' || header.ident == '2PNA') {
        LoadAnimFile_ANP23(stream, loadCompressed, header.ident == '3PNA');
    } else if (header.ident == 'KPNA') {
        LoadAnimFile_ANPK(stream, loadCompressed, uncompressedAnimations);
    }
}

inline void CAnimManager::LoadAnimFile_ANPK(RwStream* stream, bool compress, const char (*uncompressedAnims)[32]) {
#define ROUND_SIZE(x)                                                                                                                                                              \
    if ((x)&3)                                                                                                                                                                     \
    (x) += 4 - ((x)&3)

    IfpHeader info, name, dgan, cpan, anim;
    char buf[256];
    float* fbuf = (float*)buf;

    // block name
    // RwStreamRead(stream, &anpk, sizeof(IfpHeader));
    // assert(anpk.ident[0] == 'A' && anpk.ident[1] == 'N' && anpk.ident[2] == 'P');
    // if (anpk.ident[3] != 'K')
    //     return LoadAnimFile_2(stream, compress, uncompressedAnims, anpk.ident[3] == '3');
    // ROUND_SIZE(anpk.size);

    RwStreamRead(stream, &info, sizeof(IfpHeader));
    ROUND_SIZE(info.size);
    RwStreamRead(stream, buf, info.size);
    CAnimBlock* animBlock = GetAnimationBlock(buf + 4);
    if (animBlock) {
        if (animBlock->animationCount == 0) {
            animBlock->animationCount = *(int*)buf;
            animBlock->startAnimation = ms_numAnimations;
        }
    } else {
        animBlock = &ms_aAnimBlocks[ms_numAnimBlocks++];
        strncpy_s(animBlock->szName, buf + 4, MAX_ANIM_BLOCK_NAME);
        animBlock->animationCount = *(int*)buf;
        animBlock->startAnimation = ms_numAnimations;
        animBlock->animationStyle = GetFirstAssocGroup(animBlock->szName);
    }

    DEV_LOG("Loading ANIMS {}", animBlock->szName);
    animBlock->bLoaded = true;

    int animIndex = animBlock->startAnimation;
    for (auto j = 0; j < animBlock->animationCount; j++) {
        assert(animIndex < (int32)std::size(ms_aAnimations));
        CAnimBlendHierarchy* hier = &ms_aAnimations[animIndex++];

        // animation name
        RwStreamRead(stream, &name, sizeof(IfpHeader));
        ROUND_SIZE(name.size);
        RwStreamRead(stream, buf, name.size);
        //printf("Loading hierarchy %s\n", buf);
        hier->SetName(buf);

        //#ifdef ANIM_COMPRESSION
        bool isCompressed = compress;
        //#else
        //        bool compressHier = false;
        //#endif
        if (uncompressedAnims) {
            for (int i = 0; uncompressedAnims[i][0]; i++) {
                //if (!stricmp(uncompressedAnims[i], buf))
                if (CKeyGen::GetUppercaseKey(uncompressedAnims[i]) == hier->m_hashKey)// {
                    //debug("Loading %s uncompressed\n", hier->name);
                    isCompressed = false;
                //}
            }
        }

        hier->m_bIsCompressed = isCompressed;
        hier->m_bKeepCompressed = false;

        // DG info has number of nodes/sequences
        RwStreamRead(stream, (char*)&dgan, sizeof(IfpHeader));
        ROUND_SIZE(dgan.size);

        RwStreamRead(stream, (char*)&info, sizeof(IfpHeader));
        ROUND_SIZE(info.size);

        RwStreamRead(stream, buf, info.size);
        int nSeq = *(int*)buf;
        hier->m_nSeqCount = nSeq;
        hier->m_pSequences = new CAnimBlendSequence[nSeq]; //= (CAnimBlendSequence*)CMemoryMgr::Malloc(nSeq * sizeof(CAnimBlendSequence));

        for (auto s = 0; s < nSeq; s++) { // or seq++ ?
            CAnimBlendSequence* seq = &hier->m_pSequences[s];

            // Each node has a name and key frames
            RwStreamRead(stream, &cpan, sizeof(IfpHeader));
            ROUND_SIZE(cpan.size);

            RwStreamRead(stream, &anim, sizeof(IfpHeader));
            ROUND_SIZE(anim.size);

            RwStreamRead(stream, buf, anim.size);
            int numFrames = *(int*)(buf + 28);
            seq->SetName(buf);
            if (anim.size == 44)
                seq->SetBoneTag(*(int*)(buf + 40));
            if (numFrames == 0)
                continue;
            //printf("Loading %s frames %d\n", buf, numFrames);

            bool hasScale = false;
            bool hasTranslation = false;
            RwStreamRead(stream, &info, sizeof(info));
            //if (numFrames == 0)
            //    continue;

            if (memcmp(&info.ident, "KRTS", 4) == 0) {
                hasScale = true;
                seq->SetNumFrames(numFrames, true, isCompressed, NULL);
            } else if (memcmp(&info.ident, "KRT0", 4) == 0) {
                hasTranslation = true;
                seq->SetNumFrames(numFrames, true, isCompressed, NULL);
            } else if (memcmp(&info.ident, "KR00", 4) == 0) {
                seq->SetNumFrames(numFrames, false, isCompressed, NULL);
            }

            //if (seq->numFrames)
            // if(strstr(seq->name, "L Toe"))
            //	debug("anim %s has toe keyframes\n", hier->name); // BUG: seq->name

            for (auto l = 0; l < numFrames; l++) {
                if (hasScale) {
                    RwStreamRead(stream, buf, 0x2C);
                    CQuaternion rot(fbuf[0], fbuf[1], fbuf[2], fbuf[3]);
                    rot.Conjugate();
                    CVector trans(fbuf[4], fbuf[5], fbuf[6]);

                    if (isCompressed) {
                        KeyFrameTransCompressed* kf = (KeyFrameTransCompressed*)seq->GetCompressedFrame(l);
                        kf->SetRotation(rot);
                        kf->SetTranslation(trans);
                        // scaling ignored
                        kf->SetTime(fbuf[10]); // absolute time here
                    } else {
                        KeyFrameTrans* kf = (KeyFrameTrans*)seq->GetUncompressedFrame(l);
                        kf->rotation = rot;
                        kf->translation = trans;
                        // scaling ignored
                        kf->deltaTime = fbuf[10]; // absolute time here
                    }
                } else if (hasTranslation) {
                    RwStreamRead(stream, buf, 0x20);
                    CQuaternion rot(fbuf[0], fbuf[1], fbuf[2], fbuf[3]);
                    rot.Conjugate();
                    CVector trans(fbuf[4], fbuf[5], fbuf[6]);

                    if (isCompressed) {
                        KeyFrameTransCompressed* kf = (KeyFrameTransCompressed*)seq->GetCompressedFrame(l);
                        kf->SetRotation(rot);
                        kf->SetTranslation(trans);
                        kf->SetTime(fbuf[7]); // absolute time here
                    } else {
                        KeyFrameTrans* kf = (KeyFrameTrans*)seq->GetUncompressedFrame(l);
                        kf->rotation = rot;
                        kf->translation = trans;
                        kf->deltaTime = fbuf[7]; // absolute time here
                    }
                } else {
                    RwStreamRead(stream, buf, 0x14);
                    CQuaternion rot(fbuf[0], fbuf[1], fbuf[2], fbuf[3]);
                    rot.Conjugate();

                    if (isCompressed) {
                        KeyFrameCompressed* kf = (KeyFrameCompressed*)seq->GetCompressedFrame(l);
                        kf->SetRotation(rot);
                        kf->SetTime(fbuf[4]); // absolute time here
                    } else {
                        KeyFrame* kf = (KeyFrame*)seq->GetUncompressedFrame(l);
                        kf->rotation = rot;
                        kf->deltaTime = fbuf[4]; // absolute time here
                    }
                }
            }
        }

        if (!isCompressed) {
            hier->RemoveQuaternionFlips();
            hier->CalcTotalTime();
        }
    }

    if (animIndex > ms_numAnimations) {
        ms_numAnimations = animIndex;
    }
    
#undef ROUND_SIZE
}

// NOTSA
inline void CAnimManager::LoadAnimFile_ANP23(RwStream* stream, bool compress, bool isANP3) {
    char buf[256];
    char blockName[24];
    int nAnims, nSeq;

    RwStreamRead(stream, &blockName, sizeof(blockName));
    RwStreamRead(stream, &nAnims, sizeof(nAnims));

    CAnimBlock* animBlock = GetAnimationBlock(blockName);
    if (animBlock) {
        if (animBlock->animationCount == 0) {
            animBlock->animationCount = nAnims;
            animBlock->startAnimation = ms_numAnimations;
        }
    } else { // Register a new block
        animBlock = &ms_aAnimBlocks[ms_numAnimBlocks++];
        strncpy_s(animBlock->szName, buf, MAX_ANIM_BLOCK_NAME);
        animBlock->animationCount = nAnims;
        animBlock->startAnimation = ms_numAnimations;
        animBlock->animationStyle = GetFirstAssocGroup(animBlock->szName);
    }

    // debug("Loading ANIMS %s (%d)\n", animBlock->name, nAnims);
    animBlock->bLoaded = true;

    if (!nAnims)
        return;

    auto animIndex = animBlock->startAnimation;
    for (auto j = 0; j < nAnims; j++) {
        assert(animIndex < (int32)std::size(ms_aAnimations));
        CAnimBlendHierarchy* hier = &ms_aAnimations[animIndex++];

        // Each node has a name and key frames
        RwStreamRead(stream, &buf, 24);
        RwStreamRead(stream, &nSeq, 4);
        CAnimBlendSequence* st = nullptr;
        if (isANP3) {
            int n[2];
            RwStreamRead(stream, &n, sizeof(n));
            st = static_cast<CAnimBlendSequence*>(CMemoryMgr::Malloc(n[0]));
            //hier->m_bRunningCompressed = n[1] & 1; // unused?
        }
        hier->SetName(buf);
        hier->m_nSeqCount = nSeq;
        hier->m_pSequences = new CAnimBlendSequence[nSeq]; // (CAnimBlendSequence*)CMemoryMgr::Malloc(nSeq * sizeof(CAnimBlendSequence));
        hier->m_bKeepCompressed = false;

        CAnimBlendSequence* seq = hier->m_pSequences;
        for (auto k = 0; k < hier->m_nSeqCount; k++, seq++) {
            struct {
                int32 type;
                int32 frames_count;
                int32 bone_id;
            } sdata;
            RwStreamRead(stream, &buf, 24);
            RwStreamRead(stream, &sdata, sizeof(sdata));
            seq->SetName(buf);
            seq->SetBoneTag(sdata.bone_id);
            size_t data_size = 0;
            bool bIsRoot, bIsCompressed, bInvalidType = false;
            switch (sdata.type) {
            case 1:
                data_size = sizeof(KeyFrame) * sdata.frames_count;
                bIsRoot = false;
                bIsCompressed = false;
                break;
            case 2:
                data_size = sizeof(KeyFrameTrans) * sdata.frames_count;
                bIsRoot = true;
                bIsCompressed = false;
                break;
            case 3:
                data_size = sizeof(KeyFrameCompressed) * sdata.frames_count;
                bIsRoot = false;
                bIsCompressed = true;
                break;
            case 4:
                data_size = sizeof(KeyFrameTransCompressed) * sdata.frames_count;
                bIsRoot = true;
                bIsCompressed = true;
                break;
            default:
                bInvalidType = true;
                break;
            }
            if (!bInvalidType) {
                if (k == 0) {
                    hier->m_bIsCompressed = bIsCompressed;
                }

                seq->SetNumFrames(sdata.frames_count, bIsRoot, bIsCompressed, st);
                RwStreamRead(stream, seq->m_pFrames, data_size);
                if (isANP3) {
                    // st += data_size; //(void *)((uint32)st + data_size);
                    st = (CAnimBlendSequence*)((size_t)st + data_size);
                    seq->m_usingExternalMemory = true;
                    // seq->usFlags |= EXTERNAL_KEYFRAMES_MEM;
                }
            }
        }
        if (!hier->m_bIsCompressed) {
            hier->RemoveQuaternionFlips();
            hier->CalcTotalTime();
        }
    }

    if (animIndex > ms_numAnimations) {
        ms_numAnimations = animIndex;
    }
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
