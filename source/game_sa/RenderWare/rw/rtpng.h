/***************************************************************************
 *                                                                         *
 * Module  : rtPng.h                                                       *
 *                                                                         *
 * Purpose : Load PNG format files                                         *
 *                                                                         *
 **************************************************************************/

#ifndef RTPNG_H
#define RTPNG_H

/**
 * \defgroup rtpng RtPNG
 * \ingroup imageconversiontools
 *
 * PNG/Portable Network Graphics Image Format Toolkit for RenderWare.
 *
 * See also http://www.libpng.org/pub/png/
 */

/****************************************************************************
 Includes
 */

/*--- Include files ---*/
#include "rwcore.h"

#include "rtpng.rpe"   /* automatically generated header file */

/****************************************************************************
 Function prototypes
 */


RwImage *RtPNGImageWrite(RwImage *image, const RwChar *imageName); // 0x7CF600
RwImage *RtPNGImageRead(const RwChar *imageName);                  // 0x7CF9B0


/* RWPUBLICEND */

#endif /* RTPNG_H */
