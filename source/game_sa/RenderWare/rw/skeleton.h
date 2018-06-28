/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
/****************************************************************************
 *
 * skeleton.h
 *
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
 * Copyright (c) 1999, 2000 Criterion Software Ltd.
 * All Rights Reserved.
 *
 */
#include "rwcore.h"
#include <Windows.h>

/* Default arena size depending on platform. */

#if (defined(SKY))
#define rsRESOURCESDEFAULTARENASIZE (8 << 20)
#elif (defined(_XBOX))
#define rsRESOURCESDEFAULTARENASIZE (8 << 20)
#elif (defined(DOLPHIN))
#define rsRESOURCESDEFAULTARENASIZE (4 << 20)
#elif (defined(D3D8_DRVMODEL_H))
#define rsRESOURCESDEFAULTARENASIZE (4 << 20)
#elif (defined(D3D9_DRVMODEL_H))
#define rsRESOURCESDEFAULTARENASIZE (4 << 20)
#elif (defined(OPENGL_DRVMODEL_H))
#if (defined(macintosh))
#define rsRESOURCESDEFAULTARENASIZE (2 << 20)
#else
#define rsRESOURCESDEFAULTARENASIZE (16 << 20)
#endif
#else
#define rsRESOURCESDEFAULTARENASIZE (16 << 20)
#endif

enum RsInputDeviceType
{
    rsKEYBOARD,
    rsMOUSE,
    rsPAD
};
typedef enum RsInputDeviceType RsInputDeviceType;

enum RsEventStatus
{
    rsEVENTERROR,
    rsEVENTPROCESSED,
    rsEVENTNOTPROCESSED
};
typedef enum RsEventStatus RsEventStatus;

enum RsEvent
{
#ifdef RWSPLASH
    rsDISPLAYSPLASH,
#endif
    rsCAMERASIZE,
    rsCOMMANDLINE,
    rsFILELOAD,
    rsINITDEBUG,
    rsINPUTDEVICEATTACH,
    rsLEFTBUTTONDOWN,
    rsLEFTBUTTONUP,
    rsMOUSEMOVE,
    rsMOUSEWHEELMOVE,
    rsPLUGINATTACH,
    rsREGISTERIMAGELOADER,
    rsRIGHTBUTTONDOWN,
    rsRIGHTBUTTONUP,
    rsRWINITIALIZE,
    rsRWTERMINATE,
    rsSELECTDEVICE,
    rsINITIALIZE,
    rsTERMINATE,
    rsIDLE,
    rsKEYDOWN,
    rsKEYUP,
    rsQUITAPP,
    rsPADBUTTONDOWN,
    rsPADBUTTONUP,
    rsPADANALOGUELEFT,
    rsPADANALOGUELEFTRESET,
    rsPADANALOGUERIGHT,
    rsPADANALOGUERIGHTRESET,
    rsPREINITCOMMANDLINE,
    rsACTIVATE,
    rsSETMEMORYFUNCS
};
typedef enum RsEvent RsEvent;

typedef RsEventStatus (*RsInputEventHandler)(RsEvent event, void *param);

typedef struct RsInputDevice RsInputDevice;
struct RsInputDevice
{
    RsInputDeviceType inputDeviceType;
    RwBool used;
    RsInputEventHandler inputEventHandler;
};

struct psGlobalType
{
    HWND      window;
    HINSTANCE instance;
    RwBool    fullScreen;
    RwV2d     lastMousePos;
    int       field_14;
    void*     diInterface;
    void*     diMouse;
    void*     diDevice1;
    void*     diDevice2;
};

typedef struct RsGlobalType RsGlobalType;
struct RsGlobalType
{
    const RwChar *appName;
    RwInt32 maximumWidth;
    RwInt32 maximumHeight;
    RwInt32 frameLimit;
    RwBool  quit;

    psGlobalType   *ps; /* platform specific data */

    RsInputDevice keyboard;
    RsInputDevice mouse;
    RsInputDevice pad;
};

typedef struct RsMouseStatus RsMouseStatus;
struct RsMouseStatus
{
    RwV2d   pos;
    RwV2d   delta;
    RwBool  shift;
    RwBool  control;
#if defined(macintosh)
    RwBool  alt;
#endif /* defined(macintosh) */
};

enum RsKeyCodes
{
    rsESC       = 128,

    rsF1        = 129,
    rsF2        = 130,
    rsF3        = 131,
    rsF4        = 132,
    rsF5        = 133,
    rsF6        = 134,
    rsF7        = 135,
    rsF8        = 136,
    rsF9        = 137,
    rsF10       = 138,
    rsF11       = 139,
    rsF12       = 140,

    rsINS       = 141,
    rsDEL       = 142,
    rsHOME      = 143,
    rsEND       = 144,
    rsPGUP      = 145,
    rsPGDN      = 146,

    rsUP        = 147,
    rsDOWN      = 148,
    rsLEFT      = 149,
    rsRIGHT     = 150,

    rsPADINS    = 151,
    rsPADDEL    = 152,
    rsPADHOME   = 153,
    rsPADEND    = 154,
    rsPADPGUP   = 155,
    rsPADPGDN   = 156,

    rsPADUP     = 157,
    rsPADDOWN   = 158,
    rsPADLEFT   = 159,
    rsPADRIGHT  = 160,

    rsNUMLOCK   = 161,
    rsDIVIDE    = 162,
    rsTIMES     = 163,
    rsMINUS     = 164,
    rsPLUS      = 165,
    rsPADENTER  = 166,
    rsPAD5      = 167,

    rsBACKSP    = 168,
    rsTAB       = 169,
    rsCAPSLK    = 170,
    rsENTER     = 171,
    rsLSHIFT    = 172,
    rsRSHIFT    = 173,
    rsLCTRL     = 174,
    rsRCTRL     = 175,
    rsLALT      = 176,
    rsRALT      = 177,

    rsNULL       = 255
};
typedef enum RsKeyCodes RsKeyCodes;

typedef struct RsKeyStatus RsKeyStatus;
struct RsKeyStatus
{
    RwInt32     keyScanCode;
    RwInt32     keyCharCode;
#if defined(macintosh)
    RwBool      shift;
    RwBool      control;
    RwBool      alt;
#endif /* defined(macintosh) */
};

typedef struct RsPadButtonStatus RsPadButtonStatus;
struct RsPadButtonStatus
{
    RwInt32     padID;
    RwUInt32    padButtons;
};

enum RsPadButtons
{
    rsPADDPADLEFT   = 0x00000001,
    rsPADDPADRIGHT  = 0x00000002,
    rsPADDPADUP     = 0x00000004,
    rsPADDPADDOWN   = 0x00000008,
    rsPADSTART      = 0x00000010,
    rsPADSELECT     = 0x00000020,
    rsPADBUTTON1    = 0x00000040,
    rsPADBUTTON2    = 0x00000080,
    rsPADBUTTON3    = 0x00000100,
    rsPADBUTTON4    = 0x00000200,
    rsPADBUTTON5    = 0x00000400,
    rsPADBUTTON6    = 0x00000800,
    rsPADBUTTON7    = 0x00001000,
    rsPADBUTTON8    = 0x00002000,
    rsPADBUTTONA1   = 0x00004000,
    rsPADBUTTONA2   = 0x00008000
};
typedef enum RsPadButtons RsPadButtons;

enum RsPrintPos
{
    rsPRINTPOSMIDDLE    = 0,

    rsPRINTPOSLEFT   = 1,
    rsPRINTPOSRIGHT  = 2,
    rsPRINTPOSTOP    = 4,
    rsPRINTPOSBOTTOM = 8,

    rsPRINTPOSTOPLEFT     = rsPRINTPOSTOP    | rsPRINTPOSLEFT,
    rsPRINTPOSTOPRIGHT    = rsPRINTPOSTOP    | rsPRINTPOSRIGHT,
    rsPRINTPOSBOTTOMLEFT  = rsPRINTPOSBOTTOM | rsPRINTPOSLEFT,
    rsPRINTPOSBOTTOMRIGHT = rsPRINTPOSBOTTOM | rsPRINTPOSRIGHT,

    rsPRINTPOSFORCENUMSIZEINT = 0x7FFFFFFF
};
typedef enum RsPrintPos RsPrintPos;

/* Screen margins in charset width/height units, used w/ RsPrintPos */
enum RsPrintMargin
{
    rsPRINTMARGINMIDDLE = 0,

#if ((defined(SKY2_DRVMODEL_H)) || (defined(GCN_DRVMODEL_H)) || (defined(XBOX_DRVMODEL_H)))
    rsPRINTMARGINTOP    = 2,
    rsPRINTMARGINBOTTOM = 4,
    rsPRINTMARGINLEFT   = 5,
    rsPRINTMARGINRIGHT  = 5,
#else /* ((defined(SKY2_DRVMODEL_H)) || (defined(GCN_DRVMODEL_H)) || (defined(XBOX_DRVMODEL_H)) */
    rsPRINTMARGINTOP    = 1,
    rsPRINTMARGINBOTTOM = 1,
    rsPRINTMARGINLEFT   = 1,
    rsPRINTMARGINRIGHT  = 1,
#endif /* ((defined(SKY2_DRVMODEL_H)) || (defined(GCN_DRVMODEL_H)) || (defined(XBOX_DRVMODEL_H)) */
    rsPRINTMARGINFORCENUMSIZEINT = 0x7FFFFFFF
};
typedef enum RsPrintMargin RsPrintMargin;
