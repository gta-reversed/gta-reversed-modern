/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
/******************************************
 *                                        *
 *    RenderWare(TM) Graphics Library     *
 *                                        *
 ******************************************/

/*
 * This file is a product of Criterion Software Ltd.
 *
 * This file is provided as is with no warranties of any kind and is
 * provided without any obligation on Criterion Software Ltd.
 * or Canon Inc. to assist in its use or modification.
 *
 * Criterion Software Ltd. and Canon Inc. will not, under any
 * circumstances, be liable for any lost revenue or other damages
 * arising from the use of this file.
 *
 * Copyright (c) 1998. Criterion Software Ltd.
 * All Rights Reserved.
 */

/***************************************************************************
 *                                                                         *
 * Module  : rpanim.h                                                      *
 *                                                                         *
 * Purpose : Hierarchical animation                                        *
 *                                                                         *
 **************************************************************************/

/**
 * Hierarchal animation plugin
 */

/* Doxygen plugin groups. */

/**
 * \defgroup rphanim RpHAnim
 * \ingroup objectframehanim
 *
 * Hierarchical Animation Plugin for RenderWare Graphics.
 */

/**
 * \defgroup rphanimchanges RpHAnim Changes
 * \ingroup rphanim
 *
 */

/****************************************************************************
 Includes
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rwcore.h"
#include "rpworld.h"

#include "rpcriter.h"          /* Note: each vendor can choose their own method for
                                * allocation of unique ID's. This file defines
                                * the ID's used by Criterion.
                                */
#include "rtquat.h"
#include "rtanim.h"

#define rpHANIMSTREAMCURRENTVERSION 0x100

#if (!defined(DOXYGEN))

typedef struct RpHAnimAtomicGlobalVars RpHAnimAtomicGlobalVars;

struct RpHAnimAtomicGlobalVars
{
        RwInt32   engineOffset;
        RwFreeList *HAnimFreeList;
};

#endif /* (!defined(DOXYGEN)) */

#define rpHANIMSTDKEYFRAMESIZE sizeof(RpHAnimKeyFrame)
#define rpHANIMSTDKEYFRAMETYPEID 0x1

#define RpV3dInterpolate(o,a,s,b)                            \
MACRO_START                                                     \
{                                                               \
    (o)->x = (((a)->x) + ((s)) * (((b)->x) - ((a)->x)));        \
    (o)->y = (((a)->y) + ((s)) * (((b)->y) - ((a)->y)));        \
    (o)->z = (((a)->z) + ((s)) * (((b)->z) - ((a)->z)));        \
}                                                               \
MACRO_STOP


/**
 * \ingroup rphanim
 * \ref RpHAnimKeyFrame
 * typedef for struct RpHAnimKeyFrame. Based on \ref RtAnimKeyFrameHeader.
 */
typedef struct RpHAnimKeyFrame RpHAnimKeyFrame;

/**
 * \ingroup rphanim
 * \struct RpHAnimKeyFrame
 * A structure representing the standard keyframe data. Sequences of
 * such keyframes in an \ref RtAnimAnimation defines the animation of each
 * node in a hierarchy.
 */
struct RpHAnimKeyFrame
{
    RpHAnimKeyFrame    *prevFrame;  /**< Pointer to the previous keyframe */
    RwReal              time;       /**< Time at keyframe */
    RtQuat              q;          /**< Quaternion rotation at keyframe  */
    RwV3d               t;          /**< Translation at keyframe  */
};

/**
 * \ingroup rphanim
 * \ref RpHAnimInterpFrame
 * typedef for struct RpHAnimInterpFrame. Based on \ref RtAnimInterpFrameHeader.
 */
typedef struct RpHAnimInterpFrame RpHAnimInterpFrame;

/**
 * \ingroup rphanim
 * \struct RpHAnimInterpFrame
 * A structure representing an interpolated keyframe. The initial part of the
 * structure matches \ref RtAnimInterpFrameHeader.
 */
struct RpHAnimInterpFrame
{
    RpHAnimKeyFrame    *keyFrame1;
        /**< Pointer to 1st keyframe of current interpolation pair */
    RpHAnimKeyFrame    *keyFrame2;
        /**< Pointer to 2nd keyframe of current interpolation pair */
    RtQuat              q;          /**< Quaternion rotation */
    RwV3d               t;          /**< Translation */
};

/**
 * \ingroup rphanim
 * \ref RpHAnimHierarchy typedef for struct RpHAnimHierarchy
 */
typedef struct RpHAnimHierarchy RpHAnimHierarchy;

/* Flags for FrameInfos */

#define rpHANIMPOPPARENTMATRIX      0x01
#define rpHANIMPUSHPARENTMATRIX     0x02

/**
 * \ingroup rphanim
 * \ref RpHAnimNodeInfo
 * typedef for struct RpHAnimNodeInfo
 */
typedef struct RpHAnimNodeInfo RpHAnimNodeInfo;

/**
 * \ingroup rphanim
 * \struct RpHAnimNodeInfo
 *
 * Used to describe a hierarchy toplogy.
 * It holds flags representing its position in the
 * hierarchy as well as a pointer to the matching \ref RwFrame if the
 * hierarchy has been attached to a \ref RwFrame hierarchy.
 *
 */
struct RpHAnimNodeInfo
{
    RwInt32     nodeID;     /**< User defined ID for this node  */
    RwInt32     nodeIndex;  /**< Array index of node  */
    RwInt32     flags;      /**< Matrix push/pop flags  */
    RwFrame *   pFrame;     /**< Pointer to an attached RwFrame (see \ref RpHAnimHierarchyAttach) */
};

/**
 * \ingroup rphanim
 * \ref RpHAnimHierarchyFlag defines type and update modes in HAnimHierarchies
 */
enum RpHAnimHierarchyFlag
{
    /* creation flags */
    rpHANIMHIERARCHYSUBHIERARCHY =              0x01, /**< This hierarchy is a sub-hierarchy */
    rpHANIMHIERARCHYNOMATRICES =                0x02, /**< This hierarchy has no local matrices */

    /* update flags */
    rpHANIMHIERARCHYUPDATEMODELLINGMATRICES = 0x1000, /**< This hierarchy updates modeling matrices */
    rpHANIMHIERARCHYUPDATELTMS =              0x2000, /**< This hierarchy updates LTMs */
    rpHANIMHIERARCHYLOCALSPACEMATRICES =      0x4000, /**< This hierarchy calculates matrices in a space
                                                           relative to its root */

    rpHANIMHIERARCHYFLAGFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

/*
 * These flags are used to control the creation and
 * update status of the hierarchy
 */
typedef enum RpHAnimHierarchyFlag RpHAnimHierarchyFlag;

/**
 * \ingroup rphanim
 * \struct RpHAnimHierarchy
 * An RpHAnimHierarchy is used to "play back" an animation.
 *
 * The structure of a hierarchy is defined by an array
 * of \ref RpHAnimNodeInfo structures.
 *
 * The hierarchy is defined by running through the node array in order,
 * pushing the parent-node's matrix whenever a child is reached that has
 * more than one sibling, and popping the parent matrix when a "leaf"
 * node is encountered.
 *
 */
struct RpHAnimHierarchy
{
    RwInt32             flags;          /**< Flags for the hierarchy  */
    RwInt32             numNodes;      /**< Number of nodes in the hierarchy  */

    RwMatrix           *pMatrixArray;   /**< Pointer to node matrices*/
    void               *pMatrixArrayUnaligned; /**< Pointer to memory used for node matrices
                                                * from which the aligned pMatrixArray is allocated */
    RpHAnimNodeInfo    *pNodeInfo;     /**< Array of node information (push/pop flags etc) */
    RwFrame            *parentFrame;    /**< Pointer to the Root RwFrame of the hierarchy this
                                           * RpHAnimHierarchy represents */
    RpHAnimHierarchy   *parentHierarchy;                       /**< Internal use */
    RwInt32             rootParentOffset;                      /**< Internal use */

    RtAnimInterpolator   *currentAnim;                    /**< Internal use */
};

/**
 * \ingroup rphanim
 * \ref RpHAnimFrameExtension typedef for struct RpHAnimFrameExtension
 */

typedef struct RpHAnimFrameExtension RpHAnimFrameExtension;

/**
 * \ingroup rphanim
 * \struct RpHAnimFrameExtension
 *
 * Used to extend \ref RwFrame objects, and thus
 * allow the mapping between animation hierarchy node ID and \ref RwFrame.
 *
 */
struct RpHAnimFrameExtension
{
    RwInt32          id;         /**< ID given to this RwFrame (default of -1) */
    RpHAnimHierarchy *hierarchy; /**< Pointer to Animation hierarchy attached to this RwFrame */
};

/* Legacy TypeDef */


typedef RtAnimAnimation RpHAnimAnimation;
typedef RpHAnimKeyFrame RpHAnimStdKeyFrame;

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
RwBool RpHAnimPluginAttach(); // 0x7C4600
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
