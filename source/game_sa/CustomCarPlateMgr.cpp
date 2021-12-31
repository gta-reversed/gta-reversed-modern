#include "StdInc.h"
#include <format>

void CCustomCarPlateMgr::InjectHooks() {
    ReversibleHooks::Install("CCustomCarPlateMgr", "Initialise", 0x6FD500, &CCustomCarPlateMgr::Initialise);
//    ReversibleHooks::Install("CCustomCarPlateMgr", "Shutdown", 0x6FD720, &CCustomCarPlateMgr::Shutdown);
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
bool CCustomCarPlateMgr::Shutdown() {
    return plugin::CallAndReturn<bool, 0x6FD720>();
}


bool CCustomCarPlateMgr::GeneratePlateText(char* plateTextBuf, int32 length)
{
    return plugin::CallAndReturn<bool, 0x6FD5B0, char*, int32>(plateTextBuf, length);
}

RpMaterial* CCustomCarPlateMgr::SetupClump(RpClump* clump, char* plateText, uint8 plateType)
{
    return plugin::CallAndReturn<RpMaterial*, 0x6FE0F0, RpClump*, char*, uint8>(clump, plateText, plateType);
}
