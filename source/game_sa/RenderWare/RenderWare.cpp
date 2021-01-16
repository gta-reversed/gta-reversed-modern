/*
Plugin-SDK (Grand Theft Auto San Andreas) source file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

RwGlobals *&RwEngineInstance = *(RwGlobals **)0xC97B24;

RsGlobalType &RsGlobal = *(RsGlobalType *)0xC17040;

RwPluginRegistry &geometryTKList = *(RwPluginRegistry *)0x8D628C;

RtDictSchema &RpUVAnimDictSchema = *(RtDictSchema *)0x8DED50;

IDirect3DDevice9 *GetD3DDevice() {
    return *reinterpret_cast<IDirect3DDevice9 **>(0xC97C28);
}

_D3DMATRIX *GetD3DViewTransform() {
    return reinterpret_cast<_D3DMATRIX *>(0xC9BC80);
}

_D3DMATRIX *GetD3DProjTransform() {
    return reinterpret_cast<_D3DMATRIX *>(0x8E2458);
}

/* rwplcore.h */

RwMemoryFunctions* RwOsGetMemoryInterface(void) {
    return ((RwMemoryFunctions*(__cdecl *)(void))0x802230)();
}

RwFreeList* _rwFreeListCreate(RwInt32 entrySize, RwInt32 entriesPerBlock, RwInt32 alignment, RwUInt32 hint, const RwChar* fileCreate, RwUInt32 lineCreate) {
    return ((RwFreeList*(__cdecl *)(RwInt32, RwInt32, RwInt32, RwUInt32, const RwChar*, RwUInt32))0x801980)(entrySize, entriesPerBlock, alignment, hint, fileCreate, lineCreate);
}

RwFreeList* RwFreeListCreateAndPreallocateSpace(RwInt32 entrySize, RwInt32 entriesPerBlock, RwInt32 alignment, RwInt32 numBlocksToPreallocate, RwFreeList* inPlaceSpaceForFreeListStruct, RwUInt32 hint) {
    return ((RwFreeList*(__cdecl *)(RwInt32, RwInt32, RwInt32, RwInt32, RwFreeList*, RwUInt32))0x801B70)(entrySize, entriesPerBlock, alignment, numBlocksToPreallocate, inPlaceSpaceForFreeListStruct, hint);
}

RwBool RwFreeListDestroy(RwFreeList* freelist) {
    return ((RwBool(__cdecl *)(RwFreeList*))0x801B80)(freelist);
}

void RwFreeListSetFlags(RwFreeList* freeList, RwUInt32 flags) {
    ((void(__cdecl *)(RwFreeList*, RwUInt32))0x801C10)(freeList, flags);
}

RwUInt32 RwFreeListGetFlags(RwFreeList* freeList) {
    return ((RwUInt32(__cdecl *)(RwFreeList*))0x801C20)(freeList);
}

RwInt32 RwFreeListPurge(RwFreeList* freelist) {
    return ((RwInt32(__cdecl *)(RwFreeList*))0x801E00)(freelist);
}

RwFreeList* RwFreeListForAllUsed(RwFreeList* freelist, RwFreeListCallBack fpCallBack, void* pData) {
    return ((RwFreeList*(__cdecl *)(RwFreeList*, RwFreeListCallBack, void*))0x801E90)(freelist, fpCallBack, pData);
}

RwInt32 RwFreeListPurgeAllFreeLists(void) {
    return ((RwInt32(__cdecl *)(void))0x801F90)();
}

void RwStreamSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc) {
    ((void(__cdecl *)(RwInt32, RwInt32))0x7EC760)(blockSize, numBlocksToPrealloc);
}

RwStream* _rwStreamInitialize(RwStream* stream, RwBool rwOwned, RwStreamType type, RwStreamAccessType accessType, const void* pData) {
    return ((RwStream*(__cdecl *)(RwStream*, RwBool, RwStreamType, RwStreamAccessType, const void*))0x7EC810)(stream, rwOwned, type, accessType, pData);
}

RwStream* RwStreamOpen(RwStreamType type, RwStreamAccessType accessType, const void* pData) {
    return ((RwStream*(__cdecl *)(RwStreamType, RwStreamAccessType, const void*))0x7ECEF0)(type, accessType, pData);
}

RwBool RwStreamClose(RwStream* stream, void* pData) {
    return ((RwBool(__cdecl *)(RwStream*, void*))0x7ECE20)(stream, pData);
}

RwUInt32 RwStreamRead(RwStream* stream, void* buffer, RwUInt32 length) {
    return ((RwUInt32(__cdecl *)(RwStream*, void*, RwUInt32))0x7EC9D0)(stream, buffer, length);
}

RwStream* RwStreamWrite(RwStream* stream, const void* buffer, RwUInt32 length) {
    return ((RwStream*(__cdecl *)(RwStream*, const void*, RwUInt32))0x7ECB30)(stream, buffer, length);
}

RwStream* RwStreamSkip(RwStream* stream, RwUInt32 offset) {
    return ((RwStream*(__cdecl *)(RwStream*, RwUInt32))0x7ECD00)(stream, offset);
}

RwBool _rwStringOpen(void) {
    return ((RwBool(__cdecl *)(void))0x80A240)();
}

void _rwStringClose(void) {
    ((void(__cdecl *)(void))0x80A440)();
}

RwBool _rwStringDestroy(RwChar* string) {
    return ((RwBool(__cdecl *)(RwChar*))0x80A450)(string);
}

RwUInt32 _rwStringStreamGetSize(const RwChar* string) {
    return ((RwUInt32(__cdecl *)(const RwChar*))0x80A470)(string);
}

const RwChar* _rwStringStreamWrite(const RwChar* string, RwStream* stream) {
    return ((const RwChar*(__cdecl *)(const RwChar*, RwStream*))0x80A4A0)(string, stream);
}

RwChar* _rwStringStreamFindAndRead(RwChar* string, RwStream* stream) {
    return ((RwChar*(__cdecl *)(RwChar*, RwStream*))0x80A510)(string, stream);
}

void RwPluginRegistrySetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc) {
    ((void(__cdecl *)(RwInt32, RwInt32))0x8087B0)(blockSize, numBlocksToPrealloc);
}

RwBool _rwPluginRegistrySetStaticPluginsSize(RwPluginRegistry* reg, RwInt32 size) {
    return ((RwBool(__cdecl *)(RwPluginRegistry*, RwInt32))0x808430)(reg, size);
}

RwInt32 _rwPluginRegistryAddPlugin(RwPluginRegistry* reg, RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor constructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB) {
    return ((RwInt32(__cdecl *)(RwPluginRegistry*, RwInt32, RwUInt32, RwPluginObjectConstructor, RwPluginObjectDestructor, RwPluginObjectCopy))0x8084A0)(reg, size, pluginID, constructCB, destructCB, copyCB);
}

RwInt32 _rwPluginRegistryGetPluginOffset(const RwPluginRegistry* reg, RwUInt32 pluginID) {
    return ((RwInt32(__cdecl *)(const RwPluginRegistry*, RwUInt32))0x808470)(reg, pluginID);
}

const RwPluginRegistry* _rwPluginRegistryInitObject(const RwPluginRegistry* reg, void* object) {
    return ((const RwPluginRegistry*(__cdecl *)(const RwPluginRegistry*, void*))0x8086E0)(reg, object);
}

const RwPluginRegistry* _rwPluginRegistryDeInitObject(const RwPluginRegistry* reg, void* object) {
    return ((const RwPluginRegistry*(__cdecl *)(const RwPluginRegistry*, void*))0x808740)(reg, object);
}

const RwPluginRegistry* _rwPluginRegistryCopyObject(const RwPluginRegistry* reg, void* dstObject, const void* srcObject) {
    return ((const RwPluginRegistry*(__cdecl *)(const RwPluginRegistry*, void*, const void*))0x808770)(reg, dstObject, srcObject);
}

RwInt32 _rwPluginRegistryAddPluginStream(RwPluginRegistry* reg, RwUInt32 pluginID, RwPluginDataChunkReadCallBack readCB, RwPluginDataChunkWriteCallBack writeCB, RwPluginDataChunkGetSizeCallBack getSizeCB) {
    return ((RwInt32(__cdecl *)(RwPluginRegistry*, RwUInt32, RwPluginDataChunkReadCallBack, RwPluginDataChunkWriteCallBack, RwPluginDataChunkGetSizeCallBack))0x8088E0)(reg, pluginID, readCB, writeCB, getSizeCB);
}

RwInt32 _rwPluginRegistryAddPlgnStrmlwysCB(RwPluginRegistry* reg, RwUInt32 pluginID, RwPluginDataChunkAlwaysCallBack alwaysCB) {
    return ((RwInt32(__cdecl *)(RwPluginRegistry*, RwUInt32, RwPluginDataChunkAlwaysCallBack))0x808920)(reg, pluginID, alwaysCB);
}

RwInt32 _rwPluginRegistryAddPlgnStrmRightsCB(RwPluginRegistry* reg, RwUInt32 pluginID, RwPluginDataChunkRightsCallBack rightsCB) {
    return ((RwInt32(__cdecl *)(RwPluginRegistry*, RwUInt32, RwPluginDataChunkRightsCallBack))0x808950)(reg, pluginID, rightsCB);
}

const RwPluginRegistry* _rwPluginRegistryReadDataChunks(const RwPluginRegistry* reg, RwStream* stream, void* object) {
    return ((const RwPluginRegistry*(__cdecl *)(const RwPluginRegistry*, RwStream*, void*))0x808980)(reg, stream, object);
}

const RwPluginRegistry* _rwPluginRegistryWriteDataChunks(const RwPluginRegistry* reg, RwStream* stream, const void* object) {
    return ((const RwPluginRegistry*(__cdecl *)(const RwPluginRegistry*, RwStream*, const void*))0x808B40)(reg, stream, object);
}

const RwPluginRegistry* _rwPluginRegistrySkipDataChunks(const RwPluginRegistry* reg, RwStream* stream) {
    return ((const RwPluginRegistry*(__cdecl *)(const RwPluginRegistry*, RwStream*))0x808C10)(reg, stream);
}

RwInt32 _rwPluginRegistryGetSize(const RwPluginRegistry* reg, const void* object) {
    return ((RwInt32(__cdecl *)(const RwPluginRegistry*, const void*))0x808B00)(reg, object);
}

const RwPluginRegistry* _rwPluginRegistryInvokeRights(const RwPluginRegistry* reg, RwUInt32 id, void* obj, RwUInt32 extraData) {
    return ((const RwPluginRegistry*(__cdecl *)(const RwPluginRegistry*, RwUInt32, void*, RwUInt32))0x808AB0)(reg, id, obj, extraData);
}

RwBool RwEngineGetMatrixTolerances(RwMatrixTolerance * const tolerance) {
    return ((RwBool(__cdecl *)(RwMatrixTolerance * const))0x7F1780)(tolerance);
}

RwBool RwEngineSetMatrixTolerances(const RwMatrixTolerance * const tolerance) {
    return ((RwBool(__cdecl *)(const RwMatrixTolerance*))0x7F17B0)(tolerance);
}

void RwMatrixSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc) {
    ((void(__cdecl *)(RwInt32, RwInt32))0x7F16A0)(blockSize, numBlocksToPrealloc);
}

RwBool RwMatrixDestroy(RwMatrix* mpMat) {
    return ((RwBool(__cdecl *)(RwMatrix*))0x7F2A20)(mpMat);
}

RwMatrix* RwMatrixCreate(void) {
    return ((RwMatrix*(__cdecl *)(void))0x7F2A50)();
}

RwMatrix* RwMatrixMultiply(RwMatrix* matrixOut, const RwMatrix* MatrixIn1, const RwMatrix* matrixIn2) {
    return ((RwMatrix*(__cdecl *)(RwMatrix*, const RwMatrix*, const RwMatrix*))0x7F18B0)(matrixOut, MatrixIn1, matrixIn2);
}

RwMatrix* RwMatrixTransform(RwMatrix* matrix, const RwMatrix* transform, RwOpCombineType combineOp) {
    return ((RwMatrix*(__cdecl *)(RwMatrix*, const RwMatrix*, RwOpCombineType))0x7F25A0)(matrix, transform, combineOp);
}

RwMatrix* RwMatrixOrthoNormalize(RwMatrix* matrixOut, const RwMatrix* matrixIn) {
    return ((RwMatrix*(__cdecl *)(RwMatrix*, const RwMatrix*))0x7F1920)(matrixOut, matrixIn);
}

RwMatrix* RwMatrixInvert(RwMatrix* matrixOut, const RwMatrix* matrixIn) {
    return ((RwMatrix*(__cdecl *)(RwMatrix*, const RwMatrix*))0x7F2070)(matrixOut, matrixIn);
}

RwMatrix* RwMatrixScale(RwMatrix* matrix, const RwV3d* scale, RwOpCombineType combineOp) {
    return ((RwMatrix*(__cdecl *)(RwMatrix*, const RwV3d*, RwOpCombineType))0x7F22C0)(matrix, scale, combineOp);
}

RwMatrix* RwMatrixTranslate(RwMatrix* matrix, const RwV3d* translation, RwOpCombineType combineOp) {
    return ((RwMatrix*(__cdecl *)(RwMatrix*, const RwV3d*, RwOpCombineType))0x7F2450)(matrix, translation, combineOp);
}

RwMatrix* RwMatrixRotate(RwMatrix* matrix, const RwV3d* axis, RwReal angle, RwOpCombineType combineOp) {
    return ((RwMatrix*(__cdecl *)(RwMatrix*, const RwV3d*, RwReal, RwOpCombineType))0x7F1FD0)(matrix, axis, angle, combineOp);
}

RwMatrix* RwMatrixRotateOneMinusCosineSine(RwMatrix* matrix, const RwV3d* unitAxis, RwReal oneMinusCosine, RwReal sine, RwOpCombineType combineOp) {
    return ((RwMatrix*(__cdecl *)(RwMatrix*, const RwV3d*, RwReal, RwReal, RwOpCombineType))0x7F1D00)(matrix, unitAxis, oneMinusCosine, sine, combineOp);
}

const RwMatrix* RwMatrixQueryRotate(const RwMatrix* matrix, RwV3d* unitAxis, RwReal* angle, RwV3d* center) {
    return ((const RwMatrix*(__cdecl *)(const RwMatrix*, RwV3d*, RwReal*, RwV3d*))0x7F2720)(matrix, unitAxis, angle, center);
}

RwMatrix* RwMatrixUpdate(RwMatrix* matrix) {
    return ((RwMatrix*(__cdecl *)(RwMatrix*))0x7F18A0)(matrix);
}

RwMatrix* RwMatrixOptimize(RwMatrix* matrix, const RwMatrixTolerance* tolerance) {
    return ((RwMatrix*(__cdecl *)(RwMatrix*, const RwMatrixTolerance*))0x7F17E0)(matrix, tolerance);
}

RwReal _rwMatrixDeterminant(const RwMatrix* matrix) {
    return ((RwReal(__cdecl *)(const RwMatrix*))0x7F1450)(matrix);
}

RwReal _rwMatrixNormalError(const RwMatrix* matrix) {
    return ((RwReal(__cdecl *)(const RwMatrix*))0x7F1500)(matrix);
}

RwReal _rwMatrixOrthogonalError(const RwMatrix* matrix) {
    return ((RwReal(__cdecl *)(const RwMatrix*))0x7F14A0)(matrix);
}

RwReal _rwMatrixIdentityError(const RwMatrix* matrix) {
    return ((RwReal(__cdecl *)(const RwMatrix*))0x7F1590)(matrix);
}

RwReal RwV3dNormalize(RwV3d* out, const RwV3d* in) {
    return ((RwReal(__cdecl *)(RwV3d*, const RwV3d*))0x7ED9B0)(out, in);
}

RwReal RwV3dLength(const RwV3d* in) {
    return ((RwReal(__cdecl *)(const RwV3d*))0x7EDAC0)(in);
}

RwReal RwV2dLength(const RwV2d* in) {
    return ((RwReal(__cdecl *)(const RwV2d*))0x7EDBF0)(in);
}

RwReal RwV2dNormalize(RwV2d* out, const RwV2d* in) {
    return ((RwReal(__cdecl *)(RwV2d*, const RwV2d*))0x7EDC60)(out, in);
}

RwV3d* RwV3dTransformPoint(RwV3d* pointOut, const RwV3d* pointIn, const RwMatrix* matrix) {
    return ((RwV3d*(__cdecl *)(RwV3d*, const RwV3d*, const RwMatrix*))0x7EDD60)(pointOut, pointIn, matrix);
}

RwV3d* RwV3dTransformPoints(RwV3d* pointsOut, const RwV3d* pointsIn, RwInt32 numPoints, const RwMatrix* matrix) {
    return ((RwV3d*(__cdecl *)(RwV3d*, const RwV3d*, RwInt32, const RwMatrix*))0x7EDD90)(pointsOut, pointsIn, numPoints, matrix);
}

RwV3d* RwV3dTransformVector(RwV3d* vectorOut, const RwV3d* vectorIn, const RwMatrix* matrix) {
    return ((RwV3d*(__cdecl *)(RwV3d*, const RwV3d*, const RwMatrix*))0x7EDDC0)(vectorOut, vectorIn, matrix);
}

RwV3d* RwV3dTransformVectors(RwV3d* vectorsOut, const RwV3d* vectorsIn, RwInt32 numPoints, const RwMatrix* matrix) {
    return ((RwV3d*(__cdecl *)(RwV3d*, const RwV3d*, RwInt32, const RwMatrix*))0x7EDDF0)(vectorsOut, vectorsIn, numPoints, matrix);
}

RwReal _rwSqrt(const RwReal num) {
    return ((RwReal(__cdecl *)(const RwReal))0x7EDB30)(num);
}

RwReal _rwInvSqrt(const RwReal num) {
    return ((RwReal(__cdecl *)(const RwReal))0x7EDB90)(num);
}

RwReal _rwV3dNormalize(RwV3d* out, const RwV3d* in) {
    return ((RwReal(__cdecl *)(RwV3d*, const RwV3d*))0x7ED910)(out, in);
}

RwSList* _rwSListCreate(RwInt32 size, RwUInt32 hint) {
    return ((RwSList*(__cdecl *)(RwInt32, RwUInt32))0x809160)(size, hint);
}

RwBool _rwSListDestroy(RwSList* sList) {
    return ((RwBool(__cdecl *)(RwSList*))0x809440)(sList);
}

void _rwSListDestroyEndEntries(RwSList* sList, RwInt32 amount) {
    ((void(__cdecl *)(RwSList*, RwInt32))0x809400)(sList, amount);
}

void* _rwSListGetEntry(RwSList* sList, RwInt32 entry) {
    return ((void*(__cdecl *)(RwSList*, RwInt32))0x809510)(sList, entry);
}

void* _rwSListGetNewEntry(RwSList* sList, RwUInt32 hint) {
    return ((void*(__cdecl *)(RwSList*, RwUInt32))0x809240)(sList, hint);
}

RwInt32 _rwSListGetNumEntries(const RwSList* sList) {
    return ((RwInt32(__cdecl *)(const RwSList*))0x8094B0)(sList);
}

void* _rwSListGetBegin(RwSList* sList) {
    return ((void*(__cdecl *)(RwSList*))0x809530)(sList);
}

void* _rwSListGetEnd(RwSList* sList) {
    return ((void*(__cdecl *)(RwSList*))0x809540)(sList);
}

RwBool RwIm2DRenderPrimitive(RwPrimitiveType primType, RwIm2DVertex* vertices, RwInt32 numVertices) {
    return ((int(__cdecl *)(RwPrimitiveType, RwIm2DVertex*, RwInt32))0x734E90)(primType, vertices, numVertices);
}

RwBool RwIm2DRenderIndexedPrimitive(RwPrimitiveType primType, RwIm2DVertex* vertices, RwInt32 numVertices, RwImVertexIndex* indices, RwInt32 numIndices) {
    return ((int(__cdecl *)(RwPrimitiveType, RwIm2DVertex*, RwInt32, RwImVertexIndex*, RwInt32))0x734EA0)(primType, vertices, numVertices, indices, numIndices);
}

RwBool RwIm2DRenderTriangle(RwIm2DVertex* vertices, RwInt32 numVertices, RwInt32 vert1, RwInt32 vert2, RwInt32 vert3) {
    return ((int(__cdecl *)(RwIm2DVertex*, RwInt32, RwInt32, RwInt32, RwInt32))0x734EB0)(vertices, numVertices, vert1, vert2, vert3);
}

RwBool RwIm2DRenderLine(RwIm2DVertex* vertices, RwInt32 numVertices, RwInt32 vert1, RwInt32 vert2) {
    return ((int(__cdecl *)(RwIm2DVertex*, RwInt32, RwInt32, RwInt32))0x734EC0)(vertices, numVertices, vert1, vert2);
}

RwUInt32 RwEngineGetVersion(void) {
    return ((RwUInt32(__cdecl *)(void))0x7F2BA0)();
}

RwBool RwEngineInit(const RwMemoryFunctions* memFuncs, RwUInt32 initFlags, RwUInt32 resArenaSize) {
    return ((RwBool(__cdecl *)(const RwMemoryFunctions*, RwUInt32, RwUInt32))0x7F3170)(memFuncs, initFlags, resArenaSize);
}

RwInt32 RwEngineRegisterPlugin(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor initCB, RwPluginObjectDestructor termCB) {
    return ((RwInt32(__cdecl *)(RwInt32, RwUInt32, RwPluginObjectConstructor, RwPluginObjectDestructor))0x7F2BB0)(size, pluginID, initCB, termCB);
}

RwInt32 RwEngineGetPluginOffset(RwUInt32 pluginID) {
    return ((RwInt32(__cdecl *)(RwUInt32))0x7F2BE0)(pluginID);
}

RwBool RwEngineOpen(RwEngineOpenParams* initParams) {
    return ((RwBool(__cdecl *)(RwEngineOpenParams*))0x7F2F70)(initParams);
}

RwBool RwEngineStart(void) {
    return ((RwBool(__cdecl *)(void))0x7F2E70)();
}

RwBool RwEngineStop(void) {
    return ((RwBool(__cdecl *)(void))0x7F2E20)();
}

RwBool RwEngineClose(void) {
    return ((RwBool(__cdecl *)(void))0x7F2F00)();
}

RwBool RwEngineTerm(void) {
    return ((RwBool(__cdecl *)(void))0x7F3130)();
}

RwInt32 RwEngineGetNumSubSystems(void) {
    return ((RwInt32(__cdecl *)(void))0x7F2C00)();
}

RwSubSystemInfo* RwEngineGetSubSystemInfo(RwSubSystemInfo* subSystemInfo, RwInt32 subSystemIndex) {
    return ((RwSubSystemInfo*(__cdecl *)(RwSubSystemInfo*, RwInt32))0x7F2C30)(subSystemInfo, subSystemIndex);
}

RwInt32 RwEngineGetCurrentSubSystem(void) {
    return ((RwInt32(__cdecl *)(void))0x7F2C60)();
}

RwBool RwEngineSetSubSystem(RwInt32 subSystemIndex) {
    return ((RwBool(__cdecl *)(RwInt32))0x7F2C90)(subSystemIndex);
}

RwInt32 RwEngineGetNumVideoModes(void) {
    return ((RwInt32(__cdecl *)(void))0x7F2CC0)();
}

RwVideoMode* RwEngineGetVideoModeInfo(RwVideoMode* modeinfo, RwInt32 modeIndex) {
    return ((RwVideoMode*(__cdecl *)(RwVideoMode*, RwInt32))0x7F2CF0)(modeinfo, modeIndex);
}

RwInt32 RwEngineGetCurrentVideoMode(void) {
    return ((RwInt32(__cdecl *)(void))0x7F2D20)();
}

RwBool RwEngineSetVideoMode(RwInt32 modeIndex) {
    return ((RwBool(__cdecl *)(RwInt32))0x7F2D50)(modeIndex);
}

RwInt32 RwEngineGetTextureMemorySize(void) {
    return ((RwInt32(__cdecl *)(void))0x7F2D80)();
}

RwInt32 RwEngineGetMaxTextureSize(void) {
    return ((RwInt32(__cdecl *)(void))0x7F2DB0)();
}

RwBool RwEngineSetFocus(RwBool enable) {
    return ((RwBool(__cdecl *)(RwBool))0x7F2DE0)(enable);
}

RwMetrics* RwEngineGetMetrics(void) {
    return ((RwMetrics*(__cdecl *)(void))0x7F2E10)();
}

RwFileFunctions* RwOsGetFileInterface(void) {
    return ((RwFileFunctions*(__cdecl *)(void))0x804130)();
}

RwError* RwErrorGet(RwError* code) {
    return ((RwError*(__cdecl *)(RwError*))0x808880)(code);
}

RwError* RwErrorSet(RwError* code) {
    return ((RwError*(__cdecl *)(RwError*))0x808820)(code);
}

RwInt32 _rwerror(RwInt32 code, ...) {
    return code;
}

RwBool RwResourcesSetArenaSize(RwUInt32 size) {
    return ((RwBool(__cdecl *)(RwUInt32))0x8080C0)(size);
}

RwInt32 RwResourcesGetArenaSize(void) {
    return ((RwInt32(__cdecl *)(void))0x8081B0)();
}

RwInt32 RwResourcesGetArenaUsage(void) {
    return ((RwInt32(__cdecl *)(void))0x8081C0)();
}

RwBool RwResourcesEmptyArena(void) {
    return ((RwBool(__cdecl *)(void))0x8081F0)();
}

RwResEntry* RwResourcesAllocateResEntry(void* owner, RwResEntry* ownerRef, RwInt32 size, RwResEntryDestroyNotify destroyNotify) {
    return ((RwResEntry*(__cdecl *)(void*, RwResEntry*, RwInt32, RwResEntryDestroyNotify))0x807ED0)(owner, ownerRef, size, destroyNotify);
}

RwBool RwResourcesFreeResEntry(RwResEntry* entry) {
    return ((RwBool(__cdecl *)(RwResEntry*))0x807DE0)(entry);
}

void _rwResourcesPurge(void) {
    ((void(__cdecl *)(void))0x807E50)();
}

RwBool RwStreamFindChunk(RwStream* stream, RwUInt32 type, RwUInt32* lengthOut, RwUInt32* versionOut) {
    return ((RwBool(__cdecl *)(RwStream*, RwUInt32, RwUInt32*, RwUInt32*))0x7ED2D0)(stream, type, lengthOut, versionOut);
}

RwStream* _rwStreamWriteVersionedChunkHeader(RwStream* stream, RwInt32 type, RwInt32 size, RwUInt32 version, RwUInt32 buildNum) {
    return ((RwStream*(__cdecl *)(RwStream*, RwInt32, RwInt32, RwUInt32, RwUInt32))0x7ED270)(stream, type, size, version, buildNum);
}

RwStream* RwStreamWriteReal(RwStream* stream, const RwReal* reals, RwUInt32 numBytes) {
    return ((RwStream*(__cdecl *)(RwStream*, const RwReal*, RwUInt32))0x7ED3D0)(stream, reals, numBytes);
}

RwStream* RwStreamWriteInt32(RwStream* stream, const RwInt32* ints, RwUInt32 numBytes) {
    return ((RwStream*(__cdecl *)(RwStream*, const RwInt32*, RwUInt32))0x7ED460)(stream, ints, numBytes);
}

RwStream* RwStreamWriteInt16(RwStream* stream, const RwInt16* ints, RwUInt32 numBytes) {
    return ((RwStream*(__cdecl *)(RwStream*, const RwInt16*, RwUInt32))0x7ED480)(stream, ints, numBytes);
}

RwStream* RwStreamReadReal(RwStream* stream, RwReal* reals, RwUInt32 numBytes) {
    return ((RwStream*(__cdecl *)(RwStream*, RwReal*, RwUInt32))0x7ED4F0)(stream, reals, numBytes);
}

RwStream* RwStreamReadInt32(RwStream* stream, RwInt32* ints, RwUInt32 numBytes) {
    return ((RwStream*(__cdecl *)(RwStream*, RwInt32*, RwUInt32))0x7ED540)(stream, ints, numBytes);
}

RwStream* RwStreamReadInt16(RwStream* stream, RwInt16* ints, RwUInt32 numBytes) {
    return ((RwStream*(__cdecl *)(RwStream*, RwInt16*, RwUInt32))0x7ED4A0)(stream, ints, numBytes);
}

RwStream* RwStreamReadChunkHeaderInfo(RwStream* stream, RwChunkHeaderInfo* chunkHeaderInfo) {
    return ((RwStream*(__cdecl *)(RwStream*, RwChunkHeaderInfo*))0x7ED590)(stream, chunkHeaderInfo);
}

/* rwcore.h */

RxHeap* RxHeapCreate(RwUInt32 size) {
    return ((RxHeap*(__cdecl *)(RwUInt32))0x809F90)(size);
}

void RxHeapDestroy(RxHeap* heap) {
    ((void(__cdecl *)(RxHeap*))0x809F30)(heap);
}

RwBool _rxHeapReset(RxHeap* heap) {
    return ((RwBool(__cdecl *)(RxHeap*))0x809EC0)(heap);
}

void* RxHeapAlloc(RxHeap* heap, RwUInt32 size) {
    return ((void*(__cdecl *)(RxHeap*, RwUInt32))0x809AA0)(heap, size);
}

void RxHeapFree(RxHeap* heap, void* block) {
    ((void(__cdecl *)(RxHeap*, void*))0x8098B0)(heap, block);
}

void* RxHeapRealloc(RxHeap* heap, void* block, RwUInt32 newSize, RwBool allowCopy) {
    return ((void*(__cdecl *)(RxHeap*, void*, RwUInt32, RwBool))0x809D10)(heap, block, newSize, allowCopy);
}

void RxPipelineSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc) {
    ((void(__cdecl *)(RwInt32, RwInt32))0x804FC0)(blockSize, numBlocksToPrealloc);
}

RwBool _rxPipelineOpen(void) {
    return ((RwBool(__cdecl *)(void))0x804FE0)();
}

RwBool _rxPipelineClose(void) {
    return ((RwBool(__cdecl *)(void))0x804F60)();
}

RxPipeline* RxPipelineCreate(void) {
    return ((RxPipeline*(__cdecl *)(void))0x8057B0)();
}

void _rxPipelineDestroy(RxPipeline* Pipeline) {
    ((void(__cdecl *)(RxPipeline*))0x805820)(Pipeline);
}

RxHeap* RxHeapGetGlobalHeap(void) {
    return ((RxHeap*(__cdecl *)(void))0x8052F0)();
}

RxPipeline* RxPipelineExecute(RxPipeline* pipeline, void* data, RwBool heapReset) {
    return ((RxPipeline*(__cdecl *)(RxPipeline*, void*, RwBool))0x805710)(pipeline, data, heapReset);
}

RxPacket* RxPacketCreate(RxPipelineNode* node) {
    return ((RxPacket*(__cdecl *)(RxPipelineNode*))0x805300)(node);
}

RxCluster* RxClusterSetStride(RxCluster* cluster, RwInt32 stride) {
    return ((RxCluster*(__cdecl *)(RxCluster*, RwInt32))0x805330)(cluster, stride);
}

RxCluster* RxClusterSetExternalData(RxCluster* cluster, void* data, RwInt32 stride, RwInt32 numElements) {
    return ((RxCluster*(__cdecl *)(RxCluster*, void*, RwInt32, RwInt32))0x805340)(cluster, data, stride, numElements);
}

RxCluster* RxClusterSetData(RxCluster* cluster, void* data, RwInt32 stride, RwInt32 numElements) {
    return ((RxCluster*(__cdecl *)(RxCluster*, void*, RwInt32, RwInt32))0x8053A0)(cluster, data, stride, numElements);
}

void _rxPacketDestroy(RxPacket* Packet) {
    ((void(__cdecl *)(RxPacket*))0x80F070)(Packet);
}

RxCluster* RxClusterInitializeData(RxCluster* cluster, RwUInt32 numElements, RwUInt16 stride) {
    return ((RxCluster*(__cdecl *)(RxCluster*, RwUInt32, RwUInt16))0x805400)(cluster, numElements, stride);
}

RxCluster* RxClusterResizeData(RxCluster* CurrentCluster, RwUInt32 NumElements) {
    return ((RxCluster*(__cdecl *)(RxCluster*, RwUInt32))0x805470)(CurrentCluster, NumElements);
}

RxCluster* RxClusterDestroyData(RxCluster* CurrentCluster) {
    return ((RxCluster*(__cdecl *)(RxCluster*))0x8054C0)(CurrentCluster);
}

RxCluster* RxClusterLockWrite(RxPacket* packet, RwUInt32 clusterIndex, RxPipelineNode* node) {
    return ((RxCluster*(__cdecl *)(RxPacket*, RwUInt32, RxPipelineNode*))0x8054F0)(packet, clusterIndex, node);
}

void RxClusterUnlock(RxCluster* cluster) {
    ((void(__cdecl *)(RxCluster*))0x8055C0)(cluster);
}

RwUInt32 RxPipelineNodeSendConfigMsg(RxPipelineNode* dest, RwUInt32 msg, RwUInt32 intparam, void* ptrparam) {
    return ((RwUInt32(__cdecl *)(RxPipelineNode*, RwUInt32, RwUInt32, void*))0x8055D0)(dest, msg, intparam, ptrparam);
}

RxPipelineNode* RxPipelineNodeForAllConnectedOutputs(RxPipelineNode* node, RxPipeline* pipeline, RxPipelineNodeOutputCallBack callbackfn, void* callbackdata) {
    return ((RxPipelineNode*(__cdecl *)(RxPipelineNode*, RxPipeline*, RxPipelineNodeOutputCallBack, void*))0x8055F0)(node, pipeline, callbackfn, callbackdata);
}

RxPipelineCluster* RxPipelineNodeGetPipelineCluster(RxPipelineNode* node, RwUInt32 clustersOfInterestIndex) {
    return ((RxPipelineCluster*(__cdecl *)(RxPipelineNode*, RwUInt32))0x805680)(node, clustersOfInterestIndex);
}

RwUInt32 RxPipelineClusterGetCreationAttributes(RxPipelineCluster* cluster) {
    return ((RwUInt32(__cdecl *)(RxPipelineCluster*))0x8056B0)(cluster);
}

RxPipelineCluster* RxPipelineClusterSetCreationAttributes(RxPipelineCluster* cluster, RwUInt32 creationAttributes) {
    return ((RxPipelineCluster*(__cdecl *)(RxPipelineCluster*, RwUInt32))0x8056C0)(cluster, creationAttributes);
}

RwUInt32 RxClusterGetAttributes(RxCluster* cluster) {
    return ((RwUInt32(__cdecl *)(RxCluster*))0x8056E0)(cluster);
}

RxCluster* RxClusterSetAttributes(RxCluster* cluster, RwUInt32 attributes) {
    return ((RxCluster*(__cdecl *)(RxCluster*, RwUInt32))0x8056F0)(cluster, attributes);
}

RxNodeOutput RxPipelineNodeFindOutputByName(RxPipelineNode* node, const RwChar* outputname) {
    return ((RxNodeOutput(__cdecl *)(RxPipelineNode*, const RwChar*))0x805D10)(node, outputname);
}

RxNodeOutput RxPipelineNodeFindOutputByIndex(RxPipelineNode* node, RwUInt32 outputindex) {
    return ((RxNodeOutput(__cdecl *)(RxPipelineNode*, RwUInt32))0x805D70)(node, outputindex);
}

RxNodeInput RxPipelineNodeFindInput(RxPipelineNode* node) {
    return ((RxNodeInput(__cdecl *)(RxPipelineNode*))0x805DA0)(node);
}

RxNodeDefinition* RxPipelineNodeCloneDefinition(RxPipelineNode* node, RxClusterDefinition* cluster2add) {
    return ((RxNodeDefinition*(__cdecl *)(RxPipelineNode*, RxClusterDefinition*))0x8059C0)(node, cluster2add);
}

RxPipeline* RxPipelineNodeRequestCluster(RxPipeline* pipeline, RxPipelineNode* node, RxClusterDefinition* clusterDef) {
    return ((RxPipeline*(__cdecl *)(RxPipeline*, RxPipelineNode*, RxClusterDefinition*))0x805DB0)(pipeline, node, clusterDef);
}

RxPipeline* RxPipelineNodeReplaceCluster(RxPipeline* pipeline, RxPipelineNode* node, RxClusterDefinition* oldClusterDef, RxClusterDefinition* newClusterDef) {
    return ((RxPipeline*(__cdecl *)(RxPipeline*, RxPipelineNode*, RxClusterDefinition*, RxClusterDefinition*))0x805E20)(pipeline, node, oldClusterDef, newClusterDef);
}

void* RxPipelineNodeGetInitData(RxPipelineNode* node) {
    return ((void*(__cdecl *)(RxPipelineNode*))0x805F30)(node);
}

void* RxPipelineNodeCreateInitData(RxPipelineNode* node, RwUInt32 size) {
    return ((void*(__cdecl *)(RxPipelineNode*, RwUInt32))0x805EA0)(node, size);
}

RxPipeline* RxPipelineClone(RxPipeline* pipeline) {
    return ((RxPipeline*(__cdecl *)(RxPipeline*))0x806AC0)(pipeline);
}

RxPipelineNode* RxPipelineFindNodeByName(RxPipeline* pipeline, const RwChar* name, RxPipelineNode* start, RwInt32* nodeIndex) {
    return ((RxPipelineNode*(__cdecl *)(RxPipeline*, const RwChar*, RxPipelineNode*, RwInt32*))0x806B30)(pipeline, name, start, nodeIndex);
}

RxPipelineNode* RxPipelineFindNodeByIndex(RxPipeline* pipeline, RwUInt32 nodeindex) {
    return ((RxPipelineNode*(__cdecl *)(RxPipeline*, RwUInt32))0x806BC0)(pipeline, nodeindex);
}

RxLockedPipe* RxPipelineLock(RxPipeline* pipeline) {
    return ((RxLockedPipe*(__cdecl *)(RxPipeline*))0x806990)(pipeline);
}

RxPipeline* RxLockedPipeUnlock(RxLockedPipe* pipeline) {
    return ((RxPipeline*(__cdecl *)(RxLockedPipe*))0x805F40)(pipeline);
}

RxPipeline* RxLockedPipeReplaceNode(RxLockedPipe* pipeline, RxPipelineNode* node, RxNodeDefinition* nodeDef) {
    return ((RxPipeline*(__cdecl *)(RxLockedPipe*, RxPipelineNode*, RxNodeDefinition*))0x806F20)(pipeline, node, nodeDef);
}

RxPipeline* RxLockedPipeDeleteNode(RxLockedPipe* pipeline, RxPipelineNode* node) {
    return ((RxPipeline*(__cdecl *)(RxLockedPipe*, RxPipelineNode*))0x807040)(pipeline, node);
}

RxPipeline* RxLockedPipeSetEntryPoint(RxLockedPipe* pipeline, RxNodeInput in) {
    return ((RxPipeline*(__cdecl *)(RxLockedPipe*, RxNodeInput))0x807070)(pipeline, in);
}

RxPipelineNode* RxLockedPipeGetEntryPoint(RxLockedPipe* pipeline) {
    return ((RxPipelineNode*(__cdecl *)(RxLockedPipe*))0x8070D0)(pipeline);
}

RxPipeline* RxLockedPipeAddPath(RxLockedPipe* pipeline, RxNodeOutput out, RxNodeInput in) {
    return ((RxPipeline*(__cdecl *)(RxLockedPipe*, RxNodeOutput, RxNodeInput))0x807100)(pipeline, out, in);
}

RxPipeline* RxLockedPipeDeletePath(RxLockedPipe* pipeline, RxNodeOutput out, RxNodeInput in) {
    return ((RxPipeline*(__cdecl *)(RxLockedPipe*, RxNodeOutput, RxNodeInput))0x807170)(pipeline, out, in);
}

RxPipeline* RxPipelineInsertDebugNode(RxPipeline* pipeline, RxPipelineNode* before, RxPipelineNode* after, RxNodeDefinition* debugNode) {
    return ((RxPipeline*(__cdecl *)(RxPipeline*, RxPipelineNode*, RxPipelineNode*, RxNodeDefinition*))0x8071B0)(pipeline, before, after, debugNode);
}

void RwD3D9VertexBufferManagerChangeDefaultSize(RwUInt32 defaultSize) {
    ((void(__cdecl *)(RwUInt32))0x7F57F0)(defaultSize);
}

RwBool RwD3D9CreateVertexBuffer(RwUInt32 stride, RwUInt32 size, void* vertexBuffer, RwUInt32* offset) {
    return ((RwBool(__cdecl *)(RwUInt32, RwUInt32, void*, RwUInt32*))0x7F5500)(stride, size, vertexBuffer, offset);
}

void RwD3D9DestroyVertexBuffer(RwUInt32 stride, RwUInt32 size, void* vertexBuffer, RwUInt32 offset) {
    ((void(__cdecl *)(RwUInt32, RwUInt32, void*, RwUInt32))0x7F56A0)(stride, size, vertexBuffer, offset);
}

RwBool RwD3D9DynamicVertexBufferCreate(RwUInt32 size, void* vertexBuffer) {
    return ((RwBool(__cdecl *)(RwUInt32, void*))0x7F5A00)(size, vertexBuffer);
}

void RwD3D9DynamicVertexBufferDestroy(void) {
    ((void(__cdecl *)(void))0x7F5AE0)();
}

RwBool RwD3D9DynamicVertexBufferLock(RwUInt32 vertexSize, RwUInt32 numVertex, void* vertexBufferOut, void* vertexDataOut, RwUInt32* baseIndexOut) {
    return ((RwBool(__cdecl *)(RwUInt32, RwUInt32, void*, void*, RwUInt32*))0x7F5B10)(vertexSize, numVertex, vertexBufferOut, vertexDataOut, baseIndexOut);
}

RwBool RwD3D9DynamicVertexBufferUnlock(void) {
    return ((RwBool(__cdecl *)(void))0x7F5C90)();
}

void RwRasterSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc) {
    ((void(__cdecl *)(RwInt32, RwInt32))0x7FB350)(blockSize, numBlocksToPrealloc);
}

RwRaster* RwRasterCreate(RwInt32 width, RwInt32 height, RwInt32 depth, RwInt32 flags) {
    return ((RwRaster*(__cdecl *)(RwInt32, RwInt32, RwInt32, RwInt32))0x7FB230)(width, height, depth, flags);
}

RwBool RwRasterDestroy(RwRaster* raster) {
    return ((RwBool(__cdecl *)(RwRaster*))0x7FB020)(raster);
}

RwRaster* RwRasterGetOffset(RwRaster* raster, RwInt16* xOffset, RwInt16* yOffset) {
    return ((RwRaster*(__cdecl *)(RwRaster*, RwInt16*, RwInt16*))0x7FAEA0)(raster, xOffset, yOffset);
}

RwInt32 RwRasterGetNumLevels(RwRaster* raster) {
    return ((RwInt32(__cdecl *)(RwRaster*))0x7FB160)(raster);
}

RwRaster* RwRasterSubRaster(RwRaster* subRaster, RwRaster* raster, RwRect* rect) {
    return ((RwRaster*(__cdecl *)(RwRaster*, RwRaster*, RwRect*))0x7FB1D0)(subRaster, raster, rect);
}

RwRaster* RwRasterRenderFast(RwRaster* raster, RwInt32 x, RwInt32 y) {
    return ((RwRaster*(__cdecl *)(RwRaster*, RwInt32, RwInt32))0x7FAF50)(raster, x, y);
}

RwRaster* RwRasterRender(RwRaster* raster, RwInt32 x, RwInt32 y) {
    return ((RwRaster*(__cdecl *)(RwRaster*, RwInt32, RwInt32))0x7FAFB0)(raster, x, y);
}

RwRaster* RwRasterRenderScaled(RwRaster* raster, RwRect* rect) {
    return ((RwRaster*(__cdecl *)(RwRaster*, RwRect*))0x7FAE80)(raster, rect);
}

RwRaster* RwRasterPushContext(RwRaster* raster) {
    return ((RwRaster*(__cdecl *)(RwRaster*))0x7FB060)(raster);
}

RwRaster* RwRasterPopContext(void) {
    return ((RwRaster*(__cdecl *)(void))0x7FB110)();
}

RwRaster* RwRasterGetCurrentContext(void) {
    return ((RwRaster*(__cdecl *)(void))0x7FAE60)();
}

RwBool RwRasterClear(RwInt32 pixelValue) {
    return ((RwBool(__cdecl *)(RwInt32))0x7FAEE0)(pixelValue);
}

RwBool RwRasterClearRect(RwRect* rpRect, RwInt32 pixelValue) {
    return ((RwBool(__cdecl *)(RwRect*, RwInt32))0x7FAF90)(rpRect, pixelValue);
}

RwRaster* RwRasterShowRaster(RwRaster* raster, void* dev, RwUInt32 flags) {
    return ((RwRaster*(__cdecl *)(RwRaster*, void*, RwUInt32))0x7FB1A0)(raster, dev, flags);
}

RwUInt8* RwRasterLock(RwRaster* raster, RwUInt8 level, RwInt32 lockMode) {
    return ((RwUInt8*(__cdecl *)(RwRaster*, RwUInt8, RwInt32))0x7FB2D0)(raster, level, lockMode);
}

RwRaster* RwRasterUnlock(RwRaster* raster) {
    return ((RwRaster*(__cdecl *)(RwRaster*))0x7FAEC0)(raster);
}

RwUInt8* RwRasterLockPalette(RwRaster* raster, RwInt32 lockMode) {
    return ((RwUInt8*(__cdecl *)(RwRaster*, RwInt32))0x7FB0E0)(raster, lockMode);
}

RwRaster* RwRasterUnlockPalette(RwRaster* raster) {
    return ((RwRaster*(__cdecl *)(RwRaster*))0x7FAFF0)(raster);
}

RwInt32 RwRasterRegisterPlugin(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor constructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB) {
    return ((RwInt32(__cdecl *)(RwInt32, RwUInt32, RwPluginObjectConstructor, RwPluginObjectDestructor, RwPluginObjectCopy))0x7FB0B0)(size, pluginID, constructCB, destructCB, copyCB);
}

RwInt32 RwRasterGetPluginOffset(RwUInt32 pluginID) {
    return ((RwInt32(__cdecl *)(RwUInt32))0x7FAE40)(pluginID);
}

RxRenderStateVector* RxRenderStateVectorSetDefaultRenderStateVector(RxRenderStateVector* rsvp) {
    return ((RxRenderStateVector*(__cdecl *)(RxRenderStateVector*))0x80EA40)(rsvp);
}

RwImage* RwImageCreate(RwInt32 width, RwInt32 height, RwInt32 depth) {
    return ((RwImage*(__cdecl *)(RwInt32, RwInt32, RwInt32))0x8026E0)(width, height, depth);
}

RwBool RwImageDestroy(RwImage* image) {
    return ((RwBool(__cdecl *)(RwImage*))0x802740)(image);
}

RwImage* RwImageAllocatePixels(RwImage* image) {
    return ((RwImage*(__cdecl *)(RwImage*))0x8027A0)(image);
}

RwImage* RwImageFreePixels(RwImage* image) {
    return ((RwImage*(__cdecl *)(RwImage*))0x802860)(image);
}

RwImage* RwImageApplyMask(RwImage* image, const RwImage* mask) {
    return ((RwImage*(__cdecl *)(RwImage*, const RwImage*))0x802AF0)(image, mask);
}

RwImage* RwImageMakeMask(RwImage* image) {
    return ((RwImage*(__cdecl *)(RwImage*))0x802A20)(image);
}

RwImage* RwImageReadMaskedImage(const RwChar* imageName, const RwChar* maskname) {
    return ((RwImage*(__cdecl *)(const RwChar*, const RwChar*))0x8035C0)(imageName, maskname);
}

RwImage* RwImageRead(const RwChar* imageName) {
    return ((RwImage*(__cdecl *)(const RwChar*))0x802FD0)(imageName);
}

const RwChar* RwImageSetPath(const RwChar* path) {
    return ((const RwChar*(__cdecl *)(const RwChar*))0x802EA0)(path);
}

RwBool RwImageSetGamma(RwReal gammaValue) {
    return ((RwBool(__cdecl *)(RwReal))0x803FE0)(gammaValue);
}

RwImage* RwImageGammaCorrect(RwImage* image) {
    return ((RwImage*(__cdecl *)(RwImage*))0x803E30)(image);
}

RwBool RwPalQuantInit(RwPalQuant* pq) {
    return ((RwBool(__cdecl *)(RwPalQuant*))0x80C470)(pq);
}

void RwPalQuantTerm(RwPalQuant* pq) {
    ((void(__cdecl *)(RwPalQuant*))0x80C520)(pq);
}

void RwPalQuantAddImage(RwPalQuant* pq, RwImage* img, RwReal weight) {
    ((void(__cdecl *)(RwPalQuant*, RwImage*, RwReal))0x80AA80)(pq, img, weight);
}

RwInt32 RwPalQuantResolvePalette(RwRGBA* palette, RwInt32 maxcols, RwPalQuant* pq) {
    return ((RwInt32(__cdecl *)(RwRGBA*, RwInt32, RwPalQuant*))0x80AF60)(palette, maxcols, pq);
}

void RwPalQuantMatchImage(RwUInt8* dstpixels, RwInt32 dststride, RwInt32 dstdepth, RwBool dstPacked, RwPalQuant* pq, RwImage* img) {
    ((void(__cdecl *)(RwUInt8*, RwInt32, RwInt32, RwBool, RwPalQuant*, RwImage*))0x80BF20)(dstpixels, dststride, dstdepth, dstPacked, pq, img);
}

RwBool RwTextureSetMipmapping(RwBool enable) {
    return ((RwBool(__cdecl *)(RwBool))0x7F3530)(enable);
}

RwBool RwTextureGetMipmapping(void) {
    return ((RwBool(__cdecl *)(void))0x7F3550)();
}

RwBool RwTextureSetAutoMipmapping(RwBool enable) {
    return ((RwBool(__cdecl *)(RwBool))0x7F3560)(enable);
}

RwBool RwTextureGetAutoMipmapping(void) {
    return ((RwBool(__cdecl *)(void))0x7F3580)();
}

RwBool RwTextureSetMipmapGenerationCallBack(RwTextureCallBackMipmapGeneration callback) {
    return ((RwBool(__cdecl *)(RwTextureCallBackMipmapGeneration))0x7F3C70)(callback);
}

RwTextureCallBackMipmapGeneration RwTextureGetMipmapGenerationCallBack(void) {
    return ((RwTextureCallBackMipmapGeneration(__cdecl *)(void))0x7F3C90)();
}

RwBool RwTextureSetMipmapNameCallBack(RwTextureCallBackMipmapName callback) {
    return ((RwBool(__cdecl *)(RwTextureCallBackMipmapName))0x7F3CA0)(callback);
}

RwTextureCallBackMipmapName RwTextureGetMipmapNameCallBack(void) {
    return ((RwTextureCallBackMipmapName(__cdecl *)(void))0x7F3CC0)();
}

RwBool RwTextureGenerateMipmapName(RwChar* name, RwChar* maskName, RwUInt8 mipLevel, RwInt32 format) {
    return ((RwBool(__cdecl *)(RwChar*, RwChar*, RwUInt8, RwInt32))0x7F3AA0)(name, maskName, mipLevel, format);
}

RwBool RwTextureRasterGenerateMipmaps(RwRaster* raster, RwImage* image) {
    return ((RwBool(__cdecl *)(RwRaster*, RwImage*))0x7F3CD0)(raster, image);
}

RwBool _rwTextureSetAutoMipMapState(RwBool enable) {
    return ((RwBool(__cdecl *)(RwBool))0x7F3590)(enable);
}

RwBool _rwTextureGetAutoMipMapState(void) {
    return ((RwBool(__cdecl *)(void))0x7F35C0)();
}

RwTextureCallBackRead RwTextureGetReadCallBack(void) {
    return ((RwTextureCallBackRead(__cdecl *)(void))0x7F3520)();
}

RwBool RwTextureSetReadCallBack(RwTextureCallBackRead callBack) {
    return ((RwBool(__cdecl *)(RwTextureCallBackRead))0x7F3500)(callBack);
}

RwTextureCallBackFind RwTextureGetFindCallBack(void) {
    return ((RwTextureCallBackFind(__cdecl *)(void))0x7F34F0)();
}

RwBool RwTextureSetFindCallBack(RwTextureCallBackFind callBack) {
    return ((RwBool(__cdecl *)(RwTextureCallBackFind))0x7F34D0)(callBack);
}

RwTexture* RwTextureSetName(RwTexture* texture, const RwChar* name) {
    return ((RwTexture*(__cdecl *)(RwTexture*, const RwChar*))0x7F38A0)(texture, name);
}

RwTexture* RwTextureSetMaskName(RwTexture* texture, const RwChar* maskName) {
    return ((RwTexture*(__cdecl *)(RwTexture*, const RwChar*))0x7F3910)(texture, maskName);
}

void RwTexDictionarySetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc) {
    ((void(__cdecl *)(RwInt32, RwInt32))0x7F3E80)(blockSize, numBlocksToPrealloc);
}

RwTexDictionary* RwTexDictionaryCreate(void) {
    return ((RwTexDictionary*(__cdecl *)(void))0x7F3600)();
}

RwBool RwTexDictionaryDestroy(RwTexDictionary* dict) {
    return ((RwBool(__cdecl *)(RwTexDictionary*))0x7F36A0)(dict);
}

RwTexture* RwTextureCreate(RwRaster* raster) {
    return ((RwTexture*(__cdecl *)(RwRaster*))0x7F37C0)(raster);
}

RwBool RwTextureDestroy(RwTexture* texture) {
    return ((RwBool(__cdecl *)(RwTexture*))0x7F3820)(texture);
}

RwTexture* RwTextureSetRaster(RwTexture* texture, RwRaster* raster) {
    return ((RwTexture*(__cdecl *)(RwTexture*, RwRaster*))0x7F35D0)(texture, raster);
}

RwTexture* RwTexDictionaryAddTexture(RwTexDictionary* dict, RwTexture* texture) {
    return ((RwTexture*(__cdecl *)(RwTexDictionary*, RwTexture*))0x7F3980)(dict, texture);
}

RwTexture* RwTexDictionaryRemoveTexture(RwTexture* texture) {
    return ((RwTexture*(__cdecl *)(RwTexture*))0x7F39C0)(texture);
}

RwTexture* RwTexDictionaryFindNamedTexture(RwTexDictionary* dict, const RwChar* name) {
    return ((RwTexture*(__cdecl *)(RwTexDictionary*, const RwChar*))0x7F39F0)(dict, name);
}

RwTexDictionary* RwTexDictionaryGetCurrent(void) {
    return ((RwTexDictionary*(__cdecl *)(void))0x7F3A90)();
}

RwTexDictionary* RwTexDictionarySetCurrent(RwTexDictionary* dict) {
    return ((RwTexDictionary*(__cdecl *)(RwTexDictionary*))0x7F3A70)(dict);
}

const RwTexDictionary* RwTexDictionaryForAllTextures(const RwTexDictionary* dict, RwTextureCallBack fpCallBack, void* pData) {
    return ((const RwTexDictionary*(__cdecl *)(const RwTexDictionary*, RwTextureCallBack, void*))0x7F3730)(dict, fpCallBack, pData);
}

RwBool RwTexDictionaryForAllTexDictionaries(RwTexDictionaryCallBack fpCallBack, void* pData) {
    return ((RwBool(__cdecl *)(RwTexDictionaryCallBack, void*))0x7F3770)(fpCallBack, pData);
}

RwInt32 RwTextureRegisterPlugin(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor constructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB) {
    return ((RwInt32(__cdecl *)(RwInt32, RwUInt32, RwPluginObjectConstructor, RwPluginObjectDestructor, RwPluginObjectCopy))0x7F3BB0)(size, pluginID, constructCB, destructCB, copyCB);
}

RwInt32 RwTexDictionaryRegisterPlugin(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor constructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB) {
    return ((RwInt32(__cdecl *)(RwInt32, RwUInt32, RwPluginObjectConstructor, RwPluginObjectDestructor, RwPluginObjectCopy))0x7F3C10)(size, pluginID, constructCB, destructCB, copyCB);
}

RwInt32 RwTextureGetPluginOffset(RwUInt32 pluginID) {
    return ((RwInt32(__cdecl *)(RwUInt32))0x7F3BE0)(pluginID);
}

RwInt32 RwTexDictionaryGetPluginOffset(RwUInt32 pluginID) {
    return ((RwInt32(__cdecl *)(RwUInt32))0x7F3C40)(pluginID);
}

RwBool RwTextureValidatePlugins(const RwTexture* texture) {
    return ((RwBool(__cdecl *)(const RwTexture*))0x7F3C00)(texture);
}

RwBool RwTexDictionaryValidatePlugins(const RwTexDictionary* dict) {
    return ((RwBool(__cdecl *)(const RwTexDictionary*))0x7F3C60)(dict);
}

rwIm3DPool* _rwIm3DGetPool(void) {
    return ((rwIm3DPool*(__cdecl *)(void))0x7EFDD0)();
}

void* RwIm3DTransform(RwIm3DVertex* pVerts, RwUInt32 numVerts, RwMatrix* ltm, RwUInt32 flags) {
    return ((void*(__cdecl *)(RwIm3DVertex*, RwUInt32, RwMatrix*, RwUInt32))0x7EF450)(pVerts, numVerts, ltm, flags);
}

RwBool RwIm3DEnd(void) {
    return ((RwBool(__cdecl *)(void))0x7EF520)();
}

RwBool RwIm3DRenderLine(RwInt32 vert1, RwInt32 vert2) {
    return ((RwBool(__cdecl *)(RwInt32, RwInt32))0x7EF900)(vert1, vert2);
}

RwBool RwIm3DRenderTriangle(RwInt32 vert1, RwInt32 vert2, RwInt32 vert3) {
    return ((RwBool(__cdecl *)(RwInt32, RwInt32, RwInt32))0x7EF810)(vert1, vert2, vert3);
}

RwBool RwIm3DRenderIndexedPrimitive(RwPrimitiveType primType, RwImVertexIndex* indices, RwInt32 numIndices) {
    return ((RwBool(__cdecl *)(RwPrimitiveType, RwImVertexIndex*, RwInt32))0x7EF550)(primType, indices, numIndices);
}

RwBool RwIm3DRenderPrimitive(RwPrimitiveType primType) {
    return ((RwBool(__cdecl *)(RwPrimitiveType))0x7EF6B0)(primType);
}

RxPipeline* RwIm3DGetTransformPipeline(void) {
    return ((RxPipeline*(__cdecl *)(void))0x7EF9D0)();
}

RxPipeline* RwIm3DGetRenderPipeline(RwPrimitiveType primType) {
    return ((RxPipeline*(__cdecl *)(RwPrimitiveType))0x7EF9E0)(primType);
}

RxPipeline* RwIm3DSetTransformPipeline(RxPipeline* pipeline) {
    return ((RxPipeline*(__cdecl *)(RxPipeline*))0x7EFAC0)(pipeline);
}

RxPipeline* RwIm3DSetRenderPipeline(RxPipeline* pipeline, RwPrimitiveType primType) {
    return ((RxPipeline*(__cdecl *)(RxPipeline*, RwPrimitiveType))0x7EFB10)(pipeline, primType);
}

RwRaster* RwD3D9RasterStreamReadDDS(RwStream* stream) {
    return ((RwRaster*(__cdecl *)(RwStream*))0x81F360)(stream);
}

RwTexture* RwD3D9DDSTextureRead(const RwChar* name, const RwChar* maskname) {
    return ((RwTexture*(__cdecl *)(const RwChar*, const RwChar*))0x820A10)(name, maskname);
}

RwBool RwD3D9RasterIsCompressed(const RwRaster* raster) {
    return ((RwBool(__cdecl *)(const RwRaster*))0x820C90)(raster);
}

RwBool RwD3D9DeviceSupportsDXTTexture(void) {
    return ((RwBool(__cdecl *)(void))0x7F9C30)();
}

void* RwD3D9GetCurrentD3DDevice(void) {
    return ((void*(__cdecl *)(void))0x7F9D50)();
}

RwUInt32 RwD3D9EngineGetMaxMultiSamplingLevels(void) {
    return ((RwUInt32(__cdecl *)(void))0x7F84E0)();
}

void RwD3D9EngineSetMultiSamplingLevels(RwUInt32 numLevels) {
    ((void(__cdecl *)(RwUInt32))0x7F84F0)(numLevels);
}

void RwD3D9EngineSetRefreshRate(RwUInt32 refreshRate) {
    ((void(__cdecl *)(RwUInt32))0x7F8580)(refreshRate);
}

void RwD3D9EngineSetMultiThreadSafe(RwBool enable) {
    ((void(__cdecl *)(RwBool))0x7F8620)(enable);
}

void RwD3D9EngineSetSoftwareVertexProcessing(RwBool enable) {
    ((void(__cdecl *)(RwBool))0x7F8630)(enable);
}

void* RwD3D9GetCurrentD3DRenderTarget(RwUInt32 index) {
    return ((void*(__cdecl *)(RwUInt32))0x7F9E80)(index);
}

RwBool RwD3D9SetRenderTarget(RwUInt32 index, RwRaster* raster) {
    return ((RwBool(__cdecl *)(RwUInt32, RwRaster*))0x7F9E90)(index, raster);
}

RwBool RwD3D9ChangeVideoMode(RwInt32 modeIndex) {
    return ((RwBool(__cdecl *)(RwInt32))0x7F8640)(modeIndex);
}

RwBool RwD3D9ChangeMultiSamplingLevels(RwUInt32 numLevels) {
    return ((RwBool(__cdecl *)(RwUInt32))0x7F8A90)(numLevels);
}

RwBool RwD3D9CameraAttachWindow(void* camera, void* hwnd) {
    return ((RwBool(__cdecl *)(void*, void*))0x7F8D70)(camera, hwnd);
}

void RwD3D9SetStreamSource(RwUInt32 streamNumber, void* streamData, RwUInt32 offset, RwUInt32 stride) {
    ((void(__cdecl *)(RwUInt32, void*, RwUInt32, RwUInt32))0x7FA030)(streamNumber, streamData, offset, stride);
}

void _rwD3D9RenderStateFlushCache(void) {
    ((void(__cdecl *)(void))0x7FC200)();
}

void _rwD3D9DrawIndexedPrimitiveUP(RwUInt32 primitiveType, RwUInt32 minIndex, RwUInt32 numVertices, RwUInt32 primitiveCount, const void* indexData, const void* vertexStreamZeroData, RwUInt32 VertexStreamZeroStride) {
    ((void(__cdecl *)(RwUInt32, RwUInt32, RwUInt32, RwUInt32, const void*, const void*, RwUInt32))0x7FA1F0)(primitiveType, minIndex, numVertices, primitiveCount, indexData, vertexStreamZeroData, VertexStreamZeroStride);
}

void _rwD3D9DrawPrimitiveUP(RwUInt32 primitiveType, RwUInt32 primitiveCount, const void* vertexStreamZeroData, RwUInt32 VertexStreamZeroStride) {
    ((void(__cdecl *)(RwUInt32, RwUInt32, const void*, RwUInt32))0x7FA290)(primitiveType, primitiveCount, vertexStreamZeroData, VertexStreamZeroStride);
}

void _rwD3D9DrawIndexedPrimitive(RwUInt32 primitiveType, RwInt32 baseVertexIndex, RwUInt32 minIndex, RwUInt32 numVertices, RwUInt32 startIndex, RwUInt32 primitiveCount) {
    ((void(__cdecl *)(RwUInt32, RwInt32, RwUInt32, RwUInt32, RwUInt32, RwUInt32))0x7FA320)(primitiveType, baseVertexIndex, minIndex, numVertices, startIndex, primitiveCount);
}

void _rwD3D9SetVertexShaderConstant(RwUInt32 registerAddress, const void* constantData, RwUInt32 constantCount) {
    ((void(__cdecl *)(RwUInt32, const void*, RwUInt32))0x7FACA0)(registerAddress, constantData, constantCount);
}

void _rwD3D9SetPixelShaderConstant(RwUInt32 registerAddress, const void* constantData, RwUInt32 constantCount) {
    ((void(__cdecl *)(RwUInt32, const void*, RwUInt32))0x7FAD00)(registerAddress, constantData, constantCount);
}

void _rwD3D9SetFVF(RwUInt32 fvf) {
    ((void(__cdecl *)(RwUInt32))0x7F9F30)(fvf);
}

void _rwD3D9SetVertexShader(void *shader) {
    ((void(__cdecl *)(void *))0x7F9FB0)(shader);
}

void _rwD3D9SetPixelShader(void *shader) {
    ((void(__cdecl *)(void *))0x7F9FF0)(shader);
}

void RwD3D9SetRenderState(RwUInt32 state, RwUInt32 value) {
    ((void(__cdecl *)(RwUInt32, RwUInt32))0x7FC2D0)(state, value);
}

void RwD3D9GetRenderState(RwUInt32 state, void* value) {
    ((void(__cdecl *)(RwUInt32, void*))0x7FC320)(state, value);
}

void RwD3D9SetTextureStageState(RwUInt32 stage, RwUInt32 type, RwUInt32 value) {
    ((void(__cdecl *)(RwUInt32, RwUInt32, RwUInt32))0x7FC340)(stage, type, value);
}

void RwD3D9GetTextureStageState(RwUInt32 stage, RwUInt32 type, void* value) {
    ((void(__cdecl *)(RwUInt32, RwUInt32, void*))0x7FC3A0)(stage, type, value);
}

void RwD3D9SetSamplerState(RwUInt32 stage, RwUInt32 type, RwUInt32 value) {
    ((void(__cdecl *)(RwUInt32, RwUInt32, RwUInt32))0x7FC3C0)(stage, type, value);
}

void RwD3D9GetSamplerState(RwUInt32 stage, RwUInt32 type, void* value) {
    ((void(__cdecl *)(RwUInt32, RwUInt32, void*))0x7FC400)(stage, type, value);
}

void RwD3D9SetStencilClear(RwUInt32 stencilClear) {
    ((void(__cdecl *)(RwUInt32))0x7F9D30)(stencilClear);
}

RwUInt32 RwD3D9GetStencilClear(void) {
    return ((RwUInt32(__cdecl *)(void))0x7F9D40)();
}

RwBool RwD3D9SetTexture(RwTexture* texture, RwUInt32 stage) {
    return ((RwBool(__cdecl *)(RwTexture*, RwUInt32))0x7FDE70)(texture, stage);
}

RwBool RwD3D9SetTransform(RwUInt32 state, const void* matrix) {
    return ((RwBool(__cdecl *)(RwUInt32, const void*))0x7FA390)(state, matrix);
}

void RwD3D9GetTransform(RwUInt32 state, void* matrix) {
    ((void(__cdecl *)(RwUInt32, void*))0x7FA4F0)(state, matrix);
}

RwBool RwD3D9SetMaterial(const void* material) {
    return ((RwBool(__cdecl *)(const void*))0x7FC430)(material);
}

RwBool RwD3D9SetClipPlane(RwUInt32 index, const RwV4d* plane) {
    return ((RwBool(__cdecl *)(RwUInt32, const RwV4d*))0x7FC4A0)(index, plane);
}

RwBool RwD3D9SetTransformWorld(const RwMatrix* matrix) {
    return ((RwBool(__cdecl *)(const RwMatrix*))0x7FA520)(matrix);
}

RwBool RwD3D9SetSurfaceProperties(const RwSurfaceProperties* surfaceProps, const RwRGBA* color, RwUInt32 flags) {
    return ((RwBool(__cdecl *)(const RwSurfaceProperties*, const RwRGBA*, RwUInt32))0x7FC4D0)(surfaceProps, color, flags);
}

RwBool RwD3D9SetLight(RwInt32 index, const void* light) {
    return ((RwBool(__cdecl *)(RwInt32, const void*))0x7FA660)(index, light);
}

void RwD3D9GetLight(RwInt32 index, void* light) {
    ((void(__cdecl *)(RwInt32, void*))0x7FA820)(index, light);
}

RwBool RwD3D9EnableLight(RwInt32 index, RwBool enable) {
    return ((RwBool(__cdecl *)(RwInt32, RwBool))0x7FA860)(index, enable);
}

RwBool RwD3D9IndexBufferCreate(RwUInt32 numIndices, void* indexBuffer) {
    return ((RwBool(__cdecl *)(RwUInt32, void*))0x4C9970)(numIndices, indexBuffer);
}

RwBool RwD3D9CreateVertexDeclaration(const void* elements, void* vertexdeclaration) {
    return ((RwBool(__cdecl *)(const void*, void*))0x7FAA30)(elements, vertexdeclaration);
}

void RwD3D9DeleteVertexDeclaration(void) {
    ((void(__cdecl *)(void))0x7FAC10)();
}

void RwD3D9DeleteVertexShader(void) {
    ((void(__cdecl *)(void))0x7FAC90)();
}

RwBool RwD3D9CreatePixelShader(const RwUInt32* function, void* shader) {
    return ((RwBool(__cdecl *)(const RwUInt32*, void*))0x7FACC0)(function, shader);
}

void RwD3D9DeletePixelShader(void) {
    ((void(__cdecl *)(void))0x7FACF0)();
}

const void* RwD3D9GetCaps(void) {
    return ((const void*(__cdecl *)(void))0x7FAD20)();
}

RwBool RwD3D9CameraIsSphereFullyInsideFrustum(const void* camera, const void* sphere) {
    return ((RwBool(__cdecl *)(const void*, const void*))0x7FAD30)(camera, sphere);
}

RwBool RwD3D9CameraIsBBoxFullyInsideFrustum(const void* camera, const void* boundingBox) {
    return ((RwBool(__cdecl *)(const void*, const void*))0x7FAD90)(camera, boundingBox);
}

void _rwD3D9RasterConvertToNonPalettized(RwRaster* raster) {
    ((void(__cdecl *)(RwRaster*))0x4CD250)(raster);
}

RwBool _rwDeviceRegisterPlugin(void) {
    return ((RwBool(__cdecl *)(void))0x7F5F60)();
}

void _rwD3D9DeviceSetRestoreCallback(rwD3D9DeviceRestoreCallBack callback) {
    ((void(__cdecl *)(rwD3D9DeviceRestoreCallBack))0x7FAE20)(callback);
}

rwD3D9DeviceRestoreCallBack _rwD3D9DeviceGetRestoreCallback(void) {
    return ((rwD3D9DeviceRestoreCallBack(__cdecl *)(void))0x7FAE30)();
}

RwImage* RwImageResample(RwImage* dstImage, const RwImage* srcImage) {
    return ((RwImage*(__cdecl *)(RwImage*, const RwImage*))0x80C600)(dstImage, srcImage);
}

RwImage* RwImageCreateResample(const RwImage* srcImage, RwInt32 width, RwInt32 height) {
    return ((RwImage*(__cdecl *)(const RwImage*, RwInt32, RwInt32))0x80CD10)(srcImage, width, height);
}

RwImage* RwImageSetFromRaster(RwImage* image, RwRaster* raster) {
    return ((RwImage*(__cdecl *)(RwImage*, RwRaster*))0x804250)(image, raster);
}

RwRaster* RwRasterSetFromImage(RwRaster* raster, RwImage* image) {
    return ((RwRaster*(__cdecl *)(RwRaster*, RwImage*))0x804290)(raster, image);
}

RwRaster* RwRasterRead(const RwChar* filename) {
    return ((RwRaster*(__cdecl *)(const RwChar*))0x8043F0)(filename);
}

RwRaster* RwRasterReadMaskedRaster(const RwChar* filename, const RwChar* maskname) {
    return ((RwRaster*(__cdecl *)(const RwChar*, const RwChar*))0x8044E0)(filename, maskname);
}

RwImage* RwImageFindRasterFormat(RwImage* ipImage, RwInt32 nRasterType, RwInt32* npWidth, RwInt32* npHeight, RwInt32* npDepth, RwInt32* npFormat) {
    return ((RwImage*(__cdecl *)(RwImage*, RwInt32, RwInt32*, RwInt32*, RwInt32*, RwInt32*))0x8042C0)(ipImage, nRasterType, npWidth, npHeight, npDepth, npFormat);
}

RwFrame* RwFrameForAllObjects(RwFrame* frame, RwObjectCallBack callBack, void* data) {
    return ((RwFrame*(__cdecl *)(RwFrame*, RwObjectCallBack, void*))0x7F1200)(frame, callBack, data);
}

RwFrame* RwFrameTranslate(RwFrame* frame, const RwV3d* v, RwOpCombineType combine) {
    return ((RwFrame*(__cdecl *)(RwFrame*, const RwV3d*, RwOpCombineType))0x7F0E30)(frame, v, combine);
}

RwFrame* RwFrameRotate(RwFrame* frame, const RwV3d* axis, RwReal angle, RwOpCombineType combine) {
    return ((RwFrame*(__cdecl *)(RwFrame*, const RwV3d*, RwReal, RwOpCombineType))0x7F1010)(frame, axis, angle, combine);
}

RwFrame* RwFrameScale(RwFrame* frame, const RwV3d* v, RwOpCombineType combine) {
    return ((RwFrame*(__cdecl *)(RwFrame*, const RwV3d*, RwOpCombineType))0x7F0ED0)(frame, v, combine);
}

RwFrame* RwFrameTransform(RwFrame* frame, const RwMatrix* m, RwOpCombineType combine) {
    return ((RwFrame*(__cdecl *)(RwFrame*, const RwMatrix*, RwOpCombineType))0x7F0F70)(frame, m, combine);
}

RwFrame* RwFrameOrthoNormalize(RwFrame* frame) {
    return ((RwFrame*(__cdecl *)(RwFrame*))0x7F1170)(frame);
}

RwFrame* RwFrameSetIdentity(RwFrame* frame) {
    return ((RwFrame*(__cdecl *)(RwFrame*))0x7F10B0)(frame);
}

RwFrame* RwFrameCloneHierarchy(RwFrame* root) {
    return ((RwFrame*(__cdecl *)(RwFrame*))0x7F0250)(root);
}

RwBool RwFrameDestroyHierarchy(RwFrame* frame) {
    return ((RwBool(__cdecl *)(RwFrame*))0x7F08A0)(frame);
}

RwFrame* RwFrameForAllChildren(RwFrame* frame, RwFrameCallBack callBack, void* data) {
    return ((RwFrame*(__cdecl *)(RwFrame*, RwFrameCallBack, void*))0x7F0DC0)(frame, callBack, data);
}

RwFrame* RwFrameRemoveChild(RwFrame* child) {
    return ((RwFrame*(__cdecl *)(RwFrame*))0x7F0CD0)(child);
}

RwFrame* RwFrameAddChild(RwFrame* parent, RwFrame* child) {
    return ((RwFrame*(__cdecl *)(RwFrame*, RwFrame*))0x7F0B00)(parent, child);
}

RwFrame* RwFrameAddChildNoUpdate(RwFrame* parent, RwFrame* child) {
    return ((RwFrame*(__cdecl *)(RwFrame*, RwFrame*))0x7F09C0)(parent, child);
}

RwFrame* RwFrameGetRoot(const RwFrame* frame) {
    return ((RwFrame*(__cdecl *)(const RwFrame*))0x7F09B0)(frame);
}

RwMatrix* RwFrameGetLTM(RwFrame* frame) {
    return ((RwMatrix*(__cdecl *)(RwFrame*))0x7F0990)(frame);
}

RwFrame* RwFrameUpdateObjects(RwFrame* frame) {
    return ((RwFrame*(__cdecl *)(RwFrame*))0x7F0910)(frame);
}

void RwFrameSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc) {
    ((void(__cdecl *)(RwInt32, RwInt32))0x7EFED0)(blockSize, numBlocksToPrealloc);
}

RwFrame* RwFrameCreate(void) {
    return ((RwFrame*(__cdecl *)(void))0x7F0410)();
}

RwBool RwFrameDestroy(RwFrame* frame) {
    return ((RwBool(__cdecl *)(RwFrame*))0x7F05A0)(frame);
}

void _rwFrameInit(RwFrame* frame) {
    ((void(__cdecl *)(RwFrame*))0x7F0450)(frame);
}

void _rwFrameDeInit(RwFrame* frame) {
    ((void(__cdecl *)(RwFrame*))0x7F06F0)(frame);
}

RwBool RwFrameDirty(const RwFrame* frame) {
    return ((RwBool(__cdecl *)(const RwFrame*))0x7F0340)(frame);
}

RwInt32 RwFrameCount(RwFrame* frame) {
    return ((RwInt32(__cdecl *)(RwFrame*))0x7F0E00)(frame);
}

RwInt32 RwFrameRegisterPlugin(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor constructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB) {
    return ((RwInt32(__cdecl *)(RwInt32, RwUInt32, RwPluginObjectConstructor, RwPluginObjectDestructor, RwPluginObjectCopy))0x7F1260)(size, pluginID, constructCB, destructCB, copyCB);
}

RwInt32 RwFrameGetPluginOffset(RwUInt32 pluginID) {
    return ((RwInt32(__cdecl *)(RwUInt32))0x7F1290)(pluginID);
}

RwBool RwFrameValidatePlugins(const RwFrame* frame) {
    return ((RwBool(__cdecl *)(const RwFrame*))0x7F12B0)(frame);
}

RwFrame* _rwFrameCloneAndLinkClones(RwFrame* root) {
    return ((RwFrame*(__cdecl *)(RwFrame*))0x7EFFB0)(root);
}

RwFrame* _rwFramePurgeClone(RwFrame* root) {
    return ((RwFrame*(__cdecl *)(RwFrame*))0x7F01A0)(root);
}

void _rwObjectHasFrameReleaseFrame(void) {
    ((void(__cdecl *)(void))0x804F40)();
}

RwBool _rwFrameSyncDirty(void) {
    return ((RwBool(__cdecl *)(void))0x809550)();
}

void _rwFrameSyncHierarchyLTM(RwFrame* frame) {
    ((void(__cdecl *)(RwFrame*))0x8097D0)(frame);
}

RwInt32 RwTextureRegisterPluginStream(RwUInt32 pluginID, RwPluginDataChunkReadCallBack readCB, RwPluginDataChunkWriteCallBack writeCB, RwPluginDataChunkGetSizeCallBack getSizeCB) {
    return ((RwInt32(__cdecl *)(RwUInt32, RwPluginDataChunkReadCallBack, RwPluginDataChunkWriteCallBack, RwPluginDataChunkGetSizeCallBack))0x804550)(pluginID, readCB, writeCB, getSizeCB);
}

RwInt32 RwTextureSetStreamAlwaysCallBack(RwUInt32 pluginID, RwPluginDataChunkAlwaysCallBack alwaysCB) {
    return ((RwInt32(__cdecl *)(RwUInt32, RwPluginDataChunkAlwaysCallBack))0x804580)(pluginID, alwaysCB);
}

RwUInt32 RwTextureStreamGetSize(const RwTexture* texture) {
    return ((RwUInt32(__cdecl *)(const RwTexture*))0x8045A0)(texture);
}

RwTexture* RwTextureStreamRead(RwStream* stream) {
    return ((RwTexture*(__cdecl *)(RwStream*))0x8046E0)(stream);
}

const RwTexture* RwTextureStreamWrite(const RwTexture* texture, RwStream* stream) {
    return ((const RwTexture*(__cdecl *)(const RwTexture*, RwStream*))0x8045E0)(texture, stream);
}

RwInt32 RwTexDictionaryRegisterPluginStream(RwUInt32 pluginID, RwPluginDataChunkReadCallBack readCB, RwPluginDataChunkWriteCallBack writeCB, RwPluginDataChunkGetSizeCallBack getSizeCB) {
    return ((RwInt32(__cdecl *)(RwUInt32, RwPluginDataChunkReadCallBack, RwPluginDataChunkWriteCallBack, RwPluginDataChunkGetSizeCallBack))0x8048E0)(pluginID, readCB, writeCB, getSizeCB);
}

RwInt32 RwTexDictionarySetStreamAlwaysCallBack(RwUInt32 pluginID, RwPluginDataChunkAlwaysCallBack alwaysCB) {
    return ((RwInt32(__cdecl *)(RwUInt32, RwPluginDataChunkAlwaysCallBack))0x804910)(pluginID, alwaysCB);
}

RwUInt32 RwTexDictionaryStreamGetSize(const RwTexDictionary* texDict) {
    return ((RwUInt32(__cdecl *)(const RwTexDictionary*))0x804930)(texDict);
}

RwTexDictionary* RwTexDictionaryStreamRead(RwStream* stream) {
    return ((RwTexDictionary*(__cdecl *)(RwStream*))0x804C30)(stream);
}

const RwTexDictionary* RwTexDictionaryStreamWrite(const RwTexDictionary* texDict, RwStream* stream) {
    return ((const RwTexDictionary*(__cdecl *)(const RwTexDictionary*, RwStream*))0x8049F0)(texDict, stream);
}

RwTextureChunkInfo* _rwTextureChunkInfoRead(RwStream* stream, RwTextureChunkInfo* textureChunkInfo, RwInt32* bytesRead) {
    return ((RwTextureChunkInfo*(__cdecl *)(RwStream*, RwTextureChunkInfo*, RwInt32*))0x804E60)(stream, textureChunkInfo, bytesRead);
}

void RwFrameListSetAutoUpdate(RwBool flag) {
    ((void(__cdecl *)(RwBool))0x807570)(flag);
}

RwInt32 RwFrameRegisterPluginStream(RwUInt32 pluginID, RwPluginDataChunkReadCallBack readCB, RwPluginDataChunkWriteCallBack writeCB, RwPluginDataChunkGetSizeCallBack getSizeCB) {
    return ((RwInt32(__cdecl *)(RwUInt32, RwPluginDataChunkReadCallBack, RwPluginDataChunkWriteCallBack, RwPluginDataChunkGetSizeCallBack))0x807580)(pluginID, readCB, writeCB, getSizeCB);
}

RwInt32 RwFrameSetStreamAlwaysCallBack(RwUInt32 pluginID, RwPluginDataChunkAlwaysCallBack alwaysCB) {
    return ((RwInt32(__cdecl *)(RwUInt32, RwPluginDataChunkAlwaysCallBack))0x8075B0)(pluginID, alwaysCB);
}

rwFrameList* _rwFrameListInitialize(rwFrameList* frameList, RwFrame* frame) {
    return ((rwFrameList*(__cdecl *)(rwFrameList*, RwFrame*))0x8075D0)(frameList, frame);
}

RwBool _rwFrameListFindFrame(const rwFrameList* frameList, const RwFrame* frame, RwInt32* npIndex) {
    return ((RwBool(__cdecl *)(const rwFrameList*, const RwFrame*, RwInt32*))0x8076E0)(frameList, frame, npIndex);
}

rwFrameList* _rwFrameListDeinitialize(rwFrameList* frameList) {
    return ((rwFrameList*(__cdecl *)(rwFrameList*))0x807720)(frameList);
}

RwUInt32 _rwFrameListStreamGetSize(const rwFrameList* frameList) {
    return ((RwUInt32(__cdecl *)(const rwFrameList*))0x807750)(frameList);
}

rwFrameList* _rwFrameListStreamRead(RwStream* stream, rwFrameList* fl) {
    return ((rwFrameList*(__cdecl *)(RwStream*, rwFrameList*))0x807970)(stream, fl);
}

const rwFrameList* _rwFrameListStreamWrite(const rwFrameList* frameList, RwStream* stream) {
    return ((const rwFrameList*(__cdecl *)(const rwFrameList*, RwStream*))0x8077A0)(frameList, stream);
}

RwBBox* RwBBoxCalculate(RwBBox* boundBox, const RwV3d* verts, RwInt32 numVerts) {
    return ((RwBBox*(__cdecl *)(RwBBox*, const RwV3d*, RwInt32))0x808F60)(boundBox, verts, numVerts);
}

RwBBox* RwBBoxInitialize(RwBBox* boundBox, const RwV3d* vertex) {
    return ((RwBBox*(__cdecl *)(RwBBox*, const RwV3d*))0x809020)(boundBox, vertex);
}

RwBBox* RwBBoxAddPoint(RwBBox* boundBox, const RwV3d* vertex) {
    return ((RwBBox*(__cdecl *)(RwBBox*, const RwV3d*))0x809060)(boundBox, vertex);
}

RwBool RwBBoxContainsPoint(const RwBBox* boundBox, const RwV3d* vertex) {
    return ((RwBool(__cdecl *)(const RwBBox*, const RwV3d*))0x8090E0)(boundBox, vertex);
}

RwCamera* RwCameraBeginUpdate(RwCamera* camera) {
    return ((RwCamera*(__cdecl *)(RwCamera*))0x7EE190)(camera);
}

RwCamera* RwCameraEndUpdate(RwCamera* camera) {
    return ((RwCamera*(__cdecl *)(RwCamera*))0x7EE180)(camera);
}

RwCamera* RwCameraClear(RwCamera* camera, RwRGBA* colour, RwInt32 clearMode) {
    return ((RwCamera*(__cdecl *)(RwCamera*, RwRGBA*, RwInt32))0x7EE340)(camera, colour, clearMode);
}

RwCamera* RwCameraShowRaster(RwCamera* camera, void* pDev, RwUInt32 flags) {
    return ((RwCamera*(__cdecl *)(RwCamera*, void*, RwUInt32))0x7EE370)(camera, pDev, flags);
}

void RwCameraSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc) {
    ((void(__cdecl *)(RwInt32, RwInt32))0x7EE0F0)(blockSize, numBlocksToPrealloc);
}

RwBool RwCameraDestroy(RwCamera* camera) {
    return ((RwBool(__cdecl *)(RwCamera*))0x7EE4B0)(camera);
}

RwCamera* RwCameraCreate(void) {
    return ((RwCamera*(__cdecl *)(void))0x7EE4F0)();
}

RwCamera* RwCameraClone(RwCamera* camera) {
    return ((RwCamera*(__cdecl *)(RwCamera*))0x7EF3B0)(camera);
}

RwCamera* RwCameraSetViewOffset(RwCamera* camera, const RwV2d* offset) {
    return ((RwCamera*(__cdecl *)(RwCamera*, const RwV2d*))0x7EE1A0)(camera, offset);
}

RwCamera* RwCameraSetViewWindow(RwCamera* camera, const RwV2d* viewWindow) {
    return ((RwCamera*(__cdecl *)(RwCamera*, const RwV2d*))0x7EE410)(camera, viewWindow);
}

RwCamera* RwCameraSetProjection(RwCamera* camera, RwCameraProjection projection) {
    return ((RwCamera*(__cdecl *)(RwCamera*, RwCameraProjection))0x7EE3A0)(camera, projection);
}

RwCamera* RwCameraSetNearClipPlane(RwCamera* camera, RwReal nearClip) {
    return ((RwCamera*(__cdecl *)(RwCamera*, RwReal))0x7EE1D0)(camera, nearClip);
}

RwCamera* RwCameraSetFarClipPlane(RwCamera* camera, RwReal farClip) {
    return ((RwCamera*(__cdecl *)(RwCamera*, RwReal))0x7EE2A0)(camera, farClip);
}

RwInt32 RwCameraRegisterPlugin(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor constructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB) {
    return ((RwInt32(__cdecl *)(RwInt32, RwUInt32, RwPluginObjectConstructor, RwPluginObjectDestructor, RwPluginObjectCopy))0x7EE450)(size, pluginID, constructCB, destructCB, copyCB);
}

RwInt32 RwCameraGetPluginOffset(RwUInt32 pluginID) {
    return ((RwInt32(__cdecl *)(RwUInt32))0x7EE480)(pluginID);
}

RwBool RwCameraValidatePlugins(const RwCamera* camera) {
    return ((RwBool(__cdecl *)(const RwCamera*))0x7EE4A0)(camera);
}

RwFrustumTestResult RwCameraFrustumTestSphere(const RwCamera* camera, const RwSphere* sphere) {
    return ((RwFrustumTestResult(__cdecl *)(const RwCamera*, const RwSphere*))0x7EE2D0)(camera, sphere);
}

RwInt32 RwCameraRegisterPluginStream(RwUInt32 pluginID, RwPluginDataChunkReadCallBack readCB, RwPluginDataChunkWriteCallBack writeCB, RwPluginDataChunkGetSizeCallBack getSizeCB) {
    return ((RwInt32(__cdecl *)(RwUInt32, RwPluginDataChunkReadCallBack, RwPluginDataChunkWriteCallBack, RwPluginDataChunkGetSizeCallBack))0x808C90)(pluginID, readCB, writeCB, getSizeCB);
}

RwInt32 RwCameraSetStreamAlwaysCallBack(RwUInt32 pluginID, RwPluginDataChunkAlwaysCallBack alwaysCB) {
    return ((RwInt32(__cdecl *)(RwUInt32, RwPluginDataChunkAlwaysCallBack))0x808CC0)(pluginID, alwaysCB);
}

RwUInt32 RwCameraStreamGetSize(const RwCamera* camera) {
    return ((RwUInt32(__cdecl *)(const RwCamera*))0x808CE0)(camera);
}

RwCamera* RwCameraStreamRead(RwStream* stream) {
    return ((RwCamera*(__cdecl *)(RwStream*))0x808DE0)(stream);
}

const RwCamera* RwCameraStreamWrite(const RwCamera* camera, RwStream* stream) {
    return ((const RwCamera*(__cdecl *)(const RwCamera*, RwStream*))0x808D00)(camera, stream);
}

RwCameraChunkInfo* RwCameraChunkInfoRead(RwStream* stream, RwCameraChunkInfo* cameraChunkInfo, RwInt32* bytesRead) {
    return ((RwCameraChunkInfo*(__cdecl *)(RwStream*, RwCameraChunkInfo*, RwInt32*))0x808EF0)(stream, cameraChunkInfo, bytesRead);
}

/* rpworld.h */

void _rwD3D9VSSetActiveWorldMatrix(const RwMatrix* worldMatrix) {
    ((void(__cdecl *)(const RwMatrix*))0x764650)(worldMatrix);
}

void _rwD3D9VSGetComposedTransformMatrix(void) {
    ((void(__cdecl *)(void))0x7646E0)();
}

void _rwD3D9VSGetWorldViewTransposedMatrix(void) {
    ((void(__cdecl *)(void))0x764730)();
}

void _rwD3D9VSGetWorldViewMatrix(void) {
    ((void(__cdecl *)(void))0x764760)();
}

void _rwD3D9VSGetInverseWorldMatrix(void) {
    ((void(__cdecl *)(void))0x7647B0)();
}

void _rwD3D9VSGetWorldMultiplyMatrix(RwMatrix* worldMultiplyMatrix, const RwMatrix* matrix) {
    ((void(__cdecl *)(RwMatrix*, const RwMatrix*))0x764920)(worldMultiplyMatrix, matrix);
}

void _rwD3D9VSGetWorldMultiplyTransposeMatrix(void* worldMultiplyMatrix, const RwMatrix* matrix) {
    ((void(__cdecl *)(void*, const RwMatrix*))0x764960)(worldMultiplyMatrix, matrix);
}

void _rwD3D9VSGetWorldViewMultiplyTransposeMatrix(void* worldViewMultiplyMatrix, const RwMatrix* matrix) {
    ((void(__cdecl *)(void*, const RwMatrix*))0x7649D0)(worldViewMultiplyMatrix, matrix);
}

void _rwD3D9VSGetWorldNormalizedMultiplyTransposeMatrix(void* worldMultiplyMatrix, const RwMatrix* matrix) {
    ((void(__cdecl *)(void*, const RwMatrix*))0x764A70)(worldMultiplyMatrix, matrix);
}

void _rwD3D9VSGetWorldNormalizedViewMultiplyTransposeMatrix(void* worldViewMultiplyMatrix, const RwMatrix* matrix) {
    ((void(__cdecl *)(void*, const RwMatrix*))0x764B50)(worldViewMultiplyMatrix, matrix);
}

void _rwD3D9VSGetWorldNormalizedTransposeMatrix(void) {
    ((void(__cdecl *)(void))0x764C60)();
}

void _rwD3D9VSGetProjectionTransposedMatrix(void) {
    ((void(__cdecl *)(void))0x764D20)();
}

void _rwD3D9VSGetNormalInLocalSpace(const RwV3d* normalWorldSpace, RwV3d* normalLocalSpace) {
    ((void(__cdecl *)(const RwV3d*, RwV3d*))0x764D30)(normalWorldSpace, normalLocalSpace);
}

void _rwD3D9VSGetPointInLocalSpace(const RwV3d* pointWorldSpace, RwV3d* pointLocalSpace) {
    ((void(__cdecl *)(const RwV3d*, RwV3d*))0x764E70)(pointWorldSpace, pointLocalSpace);
}

void _rwD3D9VSGetRadiusInLocalSpace(RwReal radiusWorldSpace, RwReal* radiusLocalSpace) {
    ((void(__cdecl *)(RwReal, RwReal*))0x764F60)(radiusWorldSpace, radiusLocalSpace);
}

void _rpD3D9VertexShaderCachePurge(void) {
    ((void(__cdecl *)(void))0x75EE60)();
}

void* _rpD3D9GetVertexShader(const _rpD3D9VertexShaderDescriptor* desc, _rpD3D9VertexShaderDispatchDescriptor* dispatch) {
    return ((void*(__cdecl *)(const _rpD3D9VertexShaderDescriptor*, _rpD3D9VertexShaderDispatchDescriptor*))0x75EED0)(desc, dispatch);
}

RwUInt32 _rpD3D9GetNumConstantsUsed(const _rpD3D9VertexShaderDescriptor* desc) {
    return ((RwUInt32(__cdecl *)(const _rpD3D9VertexShaderDescriptor*))0x75EDD0)(desc);
}

void _rxD3D9VertexShaderDefaultBeginCallBack(void* object, RwUInt32 type, _rpD3D9VertexShaderDescriptor* desc) {
    ((void(__cdecl *)(void*, RwUInt32, _rpD3D9VertexShaderDescriptor*))0x760DF0)(object, type, desc);
}

RwV4d* _rxD3D9VertexShaderDefaultLightingCallBack(void* object, RwUInt32 type, RwV4d* shaderConstantPtr, _rpD3D9VertexShaderDescriptor* desc) {
    return ((RwV4d*(__cdecl *)(void*, RwUInt32, RwV4d*, _rpD3D9VertexShaderDescriptor*))0x761170)(object, type, shaderConstantPtr, desc);
}

void* _rxD3D9VertexShaderDefaultGetMaterialShaderCallBack(const RpMaterial* material, _rpD3D9VertexShaderDescriptor* desc, _rpD3D9VertexShaderDispatchDescriptor* dispatch) {
    return ((void*(__cdecl *)(const RpMaterial*, _rpD3D9VertexShaderDescriptor*, _rpD3D9VertexShaderDispatchDescriptor*))0x761010)(material, desc, dispatch);
}

void _rxD3D9VertexShaderDefaultMeshRenderCallBack(RxD3D9ResEntryHeader* resEntryHeader, RxD3D9InstanceData* instancedMesh, const _rpD3D9VertexShaderDescriptor* desc, const _rpD3D9VertexShaderDispatchDescriptor* dispatch) {
    ((void(__cdecl *)(RxD3D9ResEntryHeader*, RxD3D9InstanceData*, const _rpD3D9VertexShaderDescriptor*, const _rpD3D9VertexShaderDispatchDescriptor*))0x761030)(resEntryHeader, instancedMesh, desc, dispatch);
}

void _rxD3D9VertexShaderDefaultEndCallBack(void* object, RwUInt32 type, _rpD3D9VertexShaderDescriptor* desc) {
    ((void(__cdecl *)(void*, RwUInt32, _rpD3D9VertexShaderDescriptor*))0x761000)(object, type, desc);
}

void _rpD3D9VertexShaderUpdateLightsColors(RwV4d* shaderConstantPtr, const _rpD3D9VertexShaderDescriptor* desc, RwReal ambientCoef, RwReal diffuseCoef) {
    ((void(__cdecl *)(RwV4d*, const _rpD3D9VertexShaderDescriptor*, RwReal, RwReal))0x761720)(shaderConstantPtr, desc, ambientCoef, diffuseCoef);
}

void _rpD3D9VertexShaderUpdateMaterialColor(const RwRGBA* color, const _rpD3D9VertexShaderDispatchDescriptor* dispatch) {
    ((void(__cdecl *)(const RwRGBA*, const _rpD3D9VertexShaderDispatchDescriptor*))0x761820)(color, dispatch);
}

void _rpD3D9VertexShaderUpdateFogData(const _rpD3D9VertexShaderDescriptor* desc, const _rpD3D9VertexShaderDispatchDescriptor* dispatch) {
    ((void(__cdecl *)(const _rpD3D9VertexShaderDescriptor*, const _rpD3D9VertexShaderDispatchDescriptor*))0x7618B0)(desc, dispatch);
}

void _rpD3D9VertexShaderUpdateMorphingCoef(RwReal morphingCoef, const _rpD3D9VertexShaderDispatchDescriptor* dispatch) {
    ((void(__cdecl *)(RwReal, const _rpD3D9VertexShaderDispatchDescriptor*))0x761950)(morphingCoef, dispatch);
}

void _rpD3DVertexShaderSetUVAnimMatrix(RwMatrix* matrix, const _rpD3D9VertexShaderDispatchDescriptor* dispatch) {
    ((void(__cdecl *)(RwMatrix*, const _rpD3D9VertexShaderDispatchDescriptor*))0x7619A0)(matrix, dispatch);
}

void _rpD3D9VertexShaderSetEnvMatrix(RwFrame* frame, const _rpD3D9VertexShaderDescriptor* desc, const _rpD3D9VertexShaderDispatchDescriptor* dispatch) {
    ((void(__cdecl *)(RwFrame*, const _rpD3D9VertexShaderDescriptor*, const _rpD3D9VertexShaderDispatchDescriptor*))0x761A10)(frame, desc, dispatch);
}

void _rpD3D9VertexShaderSetBumpMatrix(RwFrame* frame, RwReal factor, const _rpD3D9VertexShaderDispatchDescriptor* dispatch) {
    ((void(__cdecl *)(RwFrame*, RwReal, const _rpD3D9VertexShaderDispatchDescriptor*))0x761B70)(frame, factor, dispatch);
}

RxNodeDefinition* RxNodeDefinitionGetD3D9WorldSectorAllInOne(void) {
    return ((RxNodeDefinition*(__cdecl *)(void))0x75E9F0)();
}

RxNodeDefinition* RxNodeDefinitionGetD3D9AtomicAllInOne(void) {
    return ((RxNodeDefinition*(__cdecl *)(void))0x7582E0)();
}

void RpMaterialSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc) {
    ((void(__cdecl *)(RwInt32, RwInt32))0x74D8C0)(blockSize, numBlocksToPrealloc);
}

RpMaterial* RpMaterialCreate(void) {
    return ((RpMaterial*(__cdecl *)(void))0x74D990)();
}

RwBool RpMaterialDestroy(RpMaterial* material) {
    return ((RwBool(__cdecl *)(RpMaterial*))0x74DA20)(material);
}

RpMaterial* RpMaterialClone(RpMaterial* material) {
    return ((RpMaterial*(__cdecl *)(RpMaterial*))0x74DA80)(material);
}

RpMaterial* RpMaterialSetTexture(RpMaterial* material, RwTexture* texture) {
    return ((RpMaterial*(__cdecl *)(RpMaterial*, RwTexture*))0x74DBC0)(material, texture);
}

RwInt32 RpMaterialRegisterPlugin(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor constructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB) {
    return ((RwInt32(__cdecl *)(RwInt32, RwUInt32, RwPluginObjectConstructor, RwPluginObjectDestructor, RwPluginObjectCopy))0x74DBF0)(size, pluginID, constructCB, destructCB, copyCB);
}

RwInt32 RpMaterialRegisterPluginStream(RwUInt32 pluginID, RwPluginDataChunkReadCallBack readCB, RwPluginDataChunkWriteCallBack writeCB, RwPluginDataChunkGetSizeCallBack getSizeCB) {
    return ((RwInt32(__cdecl *)(RwUInt32, RwPluginDataChunkReadCallBack, RwPluginDataChunkWriteCallBack, RwPluginDataChunkGetSizeCallBack))0x74DC20)(pluginID, readCB, writeCB, getSizeCB);
}

RwInt32 RpMaterialSetStreamAlwaysCallBack(RwUInt32 pluginID, RwPluginDataChunkAlwaysCallBack alwaysCB) {
    return ((RwInt32(__cdecl *)(RwUInt32, RwPluginDataChunkAlwaysCallBack))0x74DC50)(pluginID, alwaysCB);
}

RwInt32 RpMaterialSetStreamRightsCallBack(RwUInt32 pluginID, RwPluginDataChunkRightsCallBack rightsCB) {
    return ((RwInt32(__cdecl *)(RwUInt32, RwPluginDataChunkRightsCallBack))0x74DC70)(pluginID, rightsCB);
}

RwInt32 RpMaterialGetPluginOffset(RwUInt32 pluginID) {
    return ((RwInt32(__cdecl *)(RwUInt32))0x74DC90)(pluginID);
}

RwBool RpMaterialValidatePlugins(const RpMaterial* material) {
    return ((RwBool(__cdecl *)(const RpMaterial*))0x74DCB0)(material);
}

RwUInt32 RpMaterialStreamGetSize(const RpMaterial* material) {
    return ((RwUInt32(__cdecl *)(const RpMaterial*))0x74E010)(material);
}

RpMaterial* RpMaterialStreamRead(RwStream* stream) {
    return ((RpMaterial*(__cdecl *)(RwStream*))0x74DD30)(stream);
}

const RpMaterial* RpMaterialStreamWrite(const RpMaterial* material, RwStream* stream) {
    return ((const RpMaterial*(__cdecl *)(const RpMaterial*, RwStream*))0x74E050)(material, stream);
}

RpMaterialChunkInfo* _rpMaterialChunkInfoRead(RwStream* stream, RpMaterialChunkInfo* materialChunkInfo, RwInt32* bytesRead) {
    return ((RpMaterialChunkInfo*(__cdecl *)(RwStream*, RpMaterialChunkInfo*, RwInt32*))0x74DCC0)(stream, materialChunkInfo, bytesRead);
}

RpMaterialList* _rpMaterialListInitialize(RpMaterialList* matList) {
    return ((RpMaterialList*(__cdecl *)(RpMaterialList*))0x74E1B0)(matList);
}

RpMaterialList* _rpMaterialListDeinitialize(RpMaterialList* matList) {
    return ((RpMaterialList*(__cdecl *)(RpMaterialList*))0x74E150)(matList);
}

RpMaterial** _rpMaterialListAlloc(RwUInt32 count) {
    return ((RpMaterial**(__cdecl *)(RwUInt32))0x74E1C0)(count);
}

RpMaterial* _rpMaterialListGetMaterial(const RpMaterialList* matList, RwInt32 matIndex) {
    return ((RpMaterial*(__cdecl *)(const RpMaterialList*, RwInt32))0x74E2B0)(matList, matIndex);
}

RpMaterialList* _rpMaterialListSetSize(RpMaterialList* matList, RwInt32 size) {
    return ((RpMaterialList*(__cdecl *)(RpMaterialList*, RwInt32))0x74E2C0)(matList, size);
}

RpMaterialList* _rpMaterialListCopy(RpMaterialList* matListOut, const RpMaterialList* matListIn) {
    return ((RpMaterialList*(__cdecl *)(RpMaterialList*, const RpMaterialList*))0x74E1F0)(matListOut, matListIn);
}

RwInt32 _rpMaterialListAppendMaterial(RpMaterialList* matList, RpMaterial* material) {
    return ((RwInt32(__cdecl *)(RpMaterialList*, RpMaterial*))0x74E350)(matList, material);
}

RwInt32 _rpMaterialListFindMaterialIndex(const RpMaterialList* matList, const RpMaterial* material) {
    return ((RwInt32(__cdecl *)(const RpMaterialList*, const RpMaterial*))0x74E420)(matList, material);
}

RwUInt32 _rpMaterialListStreamGetSize(const RpMaterialList* matList) {
    return ((RwUInt32(__cdecl *)(const RpMaterialList*))0x74E450)(matList);
}

RpMaterialList* _rpMaterialListStreamRead(RwStream* stream, RpMaterialList* matList) {
    return ((RpMaterialList*(__cdecl *)(RwStream*, RpMaterialList*))0x74E600)(stream, matList);
}

const RpMaterialList* _rpMaterialListStreamWrite(const RpMaterialList* matList, RwStream* stream) {
    return ((const RpMaterialList*(__cdecl *)(const RpMaterialList*, RwStream*))0x74E4B0)(matList, stream);
}

void* _rpMeshOpen(void* instance, RwInt32 offset, RwInt32 size) {
    return ((void*(__cdecl *)(void*, RwInt32, RwInt32))0x758970)(instance, offset, size);
}

void* _rpMeshClose(void* instance, RwInt32 offset, RwInt32 size) {
    return ((void*(__cdecl *)(void*, RwInt32, RwInt32))0x758940)(instance, offset, size);
}

RwInt16 _rpMeshGetNextSerialNumber(void) {
    return ((RwInt16(__cdecl *)(void))0x7590E0)();
}

RpBuildMesh* _rpBuildMeshCreate(RwUInt32 bufferSize) {
    return ((RpBuildMesh*(__cdecl *)(RwUInt32))0x758A90)(bufferSize);
}

RwBool _rpBuildMeshDestroy(RpBuildMesh* mesh) {
    return ((RwBool(__cdecl *)(RpBuildMesh*))0x758B80)(mesh);
}

RwBool _rpMeshDestroy(RpMeshHeader* mesh) {
    return ((RwBool(__cdecl *)(RpMeshHeader*))0x758BC0)(mesh);
}

RpBuildMesh* _rpBuildMeshAddTriangle(RpBuildMesh* mesh, RpMaterial* material, RwInt32 vert1, RwInt32 vert2, RwInt32 vert3, RwUInt16 matIndex, RwUInt16 textureIndex, RwUInt16 rasterIndex, RwUInt16 pipelineIndex) {
    return ((RpBuildMesh*(__cdecl *)(RpBuildMesh*, RpMaterial*, RwInt32, RwInt32, RwInt32, RwUInt16, RwUInt16, RwUInt16, RwUInt16))0x758C00)(mesh, material, vert1, vert2, vert3, matIndex, textureIndex, rasterIndex, pipelineIndex);
}

RpMeshHeader* _rpMeshHeaderForAllMeshes(RpMeshHeader* meshHeader, RpMeshCallBack fpCallBack, void* pData) {
    return ((RpMeshHeader*(__cdecl *)(RpMeshHeader*, RpMeshCallBack, void*))0x758D30)(meshHeader, fpCallBack, pData);
}

RwStream* _rpMeshWrite(const RpMeshHeader* meshHeader, const void* object, RwStream* stream, const RpMaterialList* matList) {
    return ((RwStream*(__cdecl *)(const RpMeshHeader*, const void*, RwStream*, const RpMaterialList*))0x758D70)(meshHeader, object, stream, matList);
}

RpMeshHeader* _rpMeshRead(RwStream* stream, const void* object, const RpMaterialList* matList) {
    return ((RpMeshHeader*(__cdecl *)(RwStream*, const void*, const RpMaterialList*))0x758EC0)(stream, object, matList);
}

RwInt32 _rpMeshSize(const RpMeshHeader* meshHeader, const void* object) {
    return ((RwInt32(__cdecl *)(const RpMeshHeader*, const void*))0x759090)(meshHeader, object);
}

void _rpMeshHeaderDestroy(RpMeshHeader* meshHeader) {
    ((void(__cdecl *)(RpMeshHeader*))0x758910)(meshHeader);
}

RpMeshHeader* _rpMeshHeaderCreate(RwUInt32 size) {
    return ((RpMeshHeader*(__cdecl *)(RwUInt32))0x758920)(size);
}

RpTriStripPolygon* RpTriStripPolygonFollowStrip(RpTriStripPolygon* curr, RpTriStripPolygon* prev) {
    return ((RpTriStripPolygon*(__cdecl *)(RpTriStripPolygon*, RpTriStripPolygon*))0x75C330)(curr, prev);
}

RwUInt32 RpTriStripDefaultCost(RpTriStripPolygon* startPolygon, RwUInt32 testFrame, void* data) {
    return ((RwUInt32(__cdecl *)(RpTriStripPolygon*, RwUInt32, void*))0x75B500)(startPolygon, testFrame, data);
}

RpTriStripMesh* RpTriStripMeshTunnel(RpTriStripMesh* mesh, void* data) {
    return ((RpTriStripMesh*(__cdecl *)(RpTriStripMesh*, void*))0x75B780)(mesh, data);
}

RpTriStripMesh* RpTriStripMeshQuick(RpTriStripMesh* mesh, void* data) {
    return ((RpTriStripMesh*(__cdecl *)(RpTriStripMesh*, void*))0x75BD80)(mesh, data);
}

RpMeshHeader* RpBuildMeshGenerateTriStrip(RpBuildMesh* buildMesh, void* data) {
    return ((RpMeshHeader*(__cdecl *)(RpBuildMesh*, void*))0x75C380)(buildMesh, data);
}

RpMeshHeader* RpBuildMeshGenerateTrivialTriStrip(RpBuildMesh* buildMesh, void* data) {
    return ((RpMeshHeader*(__cdecl *)(RpBuildMesh*, void*))0x759100)(buildMesh, data);
}

RpMeshHeader* RpBuildMeshGenerateDefaultTriStrip(RpBuildMesh* buildmesh, void* data) {
    return ((RpMeshHeader*(__cdecl *)(RpBuildMesh*, void*))0x7591B0)(buildmesh, data);
}

RpMeshHeader* RpBuildMeshGeneratePreprocessTriStrip(RpBuildMesh* buildmesh, void* data) {
    return ((RpMeshHeader*(__cdecl *)(RpBuildMesh*, void*))0x75A900)(buildmesh, data);
}

RpMeshHeader* RpBuildMeshGenerateExhaustiveTriStrip(RpBuildMesh* buildmesh, void* data) {
    return ((RpMeshHeader*(__cdecl *)(RpBuildMesh*, void*))0x75A940)(buildmesh, data);
}

RpMeshHeader* RpBuildMeshGenerateDefaultIgnoreWindingTriStrip(RpBuildMesh* buildmesh, void* data) {
    return ((RpMeshHeader*(__cdecl *)(RpBuildMesh*, void*))0x75A8E0)(buildmesh, data);
}

RpMeshHeader* RpBuildMeshGeneratePreprocessIgnoreWindingTriStrip(RpBuildMesh* buildmesh, void* data) {
    return ((RpMeshHeader*(__cdecl *)(RpBuildMesh*, void*))0x75A920)(buildmesh, data);
}

RpMeshHeader* RpBuildMeshGenerateExhaustiveIgnoreWindingTriStrip(RpBuildMesh* buildmesh, void* data) {
    return ((RpMeshHeader*(__cdecl *)(RpBuildMesh*, void*))0x75B4E0)(buildmesh, data);
}

RwBool RpMeshSetTriStripMethod(RpTriStripMeshCallBack callback, void* data) {
    return ((RwBool(__cdecl *)(RpTriStripMeshCallBack, void*))0x75D4C0)(callback, data);
}

RwBool RpMeshGetTriStripMethod(RpTriStripMeshCallBack* callback, void* data) {
    return ((RwBool(__cdecl *)(RpTriStripMeshCallBack*, void*))0x75D500)(callback, data);
}

RpMeshHeader* _rpTriListMeshGenerate(RpBuildMesh* buildMesh, void* data) {
    return ((RpMeshHeader*(__cdecl *)(RpBuildMesh*, void*))0x75D530)(buildMesh, data);
}

RpMeshHeader* _rpMeshOptimise(RpBuildMesh* buildmesh, RwUInt32 flags) {
    return ((RpMeshHeader*(__cdecl *)(RpBuildMesh*, RwUInt32))0x75D970)(buildmesh, flags);
}

RpGeometry* RpGeometryTransform(RpGeometry* geometry, const RwMatrix* matrix) {
    return ((RpGeometry*(__cdecl *)(RpGeometry*, const RwMatrix*))0x74BFE0)(geometry, matrix);
}

RpGeometry* RpGeometryCreateSpace(RwReal radius) {
    return ((RpGeometry*(__cdecl *)(RwReal))0x74C130)(radius);
}

const RpMorphTarget* RpMorphTargetCalcBoundingSphere(const RpMorphTarget* morphTarget, RwSphere* boundingSphere) {
    return ((const RpMorphTarget*(__cdecl *)(const RpMorphTarget*, RwSphere*))0x74C200)(morphTarget, boundingSphere);
}

RwInt32 RpGeometryAddMorphTargets(RpGeometry* geometry, RwInt32 mtcount) {
    return ((RwInt32(__cdecl *)(RpGeometry*, RwInt32))0x74C310)(geometry, mtcount);
}

RwInt32 RpGeometryAddMorphTarget(RpGeometry* geometry) {
    return ((RwInt32(__cdecl *)(RpGeometry*))0x74C4D0)(geometry);
}

RpGeometry* RpGeometryRemoveMorphTarget(RpGeometry* geometry, RwInt32 morphTarget) {
    return ((RpGeometry*(__cdecl *)(RpGeometry*, RwInt32))0x74C4E0)(geometry, morphTarget);
}

const RpGeometry* RpGeometryTriangleSetVertexIndices(const RpGeometry* geometry, RpTriangle* triangle, RwUInt16 vert1, RwUInt16 vert2, RwUInt16 vert3) {
    return ((const RpGeometry*(__cdecl *)(const RpGeometry*, RpTriangle*, RwUInt16, RwUInt16, RwUInt16))0x74C690)(geometry, triangle, vert1, vert2, vert3);
}

RpGeometry* RpGeometryTriangleSetMaterial(RpGeometry* geometry, RpTriangle* triangle, RpMaterial* material) {
    return ((RpGeometry*(__cdecl *)(RpGeometry*, RpTriangle*, RpMaterial*))0x74C6C0)(geometry, triangle, material);
}

const RpGeometry* RpGeometryTriangleGetVertexIndices(const RpGeometry* geometry, const RpTriangle* triangle, RwUInt16* vert1, RwUInt16* vert2, RwUInt16* vert3) {
    return ((const RpGeometry*(__cdecl *)(const RpGeometry*, const RpTriangle*, RwUInt16*, RwUInt16*, RwUInt16*))0x74C720)(geometry, triangle, vert1, vert2, vert3);
}

RpMaterial* RpGeometryTriangleGetMaterial(const RpGeometry* geometry, const RpTriangle* triangle) {
    return ((RpMaterial*(__cdecl *)(const RpGeometry*, const RpTriangle*))0x74C760)(geometry, triangle);
}

RpGeometry* RpGeometryForAllMaterials(RpGeometry* geometry, RpMaterialCallBack fpCallBack, void* pData) {
    return ((RpGeometry*(__cdecl *)(RpGeometry*, RpMaterialCallBack, void*))0x74C790)(geometry, fpCallBack, pData);
}

RpGeometry* RpGeometryLock(RpGeometry* geometry, RwInt32 lockMode) {
    return ((RpGeometry*(__cdecl *)(RpGeometry*, RwInt32))0x74C7D0)(geometry, lockMode);
}

RpGeometry* RpGeometryUnlock(RpGeometry* geometry) {
    return ((RpGeometry*(__cdecl *)(RpGeometry*))0x74C800)(geometry);
}

const RpGeometry* RpGeometryForAllMeshes(const RpGeometry* geometry, RpMeshCallBack fpCallBack, void* pData) {
    return ((const RpGeometry*(__cdecl *)(const RpGeometry*, RpMeshCallBack, void*))0x74CA60)(geometry, fpCallBack, pData);
}

RpGeometry* RpGeometryCreate(RwInt32 numVert, RwInt32 numTriangles, RwUInt32 format) {
    return ((RpGeometry*(__cdecl *)(RwInt32, RwInt32, RwUInt32))0x74CA90)(numVert, numTriangles, format);
}

RwBool RpGeometryDestroy(RpGeometry* geometry) {
    return ((RwBool(__cdecl *)(RpGeometry*))0x74CCC0)(geometry);
}

RwInt32 RpGeometryRegisterPlugin(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor constructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB) {
    return ((RwInt32(__cdecl *)(RwInt32, RwUInt32, RwPluginObjectConstructor, RwPluginObjectDestructor, RwPluginObjectCopy))0x74CD70)(size, pluginID, constructCB, destructCB, copyCB);
}

RwInt32 RpGeometryRegisterPluginStream(RwUInt32 pluginID, RwPluginDataChunkReadCallBack readCB, RwPluginDataChunkWriteCallBack writeCB, RwPluginDataChunkGetSizeCallBack getSizeCB) {
    return ((RwInt32(__cdecl *)(RwUInt32, RwPluginDataChunkReadCallBack, RwPluginDataChunkWriteCallBack, RwPluginDataChunkGetSizeCallBack))0x74CDA0)(pluginID, readCB, writeCB, getSizeCB);
}

RwInt32 RpGeometrySetStreamAlwaysCallBack(RwUInt32 pluginID, RwPluginDataChunkAlwaysCallBack alwaysCB) {
    return ((RwInt32(__cdecl *)(RwUInt32, RwPluginDataChunkAlwaysCallBack))0x74CDD0)(pluginID, alwaysCB);
}

RwInt32 RpGeometryGetPluginOffset(RwUInt32 pluginID) {
    return ((RwInt32(__cdecl *)(RwUInt32))0x74CDF0)(pluginID);
}

RwBool RpGeometryValidatePlugins(const RpGeometry* geometry) {
    return ((RwBool(__cdecl *)(const RpGeometry*))0x74CE10)(geometry);
}

RwUInt32 RpGeometryStreamGetSize(const RpGeometry* geometry) {
    return ((RwUInt32(__cdecl *)(const RpGeometry*))0x74CE20)(geometry);
}

const RpGeometry* RpGeometryStreamWrite(const RpGeometry* geometry, RwStream* stream) {
    return ((const RpGeometry*(__cdecl *)(const RpGeometry*, RwStream*))0x74CED0)(geometry, stream);
}

RpGeometry* RpGeometryStreamRead(RwStream* stream) {
    return ((RpGeometry*(__cdecl *)(RwStream*))0x74D190)(stream);
}

RpGeometryChunkInfo* _rpGeometryChunkInfoRead(RwStream* stream, RpGeometryChunkInfo* geometryChunkInfo, RwInt32* bytesRead) {
    return ((RpGeometryChunkInfo*(__cdecl *)(RwStream*, RpGeometryChunkInfo*, RwInt32*))0x74D750)(stream, geometryChunkInfo, bytesRead);
}

RpWorldSector* RpWorldSectorRender(RpWorldSector* worldSector) {
    return ((RpWorldSector*(__cdecl *)(RpWorldSector*))0x761C50)(worldSector);
}

const RpWorldSector* RpWorldSectorForAllMeshes(const RpWorldSector* sector, RpMeshCallBack fpCallBack, void* pData) {
    return ((const RpWorldSector*(__cdecl *)(const RpWorldSector*, RpMeshCallBack, void*))0x761C60)(sector, fpCallBack, pData);
}

RwInt32 RpWorldSectorRegisterPlugin(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor constructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB) {
    return ((RwInt32(__cdecl *)(RwInt32, RwUInt32, RwPluginObjectConstructor, RwPluginObjectDestructor, RwPluginObjectCopy))0x761C90)(size, pluginID, constructCB, destructCB, copyCB);
}

RwInt32 RpWorldSectorRegisterPluginStream(RwUInt32 pluginID, RwPluginDataChunkReadCallBack readCB, RwPluginDataChunkWriteCallBack writeCB, RwPluginDataChunkGetSizeCallBack getSizeCB) {
    return ((RwInt32(__cdecl *)(RwUInt32, RwPluginDataChunkReadCallBack, RwPluginDataChunkWriteCallBack, RwPluginDataChunkGetSizeCallBack))0x761CC0)(pluginID, readCB, writeCB, getSizeCB);
}

RwInt32 RpWorldSectorSetStreamAlwaysCallBack(RwUInt32 pluginID, RwPluginDataChunkAlwaysCallBack alwaysCB) {
    return ((RwInt32(__cdecl *)(RwUInt32, RwPluginDataChunkAlwaysCallBack))0x761CF0)(pluginID, alwaysCB);
}

RwInt32 RpWorldSectorSetStreamRightsCallBack(RwUInt32 pluginID, RwPluginDataChunkRightsCallBack rightsCB) {
    return ((RwInt32(__cdecl *)(RwUInt32, RwPluginDataChunkRightsCallBack))0x761D10)(pluginID, rightsCB);
}

RwInt32 RpWorldSectorGetPluginOffset(RwUInt32 pluginID) {
    return ((RwInt32(__cdecl *)(RwUInt32))0x761D30)(pluginID);
}

RwBool RpWorldSectorValidatePlugins(const RpWorldSector* sector) {
    return ((RwBool(__cdecl *)(const RpWorldSector*))0x761D50)(sector);
}

void RpLightSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc) {
    ((void(__cdecl *)(RwInt32, RwInt32))0x752250)(blockSize, numBlocksToPrealloc);
}

RpLight* RpLightCreate(RwInt32 type) {
    return ((RpLight*(__cdecl *)(RwInt32))0x752110)(type);
}

RwBool RpLightDestroy(RpLight* light) {
    return ((RwBool(__cdecl *)(RpLight*))0x7520D0)(light);
}

RpLight* RpLightSetRadius(RpLight* light, RwReal radius) {
    return ((RpLight*(__cdecl *)(RpLight*, RwReal))0x751A70)(light, radius);
}

RpLight* RpLightSetColor(RpLight* light, const RwRGBAReal* color) {
    return ((RpLight*(__cdecl *)(RpLight*, const RwRGBAReal*))0x751A90)(light, color);
}

RwReal RpLightGetConeAngle(const RpLight* light) {
    return ((RwReal(__cdecl *)(const RpLight*))0x751AE0)(light);
}

RpLight* RpLightSetConeAngle(RpLight* ight, RwReal angle) {
    return ((RpLight*(__cdecl *)(RpLight*, RwReal))0x751D20)(ight, angle);
}

RwUInt32 RpLightStreamGetSize(const RpLight* light) {
    return ((RwUInt32(__cdecl *)(const RpLight*))0x751E10)(light);
}

RpLight* RpLightStreamRead(RwStream* stream) {
    return ((RpLight*(__cdecl *)(RwStream*))0x751F00)(stream);
}

RpLightChunkInfo* _rpLightChunkInfoRead(RwStream* stream, RpLightChunkInfo* lightChunkInfo, RwInt32* bytesRead) {
    return ((RpLightChunkInfo*(__cdecl *)(RwStream*, RpLightChunkInfo*, RwInt32*))0x752060)(stream, lightChunkInfo, bytesRead);
}

RwInt32 RpLightRegisterPlugin(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor constructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB) {
    return ((RwInt32(__cdecl *)(RwInt32, RwUInt32, RwPluginObjectConstructor, RwPluginObjectDestructor, RwPluginObjectCopy))0x751D60)(size, pluginID, constructCB, destructCB, copyCB);
}

RwInt32 RpLightRegisterPluginStream(RwUInt32 pluginID, RwPluginDataChunkReadCallBack readCB, RwPluginDataChunkWriteCallBack writeCB, RwPluginDataChunkGetSizeCallBack getSizeCB) {
    return ((RwInt32(__cdecl *)(RwUInt32, RwPluginDataChunkReadCallBack, RwPluginDataChunkWriteCallBack, RwPluginDataChunkGetSizeCallBack))0x751D90)(pluginID, readCB, writeCB, getSizeCB);
}

RwInt32 RpLightSetStreamAlwaysCallBack(RwUInt32 pluginID, RwPluginDataChunkAlwaysCallBack alwaysCB) {
    return ((RwInt32(__cdecl *)(RwUInt32, RwPluginDataChunkAlwaysCallBack))0x751DC0)(pluginID, alwaysCB);
}

RwInt32 RpLightGetPluginOffset(RwUInt32 pluginID) {
    return ((RwInt32(__cdecl *)(RwUInt32))0x751DE0)(pluginID);
}

RwBool RpLightValidatePlugins(const RpLight* light) {
    return ((RwBool(__cdecl *)(const RpLight*))0x751E00)(light);
}

void RpD3D9LightSetAttenuationParams(RpLight* light, const RpD3D9AttenuationParams* params) {
    ((void(__cdecl *)(RpLight*, const RpD3D9AttenuationParams*))0x755D20)(light, params);
}

void RpD3D9LightGetAttenuationParams(const RpLight* light, RpD3D9AttenuationParams* params) {
    ((void(__cdecl *)(const RpLight*, RpD3D9AttenuationParams*))0x755D50)(light, params);
}

RwBool _rwD3D9LightsOpen(void) {
    return ((RwBool(__cdecl *)(void))0x755D80)();
}

RwBool _rwD3D9LightsGlobalEnable(RpLightFlag flags) {
    return ((RwBool(__cdecl *)(RpLightFlag))0x756070)(flags);
}

RwBool _rwD3D9LightDirectionalEnable(RpLight* light) {
    return ((RwBool(__cdecl *)(RpLight*))0x756260)(light);
}

RwBool _rwD3D9LightLocalEnable(RpLight* light) {
    return ((RwBool(__cdecl *)(RpLight*))0x756390)(light);
}

void _rwD3D9LightsEnable(RwBool enable, RwUInt32 type) {
    ((void(__cdecl *)(RwBool, RwUInt32))0x756600)(enable, type);
}

void _rwD3D9LightsClose(void) {
    ((void(__cdecl *)(void))0x755FE0)();
}

void RpAtomicSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc) {
    ((void(__cdecl *)(RwInt32, RwInt32))0x749720)(blockSize, numBlocksToPrealloc);
}

void RpClumpSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc) {
    ((void(__cdecl *)(RwInt32, RwInt32))0x749740)(blockSize, numBlocksToPrealloc);
}

RpAtomic* AtomicDefaultRenderCallBack(RpAtomic* atomic) {
    return ((RpAtomic * (__cdecl *)(RpAtomic*))0x7491C0)(atomic);
}

void _rpAtomicResyncInterpolatedSphere(RpAtomic* atomic) {
    ((void(__cdecl *)(RpAtomic*))0x7491F0)(atomic);
}

const RwSphere* RpAtomicGetWorldBoundingSphere(RpAtomic* atomic) {
    return ((const RwSphere*(__cdecl *)(RpAtomic*))0x749330)(atomic);
}

void RpClumpGtaCancelStream() {
    plugin::Call<0x72E700>();
}

RpClump* RpClumpForAllAtomics(RpClump* clump, RpAtomicCallBack callback, void* pData) {
    return ((RpClump*(__cdecl *)(RpClump*, RpAtomicCallBack, void*))0x749B70)(clump, callback, pData);
}

RpClump* RpClumpForAllLights(RpClump* clump, RpLightCallBack callback, void* pData) {
    return ((RpClump*(__cdecl *)(RpClump*, RpLightCallBack, void*))0x749C00)(clump, callback, pData);
}

RpClump* RpClumpForAllCameras(RpClump* clump, RwCameraCallBack callback, void* pData) {
    return ((RpClump*(__cdecl *)(RpClump*, RwCameraCallBack, void*))0x749BB0)(clump, callback, pData);
}

RpAtomic* RpAtomicSetFrame(RpAtomic* atomic, RwFrame* frame) {
    return ((RpAtomic*(__cdecl *)(RpAtomic*, RwFrame*))0x74BF20)(atomic, frame);
}

RpClump* RpClumpCreateSpace(const RwV3d* position, RwReal radius) {
    return ((RpClump*(__cdecl *)(const RwV3d*, RwReal))0x749970)(position, radius);
}

RpClump* RpClumpRender(RpClump* clump) {
    return ((RpClump*(__cdecl *)(RpClump*))0x749B20)(clump);
}

RpClump* RpClumpRemoveAtomic(RpClump* clump, RpAtomic* atomic) {
    return ((RpClump*(__cdecl *)(RpClump*, RpAtomic*))0x74A4C0)(clump, atomic);
}

RpClump* RpClumpAddAtomic(RpClump* clump, RpAtomic* atomic) {
    return ((RpClump*(__cdecl *)(RpClump*, RpAtomic*))0x74A490)(clump, atomic);
}

RpClump* RpClumpRemoveLight(RpClump* clump, RpLight* light) {
    return ((RpClump*(__cdecl *)(RpClump*, RpLight*))0x74A520)(clump, light);
}

RpClump* RpClumpAddLight(RpClump* clump, RpLight* light) {
    return ((RpClump*(__cdecl *)(RpClump*, RpLight*))0x74A4F0)(clump, light);
}

RpClump* RpClumpRemoveCamera(RpClump* clump, RwCamera* camera) {
    return ((RpClump*(__cdecl *)(RpClump*, RwCamera*))0x74A580)(clump, camera);
}

RpClump* RpClumpAddCamera(RpClump* clump, RwCamera* camera) {
    return ((RpClump*(__cdecl *)(RpClump*, RwCamera*))0x74A550)(clump, camera);
}

RwBool RpClumpDestroy(RpClump* clump) {
    return ((RwBool(__cdecl *)(RpClump*))0x74A310)(clump);
}

RpClump* RpClumpCreate(void) {
    return ((RpClump*(__cdecl *)(void))0x74A290)();
}

RpClump* RpClumpClone(RpClump* clump) {
    return ((RpClump*(__cdecl *)(RpClump*))0x749F70)(clump);
}

RwBool RpAtomicDestroy(RpAtomic* atomic) {
    return ((RwBool(__cdecl *)(RpAtomic*))0x749DC0)(atomic);
}

RpAtomic* RpAtomicClone(RpAtomic* atomic) {
    return ((RpAtomic*(__cdecl *)(RpAtomic*))0x749E60)(atomic);
}

RpAtomic* RpAtomicCreate(void) {
    return ((RpAtomic*(__cdecl *)(void))0x749C50)();
}

RpAtomic* RpAtomicSetGeometry(RpAtomic* atomic, RpGeometry* geometry, RwUInt32 flags) {
    return ((RpAtomic*(__cdecl *)(RpAtomic*, RpGeometry*, RwUInt32))0x749D40)(atomic, geometry, flags);
}

RpClump* RpClumpSetCallBack(RpClump* clump, RpClumpCallBack callback) {
    return ((RpClump*(__cdecl *)(RpClump*, RpClumpCallBack))0x74A240)(clump, callback);
}

RpClumpCallBack RpClumpGetCallBack(const RpClump* clump) {
    return ((RpClumpCallBack(__cdecl *)(const RpClump*))0x74A270)(clump);
}

RwInt32 RpClumpGetNumAtomics(RpClump* clump) {
    return ((RwInt32(__cdecl *)(RpClump*))0x7498E0)(clump);
}

RwInt32 RpClumpGetNumLights(RpClump* clump) {
    return ((RwInt32(__cdecl *)(RpClump*))0x749910)(clump);
}

RwInt32 RpClumpGetNumCameras(RpClump* clump) {
    return ((RwInt32(__cdecl *)(RpClump*))0x749940)(clump);
}

RpClump* RpLightGetClump(const RpLight* light) {
    return ((RpClump*(__cdecl *)(const RpLight*))0x749E40)(light);
}

RpClump* RwCameraGetClump(const RwCamera* camera) {
    return ((RpClump*(__cdecl *)(const RwCamera*))0x749E50)(camera);
}

RwUInt32 RpAtomicStreamGetSize(RpAtomic* atomic) {
    return ((RwUInt32(__cdecl *)(RpAtomic*))0x74A5B0)(atomic);
}

RpAtomic* RpAtomicStreamRead(RwStream* stream) {
    return ((RpAtomic*(__cdecl *)(RwStream*))0x74B030)(stream);
}

RpAtomic* RpAtomicStreamWrite(RpAtomic* atomic, RwStream* stream) {
    return ((RpAtomic*(__cdecl *)(RpAtomic*, RwStream*))0x74A850)(atomic, stream);
}

RwUInt32 RpClumpStreamGetSize(RpClump* clump) {
    return ((RwUInt32(__cdecl *)(RpClump*))0x74A5E0)(clump);
}

RpClump* RpClumpStreamRead(RwStream* stream) {
    return ((RpClump*(__cdecl *)(RwStream*))0x74B420)(stream);
}

RpClump* RpClumpStreamWrite(RpClump* clump, RwStream* stream) {
    return ((RpClump*(__cdecl *)(RpClump*, RwStream*))0x74AA10)(clump, stream);
}

RpClumpChunkInfo* _rpClumpChunkInfoRead(RwStream* stream, RpClumpChunkInfo* clumpChunkInfo, RwInt32* bytesRead) {
    return ((RpClumpChunkInfo*(__cdecl *)(RwStream*, RpClumpChunkInfo*, RwInt32*))0x74BD40)(stream, clumpChunkInfo, bytesRead);
}

RwInt32 RpAtomicRegisterPlugin(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor constructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB) {
    return ((RwInt32(__cdecl *)(RwInt32, RwUInt32, RwPluginObjectConstructor, RwPluginObjectDestructor, RwPluginObjectCopy))0x74BDA0)(size, pluginID, constructCB, destructCB, copyCB);
}

RwInt32 RpClumpRegisterPlugin(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor constructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB) {
    return ((RwInt32(__cdecl *)(RwInt32, RwUInt32, RwPluginObjectConstructor, RwPluginObjectDestructor, RwPluginObjectCopy))0x74BDD0)(size, pluginID, constructCB, destructCB, copyCB);
}

RwInt32 RpAtomicRegisterPluginStream(RwUInt32 pluginID, RwPluginDataChunkReadCallBack readCB, RwPluginDataChunkWriteCallBack writeCB, RwPluginDataChunkGetSizeCallBack getSizeCB) {
    return ((RwInt32(__cdecl *)(RwUInt32, RwPluginDataChunkReadCallBack, RwPluginDataChunkWriteCallBack, RwPluginDataChunkGetSizeCallBack))0x74BE00)(pluginID, readCB, writeCB, getSizeCB);
}

RwInt32 RpAtomicSetStreamAlwaysCallBack(RwUInt32 pluginID, RwPluginDataChunkAlwaysCallBack alwaysCB) {
    return ((RwInt32(__cdecl *)(RwUInt32, RwPluginDataChunkAlwaysCallBack))0x74BE30)(pluginID, alwaysCB);
}

RwInt32 RpAtomicSetStreamRightsCallBack(RwUInt32 pluginID, RwPluginDataChunkRightsCallBack rightsCB) {
    return ((RwInt32(__cdecl *)(RwUInt32, RwPluginDataChunkRightsCallBack))0x74BE50)(pluginID, rightsCB);
}

RwInt32 RpClumpRegisterPluginStream(RwUInt32 pluginID, RwPluginDataChunkReadCallBack readCB, RwPluginDataChunkWriteCallBack writeCB, RwPluginDataChunkGetSizeCallBack getSizeCB) {
    return ((RwInt32(__cdecl *)(RwUInt32, RwPluginDataChunkReadCallBack, RwPluginDataChunkWriteCallBack, RwPluginDataChunkGetSizeCallBack))0x74BE70)(pluginID, readCB, writeCB, getSizeCB);
}

RwInt32 RpClumpSetStreamAlwaysCallBack(RwUInt32 pluginID, RwPluginDataChunkAlwaysCallBack alwaysCB) {
    return ((RwInt32(__cdecl *)(RwUInt32, RwPluginDataChunkAlwaysCallBack))0x74BEA0)(pluginID, alwaysCB);
}

RwInt32 RpAtomicGetPluginOffset(RwUInt32 pluginID) {
    return ((RwInt32(__cdecl *)(RwUInt32))0x74BEC0)(pluginID);
}

RwInt32 RpClumpGetPluginOffset(RwUInt32 pluginID) {
    return ((RwInt32(__cdecl *)(RwUInt32))0x74BEE0)(pluginID);
}

RwBool RpAtomicValidatePlugins(const RpAtomic* atomic) {
    return ((RwBool(__cdecl *)(const RpAtomic*))0x74BF00)(atomic);
}

RwBool RpClumpValidatePlugins(const RpClump* clump) {
    return ((RwBool(__cdecl *)(const RpClump*))0x74BF10)(clump);
}

RwBool RpAtomicInstance(RpAtomic* atomic) {
    return ((RwBool(__cdecl *)(RpAtomic*))0x74BF40)(atomic);
}

RwBool _rpWorldFindBBox(RpWorld* world, RwBBox* boundingBox) {
    return ((RwBool(__cdecl *)(RpWorld*, RwBBox*))0x74EFA0)(world, boundingBox);
}

RpWorld* _rpWorldSetupSectorBoundingBoxes(RpWorld* world) {
    return ((RpWorld*(__cdecl *)(RpWorld*))0x74F020)(world);
}

void _rpWorldSectorDeinstanceAll(RpSector* sector) {
    ((void(__cdecl *)(RpSector*))0x74ECA0)(sector);
}

void _rpWorldSectorDestroyRecurse(RpSector* sector) {
    ((void(__cdecl *)(RpSector*))0x74ED50)(sector);
}

RwBool _rpWorldForAllGlobalLights(RpLightCallBack callBack, void* pData) {
    return ((RwBool(__cdecl *)(RpLightCallBack, void*))0x74EF10)(callBack, pData);
}

RpWorldSector* _rpWorldSectorForAllLocalLights(RpWorldSector* sector, RpLightCallBack callBack, void* pData) {
    return ((RpWorldSector*(__cdecl *)(RpWorldSector*, RpLightCallBack, void*))0x74EF60)(sector, callBack, pData);
}

RpWorldSector* _rpSectorDefaultRenderCallBack(RpWorldSector* sector) {
    return ((RpWorldSector*(__cdecl *)(RpWorldSector*))0x74EEC0)(sector);
}

RpWorld* RpWorldLock(RpWorld* world) {
    return ((RpWorld*(__cdecl *)(RpWorld*))0x74F1A0)(world);
}

RpWorld* RpWorldUnlock(RpWorld* world) {
    return ((RpWorld*(__cdecl *)(RpWorld*))0x74F210)(world);
}

void _rpWorldRegisterWorld(RpWorld* world, RwUInt32 memorySize) {
    ((void(__cdecl *)(RpWorld*, RwUInt32))0x74F0C0)(world, memorySize);
}

void _rpWorldUnregisterWorld(RpWorld* world) {
    ((void(__cdecl *)(RpWorld*))0x74F140)(world);
}

RwBool RpWorldPluginAttach(void) {
    return ((RwBool(__cdecl *)(void))0x74FDA0)();
}

RpWorld* RpWorldForAllClumps(RpWorld* world, RpClumpCallBack fpCallBack, void* pData) {
    return ((RpWorld*(__cdecl *)(RpWorld*, RpClumpCallBack, void*))0x74FB80)(world, fpCallBack, pData);
}

RpWorld* RpWorldForAllMaterials(RpWorld* world, RpMaterialCallBack fpCallBack, void* pData) {
    return ((RpWorld*(__cdecl *)(RpWorld*, RpMaterialCallBack, void*))0x74FBC0)(world, fpCallBack, pData);
}

RpWorld* RpWorldForAllLights(RpWorld* world, RpLightCallBack fpCallBack, void* pData) {
    return ((RpWorld*(__cdecl *)(RpWorld*, RpLightCallBack, void*))0x74FC00)(world, fpCallBack, pData);
}

RpWorld* RpWorldForAllWorldSectors(RpWorld* world, RpWorldSectorCallBack fpCallBack, void* pData) {
    return ((RpWorld*(__cdecl *)(RpWorld*, RpWorldSectorCallBack, void*))0x74FC70)(world, fpCallBack, pData);
}

RpWorld* RpWorldRender(RpWorld* world) {
    return ((RpWorld*(__cdecl *)(RpWorld*))0x74F570)(world);
}

RwBool RpWorldDestroy(RpWorld* world) {
    return ((RwBool(__cdecl *)(RpWorld*))0x74F610)(world);
}

RpWorld* RpWorldCreate(RwBBox* boundingBox) {
    return ((RpWorld*(__cdecl *)(RwBBox*))0x74F760)(boundingBox);
}

RpWorld* RpWorldSetSectorRenderCallBack(RpWorld* world, RpWorldSectorCallBackRender fpCallBack) {
    return ((RpWorld*(__cdecl *)(RpWorld*, RpWorldSectorCallBackRender))0x74F730)(world, fpCallBack);
}

RpWorldSectorCallBackRender RpWorldGetSectorRenderCallBack(const RpWorld* world) {
    return ((RpWorldSectorCallBackRender(__cdecl *)(const RpWorld*))0x74F750)(world);
}

RpWorld* RpWorldSectorGetWorld(const RpWorldSector* sector) {
    return ((RpWorld*(__cdecl *)(const RpWorldSector*))0x74F4E0)(sector);
}

RwInt32 RpWorldRegisterPlugin(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor constructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB) {
    return ((RwInt32(__cdecl *)(RwInt32, RwUInt32, RwPluginObjectConstructor, RwPluginObjectDestructor, RwPluginObjectCopy))0x74FCD0)(size, pluginID, constructCB, destructCB, copyCB);
}

RwInt32 RpWorldRegisterPluginStream(RwUInt32 pluginID, RwPluginDataChunkReadCallBack readCB, RwPluginDataChunkWriteCallBack writeCB, RwPluginDataChunkGetSizeCallBack getSizeCB) {
    return ((RwInt32(__cdecl *)(RwUInt32, RwPluginDataChunkReadCallBack, RwPluginDataChunkWriteCallBack, RwPluginDataChunkGetSizeCallBack))0x74FD00)(pluginID, readCB, writeCB, getSizeCB);
}

RwInt32 RpWorldSetStreamAlwaysCallBack(RwUInt32 pluginID, RwPluginDataChunkAlwaysCallBack alwaysCB) {
    return ((RwInt32(__cdecl *)(RwUInt32, RwPluginDataChunkAlwaysCallBack))0x74FD30)(pluginID, alwaysCB);
}

RwInt32 RpWorldSetStreamRightsCallBack(RwUInt32 pluginID, RwPluginDataChunkRightsCallBack rightsCB) {
    return ((RwInt32(__cdecl *)(RwUInt32, RwPluginDataChunkRightsCallBack))0x74FD50)(pluginID, rightsCB);
}

RwInt32 RpWorldGetPluginOffset(RwUInt32 pluginID) {
    return ((RwInt32(__cdecl *)(RwUInt32))0x74FD70)(pluginID);
}

RwBool RpWorldValidatePlugins(RpWorld* world) {
    return ((RwBool(__cdecl *)(RpWorld*))0x74FD90)(world);
}

void RpD3D9GeometrySetUsageFlags(RpGeometry* geometry, RpD3D9GeometryUsageFlag flags) {
    ((void(__cdecl *)(RpGeometry*, RpD3D9GeometryUsageFlag))0x7588B0)(geometry, flags);
}

RpD3D9GeometryUsageFlag RpD3D9GeometryGetUsageFlags(const RpGeometry* geometry) {
    return ((RpD3D9GeometryUsageFlag(__cdecl *)(const RpGeometry*))0x7588D0)(geometry);
}

void RpD3D9WorldSectorSetUsageFlags(RpWorldSector* sector, RpD3D9WorldSectorUsageFlag flags) {
    ((void(__cdecl *)(RpWorldSector*, RpD3D9WorldSectorUsageFlag))0x7588E0)(sector, flags);
}

RpD3D9WorldSectorUsageFlag RpD3D9WorldSectorGetUsageFlags(const RpWorldSector* sector) {
    return ((RpD3D9WorldSectorUsageFlag(__cdecl *)(const RpWorldSector*))0x758900)(sector);
}

void RxD3D9AllInOneSetInstanceCallBack(RxPipelineNode* node, RxD3D9AllInOneInstanceCallBack callback) {
    ((void(__cdecl *)(RxPipelineNode*, RxD3D9AllInOneInstanceCallBack))0x757380)(node, callback);
}

RxD3D9AllInOneInstanceCallBack RxD3D9AllInOneGetInstanceCallBack(RxPipelineNode* node) {
    return ((RxD3D9AllInOneInstanceCallBack(__cdecl *)(RxPipelineNode*))0x757390)(node);
}

void RxD3D9AllInOneSetReinstanceCallBack(RxPipelineNode* node, RxD3D9AllInOneReinstanceCallBack callback) {
    ((void(__cdecl *)(RxPipelineNode*, RxD3D9AllInOneReinstanceCallBack))0x7573A0)(node, callback);
}

RxD3D9AllInOneReinstanceCallBack RxD3D9AllInOneGetReinstanceCallBack(RxPipelineNode* node) {
    return ((RxD3D9AllInOneReinstanceCallBack(__cdecl *)(RxPipelineNode*))0x7573B0)(node);
}

void RxD3D9AllInOneSetLightingCallBack(RxPipelineNode* node, RxD3D9AllInOneLightingCallBack callback) {
    ((void(__cdecl *)(RxPipelineNode*, RxD3D9AllInOneLightingCallBack))0x7573C0)(node, callback);
}

RxD3D9AllInOneLightingCallBack RxD3D9AllInOneGetLightingCallBack(RxPipelineNode* node) {
    return ((RxD3D9AllInOneLightingCallBack(__cdecl *)(RxPipelineNode*))0x7573D0)(node);
}

void RxD3D9AllInOneSetRenderCallBack(RxPipelineNode* node, RxD3D9AllInOneRenderCallBack callback) {
    ((void(__cdecl *)(RxPipelineNode*, RxD3D9AllInOneRenderCallBack))0x7573E0)(node, callback);
}

RxD3D9AllInOneRenderCallBack RxD3D9AllInOneGetRenderCallBack(RxPipelineNode* node) {
    return ((RxD3D9AllInOneRenderCallBack(__cdecl *)(RxPipelineNode*))0x7573F0)(node);
}

void _rpD3D9AddDynamicGeometry(RpGeometry* geometry) {
    ((void(__cdecl *)(RpGeometry*))0x74E970)(geometry);
}

void _rpD3D9RemoveDynamicGeometry(RpGeometry* geometry) {
    ((void(__cdecl *)(RpGeometry*))0x74E9E0)(geometry);
}

RwUInt32 _rpD3D9VertexDeclarationGetSize(RwUInt32 type) {
    return ((RwUInt32(__cdecl *)(RwUInt32))0x7522E0)(type);
}

RwUInt32 _rpD3D9VertexDeclarationGetStride(const void* vertexDeclaration) {
    return ((RwUInt32(__cdecl *)(const void*))0x7522F0)(vertexDeclaration);
}

RwUInt32 _rpD3D9VertexDeclarationInstV3d(RwUInt32 type, RwUInt8* mem, const RwV3d* src, RwInt32 numVerts, RwUInt32 stride) {
    return ((RwUInt32(__cdecl *)(RwUInt32, RwUInt8*, const RwV3d*, RwInt32, RwUInt32))0x752AD0)(type, mem, src, numVerts, stride);
}

RwUInt32 _rpD3D9VertexDeclarationInstV3dComp(RwUInt32 type, RwUInt8* mem, const RpVertexNormal* src, RwInt32 numVerts, RwUInt32 stride) {
    return ((RwUInt32(__cdecl *)(RwUInt32, RwUInt8*, const RpVertexNormal*, RwInt32, RwUInt32))0x7531B0)(type, mem, src, numVerts, stride);
}

RwUInt32 _rpD3D9VertexDeclarationInstV3dMorph(RwUInt32 type, RwUInt8* mem, const RwV3d* src1, const RwV3d* src2, RwReal scale, RwInt32 numVerts, RwUInt32 stride) {
    return ((RwUInt32(__cdecl *)(RwUInt32, RwUInt8*, const RwV3d*, const RwV3d*, RwReal, RwInt32, RwUInt32))0x753B60)(type, mem, src1, src2, scale, numVerts, stride);
}

RwUInt32 _rpD3D9VertexDeclarationInstV2d(RwUInt32 type, RwUInt8* mem, const RwV2d* src, RwInt32 numVerts, RwUInt32 stride) {
    return ((RwUInt32(__cdecl *)(RwUInt32, RwUInt8*, const RwV2d*, RwInt32, RwUInt32))0x7544E0)(type, mem, src, numVerts, stride);
}

RwBool _rpD3D9VertexDeclarationInstColor(RwUInt8* mem, const RwRGBA* color, RwInt32 numVerts, RwUInt32 stride) {
    return ((RwBool(__cdecl *)(RwUInt8*, const RwRGBA*, RwInt32, RwUInt32))0x754AE0)(mem, color, numVerts, stride);
}

RwUInt32 _rpD3D9VertexDeclarationInstIndices(RwUInt32 type, RwUInt8* mem, const RwUInt32* indices, RwInt32 numVerts, RwUInt32 stride) {
    return ((RwUInt32(__cdecl *)(RwUInt32, RwUInt8*, const RwUInt32*, RwInt32, RwUInt32))0x754B40)(type, mem, indices, numVerts, stride);
}

RwUInt32 _rpD3D9VertexDeclarationInstIndicesRemap(RwUInt32 type, RwUInt8* mem, const RwUInt32* indices, const RwUInt8* remap, RwInt32 numVerts, RwUInt32 stride) {
    return ((RwUInt32(__cdecl *)(RwUInt32, RwUInt8*, const RwUInt32*, const RwUInt8*, RwInt32, RwUInt32))0x754C80)(type, mem, indices, remap, numVerts, stride);
}

RwUInt32 _rpD3D9VertexDeclarationInstWeights(RwUInt32 type, RwUInt8* mem, const RwV4d* src, RwInt32 numVerts, RwUInt32 stride) {
    return ((RwUInt32(__cdecl *)(RwUInt32, RwUInt8*, const RwV4d*, RwInt32, RwUInt32))0x752320)(type, mem, src, numVerts, stride);
}

RwUInt32 _rpD3D9VertexDeclarationInstTangent(RwUInt32 type, RwUInt8* mem, const RwV3d* pos, const RwTexCoords* texCoord, RxD3D9ResEntryHeader* meshHeader, RwUInt32 stride) {
    return ((RwUInt32(__cdecl *)(RwUInt32, RwUInt8*, const RwV3d*, const RwTexCoords*, RxD3D9ResEntryHeader*, RwUInt32))0x754E20)(type, mem, pos, texCoord, meshHeader, stride);
}

void _rpD3D9VertexDeclarationUnInstV3d(RwUInt32 type, RwV3d* dst, const RwUInt8* src) {
    ((void(__cdecl *)(RwUInt32, RwV3d*, const RwUInt8*))0x7551F0)(type, dst, src);
}

void _rpD3D9VertexDeclarationUnInstV2d(RwUInt32 type, RwV2d* dst, const RwUInt8* src) {
    ((void(__cdecl *)(RwUInt32, RwV2d*, const RwUInt8*))0x7555E0)(type, dst, src);
}

void _rpD3D9GetMinMaxValuesV3d(const RwV3d* src, RwInt32 numElements, RwV3d* min, RwV3d* max) {
    ((void(__cdecl *)(const RwV3d*, RwInt32, RwV3d*, RwV3d*))0x755830)(src, numElements, min, max);
}

void _rpD3D9GetMinMaxValuesV2d(const RwV2d* src, RwInt32 numElements, RwV2d* min, RwV2d* max) {
    ((void(__cdecl *)(const RwV2d*, RwInt32, RwV2d*, RwV2d*))0x7558F0)(src, numElements, min, max);
}

RwUInt32 _rpD3D9FindFormatV3d(const RwV3d* src, RwInt32 numElements) {
    return ((RwUInt32(__cdecl *)(const RwV3d*, RwInt32))0x755980)(src, numElements);
}

RwUInt32 _rpD3D9FindFormatV2d(const RwV2d* src, RwInt32 numElements) {
    return ((RwUInt32(__cdecl *)(const RwV2d*, RwInt32))0x755AA0)(src, numElements);
}

RxPipeline* RpWorldSetDefaultSectorPipeline(RxPipeline* pipeline) {
    return ((RxPipeline*(__cdecl *)(RxPipeline*))0x75E270)(pipeline);
}

RxPipeline* RpAtomicSetDefaultPipeline(RxPipeline* pipeline) {
    return ((RxPipeline*(__cdecl *)(RxPipeline*))0x75E2A0)(pipeline);
}

RxPipeline* RpMaterialSetDefaultPipeline(RxPipeline* pipeline) {
    return ((RxPipeline*(__cdecl *)(RxPipeline*))0x75E2D0)(pipeline);
}

const RpGeometry* RpGeometryIsCorrectlySorted(const RpGeometry* geometry, RwBool* result) {
    return ((const RpGeometry*(__cdecl *)(const RpGeometry*, RwBool*))0x75D9D0)(geometry, result);
}

RpGeometry* RpGeometrySortByMaterial(const RpGeometry* geometry, RpGeometrySortByMaterialCallBack callback) {
    return ((RpGeometry*(__cdecl *)(const RpGeometry*, RpGeometrySortByMaterialCallBack))0x75DAE0)(geometry, callback);
}

void RpTieSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc) {
    ((void(__cdecl *)(RwInt32, RwInt32))0x74FF60)(blockSize, numBlocksToPrealloc);
}

void RpLightTieSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc) {
    ((void(__cdecl *)(RwInt32, RwInt32))0x74FF80)(blockSize, numBlocksToPrealloc);
}

RpWorld* RpWorldRemoveCamera(RpWorld* world, RwCamera* camera) {
    return ((RpWorld*(__cdecl *)(RpWorld*, RwCamera*))0x750F50)(world, camera);
}

RpWorld* RpWorldAddCamera(RpWorld* world, RwCamera* camera) {
    return ((RpWorld*(__cdecl *)(RpWorld*, RwCamera*))0x750F20)(world, camera);
}

RpWorld* RwCameraGetWorld(const RwCamera* camera) {
    return ((RpWorld*(__cdecl *)(const RwCamera*))0x750F80)(camera);
}

RpWorld* RpWorldRemoveAtomic(RpWorld* world, RpAtomic* atomic) {
    return ((RpWorld*(__cdecl *)(RpWorld*, RpAtomic*))0x750FC0)(world, atomic);
}

RpWorld* RpWorldAddAtomic(RpWorld* world, RpAtomic* atomic) {
    return ((RpWorld*(__cdecl *)(RpWorld*, RpAtomic*))0x750F90)(world, atomic);
}

RpWorld* RpAtomicGetWorld(const RpAtomic* atomic) {
    return ((RpWorld*(__cdecl *)(const RpAtomic*))0x751050)(atomic);
}

RpWorld* RpWorldAddClump(RpWorld* world, RpClump* clump) {
    return ((RpWorld*(__cdecl *)(RpWorld*, RpClump*))0x751300)(world, clump);
}

RpWorld* RpWorldRemoveClump(RpWorld* world, RpClump* clump) {
    return ((RpWorld*(__cdecl *)(RpWorld*, RpClump*))0x751460)(world, clump);
}

RpWorld* RpClumpGetWorld(const RpClump* clump) {
    return ((RpWorld*(__cdecl *)(const RpClump*))0x7516B0)(clump);
}

RpWorld* RpWorldAddLight(RpWorld* world, RpLight* light) {
    return ((RpWorld*(__cdecl *)(RpWorld*, RpLight*))0x751910)(world, light);
}

RpWorld* RpWorldRemoveLight(RpWorld* world, RpLight* light) {
    return ((RpWorld*(__cdecl *)(RpWorld*, RpLight*))0x751960)(world, light);
}

RpWorld* RpLightGetWorld(const RpLight* light) {
    return ((RpWorld*(__cdecl *)(const RpLight*))0x7519E0)(light);
}

RwCamera* RwCameraForAllClumpsInFrustum(RwCamera* camera, void* data) {
    return ((RwCamera*(__cdecl *)(RwCamera*, void*))0x7516C0)(camera, data);
}

RwCamera* RwCameraForAllAtomicsInFrustum(RwCamera* camera, RpAtomicCallBack callback, void* data) {
    return ((RwCamera*(__cdecl *)(RwCamera*, RpAtomicCallBack, void*))0x7517F0)(camera, callback, data);
}

RwCamera* RwCameraForAllSectorsInFrustum(RwCamera* camera, RpWorldSectorCallBack callBack, void* pData) {
    return ((RwCamera*(__cdecl *)(RwCamera*, RpWorldSectorCallBack, void*))0x751660)(camera, callBack, pData);
}

RpLight* RpLightForAllWorldSectors(RpLight* light, RpWorldSectorCallBack callback, void* data) {
    return ((RpLight*(__cdecl *)(RpLight*, RpWorldSectorCallBack, void*))0x7519F0)(light, callback, data);
}

RpAtomic* RpAtomicForAllWorldSectors(RpAtomic* atomic, RpWorldSectorCallBack callback, void* data) {
    return ((RpAtomic*(__cdecl *)(RpAtomic*, RpWorldSectorCallBack, void*))0x751060)(atomic, callback, data);
}

RpWorldSector* RpWorldSectorForAllAtomics(RpWorldSector* sector, RpAtomicCallBack callback, void* data) {
    return ((RpWorldSector*(__cdecl *)(RpWorldSector*, RpAtomicCallBack, void*))0x7510A0)(sector, callback, data);
}

RpWorldSector* RpWorldSectorForAllCollisionAtomics(RpWorldSector* sector, RpAtomicCallBack callback, void* data) {
    return ((RpWorldSector*(__cdecl *)(RpWorldSector*, RpAtomicCallBack, void*))0x751140)(sector, callback, data);
}

RpWorldSector* RpWorldSectorForAllLights(RpWorldSector* sector, RpLightCallBack callback, void* data) {
    return ((RpWorldSector*(__cdecl *)(RpWorldSector*, RpLightCallBack, void*))0x7511E0)(sector, callback, data);
}

RwUInt32 RpWorldStreamGetSize(const RpWorld* world) {
    return ((RwUInt32(__cdecl *)(const RpWorld*))0x761EA0)(world);
}

RpWorld* RpWorldStreamRead(RwStream* stream) {
    return ((RpWorld*(__cdecl *)(RwStream*))0x762960)(stream);
}

const RpWorld* RpWorldStreamWrite(const RpWorld* world, RwStream* stream) {
    return ((const RpWorld*(__cdecl *)(const RpWorld*, RwStream*))0x762150)(world, stream);
}

RpWorldSectorChunkInfo* _rpWorldSectorChunkInfoRead(RwStream* stream, RpWorldSectorChunkInfo* worldSectorChunkInfo, RwInt32* bytesRead) {
    return ((RpWorldSectorChunkInfo*(__cdecl *)(RwStream*, RpWorldSectorChunkInfo*, RwInt32*))0x7635B0)(stream, worldSectorChunkInfo, bytesRead);
}

RpPlaneSectorChunkInfo* _rpPlaneSectorChunkInfoRead(RwStream* stream, RpPlaneSectorChunkInfo* planeSectorChunkInfo, RwInt32* bytesRead) {
    return ((RpPlaneSectorChunkInfo*(__cdecl *)(RwStream*, RpPlaneSectorChunkInfo*, RwInt32*))0x763620)(stream, planeSectorChunkInfo, bytesRead);
}

RpWorldChunkInfo* _rpWorldChunkInfoRead(RwStream* stream, RpWorldChunkInfo* worldChunkInfo, RwInt32* bytesRead) {
    return ((RpWorldChunkInfo*(__cdecl *)(RwStream*, RpWorldChunkInfo*, RwInt32*))0x763690)(stream, worldChunkInfo, bytesRead);
}

/* rtquat.h */

void RtQuatConvertToMatrix(const RtQuat* const qpQuat, RwMatrix* const mpMatrix) {
    RwReal              rS;
    RwV3d               rV;
    RwV3d               rW;
    RwV3d               square;
    RwV3d               cross;

    rS = ((RwReal)2) / (qpQuat->imag.x * qpQuat->imag.x
        + qpQuat->imag.y * qpQuat->imag.y
        + qpQuat->imag.z * qpQuat->imag.z
        + qpQuat->real * qpQuat->real);

    RwV3dScale(&rV, &(qpQuat)->imag, rS);
    RwV3dScale(&rW, &rV, (qpQuat)->real);

    square.x = (qpQuat)->imag.x * rV.x;
    square.y = (qpQuat)->imag.y * rV.y;
    square.z = (qpQuat)->imag.z * rV.z;

    cross.x = (qpQuat)->imag.y * rV.z;
    cross.y = (qpQuat)->imag.z * rV.x;
    cross.z = (qpQuat)->imag.x * rV.y;

    (mpMatrix)->right.x = ((RwReal)1) - (square.y + square.z);
    (mpMatrix)->right.y = cross.z + rW.z;
    (mpMatrix)->right.z = cross.y - rW.y;

    (mpMatrix)->up.x = cross.z - rW.z;
    (mpMatrix)->up.y = ((RwReal)1) - (square.z + square.x);
    (mpMatrix)->up.z = cross.x + rW.x;

    (mpMatrix)->at.x = cross.y + rW.y;
    (mpMatrix)->at.y = cross.x - rW.x;
    (mpMatrix)->at.z = ((RwReal)1) - (square.x + square.y);

    /* Set position */
    (mpMatrix)->pos.x = ((RwReal)0);
    (mpMatrix)->pos.y = ((RwReal)0);
    (mpMatrix)->pos.z = ((RwReal)0);

    /* Matrix is orthogonal */
    mpMatrix->flags = rwMATRIXTYPEORTHONORMAL & ~rwMATRIXINTERNALIDENTITY;
}

RwBool RtQuatConvertFromMatrix(RtQuat * const qpQuat, const RwMatrix * const mpMatrix) {
    return ((RwBool(__cdecl *)(RtQuat * const, const RwMatrix * const))0x7EB5C0)(qpQuat, mpMatrix);
}

RtQuat* RtQuatRotate(RtQuat* quat, const RwV3d* axis, RwReal angle, RwOpCombineType combineOp) {
    return ((RtQuat*(__cdecl *)(RtQuat*, const RwV3d*, RwReal, RwOpCombineType))0x7EB7C0)(quat, axis, angle, combineOp);
}

const RtQuat* RtQuatQueryRotate(const RtQuat* quat, RwV3d* unitAxis, RwReal* angle) {
    return ((const RtQuat*(__cdecl *)(const RtQuat*, RwV3d*, RwReal*))0x7EBA80)(quat, unitAxis, angle);
}

RwV3d* RtQuatTransformVectors(RwV3d* vectorsOut, const RwV3d* vectorsIn, const RwInt32 numPoints, const RtQuat* quat) {
    return ((RwV3d*(__cdecl *)(RwV3d*, const RwV3d*, const RwInt32, const RtQuat*))0x7EBBB0)(vectorsOut, vectorsIn, numPoints, quat);
}

RwReal RtQuatModulus(RtQuat* q) {
    return ((RwReal(__cdecl *)(RtQuat*))0x7EBD10)(q);
}

/* rtanim.h */

void RtAnimAnimationFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc) {
    ((void(__cdecl *)(RwInt32, RwInt32))0x7CCC80)(blockSize, numBlocksToPrealloc);
}

RwBool RtAnimInitialize(void) {
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

/* rphanim.h */

void RpHAnimHierarchySetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc) {
    ((void(__cdecl *)(RwInt32, RwInt32))0x7C45E0)(blockSize, numBlocksToPrealloc);
}

RpHAnimHierarchy* RpHAnimHierarchyCreate(RwInt32 numNodes, RwUInt32* nodeFlags, RwInt32* nodeIDs, RpHAnimHierarchyFlag flags, RwInt32 maxInterpKeyFrameSize) {
    return ((RpHAnimHierarchy*(__cdecl *)(RwInt32, RwUInt32*, RwInt32*, RpHAnimHierarchyFlag, RwInt32))0x7C4C30)(numNodes, nodeFlags, nodeIDs, flags, maxInterpKeyFrameSize);
}

RpHAnimHierarchy* RpHAnimHierarchyCreateFromHierarchy(RpHAnimHierarchy* hierarchy, RpHAnimHierarchyFlag flags, RwInt32 maxInterpKeyFrameSize) {
    return ((RpHAnimHierarchy*(__cdecl *)(RpHAnimHierarchy*, RpHAnimHierarchyFlag, RwInt32))0x7C4ED0)(hierarchy, flags, maxInterpKeyFrameSize);
}

RpHAnimHierarchy* RpHAnimHierarchyDestroy(RpHAnimHierarchy* hierarchy) {
    return ((RpHAnimHierarchy*(__cdecl *)(RpHAnimHierarchy*))0x7C4D30)(hierarchy);
}

RpHAnimHierarchy* RpHAnimHierarchyCreateSubHierarchy(RpHAnimHierarchy* parentHierarchy, RwInt32 startNode, RpHAnimHierarchyFlag flags, RwInt32 maxInterpKeyFrameSize) {
    return ((RpHAnimHierarchy*(__cdecl *)(RpHAnimHierarchy*, RwInt32, RpHAnimHierarchyFlag, RwInt32))0x7C4DB0)(parentHierarchy, startNode, flags, maxInterpKeyFrameSize);
}

RpHAnimHierarchy* RpHAnimHierarchyAttach(RpHAnimHierarchy* hierarchy) {
    return ((RpHAnimHierarchy*(__cdecl *)(RpHAnimHierarchy*))0x7C4F40)(hierarchy);
}

RpHAnimHierarchy* RpHAnimHierarchyDetach(RpHAnimHierarchy* hierarchy) {
    return ((RpHAnimHierarchy*(__cdecl *)(RpHAnimHierarchy*))0x7C4FF0)(hierarchy);
}

RpHAnimHierarchy* RpHAnimHierarchyAttachFrameIndex(RpHAnimHierarchy* hierarchy, RwInt32 nodeIndex) {
    return ((RpHAnimHierarchy*(__cdecl *)(RpHAnimHierarchy*, RwInt32))0x7C5020)(hierarchy, nodeIndex);
}

RpHAnimHierarchy* RpHAnimHierarchyDetachFrameIndex(RpHAnimHierarchy* hierarchy, RwInt32 nodeIndex) {
    return ((RpHAnimHierarchy*(__cdecl *)(RpHAnimHierarchy*, RwInt32))0x7C5100)(hierarchy, nodeIndex);
}

RwBool RpHAnimFrameSetHierarchy(RwFrame* frame, RpHAnimHierarchy* hierarchy) {
    return ((RwBool(__cdecl *)(RwFrame*, RpHAnimHierarchy*))0x7C5130)(frame, hierarchy);
}

RpHAnimHierarchy* RpHAnimFrameGetHierarchy(RwFrame* frame) {
    return ((RpHAnimHierarchy*(__cdecl *)(RwFrame*))0x7C5160)(frame);
}

RwMatrix* RpHAnimHierarchyGetMatrixArray(RpHAnimHierarchy* hierarchy) {
    return ((RwMatrix*(__cdecl *)(RpHAnimHierarchy*))0x7C5120)(hierarchy);
}

RwBool RpHAnimHierarchyUpdateMatrices(RpHAnimHierarchy* hierarchy) {
    return ((RwBool(__cdecl *)(RpHAnimHierarchy*))0x7C51D0)(hierarchy);
}

RwInt32 RpHAnimIDGetIndex(RpHAnimHierarchy* hierarchy, RwInt32 ID) {
    return ((RwInt32(__cdecl *)(RpHAnimHierarchy*, RwInt32))0x7C51A0)(hierarchy, ID);
}

RwBool RpHAnimPluginAttach(void) {
    return ((RwBool(__cdecl *)(void))0x7C4600)();
}

void RpHAnimKeyFrameApply(void* matrix, void* voidIFrame) {
    ((void(__cdecl *)(void*, void*))0x7C5B80)(matrix, voidIFrame);
}

void RpHAnimKeyFrameBlend(void* voidOut, void* voidIn1, void* voidIn2, RwReal alpha) {
    ((void(__cdecl *)(void*, void*, void*, RwReal))0x7C60C0)(voidOut, voidIn1, voidIn2, alpha);
}

void RpHAnimKeyFrameInterpolate(void* voidOut, void* voidIn1, void* voidIn2, RwReal time, void* customData) {
    ((void(__cdecl *)(void*, void*, void*, RwReal, void*))0x7C5CA0)(voidOut, voidIn1, voidIn2, time, customData);
}

void RpHAnimKeyFrameAdd(void* voidOut, void* voidIn1, void* voidIn2) {
    ((void(__cdecl *)(void*, void*, void*))0x7C6720)(voidOut, voidIn1, voidIn2);
}

void RpHAnimKeyFrameMulRecip(void* voidFrame, void* voidStart) {
    ((void(__cdecl *)(void*, void*))0x7C65C0)(voidFrame, voidStart);
}

RtAnimAnimation* RpHAnimKeyFrameStreamRead(RwStream* stream, RtAnimAnimation* animation) {
    return ((RtAnimAnimation*(__cdecl *)(RwStream*, RtAnimAnimation*))0x7C64C0)(stream, animation);
}

RwBool RpHAnimKeyFrameStreamWrite(const RtAnimAnimation* animation, RwStream* stream) {
    return ((RwBool(__cdecl *)(const RtAnimAnimation*, RwStream*))0x7C6540)(animation, stream);
}

RwInt32 RpHAnimKeyFrameStreamGetSize(const RtAnimAnimation* animation) {
    return ((RwInt32(__cdecl *)(const RtAnimAnimation*))0x7C65B0)(animation);
}

RwBool RpHAnimFrameSetID(RwFrame* frame, RwInt32 id) {
    return ((RwBool(__cdecl *)(RwFrame*, RwInt32))0x7C5170)(frame, id);
}

RwInt32 RpHAnimFrameGetID(RwFrame* frame) {
    return ((RwInt32(__cdecl *)(RwFrame*))0x7C5190)(frame);
}

/* rpuvanim.h */

_rpUVAnimCustomData* _rpUVAnimCustomDataStreamRead(RwStream* stream) {
    return ((_rpUVAnimCustomData*(__cdecl *)(RwStream*))0x7CBF70)(stream);
}

const _rpUVAnimCustomData* _rpUVAnimCustomDataStreamWrite(const _rpUVAnimCustomData* customData, RwStream* stream) {
    return ((const _rpUVAnimCustomData*(__cdecl *)(const _rpUVAnimCustomData*, RwStream*))0x7CBFD0)(customData, stream);
}

RwUInt32 _rpUVAnimCustomDataStreamGetSize(const _rpUVAnimCustomData* customData) {
    return ((RwUInt32(__cdecl *)(const _rpUVAnimCustomData*))0x7CC010)(customData);
}

RwBool RpUVAnimPluginAttach(void) {
    return ((RwBool(__cdecl *)(void))0x7CB940)();
}

void RpUVAnimLinearKeyFrameApply(void* matrix, void* voidIFrame) {
    ((void(__cdecl *)(void*, void*))0x7CC9F0)(matrix, voidIFrame);
}

void RpUVAnimLinearKeyFrameBlend(void* voidOut, void* voidIn1, void* voidIn2, RwReal alpha) {
    ((void(__cdecl *)(void*, void*, void*, RwReal))0x7CCAC0)(voidOut, voidIn1, voidIn2, alpha);
}

void RpUVAnimLinearKeyFrameInterpolate(void* voidOut, void* voidIn1, void* voidIn2, RwReal time, void* customData) {
    ((void(__cdecl *)(void*, void*, void*, RwReal, void*))0x7CCA40)(voidOut, voidIn1, voidIn2, time, customData);
}

void RpUVAnimLinearKeyFrameAdd(void* voidOut, void* voidIn1, void* voidIn2) {
    ((void(__cdecl *)(void*, void*, void*))0x7CCBE0)(voidOut, voidIn1, voidIn2);
}

void RpUVAnimLinearKeyFrameMulRecip(void* voidFrame, void* voidStart) {
    ((void(__cdecl *)(void*, void*))0x7CCB30)(voidFrame, voidStart);
}

void RpUVAnimParamKeyFrameApply(void* matrix, void* voidIFrame) {
    ((void(__cdecl *)(void*, void*))0x7CC560)(matrix, voidIFrame);
}

void RpUVAnimParamKeyFrameBlend(void* voidOut, void* voidIn1, void* voidIn2, RwReal alpha) {
    ((void(__cdecl *)(void*, void*, void*, RwReal))0x7CC6A0)(voidOut, voidIn1, voidIn2, alpha);
}

void RpUVAnimParamKeyFrameInterpolate(void* voidOut, void* voidIn1, void* voidIn2, RwReal time, void* customData) {
    ((void(__cdecl *)(void*, void*, void*, RwReal, void*))0x7CC600)(voidOut, voidIn1, voidIn2, time, customData);
}

void RpUVAnimParamKeyFrameAdd(void* voidOut, void* voidIn1, void* voidIn2) {
    ((void(__cdecl *)(void*, void*, void*))0x7CC750)(voidOut, voidIn1, voidIn2);
}

void RpUVAnimParamKeyFrameMulRecip(void* voidFrame, void* voidStart) {
    ((void(__cdecl *)(void*, void*))0x7CC740)(voidFrame, voidStart);
}

RtAnimAnimation* RpUVAnimKeyFrameStreamRead(RwStream* stream, RtAnimAnimation* animation) {
    return ((RtAnimAnimation*(__cdecl *)(RwStream*, RtAnimAnimation*))0x7CC870)(stream, animation);
}

RwBool RpUVAnimKeyFrameStreamWrite(const RtAnimAnimation* animation, RwStream* stream) {
    return ((RwBool(__cdecl *)(const RtAnimAnimation*, RwStream*))0x7CC920)(animation, stream);
}

RwInt32 RpUVAnimKeyFrameStreamGetSize(const RtAnimAnimation* animation) {
    return ((RwInt32(__cdecl *)(const RtAnimAnimation*))0x7CC9D0)(animation);
}

RpUVAnim* RpUVAnimCreate(const RwChar* name, RwUInt32 numNodes, RwUInt32 numFrames, RwReal duration, RwUInt32* nodeIndexToUVChannelMap, RpUVAnimKeyFrameType keyframeType) {
    return ((RpUVAnim*(__cdecl *)(const RwChar*, RwUInt32, RwUInt32, RwReal, RwUInt32*, RpUVAnimKeyFrameType))0x7CC020)(name, numNodes, numFrames, duration, nodeIndexToUVChannelMap, keyframeType);
}

RwBool RpUVAnimDestroy(RpUVAnim* anim) {
    return ((RwBool(__cdecl *)(RpUVAnim*))0x7CC0C0)(anim);
}

RpUVAnim* RpUVAnimAddRef(RpUVAnim* anim) {
    return ((RpUVAnim*(__cdecl *)(RpUVAnim*))0x7CC100)(anim);
}

const RwChar* RpUVAnimGetName(const RpUVAnim* anim) {
    return ((const RwChar*(__cdecl *)(const RpUVAnim*))0x7CC3A0)(anim);
}

RpMaterial* RpMaterialSetUVAnim(RpMaterial* material, RpUVAnim* anim, RwUInt32 slot) {
    return ((RpMaterial*(__cdecl *)(RpMaterial*, RpUVAnim*, RwUInt32))0x7CC3B0)(material, anim, slot);
}

RpUVAnimInterpolator* RpMaterialUVAnimGetInterpolator(RpMaterial* material, RwUInt32 slot) {
    return ((RpUVAnimInterpolator*(__cdecl *)(RpMaterial*, RwUInt32))0x7CC430)(material, slot);
}

RpMaterial* RpMaterialUVAnimSetInterpolator(RpMaterial* material, RpUVAnimInterpolator* interp, RwUInt32 slot) {
    return ((RpMaterial*(__cdecl *)(RpMaterial*, RpUVAnimInterpolator*, RwUInt32))0x7CC450)(material, interp, slot);
}

RpMaterial* RpMaterialUVAnimSetCurrentTime(RpMaterial* material, RwReal time) {
    return ((RpMaterial*(__cdecl *)(RpMaterial*, RwReal))0x7CC470)(material, time);
}

RpMaterial* RpMaterialUVAnimAddAnimTime(RpMaterial* material, RwReal deltaTime) {
    return ((RpMaterial*(__cdecl *)(RpMaterial*, RwReal))0x7CC4B0)(material, deltaTime);
}

RpMaterial* RpMaterialUVAnimSubAnimTime(RpMaterial* material, RwReal deltaTime) {
    return ((RpMaterial*(__cdecl *)(RpMaterial*, RwReal))0x7CC4F0)(material, deltaTime);
}

RpMaterial* RpMaterialUVAnimApplyUpdate(RpMaterial* material)
{
    return plugin::CallAndReturn<RpMaterial*, 0x7CC110, RpMaterial*>(material);
}

RwBool RpMaterialUVAnimExists(const RpMaterial* material) {
    return ((RwBool(__cdecl *)(const RpMaterial*))0x7CC530)(material);
}

/* rpskin.h */

void RpSkinSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc) {
    ((void(__cdecl *)(RwInt32, RwInt32))0x7C67F0)(blockSize, numBlocksToPrealloc);
}

RwBool RpSkinPluginAttach(void) {
    return ((RwBool(__cdecl *)(void))0x7C6820)();
}

RpAtomic* RpSkinAtomicSetHAnimHierarchy(RpAtomic* atomic, RpHAnimHierarchy* hierarchy) {
    return ((RpAtomic*(__cdecl *)(RpAtomic*, RpHAnimHierarchy*))0x7C7520)(atomic, hierarchy);
}

RpHAnimHierarchy* RpSkinAtomicGetHAnimHierarchy(const RpAtomic* atomic) {
    return ((RpHAnimHierarchy*(__cdecl *)(const RpAtomic*))0x7C7540)(atomic);
}

RpGeometry* RpSkinGeometrySetSkin(RpGeometry* geometry, RpSkin* skin) {
    return ((RpGeometry*(__cdecl *)(RpGeometry*, RpSkin*))0x7C7560)(geometry, skin);
}

RpSkin* RpSkinGeometryGetSkin(RpGeometry* geometry) {
    return ((RpSkin*(__cdecl *)(RpGeometry*))0x7C7550)(geometry);
}

RpSkin* RpSkinCreate(RwUInt32 numVertices, RwUInt32 numBones, RwMatrixWeights* vertexWeights, RwUInt32* vertexIndices, RwMatrix* inverseMatrices) {
    return ((RpSkin*(__cdecl *)(RwUInt32, RwUInt32, RwMatrixWeights*, RwUInt32*, RwMatrix*))0x7C75B0)(numVertices, numBones, vertexWeights, vertexIndices, inverseMatrices);
}

RpSkin* RpSkinDestroy(RpSkin* skin) {
    return ((RpSkin*(__cdecl *)(RpSkin*))0x7C77A0)(skin);
}

RwUInt32 RpSkinGetNumBones(RpSkin* skin) {
    return ((RwUInt32(__cdecl *)(RpSkin*))0x7C77E0)(skin);
}

const RwMatrixWeights* RpSkinGetVertexBoneWeights(RpSkin* skin) {
    return ((const RwMatrixWeights*(__cdecl *)(RpSkin*))0x7C77F0)(skin);
}

const RwUInt32* RpSkinGetVertexBoneIndices(RpSkin* skin) {
    return ((const RwUInt32*(__cdecl *)(RpSkin*))0x7C7800)(skin);
}

const RwMatrix* RpSkinGetSkinToBoneMatrices(RpSkin* skin) {
    return ((const RwMatrix*(__cdecl *)(RpSkin*))0x7C7810)(skin);
}

RwBool RpSkinIsSplit(RpSkin* skin) {
    return ((RwBool(__cdecl *)(RpSkin*))0x7C7820)(skin);
}

RpAtomic* RpSkinAtomicSetType(RpAtomic* atomic, RpSkinType type) {
    return ((RpAtomic*(__cdecl *)(RpAtomic*, RpSkinType))0x7C7830)(atomic, type);
}

RpSkinType RpSkinAtomicGetType(RpAtomic* atomic) {
    return ((RpSkinType(__cdecl *)(RpAtomic*))0x7C7880)(atomic);
}

RpGeometry* _rpSkinInitialize(RpGeometry* geometry) {
    return ((RpGeometry*(__cdecl *)(RpGeometry*))0x7C8740)(geometry);
}

RpGeometry* _rpSkinDeinitialize(RpGeometry* geometry) {
    return ((RpGeometry*(__cdecl *)(RpGeometry*))0x7C8820)(geometry);
}

RwUInt8* _rpSkinGetMeshBoneRemapIndices(RpSkin* skin) {
    return ((RwUInt8*(__cdecl *)(RpSkin*))0x7C8A40)(skin);
}

RwUInt8* _rpSkinGetMeshBoneRLECount(RpSkin* skin) {
    return ((RwUInt8*(__cdecl *)(RpSkin*))0x7C8A50)(skin);
}

RwUInt8* _rpSkinGetMeshBoneRLE(RpSkin* skin) {
    return ((RwUInt8*(__cdecl *)(RpSkin*))0x7C8A60)(skin);
}

RpSkin* _rpSkinSplitDataCreate(RpSkin* skin, RwUInt32 boneLimit, RwUInt32 numMatrices, RwUInt32 numMeshes, RwUInt32 numRLE) {
    return ((RpSkin*(__cdecl *)(RpSkin*, RwUInt32, RwUInt32, RwUInt32, RwUInt32))0x7C8A70)(skin, boneLimit, numMatrices, numMeshes, numRLE);
}

RwBool _rpSkinSplitDataDestroy(RpSkin* skin) {
    return ((RwBool(__cdecl *)(RpSkin*))0x7C8B10)(skin);
}

RxNodeDefinition* RxNodeDefinitionGetD3D9SkinAtomicAllInOne(void) {
    return ((RxNodeDefinition*(__cdecl *)(void))0x7CB2A0)();
}

/* rtdict.h */

RtDictSchema* RtDictSchemaInit(RtDictSchema* schema) {
    return ((RtDictSchema*(__cdecl *)(RtDictSchema*))0x7CED40)(schema);
}

RwBool RtDictSchemaDestruct(RtDictSchema* schema) {
    return ((RwBool(__cdecl *)(RtDictSchema*))0x7CED70)(schema);
}

RtDict* RtDictSchemaStreamReadDict(RtDictSchema* schema, RwStream* stream) {
    return ((RtDict*(__cdecl *)(RtDictSchema*, RwStream*))0x7CF240)(schema, stream);
}

RtDict* RtDictSchemaCreateDict(RtDictSchema* schema) {
    return ((RtDict*(__cdecl *)(RtDictSchema*))0x7CED90)(schema);
}

RtDictSchema* RtDictSchemaAddDict(RtDictSchema* schema, RtDict* dict) {
    return ((RtDictSchema*(__cdecl *)(RtDictSchema*, RtDict*))0x7CEE50)(schema, dict);
}

RtDictSchema* RtDictSchemaRemoveDict(RtDictSchema* schema, RtDict* dict) {
    return ((RtDictSchema*(__cdecl *)(RtDictSchema*, RtDict*))0x7CEE80)(schema, dict);
}

RwBool RtDictSchemaForAllDictionaries(RtDictSchema* schema, RtDictCallBack* callback, RtDictEntryType data) {
    return ((RwBool(__cdecl *)(RtDictSchema*, RtDictCallBack*, RtDictEntryType))0x7CF5B0)(schema, callback, data);
}

RtDict* RtDictSchemaGetCurrentDict(RtDictSchema* schema) {
    return ((RtDict*(__cdecl *)(RtDictSchema*))0x7CEEE0)(schema);
}

RtDictSchema* RtDictSchemaSetCurrentDict(RtDictSchema* schema, RtDict* dict) {
    return ((RtDictSchema*(__cdecl *)(RtDictSchema*, RtDict*))0x7CEEF0)(schema, dict);
}

RwBool RtDictDestroy(RtDict* dictionary) {
    return ((RwBool(__cdecl *)(RtDict*))0x7CF130)(dictionary);
}

RtDictEntryType RtDictAddEntry(RtDict* dictionary, RtDictEntryType entry) {
    return ((RtDictEntryType(__cdecl *)(RtDict*, RtDictEntryType))0x7CEFB0)(dictionary, entry);
}

RtDictEntryType RtDictFindNamedEntry(RtDict* dictionary, const RwChar* name) {
    return ((RtDictEntryType(__cdecl *)(RtDict*, const RwChar*))0x7CEFE0)(dictionary, name);
}

const RtDict* RtDictForAllEntries(const RtDict* dictionary, RtDictEntryCallBack* callBack, RtDictEntryType data) {
    return ((const RtDict*(__cdecl *)(const RtDict*, RtDictEntryCallBack*, RtDictEntryType))0x7CF060)(dictionary, callBack, data);
}

RtDict* RtDictRemoveEntry(RtDict* dictionary, RtDictEntryType entry) {
    return ((RtDict*(__cdecl *)(RtDict*, RtDictEntryType))0x7CF0C0)(dictionary, entry);
}

const RtDict* RtDictStreamWrite(const RtDict* dictionary, RwStream* stream) {
    return ((const RtDict*(__cdecl *)(const RtDict*, RwStream*))0x7CF490)(dictionary, stream);
}

RwUInt32 RtDictStreamGetSize(const RtDict* dictionary) {
    return ((RwUInt32(__cdecl *)(const RtDict*))0x7CF1F0)(dictionary);
}

RtDict* _rtDictSchemaInitDict(RtDictSchema* schema, RtDict* dictionary) {
    return ((RtDict*(__cdecl *)(RtDictSchema*, RtDict*))0x7CEF00)(schema, dictionary);
}

RwBool _rtDictDestruct(RtDict* dictionary) {
    return ((RwBool(__cdecl *)(RtDict*))0x7CEF60)(dictionary);
}

/* rpmatfx.h */

void RpMatFXMaterialDataSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc) {
    ((void(__cdecl *)(RwInt32, RwInt32))0x810700)(blockSize, numBlocksToPrealloc);
}

RwBool RpMatFXPluginAttach(void) {
    return ((RwBool(__cdecl *)(void))0x810AA0)();
}

RpAtomic* RpMatFXAtomicEnableEffects(RpAtomic* atomic) {
    return ((RpAtomic*(__cdecl *)(RpAtomic*))0x811C00)(atomic);
}

RwBool RpMatFXAtomicQueryEffects(RpAtomic* atomic) {
    return ((RwBool(__cdecl *)(RpAtomic*))0x811C30)(atomic);
}

RpWorldSector* RpMatFXWorldSectorEnableEffects(RpWorldSector* worldSector) {
    return ((RpWorldSector*(__cdecl *)(RpWorldSector*))0x811C40)(worldSector);
}

RwBool RpMatFXWorldSectorQueryEffects(RpWorldSector* worldSector) {
    return ((RwBool(__cdecl *)(RpWorldSector*))0x811C70)(worldSector);
}

RpMaterial* RpMatFXMaterialSetEffects(RpMaterial* material, RpMatFXMaterialFlags flags) {
    return ((RpMaterial*(__cdecl *)(RpMaterial*, RpMatFXMaterialFlags))0x811C80)(material, flags);
}

RpMaterial* RpMatFXMaterialSetupBumpMap(RpMaterial* material, RwTexture* texture, RwFrame* frame, RwReal coef) {
    return ((RpMaterial*(__cdecl *)(RpMaterial*, RwTexture*, RwFrame*, RwReal))0x811E00)(material, texture, frame, coef);
}

RpMaterial* RpMatFXMaterialSetupEnvMap(RpMaterial* material, RwTexture* texture, RwFrame* frame, RwBool useFrameBufferAlpha, RwReal coef) {
    return ((RpMaterial*(__cdecl *)(RpMaterial*, RwTexture*, RwFrame*, RwBool, RwReal))0x811ED0)(material, texture, frame, useFrameBufferAlpha, coef);
}

RpMaterial* RpMatFXMaterialSetupDualTexture(RpMaterial* material, RwTexture* texture, RwBlendFunction srcBlendMode, RwBlendFunction dstBlendMode) {
    return ((RpMaterial*(__cdecl *)(RpMaterial*, RwTexture*, RwBlendFunction, RwBlendFunction))0x812040)(material, texture, srcBlendMode, dstBlendMode);
}

RpMatFXMaterialFlags RpMatFXMaterialGetEffects(const RpMaterial* material) {
    return ((RpMatFXMaterialFlags(__cdecl *)(const RpMaterial*))0x812140)(material);
}

RpMaterial* RpMatFXMaterialSetBumpMapTexture(RpMaterial* material, RwTexture* texture) {
    return ((RpMaterial*(__cdecl *)(RpMaterial*, RwTexture*))0x812160)(material, texture);
}

RpMaterial* RpMatFXMaterialSetBumpMapFrame(RpMaterial* material, RwFrame* frame) {
    return ((RpMaterial*(__cdecl *)(RpMaterial*, RwFrame*))0x812320)(material, frame);
}

RpMaterial* RpMatFXMaterialSetBumpMapCoefficient(RpMaterial* material, RwReal coef) {
    return ((RpMaterial*(__cdecl *)(RpMaterial*, RwReal))0x812380)(material, coef);
}

RwTexture* RpMatFXMaterialGetBumpMapTexture(const RpMaterial* material) {
    return ((RwTexture*(__cdecl *)(const RpMaterial*))0x812430)(material);
}

RwTexture* RpMatFXMaterialGetBumpMapBumpedTexture(const RpMaterial* material) {
    return ((RwTexture*(__cdecl *)(const RpMaterial*))0x8123E0)(material);
}

RwFrame* RpMatFXMaterialGetBumpMapFrame(const RpMaterial* material) {
    return ((RwFrame*(__cdecl *)(const RpMaterial*))0x812480)(material);
}

RwReal RpMatFXMaterialGetBumpMapCoefficient(const RpMaterial* material) {
    return ((RwReal(__cdecl *)(const RpMaterial*))0x8124D0)(material);
}

RpMaterial* RpMatFXMaterialSetEnvMapTexture(RpMaterial* material, RwTexture* texture) {
    return ((RpMaterial*(__cdecl *)(RpMaterial*, RwTexture*))0x812530)(material, texture);
}

RpMaterial* RpMatFXMaterialSetEnvMapFrame(RpMaterial* material, RwFrame* frame) {
    return ((RpMaterial*(__cdecl *)(RpMaterial*, RwFrame*))0x8125B0)(material, frame);
}

RpMaterial* RpMatFXMaterialSetEnvMapFrameBufferAlpha(RpMaterial* material, RwBool useFrameBufferAlpha) {
    return ((RpMaterial*(__cdecl *)(RpMaterial*, RwBool))0x812610)(material, useFrameBufferAlpha);
}

RpMaterial* RpMatFXMaterialSetEnvMapCoefficient(RpMaterial* material, RwReal coef) {
    return ((RpMaterial*(__cdecl *)(RpMaterial*, RwReal))0x812680)(material, coef);
}

RwTexture* RpMatFXMaterialGetEnvMapTexture(const RpMaterial* material) {
    return ((RwTexture*(__cdecl *)(const RpMaterial*))0x8126F0)(material);
}

RwFrame* RpMatFXMaterialGetEnvMapFrame(const RpMaterial* material) {
    return ((RwFrame*(__cdecl *)(const RpMaterial*))0x812740)(material);
}

RwBool RpMatFXMaterialGetEnvMapFrameBufferAlpha(const RpMaterial* material) {
    return ((RwBool(__cdecl *)(const RpMaterial*))0x812790)(material);
}

RwReal RpMatFXMaterialGetEnvMapCoefficient(const RpMaterial* material) {
    return ((RwReal(__cdecl *)(const RpMaterial*))0x8127E0)(material);
}

RpMaterial* RpMatFXMaterialSetDualTexture(RpMaterial* material, RwTexture* texture) {
    return ((RpMaterial*(__cdecl *)(RpMaterial*, RwTexture*))0x812830)(material, texture);
}

RpMaterial* RpMatFXMaterialSetDualBlendModes(RpMaterial* material, RwBlendFunction srcBlendMode, RwBlendFunction dstBlendMode) {
    return ((RpMaterial*(__cdecl *)(RpMaterial*, RwBlendFunction, RwBlendFunction))0x8128C0)(material, srcBlendMode, dstBlendMode);
}

RwTexture* RpMatFXMaterialGetDualTexture(const RpMaterial* material) {
    return ((RwTexture*(__cdecl *)(const RpMaterial*))0x812930)(material);
}

const RpMaterial* RpMatFXMaterialGetDualBlendModes(const RpMaterial* material, RwBlendFunction* srcBlendMode, RwBlendFunction* dstBlendMode) {
    return ((const RpMaterial*(__cdecl *)(const RpMaterial*, RwBlendFunction*, RwBlendFunction*))0x812980)(material, srcBlendMode, dstBlendMode);
}

RpMaterial* RpMatFXMaterialSetUVTransformMatrices(RpMaterial* material, RwMatrix* baseTransform, RwMatrix* dualTransform) {
    return ((RpMaterial*(__cdecl *)(RpMaterial*, RwMatrix*, RwMatrix*))0x8129E0)(material, baseTransform, dualTransform);
}

const RpMaterial* RpMatFXMaterialGetUVTransformMatrices(const RpMaterial* material, RwMatrix* baseTransform, RwMatrix* dualTransform) {
    return ((const RpMaterial*(__cdecl *)(const RpMaterial*, RwMatrix*, RwMatrix*))0x812A50)(material, baseTransform, dualTransform);
}

RxPipeline* RpMatFXGetD3D9Pipeline(RpMatFXD3D9Pipeline d3d9Pipeline) {
    return ((RxPipeline*(__cdecl *)(RpMatFXD3D9Pipeline))0x8162F0)(d3d9Pipeline);
}

/* rpanisot.h */

RwInt8 RpAnisotGetMaxSupportedMaxAnisotropy(void) {
    return ((RwInt8(__cdecl *)(void))0x748F20)();
}

RwTexture* RpAnisotTextureSetMaxAnisotropy(RwTexture* tex, RwInt8 val) {
    return ((RwTexture*(__cdecl *)(RwTexture*, RwInt8))0x748F30)(tex, val);
}

RwInt8 RpAnisotTextureGetMaxAnisotropy(RwTexture* tex) {
    return ((RwInt8(__cdecl *)(RwTexture*))0x748F50)(tex);
}

RwBool RpAnisotPluginAttach(void) {
    return ((RwBool(__cdecl *)(void))0x748F70)();
}

/* rtbmp.h */

RwImage* RtBMPImageWrite(RwImage* image, const RwChar* imageName) {
    return ((RwImage*(__cdecl *)(RwImage*, const RwChar*))0x7CE990)(image, imageName);
}

RwImage* RtBMPImageRead(const RwChar* imageName) {
    return ((RwImage*(__cdecl *)(const RwChar*))0x7CDF60)(imageName);
}

/* rtpng.h */

RwImage* RtPNGImageWrite(RwImage* image, const RwChar* imageName) {
    return ((RwImage*(__cdecl *)(RwImage*, const RwChar*))0x7CF600)(image, imageName);
}

RwImage* RtPNGImageRead(const RwChar* imageName) {
    return ((RwImage*(__cdecl *)(const RwChar*))0x7CF9B0)(imageName);
}


void _rpMaterialSetDefaultSurfaceProperties(RwSurfaceProperties *surfProps) {
    ((void(__cdecl *)(RwSurfaceProperties*))0x74D870)(surfProps);
}


void _rwObjectHasFrameSetFrame(void *object, RwFrame *frame) {
    plugin::Call<0x804EF0, void *, RwFrame *>(object, frame);
}

void _rwObjectHasFrameReleaseFrame(void *object) {
    plugin::Call<0x804F40, void *>(object);
}
