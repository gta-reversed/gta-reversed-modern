#pragma once
#include "PluginBase.h"

class CCustomRoadsignMgr {
public:
    static RwTexture*& pCharsetTex;
    static RwUInt8*& pCharsetLockedRaster;
    static RwUInt8*& pCharsetLockedPallete; //Unused, never really locked
public:
    static void InjectHooks();

    static bool Initialise();
    static void Shutdown();
    static void RenderTest(CVector const& vecUnused);
    static void DebugDrawInternalTexture();
    static RwTexture* CreateRoadsignTexture(char* pName, int numOfChars);
    static RwTexture* SetupRoadsignAtomic(RpAtomic* pAtomic, char* pName, int numOfChars);
    static RpAtomic* SetAtomicAlpha(RpAtomic* pAtomic, unsigned char alpha);
    static RpAtomic* CreateRoadsignAtomicA(float xScale, float yScale, signed int numLines, char* pLine1, char* pLine2, char* pLine3, char* pLine4, int lettersPerLine, unsigned char ucPallete);
    static RpAtomic* CreateRoadsignAtomic(float xScale, float yScale, signed int numLines, char* pLine1, char* pLine2, char* pLine3, char* pLine4, int lettersPerLine, unsigned char ucPallete);
    static RpAtomic* RenderRoadsignAtomic(RpAtomic* pAtomic, CVector const& vecDir);
};

bool RoadsignGenerateTextRaster(char* roadName, int numLetters, RwRaster* charsetRaster, int unused, RwRaster* signRaster);
