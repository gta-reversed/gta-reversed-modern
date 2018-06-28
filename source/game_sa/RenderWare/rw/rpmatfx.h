/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
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
