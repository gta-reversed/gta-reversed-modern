/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

// TODO: Clean up RW headers

#include "rw/rwcore.h"
#include "rw/rphanim.h"
#include "rw/rpuvanim.h"
#include "rw/rpskin.h"
#include "rw/rpmatfx.h"
#include "rw/skeleton.h"
#ifdef _DX9_SDK_INSTALLED
#include "d3d9.h"
#endif

extern RwGlobals *&RwEngineInstance;

/* macro used to access global data structure (the root type is RwGlobals) */
#define RWSRCGLOBAL(variable) (RwEngineInstance->variable)

extern RsGlobalType &RsGlobal;

extern RwPluginRegistry &geometryTKList;

struct IDirect3DDevice9 *GetD3DDevice();

#ifndef D3DMATRIX_DEFINED
struct _D3DMATRIX;
#endif

_D3DMATRIX *GetD3DViewTransform();
_D3DMATRIX *GetD3DProjTransform();

/* rwplcore.h */

RwMemoryFunctions* RwOsGetMemoryInterface(void); // 0x802230
RwFreeList* _rwFreeListCreate(RwInt32 entrySize, RwInt32 entriesPerBlock, RwInt32 alignment, RwUInt32 hint, const RwChar* fileCreate, RwUInt32 lineCreate); // 0x801980
RwFreeList* RwFreeListCreateAndPreallocateSpace(RwInt32 entrySize, RwInt32 entriesPerBlock, RwInt32 alignment, RwInt32 numBlocksToPreallocate, RwFreeList* inPlaceSpaceForFreeListStruct, RwUInt32 hint); // 0x801B70
RwBool RwFreeListDestroy(RwFreeList* freelist); // 0x801B80
void RwFreeListSetFlags(RwFreeList* freeList, RwUInt32 flags); // 0x801C10
RwUInt32 RwFreeListGetFlags(RwFreeList* freeList); // 0x801C20
RwInt32 RwFreeListPurge(RwFreeList* freelist); // 0x801E00
RwFreeList* RwFreeListForAllUsed(RwFreeList* freelist, RwFreeListCallBack fpCallBack, void* pData); // 0x801E90
RwInt32 RwFreeListPurgeAllFreeLists(void); // 0x801F90
void RwStreamSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc); // 0x7EC760
RwStream* _rwStreamInitialize(RwStream* stream, RwBool rwOwned, RwStreamType type, RwStreamAccessType accessType, const void* pData); // 0x7EC810
RwStream* RwStreamOpen(RwStreamType type, RwStreamAccessType accessType, const void* pData); // 0x7ECEF0
RwBool RwStreamClose(RwStream* stream, void* pData); // 0x7ECE20
RwUInt32 RwStreamRead(RwStream* stream, void* buffer, RwUInt32 length); // 0x7EC9D0
RwStream* RwStreamWrite(RwStream* stream, const void* buffer, RwUInt32 length); // 0x7ECB30
RwStream* RwStreamSkip(RwStream* stream, RwUInt32 offset); // 0x7ECD00
RwBool _rwStringOpen(void); // 0x80A240
void _rwStringClose(void); // 0x80A440
RwBool _rwStringDestroy(RwChar* string); // 0x80A450
RwUInt32 _rwStringStreamGetSize(const RwChar* string); // 0x80A470
const RwChar* _rwStringStreamWrite(const RwChar* string, RwStream* stream); // 0x80A4A0
RwChar* _rwStringStreamFindAndRead(RwChar* string, RwStream* stream); // 0x80A510
void RwPluginRegistrySetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc); // 0x8087B0
RwBool _rwPluginRegistrySetStaticPluginsSize(RwPluginRegistry* reg, RwInt32 size); // 0x808430
RwInt32 _rwPluginRegistryAddPlugin(RwPluginRegistry* reg, RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor constructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB); // 0x8084A0
RwInt32 _rwPluginRegistryGetPluginOffset(const RwPluginRegistry* reg, RwUInt32 pluginID); // 0x808470
const RwPluginRegistry* _rwPluginRegistryInitObject(const RwPluginRegistry* reg, void* object); // 0x8086E0
const RwPluginRegistry* _rwPluginRegistryDeInitObject(const RwPluginRegistry* reg, void* object); // 0x808740
const RwPluginRegistry* _rwPluginRegistryCopyObject(const RwPluginRegistry* reg, void* dstObject, const void* srcObject); // 0x808770
RwInt32 _rwPluginRegistryAddPluginStream(RwPluginRegistry* reg, RwUInt32 pluginID, RwPluginDataChunkReadCallBack readCB, RwPluginDataChunkWriteCallBack writeCB, RwPluginDataChunkGetSizeCallBack getSizeCB); // 0x8088E0
RwInt32 _rwPluginRegistryAddPlgnStrmlwysCB(RwPluginRegistry* reg, RwUInt32 pluginID, RwPluginDataChunkAlwaysCallBack alwaysCB); // 0x808920
RwInt32 _rwPluginRegistryAddPlgnStrmRightsCB(RwPluginRegistry* reg, RwUInt32 pluginID, RwPluginDataChunkRightsCallBack rightsCB); // 0x808950
const RwPluginRegistry* _rwPluginRegistryReadDataChunks(const RwPluginRegistry* reg, RwStream* stream, void* object); // 0x808980
const RwPluginRegistry* _rwPluginRegistryWriteDataChunks(const RwPluginRegistry* reg, RwStream* stream, const void* object); // 0x808B40
const RwPluginRegistry* _rwPluginRegistrySkipDataChunks(const RwPluginRegistry* reg, RwStream* stream); // 0x808C10
RwInt32 _rwPluginRegistryGetSize(const RwPluginRegistry* reg, const void* object); // 0x808B00
const RwPluginRegistry* _rwPluginRegistryInvokeRights(const RwPluginRegistry* reg, RwUInt32 id, void* obj, RwUInt32 extraData); // 0x808AB0
RwBool RwEngineGetMatrixTolerances(RwMatrixTolerance * const tolerance); // 0x7F1780
RwBool RwEngineSetMatrixTolerances(const RwMatrixTolerance * const tolerance); // 0x7F17B0
void RwMatrixSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc); // 0x7F16A0
RwBool RwMatrixDestroy(RwMatrix* mpMat); // 0x7F2A20
RwMatrix* RwMatrixCreate(void); // 0x7F2A50
RwMatrix* RwMatrixMultiply(RwMatrix* matrixOut, const RwMatrix* MatrixIn1, const RwMatrix* matrixIn2); // 0x7F18B0
RwMatrix* RwMatrixTransform(RwMatrix* matrix, const RwMatrix* transform, RwOpCombineType combineOp); // 0x7F25A0
RwMatrix* RwMatrixOrthoNormalize(RwMatrix* matrixOut, const RwMatrix* matrixIn); // 0x7F1920
RwMatrix* RwMatrixInvert(RwMatrix* matrixOut, const RwMatrix* matrixIn); // 0x7F2070
RwMatrix* RwMatrixScale(RwMatrix* matrix, const RwV3d* scale, RwOpCombineType combineOp); // 0x7F22C0
RwMatrix* RwMatrixTranslate(RwMatrix* matrix, const RwV3d* translation, RwOpCombineType combineOp); // 0x7F2450
RwMatrix* RwMatrixRotate(RwMatrix* matrix, const RwV3d* axis, RwReal angle, RwOpCombineType combineOp); // 0x7F1FD0
RwMatrix* RwMatrixRotateOneMinusCosineSine(RwMatrix* matrix, const RwV3d* unitAxis, RwReal oneMinusCosine, RwReal sine, RwOpCombineType combineOp); // 0x7F1D00
const RwMatrix* RwMatrixQueryRotate(const RwMatrix* matrix, RwV3d* unitAxis, RwReal* angle, RwV3d* center); // 0x7F2720
RwMatrix* RwMatrixUpdate(RwMatrix* matrix); // 0x7F18A0
RwMatrix* RwMatrixOptimize(RwMatrix* matrix, const RwMatrixTolerance* tolerance); // 0x7F17E0
RwReal _rwMatrixDeterminant(const RwMatrix* matrix); // 0x7F1450
RwReal _rwMatrixNormalError(const RwMatrix* matrix); // 0x7F1500
RwReal _rwMatrixOrthogonalError(const RwMatrix* matrix); // 0x7F14A0
RwReal _rwMatrixIdentityError(const RwMatrix* matrix); // 0x7F1590
RwReal RwV3dNormalize(RwV3d* out, const RwV3d* in); // 0x7ED9B0
RwReal RwV3dLength(const RwV3d* in); // 0x7EDAC0
RwReal RwV2dLength(const RwV2d* in); // 0x7EDBF0
RwReal RwV2dNormalize(RwV2d* out, const RwV2d* in); // 0x7EDC60
RwV3d* RwV3dTransformPoint(RwV3d* pointOut, const RwV3d* pointIn, const RwMatrix* matrix); // 0x7EDD60
RwV3d* RwV3dTransformPoints(RwV3d* pointsOut, const RwV3d* pointsIn, RwInt32 numPoints, const RwMatrix* matrix); // 0x7EDD90
RwV3d* RwV3dTransformVector(RwV3d* vectorOut, const RwV3d* vectorIn, const RwMatrix* matrix); // 0x7EDDC0
RwV3d* RwV3dTransformVectors(RwV3d* vectorsOut, const RwV3d* vectorsIn, RwInt32 numPoints, const RwMatrix* matrix); // 0x7EDDF0
RwReal _rwSqrt(const RwReal num); // 0x7EDB30
RwReal _rwInvSqrt(const RwReal num); // 0x7EDB90
RwReal _rwV3dNormalize(RwV3d* out, const RwV3d* in); // 0x7ED910
RwSList* _rwSListCreate(RwInt32 size, RwUInt32 hint); // 0x809160
RwBool _rwSListDestroy(RwSList* sList); // 0x809440
void _rwSListDestroyEndEntries(RwSList* sList, RwInt32 amount); // 0x809400
void* _rwSListGetEntry(RwSList* sList, RwInt32 entry); // 0x809510
void* _rwSListGetNewEntry(RwSList* sList, RwUInt32 hint); // 0x809240
RwInt32 _rwSListGetNumEntries(const RwSList* sList); // 0x8094B0
void* _rwSListGetBegin(RwSList* sList); // 0x809530
void* _rwSListGetEnd(RwSList* sList); // 0x809540
RwBool RwIm2DRenderPrimitive(RwPrimitiveType primType, RwIm2DVertex* vertices, RwInt32 numVertices);
RwBool RwIm2DRenderIndexedPrimitive(RwPrimitiveType primType, RwIm2DVertex* vertices, RwInt32 numVertices, RwImVertexIndex* indices, RwInt32 numIndices);
RwBool RwIm2DRenderTriangle(RwIm2DVertex* vertices, RwInt32 numVertices, RwInt32 vert1, RwInt32 vert2, RwInt32 vert3);
RwBool RwIm2DRenderLine(RwIm2DVertex* vertices, RwInt32 numVertices, RwInt32 vert1, RwInt32 vert2);
RwUInt32 RwEngineGetVersion(void); // 0x7F2BA0
RwBool RwEngineInit(const RwMemoryFunctions* memFuncs, RwUInt32 initFlags, RwUInt32 resArenaSize); // 0x7F3170
RwInt32 RwEngineRegisterPlugin(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor initCB, RwPluginObjectDestructor termCB); // 0x7F2BB0
RwInt32 RwEngineGetPluginOffset(RwUInt32 pluginID); // 0x7F2BE0
RwBool RwEngineOpen(RwEngineOpenParams* initParams); // 0x7F2F70
RwBool RwEngineStart(void); // 0x7F2E70
RwBool RwEngineStop(void); // 0x7F2E20
RwBool RwEngineClose(void); // 0x7F2F00
RwBool RwEngineTerm(void); // 0x7F3130
RwInt32 RwEngineGetNumSubSystems(void); // 0x7F2C00
RwSubSystemInfo* RwEngineGetSubSystemInfo(RwSubSystemInfo* subSystemInfo, RwInt32 subSystemIndex); // 0x7F2C30
RwInt32 RwEngineGetCurrentSubSystem(void); // 0x7F2C60
RwBool RwEngineSetSubSystem(RwInt32 subSystemIndex); // 0x7F2C90
RwInt32 RwEngineGetNumVideoModes(void); // 0x7F2CC0
RwVideoMode* RwEngineGetVideoModeInfo(RwVideoMode* modeinfo, RwInt32 modeIndex); // 0x7F2CF0
RwInt32 RwEngineGetCurrentVideoMode(void); // 0x7F2D20
RwBool RwEngineSetVideoMode(RwInt32 modeIndex); // 0x7F2D50
RwInt32 RwEngineGetTextureMemorySize(void); // 0x7F2D80
RwInt32 RwEngineGetMaxTextureSize(void); // 0x7F2DB0
RwBool RwEngineSetFocus(RwBool enable); // 0x7F2DE0
RwMetrics* RwEngineGetMetrics(void); // 0x7F2E10
RwFileFunctions* RwOsGetFileInterface(void); // 0x804130
RwError* RwErrorGet(RwError* code); // 0x808880
RwError* RwErrorSet(RwError* code); // 0x808820
RwInt32 _rwerror(RwInt32 code, ...); // 0x8088D0
RwBool RwResourcesSetArenaSize(RwUInt32 size); // 0x8080C0
RwInt32 RwResourcesGetArenaSize(void); // 0x8081B0
RwInt32 RwResourcesGetArenaUsage(void); // 0x8081C0
RwBool RwResourcesEmptyArena(void); // 0x8081F0
RwResEntry* RwResourcesAllocateResEntry(void* owner, RwResEntry* ownerRef, RwInt32 size, RwResEntryDestroyNotify destroyNotify); // 0x807ED0
RwBool RwResourcesFreeResEntry(RwResEntry* entry); // 0x807DE0
void _rwResourcesPurge(void); // 0x807E50
RwBool RwStreamFindChunk(RwStream* stream, RwUInt32 type, RwUInt32* lengthOut, RwUInt32* versionOut); // 0x7ED2D0
RwStream* _rwStreamWriteVersionedChunkHeader(RwStream* stream, RwInt32 type, RwInt32 size, RwUInt32 version, RwUInt32 buildNum); // 0x7ED270
RwStream* RwStreamWriteReal(RwStream* stream, const RwReal* reals, RwUInt32 numBytes); // 0x7ED3D0
RwStream* RwStreamWriteInt32(RwStream* stream, const RwInt32* ints, RwUInt32 numBytes); // 0x7ED460
RwStream* RwStreamWriteInt16(RwStream* stream, const RwInt16* ints, RwUInt32 numBytes); // 0x7ED480
RwStream* RwStreamReadReal(RwStream* stream, RwReal* reals, RwUInt32 numBytes); // 0x7ED4F0
RwStream* RwStreamReadInt32(RwStream* stream, RwInt32* ints, RwUInt32 numBytes); // 0x7ED540
RwStream* RwStreamReadInt16(RwStream* stream, RwInt16* ints, RwUInt32 numBytes); // 0x7ED4A0
RwStream* RwStreamReadChunkHeaderInfo(RwStream* stream, RwChunkHeaderInfo* chunkHeaderInfo); // 0x7ED590

/* rwcore.h */

RxHeap* RxHeapCreate(RwUInt32 size); // 0x809F90
void RxHeapDestroy(RxHeap* heap); // 0x809F30
RwBool _rxHeapReset(RxHeap* heap); // 0x809EC0
void* RxHeapAlloc(RxHeap* heap, RwUInt32 size); // 0x809AA0
void RxHeapFree(RxHeap* heap, void* block); // 0x8098B0
void* RxHeapRealloc(RxHeap* heap, void* block, RwUInt32 newSize, RwBool allowCopy); // 0x809D10
void RxPipelineSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc); // 0x804FC0
RwBool _rxPipelineOpen(void); // 0x804FE0
RwBool _rxPipelineClose(void); // 0x804F60
RxPipeline* RxPipelineCreate(void); // 0x8057B0
void _rxPipelineDestroy(RxPipeline* Pipeline); // 0x805820
RxHeap* RxHeapGetGlobalHeap(void); // 0x8052F0
RxPipeline* RxPipelineExecute(RxPipeline* pipeline, void* data, RwBool heapReset); // 0x805710
RxPacket* RxPacketCreate(RxPipelineNode* node); // 0x805300
RxCluster* RxClusterSetStride(RxCluster* cluster, RwInt32 stride); // 0x805330
RxCluster* RxClusterSetExternalData(RxCluster* cluster, void* data, RwInt32 stride, RwInt32 numElements); // 0x805340
RxCluster* RxClusterSetData(RxCluster* cluster, void* data, RwInt32 stride, RwInt32 numElements); // 0x8053A0
void _rxPacketDestroy(RxPacket* Packet); // 0x80F070
RxCluster* RxClusterInitializeData(RxCluster* cluster, RwUInt32 numElements, RwUInt16 stride); // 0x805400
RxCluster* RxClusterResizeData(RxCluster* CurrentCluster, RwUInt32 NumElements); // 0x805470
RxCluster* RxClusterDestroyData(RxCluster* CurrentCluster); // 0x8054C0
RxCluster* RxClusterLockWrite(RxPacket* packet, RwUInt32 clusterIndex, RxPipelineNode* node); // 0x8054F0
void RxClusterUnlock(RxCluster* cluster); // 0x8055C0
RwUInt32 RxPipelineNodeSendConfigMsg(RxPipelineNode* dest, RwUInt32 msg, RwUInt32 intparam, void* ptrparam); // 0x8055D0
RxPipelineNode* RxPipelineNodeForAllConnectedOutputs(RxPipelineNode* node, RxPipeline* pipeline, RxPipelineNodeOutputCallBack callbackfn, void* callbackdata); // 0x8055F0
RxPipelineCluster* RxPipelineNodeGetPipelineCluster(RxPipelineNode* node, RwUInt32 clustersOfInterestIndex); // 0x805680
RwUInt32 RxPipelineClusterGetCreationAttributes(RxPipelineCluster* cluster); // 0x8056B0
RxPipelineCluster* RxPipelineClusterSetCreationAttributes(RxPipelineCluster* cluster, RwUInt32 creationAttributes); // 0x8056C0
RwUInt32 RxClusterGetAttributes(RxCluster* cluster); // 0x8056E0
RxCluster* RxClusterSetAttributes(RxCluster* cluster, RwUInt32 attributes); // 0x8056F0
RxNodeOutput RxPipelineNodeFindOutputByName(RxPipelineNode* node, const RwChar* outputname); // 0x805D10
RxNodeOutput RxPipelineNodeFindOutputByIndex(RxPipelineNode* node, RwUInt32 outputindex); // 0x805D70
RxNodeInput RxPipelineNodeFindInput(RxPipelineNode* node); // 0x805DA0
RxNodeDefinition* RxPipelineNodeCloneDefinition(RxPipelineNode* node, RxClusterDefinition* cluster2add); // 0x8059C0
RxPipeline* RxPipelineNodeRequestCluster(RxPipeline* pipeline, RxPipelineNode* node, RxClusterDefinition* clusterDef); // 0x805DB0
RxPipeline* RxPipelineNodeReplaceCluster(RxPipeline* pipeline, RxPipelineNode* node, RxClusterDefinition* oldClusterDef, RxClusterDefinition* newClusterDef); // 0x805E20
void* RxPipelineNodeGetInitData(RxPipelineNode* node); // 0x805F30
void* RxPipelineNodeCreateInitData(RxPipelineNode* node, RwUInt32 size); // 0x805EA0
RxPipeline* RxPipelineClone(RxPipeline* pipeline); // 0x806AC0
RxPipelineNode* RxPipelineFindNodeByName(RxPipeline* pipeline, const RwChar* name, RxPipelineNode* start, RwInt32* nodeIndex); // 0x806B30
RxPipelineNode* RxPipelineFindNodeByIndex(RxPipeline* pipeline, RwUInt32 nodeindex); // 0x806BC0
RxLockedPipe* RxPipelineLock(RxPipeline* pipeline); // 0x806990
RxPipeline* RxLockedPipeUnlock(RxLockedPipe* pipeline); // 0x805F40
RxPipeline* RxLockedPipeReplaceNode(RxLockedPipe* pipeline, RxPipelineNode* node, RxNodeDefinition* nodeDef); // 0x806F20
RxPipeline* RxLockedPipeDeleteNode(RxLockedPipe* pipeline, RxPipelineNode* node); // 0x807040
RxPipeline* RxLockedPipeSetEntryPoint(RxLockedPipe* pipeline, RxNodeInput in); // 0x807070
RxPipelineNode* RxLockedPipeGetEntryPoint(RxLockedPipe* pipeline); // 0x8070D0
RxPipeline* RxLockedPipeAddPath(RxLockedPipe* pipeline, RxNodeOutput out, RxNodeInput in); // 0x807100
RxPipeline* RxLockedPipeDeletePath(RxLockedPipe* pipeline, RxNodeOutput out, RxNodeInput in); // 0x807170
RxPipeline* RxPipelineInsertDebugNode(RxPipeline* pipeline, RxPipelineNode* before, RxPipelineNode* after, RxNodeDefinition* debugNode); // 0x8071B0
void RwD3D9VertexBufferManagerChangeDefaultSize(RwUInt32 defaultSize); // 0x7F57F0
RwBool RwD3D9CreateVertexBuffer(RwUInt32 stride, RwUInt32 size, void* vertexBuffer, RwUInt32* offset); // 0x7F5500
void RwD3D9DestroyVertexBuffer(RwUInt32 stride, RwUInt32 size, void* vertexBuffer, RwUInt32 offset); // 0x7F56A0
RwBool RwD3D9DynamicVertexBufferCreate(RwUInt32 size, void* vertexBuffer); // 0x7F5A00
void RwD3D9DynamicVertexBufferDestroy(void); // 0x7F5AE0
RwBool RwD3D9DynamicVertexBufferLock(RwUInt32 vertexSize, RwUInt32 numVertex, void* vertexBufferOut, void* vertexDataOut, RwUInt32* baseIndexOut); // 0x7F5B10
RwBool RwD3D9DynamicVertexBufferUnlock(void); // 0x7F5C90
void RwRasterSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc); // 0x7FB350
RwRaster* RwRasterCreate(RwInt32 width, RwInt32 height, RwInt32 depth, RwInt32 flags); // 0x7FB230
RwBool RwRasterDestroy(RwRaster* raster); // 0x7FB020
RwRaster* RwRasterGetOffset(RwRaster* raster, RwInt16* xOffset, RwInt16* yOffset); // 0x7FAEA0
RwInt32 RwRasterGetNumLevels(RwRaster* raster); // 0x7FB160
RwRaster* RwRasterSubRaster(RwRaster* subRaster, RwRaster* raster, RwRect* rect); // 0x7FB1D0
RwRaster* RwRasterRenderFast(RwRaster* raster, RwInt32 x, RwInt32 y); // 0x7FAF50
RwRaster* RwRasterRender(RwRaster* raster, RwInt32 x, RwInt32 y); // 0x7FAFB0
RwRaster* RwRasterRenderScaled(RwRaster* raster, RwRect* rect); // 0x7FAE80
RwRaster* RwRasterPushContext(RwRaster* raster); // 0x7FB060
RwRaster* RwRasterPopContext(void); // 0x7FB110
RwRaster* RwRasterGetCurrentContext(void); // 0x7FAE60
RwBool RwRasterClear(RwInt32 pixelValue); // 0x7FAEE0
RwBool RwRasterClearRect(RwRect* rpRect, RwInt32 pixelValue); // 0x7FAF90
RwRaster* RwRasterShowRaster(RwRaster* raster, void* dev, RwUInt32 flags); // 0x7FB1A0
RwUInt8* RwRasterLock(RwRaster* raster, RwUInt8 level, RwInt32 lockMode); // 0x7FB2D0
RwRaster* RwRasterUnlock(RwRaster* raster); // 0x7FAEC0
RwUInt8* RwRasterLockPalette(RwRaster* raster, RwInt32 lockMode); // 0x7FB0E0
RwRaster* RwRasterUnlockPalette(RwRaster* raster); // 0x7FAFF0
RwInt32 RwRasterRegisterPlugin(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor constructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB); // 0x7FB0B0
RwInt32 RwRasterGetPluginOffset(RwUInt32 pluginID); // 0x7FAE40
RxRenderStateVector* RxRenderStateVectorSetDefaultRenderStateVector(RxRenderStateVector* rsvp); // 0x80EA40
RwImage* RwImageCreate(RwInt32 width, RwInt32 height, RwInt32 depth); // 0x8026E0
RwBool RwImageDestroy(RwImage* image); // 0x802740
RwImage* RwImageAllocatePixels(RwImage* image); // 0x8027A0
RwImage* RwImageFreePixels(RwImage* image); // 0x802860
RwImage* RwImageApplyMask(RwImage* image, const RwImage* mask); // 0x802AF0
RwImage* RwImageMakeMask(RwImage* image); // 0x802A20
RwImage* RwImageReadMaskedImage(const RwChar* imageName, const RwChar* maskname); // 0x8035C0
RwImage* RwImageRead(const RwChar* imageName); // 0x802FD0
const RwChar* RwImageSetPath(const RwChar* path); // 0x802EA0
RwBool RwImageSetGamma(RwReal gammaValue); // 0x803FE0
RwImage* RwImageGammaCorrect(RwImage* image); // 0x803E30
RwBool RwPalQuantInit(RwPalQuant* pq); // 0x80C470
void RwPalQuantTerm(RwPalQuant* pq); // 0x80C520
void RwPalQuantAddImage(RwPalQuant* pq, RwImage* img, RwReal weight); // 0x80AA80
RwInt32 RwPalQuantResolvePalette(RwRGBA* palette, RwInt32 maxcols, RwPalQuant* pq); // 0x80AF60
void RwPalQuantMatchImage(RwUInt8* dstpixels, RwInt32 dststride, RwInt32 dstdepth, RwBool dstPacked, RwPalQuant* pq, RwImage* img); // 0x80BF20
RwBool RwTextureSetMipmapping(RwBool enable); // 0x7F3530
RwBool RwTextureGetMipmapping(void); // 0x7F3550
RwBool RwTextureSetAutoMipmapping(RwBool enable); // 0x7F3560
RwBool RwTextureGetAutoMipmapping(void); // 0x7F3580
RwBool RwTextureSetMipmapGenerationCallBack(RwTextureCallBackMipmapGeneration callback); // 0x7F3C70
RwTextureCallBackMipmapGeneration RwTextureGetMipmapGenerationCallBack(void); // 0x7F3C90
RwBool RwTextureSetMipmapNameCallBack(RwTextureCallBackMipmapName callback); // 0x7F3CA0
RwTextureCallBackMipmapName RwTextureGetMipmapNameCallBack(void); // 0x7F3CC0
RwBool RwTextureGenerateMipmapName(RwChar* name, RwChar* maskName, RwUInt8 mipLevel, RwInt32 format); // 0x7F3AA0
RwBool RwTextureRasterGenerateMipmaps(RwRaster* raster, RwImage* image); // 0x7F3CD0
RwBool _rwTextureSetAutoMipMapState(RwBool enable); // 0x7F3590
RwBool _rwTextureGetAutoMipMapState(void); // 0x7F35C0
RwTextureCallBackRead RwTextureGetReadCallBack(void); // 0x7F3520
RwBool RwTextureSetReadCallBack(RwTextureCallBackRead callBack); // 0x7F3500
RwTextureCallBackFind RwTextureGetFindCallBack(void); // 0x7F34F0
RwBool RwTextureSetFindCallBack(RwTextureCallBackFind callBack); // 0x7F34D0
RwTexture* RwTextureSetName(RwTexture* texture, const RwChar* name); // 0x7F38A0
RwTexture* RwTextureSetMaskName(RwTexture* texture, const RwChar* maskName); // 0x7F3910
void RwTexDictionarySetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc); // 0x7F3E80
RwTexDictionary* RwTexDictionaryCreate(void); // 0x7F3600
RwBool RwTexDictionaryDestroy(RwTexDictionary* dict); // 0x7F36A0
RwTexture* RwTextureCreate(RwRaster* raster); // 0x7F37C0
RwBool RwTextureDestroy(RwTexture* texture); // 0x7F3820
RwTexture* RwTextureSetRaster(RwTexture* texture, RwRaster* raster); // 0x7F35D0
RwTexture* RwTexDictionaryAddTexture(RwTexDictionary* dict, RwTexture* texture); // 0x7F3980
RwTexture* RwTexDictionaryRemoveTexture(RwTexture* texture); // 0x7F39C0
RwTexture* RwTexDictionaryFindNamedTexture(RwTexDictionary* dict, const RwChar* name); // 0x7F39F0
RwTexDictionary* RwTexDictionaryGetCurrent(void); // 0x7F3A90
RwTexDictionary* RwTexDictionarySetCurrent(RwTexDictionary* dict); // 0x7F3A70
const RwTexDictionary* RwTexDictionaryForAllTextures(const RwTexDictionary* dict, RwTextureCallBack fpCallBack, void* pData); // 0x7F3730
RwBool RwTexDictionaryForAllTexDictionaries(RwTexDictionaryCallBack fpCallBack, void* pData); // 0x7F3770
RwInt32 RwTextureRegisterPlugin(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor constructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB); // 0x7F3BB0
RwInt32 RwTexDictionaryRegisterPlugin(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor constructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB); // 0x7F3C10
RwInt32 RwTextureGetPluginOffset(RwUInt32 pluginID); // 0x7F3BE0
RwInt32 RwTexDictionaryGetPluginOffset(RwUInt32 pluginID); // 0x7F3C40
RwBool RwTextureValidatePlugins(const RwTexture* texture); // 0x7F3C00
RwBool RwTexDictionaryValidatePlugins(const RwTexDictionary* dict); // 0x7F3C60
rwIm3DPool* _rwIm3DGetPool(void); // 0x7EFDD0
void* RwIm3DTransform(RwIm3DVertex* pVerts, RwUInt32 numVerts, RwMatrix* ltm, RwUInt32 flags); // 0x7EF450
RwBool RwIm3DEnd(void); // 0x7EF520
RwBool RwIm3DRenderLine(RwInt32 vert1, RwInt32 vert2); // 0x7EF900
RwBool RwIm3DRenderTriangle(RwInt32 vert1, RwInt32 vert2, RwInt32 vert3); // 0x7EF810
RwBool RwIm3DRenderIndexedPrimitive(RwPrimitiveType primType, RwImVertexIndex* indices, RwInt32 numIndices); // 0x7EF550
RwBool RwIm3DRenderPrimitive(RwPrimitiveType primType); // 0x7EF6B0
RxPipeline* RwIm3DGetTransformPipeline(void); // 0x7EF9D0
RxPipeline* RwIm3DGetRenderPipeline(RwPrimitiveType primType); // 0x7EF9E0
RxPipeline* RwIm3DSetTransformPipeline(RxPipeline* pipeline); // 0x7EFAC0
RxPipeline* RwIm3DSetRenderPipeline(RxPipeline* pipeline, RwPrimitiveType primType); // 0x7EFB10
RwRaster* RwD3D9RasterStreamReadDDS(RwStream* stream); // 0x81F360
RwTexture* RwD3D9DDSTextureRead(const RwChar* name, const RwChar* maskname); // 0x820A10
RwBool RwD3D9RasterIsCompressed(const RwRaster* raster); // 0x820C90
RwBool RwD3D9DeviceSupportsDXTTexture(void); // 0x7F9C30
void* RwD3D9GetCurrentD3DDevice(void); // 0x7F9D50
RwUInt32 RwD3D9EngineGetMaxMultiSamplingLevels(void); // 0x7F84E0
void RwD3D9EngineSetMultiSamplingLevels(RwUInt32 numLevels); // 0x7F84F0
void RwD3D9EngineSetRefreshRate(RwUInt32 refreshRate); // 0x7F8580
void RwD3D9EngineSetMultiThreadSafe(RwBool enable); // 0x7F8620
void RwD3D9EngineSetSoftwareVertexProcessing(RwBool enable); // 0x7F8630
void* RwD3D9GetCurrentD3DRenderTarget(RwUInt32 index); // 0x7F9E80
RwBool RwD3D9SetRenderTarget(RwUInt32 index, RwRaster* raster); // 0x7F9E90
RwBool RwD3D9ChangeVideoMode(RwInt32 modeIndex); // 0x7F8640
RwBool RwD3D9ChangeMultiSamplingLevels(RwUInt32 numLevels); // 0x7F8A90
RwBool RwD3D9CameraAttachWindow(void* camera, void* hwnd); // 0x7F8D70
void RwD3D9SetStreamSource(RwUInt32 streamNumber, void* streamData, RwUInt32 offset, RwUInt32 stride); // 0x7FA030
void _rwD3D9RenderStateFlushCache(void); // 0x7FC200
void _rwD3D9DrawIndexedPrimitiveUP(RwUInt32 primitiveType, RwUInt32 minIndex, RwUInt32 numVertices, RwUInt32 primitiveCount, const void* indexData, const void* vertexStreamZeroData, RwUInt32 VertexStreamZeroStride); // 0x7FA1F0
void _rwD3D9DrawPrimitiveUP(RwUInt32 primitiveType, RwUInt32 primitiveCount, const void* vertexStreamZeroData, RwUInt32 VertexStreamZeroStride); // 0x7FA290
void _rwD3D9DrawIndexedPrimitive(RwUInt32 primitiveType, RwInt32 baseVertexIndex, RwUInt32 minIndex, RwUInt32 numVertices, RwUInt32 startIndex, RwUInt32 primitiveCount); // 0x7FA320
void _rwD3D9SetVertexShaderConstant(RwUInt32 registerAddress, const void* constantData, RwUInt32 constantCount); // 0x7FACA0
void _rwD3D9SetPixelShaderConstant(RwUInt32 registerAddress, const void* constantData, RwUInt32 constantCount); // 0x7FAD00
void _rwD3D9SetFVF(RwUInt32 fvf); // 0x7F9F30
void _rwD3D9SetVertexShader(void *shader); // 0x7F9FB0
void _rwD3D9SetPixelShader(void *shader); // 0x7F9FF0
void RwD3D9SetRenderState(RwUInt32 state, RwUInt32 value); // 0x7FC2D0
void RwD3D9GetRenderState(RwUInt32 state, void* value); // 0x7FC320
void RwD3D9SetTextureStageState(RwUInt32 stage, RwUInt32 type, RwUInt32 value); // 0x7FC340
void RwD3D9GetTextureStageState(RwUInt32 stage, RwUInt32 type, void* value); // 0x7FC3A0
void RwD3D9SetSamplerState(RwUInt32 stage, RwUInt32 type, RwUInt32 value); // 0x7FC3C0
void RwD3D9GetSamplerState(RwUInt32 stage, RwUInt32 type, void* value); // 0x7FC400
void RwD3D9SetStencilClear(RwUInt32 stencilClear); // 0x7F9D30
RwUInt32 RwD3D9GetStencilClear(void); // 0x7F9D40
RwBool RwD3D9SetTexture(RwTexture* texture, RwUInt32 stage); // 0x7FDE70
RwBool RwD3D9SetTransform(RwUInt32 state, const void* matrix); // 0x7FA390
void RwD3D9GetTransform(RwUInt32 state, void* matrix); // 0x7FA4F0
RwBool RwD3D9SetMaterial(const void* material); // 0x7FC430
RwBool RwD3D9SetClipPlane(RwUInt32 index, const RwV4d* plane); // 0x7FC4A0
RwBool RwD3D9SetTransformWorld(const RwMatrix* matrix); // 0x7FA520
RwBool RwD3D9SetSurfaceProperties(const RwSurfaceProperties* surfaceProps, const RwRGBA* color, RwUInt32 flags); // 0x7FC4D0
RwBool RwD3D9SetLight(RwInt32 index, const void* light); // 0x7FA660
void RwD3D9GetLight(RwInt32 index, void* light); // 0x7FA820
RwBool RwD3D9EnableLight(RwInt32 index, RwBool enable); // 0x7FA860
RwBool RwD3D9IndexBufferCreate(RwUInt32 numIndices, void* indexBuffer); // 0x4C9970
RwBool RwD3D9CreateVertexDeclaration(const void* elements, void* vertexdeclaration); // 0x7FAA30
void RwD3D9DeleteVertexDeclaration(void); // 0x7FAC10
void RwD3D9DeleteVertexShader(void); // 0x7FAC90
RwBool RwD3D9CreatePixelShader(const RwUInt32* function, void* shader); // 0x7FACC0
void RwD3D9DeletePixelShader(void); // 0x7FACF0
const void* RwD3D9GetCaps(void); // 0x7FAD20
RwBool RwD3D9CameraIsSphereFullyInsideFrustum(const void* camera, const void* sphere); // 0x7FAD30
RwBool RwD3D9CameraIsBBoxFullyInsideFrustum(const void* camera, const void* boundingBox); // 0x7FAD90
void _rwD3D9RasterConvertToNonPalettized(RwRaster* raster); // 0x4CD250
RwBool _rwDeviceRegisterPlugin(void); // 0x7F5F60
void _rwD3D9DeviceSetRestoreCallback(rwD3D9DeviceRestoreCallBack callback); // 0x7FAE20
rwD3D9DeviceRestoreCallBack _rwD3D9DeviceGetRestoreCallback(void); // 0x7FAE30
RwImage* RwImageResample(RwImage* dstImage, const RwImage* srcImage); // 0x80C600
RwImage* RwImageCreateResample(const RwImage* srcImage, RwInt32 width, RwInt32 height); // 0x80CD10
RwImage* RwImageSetFromRaster(RwImage* image, RwRaster* raster); // 0x804250
RwRaster* RwRasterSetFromImage(RwRaster* raster, RwImage* image); // 0x804290
RwRaster* RwRasterRead(const RwChar* filename); // 0x8043F0
RwRaster* RwRasterReadMaskedRaster(const RwChar* filename, const RwChar* maskname); // 0x8044E0
RwImage* RwImageFindRasterFormat(RwImage* ipImage, RwInt32 nRasterType, RwInt32* npWidth, RwInt32* npHeight, RwInt32* npDepth, RwInt32* npFormat); // 0x8042C0
RwFrame* RwFrameForAllObjects(RwFrame* frame, RwObjectCallBack callBack, void* data); // 0x7F1200
RwFrame* RwFrameTranslate(RwFrame* frame, const RwV3d* v, RwOpCombineType combine); // 0x7F0E30
RwFrame* RwFrameRotate(RwFrame* frame, const RwV3d* axis, RwReal angle, RwOpCombineType combine); // 0x7F1010
RwFrame* RwFrameScale(RwFrame* frame, const RwV3d* v, RwOpCombineType combine); // 0x7F0ED0
RwFrame* RwFrameTransform(RwFrame* frame, const RwMatrix* m, RwOpCombineType combine); // 0x7F0F70
RwFrame* RwFrameOrthoNormalize(RwFrame* frame); // 0x7F1170
RwFrame* RwFrameSetIdentity(RwFrame* frame); // 0x7F10B0
RwFrame* RwFrameCloneHierarchy(RwFrame* root); // 0x7F0250
RwBool RwFrameDestroyHierarchy(RwFrame* frame); // 0x7F08A0
RwFrame* RwFrameForAllChildren(RwFrame* frame, RwFrameCallBack callBack, void* data); // 0x7F0DC0
RwFrame* RwFrameRemoveChild(RwFrame* child); // 0x7F0CD0
RwFrame* RwFrameAddChild(RwFrame* parent, RwFrame* child); // 0x7F0B00
RwFrame* RwFrameAddChildNoUpdate(RwFrame* parent, RwFrame* child); // 0x7F09C0
RwFrame* RwFrameGetRoot(const RwFrame* frame); // 0x7F09B0
RwMatrix* RwFrameGetLTM(RwFrame* frame); // 0x7F0990
RwFrame* RwFrameUpdateObjects(RwFrame* frame); // 0x7F0910
void RwFrameSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc); // 0x7EFED0
RwFrame* RwFrameCreate(void); // 0x7F0410
RwBool RwFrameDestroy(RwFrame* frame); // 0x7F05A0
void _rwFrameInit(RwFrame* frame); // 0x7F0450
void _rwFrameDeInit(RwFrame* frame); // 0x7F06F0
RwBool RwFrameDirty(const RwFrame* frame); // 0x7F0340
RwInt32 RwFrameCount(RwFrame* frame); // 0x7F0E00
RwInt32 RwFrameRegisterPlugin(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor constructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB); // 0x7F1260
RwInt32 RwFrameGetPluginOffset(RwUInt32 pluginID); // 0x7F1290
RwBool RwFrameValidatePlugins(const RwFrame* frame); // 0x7F12B0
RwFrame* _rwFrameCloneAndLinkClones(RwFrame* root); // 0x7EFFB0
RwFrame* _rwFramePurgeClone(RwFrame* root); // 0x7F01A0
void _rwObjectHasFrameReleaseFrame(void); // 0x804F40
RwBool _rwFrameSyncDirty(void); // 0x809550
void _rwFrameSyncHierarchyLTM(RwFrame* frame); // 0x8097D0
RwInt32 RwTextureRegisterPluginStream(RwUInt32 pluginID, RwPluginDataChunkReadCallBack readCB, RwPluginDataChunkWriteCallBack writeCB, RwPluginDataChunkGetSizeCallBack getSizeCB); // 0x804550
RwInt32 RwTextureSetStreamAlwaysCallBack(RwUInt32 pluginID, RwPluginDataChunkAlwaysCallBack alwaysCB); // 0x804580
RwUInt32 RwTextureStreamGetSize(const RwTexture* texture); // 0x8045A0
RwTexture* RwTextureStreamRead(RwStream* stream); // 0x8046E0
const RwTexture* RwTextureStreamWrite(const RwTexture* texture, RwStream* stream); // 0x8045E0
RwInt32 RwTexDictionaryRegisterPluginStream(RwUInt32 pluginID, RwPluginDataChunkReadCallBack readCB, RwPluginDataChunkWriteCallBack writeCB, RwPluginDataChunkGetSizeCallBack getSizeCB); // 0x8048E0
RwInt32 RwTexDictionarySetStreamAlwaysCallBack(RwUInt32 pluginID, RwPluginDataChunkAlwaysCallBack alwaysCB); // 0x804910
RwUInt32 RwTexDictionaryStreamGetSize(const RwTexDictionary* texDict); // 0x804930
RwTexDictionary* RwTexDictionaryStreamRead(RwStream* stream); // 0x804C30
const RwTexDictionary* RwTexDictionaryStreamWrite(const RwTexDictionary* texDict, RwStream* stream); // 0x8049F0
RwTextureChunkInfo* _rwTextureChunkInfoRead(RwStream* stream, RwTextureChunkInfo* textureChunkInfo, RwInt32* bytesRead); // 0x804E60
void RwFrameListSetAutoUpdate(RwBool flag); // 0x807570
RwInt32 RwFrameRegisterPluginStream(RwUInt32 pluginID, RwPluginDataChunkReadCallBack readCB, RwPluginDataChunkWriteCallBack writeCB, RwPluginDataChunkGetSizeCallBack getSizeCB); // 0x807580
RwInt32 RwFrameSetStreamAlwaysCallBack(RwUInt32 pluginID, RwPluginDataChunkAlwaysCallBack alwaysCB); // 0x8075B0
rwFrameList* _rwFrameListInitialize(rwFrameList* frameList, RwFrame* frame); // 0x8075D0
RwBool _rwFrameListFindFrame(const rwFrameList* frameList, const RwFrame* frame, RwInt32* npIndex); // 0x8076E0
rwFrameList* _rwFrameListDeinitialize(rwFrameList* frameList); // 0x807720
RwUInt32 _rwFrameListStreamGetSize(const rwFrameList* frameList); // 0x807750
rwFrameList* _rwFrameListStreamRead(RwStream* stream, rwFrameList* fl); // 0x807970
const rwFrameList* _rwFrameListStreamWrite(const rwFrameList* frameList, RwStream* stream); // 0x8077A0
RwBBox* RwBBoxCalculate(RwBBox* boundBox, const RwV3d* verts, RwInt32 numVerts); // 0x808F60
RwBBox* RwBBoxInitialize(RwBBox* boundBox, const RwV3d* vertex); // 0x809020
RwBBox* RwBBoxAddPoint(RwBBox* boundBox, const RwV3d* vertex); // 0x809060
RwBool RwBBoxContainsPoint(const RwBBox* boundBox, const RwV3d* vertex); // 0x8090E0
RwCamera* RwCameraBeginUpdate(RwCamera* camera); // 0x7EE190
RwCamera* RwCameraEndUpdate(RwCamera* camera); // 0x7EE180
RwCamera* RwCameraClear(RwCamera* camera, RwRGBA* colour, RwInt32 clearMode); // 0x7EE340
RwCamera* RwCameraShowRaster(RwCamera* camera, void* pDev, RwUInt32 flags); // 0x7EE370
void RwCameraSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc); // 0x7EE0F0
RwBool RwCameraDestroy(RwCamera* camera); // 0x7EE4B0
RwCamera* RwCameraCreate(void); // 0x7EE4F0
RwCamera* RwCameraClone(RwCamera* camera); // 0x7EF3B0
RwCamera* RwCameraSetViewOffset(RwCamera* camera, const RwV2d* offset); // 0x7EE1A0
RwCamera* RwCameraSetViewWindow(RwCamera* camera, const RwV2d* viewWindow); // 0x7EE410
RwCamera* RwCameraSetProjection(RwCamera* camera, RwCameraProjection projection); // 0x7EE3A0
RwCamera* RwCameraSetNearClipPlane(RwCamera* camera, RwReal nearClip); // 0x7EE1D0
RwCamera* RwCameraSetFarClipPlane(RwCamera* camera, RwReal farClip); // 0x7EE2A0
RwInt32 RwCameraRegisterPlugin(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor constructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB); // 0x7EE450
RwInt32 RwCameraGetPluginOffset(RwUInt32 pluginID); // 0x7EE480
RwBool RwCameraValidatePlugins(const RwCamera* camera); // 0x7EE4A0
RwFrustumTestResult RwCameraFrustumTestSphere(const RwCamera* camera, const RwSphere* sphere); // 0x7EE2D0
RwInt32 RwCameraRegisterPluginStream(RwUInt32 pluginID, RwPluginDataChunkReadCallBack readCB, RwPluginDataChunkWriteCallBack writeCB, RwPluginDataChunkGetSizeCallBack getSizeCB); // 0x808C90
RwInt32 RwCameraSetStreamAlwaysCallBack(RwUInt32 pluginID, RwPluginDataChunkAlwaysCallBack alwaysCB); // 0x808CC0
RwUInt32 RwCameraStreamGetSize(const RwCamera* camera); // 0x808CE0
RwCamera* RwCameraStreamRead(RwStream* stream); // 0x808DE0
const RwCamera* RwCameraStreamWrite(const RwCamera* camera, RwStream* stream); // 0x808D00
RwCameraChunkInfo* RwCameraChunkInfoRead(RwStream* stream, RwCameraChunkInfo* cameraChunkInfo, RwInt32* bytesRead); // 0x808EF0

/* rpworld.h */

void _rwD3D9VSSetActiveWorldMatrix(const RwMatrix* worldMatrix); // 0x764650
void _rwD3D9VSGetComposedTransformMatrix(void); // 0x7646E0
void _rwD3D9VSGetWorldViewTransposedMatrix(void); // 0x764730
void _rwD3D9VSGetWorldViewMatrix(void); // 0x764760
void _rwD3D9VSGetInverseWorldMatrix(void); // 0x7647B0
void _rwD3D9VSGetWorldMultiplyMatrix(RwMatrix* worldMultiplyMatrix, const RwMatrix* matrix); // 0x764920
void _rwD3D9VSGetWorldMultiplyTransposeMatrix(void* worldMultiplyMatrix, const RwMatrix* matrix); // 0x764960
void _rwD3D9VSGetWorldViewMultiplyTransposeMatrix(void* worldViewMultiplyMatrix, const RwMatrix* matrix); // 0x7649D0
void _rwD3D9VSGetWorldNormalizedMultiplyTransposeMatrix(void* worldMultiplyMatrix, const RwMatrix* matrix); // 0x764A70
void _rwD3D9VSGetWorldNormalizedViewMultiplyTransposeMatrix(void* worldViewMultiplyMatrix, const RwMatrix* matrix); // 0x764B50
void _rwD3D9VSGetWorldNormalizedTransposeMatrix(void); // 0x764C60
void _rwD3D9VSGetProjectionTransposedMatrix(void); // 0x764D20
void _rwD3D9VSGetNormalInLocalSpace(const RwV3d* normalWorldSpace, RwV3d* normalLocalSpace); // 0x764D30
void _rwD3D9VSGetPointInLocalSpace(const RwV3d* pointWorldSpace, RwV3d* pointLocalSpace); // 0x764E70
void _rwD3D9VSGetRadiusInLocalSpace(RwReal radiusWorldSpace, RwReal* radiusLocalSpace); // 0x764F60
void _rpD3D9VertexShaderCachePurge(void); // 0x75EE60
void* _rpD3D9GetVertexShader(const _rpD3D9VertexShaderDescriptor* desc, _rpD3D9VertexShaderDispatchDescriptor* dispatch); // 0x75EED0
RwUInt32 _rpD3D9GetNumConstantsUsed(const _rpD3D9VertexShaderDescriptor* desc); // 0x75EDD0
void _rxD3D9VertexShaderDefaultBeginCallBack(void* object, RwUInt32 type, _rpD3D9VertexShaderDescriptor* desc); // 0x760DF0
RwV4d* _rxD3D9VertexShaderDefaultLightingCallBack(void* object, RwUInt32 type, RwV4d* shaderConstantPtr, _rpD3D9VertexShaderDescriptor* desc); // 0x761170
void* _rxD3D9VertexShaderDefaultGetMaterialShaderCallBack(const RpMaterial* material, _rpD3D9VertexShaderDescriptor* desc, _rpD3D9VertexShaderDispatchDescriptor* dispatch); // 0x761010
void _rxD3D9VertexShaderDefaultMeshRenderCallBack(RxD3D9ResEntryHeader* resEntryHeader, RxD3D9InstanceData* instancedMesh, const _rpD3D9VertexShaderDescriptor* desc, const _rpD3D9VertexShaderDispatchDescriptor* dispatch); // 0x761030
void _rxD3D9VertexShaderDefaultEndCallBack(void* object, RwUInt32 type, _rpD3D9VertexShaderDescriptor* desc); // 0x761000
void _rpD3D9VertexShaderUpdateLightsColors(RwV4d* shaderConstantPtr, const _rpD3D9VertexShaderDescriptor* desc, RwReal ambientCoef, RwReal diffuseCoef); // 0x761720
void _rpD3D9VertexShaderUpdateMaterialColor(const RwRGBA* color, const _rpD3D9VertexShaderDispatchDescriptor* dispatch); // 0x761820
void _rpD3D9VertexShaderUpdateFogData(const _rpD3D9VertexShaderDescriptor* desc, const _rpD3D9VertexShaderDispatchDescriptor* dispatch); // 0x7618B0
void _rpD3D9VertexShaderUpdateMorphingCoef(RwReal morphingCoef, const _rpD3D9VertexShaderDispatchDescriptor* dispatch); // 0x761950
void _rpD3DVertexShaderSetUVAnimMatrix(RwMatrix* matrix, const _rpD3D9VertexShaderDispatchDescriptor* dispatch); // 0x7619A0
void _rpD3D9VertexShaderSetEnvMatrix(RwFrame* frame, const _rpD3D9VertexShaderDescriptor* desc, const _rpD3D9VertexShaderDispatchDescriptor* dispatch); // 0x761A10
void _rpD3D9VertexShaderSetBumpMatrix(RwFrame* frame, RwReal factor, const _rpD3D9VertexShaderDispatchDescriptor* dispatch); // 0x761B70
RxNodeDefinition* RxNodeDefinitionGetD3D9WorldSectorAllInOne(void); // 0x75E9F0
RxNodeDefinition* RxNodeDefinitionGetD3D9AtomicAllInOne(void); // 0x7582E0
void RpMaterialSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc); // 0x74D8C0
RpMaterial* RpMaterialCreate(void); // 0x74D990
RwBool RpMaterialDestroy(RpMaterial* material); // 0x74DA20
RpMaterial* RpMaterialClone(RpMaterial* material); // 0x74DA80
RpMaterial* RpMaterialSetTexture(RpMaterial* material, RwTexture* texture); // 0x74DBC0
RwInt32 RpMaterialRegisterPlugin(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor constructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB); // 0x74DBF0
RwInt32 RpMaterialRegisterPluginStream(RwUInt32 pluginID, RwPluginDataChunkReadCallBack readCB, RwPluginDataChunkWriteCallBack writeCB, RwPluginDataChunkGetSizeCallBack getSizeCB); // 0x74DC20
RwInt32 RpMaterialSetStreamAlwaysCallBack(RwUInt32 pluginID, RwPluginDataChunkAlwaysCallBack alwaysCB); // 0x74DC50
RwInt32 RpMaterialSetStreamRightsCallBack(RwUInt32 pluginID, RwPluginDataChunkRightsCallBack rightsCB); // 0x74DC70
RwInt32 RpMaterialGetPluginOffset(RwUInt32 pluginID); // 0x74DC90
RwBool RpMaterialValidatePlugins(const RpMaterial* material); // 0x74DCB0
RwUInt32 RpMaterialStreamGetSize(const RpMaterial* material); // 0x74E010
RpMaterial* RpMaterialStreamRead(RwStream* stream); // 0x74DD30
const RpMaterial* RpMaterialStreamWrite(const RpMaterial* material, RwStream* stream); // 0x74E050
RpMaterialChunkInfo* _rpMaterialChunkInfoRead(RwStream* stream, RpMaterialChunkInfo* materialChunkInfo, RwInt32* bytesRead); // 0x74DCC0
RpMaterialList* _rpMaterialListInitialize(RpMaterialList* matList); // 0x74E1B0
RpMaterialList* _rpMaterialListDeinitialize(RpMaterialList* matList); // 0x74E150
RpMaterial** _rpMaterialListAlloc(RwUInt32 count); // 0x74E1C0
RpMaterial* _rpMaterialListGetMaterial(const RpMaterialList* matList, RwInt32 matIndex); // 0x74E2B0
RpMaterialList* _rpMaterialListSetSize(RpMaterialList* matList, RwInt32 size); // 0x74E2C0
RpMaterialList* _rpMaterialListCopy(RpMaterialList* matListOut, const RpMaterialList* matListIn); // 0x74E1F0
RwInt32 _rpMaterialListAppendMaterial(RpMaterialList* matList, RpMaterial* material); // 0x74E350
RwInt32 _rpMaterialListFindMaterialIndex(const RpMaterialList* matList, const RpMaterial* material); // 0x74E420
RwUInt32 _rpMaterialListStreamGetSize(const RpMaterialList* matList); // 0x74E450
RpMaterialList* _rpMaterialListStreamRead(RwStream* stream, RpMaterialList* matList); // 0x74E600
const RpMaterialList* _rpMaterialListStreamWrite(const RpMaterialList* matList, RwStream* stream); // 0x74E4B0
void* _rpMeshOpen(void* instance, RwInt32 offset, RwInt32 size); // 0x758970
void* _rpMeshClose(void* instance, RwInt32 offset, RwInt32 size); // 0x758940
RwInt16 _rpMeshGetNextSerialNumber(void); // 0x7590E0
RpBuildMesh* _rpBuildMeshCreate(RwUInt32 bufferSize); // 0x758A90
RwBool _rpBuildMeshDestroy(RpBuildMesh* mesh); // 0x758B80
RwBool _rpMeshDestroy(RpMeshHeader* mesh); // 0x758BC0
RpBuildMesh* _rpBuildMeshAddTriangle(RpBuildMesh* mesh, RpMaterial* material, RwInt32 vert1, RwInt32 vert2, RwInt32 vert3, RwUInt16 matIndex, RwUInt16 textureIndex, RwUInt16 rasterIndex, RwUInt16 pipelineIndex); // 0x758C00
RpMeshHeader* _rpMeshHeaderForAllMeshes(RpMeshHeader* meshHeader, RpMeshCallBack fpCallBack, void* pData); // 0x758D30
RwStream* _rpMeshWrite(const RpMeshHeader* meshHeader, const void* object, RwStream* stream, const RpMaterialList* matList); // 0x758D70
RpMeshHeader* _rpMeshRead(RwStream* stream, const void* object, const RpMaterialList* matList); // 0x758EC0
RwInt32 _rpMeshSize(const RpMeshHeader* meshHeader, const void* object); // 0x759090
void _rpMeshHeaderDestroy(RpMeshHeader* meshHeader); // 0x758910
RpMeshHeader* _rpMeshHeaderCreate(RwUInt32 size); // 0x758920
RpTriStripPolygon* RpTriStripPolygonFollowStrip(RpTriStripPolygon* curr, RpTriStripPolygon* prev); // 0x75C330
RwUInt32 RpTriStripDefaultCost(RpTriStripPolygon* startPolygon, RwUInt32 testFrame, void* data); // 0x75B500
RpTriStripMesh* RpTriStripMeshTunnel(RpTriStripMesh* mesh, void* data); // 0x75B780
RpTriStripMesh* RpTriStripMeshQuick(RpTriStripMesh* mesh, void* data); // 0x75BD80
RpMeshHeader* RpBuildMeshGenerateTriStrip(RpBuildMesh* buildMesh, void* data); // 0x75C380
RpMeshHeader* RpBuildMeshGenerateTrivialTriStrip(RpBuildMesh* buildMesh, void* data); // 0x759100
RpMeshHeader* RpBuildMeshGenerateDefaultTriStrip(RpBuildMesh* buildmesh, void* data); // 0x7591B0
RpMeshHeader* RpBuildMeshGeneratePreprocessTriStrip(RpBuildMesh* buildmesh, void* data); // 0x75A900
RpMeshHeader* RpBuildMeshGenerateExhaustiveTriStrip(RpBuildMesh* buildmesh, void* data); // 0x75A940
RpMeshHeader* RpBuildMeshGenerateDefaultIgnoreWindingTriStrip(RpBuildMesh* buildmesh, void* data); // 0x75A8E0
RpMeshHeader* RpBuildMeshGeneratePreprocessIgnoreWindingTriStrip(RpBuildMesh* buildmesh, void* data); // 0x75A920
RpMeshHeader* RpBuildMeshGenerateExhaustiveIgnoreWindingTriStrip(RpBuildMesh* buildmesh, void* data); // 0x75B4E0
RwBool RpMeshSetTriStripMethod(RpTriStripMeshCallBack callback, void* data); // 0x75D4C0
RwBool RpMeshGetTriStripMethod(RpTriStripMeshCallBack* callback, void* data); // 0x75D500
RpMeshHeader* _rpTriListMeshGenerate(RpBuildMesh* buildMesh, void* data); // 0x75D530
RpMeshHeader* _rpMeshOptimise(RpBuildMesh* buildmesh, RwUInt32 flags); // 0x75D970
RpGeometry* RpGeometryTransform(RpGeometry* geometry, const RwMatrix* matrix); // 0x74BFE0
RpGeometry* RpGeometryCreateSpace(RwReal radius); // 0x74C130
const RpMorphTarget* RpMorphTargetCalcBoundingSphere(const RpMorphTarget* morphTarget, RwSphere* boundingSphere); // 0x74C200
RwInt32 RpGeometryAddMorphTargets(RpGeometry* geometry, RwInt32 mtcount); // 0x74C310
RwInt32 RpGeometryAddMorphTarget(RpGeometry* geometry); // 0x74C4D0
RpGeometry* RpGeometryRemoveMorphTarget(RpGeometry* geometry, RwInt32 morphTarget); // 0x74C4E0
const RpGeometry* RpGeometryTriangleSetVertexIndices(const RpGeometry* geometry, RpTriangle* triangle, RwUInt16 vert1, RwUInt16 vert2, RwUInt16 vert3); // 0x74C690
RpGeometry* RpGeometryTriangleSetMaterial(RpGeometry* geometry, RpTriangle* triangle, RpMaterial* material); // 0x74C6C0
const RpGeometry* RpGeometryTriangleGetVertexIndices(const RpGeometry* geometry, const RpTriangle* triangle, RwUInt16* vert1, RwUInt16* vert2, RwUInt16* vert3); // 0x74C720
RpMaterial* RpGeometryTriangleGetMaterial(const RpGeometry* geometry, const RpTriangle* triangle); // 0x74C760
RpGeometry* RpGeometryForAllMaterials(RpGeometry* geometry, RpMaterialCallBack fpCallBack, void* pData); // 0x74C790
RpGeometry* RpGeometryLock(RpGeometry* geometry, RwInt32 lockMode); // 0x74C7D0
RpGeometry* RpGeometryUnlock(RpGeometry* geometry); // 0x74C800
const RpGeometry* RpGeometryForAllMeshes(const RpGeometry* geometry, RpMeshCallBack fpCallBack, void* pData); // 0x74CA60
RpGeometry* RpGeometryCreate(RwInt32 numVert, RwInt32 numTriangles, RwUInt32 format); // 0x74CA90
RwBool RpGeometryDestroy(RpGeometry* geometry); // 0x74CCC0
RwInt32 RpGeometryRegisterPlugin(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor constructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB); // 0x74CD70
RwInt32 RpGeometryRegisterPluginStream(RwUInt32 pluginID, RwPluginDataChunkReadCallBack readCB, RwPluginDataChunkWriteCallBack writeCB, RwPluginDataChunkGetSizeCallBack getSizeCB); // 0x74CDA0
RwInt32 RpGeometrySetStreamAlwaysCallBack(RwUInt32 pluginID, RwPluginDataChunkAlwaysCallBack alwaysCB); // 0x74CDD0
RwInt32 RpGeometryGetPluginOffset(RwUInt32 pluginID); // 0x74CDF0
RwBool RpGeometryValidatePlugins(const RpGeometry* geometry); // 0x74CE10
RwUInt32 RpGeometryStreamGetSize(const RpGeometry* geometry); // 0x74CE20
const RpGeometry* RpGeometryStreamWrite(const RpGeometry* geometry, RwStream* stream); // 0x74CED0
RpGeometry* RpGeometryStreamRead(RwStream* stream); // 0x74D190
RpGeometryChunkInfo* _rpGeometryChunkInfoRead(RwStream* stream, RpGeometryChunkInfo* geometryChunkInfo, RwInt32* bytesRead); // 0x74D750
RpWorldSector* RpWorldSectorRender(RpWorldSector* worldSector); // 0x761C50
const RpWorldSector* RpWorldSectorForAllMeshes(const RpWorldSector* sector, RpMeshCallBack fpCallBack, void* pData); // 0x761C60
RwInt32 RpWorldSectorRegisterPlugin(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor constructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB); // 0x761C90
RwInt32 RpWorldSectorRegisterPluginStream(RwUInt32 pluginID, RwPluginDataChunkReadCallBack readCB, RwPluginDataChunkWriteCallBack writeCB, RwPluginDataChunkGetSizeCallBack getSizeCB); // 0x761CC0
RwInt32 RpWorldSectorSetStreamAlwaysCallBack(RwUInt32 pluginID, RwPluginDataChunkAlwaysCallBack alwaysCB); // 0x761CF0
RwInt32 RpWorldSectorSetStreamRightsCallBack(RwUInt32 pluginID, RwPluginDataChunkRightsCallBack rightsCB); // 0x761D10
RwInt32 RpWorldSectorGetPluginOffset(RwUInt32 pluginID); // 0x761D30
RwBool RpWorldSectorValidatePlugins(const RpWorldSector* sector); // 0x761D50
void RpLightSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc); // 0x752250
RpLight* RpLightCreate(RwInt32 type); // 0x752110
RwBool RpLightDestroy(RpLight* light); // 0x7520D0
RpLight* RpLightSetRadius(RpLight* light, RwReal radius); // 0x751A70
RpLight* RpLightSetColor(RpLight* light, const RwRGBAReal* color); // 0x751A90
RwReal RpLightGetConeAngle(const RpLight* light); // 0x751AE0
RpLight* RpLightSetConeAngle(RpLight* ight, RwReal angle); // 0x751D20
RwUInt32 RpLightStreamGetSize(const RpLight* light); // 0x751E10
RpLight* RpLightStreamRead(RwStream* stream); // 0x751F00
RpLightChunkInfo* _rpLightChunkInfoRead(RwStream* stream, RpLightChunkInfo* lightChunkInfo, RwInt32* bytesRead); // 0x752060
RwInt32 RpLightRegisterPlugin(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor constructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB); // 0x751D60
RwInt32 RpLightRegisterPluginStream(RwUInt32 pluginID, RwPluginDataChunkReadCallBack readCB, RwPluginDataChunkWriteCallBack writeCB, RwPluginDataChunkGetSizeCallBack getSizeCB); // 0x751D90
RwInt32 RpLightSetStreamAlwaysCallBack(RwUInt32 pluginID, RwPluginDataChunkAlwaysCallBack alwaysCB); // 0x751DC0
RwInt32 RpLightGetPluginOffset(RwUInt32 pluginID); // 0x751DE0
RwBool RpLightValidatePlugins(const RpLight* light); // 0x751E00
void RpD3D9LightSetAttenuationParams(RpLight* light, const RpD3D9AttenuationParams* params); // 0x755D20
void RpD3D9LightGetAttenuationParams(const RpLight* light, RpD3D9AttenuationParams* params); // 0x755D50
RwBool _rwD3D9LightsOpen(void); // 0x755D80
RwBool _rwD3D9LightsGlobalEnable(RpLightFlag flags); // 0x756070
RwBool _rwD3D9LightDirectionalEnable(RpLight* light); // 0x756260
RwBool _rwD3D9LightLocalEnable(RpLight* light); // 0x756390
void _rwD3D9LightsEnable(RwBool enable, RwUInt32 type); // 0x756600
void _rwD3D9LightsClose(void); // 0x755FE0
void RpAtomicSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc); // 0x749720
void RpClumpSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc); // 0x749740
RpAtomic* AtomicDefaultRenderCallBack(RpAtomic* atomic); // 0x7491C0
void _rpAtomicResyncInterpolatedSphere(RpAtomic* atomic); // 0x7491F0
const RwSphere* RpAtomicGetWorldBoundingSphere(RpAtomic* atomic); // 0x749330
RpClump* RpClumpForAllAtomics(RpClump* clump, RpAtomicCallBack callback, void* pData); // 0x749B70
RpClump* RpClumpForAllLights(RpClump* clump, RpLightCallBack callback, void* pData); // 0x749C00
RpClump* RpClumpForAllCameras(RpClump* clump, RwCameraCallBack callback, void* pData); // 0x749BB0
RpAtomic* RpAtomicSetFrame(RpAtomic* atomic, RwFrame* frame); // 0x74BF20
RpClump* RpClumpCreateSpace(const RwV3d* position, RwReal radius); // 0x749970
RpClump* RpClumpRender(RpClump* clump); // 0x749B20
RpClump* RpClumpRemoveAtomic(RpClump* clump, RpAtomic* atomic); // 0x74A4C0
RpClump* RpClumpAddAtomic(RpClump* clump, RpAtomic* atomic); // 0x74A490
RpClump* RpClumpRemoveLight(RpClump* clump, RpLight* light); // 0x74A520
RpClump* RpClumpAddLight(RpClump* clump, RpLight* light); // 0x74A4F0
RpClump* RpClumpRemoveCamera(RpClump* clump, RwCamera* camera); // 0x74A580
RpClump* RpClumpAddCamera(RpClump* clump, RwCamera* camera); // 0x74A550
RwBool RpClumpDestroy(RpClump* clump); // 0x74A310
RpClump* RpClumpCreate(void); // 0x74A290
RpClump* RpClumpClone(RpClump* clump); // 0x749F70
RwBool RpAtomicDestroy(RpAtomic* atomic); // 0x749DC0
RpAtomic* RpAtomicClone(RpAtomic* atomic); // 0x749E60
RpAtomic* RpAtomicCreate(void); // 0x749C50
RpAtomic* RpAtomicSetGeometry(RpAtomic* atomic, RpGeometry* geometry, RwUInt32 flags); // 0x749D40
RpClump* RpClumpSetCallBack(RpClump* clump, RpClumpCallBack callback); // 0x74A240
RpClumpCallBack RpClumpGetCallBack(const RpClump* clump); // 0x74A270
RwInt32 RpClumpGetNumAtomics(RpClump* clump); // 0x7498E0
RwInt32 RpClumpGetNumLights(RpClump* clump); // 0x749910
RwInt32 RpClumpGetNumCameras(RpClump* clump); // 0x749940
RpClump* RpLightGetClump(const RpLight* light); // 0x749E40
RpClump* RwCameraGetClump(const RwCamera* camera); // 0x749E50
RwUInt32 RpAtomicStreamGetSize(RpAtomic* atomic); // 0x74A5B0
RpAtomic* RpAtomicStreamRead(RwStream* stream); // 0x74B030
RpAtomic* RpAtomicStreamWrite(RpAtomic* atomic, RwStream* stream); // 0x74A850
RwUInt32 RpClumpStreamGetSize(RpClump* clump); // 0x74A5E0
RpClump* RpClumpStreamRead(RwStream* stream); // 0x74B420
RpClump* RpClumpStreamWrite(RpClump* clump, RwStream* stream); // 0x74AA10
RpClumpChunkInfo* _rpClumpChunkInfoRead(RwStream* stream, RpClumpChunkInfo* clumpChunkInfo, RwInt32* bytesRead); // 0x74BD40
RwInt32 RpAtomicRegisterPlugin(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor constructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB); // 0x74BDA0
RwInt32 RpClumpRegisterPlugin(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor constructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB); // 0x74BDD0
RwInt32 RpAtomicRegisterPluginStream(RwUInt32 pluginID, RwPluginDataChunkReadCallBack readCB, RwPluginDataChunkWriteCallBack writeCB, RwPluginDataChunkGetSizeCallBack getSizeCB); // 0x74BE00
RwInt32 RpAtomicSetStreamAlwaysCallBack(RwUInt32 pluginID, RwPluginDataChunkAlwaysCallBack alwaysCB); // 0x74BE30
RwInt32 RpAtomicSetStreamRightsCallBack(RwUInt32 pluginID, RwPluginDataChunkRightsCallBack rightsCB); // 0x74BE50
RwInt32 RpClumpRegisterPluginStream(RwUInt32 pluginID, RwPluginDataChunkReadCallBack readCB, RwPluginDataChunkWriteCallBack writeCB, RwPluginDataChunkGetSizeCallBack getSizeCB); // 0x74BE70
RwInt32 RpClumpSetStreamAlwaysCallBack(RwUInt32 pluginID, RwPluginDataChunkAlwaysCallBack alwaysCB); // 0x74BEA0
RwInt32 RpAtomicGetPluginOffset(RwUInt32 pluginID); // 0x74BEC0
RwInt32 RpClumpGetPluginOffset(RwUInt32 pluginID); // 0x74BEE0
RwBool RpAtomicValidatePlugins(const RpAtomic* atomic); // 0x74BF00
RwBool RpClumpValidatePlugins(const RpClump* clump); // 0x74BF10
RwBool RpAtomicInstance(RpAtomic* atomic); // 0x74BF40
RwBool _rpWorldFindBBox(RpWorld* world, RwBBox* boundingBox); // 0x74EFA0
RpWorld* _rpWorldSetupSectorBoundingBoxes(RpWorld* world); // 0x74F020
void _rpWorldSectorDeinstanceAll(RpSector* sector); // 0x74ECA0
void _rpWorldSectorDestroyRecurse(RpSector* sector); // 0x74ED50
RwBool _rpWorldForAllGlobalLights(RpLightCallBack callBack, void* pData); // 0x74EF10
RpWorldSector* _rpWorldSectorForAllLocalLights(RpWorldSector* sector, RpLightCallBack callBack, void* pData); // 0x74EF60
RpWorldSector* _rpSectorDefaultRenderCallBack(RpWorldSector* sector); // 0x74EEC0
RpWorld* RpWorldLock(RpWorld* world); // 0x74F1A0
RpWorld* RpWorldUnlock(RpWorld* world); // 0x74F210
void _rpWorldRegisterWorld(RpWorld* world, RwUInt32 memorySize); // 0x74F0C0
void _rpWorldUnregisterWorld(RpWorld* world); // 0x74F140
RwBool RpWorldPluginAttach(void); // 0x74FDA0
RpWorld* RpWorldForAllClumps(RpWorld* world, RpClumpCallBack fpCallBack, void* pData); // 0x74FB80
RpWorld* RpWorldForAllMaterials(RpWorld* world, RpMaterialCallBack fpCallBack, void* pData); // 0x74FBC0
RpWorld* RpWorldForAllLights(RpWorld* world, RpLightCallBack fpCallBack, void* pData); // 0x74FC00
RpWorld* RpWorldForAllWorldSectors(RpWorld* world, RpWorldSectorCallBack fpCallBack, void* pData); // 0x74FC70
RpWorld* RpWorldRender(RpWorld* world); // 0x74F570
RwBool RpWorldDestroy(RpWorld* world); // 0x74F610
RpWorld* RpWorldCreate(RwBBox* boundingBox); // 0x74F760
RpWorld* RpWorldSetSectorRenderCallBack(RpWorld* world, RpWorldSectorCallBackRender fpCallBack); // 0x74F730
RpWorldSectorCallBackRender RpWorldGetSectorRenderCallBack(const RpWorld* world); // 0x74F750
RpWorld* RpWorldSectorGetWorld(const RpWorldSector* sector); // 0x74F4E0
RwInt32 RpWorldRegisterPlugin(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor constructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB); // 0x74FCD0
RwInt32 RpWorldRegisterPluginStream(RwUInt32 pluginID, RwPluginDataChunkReadCallBack readCB, RwPluginDataChunkWriteCallBack writeCB, RwPluginDataChunkGetSizeCallBack getSizeCB); // 0x74FD00
RwInt32 RpWorldSetStreamAlwaysCallBack(RwUInt32 pluginID, RwPluginDataChunkAlwaysCallBack alwaysCB); // 0x74FD30
RwInt32 RpWorldSetStreamRightsCallBack(RwUInt32 pluginID, RwPluginDataChunkRightsCallBack rightsCB); // 0x74FD50
RwInt32 RpWorldGetPluginOffset(RwUInt32 pluginID); // 0x74FD70
RwBool RpWorldValidatePlugins(RpWorld* world); // 0x74FD90
void RpD3D9GeometrySetUsageFlags(RpGeometry* geometry, RpD3D9GeometryUsageFlag flags); // 0x7588B0
RpD3D9GeometryUsageFlag RpD3D9GeometryGetUsageFlags(const RpGeometry* geometry); // 0x7588D0
void RpD3D9WorldSectorSetUsageFlags(RpWorldSector* sector, RpD3D9WorldSectorUsageFlag flags); // 0x7588E0
RpD3D9WorldSectorUsageFlag RpD3D9WorldSectorGetUsageFlags(const RpWorldSector* sector); // 0x758900
void RxD3D9AllInOneSetInstanceCallBack(RxPipelineNode* node, RxD3D9AllInOneInstanceCallBack callback); // 0x757380
RxD3D9AllInOneInstanceCallBack RxD3D9AllInOneGetInstanceCallBack(RxPipelineNode* node); // 0x757390
void RxD3D9AllInOneSetReinstanceCallBack(RxPipelineNode* node, RxD3D9AllInOneReinstanceCallBack callback); // 0x7573A0
RxD3D9AllInOneReinstanceCallBack RxD3D9AllInOneGetReinstanceCallBack(RxPipelineNode* node); // 0x7573B0
void RxD3D9AllInOneSetLightingCallBack(RxPipelineNode* node, RxD3D9AllInOneLightingCallBack callback); // 0x7573C0
RxD3D9AllInOneLightingCallBack RxD3D9AllInOneGetLightingCallBack(RxPipelineNode* node); // 0x7573D0
void RxD3D9AllInOneSetRenderCallBack(RxPipelineNode* node, RxD3D9AllInOneRenderCallBack callback); // 0x7573E0
RxD3D9AllInOneRenderCallBack RxD3D9AllInOneGetRenderCallBack(RxPipelineNode* node); // 0x7573F0
void _rpD3D9AddDynamicGeometry(RpGeometry* geometry); // 0x74E970
void _rpD3D9RemoveDynamicGeometry(RpGeometry* geometry); // 0x74E9E0
RwUInt32 _rpD3D9VertexDeclarationGetSize(RwUInt32 type); // 0x7522E0
RwUInt32 _rpD3D9VertexDeclarationGetStride(const void* vertexDeclaration); // 0x7522F0
RwUInt32 _rpD3D9VertexDeclarationInstV3d(RwUInt32 type, RwUInt8* mem, const RwV3d* src, RwInt32 numVerts, RwUInt32 stride); // 0x752AD0
RwUInt32 _rpD3D9VertexDeclarationInstV3dComp(RwUInt32 type, RwUInt8* mem, const RpVertexNormal* src, RwInt32 numVerts, RwUInt32 stride); // 0x7531B0
RwUInt32 _rpD3D9VertexDeclarationInstV3dMorph(RwUInt32 type, RwUInt8* mem, const RwV3d* src1, const RwV3d* src2, RwReal scale, RwInt32 numVerts, RwUInt32 stride); // 0x753B60
RwUInt32 _rpD3D9VertexDeclarationInstV2d(RwUInt32 type, RwUInt8* mem, const RwV2d* src, RwInt32 numVerts, RwUInt32 stride); // 0x7544E0
RwBool _rpD3D9VertexDeclarationInstColor(RwUInt8* mem, const RwRGBA* color, RwInt32 numVerts, RwUInt32 stride); // 0x754AE0
RwUInt32 _rpD3D9VertexDeclarationInstIndices(RwUInt32 type, RwUInt8* mem, const RwUInt32* indices, RwInt32 numVerts, RwUInt32 stride); // 0x754B40
RwUInt32 _rpD3D9VertexDeclarationInstIndicesRemap(RwUInt32 type, RwUInt8* mem, const RwUInt32* indices, const RwUInt8* remap, RwInt32 numVerts, RwUInt32 stride); // 0x754C80
RwUInt32 _rpD3D9VertexDeclarationInstWeights(RwUInt32 type, RwUInt8* mem, const RwV4d* src, RwInt32 numVerts, RwUInt32 stride); // 0x752320
RwUInt32 _rpD3D9VertexDeclarationInstTangent(RwUInt32 type, RwUInt8* mem, const RwV3d* pos, const RwTexCoords* texCoord, RxD3D9ResEntryHeader* meshHeader, RwUInt32 stride); // 0x754E20
void _rpD3D9VertexDeclarationUnInstV3d(RwUInt32 type, RwV3d* dst, const RwUInt8* src); // 0x7551F0
void _rpD3D9VertexDeclarationUnInstV2d(RwUInt32 type, RwV2d* dst, const RwUInt8* src); // 0x7555E0
void _rpD3D9GetMinMaxValuesV3d(const RwV3d* src, RwInt32 numElements, RwV3d* min, RwV3d* max); // 0x755830
void _rpD3D9GetMinMaxValuesV2d(const RwV2d* src, RwInt32 numElements, RwV2d* min, RwV2d* max); // 0x7558F0
RwUInt32 _rpD3D9FindFormatV3d(const RwV3d* src, RwInt32 numElements); // 0x755980
RwUInt32 _rpD3D9FindFormatV2d(const RwV2d* src, RwInt32 numElements); // 0x755AA0
RxPipeline* RpWorldSetDefaultSectorPipeline(RxPipeline* pipeline); // 0x75E270
RxPipeline* RpAtomicSetDefaultPipeline(RxPipeline* pipeline); // 0x75E2A0
RxPipeline* RpMaterialSetDefaultPipeline(RxPipeline* pipeline); // 0x75E2D0
const RpGeometry* RpGeometryIsCorrectlySorted(const RpGeometry* geometry, RwBool* result); // 0x75D9D0
RpGeometry* RpGeometrySortByMaterial(const RpGeometry* geometry, RpGeometrySortByMaterialCallBack callback); // 0x75DAE0
void RpTieSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc); // 0x74FF60
void RpLightTieSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc); // 0x74FF80
RpWorld* RpWorldRemoveCamera(RpWorld* world, RwCamera* camera); // 0x750F50
RpWorld* RpWorldAddCamera(RpWorld* world, RwCamera* camera); // 0x750F20
RpWorld* RwCameraGetWorld(const RwCamera* camera); // 0x750F80
RpWorld* RpWorldRemoveAtomic(RpWorld* world, RpAtomic* atomic); // 0x750FC0
RpWorld* RpWorldAddAtomic(RpWorld* world, RpAtomic* atomic); // 0x750F90
RpWorld* RpAtomicGetWorld(const RpAtomic* atomic); // 0x751050
RpWorld* RpWorldAddClump(RpWorld* world, RpClump* clump); // 0x751300
RpWorld* RpWorldRemoveClump(RpWorld* world, RpClump* clump); // 0x751460
RpWorld* RpClumpGetWorld(const RpClump* clump); // 0x7516B0
RpWorld* RpWorldAddLight(RpWorld* world, RpLight* light); // 0x751910
RpWorld* RpWorldRemoveLight(RpWorld* world, RpLight* light); // 0x751960
RpWorld* RpLightGetWorld(const RpLight* light); // 0x7519E0
RwCamera* RwCameraForAllClumpsInFrustum(RwCamera* camera, void* data); // 0x7516C0
RwCamera* RwCameraForAllAtomicsInFrustum(RwCamera* camera, RpAtomicCallBack callback, void* data); // 0x7517F0
RwCamera* RwCameraForAllSectorsInFrustum(RwCamera* camera, RpWorldSectorCallBack callBack, void* pData); // 0x751660
RpLight* RpLightForAllWorldSectors(RpLight* light, RpWorldSectorCallBack callback, void* data); // 0x7519F0
RpAtomic* RpAtomicForAllWorldSectors(RpAtomic* atomic, RpWorldSectorCallBack callback, void* data); // 0x751060
RpWorldSector* RpWorldSectorForAllAtomics(RpWorldSector* sector, RpAtomicCallBack callback, void* data); // 0x7510A0
RpWorldSector* RpWorldSectorForAllCollisionAtomics(RpWorldSector* sector, RpAtomicCallBack callback, void* data); // 0x751140
RpWorldSector* RpWorldSectorForAllLights(RpWorldSector* sector, RpLightCallBack callback, void* data); // 0x7511E0
RwUInt32 RpWorldStreamGetSize(const RpWorld* world); // 0x761EA0
RpWorld* RpWorldStreamRead(RwStream* stream); // 0x762960
const RpWorld* RpWorldStreamWrite(const RpWorld* world, RwStream* stream); // 0x762150
RpWorldSectorChunkInfo* _rpWorldSectorChunkInfoRead(RwStream* stream, RpWorldSectorChunkInfo* worldSectorChunkInfo, RwInt32* bytesRead); // 0x7635B0
RpPlaneSectorChunkInfo* _rpPlaneSectorChunkInfoRead(RwStream* stream, RpPlaneSectorChunkInfo* planeSectorChunkInfo, RwInt32* bytesRead); // 0x763620
RpWorldChunkInfo* _rpWorldChunkInfoRead(RwStream* stream, RpWorldChunkInfo* worldChunkInfo, RwInt32* bytesRead); // 0x763690

/* rtquat.h */

RwBool RtQuatConvertFromMatrix(RtQuat * const qpQuat, const RwMatrix * const mpMatrix); // 0x7EB5C0
RtQuat* RtQuatRotate(RtQuat* quat, const RwV3d* axis, RwReal angle, RwOpCombineType combineOp); // 0x7EB7C0
const RtQuat* RtQuatQueryRotate(const RtQuat* quat, RwV3d* unitAxis, RwReal* angle); // 0x7EBA80
RwV3d* RtQuatTransformVectors(RwV3d* vectorsOut, const RwV3d* vectorsIn, const RwInt32 numPoints, const RtQuat* quat); // 0x7EBBB0
RwReal RtQuatModulus(RtQuat* q); // 0x7EBD10

/* rtanim.h */

void RtAnimAnimationFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc); // 0x7CCC80
RwBool RtAnimInitialize(void); // 0x7CCCA0
RwBool RtAnimRegisterInterpolationScheme(RtAnimInterpolatorInfo* interpolatorInfo); // 0x7CCD40
RtAnimInterpolatorInfo* RtAnimGetInterpolatorInfo(RwInt32 typeID); // 0x7CCDE0
RtAnimAnimation* RtAnimAnimationCreate(RwInt32 typeID, RwInt32 numFrames, RwInt32 flags, RwReal duration); // 0x7CCE40
RwBool RtAnimAnimationDestroy(RtAnimAnimation* animation); // 0x7CCF10
RtAnimAnimation* RtAnimAnimationRead(const RwChar* filename); // 0x7CCF30
RwBool RtAnimAnimationWrite(const RtAnimAnimation* animation, const RwChar* filename); // 0x7CD160
RtAnimAnimation* RtAnimAnimationStreamRead(RwStream* stream); // 0x7CD220
RwBool RtAnimAnimationStreamWrite(const RtAnimAnimation* animation, RwStream* stream); // 0x7CD410
RwInt32 RtAnimAnimationStreamGetSize(const RtAnimAnimation* animation); // 0x7CD4D0
RwUInt32 RtAnimAnimationGetNumNodes(const RtAnimAnimation* animation); // 0x7CD4F0
RtAnimInterpolator* RtAnimInterpolatorCreate(RwInt32 numNodes, RwInt32 maxInterpKeyFrameSize); // 0x7CD520
void RtAnimInterpolatorDestroy(RtAnimInterpolator* anim); // 0x7CD590
RwBool RtAnimInterpolatorSetCurrentAnim(RtAnimInterpolator* animI, RtAnimAnimation* anim); // 0x7CD5A0
RwBool RtAnimInterpolatorSetKeyFrameCallBacks(RtAnimInterpolator* anim, RwInt32 keyFrameTypeID); // 0x7CD660
void RtAnimInterpolatorSetAnimLoopCallBack(RtAnimInterpolator* anim, RtAnimCallBack callBack, void* data); // 0x7CD6F0
void RtAnimInterpolatorSetAnimCallBack(RtAnimInterpolator* anim, RtAnimCallBack callBack, RwReal time, void* data); // 0x7CD710
RwBool RtAnimInterpolatorCopy(RtAnimInterpolator* outAnim, RtAnimInterpolator* inAnim); // 0x7CD730
RwBool RtAnimInterpolatorSubAnimTime(RtAnimInterpolator* anim, RwReal time); // 0x7CD760
RwBool RtAnimInterpolatorAddAnimTime(RtAnimInterpolator* anim, RwReal time); // 0x7CD8D0
RwBool RtAnimInterpolatorSetCurrentTime(RtAnimInterpolator* anim, RwReal time); // 0x7CDAB0
RwBool RtAnimAnimationMakeDelta(RtAnimAnimation* animation, RwInt32 numNodes, RwReal time); // 0x7CDB00
RwBool RtAnimInterpolatorBlend(RtAnimInterpolator* outAnim, RtAnimInterpolator* inAnim1, RtAnimInterpolator* inAnim2, RwReal alpha); // 0x7CDBF0
RwBool RtAnimInterpolatorAddTogether(RtAnimInterpolator* outAnim, RtAnimInterpolator* inAnim1, RtAnimInterpolator* inAnim2); // 0x7CDC50
RtAnimInterpolator* RtAnimInterpolatorCreateSubInterpolator(RtAnimInterpolator* parentAnim, RwInt32 startNode, RwInt32 numNodes, RwInt32 maxInterpKeyFrameSize); // 0x7CDCB0
RwBool RtAnimInterpolatorBlendSubInterpolator(RtAnimInterpolator* outAnim, RtAnimInterpolator* inAnim1, RtAnimInterpolator* inAnim2, RwReal alpha); // 0x7CDCF0
RwBool RtAnimInterpolatorAddSubInterpolator(RtAnimInterpolator* outAnim, RtAnimInterpolator* mainAnim, RtAnimInterpolator* subAnim); // 0x7CDEF0

/* rphanim.h */

void RpHAnimHierarchySetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc); // 0x7C45E0
RpHAnimHierarchy* RpHAnimHierarchyCreate(RwInt32 numNodes, RwUInt32* nodeFlags, RwInt32* nodeIDs, RpHAnimHierarchyFlag flags, RwInt32 maxInterpKeyFrameSize); // 0x7C4C30
RpHAnimHierarchy* RpHAnimHierarchyCreateFromHierarchy(RpHAnimHierarchy* hierarchy, RpHAnimHierarchyFlag flags, RwInt32 maxInterpKeyFrameSize); // 0x7C4ED0
RpHAnimHierarchy* RpHAnimHierarchyDestroy(RpHAnimHierarchy* hierarchy); // 0x7C4D30
RpHAnimHierarchy* RpHAnimHierarchyCreateSubHierarchy(RpHAnimHierarchy* parentHierarchy, RwInt32 startNode, RpHAnimHierarchyFlag flags, RwInt32 maxInterpKeyFrameSize); // 0x7C4DB0
RpHAnimHierarchy* RpHAnimHierarchyAttach(RpHAnimHierarchy* hierarchy); // 0x7C4F40
RpHAnimHierarchy* RpHAnimHierarchyDetach(RpHAnimHierarchy* hierarchy); // 0x7C4FF0
RpHAnimHierarchy* RpHAnimHierarchyAttachFrameIndex(RpHAnimHierarchy* hierarchy, RwInt32 nodeIndex); // 0x7C5020
RpHAnimHierarchy* RpHAnimHierarchyDetachFrameIndex(RpHAnimHierarchy* hierarchy, RwInt32 nodeIndex); // 0x7C5100
RwBool RpHAnimFrameSetHierarchy(RwFrame* frame, RpHAnimHierarchy* hierarchy); // 0x7C5130
RpHAnimHierarchy* RpHAnimFrameGetHierarchy(RwFrame* frame); // 0x7C5160
RwMatrix* RpHAnimHierarchyGetMatrixArray(RpHAnimHierarchy* hierarchy); // 0x7C5120
RwBool RpHAnimHierarchyUpdateMatrices(RpHAnimHierarchy* hierarchy); // 0x7C51D0
RwInt32 RpHAnimIDGetIndex(RpHAnimHierarchy* hierarchy, RwInt32 ID); // 0x7C51A0
RwBool RpHAnimPluginAttach(void); // 0x7C4600
void RpHAnimKeyFrameApply(void* matrix, void* voidIFrame); // 0x7C5B80
void RpHAnimKeyFrameBlend(void* voidOut, void* voidIn1, void* voidIn2, RwReal alpha); // 0x7C60C0
void RpHAnimKeyFrameInterpolate(void* voidOut, void* voidIn1, void* voidIn2, RwReal time, void* customData); // 0x7C5CA0
void RpHAnimKeyFrameAdd(void* voidOut, void* voidIn1, void* voidIn2); // 0x7C6720
void RpHAnimKeyFrameMulRecip(void* voidFrame, void* voidStart); // 0x7C65C0
RtAnimAnimation* RpHAnimKeyFrameStreamRead(RwStream* stream, RtAnimAnimation* animation); // 0x7C64C0
RwBool RpHAnimKeyFrameStreamWrite(const RtAnimAnimation* animation, RwStream* stream); // 0x7C6540
RwInt32 RpHAnimKeyFrameStreamGetSize(const RtAnimAnimation* animation); // 0x7C65B0
RwBool RpHAnimFrameSetID(RwFrame* frame, RwInt32 id); // 0x7C5170
RwInt32 RpHAnimFrameGetID(RwFrame* frame); // 0x7C5190

/* rpuvanim.h */

_rpUVAnimCustomData* _rpUVAnimCustomDataStreamRead(RwStream* stream); // 0x7CBF70
const _rpUVAnimCustomData* _rpUVAnimCustomDataStreamWrite(const _rpUVAnimCustomData* customData, RwStream* stream); // 0x7CBFD0
RwUInt32 _rpUVAnimCustomDataStreamGetSize(const _rpUVAnimCustomData* customData); // 0x7CC010
RwBool RpUVAnimPluginAttach(void); // 0x7CB940
void RpUVAnimLinearKeyFrameApply(void* matrix, void* voidIFrame); // 0x7CC9F0
void RpUVAnimLinearKeyFrameBlend(void* voidOut, void* voidIn1, void* voidIn2, RwReal alpha); // 0x7CCAC0
void RpUVAnimLinearKeyFrameInterpolate(void* voidOut, void* voidIn1, void* voidIn2, RwReal time, void* customData); // 0x7CCA40
void RpUVAnimLinearKeyFrameAdd(void* voidOut, void* voidIn1, void* voidIn2); // 0x7CCBE0
void RpUVAnimLinearKeyFrameMulRecip(void* voidFrame, void* voidStart); // 0x7CCB30
void RpUVAnimParamKeyFrameApply(void* matrix, void* voidIFrame); // 0x7CC560
void RpUVAnimParamKeyFrameBlend(void* voidOut, void* voidIn1, void* voidIn2, RwReal alpha); // 0x7CC6A0
void RpUVAnimParamKeyFrameInterpolate(void* voidOut, void* voidIn1, void* voidIn2, RwReal time, void* customData); // 0x7CC600
void RpUVAnimParamKeyFrameAdd(void* voidOut, void* voidIn1, void* voidIn2); // 0x7CC750
void RpUVAnimParamKeyFrameMulRecip(void* voidFrame, void* voidStart); // 0x7CC740
RtAnimAnimation* RpUVAnimKeyFrameStreamRead(RwStream* stream, RtAnimAnimation* animation); // 0x7CC870
RwBool RpUVAnimKeyFrameStreamWrite(const RtAnimAnimation* animation, RwStream* stream); // 0x7CC920
RwInt32 RpUVAnimKeyFrameStreamGetSize(const RtAnimAnimation* animation); // 0x7CC9D0
RpUVAnim* RpUVAnimCreate(const RwChar* name, RwUInt32 numNodes, RwUInt32 numFrames, RwReal duration, RwUInt32* nodeIndexToUVChannelMap, RpUVAnimKeyFrameType keyframeType); // 0x7CC020
RwBool RpUVAnimDestroy(RpUVAnim* anim); // 0x7CC0C0
RpUVAnim* RpUVAnimAddRef(RpUVAnim* anim); // 0x7CC100
const RwChar* RpUVAnimGetName(const RpUVAnim* anim); // 0x7CC3A0
RpMaterial* RpMaterialSetUVAnim(RpMaterial* material, RpUVAnim* anim, RwUInt32 slot); // 0x7CC3B0
RpUVAnimInterpolator* RpMaterialUVAnimGetInterpolator(RpMaterial* material, RwUInt32 slot); // 0x7CC430
RpMaterial* RpMaterialUVAnimSetInterpolator(RpMaterial* material, RpUVAnimInterpolator* interp, RwUInt32 slot); // 0x7CC450
RpMaterial* RpMaterialUVAnimSetCurrentTime(RpMaterial* material, RwReal time); // 0x7CC470
RpMaterial* RpMaterialUVAnimAddAnimTime(RpMaterial* material, RwReal deltaTime); // 0x7CC4B0
RpMaterial* RpMaterialUVAnimSubAnimTime(RpMaterial* material, RwReal deltaTime); // 0x7CC4F0
RwBool RpMaterialUVAnimExists(const RpMaterial* material); // 0x7CC530

/* rpskin.h */

void RpSkinSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc); // 0x7C67F0
RwBool RpSkinPluginAttach(void); // 0x7C6820
RpAtomic* RpSkinAtomicSetHAnimHierarchy(RpAtomic* atomic, RpHAnimHierarchy* hierarchy); // 0x7C7520
RpHAnimHierarchy* RpSkinAtomicGetHAnimHierarchy(const RpAtomic* atomic); // 0x7C7540
RpGeometry* RpSkinGeometrySetSkin(RpGeometry* geometry, RpSkin* skin); // 0x7C7560
RpSkin* RpSkinGeometryGetSkin(RpGeometry* geometry); // 0x7C7550
RpSkin* RpSkinCreate(RwUInt32 numVertices, RwUInt32 numBones, RwMatrixWeights* vertexWeights, RwUInt32* vertexIndices, RwMatrix* inverseMatrices); // 0x7C75B0
RpSkin* RpSkinDestroy(RpSkin* skin); // 0x7C77A0
RwUInt32 RpSkinGetNumBones(RpSkin* skin); // 0x7C77E0
const RwMatrixWeights* RpSkinGetVertexBoneWeights(RpSkin* skin); // 0x7C77F0
const RwUInt32* RpSkinGetVertexBoneIndices(RpSkin* skin); // 0x7C7800
const RwMatrix* RpSkinGetSkinToBoneMatrices(RpSkin* skin); // 0x7C7810
RwBool RpSkinIsSplit(RpSkin* skin); // 0x7C7820
RpAtomic* RpSkinAtomicSetType(RpAtomic* atomic, RpSkinType type); // 0x7C7830
RpSkinType RpSkinAtomicGetType(RpAtomic* atomic); // 0x7C7880
RpGeometry* _rpSkinInitialize(RpGeometry* geometry); // 0x7C8740
RpGeometry* _rpSkinDeinitialize(RpGeometry* geometry); // 0x7C8820
RwUInt8* _rpSkinGetMeshBoneRemapIndices(RpSkin* skin); // 0x7C8A40
RwUInt8* _rpSkinGetMeshBoneRLECount(RpSkin* skin); // 0x7C8A50
RwUInt8* _rpSkinGetMeshBoneRLE(RpSkin* skin); // 0x7C8A60
RpSkin* _rpSkinSplitDataCreate(RpSkin* skin, RwUInt32 boneLimit, RwUInt32 numMatrices, RwUInt32 numMeshes, RwUInt32 numRLE); // 0x7C8A70
RwBool _rpSkinSplitDataDestroy(RpSkin* skin); // 0x7C8B10
RxNodeDefinition* RxNodeDefinitionGetD3D9SkinAtomicAllInOne(void); // 0x7CB2A0

/* rtdict.h */

RtDictSchema* RtDictSchemaInit(RtDictSchema* schema); // 0x7CED40
RwBool RtDictSchemaDestruct(RtDictSchema* schema); // 0x7CED70
RtDict* RtDictSchemaStreamReadDict(RtDictSchema* schema, RwStream* stream); // 0x7CF240
RtDict* RtDictSchemaCreateDict(RtDictSchema* schema); // 0x7CED90
RtDictSchema* RtDictSchemaAddDict(RtDictSchema* schema, RtDict* dict); // 0x7CEE50
RtDictSchema* RtDictSchemaRemoveDict(RtDictSchema* schema, RtDict* dict); // 0x7CEE80
RwBool RtDictSchemaForAllDictionaries(RtDictSchema* schema, RtDictCallBack* callback, RtDictEntryType data); // 0x7CF5B0
RtDict* RtDictSchemaGetCurrentDict(RtDictSchema* schema); // 0x7CEEE0
RtDictSchema* RtDictSchemaSetCurrentDict(RtDictSchema* schema, RtDict* dict); // 0x7CEEF0
RwBool RtDictDestroy(RtDict* dictionary); // 0x7CF130
RtDictEntryType RtDictAddEntry(RtDict* dictionary, RtDictEntryType entry); // 0x7CEFB0
RtDictEntryType RtDictFindNamedEntry(RtDict* dictionary, const RwChar* name); // 0x7CEFE0
const RtDict* RtDictForAllEntries(const RtDict* dictionary, RtDictEntryCallBack* callBack, RtDictEntryType data); // 0x7CF060
RtDict* RtDictRemoveEntry(RtDict* dictionary, RtDictEntryType entry); // 0x7CF0C0
const RtDict* RtDictStreamWrite(const RtDict* dictionary, RwStream* stream); // 0x7CF490
RwUInt32 RtDictStreamGetSize(const RtDict* dictionary); // 0x7CF1F0
RtDict* _rtDictSchemaInitDict(RtDictSchema* schema, RtDict* dictionary); // 0x7CEF00
RwBool _rtDictDestruct(RtDict* dictionary); // 0x7CEF60

/* rpmatfx.h */

void RpMatFXMaterialDataSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc); // 0x810700
RwBool RpMatFXPluginAttach(void); // 0x810AA0
RpAtomic* RpMatFXAtomicEnableEffects(RpAtomic* atomic); // 0x811C00
RwBool RpMatFXAtomicQueryEffects(RpAtomic* atomic); // 0x811C30
RpWorldSector* RpMatFXWorldSectorEnableEffects(RpWorldSector* worldSector); // 0x811C40
RwBool RpMatFXWorldSectorQueryEffects(RpWorldSector* worldSector); // 0x811C70
RpMaterial* RpMatFXMaterialSetEffects(RpMaterial* material, RpMatFXMaterialFlags flags); // 0x811C80
RpMaterial* RpMatFXMaterialSetupBumpMap(RpMaterial* material, RwTexture* texture, RwFrame* frame, RwReal coef); // 0x811E00
RpMaterial* RpMatFXMaterialSetupEnvMap(RpMaterial* material, RwTexture* texture, RwFrame* frame, RwBool useFrameBufferAlpha, RwReal coef); // 0x811ED0
RpMaterial* RpMatFXMaterialSetupDualTexture(RpMaterial* material, RwTexture* texture, RwBlendFunction srcBlendMode, RwBlendFunction dstBlendMode); // 0x812040
RpMatFXMaterialFlags RpMatFXMaterialGetEffects(const RpMaterial* material); // 0x812140
RpMaterial* RpMatFXMaterialSetBumpMapTexture(RpMaterial* material, RwTexture* texture); // 0x812160
RpMaterial* RpMatFXMaterialSetBumpMapFrame(RpMaterial* material, RwFrame* frame); // 0x812320
RpMaterial* RpMatFXMaterialSetBumpMapCoefficient(RpMaterial* material, RwReal coef); // 0x812380
RwTexture* RpMatFXMaterialGetBumpMapTexture(const RpMaterial* material); // 0x812430
RwTexture* RpMatFXMaterialGetBumpMapBumpedTexture(const RpMaterial* material); // 0x8123E0
RwFrame* RpMatFXMaterialGetBumpMapFrame(const RpMaterial* material); // 0x812480
RwReal RpMatFXMaterialGetBumpMapCoefficient(const RpMaterial* material); // 0x8124D0
RpMaterial* RpMatFXMaterialSetEnvMapTexture(RpMaterial* material, RwTexture* texture); // 0x812530
RpMaterial* RpMatFXMaterialSetEnvMapFrame(RpMaterial* material, RwFrame* frame); // 0x8125B0
RpMaterial* RpMatFXMaterialSetEnvMapFrameBufferAlpha(RpMaterial* material, RwBool useFrameBufferAlpha); // 0x812610
RpMaterial* RpMatFXMaterialSetEnvMapCoefficient(RpMaterial* material, RwReal coef); // 0x812680
RwTexture* RpMatFXMaterialGetEnvMapTexture(const RpMaterial* material); // 0x8126F0
RwFrame* RpMatFXMaterialGetEnvMapFrame(const RpMaterial* material); // 0x812740
RwBool RpMatFXMaterialGetEnvMapFrameBufferAlpha(const RpMaterial* material); // 0x812790
RwReal RpMatFXMaterialGetEnvMapCoefficient(const RpMaterial* material); // 0x8127E0
RpMaterial* RpMatFXMaterialSetDualTexture(RpMaterial* material, RwTexture* texture); // 0x812830
RpMaterial* RpMatFXMaterialSetDualBlendModes(RpMaterial* material, RwBlendFunction srcBlendMode, RwBlendFunction dstBlendMode); // 0x8128C0
RwTexture* RpMatFXMaterialGetDualTexture(const RpMaterial* material); // 0x812930
const RpMaterial* RpMatFXMaterialGetDualBlendModes(const RpMaterial* material, RwBlendFunction* srcBlendMode, RwBlendFunction* dstBlendMode); // 0x812980
RpMaterial* RpMatFXMaterialSetUVTransformMatrices(RpMaterial* material, RwMatrix* baseTransform, RwMatrix* dualTransform); // 0x8129E0
const RpMaterial* RpMatFXMaterialGetUVTransformMatrices(const RpMaterial* material, RwMatrix* baseTransform, RwMatrix* dualTransform); // 0x812A50
RxPipeline* RpMatFXGetD3D9Pipeline(RpMatFXD3D9Pipeline d3d9Pipeline); // 0x8162F0

/* rpanisot.h */

RwInt8 RpAnisotGetMaxSupportedMaxAnisotropy(void); // 0x748F20
RwTexture* RpAnisotTextureSetMaxAnisotropy(RwTexture* tex, RwInt8 val); // 0x748F30
RwInt8 RpAnisotTextureGetMaxAnisotropy(RwTexture* tex); // 0x748F50
RwBool RpAnisotPluginAttach(void); // 0x748F70

/* rtbmp.h */

RwImage* RtBMPImageWrite(RwImage* image, const RwChar* imageName); // 0x7CE990
RwImage* RtBMPImageRead(const RwChar* imageName); // 0x7CDF60

/* rtpng.h */

RwImage* RtPNGImageWrite(RwImage* image, const RwChar* imageName); // 0x7CF600
RwImage* RtPNGImageRead(const RwChar* imageName); // 0x7CF9B0


void _rpMaterialSetDefaultSurfaceProperties(RwSurfaceProperties *surfProps);

void _rwObjectHasFrameSetFrame(void *object, RwFrame *frame);
void _rwObjectHasFrameReleaseFrame(void *object);


#define RwRenderStateGetMacro(_state, _value)   \
    (RWSRCGLOBAL(dOpenDevice).fpRenderStateGet(_state, _value))

#define RwRenderStateSetMacro(_state, _value)   \
    (RWSRCGLOBAL(dOpenDevice).fpRenderStateSet(_state, _value))

#define RwRenderStateGet(_state, _value) \
        RwRenderStateGetMacro(_state, _value)

#define RwRenderStateSet(_state, _value) \
        RwRenderStateSetMacro(_state, _value)

#define RWRSTATE(a) (reinterpret_cast<void *>(a))

#define rwObjectHasFrameSetFrame(object, frame) \
        _rwObjectHasFrameSetFrame(object, frame)
#define rwObjectHasFrameReleaseFrame(object) \
        _rwObjectHasFrameReleaseFrame(object)
