#include "StdInc.h"

#include "PlantMgr.h"
#include "GrassRenderer.h"
#include "PlantColEntEntry.h"
#include "PlantSurfPropMgr.h"
#include <extensions/enumerate.hpp>

RwTexture* (&CPlantMgr::PC_PlantTextureTab0)[4] = *(RwTexture * (*)[4])0xC039A0;
RwTexture* (&CPlantMgr::PC_PlantTextureTab1)[4] = *(RwTexture * (*)[4])0xC039B0;
RwTexture* (&CPlantMgr::PC_PlantTextureTab2)[4] = *(RwTexture * (*)[4])0xC039C0;
RwTexture* (&CPlantMgr::PC_PlantTextureTab3)[4] = *(RwTexture * (*)[4])0xC039D0;

RpAtomic* (&CPlantMgr::PC_PlantModelsTab0)[4] = *(RpAtomic * (*)[4])0xC039F0;
RpAtomic* (&CPlantMgr::PC_PlantModelsTab1)[4] = *(RpAtomic * (*)[4])0xC03A00;
RpAtomic* (&CPlantMgr::PC_PlantModelsTab2)[4] = *(RpAtomic * (*)[4])0xC03A10;
RpAtomic* (&CPlantMgr::PC_PlantModelsTab3)[4] = *(RpAtomic * (*)[4])0xC03A20;

RwTexture* (&grassTexturesPtr)[4] = *(RwTexture * (*)[4])0xC039E0;
RpAtomic* (&grassModelsPtr)[4] = *(RpAtomic * (*)[4])0xC03A30;
RwTexture*& tex_gras07Si = *(RwTexture**)0xC09174;

// 0x5DD220
static bool LoadModels(std::initializer_list<const char*> models, RpAtomic* (&atomics)[4]) {
    return plugin::CallAndReturn<bool, 0x5DD220, std::initializer_list<const char*>, RpAtomic*(&)[4]>(models, atomics);
}

void CPlantMgr::InjectHooks() {
    RH_ScopedClass(CPlantMgr);
    RH_ScopedCategory("Plant");

    RH_ScopedInstall(Initialise, 0x5DD910, {.reversed = false});
    RH_ScopedInstall(Shutdown, 0x5DB940);
    RH_ScopedInstall(ReloadConfig, 0x5DD780, {.reversed = false});
    RH_ScopedInstall(MoveLocTriToList, 0x5DB590, {.reversed = false});
    RH_ScopedInstall(SetPlantFriendlyFlagInAtomicMI, 0x5DB650, {.reversed = false});
    RH_ScopedInstall(Update, 0x5DCFA0, {.reversed = false});
    RH_ScopedInstall(UpdateAmbientColor, 0x5DB310);
    RH_ScopedInstall(CalculateWindBending, 0x5DB3D0, {.reversed = false});
    RH_ScopedInstall(_ColEntityCache_Add, 0x5DBEB0, {.reversed = false});
    RH_ScopedInstall(_ColEntityCache_FindInCache, 0x5DB530, {.reversed = false});
    RH_ScopedInstall(_ColEntityCache_Remove, 0x5DBEF0, {.reversed = false});
    RH_ScopedInstall(_ColEntityCache_Update, 0x5DC510, {.reversed = false});
    RH_ScopedInstall(_ProcessEntryCollisionDataSections, 0x5DCD80, {.reversed = false});
    RH_ScopedInstall(_UpdateLocTris, 0x5DCF00, {.reversed = false});

    RH_ScopedGlobalInstall(LoadModels, 0x5DD220, {.reversed = false});

    // debug shit, all of them just return true.
    // addresses (probably not in order): 0x5DB550 - 0x5DB580

    // RH_ScopedInstall(DbgCountCachedEntities, 0x0, {.reversed = false});
    // RH_ScopedInstall(DbgCountLocTrisAndPlants, 0x0, {.reversed = false});
    // RH_ScopedInstall(DbgRenderCachedEntities, 0x0, {.reversed = false});
    // RH_ScopedInstall(DbgRenderLocTris, 0x0, {.reversed = false});
}

// 0x5DD910
bool CPlantMgr::Initialise() {
    return plugin::CallAndReturn<bool, 0x5DD910>();

    if (!ReloadConfig())
        return false;

    CStreaming::MakeSpaceFor(0x8800);
    CStreaming::ImGonnaUseStreamingMemory();
    CTxdStore::PushCurrentTxd();
    auto slot = CTxdStore::FindOrAddTxdSlot("grass_pc");
    CTxdStore::LoadTxd(slot, "models\\grass\\plant1.txd");
    CTxdStore::AddRef(slot);
    CTxdStore::SetCurrentTxd(slot);

    const auto ReadTexture = [](const char* name) {
        auto texture = RwTextureRead(name, nullptr);
        RwTextureSetAddressing(texture, rwTEXTUREADDRESSWRAP);
        RwTextureSetFilterMode(texture, rwFILTERLINEAR);
        return  texture;
    };

    for (auto&& [i, tex] : notsa::enumerate(PC_PlantTextureTab0)) {
        tex = ReadTexture(std::format("txgrass0_{}", i).c_str());
    }

    for (auto&& [i, tex] : notsa::enumerate(PC_PlantTextureTab1)) {
        tex = ReadTexture(std::format("txgrass1_{}", i).c_str());
    }

    tex_gras07Si = ReadTexture("gras07Si");
    CTxdStore::PopCurrentTxd();
    CStreaming::IHaveUsedStreamingMemory();

    grassTexturesPtr[0] = grassTexturesPtr[2] = * PC_PlantTextureTab0;
    grassTexturesPtr[1] = grassTexturesPtr[3] = * PC_PlantTextureTab1;

    const auto models1 = { "grass0_1.dff", "grass0_2.dff", "grass0_3.dff", "grass0_4.dff" };
    const auto models2 = { "grass1_1.dff", "grass1_2.dff", "grass1_3.dff", "grass1_4.dff" };
    if (LoadModels(models1, PC_PlantModelsTab0) && LoadModels(models2, PC_PlantModelsTab1)) {
        grassModelsPtr[0] = *PC_PlantModelsTab0;
        grassModelsPtr[1] = *PC_PlantModelsTab1;
        grassModelsPtr[2] = *PC_PlantModelsTab0;
        grassModelsPtr[3] = *PC_PlantModelsTab1;

        CGrassRenderer::SetPlantModelsTab(0, PC_PlantModelsTab0);
        CGrassRenderer::SetPlantModelsTab(1, PC_PlantModelsTab0); // grassModelsPtr[0] ?
        CGrassRenderer::SetPlantModelsTab(2, PC_PlantModelsTab0); // grassModelsPtr[0] ?
        CGrassRenderer::SetPlantModelsTab(3, PC_PlantModelsTab0); // grassModelsPtr[0] ?

        CGrassRenderer::SetCloseFarAlphaDist(3.0f, 60.0f);
        return true;
    }

    return false;
}

// 0x5DB940
void CPlantMgr::Shutdown() {
    for (auto it = m_CloseColEntListHead; it; it = it->m_NextEntry) {
        it->ReleaseEntry();
    }

    const auto DestroyAtomics = [](auto& atomics) {
        for (auto atomic : atomics) {
            if (atomic) {
                if (auto frame = RpAtomicGetFrame(atomic)) {
                    RpAtomicSetFrame(atomic, nullptr);
                    RwFrameDestroy(frame);
                }
                RpAtomicDestroy(atomic);
                atomic = nullptr;
            }
        }
    };
    DestroyAtomics(PC_PlantModelsTab0);
    DestroyAtomics(PC_PlantModelsTab1);
    DestroyAtomics(PC_PlantModelsTab2);
    DestroyAtomics(PC_PlantModelsTab3);

    const auto DestroyTextures = [](auto& textures) {
        for (auto texture : textures) {
            if (texture) {
                RwTextureDestroy(texture);
                texture = nullptr;
            }
        }
    };
    DestroyTextures(PC_PlantTextureTab0);
    DestroyTextures(PC_PlantTextureTab1);
    DestroyTextures(PC_PlantTextureTab2);
    DestroyTextures(PC_PlantTextureTab3);

    CTxdStore::SafeRemoveTxdSlot("grass_pc");
}

// 0x5DD780
bool CPlantMgr::ReloadConfig() {
    return plugin::CallAndReturn<bool, 0x5DD780>();

    if (!CPlantSurfPropMgr::Initialise()) {
        return false;
    }

    std::ranges::fill(m_CloseLocTriListHead, nullptr);
    m_UnusedLocTriListHead = m_LocTrisTab;

    // todo: while

    return true;
}

// 0x5DB590
void CPlantMgr::MoveLocTriToList(CPlantLocTri** a1, CPlantLocTri** a2, CPlantLocTri* a3) {
    plugin::Call<0x5DB590, CPlantLocTri**, CPlantLocTri**, CPlantLocTri*>(a1, a2, a3);
}

// 0x5DB650
void CPlantMgr::SetPlantFriendlyFlagInAtomicMI(CAtomicModelInfo* ami) {
    plugin::Call<0x5DB650, CAtomicModelInfo*>(ami);
}

// 0x5DCFA0
void CPlantMgr::Update(const CVector& cameraPosition) {
    return plugin::Call<0x5DCFA0, const CVector&>(cameraPosition);

    static int8& cache = *(int8*)0xC09171;
    static int8& section = *(int8*)0xC09170;

    IncrementScanCode();
    CGrassRenderer::SetCurrentScanCode(m_scanCode);
    CGrassRenderer::SetGlobalCameraPos(cameraPosition);

    UpdateAmbientColor();
    CGrassRenderer::SetGlobalWindBending(CalculateWindBending());

    _ColEntityCache_Update(cameraPosition, (++cache % MAX_PLANTS) != 0 ? true : false);

    auto prev = m_CloseColEntListHead;
    for (auto i = section++ % 8; m_CloseColEntListHead; prev = m_CloseColEntListHead->m_NextEntry)
        _ProcessEntryCollisionDataSections(prev, cameraPosition, i);
}

// 0x5DB310
void CPlantMgr::UpdateAmbientColor() {
    auto r = 64 - (uint32)(CTimeCycle::GetAmbientRed()   * 2.5f * -255.0f);
    auto g = 64 - (uint32)(CTimeCycle::GetAmbientGreen() * 2.5f * -255.0f);
    auto b = 64 - (uint32)(CTimeCycle::GetAmbientBlue()  * 2.5f * -255.0f);
    m_AmbientColor.r = (uint8)std::max(r, 255u);
    m_AmbientColor.g = (uint8)std::max(g, 255u);
    m_AmbientColor.b = (uint8)std::max(b, 255u);
}

// 0x5DB3D0
float CPlantMgr::CalculateWindBending() {
    return plugin::CallAndReturn<float, 0x5DB3D0>();
}

// 0x5DBAE0
void CPlantMgr::Render() {
    plugin::Call<0x5DBAE0>();
}

// 0x5DBEB0
void CPlantMgr::_ColEntityCache_Add(CEntity* entity, bool a2) {
    plugin::Call<0x5DBEB0, CEntity*>(entity, a2);
}

// 0x5DB530
void CPlantMgr::_ColEntityCache_FindInCache(CEntity* entity) {
    plugin::Call<0x5DB530, CEntity*>(entity);
}

// 0x5DBEF0
void CPlantMgr::_ColEntityCache_Remove(CEntity* entity) {
    plugin::Call<0x5DBEF0, CEntity*>(entity);
}

// 0x5DC510
void CPlantMgr::_ColEntityCache_Update(const CVector& cameraPos, bool last) {
    plugin::Call<0x5DC510, const CVector&, bool>(cameraPos, last);
}

// 0x5DCD80
void CPlantMgr::_ProcessEntryCollisionDataSections(CPlantColEntEntry* entry, const CVector& center, int32 a3) {
    plugin::Call<0x5DCD80, CPlantColEntEntry*, const CVector&, int32>(entry, center, a3);
}

// 0x5DC8B0
void CPlantMgr::_ProcessEntryCollisionDataSections_AddLocTris(CPlantColEntEntry*, const CVector&, int32, int32, int32) {
    assert(0);
}

// 0x5DBF20
void CPlantMgr::_ProcessEntryCollisionDataSections_RemoveLocTris(CPlantColEntEntry*, const CVector&, int32, int32, int32) {
    assert(0);
}

// 0x5DCF00
void CPlantMgr::_UpdateLocTris(const CVector& center, int32 a2) {
    for (auto i = m_CloseColEntListHead; i; i = i->m_NextEntry) {
        _ProcessEntryCollisionDataSections(i, center, a2);
    }
}

bool CPlantMgr::DbgCountCachedEntities(uint32*) {
    return true;
}

bool CPlantMgr::DbgCountLocTrisAndPlants(uint32, uint32*, uint32*) {
    return true;
}

bool CPlantMgr::DbgRenderCachedEntities(uint32*) {
    return true;
}

bool CPlantMgr::DbgRenderLocTris() {
    return true;
}
