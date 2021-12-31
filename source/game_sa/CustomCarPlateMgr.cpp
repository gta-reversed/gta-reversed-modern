#include "StdInc.h"
#include <format>

void CCustomCarPlateMgr::InjectHooks() {
    ReversibleHooks::Install("CCustomCarPlateMgr", "Initialise", 0x6FD500, &CCustomCarPlateMgr::Initialise);
    // ReversibleHooks::Install("CCustomCarPlateMgr", "GeneratePlateText", 0x6FD5B0, &CCustomCarPlateMgr::GeneratePlateText);
    ReversibleHooks::Install("CCustomCarPlateMgr", "Shutdown", 0x6FD720, &CCustomCarPlateMgr::Shutdown);
    ReversibleHooks::Install("CCustomCarPlateMgr", "GetMapRegionPlateDesign", 0x6FD7A0, &CCustomCarPlateMgr::GetMapRegionPlateDesign);
    // ReversibleHooks::Install("CCustomCarPlateMgr", "LoadPlatecharsetDat", 0x6FDC00, &CCustomCarPlateMgr::LoadPlatecharsetDat);
    ReversibleHooks::Install("CCustomCarPlateMgr", "SetupMaterialPlatebackTexture", 0x6FDE50, &CCustomCarPlateMgr::SetupMaterialPlatebackTexture);
    ReversibleHooks::Install("CCustomCarPlateMgr", "CreatePlateTexture", 0x6FDEA0, &CCustomCarPlateMgr::CreatePlateTexture);
    // ReversibleHooks::Install("CCustomCarPlateMgr", "SetupClumpAfterVehicleUpgrade", 0x6FDFE0, &CCustomCarPlateMgr::SetupClumpAfterVehicleUpgrade);
    // ReversibleHooks::Install("CCustomCarPlateMgr", "SetupMaterialPlateTexture", 0x6FE020, &CCustomCarPlateMgr::SetupMaterialPlateTexture);
    // ReversibleHooks::Install("CCustomCarPlateMgr", "SetupClump", 0x6FE0F0, &CCustomCarPlateMgr::SetupClump);
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

// 0x6FDEA0
RwTexture* CCustomCarPlateMgr::CreatePlateTexture(char* text, uint8_t plateType) {
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

// 0x6FDFE0
int8_t CCustomCarPlateMgr::SetupClumpAfterVehicleUpgrade(RpClump* clump, RpMaterial* plateMaterial, uint8_t plateType) {
    return plugin::CallAndReturn<int8_t, 0x6FDFE0, RpClump*, RpMaterial*, uint8_t>(clump, plateMaterial, plateType);
}

// 0x6FE020
RwTexture* CCustomCarPlateMgr::SetupMaterialPlateTexture(RpMaterial* material, char* plateText, uint8_t plateType) {
    return plugin::CallAndReturn<RwTexture*, 0x6FE020, RpMaterial*, char*, uint8_t>(material, plateText, plateType);
}

// 0x6FE0F0
RpMaterial* CCustomCarPlateMgr::SetupClump(RpClump* clump, char* plateText, uint8_t plateType) {
    return plugin::CallAndReturn<RpMaterial*, 0x6FE0F0, RpClump*, char*, uint8_t>(clump, plateText, plateType);
}
