/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
/*
 * Data structures for Quaternions
 * See http://www-groups.dcs.st-and.ac.uk/~history/Mathematicians/Hamilton.html
 *
 * Copyright (c) Criterion Software Limited
 */

/**
 * \defgroup rtquat RtQuat
 * \ingroup mathtools
 *
 * Quaternion Toolkit for RenderWare.
 *
 * See also http://www.gamasutra.com/features/19980703/quaternions_01.htm
 */

/*
 * See http://www-groups.dcs.st-and.ac.uk/~history/Mathematicians/Hamilton.html
 * On 16 October 1843 (a Monday) Hamilton was walking in along the Royal
 * Canal with his wife to preside at a Council meeting of the Royal Irish
 * Academy.
 * 
 * Although his wife talked to him now and again Hamilton hardly
 * heard, for the discovery of the quaternions, the first noncommutative
 * algebra to be studied, was taking shape in his mind:-
 * 
 *    "And here there dawned on me the notion that we must admit, in
 *     some sense, a fourth dimension of space for the purpose of calculating
 *     with triples ...  An electric circuit seemed to close, and a spark
 *     flashed forth."
 */


/****************************************************************************
 Includes
 */

#include <cmath>

/* renderware */
#include "rwcore.h"

#define RW_TOL_ORTHONORMAL  ((RwReal)0.01)

/****************************************************************************
 Global Types
 */


typedef struct RtQuat RtQuat;
/**
 * \ingroup rtquat
 * \struct RtQuat 
 * A structure describing a Quaternion
 *
*/ 
struct RtQuat
{
    RwV3d               imag;   /**< The imaginary part(s) */
    RwReal              real;   /**< The real part */
};

/*
 * Backwards compatibility code
 */

typedef RtQuat RpQuat;

void RtQuatConvertToMatrix(const RtQuat* const qpQuat, RwMatrix* const mpMatrix);
RwBool RtQuatConvertFromMatrix(RtQuat * qpQuat, const RwMatrix * const mpMatrix); // 0x7EB5C0
RtQuat* RtQuatRotate(RtQuat* quat, const RwV3d* axis, RwReal angle, RwOpCombineType combineOp); // 0x7EB7C0
const RtQuat* RtQuatQueryRotate(const RtQuat* quat, RwV3d* unitAxis, RwReal* angle); // 0x7EBA80
RwV3d* RtQuatTransformVectors(RwV3d* vectorsOut, const RwV3d* vectorsIn, const RwInt32 numPoints, const RtQuat* quat); // 0x7EBBB0
RwReal RtQuatModulus(RtQuat* q); // 0x7EBD10

#define RtQuatUnitConvertToMatrixMacro(qpQuat, mpMatrix)                   \
MACRO_START                                                                \
{                                                                          \
    const RwReal        x = (qpQuat)->imag.x;                              \
    const RwReal        y = (qpQuat)->imag.y;                              \
    const RwReal        z = (qpQuat)->imag.z;                              \
    const RwReal        w = (qpQuat)->real;                                \
    RwV3d               square;                                            \
    RwV3d               cross;                                             \
    RwV3d               wimag;                                             \
                                                                           \
    square.x = x * x;                                                      \
    square.y = y * y;                                                      \
    square.z = z * z;                                                      \
                                                                           \
    cross.x = y * z;                                                       \
    cross.y = z * x;                                                       \
    cross.z = x * y;                                                       \
                                                                           \
    wimag.x = w * x;                                                       \
    wimag.y = w * y;                                                       \
    wimag.z = w * z;                                                       \
                                                                           \
    (mpMatrix)->right.x = 1 - 2 * (square.y + square.z);                   \
    (mpMatrix)->right.y = 2 * (cross.z + wimag.z);                         \
    (mpMatrix)->right.z = 2 * (cross.y - wimag.y);                         \
                                                                           \
    (mpMatrix)->up.x = 2 * (cross.z - wimag.z);                            \
    (mpMatrix)->up.y = 1 - 2 * (square.x + square.z);                      \
    (mpMatrix)->up.z = 2 * (cross.x + wimag.x);                            \
                                                                           \
    (mpMatrix)->at.x = 2 * (cross.y + wimag.y);                            \
    (mpMatrix)->at.y = 2 * (cross.x - wimag.x);                            \
    (mpMatrix)->at.z = (1 - 2 * (square.x + square.y));                    \
                                                                           \
    /* Set position */                                                     \
    (mpMatrix)->pos.x = ((RwReal) 0);                                      \
    (mpMatrix)->pos.y = ((RwReal) 0);                                      \
    (mpMatrix)->pos.z = ((RwReal) 0);                                      \
                                                                           \
    /* Matrix is orthonormal */                                            \
    rwMatrixSetFlags((mpMatrix),                                           \
                      (rwMATRIXTYPEORTHONORMAL  &                          \
                       ~rwMATRIXINTERNALIDENTITY) );                       \
}                                                                          \
MACRO_STOP

#define RtQuatUnitConvertToMatrix(qpQuat, mpMatrix)                        \
    RtQuatUnitConvertToMatrixMacro(qpQuat, mpMatrix)    
