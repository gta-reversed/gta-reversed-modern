#pragma once

static inline uint32& ClumpOffset = *(uint32*)0xB5F878;

#define RpClumpGetAnimBlendClumpData(clump) (*(CAnimBlendClumpData **)(((uint32)(clump) + ClumpOffset)))

bool RpAnimBlendPluginAttach();

CAnimBlendClumpData* RpAnimBlendAllocateData(RpClump* clump);
CAnimBlendAssociation* RpAnimBlendClumpAddAssociation(RpClump* clump, CAnimBlendAssociation* association, uint32 flags, float startTime, float blendAmount);
CAnimBlendAssociation* RpAnimBlendClumpExtractAssociations(RpClump* clump);
void RpAnimBlendClumpFillFrameArray(RpClump* clump, AnimBlendFrameData** frameData);
AnimBlendFrameData* RpAnimBlendClumpFindBone(RpClump* clump, uint32 id);

AnimBlendFrameData* RpAnimBlendClumpFindFrame(RpClump* clump, const char* name);
AnimBlendFrameData* RpAnimBlendClumpFindFrameFromHashKey(RpClump* clump, uint32 key);

CAnimBlendAssociation* RpAnimBlendClumpGetAssociation(RpClump* clump, bool bStopFunctionConfusion, CAnimBlendHierarchy* hierarchy);
CAnimBlendAssociation* RpAnimBlendClumpGetAssociation(RpClump* clump, const char* name);
CAnimBlendAssociation* RpAnimBlendClumpGetAssociation(RpClump* clump, uint32 animId);

CAnimBlendAssociation* RpAnimBlendClumpGetFirstAssociation(RpClump* clump);
CAnimBlendAssociation* RpAnimBlendClumpGetFirstAssociation(RpClump* clump, uint32 flags);

CAnimBlendAssociation* RpAnimBlendClumpGetMainAssociation(RpClump* clump, CAnimBlendAssociation** pp2ndAnim, float* pBlendVal2nd);
CAnimBlendAssociation* RpAnimBlendClumpGetMainAssociation_N(RpClump* clump, int32 n);

CAnimBlendAssociation* RpAnimBlendClumpGetMainPartialAssociation(RpClump* clump);
CAnimBlendAssociation* RpAnimBlendClumpGetMainPartialAssociation_N(RpClump* clump, int32 n);

uint32 RpAnimBlendClumpGetNumAssociations(RpClump* clump);
uint32 RpAnimBlendClumpGetNumNonPartialAssociations(RpClump* clump);
uint32 RpAnimBlendClumpGetNumPartialAssociations(RpClump* clump);

void RpAnimBlendClumpGiveAssociations(RpClump* clump, CAnimBlendAssociation* association);
void RpAnimBlendClumpInit(RpClump* clump);
bool RpAnimBlendClumpIsInitialized(RpClump* clump);
void RpAnimBlendClumpPauseAllAnimations(RpClump* clump);
void RpAnimBlendClumpRemoveAllAssociations(RpClump* clump);
void RpAnimBlendClumpRemoveAssociations(RpClump* clump, uint32 flags);
void RpAnimBlendClumpSetBlendDeltas(RpClump* clump, uint32 flags, float delta);
void RpAnimBlendClumpUnPauseAllAnimations(RpClump* clump);
void RpAnimBlendClumpUpdateAnimations(RpClump* clump, float step, bool onScreen);
RtAnimAnimation* RpAnimBlendCreateAnimationForHierarchy(RpHAnimHierarchy* hierarchy);
char* RpAnimBlendFrameGetName(RwFrame* frame);
void RpAnimBlendFrameSetName(RwFrame* frame, char* name);
CAnimBlendAssociation* RpAnimBlendGetNextAssociation(CAnimBlendAssociation* association);
CAnimBlendAssociation* RpAnimBlendGetNextAssociation(CAnimBlendAssociation* association, uint32 flags);
void RpAnimBlendKeyFrameInterpolate(void* voidOut, void* voidIn1, void* voidIn2, float time, void* customData);
void* RtAnimBlendKeyFrameApply(void* result, void* frame);

/*!
* @notsa
* @brief Iterate over all the anims associated with the clump
*/
void RpAnimBlendClumpIterateAssociations(RpClump* clump, auto&& IterFn) {
    for (auto a = RpAnimBlendClumpGetFirstAssociation(clump); a; a = RpAnimBlendGetNextAssociation(a)) {
        if (!IterFn(a)) {
            break;
        }
    }
}
