#include "rtanim.h"

void RtAnimAnimationFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc) {
    ((void(__cdecl *)(RwInt32, RwInt32))0x7CCC80)(blockSize, numBlocksToPrealloc);
}

RwBool RtAnimInitialize() {
    return ((RwBool(__cdecl *)(void))0x7CCCA0)();
}

RwBool RtAnimRegisterInterpolationScheme(RtAnimInterpolatorInfo* interpolatorInfo) {
    return ((RwBool(__cdecl *)(RtAnimInterpolatorInfo*))0x7CCD40)(interpolatorInfo);
}

RtAnimInterpolatorInfo* RtAnimGetInterpolatorInfo(RwInt32 typeID) {
    return ((RtAnimInterpolatorInfo*(__cdecl *)(RwInt32))0x7CCDE0)(typeID);
}

RtAnimAnimation* RtAnimAnimationCreate(RwInt32 typeID, RwInt32 numFrames, RwInt32 flags, RwReal duration) {
    return ((RtAnimAnimation*(__cdecl *)(RwInt32, RwInt32, RwInt32, RwReal))0x7CCE40)(typeID, numFrames, flags, duration);
}

RwBool RtAnimAnimationDestroy(RtAnimAnimation* animation) {
    return ((RwBool(__cdecl *)(RtAnimAnimation*))0x7CCF10)(animation);
}

RtAnimAnimation* RtAnimAnimationRead(const RwChar* filename) {
    return ((RtAnimAnimation*(__cdecl *)(const RwChar*))0x7CCF30)(filename);
}

RwBool RtAnimAnimationWrite(const RtAnimAnimation* animation, const RwChar* filename) {
    return ((RwBool(__cdecl *)(const RtAnimAnimation*, const RwChar*))0x7CD160)(animation, filename);
}

RtAnimAnimation* RtAnimAnimationStreamRead(RwStream* stream) {
    return ((RtAnimAnimation*(__cdecl *)(RwStream*))0x7CD220)(stream);
}

RwBool RtAnimAnimationStreamWrite(const RtAnimAnimation* animation, RwStream* stream) {
    return ((RwBool(__cdecl *)(const RtAnimAnimation*, RwStream*))0x7CD410)(animation, stream);
}

RwInt32 RtAnimAnimationStreamGetSize(const RtAnimAnimation* animation) {
    return ((RwInt32(__cdecl *)(const RtAnimAnimation*))0x7CD4D0)(animation);
}

RwUInt32 RtAnimAnimationGetNumNodes(const RtAnimAnimation* animation) {
    return ((RwUInt32(__cdecl *)(const RtAnimAnimation*))0x7CD4F0)(animation);
}

RtAnimInterpolator* RtAnimInterpolatorCreate(RwInt32 numNodes, RwInt32 maxInterpKeyFrameSize) {
    return ((RtAnimInterpolator*(__cdecl *)(RwInt32, RwInt32))0x7CD520)(numNodes, maxInterpKeyFrameSize);
}

void RtAnimInterpolatorDestroy(RtAnimInterpolator* anim) {
    ((void(__cdecl *)(RtAnimInterpolator*))0x7CD590)(anim);
}

RwBool RtAnimInterpolatorSetCurrentAnim(RtAnimInterpolator* animI, RtAnimAnimation* anim) {
    return ((RwBool(__cdecl *)(RtAnimInterpolator*, RtAnimAnimation*))0x7CD5A0)(animI, anim);
}

RwBool RtAnimInterpolatorSetKeyFrameCallBacks(RtAnimInterpolator* anim, RwInt32 keyFrameTypeID) {
    return ((RwBool(__cdecl *)(RtAnimInterpolator*, RwInt32))0x7CD660)(anim, keyFrameTypeID);
}

void RtAnimInterpolatorSetAnimLoopCallBack(RtAnimInterpolator* anim, RtAnimCallBack callBack, void* data) {
    ((void(__cdecl *)(RtAnimInterpolator*, RtAnimCallBack, void*))0x7CD6F0)(anim, callBack, data);
}

void RtAnimInterpolatorSetAnimCallBack(RtAnimInterpolator* anim, RtAnimCallBack callBack, RwReal time, void* data) {
    ((void(__cdecl *)(RtAnimInterpolator*, RtAnimCallBack, RwReal, void*))0x7CD710)(anim, callBack, time, data);
}

RwBool RtAnimInterpolatorCopy(RtAnimInterpolator* outAnim, RtAnimInterpolator* inAnim) {
    return ((RwBool(__cdecl *)(RtAnimInterpolator*, RtAnimInterpolator*))0x7CD730)(outAnim, inAnim);
}

RwBool RtAnimInterpolatorSubAnimTime(RtAnimInterpolator* anim, RwReal time) {
    return ((RwBool(__cdecl *)(RtAnimInterpolator*, RwReal))0x7CD760)(anim, time);
}

RwBool RtAnimInterpolatorAddAnimTime(RtAnimInterpolator* anim, RwReal time) {
    return ((RwBool(__cdecl *)(RtAnimInterpolator*, RwReal))0x7CD8D0)(anim, time);
}

RwBool RtAnimInterpolatorSetCurrentTime(RtAnimInterpolator* anim, RwReal time) {
    return ((RwBool(__cdecl *)(RtAnimInterpolator*, RwReal))0x7CDAB0)(anim, time);
}

RwBool RtAnimAnimationMakeDelta(RtAnimAnimation* animation, RwInt32 numNodes, RwReal time) {
    return ((RwBool(__cdecl *)(RtAnimAnimation*, RwInt32, RwReal))0x7CDB00)(animation, numNodes, time);
}

RwBool RtAnimInterpolatorBlend(RtAnimInterpolator* outAnim, RtAnimInterpolator* inAnim1, RtAnimInterpolator* inAnim2, RwReal alpha) {
    return ((RwBool(__cdecl *)(RtAnimInterpolator*, RtAnimInterpolator*, RtAnimInterpolator*, RwReal))0x7CDBF0)(outAnim, inAnim1, inAnim2, alpha);
}

RwBool RtAnimInterpolatorAddTogether(RtAnimInterpolator* outAnim, RtAnimInterpolator* inAnim1, RtAnimInterpolator* inAnim2) {
    return ((RwBool(__cdecl *)(RtAnimInterpolator*, RtAnimInterpolator*, RtAnimInterpolator*))0x7CDC50)(outAnim, inAnim1, inAnim2);
}

RtAnimInterpolator* RtAnimInterpolatorCreateSubInterpolator(RtAnimInterpolator* parentAnim, RwInt32 startNode, RwInt32 numNodes, RwInt32 maxInterpKeyFrameSize) {
    return ((RtAnimInterpolator*(__cdecl *)(RtAnimInterpolator*, RwInt32, RwInt32, RwInt32))0x7CDCB0)(parentAnim, startNode, numNodes, maxInterpKeyFrameSize);
}

RwBool RtAnimInterpolatorBlendSubInterpolator(RtAnimInterpolator* outAnim, RtAnimInterpolator* inAnim1, RtAnimInterpolator* inAnim2, RwReal alpha) {
    return ((RwBool(__cdecl *)(RtAnimInterpolator*, RtAnimInterpolator*, RtAnimInterpolator*, RwReal))0x7CDCF0)(outAnim, inAnim1, inAnim2, alpha);
}

RwBool RtAnimInterpolatorAddSubInterpolator(RtAnimInterpolator* outAnim, RtAnimInterpolator* mainAnim, RtAnimInterpolator* subAnim) {
    return ((RwBool(__cdecl *)(RtAnimInterpolator*, RtAnimInterpolator*, RtAnimInterpolator*))0x7CDEF0)(outAnim, mainAnim, subAnim);
}
