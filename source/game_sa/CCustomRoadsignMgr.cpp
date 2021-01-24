#include "StdInc.h"

bool CCustomRoadsignMgr::Initialise()
{
    return plugin::CallAndReturn<bool, 0x6FE120>();
}

void CCustomRoadsignMgr::Shutdown()
{
    plugin::Call<0x6FE180>();
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
    return plugin::CallAndReturn<RwTexture*, 0x6FECA0, char*, int>(pName, numOfChars);
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
    return plugin::CallAndReturn<RpAtomic*, 0x6FF2D0, float, float, int, char*, char*, char*, char*, int, unsigned char>
        (xScale, yScale, numLines, pLine1, pLine2, pLine3, pLine4, lettersPerLine, ucPallete);
}

RpAtomic* CCustomRoadsignMgr::RenderRoadsignAtomic(RpAtomic* pAtomic, CVector const& vecDir)
{
    return plugin::CallAndReturn<RpAtomic*, 0x6FF350, RpAtomic*, CVector const&>(pAtomic, vecDir);
}
