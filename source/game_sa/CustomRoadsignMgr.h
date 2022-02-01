#pragma once

#include "Vector.h"

#define SIGN_CHAR_WIDTH 8
#define SIGN_CHAR_HEIGHT 16
#define SIGN_PIXEL_BYTES 4

class CCustomRoadsignMgr {
public:
    static RwTexture*& pCharsetTex;
    static RwUInt8*& pCharsetLockedRaster;
    static RwUInt8*& pCharsetLockedPallete; //Unused, never really locked
public:
    static void InjectHooks();

    static bool Initialise();
    static void Shutdown();
    static bool RenderTest(CVector const& vecUnused) { return true; };
    static void DebugDrawInternalTexture() {}
    static RwTexture* CreateRoadsignTexture(char* pName, int32 numOfChars);
    static RwTexture* SetupRoadsignAtomic(RpAtomic* pAtomic, char* pName, int32 numOfChars);
    static RpAtomic* SetAtomicAlpha(RpAtomic* pAtomic, uint8 alpha);
    static RpAtomic* CreateRoadsignAtomicA(float fWidth, float fHeight, signed int numLines, char* pLine1, char* pLine2, char* pLine3, char* pLine4, int32 lettersPerLine, uint8 ucPallete);
    static RpAtomic* CreateRoadsignAtomic(float xScale, float yScale, signed int numLines, char* pLine1, char* pLine2, char* pLine3, char* pLine4, int32 lettersPerLine, uint8 ucPallete);
    static RpAtomic* RenderRoadsignAtomic(RpAtomic* pAtomic, CVector const& vecPos);
};

RpMaterial* RoadsignSetMaterialAlphaCB(RpMaterial* material, void* data); //data is uint8 alpha
RpMaterial* RoadsignSetMaterialTextureCB(RpMaterial* material, void* data); //data is RwTexture*
bool RoadsignGenerateTextRaster(char* roadName, int32 numLetters, RwRaster* charsetRaster, int32 unused, RwRaster* signRaster);
void RoadsignGetLineAndRow(char cLetter, int32* line, int32* row); // Weird calling convention in SA, passing argument in <al>, line is column
