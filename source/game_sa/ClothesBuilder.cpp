#include "StdInc.h"

#include "ClothesBuilder.h"

CDirectory& playerImg = *(CDirectory*)0xBC12C0;
CDirectory::DirectoryInfo& playerImgEntries = *(CDirectory::DirectoryInfo*)0xBBCDC8;

auto& gBoneIndices = StaticRef<notsa::mdarray<int16, 10, 64>>(0xBBC8C8);

void CClothesBuilder::InjectHooks() {
    RH_ScopedClass(CClothesBuilder);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(LoadCdDirectory, 0x5A4190);
    RH_ScopedInstall(RequestGeometry, 0x5A41C0);
    RH_ScopedInstall(RequestTexture, 0x5A4220); 
    //RH_ScopedInstall(nullptr, 0x5A42B0, { .reversed = false }); 
    //RH_ScopedInstall(nullptr, 0x5A4380, { .reversed = false }); AtomicInstanceCB
    //RH_ScopedInstall(nullptr, 0x5A43A0, { .reversed = false });
    //RH_ScopedInstall(nullptr, 0x5A44A0, { .reversed = false }); DestroyTextureCB
    RH_ScopedInstall(PreprocessClothesDesc, 0x5A44C0, { .reversed = false });
    RH_ScopedInstall(ReleaseGeometry, 0x5A47B0, { .reversed = false });
    RH_ScopedGlobalInstall(FindAtomicFromNameCB, 0x5A47E0, { .reversed = false });
    RH_ScopedGlobalInstall(GetAtomicWithName, 0x5A4810, { .reversed = false });
    RH_ScopedInstall(sub_5A4840, 0x5A4840, { .reversed = false });
    RH_ScopedInstall(StoreBoneArray, 0x5A48B0, { .reversed = false });
    // RH_ScopedOverloadedInstall(BlendGeometry, "", 0x5A4940, RpGeometry* (*)(RpClump*, const char*, const char*, const char*, float, float, float));
    // RH_ScopedOverloadedInstall(BlendGeometry, "", 0x5A4F10, RpGeometry* (*)(RpClump*, const char*, const char*, float, float));
    RH_ScopedInstall(CopyGeometry, 0x5A5340, { .reversed = false });
    RH_ScopedInstall(ConstructGeometryArray, 0x5A55A0, { .reversed = false });
    RH_ScopedInstall(DestroySkinArrays, 0x5A56C0, { .reversed = false });
    RH_ScopedInstall(BuildBoneIndexConversionTable, 0x5A56E0);
    RH_ScopedInstall(CopyTexture, 0x5A5730, { .reversed = false });
    RH_ScopedInstall(PlaceTextureOnTopOfTexture, 0x5A57B0);
    RH_ScopedOverloadedInstall(BlendTextures, "Dst-Src", 0x5A5820, void (*)(RwTexture*, RwTexture*, float, float, int32));
    RH_ScopedOverloadedInstall(BlendTextures, "Dst-Src1-Src2", 0x5A59C0, void (*)(RwTexture*, RwTexture*, RwTexture*, float, float, float, int32));
    RH_ScopedOverloadedInstall(BlendTextures, "Dst-Src1-Src2-Tat", 0x5A5BC0, void (*)(RwTexture*, RwTexture*, RwTexture*, float, float, float, int32, RwTexture*));
    RH_ScopedInstall(InitPaletteOctTree, 0x5A5EB0, { .reversed = false });
    RH_ScopedInstall(ShutdownPaletteOctTree, 0x5A5EE0, { .reversed = false });
    RH_ScopedInstall(ReducePaletteOctTree, 0x5A5EF0, { .reversed = false });
    RH_ScopedInstall(AddColour, 0x5A5F00, { .reversed = false });
    RH_ScopedInstall(FillPalette, 0x5A5F30, { .reversed = false });
    RH_ScopedInstall(FindNearestColour, 0x5A5F40, { .reversed = false });
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
void CClothesBuilder::RequestGeometry(int32 modelId, uint32 modelNameKey) {
    CModelInfo::GetModelInfo(modelId)->bHasComplexHierarchy = true; // TODO/NOTE: Not sure
    uint32 offset, size;
    VERIFY(playerImg.FindItem(CKeyGen::AppendStringToKey(modelNameKey, ".DFF"), offset, size));
    CStreaming::RequestFile(modelId, offset, size, CClothes::ms_clothesImageId, STREAMING_PRIORITY_REQUEST | STREAMING_GAME_REQUIRED);
}

// 0x5A4220
int32 CClothesBuilder::RequestTexture(uint32 txdNameKey) {
    if (txdNameKey == 0) {
        return -1;
    }

    auto& defaultTxdIdx = StaticRef<uint32>(0xBC12D0);
    const auto defaultTxd = CTxdStore::defaultTxds[defaultTxdIdx];
    defaultTxdIdx = (defaultTxdIdx + 1) % 4;

    uint32 offset, size;
    VERIFY(playerImg.FindItem(CKeyGen::AppendStringToKey(txdNameKey, ".TXD"), offset, size));
    CStreaming::RequestFile(TXDToModelId(defaultTxdIdx), offset, size, CClothes::ms_clothesImageId, STREAMING_PRIORITY_REQUEST | STREAMING_GAME_REQUIRED);

    return defaultTxd;
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
void FindAtomicFromNameCB(RpAtomic* atomic, void* data) {
    plugin::Call<0x5A47E0, RpAtomic*, void*>(atomic, data);
}

// 0x5A4810
void GetAtomicWithName(RpClump* clump, const char* name) {
    plugin::Call<0x5A4810, RpClump*, const char*>(clump, name);
}

// 0x5A4840
void CClothesBuilder::sub_5A4840() {

}

// 0x5A48B0
void CClothesBuilder::StoreBoneArray(RpClump* clump, int32 a2) {
    plugin::Call<0x5A48B0, RpClump*, int32>(clump, a2);
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
void CClothesBuilder::DestroySkinArrays(RwMatrixWeights* weights, uint32* a2) {
    operator delete(weights);
    operator delete(a2);
}

// 0x5A56E0
void CClothesBuilder::BuildBoneIndexConversionTable(uint8* pTable, RpHAnimHierarchy* hier, int32 index) {
    for (const auto [tableIdx, boneId] : notsa::enumerate(gBoneIndices[index])) {
        if (boneId == -1) {
            break;
        }
        const auto idx = RpHAnimIDGetIndex(hier, boneId);
        pTable[tableIdx] = idx == 0xFF ? 0 : idx;
    }
}

// 0x5A5730
RwTexture* CClothesBuilder::CopyTexture(RwTexture* texture) {
    return plugin::CallAndReturn<RwTexture*, 0x5A5730, RwTexture*>(texture);
}

void AssertTextureLayouts(std::initializer_list<RwTexture*> textures) {
    assert(textures.size() >= 2);
    for (auto i = 0u; i < textures.size() - 1; i++) {
        const auto r1 = RwTextureGetRaster(textures.begin()[i]), r2 = RwTextureGetRaster(textures.begin()[i + 1]);

        assert(RwRasterGetStride(r1) == RwRasterGetStride(r2));
        assert(RwRasterGetWidth(r1) == RwRasterGetWidth(r2));
        assert(RwRasterGetHeight(r1) == RwRasterGetHeight(r2));
        assert(RwRasterGetDepth(r1) == RwRasterGetDepth(r2));
        assert(RwRasterGetDepth(r1) == 32);
    }
}

// 0x5A57B0
void CClothesBuilder::PlaceTextureOnTopOfTexture(RwTexture* dstTex, RwTexture* srcTex) {
    ZoneScoped;

    AssertTextureLayouts({ dstTex, srcTex });

    const auto dstRaster = RwTextureGetRaster(dstTex);
    const auto srcRaster = RwTextureGetRaster(srcTex);

    auto dstIt = (RwUInt32*)RwRasterLock(dstRaster, 0, rwRASTERLOCKWRITE | rwRASTERLOCKREAD);
    auto srcIt = (RwUInt32*)RwRasterLock(srcRaster, 0, rwRASTERLOCKWRITE | rwRASTERLOCKREAD);

    // NOTE: They don't skip the stride, but it's fine [This way vectorization should be easier for the compiler]
    for (auto i = RwRasterGetHeight(dstRaster) * RwRasterGetWidth(dstRaster); i-- > 0; dstIt++, srcIt++) {
        if (*srcIt & 0xFF000000) { // Check alpha != 0
            *dstIt = *srcIt;
        }
    }

    RwRasterUnlock(dstRaster);
    RwRasterUnlock(srcRaster);
}

// 0x5A5820
void CClothesBuilder::BlendTextures(RwTexture* dst, RwTexture* src, float r1, float r2, int32 numColors) {
    ZoneScoped;

    AssertTextureLayouts({ dst, src });

    const auto dstRaster = RwTextureGetRaster(dst);
    const auto srcRaster = RwTextureGetRaster(src);

    CTimer::Suspend();

    auto srcIt = RwRasterLock(srcRaster, 0, rwRASTERLOCKREAD);
    auto dstIt = RwRasterLock(dstRaster, 0, rwRASTERLOCKREAD | rwRASTERLOCKWRITE);

    for (auto i = RwRasterGetHeight(dstRaster) * RwRasterGetWidth(dstRaster); i-- > 0; dstIt++, srcIt++) {
        for (auto c = 3; i-- > 0; dstIt++, srcIt++) { // Copy RGB, alpha stays the same
            *dstIt = multiply_weighted<RwUInt8>({ { *dstIt, r1 }, { *srcIt, r2 } });
        }
    }

    RwRasterUnlock(dstRaster);
    RwRasterUnlock(srcRaster);

    CTimer::Resume();
}

// 0x5A59C0
void CClothesBuilder::BlendTextures(RwTexture* dst, RwTexture* src1, RwTexture* src2, float r1, float r2, float r3, int32) {
    ZoneScoped;

    AssertTextureLayouts({ dst, src1, src2 });

    const auto dstRaster  = RwTextureGetRaster(dst);
    const auto src1Raster = RwTextureGetRaster(src1);
    const auto src2Raster = RwTextureGetRaster(src2);

    CTimer::Suspend();

    auto src1It = RwRasterLock(src1Raster, 0, rwRASTERLOCKREAD);
    auto src2It = RwRasterLock(src2Raster, 0, rwRASTERLOCKREAD);
    auto dstIt  = RwRasterLock(dstRaster, 0, rwRASTERLOCKREAD | rwRASTERLOCKWRITE);

    for (auto i = RwRasterGetHeight(dstRaster) * RwRasterGetWidth(dstRaster); i-- > 0; dstIt++, src1It++, src2It++) {
        for (auto c = 3; i-- > 0; dstIt++, src1It++, src2It++) { // Copy RGB, alpha doesn't change
            *dstIt = multiply_weighted<RwUInt8>({ { *dstIt, r1 }, { *src1It, r2 }, { *src2It, r3 } });
        }
    }

    RwRasterUnlock(dstRaster);
    RwRasterUnlock(src1Raster);
    RwRasterUnlock(src2Raster);

    CTimer::Resume();
}

// 0x5A5BC0
void CClothesBuilder::BlendTextures(RwTexture* dst, RwTexture* src1, RwTexture* src2, float r1, float r2, float r3, int32 numColors, RwTexture* tattoos) {
    ZoneScoped;

    AssertTextureLayouts({ dst, src1, src2, tattoos });

    const auto dstRaster = RwTextureGetRaster(dst);
    const auto src1Raster = RwTextureGetRaster(src1);
    const auto src2Raster = RwTextureGetRaster(src2);
    const auto tatRaster = RwTextureGetRaster(src2);

    CTimer::Suspend();

    auto src1It = RwRasterLock(src1Raster, 0, rwRASTERLOCKREAD);
    auto src2It = RwRasterLock(src2Raster, 0, rwRASTERLOCKREAD);
    auto tatIt  = RwRasterLock(tatRaster, 0, rwRASTERLOCKREAD);
    auto dstIt  = RwRasterLock(dstRaster, 0, rwRASTERLOCKREAD | rwRASTERLOCKWRITE);

    for (auto i = RwRasterGetHeight(dstRaster) * RwRasterGetWidth(dstRaster); i-- > 0; dstIt++, src1It++, src2It++, tatIt++) {
        const auto tatAlphaT = (float)tatIt[3] / 255.f;
        for (auto c = 3; i-- > 0; dstIt++, src1It++, src2It++, tatIt++) { // Copy RGB, alpha doesn't change
            *dstIt = lerp(multiply_weighted<RwUInt8>({ { *dstIt, r1 }, { *src1It, r2 }, { *src2It, r3 } }), *tatIt, tatAlphaT);
        }
    }

    RwRasterUnlock(dstRaster);
    RwRasterUnlock(src1Raster);
    RwRasterUnlock(src2Raster);
    RwRasterUnlock(tatRaster);

    CTimer::Resume();
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

// 0x5A5F00
bool CClothesBuilder::AddColour(RwRGBA* color) {
    return plugin::CallAndReturn<bool, 0x5A5F00, RwRGBA*>(color);
    /*
    if (!color->alpha)
        gOctTreeBase.m_bHasTransparentPixels = 1;

    return gOctTreeBase.Insert(color);
    */
}

// 0x5A5F30
void CClothesBuilder::FillPalette(RwRGBA* color) {
    // gOctTreeBase.FillPalette(color);
}

// unused
// 0x5A5F40
int32 CClothesBuilder::FindNearestColour(RwRGBA* color) {
    return plugin::CallAndReturn<int32, 0x5A5F40, RwRGBA*>(color);
    /*
    if (color->alpha)
        return gOctTreeBase.FindNearestColour(color);
    else
        return 0;
    */
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
