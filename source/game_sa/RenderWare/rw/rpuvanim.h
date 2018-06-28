/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
/*****************************************************************************
 *
 * File :     rpuvanim.h
 *
 * Abstract : UV animation
 *
 *****************************************************************************
 *
 * This file is a product of Criterion Software Ltd.
 *
 * This file is provided as is with no warranties of any kind and is
 * provided without any obligation on Criterion Software Ltd. or
 * Canon Inc. to assist in its use or modification.
 *
 * Criterion Software Ltd. will not, under any
 * circumstances, be liable for any lost revenue or other damages arising
 * from the use of this file.
 *
 * Copyright (c) 2000 Criterion Software Ltd.
 * All Rights Reserved.
 *
 * RenderWare is a trademark of Canon Inc.
 *
 *****************************************************************************/

/**
 * \defgroup rpuvanim RpUVAnim
 * \ingroup animtools
 *
 * UV Animation Plugin for RenderWare Graphics.
 */

/*===========================================================================*
 *--- Include files ---------------------------------------------------------*
 *===========================================================================*/
#include "rwcore.h"
#include "rpworld.h"
#include "rtanim.h"
#include "rtdict.h"

#include "rpcriter.h"

/*===========================================================================*
 *--- Global Types ----------------------------------------------------------*
 *===========================================================================*/

/**
 * \ingroup rpuvanim
 * \def RP_UVANIM_MAXSLOTS is the maximum number of separate UV animations
 * that can be applied to a single material
 */
#define RP_UVANIM_MAXSLOTS (8)
/**
 * \ingroup rpuvanim
 * \def RP_UVANIM_APPLIEDCHANNELS is the number of UV channels that will be
 * updated via the default implementation of \ref RpMaterialUVAnimApplyUpdate 
 */
#define RP_UVANIM_APPLIEDCHANNELS (2)

#define RP_UVANIM_FIRST_PASS_CHANNEL (0)
#define RP_UVANIM_DUAL_PASS_CHANNEL (1)
/**
 * \ingroup rpuvanim
 * \def RP_UVANIM_MAXNAME is the maximum number of chars stored in a UV
 * animation name, including the terminating NULL
 */
#define RP_UVANIM_MAXNAME (32)

/*===========================================================================*
 *--- Global variables ------------------------------------------------------*
 *===========================================================================*/

/*===========================================================================*
 *--- Plugin API Functions --------------------------------------------------*
 *===========================================================================*/


/*--- UVAnimPlugin functions ------------------------------------------------*/

/****************************************************************************
 Includes
 */

typedef struct RpUVAnimMaterialGlobalVars RpUVAnimMaterialGlobalVars;

struct RpUVAnimMaterialGlobalVars
{
    RwInt32   engineOffset;
};

typedef struct _rpUVAnimCustomData _rpUVAnimCustomData;

struct _rpUVAnimCustomData   /* Warning - streaming depends on layout */
{
    RwChar name[RP_UVANIM_MAXNAME];
    RwUInt32 nodeToUVChannelMap[RP_UVANIM_MAXSLOTS];
    RwUInt32 refCount;
};

/**
 * \ingroup rpuvanim
 * \ref RpUVAnim
 * typedef for struct RpUVAnim
 */
typedef RtAnimAnimation RpUVAnim;

/**
 * \ingroup rpuvanim
 * \ref RpUVAnimInterpolator
 * typedef for struct RpUVAnimInterpolator
 */
typedef RtAnimInterpolator RpUVAnimInterpolator;

/**
 * \ingroup rpuvanim
 * \ref RpUVAnimKeyFrameType
 * enum delineating the keyframe schemes that may be used
 */
enum RpUVAnimKeyFrameType
{
    rpUVANIMLINEARKEYFRAMES = 0, /**<Linearly interpolated keyframes       */
    rpUVANIMPARAMKEYFRAMES  = 1, /**<Parametrically interpolated keyframes;
                                  **<better for rotations */
    rpUVANIMFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

/**
 * \ingroup rpuvanim
 * \ref RpUVAnimKeyFrameType
 * typedef for enum RpUVAnimKeyFrameType
 */
typedef enum RpUVAnimKeyFrameType RpUVAnimKeyFrameType;

/**
 * \ingroup rpuvanim
 * \ref RpUVAnimLinearKeyFrameData
 * typedef for struct RpUVAnimLinearKeyFrameData
 */
typedef struct RpUVAnimLinearKeyFrameData RpUVAnimLinearKeyFrameData;

/**
 * \ingroup rpuvanim
 * \struct RpUVAnimLinearKeyFrameData
 * A structure representing linear keyframe data.
 */
struct RpUVAnimLinearKeyFrameData
{
    RwReal              uv[6];
                                    /**< UV matrix at keyframe  */
                                    /**<   (matrix) | uv[0] uv[1] - | (right) */
                                    /**<            | uv[2] uv[3] - | (up) */
                                    /**<            |  -     -    - | (at) */
                                    /**<            | uv[4] uv[5] - | (pos) */
                                    /**<The transformed UV texture coordinates will be: */ 
                                    /**<   u' = rx * u + ux * v + px */
                                    /**<   v' = ry * u + uy * v + py */
};

/**
 * \ingroup rpuvanim
 * \ref RpUVAnimParamKeyFrameData
 * typedef for struct RpUVAnimParamKeyFrameData
 */
typedef struct RpUVAnimParamKeyFrameData RpUVAnimParamKeyFrameData;

/**
 * \ingroup rpuvanim
 * \struct RpUVAnimParamKeyFrameData
 * A structure representing paramaterized keyframe data.
 */
struct RpUVAnimParamKeyFrameData
{
    RwReal              theta;  /**< Angle of rotation at keyframe  */
    RwReal              s0;     /**< x-scaling at keyframe  */
    RwReal              s1;     /**< y-scaling at keyframe  */
    RwReal              skew;   /**< skew at keyframe       */
    RwReal              x;      /**< x-position at keyframe */
    RwReal              y;      /**< y-position at keyframe */
};

/**
 * \ingroup rpuvanim
 * \ref RpUVAnimKeyFrameData
 * typedef for union RpUVAnimKeyFrameData
 */
typedef union RpUVAnimKeyFrameData RpUVAnimKeyFrameData;

/**
 * \ingroup rpuvanim
 * \struct RpUVAnimKeyFrameData
 * A union representing linear or paramaterized keyframe data.
 */
union RpUVAnimKeyFrameData
{
    RpUVAnimLinearKeyFrameData linear; /**< Linear format keyframe */
    RpUVAnimParamKeyFrameData param;   /**< Parameterized format keyframe */
};

/**
 * \ingroup rpuvanim
 * \ref RpUVAnimKeyFrame
 * typedef for struct RpUVAnimKeyFrame. Based on \ref RtAnimKeyFrameHeader.
 */
typedef struct RpUVAnimKeyFrame RpUVAnimKeyFrame;

/**
 * \ingroup rpuvanim
 * \struct RpUVAnimKeyFrame
 * A structure representing the standard keyframe data. Sequences of
 * such keyframes in an \ref RtAnimAnimation define the entire UV animation.
 */
struct RpUVAnimKeyFrame
{
    RpUVAnimKeyFrame     *prevFrame; /**< Pointer to the previous keyframe */
    RwReal               time;       /**< Time at keyframe */
    RpUVAnimKeyFrameData data;       /**< Linear or parameterized keyframe data */
};

/**
 * \ingroup rpuvanim
 * \ref RpUVAnimInterpFrame
 * typedef for struct RpUVAnimInterpFrame. Based on \ref RtAnimInterpFrameHeader.
 */
typedef struct RpUVAnimInterpFrame RpUVAnimInterpFrame;

/**
 * \ingroup rpuvanim
 * \struct RpUVAnimInterpFrame
 * A structure representing an interpolated keyframe. The initial part of the
 * structure matches \ref RtAnimInterpFrameHeader.
 */
struct RpUVAnimInterpFrame
{
    RpUVAnimKeyFrame    *keyFrame1;
        /**< Pointer to 1st keyframe of current interpolation pair */
    RpUVAnimKeyFrame    *keyFrame2;
        /**< Pointer to 2nd keyframe of current interpolation pair */
    RpUVAnimKeyFrameData data;  /**< Interpolated keyframe data in a linear
                                  * or parameterized format */
};


/**
 * \ingroup rpuvanim
 * \ref RpUVAnimMaterialExtension typedef for struct RpUVAnimMaterialExtension
 */

typedef struct RpUVAnimMaterialExtension RpUVAnimMaterialExtension;

/**
 * \ingroup rpuvanim
 * \struct RpUVAnimMaterialExtension
 *
 * Used to extend \ref RpMaterial objects, and thus
 * allow the mapping between UV animation and \ref RpMaterial.
 *
 */
struct RpUVAnimMaterialExtension
{
    RwMatrix *uv[RP_UVANIM_APPLIEDCHANNELS];
                /**< Matrices used by the default implementation of */
                /**< \ref RpMaterialUVAnimApplyUpdates to store the updated */
                /**< matrices for the single and dual pass channels */
    RtAnimInterpolator *interp[RP_UVANIM_MAXSLOTS];
                /**< Animations on each UV range. Note that the default  */
                /**< animation functions apply animations to the first   */
                /**< pass and dual pass UV transformations only */ 
};
