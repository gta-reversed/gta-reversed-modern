
/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "RenderWare.h" // important

class PedClothesDesc;

class CClothesBuilder {
public:
    static void  InjectHooks();

    static void LoadCdDirectory();
    static void RequestGeometry(int32 modelId, uint32 crc);
    static int32 RequestTexture(uint32 crc);
    static void PreprocessClothesDesc(CPedClothesDesc& desc, bool a2);
    static void ReleaseGeometry(int32 numToRelease);
    static void sub_5A4840();
    static void StoreBoneArray(RpClump* clump, int32 a2);
    static RpGeometry* BlendGeometry(RpClump* clump, const char* a2, const char* a3, const char* a4, float a5, float a6, float a7);
    static RpGeometry* BlendGeometry(RpClump* clump, const char* a2, const char* a3, float a4, float a5);
    static RpGeometry* CopyGeometry(RpClump* clump, const char* a2, const char* a3);
    static void ConstructGeometryArray(RpGeometry** geometry, uint32* a2, float a3, float a4, float a5);
    static void DestroySkinArrays(RwMatrixWeights* weights, uint32* pBones);
    static void BuildBoneIndexConversionTable(uint8* a1, RpHAnimHierarchy* a2, int32 a3);
    static RwTexture* CopyTexture(RwTexture* texture);
    static void PlaceTextureOnTopOfTexture(RwTexture* textureTo, RwTexture* textureFrom);
    static void BlendTextures(RwTexture* t1, RwTexture* t2, float a3, float a4, int32 a5);
    static void BlendTextures(RwTexture* t1, RwTexture* t2, RwTexture* t3, float factorA, float factorB, float factorC, int32 a7);
    static void BlendTextures(RwTexture* t1, RwTexture* t2, RwTexture* t3, float factorA, float factorB, float factorC, int32 a7, RwTexture* t4);
    static void InitPaletteOctTree(int32 numColors);
    static void ShutdownPaletteOctTree();
    static void ReducePaletteOctTree(int32 numColorsToReduce);
    static bool AddColour(CRGBA* color);
    static void FillPalette(CRGBA* color);
    static int32 FindNearestColour(CRGBA* color);
    static void ConstructTextures(RwTexDictionary* dict, uint32* hashes, float factorA, float factorB, float factorC);
    static void ConstructGeometryAndSkinArrays(RpHAnimHierarchy* animHierarchy, RpGeometry** geometry1, RwMatrixWeights** weights, uint32** a4, uint32 a5, RpGeometry** geometry2, RpMaterial** material);
    static void ReducePaletteSize(RwTexture* texture, int32 numColorsToReduce);
    static RpClump* CreateSkinnedClump(RpClump* clump, RwTexDictionary* dict, CPedClothesDesc& newClothes, const CPedClothesDesc* oldClothes, bool CutscenePlayer);
};

void FindAtomicFromNameCB(RpAtomic* atomic, void* data);
void GetAtomicWithName(RpClump* clump, const char* name);
RwTexture* GetTextureFromTxdAndLoadNextTxd(RwTexture* destTexture, int32 txdId_withTexture, int32 CRC_nextTxd, int32* nextTxdId);
