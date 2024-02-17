#pragma once

class CAnimBlendClumpData;
class AnimBlendFrameData;
class CAnimBlendAssociation;
struct RtAnimAnimation;

/**
* RpAnimBlend plugin unique rwID
*/
#define rwID_RPANIMBLENDPLUGIN MAKECHUNKID(rwVENDORID_DEVELOPER, 0xFB)

//#define RpAnimBlendClumpGetData(clump) (*(CAnimBlendClumpData **)(((uint32)(clump) + ClumpOffset)))

CAnimBlendClumpData*& RpAnimBlendClumpGetData(RpClump* clump);

namespace RpAnimBlendPlugin {
    void InjectHooks();
};
bool RpAnimBlendPluginAttach();

void RpAnimBlendAllocateData(RpClump* clump);
CAnimBlendAssociation* RpAnimBlendClumpAddAssociation(RpClump* clump, CAnimBlendAssociation* association, uint32 flags, float startTime, float blendAmount);

/*!
 * @notsa
 * @brief 
 * @param clump 
 * @return 
*/
CAnimBlendLink& RpAnimBlendClumpGetAssociations(RpClump* clump);

/*!
 * @notsa
 * @brief Iterate over all associations of a clump
 * @note The IterFn shouldn't modify the clump's association list
 * @param clump The clump containing the associations
 * @param IterFn The function to be called for iterator
*/
template<typename Fn>
void RpAnimBlendClumpForEachAssociation(RpClump* clump, Fn&& IterFn) {
    const auto bd = RpAnimBlendClumpGetData(clump);

    for (auto l = bd->m_AnimList.next; l;) {
        const auto a = CAnimBlendAssociation::FromLink(l);
        l            = a->GetLink().next;
        std::invoke(IterFn, a);
    }
}

/*!
 * @addr 0x4D6BE0
 * @brief Take ownership of all associations of the clump
 * @brief It leaves this clump with no associations
 * @brief The opposite of this function is `RpAnimBlendClumpGiveAssociations`
 * @param clump The clump containing the associations
 * @return The first animation of the clump that has a link to all other animations
*/
CAnimBlendAssociation* RpAnimBlendClumpExtractAssociations(RpClump* clump);

/*!
* @addr 0x4D6BE0
* @brief Give ownership of a list of associations to this clump
* @brief The opposite of this function is `RpAnimBlendClumpExtractAssociations`
* @param clump The clump to give the ownership of associations to
*/
void RpAnimBlendClumpGiveAssociations(RpClump* clump, CAnimBlendAssociation* associations);

void RpAnimBlendClumpFillFrameArray(RpClump* clump, AnimBlendFrameData** frameData);
AnimBlendFrameData* RpAnimBlendClumpFindBone(RpClump* clump, uint32 id);

AnimBlendFrameData* RpAnimBlendClumpFindFrame(RpClump* clump, const char* name);
AnimBlendFrameData* RpAnimBlendClumpFindFrameFromHashKey(RpClump* clump, uint32 key);

/*!
 * @addr 0x4D68E0
 * @brief Find animation of based on a hierarchy
 * @param clump The clump containing the associations
 * @param hierarchy The hierarchy to search for  
 * @return The first animation of the given hierarchy, or null
*/
CAnimBlendAssociation* RpAnimBlendClumpGetAssociation(RpClump* clump, bool, CAnimBlendHierarchy* hierarchy);

/*!
 * @addr 0x4D6870
 * @brief Find animation of the given name
 * @param clump The clump containing the associations
 * @param name Name of the animation to search for
 * @return The first animation with the given name, or null
*/
CAnimBlendAssociation* RpAnimBlendClumpGetAssociation(RpClump* clump, const char* name);

/*!
 * @addr 0x4D6870
 * @brief Find animation of the given id
 * @param clump The clump containing the associations
 * @param animId ID of the animation to search for
 * @return The first animation with the given id, or null
*/
CAnimBlendAssociation* RpAnimBlendClumpGetAssociation(RpClump* clump, uint32 animId);

/*!
 * @brief Get the first animation associated with the clump
 * @param clump The clump containing the associations
 * @return The first animation associated with the clump, or null
*/
CAnimBlendAssociation* RpAnimBlendClumpGetFirstAssociation(RpClump* clump);

/*!
 * @addr 0x4D6A70
 * @param clump The clump containing the associations
 * @param flags The flags of which at least one is expected to be set
 * @return The first anim with any of the flags set, or null if no anims are present on the clump/no anims have the specified flags set.
*/
CAnimBlendAssociation* RpAnimBlendClumpGetFirstAssociation(RpClump* clump, uint32 flags);

/*!
 * @addr 0x4D6910
 * @brief Get the 1st (and optionally 2nd) non-partial animations with the highest blend value
 * @param           clump The clump containing the associations
 * @param [opt,out] pp2ndAnim The 2nd animation
 * @param [opt,out] pBlendVal2nd The 2nd animation's blend amount
 * @return The 1st non-partial animation with the highest blend value, or null
*/
CAnimBlendAssociation* RpAnimBlendClumpGetMainAssociation(RpClump* clump, CAnimBlendAssociation** pp2ndAnim, float* pBlendVal2nd);

/*!
 * @addr 0x4D6A30
 * @brief Get the `n`th non-partial animation
 * @param clump The clump containing the associations
 * @param n The `n`
 * @return The `n`th non-partial animation
*/
CAnimBlendAssociation* RpAnimBlendClumpGetMainAssociation_N(RpClump* clump, uint32 n);

/*!
 * @brief 0x4D69A0
 * @param clump The clump containing the associations
 * @return 
*/
CAnimBlendAssociation* RpAnimBlendClumpGetMainPartialAssociation(RpClump* clump);

/*!
 * @brief 0x4D69F0
 * @brief Get the `n`th partial animation
 * @param clump The clump containing the associations
 * @param n The `n`
 * @return The `n`th partial animation
*/
CAnimBlendAssociation* RpAnimBlendClumpGetMainPartialAssociation_N(RpClump* clump, int32 n);

/*!
 * @brief 0x4D6B60
 * @param clump The clump containing the associations
 * @return The number of associations (anims) this clump has
*/
uint32 RpAnimBlendClumpGetNumAssociations(RpClump* clump);

/*!
* @brief 0x4D6BB0
* @param clump The clump containing the associations
* @return The number of non-partial associations (anims) this clump has
*/
uint32 RpAnimBlendClumpGetNumNonPartialAssociations(RpClump* clump);

/*!
* @brief 0x4D6B80
* @param clump The clump containing the associations
* @return The number of partial associations (anims) this clump has
*/
uint32 RpAnimBlendClumpGetNumPartialAssociations(RpClump* clump);

/*!
 * @addr 0x4D6720
 * @brief Initialize clump data for RpAnimBlend
 * @param clump The clump
*/
void RpAnimBlendClumpInit(RpClump* clump);
bool RpAnimBlendClumpIsInitialized(RpClump* clump);
void RpAnimBlendClumpPauseAllAnimations(RpClump* clump);
void RpAnimBlendClumpUnPauseAllAnimations(RpClump* clump);
void RpAnimBlendClumpRemoveAllAssociations(RpClump* clump);
void RpAnimBlendClumpRemoveAssociations(RpClump* clump, uint32 flags);
void RpAnimBlendClumpSetBlendDeltas(RpClump* clump, uint32 flags, float delta);
void RpAnimBlendClumpUpdateAnimations(RpClump* clump, float step, bool onScreen);
RtAnimAnimation* RpAnimBlendCreateAnimationForHierarchy(RpHAnimHierarchy* hierarchy);
const char* RpAnimBlendFrameGetName(RwFrame* frame);
void RpAnimBlendFrameSetName(RwFrame* frame, const char* name);
CAnimBlendAssociation* RpAnimBlendGetNextAssociation(CAnimBlendAssociation* association);
CAnimBlendAssociation* RpAnimBlendGetNextAssociation(CAnimBlendAssociation* association, uint32 flags);

/*!
* @addr 0x4D5FA0
* @brief Converts a standard keyframe to a matrix
* @param pMatrix A pointer to the output matrix
* @param pVoidIFrame A pointer to the input frame
*/
void RtAnimBlendKeyFrameApply(void* result, void* frame);

void RpAnimBlendKeyFrameInterpolate(void* voidOut, void* voidIn1, void* voidIn2, float time, void* customData);
