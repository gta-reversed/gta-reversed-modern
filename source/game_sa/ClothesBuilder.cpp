#include "StdInc.h"

#include "ClothesBuilder.h"
#include "OctTreeBase.h"

CDirectory& playerImg = *(CDirectory*)0xBC12C0;
CDirectory::DirectoryInfo& playerImgEntries = *(CDirectory::DirectoryInfo*)0xBBCDC8;
int16 (&gBoneIndices)[10][64] = *(int16(*)[10][64])0xBBC8C8;

struct sDataFindAtomicFromName {
    const char* inputData;
    RpAtomic* outputData;
};

void CClothesBuilder::InjectHooks() {
    RH_ScopedClass(CClothesBuilder);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(LoadCdDirectory, 0x5A4190);
    RH_ScopedInstall(RequestGeometry, 0x5A41C0, { .reversed = false });
    RH_ScopedInstall(RequestTexture, 0x5A4220, { .reversed = false }); 
    //RH_ScopedInstall(nullptr, 0x5A42B0, { .reversed = false }); 
    //RH_ScopedInstall(nullptr, 0x5A4380, { .reversed = false }); AtomicInstanceCB
    //RH_ScopedInstall(nullptr, 0x5A43A0, { .reversed = false });
    //RH_ScopedInstall(nullptr, 0x5A44A0, { .reversed = false }); DestroyTextureCB
    RH_ScopedInstall(PreprocessClothesDesc, 0x5A44C0, { .reversed = false });
    RH_ScopedInstall(ReleaseGeometry, 0x5A47B0, { .reversed = false });
    RH_ScopedGlobalInstall(FindAtomicFromNameCB, 0x5A47E0);
    RH_ScopedGlobalInstall(GetAtomicWithName, 0x5A4810);
    RH_ScopedInstall(sub_5A4840, 0x5A4840, { .reversed = false });
    RH_ScopedInstall(StoreBoneArray, 0x5A48B0);
    // RH_ScopedOverloadedInstall(BlendGeometry, "", 0x5A4940, RpGeometry* (*)(RpClump*, const char*, const char*, const char*, float, float, float));
    // RH_ScopedOverloadedInstall(BlendGeometry, "", 0x5A4F10, RpGeometry* (*)(RpClump*, const char*, const char*, float, float));
    RH_ScopedInstall(CopyGeometry, 0x5A5340, { .reversed = false });
    RH_ScopedInstall(ConstructGeometryArray, 0x5A55A0, { .reversed = false });
    RH_ScopedInstall(DestroySkinArrays, 0x5A56C0);
    RH_ScopedInstall(BuildBoneIndexConversionTable, 0x5A56E0, { .reversed = false });
    RH_ScopedInstall(CopyTexture, 0x5A5730);
    RH_ScopedInstall(PlaceTextureOnTopOfTexture, 0x5A57B0);
    // RH_ScopedOverloadedInstall(BlendTextures, "", 0x5A5820, void (*)(RwTexture*, RwTexture*, float, float, int32));
    // RH_ScopedOverloadedInstall(BlendTextures, "", 0x5A59C0, void (*)(RwTexture*, RwTexture*, RwTexture*, float, float, float, int32));
    // RH_ScopedOverloadedInstall(BlendTextures, "", 0x5A5BC0, void (*)(RwTexture*, RwTexture*, RwTexture*, float, float, float, int32, RwTexture*));
    RH_ScopedInstall(InitPaletteOctTree, 0x5A5EB0, { .reversed = false });
    RH_ScopedInstall(ShutdownPaletteOctTree, 0x5A5EE0, { .reversed = false });
    RH_ScopedInstall(ReducePaletteOctTree, 0x5A5EF0, { .reversed = false });
    RH_ScopedInstall(AddColour, 0x5A5F00);
    RH_ScopedInstall(FillPalette, 0x5A5F30);
    RH_ScopedInstall(FindNearestColour, 0x5A5F40);
    RH_ScopedGlobalInstall(GetTextureFromTxdAndLoadNextTxd, 0x5A5F70, { .reversed = false });
    RH_ScopedInstall(ConstructTextures, 0x5A6040, { .reversed = false });
    RH_ScopedInstall(ConstructGeometryAndSkinArrays, 0x5A6530, { .reversed = false });
    RH_ScopedInstall(ReducePaletteSize, 0x5A6870, { .reversed = false });
    RH_ScopedInstall(CreateSkinnedClump, 0x5A69D0, { .reversed = false });
}

// inlined
// 0x5A4190
void CClothesBuilder::LoadCdDirectory() {
    playerImg.Init(550, &playerImgEntries);
    playerImg.ReadDirFile("MODELS\\PLAYER.IMG");
}

// 0x5A41C0
void CClothesBuilder::RequestGeometry(int32 modelId, uint32 crc) {
    plugin::Call<0x5A41C0, int32, uint32>(modelId, crc);
}

// 0x5A4220
int32 CClothesBuilder::RequestTexture(uint32 crc) {
    return plugin::CallAndReturn<int32, 0x5A4220, uint32>(crc);
}

// 0x5A44C0
void CClothesBuilder::PreprocessClothesDesc(CPedClothesDesc& desc, bool a2) {
    plugin::Call<0x5A44C0, CPedClothesDesc&, bool>(desc, a2);
}

// unused
// 0x5A47B0
void CClothesBuilder::ReleaseGeometry(int32 numToRelease) {
    for (auto i = numToRelease; i; CStreaming::SetModelIsDeletable(MODEL_CLOTHES01_ID384 + i))
        --i;
}

// 0x5A47E0
RpAtomic* FindAtomicFromNameCB(RpAtomic* atomic, void* data) {
    sDataFindAtomicFromName* dataStruct = reinterpret_cast<sDataFindAtomicFromName*>(data);
    if (stricmp(GetFrameNodeName(RpAtomicGetFrame(atomic)), dataStruct->inputData)) {
        return atomic;
    }

    dataStruct->outputData = atomic;
    return atomic;
}

// 0x5A4810
RpAtomic* GetAtomicWithName(RpClump* clump, const char* name) {
    sDataFindAtomicFromName pData;
    pData.inputData = name;
    RpClumpForAllAtomics(clump, FindAtomicFromNameCB, &pData);

    return pData.outputData;
}

// 0x5A4840
void CClothesBuilder::sub_5A4840() {

}

// 0x5A48B0
void CClothesBuilder::StoreBoneArray(RpClump* clump, int32 num) {
    auto result = RpSkinAtomicGetHAnimHierarchy(GetAtomicWithName(clump, "normal"));

    if (result->numNodes < 1) {
        gBoneIndices[num][0] = -1;
        return;
    }

    for (uint32 i = 0; i < result->numNodes; i++) {
        gBoneIndices[num][i] = result->pNodeInfo[i].nodeID;
    }

    if (result->numNodes < 64) {
        gBoneIndices[num][result->numNodes - 1] = -1;
    }
}

// 0x5A4940
RpGeometry* CClothesBuilder::BlendGeometry(RpClump* clump, const char* a2, const char* a3, const char* a4, float a5, float a6, float a7) {
    return plugin::CallAndReturn<RpGeometry*, 0x5A4940, RpClump*, const char*, const char*, const char*, float, float, float>(clump, a2, a3, a4, a5, a6, a7);
}

// 0x5A4F10
RpGeometry* CClothesBuilder::BlendGeometry(RpClump* clump, const char* a2, const char* a3, float a4, float a5) {
    return plugin::CallAndReturn<RpGeometry*, 0x5A4F10, RpClump*, const char*, const char*, float, float>(clump, a2, a3, a4, a5);
}

// 0x5A5340
RpGeometry* CClothesBuilder::CopyGeometry(RpClump* clump, const char* a2, const char* a3) {
    return plugin::CallAndReturn<RpGeometry*, 0x5A5340, RpClump*, const char*, const char*>(clump, a2, a3);
}

// 0x5A55A0
void CClothesBuilder::ConstructGeometryArray(RpGeometry** geometry, uint32* a2, float a3, float a4, float a5) {
    plugin::Call<0x5A55A0, RpGeometry**, uint32*, float, float, float>(geometry, a2, a3, a4, a5);
}

// inlined, see 0x5A6CE1
// 0x5A56C0
void CClothesBuilder::DestroySkinArrays(RwMatrixWeights* weights, uint32* pBones) {
    delete[] weights;
    delete[] pBones;
}

// 0x5A56E0
void CClothesBuilder::BuildBoneIndexConversionTable(uint8* pTable, RpHAnimHierarchy* pSkinHier, int32 index) {
    for (size_t i = 0; i < 64; i++) {
        int16 boneIndex = gBoneIndices[index][i];

        if (boneIndex == -1) {
            break;
        }

        const auto index = RpHAnimIDGetIndex(pSkinHier, boneIndex);
        pTable[i] = index != -1 ? index : 0;
    }
}

// 0x5A5730
RwTexture* CClothesBuilder::CopyTexture(RwTexture* texture) {
    RwRaster* raster = RwRasterCreate(
        RwRasterGetWidth(RwTextureGetRaster(texture)),
        RwRasterGetHeight(RwTextureGetRaster(texture)),
        RwRasterGetDepth(RwTextureGetRaster(texture)),
        (RwRasterGetFormat(RwTextureGetRaster(texture)) & (rwRASTERFORMAT1555 | rwRASTERFORMAT565 | rwRASTERFORMAT4444 | rwRASTERFORMATLUM8 | rwRASTERFORMAT8888 | rwRASTERFORMAT888 |
                                                        rwRASTERFORMAT16 |
                    rwRASTERFORMAT24 | rwRASTERFORMAT32 | rwRASTERFORMAT555 | rwRASTERFORMATPAL8 | rwRASTERFORMATPAL4)) | 4
    );

    const auto lockedRasterPixelsOld = RwRasterLock(RwTextureGetRaster(texture), 0, rwRASTERLOCKREAD);
    const auto lockedRasterPixelsNew = RwRasterLock(raster, 0, rwRASTERLOCKWRITE);

    memcpy(lockedRasterPixelsNew, lockedRasterPixelsOld, RwRasterGetHeight(RwTextureGetRaster(texture)) * RwRasterGetStride(RwTextureGetRaster(texture)));

    RwRasterUnlock(RwTextureGetRaster(texture));
    RwRasterUnlock(raster);

    RwTexture* newTexture = RwTextureCreate(raster);
    RwTextureSetFilterModeMacro(newTexture, rwFILTERLINEAR);

    return newTexture;
}

// 0x5A57B0
void CClothesBuilder::PlaceTextureOnTopOfTexture(RwTexture* textureTo, RwTexture* textureFrom) {
    if (RwRasterGetHeight(RwTextureGetRaster(textureTo)) != RwRasterGetHeight(RwTextureGetRaster(textureFrom)) ||
        RwRasterGetWidth(RwTextureGetRaster(textureTo)) != RwRasterGetWidth(RwTextureGetRaster(textureFrom))) {
        return;
    }

    CRGBA* pPixelsTo = reinterpret_cast<CRGBA*>(RwRasterLock(RwTextureGetRaster(textureTo), 0, rwRASTERLOCKREADWRITE));
    CRGBA* pPixelsFrom = reinterpret_cast<CRGBA*>(RwRasterLock(RwTextureGetRaster(textureFrom), 0, rwRASTERLOCKREADWRITE));

    uint32 countPixels = RwRasterGetHeight(RwTextureGetRaster(textureTo)) * RwRasterGetWidth(RwTextureGetRaster(textureTo));
    
    for (int i = 0; i < countPixels; ++i) {
        if (pPixelsFrom[i].a == 0) {
            continue;
        }

        memcpy(&pPixelsTo[i], &pPixelsFrom[i], sizeof(CRGBA));
    }

    RwRasterUnlock(RwTextureGetRaster(textureTo));
    RwRasterUnlock(RwTextureGetRaster(textureFrom));
}

// 0x5A5820
void CClothesBuilder::BlendTextures(RwTexture* t1, RwTexture* t2, float a3, float a4, int32 a5) {
    plugin::Call<0x5A5820, RwTexture*, RwTexture*, float, float, int32>(t1, t2, a3, a4, a5);
}

// 0x5A59C0
void CClothesBuilder::BlendTextures(RwTexture* t1, RwTexture* t2, RwTexture* t3, float factorA, float factorB, float factorC, int32 a7) {
    plugin::Call<0x5A59C0, RwTexture*, RwTexture*, RwTexture*, float, float, float>(t1, t2, t3, factorA, factorB, factorC, a7);
}

// 0x5A5BC0
void CClothesBuilder::BlendTextures(RwTexture* t1, RwTexture* t2, RwTexture* t3, float factorA, float factorB, float factorC, int32 a7, RwTexture* t4) {
    plugin::Call<0x5A5BC0, RwTexture*, RwTexture*, RwTexture*, float, float, float, int32, RwTexture*>(t1, t2, t3, factorA, factorB, factorC, a7, t4);
}

// unused or inlined
// 0x5A5EB0
void CClothesBuilder::InitPaletteOctTree(int32 numColors) {
    /*
    COctTree::InitPool(&PC_Scratch[1024], 15360u);
    COctTreeBase::Init(&gOctTreeBase, numColors);
    */
}

// 0x5A5EE0
void CClothesBuilder::ShutdownPaletteOctTree() {
    // COctTree::ShutdownPool();
}

// 0x5A5EF0
void CClothesBuilder::ReducePaletteOctTree(int32 numColorsToReduce) {
    // gOctTreeBase.ReduceBranches(newBranchesCount);
}

// unused
// 0x5A5F00
bool CClothesBuilder::AddColour(CRGBA* color) {
    if (color->a == 0) {
        gOctTreeBase.m_bHasTransparentPixels = true;
    }

    return gOctTreeBase.Insert(color->r, color->g, color->b);
}

// unused
// 0x5A5F30
void CClothesBuilder::FillPalette(CRGBA* color) {
    gOctTreeBase.FillPalette(reinterpret_cast<uint8*>(color));
}

// unused
// 0x5A5F40
int32 CClothesBuilder::FindNearestColour(CRGBA* color) {
    return color->a != 0 ? gOctTreeBase.FindNearestColour(color->r, color->g, color->b) : 0;
}

// 0x5A5F70
RwTexture* GetTextureFromTxdAndLoadNextTxd(RwTexture* destTexture, int32 txdId_withTexture, int32 CRC_nextTxd, int32* nextTxdId) {
    return plugin::CallAndReturn<RwTexture*, 0x5A5F70, RwTexture*, int32, int32, int32*>(destTexture, txdId_withTexture, CRC_nextTxd, nextTxdId);
}

// 0x5A6040
void CClothesBuilder::ConstructTextures(RwTexDictionary* dict, uint32* hashes, float factorA, float factorB, float factorC) {
    plugin::Call<0x5A6040, RwTexDictionary*, uint32*, float, float, float>(dict, hashes, factorA, factorB, factorC);
}

// 0x5A6530
void CClothesBuilder::ConstructGeometryAndSkinArrays(RpHAnimHierarchy* animHierarchy, RpGeometry** geometry1, RwMatrixWeights** weights, uint32** a4, uint32 a5, RpGeometry** geometry2, RpMaterial** material) {
    plugin::Call<0x5A6530, RpHAnimHierarchy*, RpGeometry**, RwMatrixWeights**, uint32**, uint32, RpGeometry**, RpMaterial**>(animHierarchy, geometry1, weights, a4, a5, geometry2, material);
}

// unused
// 0x5A6870
void CClothesBuilder::ReducePaletteSize(RwTexture* texture, int32 numColorsToReduce) {
    plugin::Call<0x5A6870, RwTexture*, int32>(texture, numColorsToReduce);
}

// 0x5A69D0
RpClump* CClothesBuilder::CreateSkinnedClump(RpClump* clump, RwTexDictionary* dict, CPedClothesDesc& newClothes, const CPedClothesDesc* oldClothes, bool bCutscenePlayer) {
    return plugin::CallAndReturn<RpClump*, 0x5A69D0, RpClump*, RwTexDictionary*, CPedClothesDesc&, const CPedClothesDesc*, bool>(clump, dict, newClothes, oldClothes, bCutscenePlayer);
}
