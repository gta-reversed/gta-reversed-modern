/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
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

#include <math.h>
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
