/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

/**
 * \defgroup rpskin RpSkin
 * \ingroup skinning
 *
 * Skin Plugin for RenderWare Graphics.
 */

/*===========================================================================*
 *--- Include files ---------------------------------------------------------*
 *===========================================================================*/
#include "rwcore.h"
#include "rpworld.h"

#include "rpcriter.h"

#include "rphanim.h"

/*===========================================================================*
 *--- Global Types ----------------------------------------------------------*
 *===========================================================================*/
typedef struct RwMatrixWeights RwMatrixWeights;

/**
 * \ingroup rpskin
 * \struct RwMatrixWeights
 * A structure for defining up to four matrix weights per vertex.
 * Not all entries need to be used.
 *
 * \note
 * Values should be sorted, such that any zero 0.0f entries appear
 * after the valid weights. Any weights that appear after a zero
 * entry will be ignored.
 *
 * \see RpSkinCreate
 */
struct RwMatrixWeights
{
    RwReal w0; /**< The first matrix weight.  */
    RwReal w1; /**< The second matrix weight. */
    RwReal w2; /**< The third matrix weight.  */
    RwReal w3; /**< The fourth matrix weight. */
};

/**
 * \ingroup rpskin
 * \struct RpSkin
 *
 * Skin object. This should be considered an opaque type.
 * Use the RpSkin API functions to access.
 *
 * \see RpSkinCreate
 * \see RpSkinDestroy
 */
typedef struct RpSkin RpSkin;

/*---------------------------------------------------------------------------*
 *-   Skin pipeline                                                         -*
 *---------------------------------------------------------------------------*/

/**
 * \ingroup rpskin
 * \ref RpSkinType defines the different ways a skinned atomic can
 * be rendered. Once a skinned \ref RpGeometry has been attached to
 * an \ref RpAtomic the atomic must be setup with the correct skin
 * rendering pipeline with \ref RpSkinAtomicSetType.
 */
enum RpSkinType
{
    rpNASKINTYPE        = 0, /**<Invalid skin pipeline.           */
    rpSKINTYPEGENERIC   = 1, /**<Generic skin rendering.          */
    rpSKINTYPEMATFX     = 2, /**<Material effects skin rendering. */
    rpSKINTYPETOON      = 3, /**<Toon skin rendering.   To use this 
                               * flag the \ref rptoon plugin (part 
                               * of the FX Pack) needs to be 
                               * installed.          */
    rpSKINTYPEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RpSkinType RpSkinType;

/**
 * \defgroup rpskind3d9 D3D9
 * \ingroup rpskin
 *
 * D3D9 skin pipeline extension.
 */

/**
 * \defgroup rpskind3d9features Features
 * \ingroup rpskind3d9
 *
 * D3D9 skin pipeline features.
 */

/**
 * \defgroup rpskind3d9restrictions Restrictions
 * \ingroup rpskind3d9
 *
 * D3D9 skin pipeline restrictions.
 */


/*===========================================================================*
 *--- D3D9 Defines -----------------------------------------------------------*
 *===========================================================================*/

/*===========================================================================*
 *--- D3D9 Global Types ------------------------------------------------------*
 *===========================================================================*/

/**
 * \ingroup rpskind3d9
 * \ref RpSkinD3D9Pipeline rendering pipelines available within
 * the \ref RpSkin plugin. Use \ref RpSkinGetD3D9Pipeline to
 * retrieve the \ref RxPipeline's.
 */
enum RpSkinD3D9Pipeline
{
    rpNASKIND3D9PIPELINE              = 0,
    rpSKIND3D9PIPELINEGENERIC         = 1,
    /**<D3D9 generic skin rendering pipeline.                           */
    rpSKIND3D9PIPELINEMATFX           = 2,
    /**<D3D9 material effect skin rendering pipeline.                   */
    rpSKIND3D9PIPELINETOON            = 3,
    /**<D3D9 toon skin rendering pipeline.                              */
    rpSKIND3D9PIPELINEMATFXTOON       = 4,
    /**<D3D9 toon matfx skin rendering pipeline not supported           */
    rpSKIND3D9PIPELINEMAX,
    rpSKIND3D9PIPELINEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RpSkinD3D9Pipeline RpSkinD3D9Pipeline;
