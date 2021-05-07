/***************************************************************************
 *                                                                         *
 * Module  : rtBMP.h                                                       *
 *                                                                         *
 * Purpose : Load BMP format files                                         *
 *                                                                         *
 **************************************************************************/

#ifndef RTBMP_H
#define RTBMP_H

/**
 * \defgroup rtbmp RtBMP
 * \ingroup imageconversiontools
 *
 * BMP Image Format Toolkit for RenderWare.
 *
 * See also http://www.daubnet.com/formats/BMP.html
 */

/****************************************************************************
 Includes
 */

/*--- Include files ---*/
#include "rwcore.h"

#include "rtbmp.rpe"   /* automatically generated header file */

/****************************************************************************
 Function prototypes
 */

RwImage* RtBMPImageWrite(RwImage* image, const RwChar* imageName); // 0x7CE990
RwImage* RtBMPImageRead(const RwChar* imageName);                  // 0x7CDF60

#endif /* RTBMP_H */