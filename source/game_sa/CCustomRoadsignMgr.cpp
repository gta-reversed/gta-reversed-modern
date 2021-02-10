#include "StdInc.h"

RwTexture*& CCustomRoadsignMgr::pCharsetTex = *(RwTexture**)0xC3EF84;
RwUInt8*& CCustomRoadsignMgr::pCharsetLockedRaster = *(RwUInt8**)0xC3EF88;
RwUInt8*& CCustomRoadsignMgr::pCharsetLockedPallete = *(RwUInt8**)0xC3EF8C;

void CCustomRoadsignMgr::InjectHooks()
{
    ReversibleHooks::Install("CCustomRoadsignMgr", "Initialise", 0x6FE120, &CCustomRoadsignMgr::Initialise);
    ReversibleHooks::Install("CCustomRoadsignMgr", "Shutdown", 0x6FE180, &CCustomRoadsignMgr::Shutdown);
    ReversibleHooks::Install("CCustomRoadsignMgr", "CreateRoadsignTexture", 0x6FECA0, &CCustomRoadsignMgr::CreateRoadsignTexture);
    ReversibleHooks::Install("CCustomRoadsignMgr", "CreateRoadsignAtomic", 0x6FF2D0, &CCustomRoadsignMgr::CreateRoadsignAtomic);
}

bool CCustomRoadsignMgr::Initialise()
{
    const auto iTxdSlot = CTxdStore::FindTxdSlot("particle");
    CTxdStore::PushCurrentTxd();
    CTxdStore::SetCurrentTxd(iTxdSlot);

    auto* pTexture = RwTextureRead("roadsignfont", nullptr);
    RwTextureSetFilterMode(pTexture, rwFILTERNEAREST);
    RwTextureSetAddressing(pTexture, rwTEXTUREADDRESSCLAMP);
    CCustomRoadsignMgr::pCharsetTex = pTexture;

    CTxdStore::PopCurrentTxd();
    CCustomRoadsignMgr::pCharsetLockedRaster = RwRasterLock(RwTextureGetRaster(pTexture), 0, rwRASTERLOCKREAD);
    return true;
}

void CCustomRoadsignMgr::Shutdown()
{
    if (!CCustomRoadsignMgr::pCharsetTex)
        return;

    auto* pRaster = RwTextureGetRaster(CCustomRoadsignMgr::pCharsetTex);

    if (CCustomRoadsignMgr::pCharsetLockedPallete)
    {
        RwRasterUnlockPalette(pRaster);
        CCustomRoadsignMgr::pCharsetLockedPallete = nullptr;
    }

    if(CCustomRoadsignMgr::pCharsetLockedRaster)
    {
        RwRasterUnlock(pRaster);
        CCustomRoadsignMgr::pCharsetLockedRaster = nullptr;
    }

    RwTextureDestroy(CCustomRoadsignMgr::pCharsetTex);
    CCustomRoadsignMgr::pCharsetTex = nullptr;
}

void CCustomRoadsignMgr::RenderTest(CVector const& vecUnused)
{
    plugin::Call<0x6FE1E0, CVector const&>(vecUnused);
}

void CCustomRoadsignMgr::DebugDrawInternalTexture()
{
    plugin::Call<0x6FE1F0>();
}

RwTexture* CCustomRoadsignMgr::CreateRoadsignTexture(char* pName, int numOfChars)
{
    auto* pRaster = RwRasterCreate(8 * numOfChars, 16, 32, rwRASTERFORMAT8888 | rwRASTERPIXELLOCKEDWRITE);
    assert(pRaster); //TODO: Remove if crash cause is found
    if (!pRaster)
        return nullptr;

    auto* pCharsetRaster = RwTextureGetRaster(CCustomRoadsignMgr::pCharsetTex);
    assert(pCharsetRaster); //TODO: Remove if crash cause is found
    if (!pCharsetRaster)
    {
        RwRasterDestroy(pRaster);
        return nullptr;
    }

    const auto bGenerated = RoadsignGenerateTextRaster(pName, numOfChars, pCharsetRaster, 0, pRaster);
    assert(bGenerated); //TODO: Remove if crash cause is found
    if (!bGenerated)
    {
        RwRasterDestroy(pRaster);
        return nullptr;
    }

    auto* pTexture = RwTextureCreate(pRaster);
    assert(pTexture); //TODO: Remove if crash cause is found
    if (!pTexture)
    {
        RwRasterDestroy(pRaster);
        return nullptr;
    }

    char nameCopy[12] {};
    strncpy(nameCopy, pName, 10);
    RwTextureSetName(pTexture, nameCopy);
    RwTextureSetFilterMode(pTexture, rwFILTERLINEAR);
    return pTexture;
}

RwTexture* CCustomRoadsignMgr::SetupRoadsignAtomic(RpAtomic* pAtomic, char* pName, int numOfChars)
{
    return plugin::CallAndReturn<RwTexture*, 0x6FED60, RpAtomic*, char*, int>(pAtomic, pName, numOfChars);
}

RpAtomic* CCustomRoadsignMgr::SetAtomicAlpha(RpAtomic* pAtomic, unsigned char alpha)
{
    return plugin::CallAndReturn<RpAtomic*, 0x6FE240, RpAtomic*, unsigned char>(pAtomic, alpha);
}

RpAtomic* CCustomRoadsignMgr::CreateRoadsignAtomicA(float xScale, float yScale, signed int numLines, char* pLine1, char* pLine2, char* pLine3, char* pLine4, int lettersPerLine, unsigned char ucPallete)
{
    return plugin::CallAndReturn<RpAtomic*, 0x6FEDA0, float, float, int, char*, char*, char*, char*, int, unsigned char>
        (xScale, yScale, numLines, pLine1, pLine2, pLine3, pLine4, lettersPerLine, ucPallete);
}

RpAtomic* CCustomRoadsignMgr::CreateRoadsignAtomic(float xScale, float yScale, signed int numLines, char* pLine1, char* pLine2, char* pLine3, char* pLine4, int lettersPerLine, unsigned char ucPallete)
{
    char dummy = ' ';
    auto* usedLine1 = pLine1 ? pLine1 : &dummy;
    auto* usedLine2 = pLine2 ? pLine2 : &dummy;
    auto* usedLine3 = pLine3 ? pLine3 : &dummy;
    auto* usedLine4 = pLine4 ? pLine4 : &dummy;

    auto* pAtomic = CCustomRoadsignMgr::CreateRoadsignAtomicA(xScale, yScale, numLines, usedLine1, usedLine2, usedLine3, usedLine4, lettersPerLine, ucPallete);
    assert(pAtomic); //TODO: Remove if crash cause is found
    return pAtomic;


}

RpAtomic* CCustomRoadsignMgr::RenderRoadsignAtomic(RpAtomic* pAtomic, CVector const& vecDir)
{
    return plugin::CallAndReturn<RpAtomic*, 0x6FF350, RpAtomic*, CVector const&>(pAtomic, vecDir);
}

bool RoadsignGenerateTextRaster(char* roadName, int numLetters, RwRaster* charsetRaster, int unused, RwRaster* signRaster)
{
    return plugin::CallAndReturn<bool, 0x6FEB70, char*, int, RwRaster*, int, RwRaster*>
        (roadName, numLetters, charsetRaster, unused, signRaster);
}
