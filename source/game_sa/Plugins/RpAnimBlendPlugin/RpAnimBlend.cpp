#include "StdInc.h"

#include "RpAnimBlend.h"

static uint32& ClumpOffset = *(uint32*)0xB5F878;

CAnimBlendClumpData*& RpAnimBlendClumpGetData(RpClump* clump) {
    return *RWPLUGINOFFSET(CAnimBlendClumpData*, clump, ClumpOffset);
}

// 0x4D5F40
void* ClumpAnimConstruct(void* object, RwInt32 offsetInObject, RwInt32 sizeInObject) {
    const auto clump = static_cast<RpClump*>(object);

    RpAnimBlendClumpGetData(clump) = nullptr;

    return object;
}

// 0x4D6110
void* ClumpAnimDestruct(void* object, RwInt32 offsetInObject, RwInt32 sizeInObject) {
    const auto clump = static_cast<RpClump*>(object);

    if (auto& bd = RpAnimBlendClumpGetData(clump)) {
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
    RpAnimBlendAllocateData(clump);

    const auto bd = RpAnimBlendClumpGetData(clump);

    constexpr size_t MAX_NUM_BONES = 64;

    if (IsClumpSkinned(clump)) { // 0x4D6510 (SkinnedClumpInitAnim)
        const auto skinGeo  = RpAtomicGetGeometry(GetFirstAtomic(clump));
        const auto skin     = RpSkinGeometryGetSkin(skinGeo);
        const auto nBones   = RpSkinGetNumBones(skin);
        const auto rpHAHier = GetAnimHierarchyFromSkinClump(clump);

        bd->SetNumberOfBones(nBones);

        // Get bone positions
        CVector bonePositions[MAX_NUM_BONES];
        { // 0x735360 (SkinGetBonePositionsToTable)
            assert(MAX_NUM_BONES >= nBones);

            bonePositions[0] = CVector{0.f, 0.f, 0.f};

            uint32  nodeStk[MAX_NUM_BONES]{};
            uint32* nodeStkPtr{nodeStk};
            uint32  currNodeIdx{};

            for (uint32 i = 1; i < nBones; i++) { // Intentionally starting at 1
                // Calculate inverse matrix of this bone
                RwMatrix invBoneMat;
                RwMatrixInvert(&invBoneMat, &RpSkinGetSkinToBoneMatrices(skin)[i]); // Originally they did a copy here, not sure why

                // Calculate position of this bone
                RwV3dTransformPoint(
                    &bonePositions[i],
                    RwMatrixGetPos(&invBoneMat),
                    &RpSkinGetSkinToBoneMatrices(skin)[currNodeIdx]
                );

                // Handle node stack now
                const auto nodeFlags = rpHAHier->pNodeInfo[i].flags;
                if (nodeFlags & rpHANIMPUSHPARENTMATRIX) {
                    *++nodeStkPtr = currNodeIdx;
                }
                currNodeIdx = nodeFlags & rpHANIMPOPPARENTMATRIX
                    ? *nodeStkPtr--
                    : i;
            }
        }

        // Now, fill in the frame blend data from the positions we've just calculated
        for (size_t i = 0; i < nBones; i++) {
            const auto fd = &bd->m_FrameDatas[i]; // Frame blend data
            
            fd->KeyFrame = (RpHAnimBlendInterpFrame*)rtANIMGETINTERPFRAME(rpHAHier->currentAnim, i);
            fd->BoneTag  = rpHAHier->pNodeInfo[i].nodeID;
            fd->BonePos  = bonePositions[i];
        }

        // Initialize all frames now
        bd->ForAllFramesF([](AnimBlendFrameData* fd) { // 0x4D6500 (FrameInitCBskin)
            fd->Flags = 0;
        });
    } else { // 0x4D66A0 (RpClumpInitFrameAnim)
        // Recursively count number of frames (bones in this case) in this clump
        uint32 numFrames{};
        struct F {
            static RwFrame* CountFramesCB(RwFrame* f, void* data) {
                auto& numFrames = *static_cast<uint32*>(data);
                numFrames++;
                RwFrameForAllChildren(f, CountFramesCB, &numFrames);
                return f;
            }
        };
        RwFrameForAllChildren(RpClumpGetFrame(clump), F::CountFramesCB, &numFrames);
        bd->SetNumberOfBones(numFrames);

        // Initialize all frames now
        bd->ForAllFramesF([](AnimBlendFrameData* fd) { // 0x4D6640 (FrameInitCBnonskin)
            fd->Flags    = 0;
            fd->FramePos = *RwMatrixGetPos(RwFrameGetMatrix(fd->Frame));
            fd->BoneTag  = BONE_UNKNOWN;
        });
    }
    bd->m_FrameDatas[0].HasVelocity = true;
}

// 0x4D5FA0
void RtAnimBlendKeyFrameApply(void* voidMat, void* voidFrame) { // Semantically same as the original `RpHAnimBlendKeyFrameApply`
    const auto mat   = static_cast<RwMatrix*>(voidMat);
    const auto frame = static_cast<RpHAnimBlendInterpFrame*>(voidFrame);

    RtQuatUnitConvertToMatrix(&frame->q, mat);
    RwV3dAssign(RwMatrixGetPos(mat), &frame->t);
}

// 0x4D60C0
void RpAnimBlendKeyFrameInterpolate(void* voidOut, void* voidIn1, void* voidIn2, float time, void* customData) {
    const auto out = static_cast<RpHAnimBlendInterpFrame*>(voidOut);
    *out = {};
}

// 0x4D5F50
void RpAnimBlendAllocateData(RpClump* clump) {
    RpAnimBlendClumpGetData(clump) = new CAnimBlendClumpData;
}

// 0x4D6790
CAnimBlendAssociation* RpAnimBlendClumpAddAssociation(RpClump* clump, CAnimBlendAssociation* association, uint32 playFlags, float startTime, float blendAmount) {
    NOTSA_UNREACHABLE("Unused function");
}

//! @notsa
CAnimBlendLink& RpAnimBlendClumpGetAssociations(RpClump* clump) {
    const auto bd = RpAnimBlendClumpGetData(clump);

    return bd->m_AnimList;
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
const char* ConvertBoneTag2BoneName(eBoneTag boneTag) { // todo: use eBoneTag32
    switch (boneTag) {
    case BONE_R_BREAST:    return "R Breast";
    case BONE_L_BREAST:    return "L Breast";
    case BONE_BELLY:       return "Belly";
    case BONE_ROOT:      return "Root";
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
    const auto bd = RpAnimBlendClumpGetData(clump);

    const auto next = std::exchange(bd->m_AnimList.next, nullptr);
    return CAnimBlendAssociation::FromLink(next);
}

// 0x4D6C30
void RpAnimBlendClumpGiveAssociations(RpClump* clump, CAnimBlendAssociation* associations) {
    const auto bd = RpAnimBlendClumpGetData(clump);

    // Delete all anims of this clump
    RpAnimBlendClumpRemoveAllAssociations(clump);
    
    // Use new list of associations
    bd->m_AnimList.next = &associations->GetLink();
    associations->GetLink().prev = &bd->m_AnimList;
}

// 0x4D64A0
void RpAnimBlendClumpFillFrameArray(RpClump* clump, AnimBlendFrameData** ppFrameArray) {
    const auto bd = RpAnimBlendClumpGetData(clump);

    if (IsClumpSkinned(clump)) { // 0x4D6450 (FillFrameArrayIndiciesSkinned)
        const auto ah = GetAnimHierarchyFromClump(clump);
        for (size_t i = PED_NODE_UPPER_TORSO; i < TOTAL_PED_NODES; i++) {
            ppFrameArray[i] = &bd->m_FrameDatas[RpHAnimIDGetIndex(ah, ConvertPedNode2BoneTag((ePedNode)i))];
        }
    } else {
        bd->ForAllFrames([](AnimBlendFrameData* fd, void* data) { // 0x4D6430 (FillFrameArrayCBnonskin)
            const auto ppFrameArray = static_cast<AnimBlendFrameData**>(data);

            ppFrameArray[CVisibilityPlugins::GetFrameHierarchyId(fd->Frame)] = fd;
        }, ppFrameArray);
    }
}

// 0x4D6400
AnimBlendFrameData* RpAnimBlendClumpFindBone(RpClump* clump, uint32 id) {
    const auto bd = RpAnimBlendClumpGetData(clump);

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
    const auto bd = RpAnimBlendClumpGetData(clump);

    const auto          needlesv = notsa::ci_string_view{ needle };
    AnimBlendFrameData* ret{};
    if (IsClumpSkinned(clump)) {
        bd->ForAllFramesF([&](AnimBlendFrameData* f) { // 0x4D6240
            const auto boneName = ConvertBoneTag2BoneName((eBoneTag)f->BoneTag);
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
    const auto bd = RpAnimBlendClumpGetData(clump);

    AnimBlendFrameData* ret{};
    if (IsClumpSkinned(clump)) {
        bd->ForAllFramesF([&](AnimBlendFrameData* f) { // 0x4D6310
            const auto boneName = ConvertBoneTag2BoneName((eBoneTag)f->BoneTag);
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

// notsa
template<typename Fn>
CAnimBlendAssociation* RpAnimBlendClumpFindAssociationIf_N(RpClump* clump, Fn&& Pred, size_t n) {
    const auto bd = RpAnimBlendClumpGetData(clump);

    for (auto l = bd->m_AnimList.next; l;) {
        const auto a = CAnimBlendAssociation::FromLink(l);
        if (Pred(a)) {
            if (n-- == 0) {
                return a;
            }
        }
        l = a->GetLink().next;
    }
    return nullptr;   
}

// 0x4D68E0
CAnimBlendAssociation* RpAnimBlendClumpGetAssociation(RpClump* clump, bool, CAnimBlendHierarchy* h) {
    return RpAnimBlendClumpFindAssociationIf_N(clump, [h](CAnimBlendAssociation* a) {
        return a->GetHier() == h;
    }, 0);
}

// 0x4D6870
CAnimBlendAssociation* RpAnimBlendClumpGetAssociation(RpClump* clump, const char* name) {
    return RpAnimBlendClumpFindAssociationIf_N(clump, [nameKey = CKeyGen::GetUppercaseKey(name)](CAnimBlendAssociation* a){
        return a->GetHashKey() == nameKey;
    }, 0);
}

// AnimationId animId
// 0x4D68B0
CAnimBlendAssociation* RpAnimBlendClumpGetAssociation(RpClump* clump, uint32 animId) {
    return RpAnimBlendClumpFindAssociationIf_N(clump, [animId](CAnimBlendAssociation* a){
        return a->GetAnimId() == animId;
    }, 0);
}

// 0x4D15E0
CAnimBlendAssociation* RpAnimBlendClumpGetFirstAssociation(RpClump* clump) {
    const auto bd = RpAnimBlendClumpGetData(clump);

    return RpAnimBlendClumpIsInitialized(clump) && bd->m_AnimList.next
        ? CAnimBlendAssociation::FromLink(bd->m_AnimList.next)
        : nullptr;
}

// 0x4D6A70
CAnimBlendAssociation* RpAnimBlendClumpGetFirstAssociation(RpClump* clump, uint32 flags) {
    return RpAnimBlendClumpFindAssociationIf_N(clump, [flags](CAnimBlendAssociation* a) {
        return a->m_Flags & flags;
    }, 0);
}

// 0x4D6910
CAnimBlendAssociation* RpAnimBlendClumpGetMainAssociation(RpClump* clump, CAnimBlendAssociation** pp2ndAnim, float* pBlendVal2nd) {
    const auto bd = RpAnimBlendClumpGetData(clump);

    CAnimBlendAssociation *aA{}, *aB{};
    float                  bA{}, bB{};
    RpAnimBlendClumpForEachAssociation(clump, [&](CAnimBlendAssociation* a) {
        if (a->IsPartial()) {
            return;
        }
        const auto blend = a->GetBlendAmount();
        if (blend > bA) { // Found a new main?
            aB = std::exchange(aA, a);
            bB = std::exchange(bA, blend);
        } else if (blend > bB) { // Found a new secondary?
            aB = a;
            bB = blend;
        }
    });

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
CAnimBlendAssociation* RpAnimBlendClumpGetMainAssociation_N(RpClump* clump, uint32 n) {
    return RpAnimBlendClumpFindAssociationIf_N(clump, [](CAnimBlendAssociation* a){
        return !a->IsPartial();
    }, n);
}

// 0x4D69A0
CAnimBlendAssociation* RpAnimBlendClumpGetMainPartialAssociation(RpClump* clump) {
    const auto bd = RpAnimBlendClumpGetData(clump);

    CAnimBlendAssociation *mA{};
    float                  mB{};
    RpAnimBlendClumpForEachAssociation(clump, [&](CAnimBlendAssociation* a) {
        if (!a->IsPartial()) {
            return;
        }
        if (a->GetBlendAmount() > mB) {
            mA = a;
            mB = a->GetBlendAmount();
        }
    });
    return mA;
}

// 0x4D69F0
CAnimBlendAssociation* RpAnimBlendClumpGetMainPartialAssociation_N(RpClump* clump, int32 n) {
    return RpAnimBlendClumpFindAssociationIf_N(clump, [](CAnimBlendAssociation* a){
        return a->IsPartial();
    }, n);
}

// notsa
template<typename Fn>
uint32 RpAnimBlendClumpCountAssociationsIf(RpClump* clump, Fn&& Pred) {
    const auto bd = RpAnimBlendClumpGetData(clump);

    uint32 n{};
    RpAnimBlendClumpForEachAssociation(clump, [&](CAnimBlendAssociation* a) {
        if (Pred(a)) {
            n++;
        }
    });
    return n;
}

// 0x4D6B60
uint32 RpAnimBlendClumpGetNumAssociations(RpClump* clump) {
    return RpAnimBlendClumpCountAssociationsIf(clump, [](CAnimBlendAssociation* a){
        return true; // Count all
    });
}

// 0x4D6BB0
uint32 RpAnimBlendClumpGetNumNonPartialAssociations(RpClump* clump) {
    return RpAnimBlendClumpCountAssociationsIf(clump, [](CAnimBlendAssociation* a){
        return !a->IsPartial();
    });
}

// 0x4D6B80
uint32 RpAnimBlendClumpGetNumPartialAssociations(RpClump* clump) {
    return RpAnimBlendClumpCountAssociationsIf(clump, [](CAnimBlendAssociation* a){
        return a->IsPartial();
    });
}

// 0x4D6760
bool RpAnimBlendClumpIsInitialized(RpClump* clump) {
    const auto bd = RpAnimBlendClumpGetData(clump);
    return bd && bd->m_NumFrameData;
}

// 0x4D6B00
void RpAnimBlendClumpPauseAllAnimations(RpClump* clump) {
    RpAnimBlendClumpForEachAssociation(clump, [](CAnimBlendAssociation* a) {
        a->SetFlag(ANIMATION_IS_PLAYING, false);
    });
}

// 0x4D6B30
void RpAnimBlendClumpUnPauseAllAnimations(RpClump* clump) {
    RpAnimBlendClumpForEachAssociation(clump, [](CAnimBlendAssociation* a) {
        a->SetFlag(ANIMATION_IS_PLAYING, true);
    });
}


// 0x4D6C00
void RpAnimBlendClumpRemoveAllAssociations(RpClump* clump) {
    RpAnimBlendClumpForEachAssociation(clump, [](CAnimBlendAssociation* a) {
        delete a;
    });
}

// 0x4D6820
void RpAnimBlendClumpRemoveAssociations(RpClump* clump, uint32 flags) {
    RpAnimBlendClumpForEachAssociation(clump, [=](CAnimBlendAssociation* a) {
        if (!flags || (a->m_Flags & flags)) {
            delete a;
        }
    });
}

// 0x4D67E0
void RpAnimBlendClumpSetBlendDeltas(RpClump* clump, uint32 flags, float delta) {
    RpAnimBlendClumpForEachAssociation(clump, [=](CAnimBlendAssociation* a) {
        if (!flags || (a->m_Flags & flags)) {
            a->SetBlendDelta(delta);
        }
    });
}

struct AnimBlendUpdateData { // OG name
    bool            IncludePartial{};      //!< Has non-moving anim (Eg.: Anim with MOVEMENT flag NOT set)
    CAnimBlendNode* BlendNodeArrays[12]{}; //!< Null terminated array of arrays.
                                           //!< Each entry is incremented on each call of the appropriate `FrameUpdateCallBack`
                                           //!< So that on every call they point to the blend node of the given frame
                                           //!< (This works because the sequences are sorted the same way as the frames apprear in the clump)
};

static auto& gpAnimBlendClump = StaticRef<CAnimBlendClumpData*>(0xB4EA0C);

// 0x4D2E40
void FrameUpdateCallBackCompressedSkinned(AnimBlendFrameData* fd, void* data) {
    const auto c = static_cast<AnimBlendUpdateData*>(data);

    plugin::Call<0x4D2E40>(fd, data);
}
// 0x4D32D0
void FrameUpdateCallBackCompressedNonSkinned(AnimBlendFrameData* fd, void* data) {
    const auto c = static_cast<AnimBlendUpdateData*>(data);

    plugin::Call<0x4D32D0>(fd, data);
}

// 0x4D1A50
void FrameUpdateCallBackSkinnedWith3dVelocityExtraction(AnimBlendUpdateData* c, AnimBlendFrameData* fd) { // `c` is passed in `eax`, can't hook
    _asm {
        pushad
        
        mov ecx, 0x4D1A50

        push fd
        mov eax, c
        call ecx

        popad
    }
}

float CalculateTotalBlendOfPartial(AnimBlendUpdateData* c, AnimBlendFrameData* fd, bool checkDontAddToBlend) {
    float sum{};
    if (c->IncludePartial) {
        for (auto it = c->BlendNodeArrays; *it; it++) {
            const auto node = *it;
            if (!node->IsValid()) {
                continue;
            }

            const auto assoc = node->GetAnimAssoc();
            if (assoc->HasFlag(ANIMATION_IS_PARTIAL) && (!checkDontAddToBlend || !assoc->HasFlag(ANIMATION_DONT_ADD_TO_PARTIAL_BLEND))) {
                sum += assoc->GetBlendAmount();
            }
        }
    }
    return sum;
}

// 0x4D1680
void FrameUpdateCallBackSkinnedWithVelocityExtraction(AnimBlendUpdateData* c, AnimBlendFrameData* fd) { // `c` is passed in `eax`, can't hook
    //_asm {
    //    pushad
    //
    //    mov ecx, 0x4D1680
    //    mov eax, c
    //    push fd
    //    call ecx
    //    add esp, 4
    //
    //    popad
    //};
    //return;
    // 0x4D1707
    const auto totalPartialBlend = CalculateTotalBlendOfPartial(c, fd, true);

    // 0x4D174C
    CVector2D prevTotalV{0.f, 0.f}; // Velocity
    for (auto it = c->BlendNodeArrays; *it; it++) {
        const auto node = *it;

        if (!node->IsValid()) {
            continue;
        }

        if (!node->GetRootKF()->HasTranslation()) {
            continue;
        }

        const auto assoc = node->GetAnimAssoc();
        if (assoc->HasFlag(ANIMATION_IGNORE_ROOT_TRANSLATION) || !assoc->HasFlag(ANIMATION_CAN_EXTRACT_VELOCITY)) {
            continue;
        }

        CVector t;
        node->GetCurrentTranslation(t, 1.f - totalPartialBlend);
        prevTotalV.y += t.y;
        if (assoc->HasFlag(ANIMATION_CAN_EXTRACT_X_VELOCITY)) {
            prevTotalV.x += t.x;
        }
    }

    // 0x4D17C4
    CQuaternion totalQ{}; // Rotation
    CVector     totalT{}; // Translation
    CVector2D   totalV{}, loopedTotalV{}; // 2D Velocity
    bool        hasLoopedVelocity{};
    for (auto it = c->BlendNodeArrays; *it; ++*it, it++) { // NOTE: Increments NodeArray pointer too!
        const auto node = *it;

        if (!node->IsValid()) {
            continue;
        }

        const auto assoc = node->GetAnimAssoc();

        const auto blendScale = 1.f - totalPartialBlend;
        CVector t;
        CQuaternion q;
        const auto looped = node->Update(t, q, blendScale);

        totalQ = q.Dot(totalQ) >= 0.f
            ? totalQ + q
            : totalQ - q;

        if (!node->GetRootKF()->HasTranslation() || assoc->HasFlag(ANIMATION_IGNORE_ROOT_TRANSLATION)) {
            continue;
        }

        totalT += t;

        if (!assoc->HasFlag(ANIMATION_CAN_EXTRACT_VELOCITY)) {
            continue;
        }

        totalV.y += t.y;
        if (assoc->HasFlag(ANIMATION_CAN_EXTRACT_X_VELOCITY)) {
            totalV.x += t.x;
        }

        if (hasLoopedVelocity |= looped) {
            CVector t2;
            node->GetEndTranslation(t2, blendScale);
            loopedTotalV.y += t2.y;
            if (assoc->HasFlag(ANIMATION_CAN_EXTRACT_X_VELOCITY)) {
                loopedTotalV.x += t2.x;
            }
        }
    }

    // 0x4D195C
    if (!fd->NodesDontAffectKeyFrameOrientation) {
        totalQ.Normalise();
        fd->KeyFrame->q = totalQ;
    }

    // 0x4D1980
    if (!fd->NodesDontAffectKeyFrameTranslation) {
        // Update world positions (This moves the ped around the world)
        const auto wsPos = gpAnimBlendClump->m_PedPosition;
        wsPos->x = totalV.x - prevTotalV.x;
        wsPos->y = totalV.y - prevTotalV.y;
        if (hasLoopedVelocity) {
            wsPos->x += loopedTotalV.x;
            wsPos->y += loopedTotalV.y;
        }

        // Update key-frame translation
        const auto kfT = &fd->KeyFrame->t;
        *kfT = totalT - CVector{totalV};
        kfT->x += fd->BonePos.x;
        kfT->x += fd->BonePos.y;
        if (kfT->z >= -0.8f) {
            kfT->z += kfT->z >= -0.4f
                ? fd->BonePos.z
                : (kfT->z * 2.5f + 2.f) * fd->BonePos.z;
        }
    }
}

// 0x4D2B90
void FrameUpdateCallBackSkinned(AnimBlendFrameData* fd, void* data) {
    const auto c = static_cast<AnimBlendUpdateData*>(data);

    if (fd->HasVelocity && gpAnimBlendClump->m_PedPosition) {
        if (fd->HasZVelocity) {
            FrameUpdateCallBackSkinnedWith3dVelocityExtraction(c, fd);
        } else {
            FrameUpdateCallBackSkinnedWithVelocityExtraction(c, fd);
        }
        return;
    }

    // 0x4D2C23
    const auto totalPartialBlend = CalculateTotalBlendOfPartial(c, fd, false);

    // 0x4D2D69 - Calculate new key-frame translation, rotation and blend values
    CVector totalT{};
    CQuaternion totalQ{};
    float kfBlendT{};
    for (auto it = c->BlendNodeArrays; *it; ++*it, it++) { // NOTE: Increments NodeArray pointer too!
        const auto node = *it;

        if (!node->IsValid()) {
            continue;
        }

        CVector t;
        CQuaternion q;
        node->Update(t, q, 1.f - totalPartialBlend);

        // Sum translation
        if (node->GetRootKF()->HasTranslation()) {
            totalT += t;
            kfBlendT += node->GetAnimAssoc()->GetBlendAmount();
        }

        // Sum rotation
        totalQ = totalQ + (q.Dot(totalQ) >= 0.f ? q : -q);
    }

    // 0x4D2D73 - Apply rotation to kf
    if (!fd->NodesDontAffectKeyFrameOrientation) {
        totalQ.Normalise();
        fd->KeyFrame->q = totalQ;
    }

    // 0x4D2D9D - Apply translation to kf
    if (!fd->NodesDontAffectKeyFrameTranslation) {
        fd->KeyFrame->t = lerp<CVector>(fd->BonePos, totalT, kfBlendT);
    }
}

// 0x4D30A0
void FrameUpdateCallBackNonSkinned(AnimBlendFrameData* fd, void* data) {
    const auto c = static_cast<AnimBlendUpdateData*>(data);

    plugin::Call<0x4D30A0>(fd, data);
}

// 0x4D2E10
void FrameUpdateCallBackOffscreen(AnimBlendFrameData* fd, void* data) {
    const auto c = static_cast<AnimBlendUpdateData*>(data);

    if (fd->HasVelocity && gpAnimBlendClump->m_PedPosition) {
        FrameUpdateCallBackSkinnedWithVelocityExtraction(c, fd);
    }
}

// 0x4D1570
// Can't make this function hookable because it doesn't use a proper calling convention
void RpAnimBlendNodeUpdateKeyFrames(AnimBlendUpdateData* c, AnimBlendFrameData* frames, uint32 nFrames) {
    for (auto it = c->BlendNodeArrays; *it; it++) {
        const auto nodeArray = *it; // #nodes == nFrames

        const auto assoc = nodeArray[0].GetAnimAssoc();
        for (size_t frameN = 0; frameN < nFrames; frameN++) {
            const auto fd = &frames[frameN];

            if (fd->HasVelocity && gpAnimBlendClump->m_PedPosition) {
                continue;
            }

            const auto node = &nodeArray[frameN];
            if (!node->IsValid()) {
                continue;
            }

            node->FindKeyFrame(assoc->GetCurrentTime());
        }
    }
}

// 0x4D34F0
void RpAnimBlendClumpUpdateAnimations(RpClump* clump, float timeStep, bool isOnScreen) {
    const auto bd = RpAnimBlendClumpGetData(clump);

    if (bd->m_AnimList.IsEmpty()) {
        return;
    }

    gpAnimBlendClump = bd;

    AnimBlendUpdateData ctx{};
    size_t              nodesCnt{};

    float totalTime{}, totalBlendAmnt{};

    // 0x4D351F
    RpAnimBlendClumpForEachAssociation(clump, [&](CAnimBlendAssociation* a) {
        if (!a->UpdateBlend(timeStep)) {
            return;
        }
        const auto ah = a->GetHier();
        if (ah->GetSequences().empty()) {
            return;
        }
        CAnimManager::UncompressAnimation(a->GetHier());
        if (nodesCnt + 1 <= std::size(ctx.BlendNodeArrays) - 1) { // - 1 for null terminator
            ctx.BlendNodeArrays[nodesCnt++] = a->GetNodesPtr();
        }
        if (a->IsMoving()) {
            totalTime      += ah->GetTotalTime() / a->GetSpeed() * a->GetBlendAmount();
            totalBlendAmnt += a->GetBlendAmount();
        } else {
            ctx.IncludePartial = true;        
        }
    });
    ctx.BlendNodeArrays[nodesCnt] = nullptr; // Null terminator

    // 0x4D35A2 - Update animation's timesteps
    const auto animTimeMult = totalTime == 0.f
        ? 1.f
        : 1.f / totalTime * totalBlendAmnt;
    RpAnimBlendClumpForEachAssociation(clump, [&](CAnimBlendAssociation* a) {
        a->UpdateTimeStep(timeStep, animTimeMult);
    });

    // 0x4D360E - Update all animations's frames
    const auto rootFD = &bd->GetRootFrameData();
    rootFD->IsUpdatingFrame = true;

    if (rootFD->IsCompressed) {
        bd->ForAllFrames(
            IsClumpSkinned(clump)
                ? FrameUpdateCallBackCompressedSkinned
                : FrameUpdateCallBackCompressedNonSkinned,
            &ctx
        );
    } else if (isOnScreen) {
        if (rootFD->NeedsKeyFrameUpdate) {
            RpAnimBlendNodeUpdateKeyFrames(&ctx, bd->m_FrameDatas, bd->m_NumFrameData);
        }

        bd->ForAllFrames(
            IsClumpSkinned(clump)
                ? FrameUpdateCallBackSkinned
                : FrameUpdateCallBackNonSkinned,
            &ctx
        );

        rootFD->NeedsKeyFrameUpdate = false;
    } else {
        bd->ForAllFrames(FrameUpdateCallBackOffscreen, &ctx);
        rootFD->NeedsKeyFrameUpdate = true;
    }

    // 0x4D3715 - Update all animation's times
    RpAnimBlendClumpForEachAssociation(clump, [&](CAnimBlendAssociation* a) {
        a->UpdateTime(timeStep, animTimeMult);
    });
    
    // 0x4D3764
    RwFrameUpdateObjects(RpClumpGetFrame(clump));
}

// 0x4D60E0
RtAnimAnimation* RpAnimBlendCreateAnimationForHierarchy(RpHAnimHierarchy* hierarchy) {
    if (!hierarchy) {
        return nullptr;
    }
    const auto rtA = RtAnimAnimationCreate(
        rwID_RPANIMBLENDPLUGIN,
        0,
        0,
        0.f
    );
    if (rtA) {
        rtA->numFrames = 2 * hierarchy->numNodes;
    }
    return rtA;
}

// 0x4D5EF0
const char* RpAnimBlendFrameGetName(RwFrame* frame) {
    return GetFrameNodeName(frame);
}

// 0x4D5F00
void RpAnimBlendFrameSetName(RwFrame* frame, const char* name) {
    SetFrameNodeName(frame, name);
}

// 0x4D6AB0
CAnimBlendAssociation* RpAnimBlendGetNextAssociation(CAnimBlendAssociation* association) {
    const auto next = association->GetLink().next;
    return next
        ? CAnimBlendAssociation::FromLink(next)
        : nullptr;
}

// 0x4D6AD0
CAnimBlendAssociation* RpAnimBlendGetNextAssociation(CAnimBlendAssociation* association, uint32 flags) {
    for (auto l = association->GetLink().next; l;) {
        const auto a = CAnimBlendAssociation::FromLink(l);
        l            = a->GetLink().next;
        if (a->m_Flags & flags) {
            return a;
        }
    }
    return nullptr;
}

void RpAnimBlendPlugin::InjectHooks() {
    RH_ScopedNamespaceName("RpAnimBlend");
    RH_ScopedCategory("Plugins");

    RH_ScopedGlobalInstall(RpAnimBlendPluginAttach, 0x4D6150);
    RH_ScopedGlobalInstall(RpAnimBlendClumpInit, 0x4D6720);
    RH_ScopedGlobalInstall(ClumpAnimConstruct, 0x4D5F40);
    RH_ScopedGlobalInstall(ClumpAnimDestruct, 0x4D6110);
    RH_ScopedGlobalInstall(ClumpAnimCopy, 0x4D5F90);
    RH_ScopedGlobalInstall(RpAnimBlendAllocateData, 0x4D5F50);
    RH_ScopedGlobalInstall(RtAnimBlendKeyFrameApply, 0x4D5FA0);
    RH_ScopedGlobalInstall(RpAnimBlendKeyFrameInterpolate, 0x4D60C0);
    RH_ScopedGlobalInstall(RpAnimBlendClumpAddAssociation, 0x4D6790);
    RH_ScopedGlobalInstall(RpAnimBlendClumpExtractAssociations, 0x4D6BE0);
    RH_ScopedGlobalInstall(RpAnimBlendClumpGiveAssociations, 0x4D6C30);
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
    RH_ScopedGlobalInstall(RpAnimBlendClumpGetMainAssociation_N, 0x4D6A30);
    RH_ScopedGlobalInstall(RpAnimBlendClumpGetMainPartialAssociation, 0x4D69A0);
    RH_ScopedGlobalInstall(RpAnimBlendClumpGetMainPartialAssociation_N, 0x4D69F0);
    RH_ScopedGlobalInstall(RpAnimBlendClumpGetNumAssociations, 0x4D6B60);
    RH_ScopedGlobalInstall(RpAnimBlendClumpGetNumNonPartialAssociations, 0x4D6BB0);
    RH_ScopedGlobalInstall(RpAnimBlendClumpGetNumPartialAssociations, 0x4D6B80);
    RH_ScopedGlobalInstall(RpAnimBlendClumpIsInitialized, 0x4D6760);
    RH_ScopedGlobalInstall(RpAnimBlendClumpPauseAllAnimations, 0x4D6B00);
    RH_ScopedGlobalInstall(RpAnimBlendClumpUnPauseAllAnimations, 0x4D6B30);
    RH_ScopedGlobalInstall(RpAnimBlendClumpRemoveAllAssociations, 0x4D6C00);
    RH_ScopedGlobalInstall(RpAnimBlendClumpRemoveAssociations, 0x4D6820);
    RH_ScopedGlobalInstall(RpAnimBlendClumpSetBlendDeltas, 0x4D67E0);
    RH_ScopedGlobalInstall(RpAnimBlendCreateAnimationForHierarchy, 0x4D60E0);
    RH_ScopedGlobalInstall(RpAnimBlendFrameGetName, 0x4D5EF0);
    RH_ScopedGlobalInstall(RpAnimBlendFrameSetName, 0x4D5F00);
    RH_ScopedGlobalOverloadedInstall(RpAnimBlendGetNextAssociation, "Any", 0x4D6AB0, CAnimBlendAssociation * (*)(CAnimBlendAssociation * association));
    RH_ScopedGlobalOverloadedInstall(RpAnimBlendGetNextAssociation, "Flags", 0x4D6AD0, CAnimBlendAssociation * (*)(CAnimBlendAssociation * association, uint32 flags));

    RH_ScopedGlobalInstall(FrameUpdateCallBackCompressedSkinned, 0x4D2E40, {.reversed=false});
    RH_ScopedGlobalInstall(FrameUpdateCallBackCompressedNonSkinned, 0x4D32D0, {.reversed=false});
    RH_ScopedGlobalInstall(FrameUpdateCallBackSkinned, 0x4D2B90);
    RH_ScopedGlobalInstall(FrameUpdateCallBackNonSkinned, 0x4D30A0, {.reversed=false});
    RH_ScopedGlobalInstall(FrameUpdateCallBackOffscreen, 0x4D2E10);
    RH_ScopedGlobalInstall(RpAnimBlendClumpUpdateAnimations, 0x4D34F0);
}

