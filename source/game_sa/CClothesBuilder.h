
/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "renderware.h"  // important
#include "CPedClothesDesc.h"


class  CClothesBuilder
{
public:
	 
    static void BlendTextures(RwTexture* texture1, RwTexture* texture2, RwTexture* texture3, float factorA, float factorB, float factorC, int arg7, RwTexture* texture4);
    static void BlendTextures(RwTexture* texture1, RwTexture* texture2, RwTexture* texture3, float factorA, float factorB, float factorC);
    static void BlendTextures(RwTexture* texture1, RwTexture* texture2, float arg3, float arg4);
    static void BuildBoneIndexConversionTable(unsigned char* arg1, RpHAnimHierarchy* arg2, int arg3);
    static void ConstructGeometryAndSkinArrays(RpHAnimHierarchy* arg1, RpGeometry** arg2, RwMatrixWeights** arg3, unsigned int** arg4, unsigned int arg5, RpGeometry** arg6, RpMaterial** arg7);
    static void ConstructGeometryArray(RpGeometry** arg1, unsigned int* arg2, float arg3, float arg4, float arg5);
    static void ConstructTextures(RwTexDictionary* dict, unsigned int* hashes, float factorA, float factorB, float factorC);
    static RwTexture* CopyTexture(RwTexture* texture);
    static RpClump* CreateSkinnedClump(RpClump* clump, RwTexDictionary* dict, CPedClothesDesc& newclothes, CPedClothesDesc const* oldclothes, bool bCutscenePlayer);
    static void DestroySkinArrays(RwMatrixWeights* arg1, unsigned int* arg2);
    static int FindNearestColour(RwRGBA* color);
    static void InitPaletteOctTree(int numColors);
    static void LoadCdDirectory();
    static void PlaceTextureOnTopOfTexture(RwTexture* texture1, RwTexture* texture2);
    static void PreprocessClothesDesc(CPedClothesDesc& arg1, bool arg2);
    static void ReducePaletteSize(RwTexture* texture, int numColorsToReduce);
    static void ReleaseGeometry(int numToRelease);
    void RequestGeometry(int modelid, unsigned int crc);
    static void StoreBoneArray(RpClump* clump, int arg2);
    static RpGeometry* BlendGeometry(RpClump* clump, char const* arg2, char const* arg3, char const* arg4, float arg5, float arg6, float arg7);
    static RpGeometry* BlendGeometry(RpClump* clump, char const* arg2, char const* arg3, float arg4, float arg5);
    static RpGeometry* CopyGeometry(RpClump* clump, char const* arg2, char const* arg3);
    static void ShutdownPaletteOctTree();
    static void ReducePaletteOctTree(int numColorsToReduce);
    static bool AddColour(RwRGBA* color);
    static void FillPalette(RwRGBA* color);	
};
