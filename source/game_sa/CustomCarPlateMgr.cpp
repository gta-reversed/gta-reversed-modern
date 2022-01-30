#include "StdInc.h"
#include <format>

void CCustomCarPlateMgr::InjectHooks() {
    RH_ScopedClass(CCustomCarPlateMgr);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(Initialise, 0x6FD500);
    RH_ScopedInstall(GeneratePlateText, 0x6FD5B0);
    RH_ScopedInstall(Shutdown, 0x6FD720);
    RH_ScopedInstall(GetMapRegionPlateDesign, 0x6FD7A0);
    RH_ScopedInstall(LoadPlatecharsetDat, 0x6FDC00);
    RH_ScopedInstall(SetupMaterialPlatebackTexture, 0x6FDE50);
    RH_ScopedInstall(CreatePlateTexture, 0x6FDEA0);
    RH_ScopedInstall(SetupClumpAfterVehicleUpgrade, 0x6FDFE0);
    RH_ScopedInstall(SetupMaterialPlateTexture, 0x6FE020);
    RH_ScopedInstall(SetupClump, 0x6FE0F0);
}

// 0x6FD500
bool CCustomCarPlateMgr::Initialise() {
    {
        const auto txd = CTxdStore::FindTxdSlot("vehicle");
        CTxdStore::PushCurrentTxd();
        CTxdStore::SetCurrentTxd(txd);
    }

    const auto FindTXDAndSetFlags = [](const char* name, RwTextureFilterMode filterMode) {
        const auto tex =RwTextureRead(name, nullptr);
        RwTextureSetAddressingU(tex, rwFILTERMIPNEAREST);
        RwTextureSetAddressingV(tex, rwFILTERMIPNEAREST);
        RwTextureSetFilterMode(tex, filterMode);
        return tex;
    };

    pCharsetTex = FindTXDAndSetFlags("platecharset", RwTextureFilterMode::rwFILTERNEAREST);

    const char* texNames[] = {"plateback1", "plateback2", "plateback3"};
    for (uint32 i = 0; i < std::size(texNames); i++) {
        pPlatebackTexTab[i] = FindTXDAndSetFlags(texNames[i], RwTextureFilterMode::rwFILTERLINEAR);
    }

    CTxdStore::PopCurrentTxd();

    pCharsetLockedData = RwRasterLock(RwTextureGetRaster(pCharsetTex), 0, rwRASTERLOCKREAD);

    return !!pCharsetLockedData;
}

// 0x6FD720
void CCustomCarPlateMgr::Shutdown() {
    if (pCharsetTex) {
        RwRasterUnlock(RwTextureGetRaster(pCharsetTex));
        pCharsetLockedData = nullptr;

        RwTextureDestroy(pCharsetTex);
        pCharsetTex = nullptr;
    }

    for (auto& tex : pPlatebackTexTab) {
        if (tex) {
            RwTextureDestroy(tex);
            tex = nullptr;
        }
    }

    if (const auto slot = CTxdStore::FindTxdSlot("vehicle"); slot != -1)
        CTxdStore::RemoveTxd(slot);
}

// 0x6FD7A0
int8_t CCustomCarPlateMgr::GetMapRegionPlateDesign() {
    switch (CWeather::WeatherRegion) {
    case eWeatherRegion::WEATHER_REGION_LA:
        return 2;
    case eWeatherRegion::WEATHER_REGION_LV:
    case eWeatherRegion::WEATHER_REGION_DESERT:
        return 1;
    case eWeatherRegion::WEATHER_REGION_DEFAULT:
    case eWeatherRegion::WEATHER_REGION_SF:
        return 0;
    }
}

// 0x6FDC00
// Unused
int8_t CCustomCarPlateMgr::LoadPlatecharsetDat(char const* filename, uint8_t* data) {
    return plugin::CallAndReturn<int8_t, 0x6FDC00, char const*, uint8_t*>(filename, data);
}

auto ResolvePlateType(uint8 plateType) {
    return plateType == -1 ? CCustomCarPlateMgr::GetMapRegionPlateDesign() : plateType;
}

// 0x6FDE50
void CCustomCarPlateMgr::SetupMaterialPlatebackTexture(RpMaterial* material, uint8_t plateType) {
    RpMaterialSetTexture(material, pPlatebackTexTab[ResolvePlateType(plateType)]);
}

void CCustomCarPlateMgr::GetCharacterPositionInCharSet(char c, uint32& outColumn, uint32& outRow) {
    switch (c)
    {
    case '0':
        outColumn = 2;
        outRow = 6;
        break;
    case '1':
        outColumn = 3;
        outRow = 6;
        break;
    case '2':
        outColumn = 0;
        outRow = 7;
        break;
    case '3':
        outColumn = 1;
        outRow = 7;
        break;
    case '4':
        outColumn = 2;
        outRow = 7;
        break;
    case '5':
        outColumn = 3;
        outRow = 7;
        break;
    case '6':
        outColumn = 0;
        outRow = 8;
        break;
    case '7':
        outColumn = 1;
        outRow = 8;
        break;
    case '8':
        outColumn = 2;
        outRow = 8;
        break;
    case '9':
        outColumn = 3;
        outRow = 8;
        break;
    case 'A':
    case 'a':
        outColumn = 0;
        outRow = 0;
        break;
    case 'B':
    case 'b':
        outColumn = 1;
        outRow = 0;
        break;
    case 'C':
    case 'c':
        outColumn = 2;
        outRow = 0;
        break;
    case 'D':
    case 'd':
        outColumn = 3;
        outRow = 0;
        break;
    case 'E':
    case 'e':
        outColumn = 0;
        outRow = 1;
        break;
    case 'F':
    case 'f':
        outColumn = 1;
        outRow = 1;
        break;
    case 'G':
    case 'g':
        outColumn = 2;
        outRow = 1;
        break;
    case 'H':
    case 'h':
        outColumn = 3;
        outRow = 1;
        break;
    case 'I':
    case 'i':
        outColumn = 0;
        outRow = 2;
        break;
    case 'J':
    case 'j':
        outColumn = 1;
        outRow = 2;
        break;
    case 'K':
    case 'k':
        outColumn = 2;
        outRow = 2;
        break;
    case 'L':
    case 'l':
        outColumn = 3;
        outRow = 2;
        break;
    case 'M':
    case 'm':
        outColumn = 0;
        outRow = 3;
        break;
    case 'N':
    case 'n':
        outColumn = 1;
        outRow = 3;
        break;
    case 'O':
    case 'o':
        outColumn = 2;
        outRow = 3;
        break;
    case 'P':
    case 'p':
        outColumn = 3;
        outRow = 3;
        break;
    case 'Q':
    case 'q':
        outColumn = 0;
        outRow = 4;
        break;
    case 'R':
    case 'r':
        outColumn = 1;
        outRow = 4;
        break;
    case 'S':
    case 's':
        outColumn = 2;
        outRow = 4;
        break;
    case 'T':
    case 't':
        outColumn = 3;
        outRow = 4;
        break;
    case 'U':
    case 'u':
        outColumn = 0;
        outRow = 5;
        break;
    case 'V':
    case 'v':
        outColumn = 1;
        outRow = 5;
        break;
    case 'W':
    case 'w':
        outColumn = 2;
        outRow = 5;
        break;
    case 'X':
    case 'x':
        outColumn = 3;
        outRow = 5;
        break;
    case 'Y':
    case 'y':
        outColumn = 0;
        outRow = 6;
        break;
    case 'Z':
    case 'z':
        outColumn = 1;
        outRow = 6;
        break;
    default:
        outColumn = 0;
        outRow = 9;
        break;
    }
}

bool CCustomCarPlateMgr::RenderLicenseplateTextToRaster(const char* text, RwRaster * charsRaster, _IGNORED_ void* unusedPlaette, RwRaster * plateRaster) {
    const auto lockedPlateRaster = RwRasterLock(plateRaster, 0, rwRASTERLOCKNOFETCH | rwRASTERLOCKWRITE);
    if (!lockedPlateRaster)
        return false;

    if (!pCharsetLockedData)
        return false;

    const auto plateRasterStride = plateRaster->stride; // TODO: Use macro, maybe?
    if (!plateRasterStride)
        return false;

    const auto charsRasterStride = charsRaster->stride; // TODO: Use macro, maybe?
    if (!charsRasterStride)
        return false;

    // Copy each character from charset raster to plate raster
    auto plateRasterCharIter = lockedPlateRaster;
    for (auto letter = 0; letter < MAX_TEXT_LENGTH; letter++) {
        uint32 charRow{1}, charCol{1};
        GetCharacterPositionInCharSet(text[letter], charCol, charRow);

        // Copy specific character from charset raster to plate raster
        auto charRasterIt = &pCharsetLockedData[(CHARSET_COL_WIDTH * CHARSET_ROW_HEIGHT * charCol + CHARSET_CHAR_WIDTH * charRow) * 4 /*32bit format BGRA*/];
        auto plateRasterIt = plateRasterCharIter;
        for (auto r = 0u; r < CHARSET_CHAR_HEIGHT; r++) { // Copy character row by row
            memcpy(plateRasterIt, charRasterIt, CHARSET_CHAR_WIDTH * 4);
            plateRasterIt += plateRasterStride;
            charRasterIt += charsRasterStride;
        }

        plateRasterCharIter += CHARSET_ROW_HEIGHT * 4;
    }

    RwRasterUnlock(plateRaster);
    return true;
}

// 0x6FDEA0
RwTexture* CCustomCarPlateMgr::CreatePlateTexture(const char* text, uint8_t plateType) {
    const auto plateRaster = RwRasterCreate(64, 16, 32, 0x604); // TODO: Figure out flags
    if (!plateRaster)
        return nullptr;

    if (!RwTextureGetRaster(pCharsetTex)) {
        RwRasterDestroy(plateRaster);
        return nullptr;
    }

    if (!RenderLicenseplateTextToRaster(text, RwTextureGetRaster(pCharsetTex), pPalette1555Tab[ResolvePlateType(plateType)], plateRaster)) {
        RwRasterDestroy(plateRaster);
        return nullptr;
    }

    if (const auto plateTex = RwTextureCreate(plateRaster)) {
        RwTextureSetName(plateTex, text);
        RwTextureSetFilterMode(plateTex, rwFILTERNEAREST);
        return plateTex;
    }

    return nullptr;
}

RpMaterial* CCustomCarPlateMgr::MaterialUpgradeSetCarplateTextureCB(RpMaterial* material, void* geometry) {
    if (const auto tex = RpMaterialGetTexture(material)) {
        const auto name = RwTextureGetName(tex);
        if (strcmp(name, "careplate") == 0) {
            RpGeometryReplaceOldMaterialWithNewMaterial((RpGeometry*)geometry, material, CurrentLicensePlateMaterial);
        } else if (strcmp(name, "carpback") == 0) {
            SetupMaterialPlatebackTexture(material, CurrentLicensePlateType);
        }
    }
    return material;
}

RpAtomic* CCustomCarPlateMgr::AtomicUpgradeSetCarplateTextureCB(RpAtomic* atomic, _IGNORED_ void* data) {
    RpGeometryForAllMaterials(RpAtomicGetGeometry(atomic), MaterialUpgradeSetCarplateTextureCB, RpAtomicGetGeometry(atomic));
    return atomic;
}

// 0x6FDFE0
int8_t CCustomCarPlateMgr::SetupClumpAfterVehicleUpgrade(RpClump* clump, RpMaterial* plateMaterial, uint8_t plateType) {
    if (!plateMaterial)
        return false;

    CurrentLicensePlateType = plateType;
    CurrentLicensePlateMaterial = plateMaterial;
    RpClumpForAllAtomics(clump, AtomicUpgradeSetCarplateTextureCB, nullptr);

    return true;
}

// 0x6FE020
void CCustomCarPlateMgr::SetupMaterialPlateTexture(RpMaterial* material, const char* plateText, uint8_t plateType) {
    if (material) {
        if (const auto plateTex = CreatePlateTexture(plateText, plateType)) {
            RpMaterialSetTexture(material, plateTex);
            RwTextureDestroy(plateTex);
        }
    }
}

RpMaterial* CCustomCarPlateMgr::MaterialSetCarplateTextureCB(RpMaterial * material, void* plateText) {
    if (const auto tex = RpMaterialGetTexture(material)) {
        const auto name = RwTextureGetName(tex);
        if (strcmp(name, "careplate") == 0) {
            CurrentLicensePlateMaterial = material;
            SetupMaterialPlateTexture(material, (const char*)plateText, CurrentLicensePlateType);
        } else if (strcmp(name, "carpback") == 0) {
            SetupMaterialPlatebackTexture(material, CurrentLicensePlateType);
        }
    }
    return material;
}

RpAtomic* CCustomCarPlateMgr::AtomicSetCarplateTextureCB(RpAtomic* atomic, void* plateText) {
    RpGeometryForAllMaterials(RpAtomicGetGeometry(atomic), MaterialSetCarplateTextureCB, plateText);
    return atomic;
}

// 0x6FE0F0
RpMaterial* CCustomCarPlateMgr::SetupClump(RpClump* clump, char* plateText, uint8_t plateType) {
    CurrentLicensePlateType = plateType;
    CurrentLicensePlateMaterial = nullptr;
    RpClumpForAllAtomics(clump, AtomicUpgradeSetCarplateTextureCB, plateText);
    return CurrentLicensePlateMaterial;
}

// 0x6FD5B0
bool CCustomCarPlateMgr::GeneratePlateText(char* out, uint32 length) {
    if (length < 4)
        return false;

    constexpr auto RandomAlphanumeric = [] {
        return (char)CGeneral::GetRandomNumberInRange('A', 'Z');
    };

    constexpr auto RandomNumeric = [] {
        return (char)CGeneral::GetRandomNumberInRange('0', '9');
    };

    uint32 charIdx{};
    const auto Put = [&](char c) {
        out[charIdx++] = c;
    };

    Put(RandomAlphanumeric());
    Put(RandomAlphanumeric());
    Put(RandomNumeric());
    Put(RandomNumeric());

    for (auto i = charIdx; i < length; i += 4) {
        Put(' ');
        Put(RandomNumeric());
        Put(RandomAlphanumeric());
        Put(RandomAlphanumeric());
    }

    return true;
}
