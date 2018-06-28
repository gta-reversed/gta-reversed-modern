/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "RenderWare.h"

enum eCarPlateType {
    CARPLATE_SF = 0,
    CARPLATE_LV = 1,
    CARPLATE_LA = 2
};

class  CCustomCarPlateMgr {
public:
    static RwTexture *&pCharsetTex;
    static RwTexture **pPlatebackTexTab; // static RwTexture *pPlatebackTexTab[3]
    static void **pPalette1555Tab; // static void *pPalette1555Tab[3] - unused array

    static bool Initialise();
    static bool GeneratePlateText(char* plateTextBuf, int length);
    static bool Shutdown();
    static unsigned char GetMapRegionPlateDesign();
    static bool LoadPlatecharsetDat(char const* filename, unsigned char* data, int arg2, int arg3);
    static RpMaterial* SetupMaterialPlatebackTexture(RpMaterial* material, unsigned char plateType);
    static RwTexture* CreatePlateTexture(char* text, unsigned char plateType);
    static bool SetupClumpAfterVehicleUpgrade(RpClump* clump, RpMaterial* plateMaterial, unsigned char plateType);
    static RpMaterial* SetupMaterialPlateTexture(RpMaterial* material, char* plateText, unsigned char plateType);
    static RpMaterial* SetupClump(RpClump* clump, char* plateText, unsigned char plateType);
};

extern unsigned char *&CharsetLockedData;
extern RpMaterial *&CurrentLicensePlateMaterial;
extern char &CurrentLicensePlateType;

#ifdef _MSC_VER
void GetCharacterPositionInCharSet(char c, unsigned int& outColumn, unsigned int& outRow);
#endif

bool RenderLicenseplateTextToRaster(char* text, RwRaster* charsetRaster, void* palette, RwRaster* resultRaster);
// 'data' is a pointer to RpGeometry
RpMaterial* MaterialUpgradeSetCarplateTextureCB(RpMaterial* material, void* data);
// 'data' is unused
RpAtomic* AtomicUpgradeSetCarplateTextureCB(RpAtomic* atomic, _IGNORED_ void* data);
// 'data' is a plate text (char *)
RpMaterial* MaterialSetCarplateTextureCB(RpMaterial* material, void* data);
// 'data' is a plate text (char *)
RpAtomic* AtomicSetCarplateTextureCB(RpAtomic* atomic, void* data);
