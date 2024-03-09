/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

#include "AnimBlendAssociation.h"
#include "AnimBlendStaticAssociation.h"
#include "RenderWare.h"
#include "AnimBlock.h"
#include "AnimBlendAssocGroup.h"

void CAnimBlendAssocGroup::InjectHooks() {
    RH_ScopedClass(CAnimBlendAssocGroup);
    RH_ScopedCategory("Animation");

    RH_ScopedInstall(Constructor, 0x4CDE70);
    RH_ScopedInstall(Destructor, 0x4CE1D0);

    RH_ScopedInstall(GetNumAnimations, 0x45B050);
    RH_ScopedInstall(GetAnimBlock, 0x45B060);
    RH_ScopedInstall(InitEmptyAssociations, 0x4CDFB0);
    RH_ScopedInstall(DestroyAssociations, 0x4CDFF0);
    RH_ScopedOverloadedInstall(GetAnimation, "Name", 0x4CE040, CAnimBlendStaticAssociation *(CAnimBlendAssocGroup::*)(const char*));
    RH_ScopedOverloadedInstall(GetAnimation, "AnimationId", 0x4CE090, CAnimBlendStaticAssociation *(CAnimBlendAssocGroup::*)(AnimationId));
    RH_ScopedOverloadedInstall(CopyAnimation, "Name", 0x4CE0B0, CAnimBlendAssociation *(CAnimBlendAssocGroup::*)(const char*));
    RH_ScopedOverloadedInstall(CopyAnimation, "AnimationId", 0x4CE130, CAnimBlendAssociation *(CAnimBlendAssocGroup::*)(AnimationId));
    RH_ScopedInstall(GetAnimationId, 0x4CE1B0);
    RH_ScopedOverloadedInstall(CreateAssociations, "1", 0x4CE220, void(CAnimBlendAssocGroup::*)(const char*), { .reversed = false });
    RH_ScopedOverloadedInstall(CreateAssociations, "2", 0x4CE6E0, void(CAnimBlendAssocGroup::*)(const char*, RpClump*, const char**, uint32));
    RH_ScopedOverloadedInstall(CreateAssociations, "3", 0x4CE3B0, void(CAnimBlendAssocGroup::*)(const char*, const char*, const char*, uint32));
    //RH_ScopedOverloadedInstall(CreateAssociations, "", 0x4CE5C0, void(CAnimBlendAssocGroup::*)(const char*, RpClump*), { .reversed = false });
    RH_ScopedInstall(IsCreated, 0x4D37A0);
}

// 0x4CE0B0
CAnimBlendAssociation* CAnimBlendAssocGroup::CopyAnimation(const char* name) {
    return CopyAnimation(GetAnimation(name));
}

// 0x4CE130
CAnimBlendAssociation* CAnimBlendAssocGroup::CopyAnimation(AnimationId id) {
    return CopyAnimation(GetAnimation(id));
}

// Implementation
CAnimBlendAssociation* CAnimBlendAssocGroup::CopyAnimation(CAnimBlendStaticAssociation* anim) {
    if (!anim) {
        return nullptr;
    }
    CAnimManager::UncompressAnimation(anim->m_BlendHier);
    return new CAnimBlendAssociation(*anim);
}

// notsa
void CAnimBlendAssocGroup::CreateAssociation(CAnimBlendStaticAssociation* assoc, CAnimBlendHierarchy* anim, CBaseModelInfo* mi, size_t i) {
    const auto clump = reinterpret_cast<RpClump*>(mi->CreateInstance());
    RpAnimBlendClumpInit(clump);
    assoc->Init(clump, anim);
#ifdef SA_SKINNED_PEDS
    if (IsClumpSkinned(clump)) {
        RpClumpForAllAtomics(clump, AtomicRemoveAnimFromSkinCB, nullptr);
    }
#endif
    RpClumpDestroy(clump);

    assoc->m_AnimId      = (AnimationId)(m_IdOffset + i);
    assoc->m_AnimGroupId = (AssocGroupId)(m_GroupID);
}

// 0x4CE220
void CAnimBlendAssocGroup::CreateAssociations(const char* blockName) {
    ZoneScoped;

    const auto ablock = AllocateForBlock(blockName, -1);

    for (size_t i = 0; i < ablock->NumAnims; i++) {
        const auto id    = (AnimationId)(ablock->FirstAnimIdx + i);
        const auto anim  = &CAnimManager::GetAnimation(id);
        const auto assoc = &GetAssociations()[i];
        const auto mi    = CModelInfo::GetModelInfoFromHashKey(anim->m_hashKey);
        if (!mi) {
            NOTSA_LOG_WARN("ModelInfo (Key={}) for animation(Block={}; ID={}) not found", anim->m_hashKey, blockName, (int)id);
            continue;
        }
        CreateAssociation(assoc, anim, mi, i);
    }

    NOTSA_LOG_DEBUG("Created #{} associations for block ({})", m_NumAnims, blockName);
}

// 0x4CE3B0
void CAnimBlendAssocGroup::CreateAssociations(const char* blockName, const char* animNames, const char* modelNames, uint32 strBufLen) {
    ZoneScoped;

    if (!modelNames) {
        CreateAssociations(blockName);
        return;
    }

    const auto ablock = AllocateForBlock(blockName, -1);

    for (size_t i = 0; i < ablock->NumAnims; i++) {
        const auto id    = (AnimationId)(ablock->FirstAnimIdx + i);
        const auto anim  = &CAnimManager::GetAnimation(id);
        const auto assoc = &GetAssociations()[i];

        // Find model name for this animation
        // Remember that these 2 arrays (animNames, modelNames) are "paralell" (like kv pairs)
        // So here we're basically searching for the index of the animation and then just returning the
        // associated modelNames
        for (size_t k = 0; k < ablock->NumAnims; k++) {
            const auto bufOff = k * strBufLen;
            if (CKeyGen::GetUppercaseKey(animNames + bufOff) == anim->GetHashKey()) {
                continue;

            }
            const auto modelName = modelNames + bufOff;

            CModelInfo::ms_lastPositionSearched = 0; // Why?
            const auto mi = CModelInfo::GetModelInfo(modelName);
            if (!mi) {
                NOTSA_LOG_WARN("ModelInfo (\"{}\") for animation(Block={}; ID={}) not found", modelName, blockName, (int)id);
                continue;
            }

            CreateAssociation(assoc, anim, mi, i);

            NOTSA_LOG_DEBUG("Associated model (\"{}\") with animation(Block={}; ID={})", modelName, blockName, (int)id);

            break;
        }
    }

    NOTSA_LOG_DEBUG("Created #{} associations for block ({})", m_NumAnims, blockName);
}

// 0x4CE6E0
void CAnimBlendAssocGroup::CreateAssociations(const char* blockName, RpClump* clump, const char** names, uint32 cnt) {
    ZoneScoped;

    const auto ablock = AllocateForBlock(blockName, cnt);

    for (size_t i = 0; i < cnt; i++) {
        const auto name  = names[i];
        const auto assoc = &GetAssociations()[i];

        if (name[0]) { // Check is empty string
            assoc->Init(clump, CAnimManager::GetAnimation(name, m_AnimBlock));
            assoc->m_AnimId = (AnimationId)(m_IdOffset + i);
        } else {
            assoc->m_AnimId = ANIM_ID_UNDEFINED;
        }

        assoc->m_AnimGroupId = m_GroupID;
    }

    NOTSA_LOG_DEBUG("Created #{} associations for block ({})", m_NumAnims, blockName);
}

// 0x4CDFF0
void CAnimBlendAssocGroup::DestroyAssociations() {
    if (!m_Anims) {
        return;
    }
    delete m_Anims;
    m_Anims    = nullptr;
    m_NumAnims = 0;
}

// 0x4CE040
CAnimBlendStaticAssociation* CAnimBlendAssocGroup::GetAnimation(const char* name) {
    const auto key = CKeyGen::GetUppercaseKey(name);
    for (auto& a : GetAssociations()) {
        if (a.GetHashKey() == key) {
            return &a;
        }
    }
    return nullptr;
}

// 0x4CE090
CAnimBlendStaticAssociation* CAnimBlendAssocGroup::GetAnimation(AnimationId id) {
    return &GetAssociations()[id - m_IdOffset];
}

// 0x4CE1B0
AnimationId CAnimBlendAssocGroup::GetAnimationId(const char* AnimName) {
    if (const auto a = GetAnimation(AnimName)) {
        return a->m_AnimId;
    }
    return ANIM_ID_UNDEFINED;
}

// 0x4CDFB0
void CAnimBlendAssocGroup::InitEmptyAssociations(RpClump* clump) {
    for (size_t i = m_NumAnims; i-- > 0;) {
        const auto anim = &GetAssociations()[i];
        if (!anim->IsValid()) {
            anim->Init(clump, anim->GetAnimHierarchy());
        }
    }
}

// notsa
CAnimBlock* CAnimBlendAssocGroup::AllocateForBlock(const char* blockName, int32 numAnims) {
    if (m_Anims) {
        DestroyAssociations();
    }

    const auto ablock = CAnimManager::GetAnimationBlock(blockName);

    if (numAnims == -1) {
        numAnims = (int32)ablock->NumAnims;
    }

    m_AnimBlock = ablock;
    m_Anims     = new CAnimBlendStaticAssociation[numAnims];
    m_NumAnims  = numAnims;

    return ablock;
}

// 0x4CE1D0
CAnimBlendAssocGroup::~CAnimBlendAssocGroup() {
    DestroyAssociations();
}
