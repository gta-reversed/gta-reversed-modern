#include "StdInc.h"

#include "PlantMgr.h"
#include "GrassRenderer.h"
#include "PlantColEntEntry.h"
#include "PlantLocTri.h"
#include "PlantSurfPropMgr.h"
#include <extensions/enumerate.hpp>

// 0x5DD100 (todo: move)
static void AtomicCreatePrelitIfNeeded(RpAtomic* atomic) {
    plugin::Call<0x5DD100, RpAtomic*>(atomic);
}

// 0x5DD1E0 (do not hook! it has retarded calling conv)
static bool GeometrySetPrelitConstantColor(RpGeometry* geometry, uint32 color) {
    if ((geometry->flags & rpGEOMETRYPRELIT) == 0) {
        return false;
    }

    RpGeometryLock(geometry, 4095);
    if (geometry->preLitLum) {
        std::memset(geometry->preLitLum, CRGBA(255, 255, 255, 255).ToInt(), geometry->numVertices);
    }
    RpGeometryUnlock(geometry);

    return true;
}

// 0x5DD220
static bool LoadModels(std::initializer_list<const char*> models, RpAtomic* (&atomics)[4]) {
    for (auto& model : models) {
        auto stream = RwStreamOpen(rwSTREAMFILENAME, rwSTREAMREAD, std::format("models\\grass\\{}", model).c_str());
        RpClump* clump = nullptr;

        if (stream && RwStreamFindChunk(stream, rwID_CLUMP, nullptr, nullptr)) {
            clump = RpClumpStreamRead(stream);
        }
        RwStreamClose(stream, nullptr);
        assert(clump);

        auto firstAtomic = GetFirstAtomic(clump);
        SetFilterModeOnAtomicsTextures(firstAtomic, rwFILTERMIPLINEAR);
        AtomicCreatePrelitIfNeeded(firstAtomic);

        auto geometry = firstAtomic->geometry;
        RpGeometryLock(geometry, 4095); // todo: enum?
        geometry->flags = (geometry->flags & 0xFFFFFF8F) | rpGEOMETRYMODULATEMATERIALCOLOR;
        RpGeometryUnlock(geometry);
        GeometrySetPrelitConstantColor(geometry, CRGBA(255, 255, 255, 255).ToInt());

        auto data = 0x32000000;
        RpGeometryForAllMaterials(geometry, [](RpMaterial* material, void* data) {
            material->color = *(RwRGBA*)data;
            RpMaterialSetTexture(material, tex_gras07Si);
            return material;
        }, &data);

        auto atomicCopy = RpAtomicClone(firstAtomic);
        RpClumpDestroy(clump);
        SetFilterModeOnAtomicsTextures(atomicCopy, rwFILTERLINEAR);
        RpAtomicSetFrame(atomicCopy, RwFrameCreate());
    }

    return true;
}

void CPlantMgr::InjectHooks() {
    RH_ScopedClass(CPlantMgr);
    RH_ScopedCategory("Plant");

    RH_ScopedInstall(Initialise, 0x5DD910);
    RH_ScopedInstall(Shutdown, 0x5DB940);
    RH_ScopedInstall(ReloadConfig, 0x5DD780, {.reversed = false});
    RH_ScopedInstall(MoveLocTriToList, 0x5DB590);
    RH_ScopedInstall(MoveColEntToList, 0x5DB5F0);
    RH_ScopedInstall(SetPlantFriendlyFlagInAtomicMI, 0x5DB650, {.reversed = false});
    RH_ScopedInstall(Update, 0x5DCFA0, {.reversed = false});
    RH_ScopedInstall(PreUpdateOnceForNewCameraPos, 0x5DCF30);
    RH_ScopedInstall(UpdateAmbientColor, 0x5DB310);
    RH_ScopedInstall(CalculateWindBending, 0x5DB3D0, {.reversed = false});
    RH_ScopedInstall(_ColEntityCache_Add, 0x5DBEB0, {.reversed = false});
    RH_ScopedInstall(_ColEntityCache_FindInCache, 0x5DB530, {.reversed = false});
    RH_ScopedInstall(_ColEntityCache_Remove, 0x5DBEF0, {.reversed = false});
    RH_ScopedInstall(_ColEntityCache_Update, 0x5DC510, {.reversed = false});
    RH_ScopedInstall(_ProcessEntryCollisionDataSections, 0x5DCD80, {.reversed = false});
    RH_ScopedInstall(_UpdateLocTris, 0x5DCF00, {.reversed = false});

    RH_ScopedGlobalInstall(LoadModels, 0x5DD220);

    // debug shit, all of them just return true.
    // addresses (probably not in order): 0x5DB550 - 0x5DB580

    // RH_ScopedInstall(DbgCountCachedEntities, 0x0, {.reversed = false});
    // RH_ScopedInstall(DbgCountLocTrisAndPlants, 0x0, {.reversed = false});
    // RH_ScopedInstall(DbgRenderCachedEntities, 0x0, {.reversed = false});
    // RH_ScopedInstall(DbgRenderLocTris, 0x0, {.reversed = false});
}

// 0x5DD910
bool CPlantMgr::Initialise() {
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
        return texture;
    };

    for (auto&& [i, tab] : notsa::enumerate(PC_PlantTextureTab | rng::views::take(2))) {
        for (auto&& [j, tex] : notsa::enumerate(tab)) {
            tex = ReadTexture(std::format("txgrass{}_{}", i, j).c_str());
        }
    }
    tex_gras07Si = ReadTexture("gras07Si");
    CTxdStore::PopCurrentTxd();
    CStreaming::IHaveUsedStreamingMemory();

    grassTexturesPtr[0] = grassTexturesPtr[2] = *PC_PlantTextureTab[0];
    grassTexturesPtr[1] = grassTexturesPtr[3] = *PC_PlantTextureTab[1];

    const auto models1 = { "grass0_1.dff", "grass0_2.dff", "grass0_3.dff", "grass0_4.dff" };
    const auto models2 = { "grass1_1.dff", "grass1_2.dff", "grass1_3.dff", "grass1_4.dff" };
    if (LoadModels(models1, PC_PlantModelsTab[0]) && LoadModels(models2, PC_PlantModelsTab[1])) {
        grassModelsPtr[0] = grassModelsPtr[2] = *PC_PlantModelsTab[0];
        grassModelsPtr[1] = grassModelsPtr[3] = *PC_PlantModelsTab[1];

        for (auto i = 0u; i < 4u; i++) {
            CGrassRenderer::SetPlantModelsTab(i, PC_PlantModelsTab[0]); // grassModelsPtr[0]
        }

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
        for (auto& atomic : atomics) {
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

    const auto DestroyTextures = [](auto& textures) {
        for (auto& texture : textures) {
            if (texture) {
                RwTextureDestroy(texture);
                texture = nullptr;
            }
        }
    };

    for (auto i = 0u; i < 4u; i++) {
        DestroyAtomics(PC_PlantModelsTab[i]);
        DestroyTextures(PC_PlantTextureTab[i]);
    }

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
void CPlantMgr::MoveLocTriToList(CPlantLocTri*& oldList, CPlantLocTri*& newList, CPlantLocTri* triangle) {
    if (auto next = triangle->m_NextTri) {
        if (auto prev = triangle->m_PrevTri) {
            prev->m_NextTri = next;
            next->m_PrevTri = prev;
        } else {
            next->m_PrevTri = nullptr;
        }
    } else {
        if (oldList = triangle->m_PrevTri) {
            oldList->m_NextTri = nullptr;
        }
    }
    triangle->m_PrevTri = newList;
    triangle->m_NextTri = nullptr;
    newList = triangle;

    if (auto prev = triangle->m_PrevTri) {
        prev->m_NextTri = triangle;
    }
}

// 0x5DB5F0
// unused/inlined
void CPlantMgr::MoveColEntToList(CPlantColEntEntry*& oldList, CPlantColEntEntry*& newList, CPlantColEntEntry* entry) {
    if (auto next = entry->m_NextEntry) {
        if (auto prev = entry->m_PrevEntry) {
            prev->m_NextEntry = next;
            next->m_PrevEntry = prev;
        } else {
            next->m_PrevEntry = nullptr;
        }
    } else {
        if (oldList = entry->m_PrevEntry) {
            oldList->m_NextEntry = nullptr;
        }
    }
    entry->m_PrevEntry = newList;
    entry->m_NextEntry = nullptr;
    newList = entry;

    if (auto prev = entry->m_PrevEntry) {
        prev->m_NextEntry = entry;
    }
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

// 0x5DCF30
void CPlantMgr::PreUpdateOnceForNewCameraPos(const CVector& posn) {
    CGrassRenderer::SetCurrentScanCode(++m_scanCode);
    CGrassRenderer::SetGlobalCameraPos(posn);
    UpdateAmbientColor();
    CGrassRenderer::SetGlobalWindBending(CalculateWindBending());
    _ColEntityCache_Update(posn, false);

    for (auto i = m_CloseColEntListHead; i; i = i->m_NextEntry) {
        _ProcessEntryCollisionDataSections(i, posn, 0xFAFAFAFA);
    }
}

// 0x5DB310
void CPlantMgr::UpdateAmbientColor() {
    auto r = 64 + (uint32)(CTimeCycle::GetAmbientRed()   * 2.5f * 255.0f);
    auto g = 64 + (uint32)(CTimeCycle::GetAmbientGreen() * 2.5f * 255.0f);
    auto b = 64 + (uint32)(CTimeCycle::GetAmbientBlue()  * 2.5f * 255.0f);
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
