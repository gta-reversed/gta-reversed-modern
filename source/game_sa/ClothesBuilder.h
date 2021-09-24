
/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "renderware.h"  // important
#include "PedClothesDesc.h"

class CClothesBuilder {
public:
    static void BlendTextures(RwTexture* texture1, RwTexture* texture2, RwTexture* texture3, float factorA, float factorB, float factorC, int32 arg7, RwTexture* texture4);
    static void BlendTextures(RwTexture* texture1, RwTexture* texture2, RwTexture* texture3, float factorA, float factorB, float factorC);
    static void BlendTextures(RwTexture* texture1, RwTexture* texture2, float arg3, float arg4);
    static void BuildBoneIndexConversionTable(uint8* arg1, RpHAnimHierarchy* arg2, int32 arg3);
    static void ConstructGeometryAndSkinArrays(RpHAnimHierarchy* arg1, RpGeometry** arg2, RwMatrixWeights** arg3, uint32** arg4, uint32 arg5, RpGeometry** arg6, RpMaterial** arg7);
    static void ConstructGeometryArray(RpGeometry** arg1, uint32* arg2, float arg3, float arg4, float arg5);
    static void ConstructTextures(RwTexDictionary* dict, uint32* hashes, float factorA, float factorB, float factorC);
    static RwTexture* CopyTexture(RwTexture* texture);
    static RpClump* CreateSkinnedClump(RpClump* clump, RwTexDictionary* dict, CPedClothesDesc& newclothes, CPedClothesDesc const* oldclothes, bool bCutscenePlayer);
    static void DestroySkinArrays(RwMatrixWeights* arg1, uint32* arg2);
    static int32 FindNearestColour(RwRGBA* color);
    static void InitPaletteOctTree(int32 numColors);
    static void LoadCdDirectory();
    static void PlaceTextureOnTopOfTexture(RwTexture* texture1, RwTexture* texture2);
    static void PreprocessClothesDesc(CPedClothesDesc& arg1, bool arg2);
    static void ReducePaletteSize(RwTexture* texture, int32 numColorsToReduce);
    static void ReleaseGeometry(int32 numToRelease);
    void RequestGeometry(int32 modelid, uint32 crc);
    static void StoreBoneArray(RpClump* clump, int32 arg2);
    static RpGeometry* BlendGeometry(RpClump* clump, char const* arg2, char const* arg3, char const* arg4, float arg5, float arg6, float arg7);
    static RpGeometry* BlendGeometry(RpClump* clump, char const* arg2, char const* arg3, float arg4, float arg5);
    static RpGeometry* CopyGeometry(RpClump* clump, char const* arg2, char const* arg3);
    static void ShutdownPaletteOctTree();
    static void ReducePaletteOctTree(int32 numColorsToReduce);
    static bool AddColour(RwRGBA* color);
    static void FillPalette(RwRGBA* color);	
};
