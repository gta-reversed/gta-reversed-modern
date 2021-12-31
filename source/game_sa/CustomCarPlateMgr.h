/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "RenderWare.h"

enum eCarPlateType {
    CARPLATE_SF = 0,
    CARPLATE_LV = 1,
    CARPLATE_LA = 2
};

class CCustomCarPlateMgr {
public:
    static inline RwTexture*& pCharsetTex = *(RwTexture**)0xC3EF5C;
    static inline RwTexture* (&pPlatebackTexTab)[3] = *(RwTexture*(*)[3])0xC3EF60;
    static void** pPalette1555Tab;       // static void *pPalette1555Tab[3] - unused array
    static inline RwUInt8*& pCharsetLockedData = *(RwUInt8**)0x6FD597;
public:
    static void InjectHooks();

    static bool Initialise();
    static int8_t GeneratePlateText(char* buf, int32_t len);
    static void Shutdown();
    static int8_t GetMapRegionPlateDesign();
    static int8_t LoadPlatecharsetDat(char const* filename, uint8_t* data);
    static RpMaterial* SetupMaterialPlatebackTexture(RpMaterial* material, uint8_t plateType);
    static RwTexture* CreatePlateTexture(char* text, uint8_t plateType);
    static int8_t SetupClumpAfterVehicleUpgrade(RpClump* clump, RpMaterial* plateMaterial, uint8_t plateType);
    static RwTexture* SetupMaterialPlateTexture(RpMaterial* material, char* plateText, uint8_t plateType);
    static RpMaterial* SetupClump(RpClump* clump, char* plateText, uint8_t plateType);
};

extern uint8*& CharsetLockedData;
extern RpMaterial*& CurrentLicensePlateMaterial;
extern char& CurrentLicensePlateType;

#ifdef _MSC_VER
void GetCharacterPositionInCharSet(char c, uint32& outColumn, uint32& outRow);
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
