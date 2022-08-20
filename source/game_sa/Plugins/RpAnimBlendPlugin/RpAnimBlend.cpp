#include "StdInc.h"

#include "RpAnimBlend.h"

// 0x4D6150
bool RpAnimBlendPluginAttach() {
    return plugin::CallAndReturn<bool, 0x4D6150>();
}

// 0x4D5FA0
void* RtAnimBlendKeyFrameApply(void* result, void* frame) {
    return plugin::CallAndReturn<RwMatrix*, 0x4D5FA0, void*, void*>(result, frame);
    auto matrix = static_cast<RwMatrix*>(result);
    auto quat = static_cast<RtQuat*>(frame);
}

// 0x4D5F50
CAnimBlendClumpData* RpAnimBlendAllocateData(RpClump* clump) {
    return plugin::CallAndReturn<CAnimBlendClumpData*, 0x4D5F50, RpClump*>(clump);
}

// 0x4D6790
CAnimBlendAssociation* RpAnimBlendClumpAddAssociation(RpClump* clump, CAnimBlendAssociation* association, uint32 flags, float startTime, float blendAmount) {
    return plugin::CallAndReturn<CAnimBlendAssociation*, 0x4D6790, RpClump*, CAnimBlendAssociation*, uint32, float, float>(clump, association, flags, startTime, blendAmount);
}

// 0x4D6BE0
CAnimBlendAssociation* RpAnimBlendClumpExtractAssociations(RpClump* clump) {
    return plugin::CallAndReturn<CAnimBlendAssociation*, 0x4D6BE0, RpClump*>(clump);
}

// 0x4D64A0
void RpAnimBlendClumpFillFrameArray(RpClump* clump, AnimBlendFrameData** frameData) {
    plugin::Call<0x4D64A0, RpClump*, AnimBlendFrameData**>(clump, frameData);
}

// 0x4D6400
AnimBlendFrameData* RpAnimBlendClumpFindBone(RpClump* clump, uint32 id) {
    return plugin::CallAndReturn<AnimBlendFrameData*, 0x4D6400, RpClump*, uint32>(clump, id);
}

// 0x4D62A0
AnimBlendFrameData* RpAnimBlendClumpFindFrame(RpClump* clump, const char* name) {
    return plugin::CallAndReturn<AnimBlendFrameData*, 0x4D62A0, RpClump*, const char*>(clump, name);
}

// 0x4D6370
AnimBlendFrameData* RpAnimBlendClumpFindFrameFromHashKey(RpClump* clump, uint32 key) {
    return plugin::CallAndReturn<AnimBlendFrameData*, 0x4D6370, RpClump*, uint32>(clump, key);
}

// 0x4D68E0
CAnimBlendAssociation* RpAnimBlendClumpGetAssociation(RpClump* clump, bool bStopFunctionConfusion, CAnimBlendHierarchy* hierarchy) {
    return plugin::CallAndReturn<CAnimBlendAssociation*, 0x4D68E0, RpClump*, bool, CAnimBlendHierarchy*>(clump, bStopFunctionConfusion, hierarchy);
}

// 0x4D6870
CAnimBlendAssociation* RpAnimBlendClumpGetAssociation(RpClump* clump, const char* name) {
    return plugin::CallAndReturn<CAnimBlendAssociation*, 0x4D6870, RpClump*, const char*>(clump, name);
}

// AnimationId animId
// 0x4D68B0
CAnimBlendAssociation* RpAnimBlendClumpGetAssociation(RpClump* clump, uint32 animId) {
    return plugin::CallAndReturn<CAnimBlendAssociation*, 0x4D68B0, RpClump*, uint32>(clump, animId);
}

// 0x4D15E0
CAnimBlendAssociation* RpAnimBlendClumpGetFirstAssociation(RpClump* clump) {
    return plugin::CallAndReturn<CAnimBlendAssociation*, 0x4D15E0, RpClump*>(clump);
}

// 0x4D6A70
CAnimBlendAssociation* RpAnimBlendClumpGetFirstAssociation(RpClump* clump, uint32 flags) {
    return plugin::CallAndReturn<CAnimBlendAssociation*, 0x4D6A70, RpClump*, uint32>(clump, flags);
}

// 0x4D6910
CAnimBlendAssociation* RpAnimBlendClumpGetMainAssociation(RpClump* clump, CAnimBlendAssociation** pp2ndAnim, float* pBlendVal2nd) {
    return plugin::CallAndReturn<CAnimBlendAssociation*, 0x4D6910, RpClump*, CAnimBlendAssociation**, float*>(clump, pp2ndAnim, pBlendVal2nd);
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

// 0x4D6720
void RpAnimBlendClumpInit(RpClump* clump) {
    plugin::Call<0x4D6720, RpClump*>(clump);
}

// 0x4D6760
bool RpAnimBlendClumpIsInitialized(RpClump* clump) {
    return plugin::CallAndReturn<bool, 0x4D6760, RpClump*>(clump);
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
