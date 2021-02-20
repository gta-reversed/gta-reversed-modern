#pragma once
#include "PluginBase.h"

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
    static RwTexture* CreateRoadsignTexture(char* pName, int numOfChars);
    static RwTexture* SetupRoadsignAtomic(RpAtomic* pAtomic, char* pName, int numOfChars);
    static RpAtomic* SetAtomicAlpha(RpAtomic* pAtomic, unsigned char alpha);
    static RpAtomic* CreateRoadsignAtomicA(float fWidth, float fHeight, signed int numLines, char* pLine1, char* pLine2, char* pLine3, char* pLine4, int lettersPerLine, unsigned char ucPallete);
    static RpAtomic* CreateRoadsignAtomic(float xScale, float yScale, signed int numLines, char* pLine1, char* pLine2, char* pLine3, char* pLine4, int lettersPerLine, unsigned char ucPallete);
    static RpAtomic* RenderRoadsignAtomic(RpAtomic* pAtomic, CVector const& vecPos);
};

RpMaterial* RoadsignSetMaterialAlphaCB(RpMaterial* material, void* data); //data is uint8_t alpha
RpMaterial* RoadsignSetMaterialTextureCB(RpMaterial* material, void* data); //data is RwTexture*
bool RoadsignGenerateTextRaster(char* roadName, int numLetters, RwRaster* charsetRaster, int unused, RwRaster* signRaster);
void RoadsignGetLineAndRow(char cLetter, int* line, int* row); // Weird calling convention in SA, passing argument in <al>, line is column
