#include "StdInc.h"

#include "RpAnimBlend.h"

static uint32& ClumpOffset = *(uint32*)0xB5F878;

CAnimBlendClumpData*& RpClumpGetAnimBlendClumpData(RpClump* clump) {
    return (*(CAnimBlendClumpData **)(((uint32)(clump) + ClumpOffset)));
}

// 0x4D5F40
void* ClumpAnimConstruct(void* object, RwInt32 offsetInObject, RwInt32 sizeInObject) {
    const auto clump = static_cast<RpClump*>(object);

    RpClumpGetAnimBlendClumpData(clump) = nullptr;

    return object;
}

// 0x4D6110
void* ClumpAnimDestruct(void* object, RwInt32 offsetInObject, RwInt32 sizeInObject) {
    const auto clump = static_cast<RpClump*>(object);

    if (auto& bd = RpClumpGetAnimBlendClumpData(clump)) {
        RpAnimBlendClumpRemoveAllAssociations(clump);
        delete std::exchange(bd, nullptr);
    }

    return object;
}

// 0x4D5F90
void* ClumpAnimCopy(void* dstObject, const void* srcObject, RwInt32 offsetInObject, RwInt32 sizeInObject) {
    return nullptr;
}

// 0x4D6150
bool RpAnimBlendPluginAttach() {
    ClumpOffset = RpClumpRegisterPlugin(
        sizeof(CAnimBlendClumpData*),
        rwID_RPANIMBLENDPLUGIN,
        &ClumpAnimConstruct,
        &ClumpAnimDestruct,
        &ClumpAnimCopy
    );
    if (ClumpOffset == -1) {
        return false;
    }

    RtAnimInterpolatorInfo rtInfo{
        .typeID                  = rwID_RPANIMBLENDPLUGIN,

        .interpKeyFrameSize      = sizeof(RpHAnimBlendInterpFrame),
        .animKeyFrameSize        = sizeof(RpHAnimKeyFrame),

        .keyFrameApplyCB         = RtAnimBlendKeyFrameApply,
        .keyFrameBlendCB         = RpHAnimKeyFrameBlend,
        .keyFrameInterpolateCB   = RpAnimBlendKeyFrameInterpolate,
        .keyFrameAddCB           = RpHAnimKeyFrameAdd,
        .keyFrameMulRecipCB      = RpHAnimKeyFrameMulRecip,
        .keyFrameStreamReadCB    = RpHAnimKeyFrameStreamRead,
        .keyFrameStreamWriteCB   = RpHAnimKeyFrameStreamWrite,
        .keyFrameStreamGetSizeCB = RpHAnimKeyFrameStreamGetSize,

        .customDataSize          = 0
    };
    RtAnimRegisterInterpolationScheme(&rtInfo);

    return true;
}

// 0x4D6720
void RpAnimBlendClumpInit(RpClump* clump) {
    plugin::Call<0x4D6720, RpClump*>(clump);
}

// 0x4D5FA0
void RtAnimBlendKeyFrameApply(void* vMat, void* vFrame) {
    const auto mat   = static_cast<RwMatrix*>(vMat);
    const auto frame = static_cast<RpHAnimBlendInterpFrame*>(vFrame);

    RtQuatUnitConvertToMatrix(&frame->q, mat);
    RwV3dAssign(RwMatrixGetPos(mat), &frame->t);
}

// 0x4D5F50
void RpAnimBlendAllocateData(RpClump* clump) {
    RpClumpGetAnimBlendClumpData(clump) = new CAnimBlendClumpData;
}

// 0x4D6790
CAnimBlendAssociation* RpAnimBlendClumpAddAssociation(RpClump* clump, CAnimBlendAssociation* association, uint32 playFlags, float startTime, float blendAmount) {
    NOTSA_UNREACHABLE();
}

// 0x4D58A0
RwUInt32 ConvertPedNode2BoneTag(ePedNode pedNode) {
    switch (pedNode) {
    case PED_NODE_UPPER_TORSO:     return BONE_SPINE1;
    case PED_NODE_HEAD:            return BONE_HEAD;
    case PED_NODE_LEFT_ARM:        return BONE_L_UPPER_ARM;
    case PED_NODE_RIGHT_ARM:       return BONE_R_UPPER_ARM;
    case PED_NODE_LEFT_HAND:       return BONE_L_HAND;
    case PED_NODE_RIGHT_HAND:      return BONE_R_HAND;
    case PED_NODE_LEFT_LEG:        return BONE_L_THIGH;
    case PED_NODE_RIGHT_LEG:       return BONE_R_THIGH;
    case PED_NODE_LEFT_FOOT:       return BONE_L_FOOT;
    case PED_NODE_RIGHT_FOOT:      return BONE_R_FOOT;
    case PED_NODE_RIGHT_LOWER_LEG: return BONE_R_CALF;
    case PED_NODE_LEFT_LOWER_LEG:  return BONE_L_CALF;
    case PED_NODE_LEFT_LOWER_ARM:  return BONE_L_FORE_ARM;
    case PED_NODE_RIGHT_LOWER_ARM: return BONE_R_FORE_ARM;
    case PED_NODE_LEFT_CLAVICLE:   return BONE_L_CLAVICLE;
    case PED_NODE_RIGHT_CLAVICLE:  return BONE_R_CLAVICLE;
    case PED_NODE_NECK:            return BONE_NECK;
    case PED_NODE_JAW:             return BONE_JAW;
    default:                       return BONE_UNKNOWN;
    }
}

// 0x4D56F0
const char* ConvertBoneTag2BoneName(ePedBones boneTag) { // todo: use eBoneTag32
    switch (boneTag) {
    case BONE_R_BREAST:    return "R Breast";
    case BONE_L_BREAST:    return "L Breast";
    case BONE_BELLY:       return "Belly";
    case BONE_NORMAL:      return "Root";
    case BONE_PELVIS:      return "Pelvis";
    case BONE_SPINE:       return "Spine";
    case BONE_SPINE1:      return "Spine1";
    case BONE_NECK:        return "Neck";
    case BONE_HEAD:        return "Head";
    case BONE_L_BROW:      return "L Brow";
    case BONE_R_BROW:      return "R Brow";
    case BONE_JAW:         return "Jaw";
    case BONE_R_CLAVICLE:  return "Bip01 R Clavicle";
    case BONE_R_UPPER_ARM: return "R UpperArm";
    case BONE_R_FORE_ARM:  return "R Forearm";
    case BONE_R_HAND:      return "R Hand";
    case BONE_R_FINGER:    return "R Fingers";
    case BONE_R_FINGER_01: return "R Finger01";
    case BONE_L_CLAVICLE:  return "Bip01 L Clavicle";
    case BONE_L_UPPER_ARM: return "L UpperArm";
    case BONE_L_FORE_ARM:  return "L Forearm";
    case BONE_L_HAND:      return "L Hand";
    case BONE_L_FINGER:    return "L Fingers";
    case BONE_L_FINGER_01: return "L Finger01";
    case BONE_L_THIGH:     return "L Thigh";
    case BONE_L_CALF:      return "L Calf";
    case BONE_L_FOOT:      return "L Foot";
    case BONE_L_TOE_0:     return "L Toe";
    case BONE_R_THIGH:     return "R Thigh";
    case BONE_R_CALF:      return "R Calf";
    case BONE_R_FOOT:      return "R Foot";
    case BONE_R_TOE_0:     return "R Toe";
    default:               return nullptr;
    }
}

// 0x4D6BE0
CAnimBlendAssociation* RpAnimBlendClumpExtractAssociations(RpClump* clump) {
    const auto bd = RpClumpGetAnimBlendClumpData(clump);

    const auto next = std::exchange(bd->m_AnimList.next, nullptr);
    return CAnimBlendAssociation::FromLink(next);
}

// 0x4D64A0
void RpAnimBlendClumpFillFrameArray(RpClump* clump, AnimBlendFrameData** ppFrameArray) {
    const auto bd = RpClumpGetAnimBlendClumpData(clump);

    if (IsClumpSkinned(clump)) { // 0x4D6450 (FillFrameArrayIndiciesSkinned)
        const auto ah = GetAnimHierarchyFromClump(clump);
        for (size_t i = PED_NODE_UPPER_TORSO; i < TOTAL_PED_NODES; i++) {
            ppFrameArray[i] = &bd->m_Frames[RpHAnimIDGetIndex(ah, ConvertPedNode2BoneTag((ePedNode)i))];
        }
    } else {
        bd->ForAllFrames([](AnimBlendFrameData* f, void* data) { // 0x4D6430 (FillFrameArrayCBnonskin)
            const auto ppFrameArray = static_cast<AnimBlendFrameData**>(data);

            ppFrameArray[CVisibilityPlugins::GetFrameHierarchyId(f->Frame)] = f;
        }, ppFrameArray);
    }
}

// 0x4D6400
AnimBlendFrameData* RpAnimBlendClumpFindBone(RpClump* clump, uint32 id) {
    const auto bd = RpClumpGetAnimBlendClumpData(clump);

    AnimBlendFrameData* ret{};
    bd->ForAllFramesF([&](AnimBlendFrameData* f) {
        if (f->BoneTag == id) {
            ret = f;
        }
    });
    return ret;
}

// 0x4D62A0
AnimBlendFrameData* RpAnimBlendClumpFindFrame(RpClump* clump, const char* needle) {
    const auto bd = RpClumpGetAnimBlendClumpData(clump);

    const auto          needlesv = notsa::ci_string_view{ needle };
    AnimBlendFrameData* ret{};
    if (IsClumpSkinned(clump)) {
        bd->ForAllFramesF([&](AnimBlendFrameData* f) { // 0x4D6240
            const auto boneName = ConvertBoneTag2BoneName((ePedBones)f->BoneTag);
            if (boneName && needlesv == boneName) {
                ret = f;
            }
        });
    } else {
        bd->ForAllFramesF([&](AnimBlendFrameData* f) { // 0x4D6240
            if (needlesv == GetFrameNodeName(f->Frame)) {
                ret = f;
            }
        });
    }
    return ret;
}

// 0x4D6370
AnimBlendFrameData* RpAnimBlendClumpFindFrameFromHashKey(RpClump* clump, uint32 needle) {
    const auto bd = RpClumpGetAnimBlendClumpData(clump);

    AnimBlendFrameData* ret{};
    if (IsClumpSkinned(clump)) {
        bd->ForAllFramesF([&](AnimBlendFrameData* f) { // 0x4D6310
            const auto boneName = ConvertBoneTag2BoneName((ePedBones)f->BoneTag);
            if (boneName && needle == CKeyGen::GetUppercaseKey(boneName)) {
                ret = f;
            }
        });
    } else {
        bd->ForAllFramesF([&](AnimBlendFrameData* f) { // 0x4D6340
            if (needle == CKeyGen::GetUppercaseKey(GetFrameNodeName(f->Frame))) {
                ret = f;
            }
        });
    }
    return ret;
}

// 0x4D68E0
CAnimBlendAssociation* RpAnimBlendClumpGetAssociation(RpClump* clump, bool, CAnimBlendHierarchy* hier) {
    const auto bd = RpClumpGetAnimBlendClumpData(clump);

    for (auto l = bd->m_AnimList.next; l;) {
        const auto a = CAnimBlendAssociation::FromLink(l);
        if (a->GetHier()  == hier) {
            return a;
        }
        l = a->GetLink().next;
    }
    return nullptr;
}

// 0x4D6870
CAnimBlendAssociation* RpAnimBlendClumpGetAssociation(RpClump* clump, const char* name) {
    const auto bd = RpClumpGetAnimBlendClumpData(clump);

    const auto needle = CKeyGen::GetUppercaseKey(name);
    for (auto l = bd->m_AnimList.next; l;) {
        const auto a = CAnimBlendAssociation::FromLink(l);
        if (a->GetHashKey() == needle) {
            return a;
        }
        l = a->GetLink().next;
    }
    return nullptr;
}

// AnimationId animId
// 0x4D68B0
CAnimBlendAssociation* RpAnimBlendClumpGetAssociation(RpClump* clump, uint32 animId) {
    const auto bd = RpClumpGetAnimBlendClumpData(clump);

    for (auto l = bd->m_AnimList.next; l;) {
        const auto a = CAnimBlendAssociation::FromLink(l);
        if (a->GetAnimId() == animId) {
            return a;
        }
        l = a->GetLink().next;
    }
    return nullptr;
}

// 0x4D15E0
CAnimBlendAssociation* RpAnimBlendClumpGetFirstAssociation(RpClump* clump) {
    const auto bd = RpClumpGetAnimBlendClumpData(clump);

    return RpAnimBlendClumpIsInitialized(clump) && bd->m_AnimList.next
        ? CAnimBlendAssociation::FromLink(bd->m_AnimList.next)
        : nullptr;
}

// 0x4D6A70
CAnimBlendAssociation* RpAnimBlendClumpGetFirstAssociation(RpClump* clump, uint32 flags) {
    const auto bd = RpClumpGetAnimBlendClumpData(clump);

    for (auto l = bd->m_AnimList.next; l;) {
        const auto a = CAnimBlendAssociation::FromLink(l);
        if (a->m_Flags & flags) {
            return a;
        }
        l = a->GetLink().next;
    }
    return nullptr;
}

// 0x4D6910
CAnimBlendAssociation* RpAnimBlendClumpGetMainAssociation(RpClump* clump, CAnimBlendAssociation** pp2ndAnim, float* pBlendVal2nd) {
    const auto bd = RpClumpGetAnimBlendClumpData(clump);

    CAnimBlendAssociation *aA{}, *aB{};
    float                  bA{}, bB{};
    for (auto l = bd->m_AnimList.next; l;) {
        const auto a = CAnimBlendAssociation::FromLink(l);
        if (!a->IsPartial()) {
            const auto blend = a->GetBlendAmount();
            if (blend > bA) { // Found a new main?
                aB = std::exchange(aA, a);
                bB = std::exchange(bA, blend);
            } else if (blend > bB) { // Found a new secondary?
                aB = a;
                bB = blend;
            }
        }
        l = a->GetLink().next;
    }


    if (pp2ndAnim) {
        *pp2ndAnim = aB;
    }
    if (pBlendVal2nd) {
        *pBlendVal2nd = bB;
    }

    return aA;

    /*
    * Code works, but i think it I overcomplicated it....
    // Array sorted descending by blend amount
    struct {
        CAnimBlendAssociation* anim{};
        float                  blendAmnt{};
    } sorted[2];

    // Fill array
    for (auto l = bd->m_AnimList.next; l;) {
        const auto a = CAnimBlendAssociation::FromLink(l);
        if (!a->IsPartial()) {
            const auto it = rng::upper_bound(
                sorted,
                a->GetBlendAmount(),
                [](float l, float r) { return l > r; }, // Descending
                [](auto& v) { return v.blendAmnt; }     // By blend amount
            );
            if (it != std::end(sorted)) {
                std::shift_right(it, std::end(sorted), 1); // Make space for insert
                *it = { a, a->GetBlendAmount() };
            }
        }
        l = a->GetLink().next;
    }

    if (pp2ndAnim) {
        *pp2ndAnim = sorted[1].anim;
    }
    if (pBlendVal2nd) {
        *pBlendVal2nd = sorted[1].blendAmnt;
    }

    return sorted[0].anim;
    */
}

// 0x4D6A30
CAnimBlendAssociation* RpAnimBlendClumpGetMainAssociation_N(RpClump* clump, int32 n) {
    return plugin::CallAndReturn<CAnimBlendAssociation*, 0x4D6A30, RpClump*, int32>(clump, n);
}

// 0x4D69A0
CAnimBlendAssociation* RpAnimBlendClumpGetMainPartialAssociation(RpClump* clump) {
    return plugin::CallAndReturn<CAnimBlendAssociation*, 0x4D69A0, RpClump*>(clump);
}

// 0x4D69F0
CAnimBlendAssociation* RpAnimBlendClumpGetMainPartialAssociation_N(RpClump* clump, int32 n) {
    return plugin::CallAndReturn<CAnimBlendAssociation*, 0x4D69F0, RpClump*, int32>(clump, n);
}

// 0x4D6B60
uint32 RpAnimBlendClumpGetNumAssociations(RpClump* clump) {
    return plugin::CallAndReturn<uint32, 0x4D6B60, RpClump*>(clump);
}

// 0x4D6BB0
uint32 RpAnimBlendClumpGetNumNonPartialAssociations(RpClump* clump) {
    return plugin::CallAndReturn<uint32, 0x4D6BB0, RpClump*>(clump);
}

// 0x4D6B80
uint32 RpAnimBlendClumpGetNumPartialAssociations(RpClump* clump) {
    return plugin::CallAndReturn<uint32, 0x4D6B80, RpClump*>(clump);
}

// 0x4D6C30
void RpAnimBlendClumpGiveAssociations(RpClump* clump, CAnimBlendAssociation* association) {
    plugin::Call<0x4D6C30, RpClump*, CAnimBlendAssociation*>(clump, association);
}

// 0x4D6760
bool RpAnimBlendClumpIsInitialized(RpClump* clump) {
    const auto bd = RpClumpGetAnimBlendClumpData(clump);
    return bd && bd->m_NumFrames;
}

// 0x4D6B00
void RpAnimBlendClumpPauseAllAnimations(RpClump* clump) {
    plugin::Call<0x4D6B00, RpClump*>(clump);
}

// 0x4D6C00
void RpAnimBlendClumpRemoveAllAssociations(RpClump* clump) {
    plugin::Call<0x4D6C00, RpClump*>(clump);
}

// 0x4D6820
void RpAnimBlendClumpRemoveAssociations(RpClump* clump, uint32 flags) {
    plugin::Call<0x4D6820, RpClump*, uint32>(clump, flags);
}

// 0x4D67E0
void RpAnimBlendClumpSetBlendDeltas(RpClump* clump, uint32 flags, float delta) {
    plugin::Call<0x4D67E0, RpClump*, uint32, float>(clump, flags, delta);
}

// 0x4D6B30
void RpAnimBlendClumpUnPauseAllAnimations(RpClump* clump) {
    plugin::Call<0x4D6B30, RpClump*>(clump);
}

// 0x4D34F0
void RpAnimBlendClumpUpdateAnimations(RpClump* clump, float step, bool onScreen) {
    plugin::Call<0x4D34F0, RpClump*, float, bool>(clump, step, onScreen);
}

// 0x4D60E0
RtAnimAnimation* RpAnimBlendCreateAnimationForHierarchy(RpHAnimHierarchy* hierarchy) {
    return plugin::CallAndReturn<RtAnimAnimation*, 0x4D60E0, RpHAnimHierarchy*>(hierarchy);
}

// 0x4D5EF0
char* RpAnimBlendFrameGetName(RwFrame* frame) {
    return plugin::CallAndReturn<char*, 0x4D5EF0, RwFrame*>(frame);
}

// 0x4D5F00
void RpAnimBlendFrameSetName(RwFrame* frame, char* name) {
    plugin::Call<0x4D5F00, RwFrame*, char*>(frame, name);
}

// 0x4D6AB0
CAnimBlendAssociation* RpAnimBlendGetNextAssociation(CAnimBlendAssociation* association) {
    return plugin::CallAndReturn<CAnimBlendAssociation*, 0x4D6AB0, CAnimBlendAssociation*>(association);
}

// 0x4D6AD0
CAnimBlendAssociation* RpAnimBlendGetNextAssociation(CAnimBlendAssociation* association, uint32 flags) {
    return plugin::CallAndReturn<CAnimBlendAssociation*, 0x4D6AD0, CAnimBlendAssociation*, uint32>(association, flags);
}

// 0x4D60C0
void RpAnimBlendKeyFrameInterpolate(void* voidOut, void* voidIn1, void* voidIn2, float time, void* customData) {
    plugin::Call<0x4D60C0, void*, void*, void*, float, void*>(voidOut, voidIn1, voidIn2, time, customData);
}

void RpAnimBlendPlugin::InjectHooks() {
    RH_ScopedNamespaceName("RpAnimBlend");
    RH_ScopedCategory("Plugins");

    RH_ScopedGlobalInstall(RpAnimBlendPluginAttach, 0x4D6150);
    RH_ScopedGlobalInstall(RpAnimBlendClumpInit, 0x4D6720, { .reversed = false });
    RH_ScopedGlobalInstall(ClumpAnimConstruct, 0x4D5F40);
    RH_ScopedGlobalInstall(ClumpAnimDestruct, 0x4D6110);
    RH_ScopedGlobalInstall(ClumpAnimCopy, 0x4D5F90);
    RH_ScopedGlobalInstall(RpAnimBlendAllocateData, 0x4D5F50);
    RH_ScopedGlobalInstall(RtAnimBlendKeyFrameApply, 0x4D5FA0);
    RH_ScopedGlobalInstall(RpAnimBlendClumpAddAssociation, 0x4D6790);
    RH_ScopedGlobalInstall(RpAnimBlendClumpExtractAssociations, 0x4D6BE0);
    RH_ScopedGlobalInstall(RpAnimBlendClumpFillFrameArray, 0x4D64A0);
    RH_ScopedGlobalInstall(RpAnimBlendClumpFindBone, 0x4D6400);
    RH_ScopedGlobalInstall(RpAnimBlendClumpFindFrame, 0x4D62A0);
    RH_ScopedGlobalInstall(RpAnimBlendClumpFindFrameFromHashKey, 0x4D6370);
    RH_ScopedGlobalOverloadedInstall(RpAnimBlendClumpGetAssociation, "Hier", 0x4D68E0, CAnimBlendAssociation*(*)(RpClump*, bool, CAnimBlendHierarchy*));
    RH_ScopedGlobalOverloadedInstall(RpAnimBlendClumpGetAssociation, "AnimName", 0x4D6870, CAnimBlendAssociation*(*)(RpClump*, const char*));
    RH_ScopedGlobalOverloadedInstall(RpAnimBlendClumpGetAssociation, "AnimId", 0x4D68B0, CAnimBlendAssociation*(*)(RpClump*, uint32));
    RH_ScopedGlobalOverloadedInstall(RpAnimBlendClumpGetFirstAssociation, "", 0x4D15E0, CAnimBlendAssociation*(*)(RpClump*));
    RH_ScopedGlobalOverloadedInstall(RpAnimBlendClumpGetFirstAssociation, "Flags", 0x4D6A70, CAnimBlendAssociation*(*)(RpClump*, uint32));
    RH_ScopedGlobalInstall(RpAnimBlendClumpGetMainAssociation, 0x4D6910);
    RH_ScopedGlobalInstall(RpAnimBlendClumpGetMainAssociation_N, 0x4D6A30, { .reversed = false });
    RH_ScopedGlobalInstall(RpAnimBlendClumpGetMainPartialAssociation, 0x4D69A0, { .reversed = false });
    RH_ScopedGlobalInstall(RpAnimBlendClumpGetMainPartialAssociation_N, 0x4D69F0, { .reversed = false });
    RH_ScopedGlobalInstall(RpAnimBlendClumpGetNumAssociations, 0x4D6B60, { .reversed = false });
    RH_ScopedGlobalInstall(RpAnimBlendClumpGetNumNonPartialAssociations, 0x4D6BB0, { .reversed = false });
    RH_ScopedGlobalInstall(RpAnimBlendClumpGetNumPartialAssociations, 0x4D6B80, { .reversed = false });
    RH_ScopedGlobalInstall(RpAnimBlendClumpGiveAssociations, 0x4D6C30, { .reversed = false });
    RH_ScopedGlobalInstall(RpAnimBlendClumpIsInitialized, 0x4D6760);
    RH_ScopedGlobalInstall(RpAnimBlendClumpPauseAllAnimations, 0x4D6B00, { .reversed = false });
    RH_ScopedGlobalInstall(RpAnimBlendClumpRemoveAllAssociations, 0x4D6C00, { .reversed = false });
    RH_ScopedGlobalInstall(RpAnimBlendClumpRemoveAssociations, 0x4D6820, { .reversed = false });
    RH_ScopedGlobalInstall(RpAnimBlendClumpSetBlendDeltas, 0x4D67E0, { .reversed = false });
    RH_ScopedGlobalInstall(RpAnimBlendClumpUnPauseAllAnimations, 0x4D6B30, { .reversed = false });
    RH_ScopedGlobalInstall(RpAnimBlendClumpUpdateAnimations, 0x4D34F0, { .reversed = false });
    RH_ScopedGlobalInstall(RpAnimBlendCreateAnimationForHierarchy, 0x4D60E0, { .reversed = false });
    RH_ScopedGlobalInstall(RpAnimBlendFrameGetName, 0x4D5EF0, { .reversed = false });
    RH_ScopedGlobalInstall(RpAnimBlendFrameSetName, 0x4D5F00, { .reversed = false });
    //RH_ScopedGlobalInstall(RpAnimBlendGetNextAssociation, 0x4D6AB0);
    //RH_ScopedGlobalInstall(RpAnimBlendGetNextAssociation, 0x4D6AD0);
    RH_ScopedGlobalInstall(RpAnimBlendKeyFrameInterpolate, 0x4D60C0, { .reversed = false });
}

