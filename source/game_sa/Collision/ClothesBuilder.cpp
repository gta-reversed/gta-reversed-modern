#include "StdInc.h"

#include "ClothesBuilder.h"

CDirectory& playerImg = *(CDirectory*)0xBC12C0;
CDirectory::DirectoryInfo& playerImgEntries = *(CDirectory::DirectoryInfo*)0xBBCDC8;

void CClothesBuilder::InjectHooks() {
    using namespace ReversibleHooks;
    // Install("CClothesBuilder", "LoadCdDirectory", 0x5A4190, &CClothesBuilder::LoadCdDirectory);
    // Install("CClothesBuilder", "RequestGeometry", 0x5A41C0, &CClothesBuilder::RequestGeometry);
    // Install("CClothesBuilder", "RequestTexture", 0x5A4220, &CClothesBuilder::RequestTexture); 
    // todo: Install("CClothesBuilder", "f5A42B0", 0x5A42B0, &nullptr); 
    // todo: Install("CClothesBuilder", "_AtomicInstanceCB", 0x5A4380, &nullptr);
    // todo: Install("CClothesBuilder", "f5A43A0", 0x5A43A0, &nullptr);
    // todo: Install("CClothesBuilder", "DestroyTextureCB", 0x5A44A0, &nullptr);
    // Install("CClothesBuilder", "PreprocessClothesDesc", 0x5A44C0, &CClothesBuilder::PreprocessClothesDesc);
    // Install("CClothesBuilder", "ReleaseGeometry", 0x5A47B0, &CClothesBuilder::ReleaseGeometry);
    // Install("CClothesBuilder", "FindAtomicFromNameCB", 0x5A47E0, &FindAtomicFromNameCB);
    // Install("CClothesBuilder", "GetAtomicWithName", 0x5A4810, &GetAtomicWithName);
    // Install("CClothesBuilder", "f5A4840", 0x5A4840, &CClothesBuilder::sub_5A4840);
    // Install("CClothesBuilder", "StoreBoneArray", 0x5A48B0, &CClothesBuilder::StoreBoneArray);
    // Install("CClothesBuilder", "BlendGeometry", 0x5A4940, static_cast<RpGeometry* (*)(RpClump*, const char*, const char*, const char*, float, float, float)>(&CClothesBuilder::BlendGeometry));
    // Install("CClothesBuilder", "BlendGeometry", 0x5A4F10, static_cast<RpGeometry* (*)(RpClump*, const char*, const char*, float, float)>(&CClothesBuilder::BlendGeometry));
    // Install("CClothesBuilder", "CopyGeometry", 0x5A5340, &CClothesBuilder::CopyGeometry);
    // Install("CClothesBuilder", "ConstructGeometryArray", 0x5A55A0, &CClothesBuilder::ConstructGeometryArray);
    // Install("CClothesBuilder", "DestroySkinArrays", 0x5A56C0, &CClothesBuilder::DestroySkinArrays);
    // Install("CClothesBuilder", "BuildBoneIndexConversionTable", 0x5A56E0, &CClothesBuilder::BuildBoneIndexConversionTable);
    // Install("CClothesBuilder", "CopyTexture", 0x5A5730, &CClothesBuilder::CopyTexture);
    // Install("CClothesBuilder", "PlaceTextureOnTopOfTexture", 0x5A57B0, &CClothesBuilder::PlaceTextureOnTopOfTexture);
    // Install("CClothesBuilder", "BlendTextures", 0x5A5820, static_cast<void (*)(RwTexture*, RwTexture*, float, float, int32)>(&CClothesBuilder::BlendTextures));
    // Install("CClothesBuilder", "BlendTextures", 0x5A59C0, static_cast<void (*)(RwTexture*, RwTexture*, RwTexture*, float, float, float, int32)>(&CClothesBuilder::BlendTextures));
    // Install("CClothesBuilder", "BlendTextures", 0x5A5BC0, static_cast<void (*)(RwTexture*, RwTexture*, RwTexture*, float, float, float, int32, RwTexture*)>(&CClothesBuilder::BlendTextures));
    // Install("CClothesBuilder", "InitPaletteOctTree", 0x5A5EB0, &CClothesBuilder::InitPaletteOctTree);
    // Install("CClothesBuilder", "ShutdownPaletteOctTree", 0x5A5EE0, &CClothesBuilder::ShutdownPaletteOctTree);
    // Install("CClothesBuilder", "ReducePaletteOctTree", 0x5A5EF0, &CClothesBuilder::ReducePaletteOctTree);
    // Install("CClothesBuilder", "AddColour", 0x5A5F00, &CClothesBuilder::AddColour);
    // Install("CClothesBuilder", "FillPalette", 0x5A5F30, &CClothesBuilder::FillPalette);
    // Install("CClothesBuilder", "FindNearestColour", 0x5A5F40, &CClothesBuilder::FindNearestColour);
    // Install("CClothesBuilder", "GetTextureFromTxdAndLoadNextTxd", 0x5A5F70, &GetTextureFromTxdAndLoadNextTxd);
    // Install("CClothesBuilder", "ConstructTextures", 0x5A6040, &CClothesBuilder::ConstructTextures);
    // Install("CClothesBuilder", "ConstructGeometryAndSkinArrays", 0x5A6530, &CClothesBuilder::ConstructGeometryAndSkinArrays);
    // Install("CClothesBuilder", "ReducePaletteSize", 0x5A6870, &CClothesBuilder::ReducePaletteSize);
    // Install("CClothesBuilder", "CreateSkinnedClump", 0x5A69D0, &CClothesBuilder::CreateSkinnedClump);
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
void CClothesBuilder::BuildBoneIndexConversionTable(uint8* a1, RpHAnimHierarchy* a2, int32 a3) {
    plugin::Call<0x5A56E0, uint8*, RpHAnimHierarchy*, int32>(a1, a2, a3);
}

// 0x5A5730
RwTexture* CClothesBuilder::CopyTexture(RwTexture* texture) {
    return plugin::CallAndReturn<RwTexture*, 0x5A5730, RwTexture*>(texture);
}

// 0x5A57B0
void CClothesBuilder::PlaceTextureOnTopOfTexture(RwTexture* texture1, RwTexture* texture2) {
    plugin::Call<0x5A57B0, RwTexture*, RwTexture*>(texture1, texture2);
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
