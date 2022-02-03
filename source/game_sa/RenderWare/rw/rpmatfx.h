/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

/*===========================================================================*
 *--- Include files ---------------------------------------------------------*
 *===========================================================================*/

#include "rwcore.h"
#include "rpworld.h"

/*---- start: ./matfx.h----*/


/**
 * \defgroup rpmatfx RpMatFX
 * \ingroup materials
 *
 * Material Effects Plugin for RenderWare Graphics.
 */

/*===========================================================================*
 *--- Global Types ----------------------------------------------------------*
 *===========================================================================*/

/**
 * \ingroup rpmatfx
 * RpMatFXMaterialFlags, this type represents the different types of
 * material effects that can be used on a material. The effects are
 * initialized with \ref RpMatFXMaterialSetEffects:
 */
enum RpMatFXMaterialFlags
{
    rpMATFXEFFECTNULL            = 0, /**<No material effect.           */
    rpMATFXEFFECTBUMPMAP         = 1, /**<Bump mapping                  */
    rpMATFXEFFECTENVMAP          = 2, /**<Environment mapping           */
    rpMATFXEFFECTBUMPENVMAP      = 3, /**<Bump and environment mapping  */
    rpMATFXEFFECTDUAL            = 4, /**<Dual pass                     */
    rpMATFXEFFECTUVTRANSFORM     = 5, /**<Base UV transform             */
    rpMATFXEFFECTDUALUVTRANSFORM = 6, /**<Dual UV transform (2 pass)    */

    rpMATFXEFFECTMAX,
    rpMATFXNUMEFFECTS       = rpMATFXEFFECTMAX - 1,

    rpMATFXFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RpMatFXMaterialFlags  RpMatFXMaterialFlags;

/**
 * \defgroup rpmatfxd3d9 D3D9
 * \ingroup rpmatfx
 *
 * D3D9 specific documentation.
 */


/******************************************************************************
 *  Enum types
 */

/**
 * \ingroup rpmatfxd3d9
 * \ref RpMatFXD3D9Pipeline
 */
enum RpMatFXD3D9Pipeline
{
    rpNAMATFXD3D9PIPELINE          = 0,
    rpMATFXD3D9ATOMICPIPELINE      = 1, /**<D3D9 atomic material effect rendering pipeline. */
    rpMATFXD3D9WORLDSECTORPIPELINE = 2, /**<D3D9 world sector material effect rendering pipeline. */
    rpMATFXD3D9PIPELINEMAX,
    rpMATFXD3D9PIPELINEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RpMatFXD3D9Pipeline RpMatFXD3D9Pipeline;

void RpMatFXMaterialDataSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc); // 0x810700
RwBool RpMatFXPluginAttach(); // 0x810AA0
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
