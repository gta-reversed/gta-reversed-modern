/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"
#include "IplStore.h"
#include "tBinaryIplFile.h"
#include "extensions/enumerate.hpp"
#include "TheCarGenerators.h"

int32& ms_currentIPLAreaCode = *(int32*)0x8E3EF8;

// Izzotop: tested, but not reviewed

void CIplStore::InjectHooks() {
    RH_ScopedClass(CIplStore);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(AddIplsNeededAtPosn, 0x4045B0);
    RH_ScopedInstall(LoadIpl, 0x406080);
    RH_ScopedInstall(Shutdown, 0x405FA0);
    RH_ScopedInstall(Initialise, 0x405EC0);
    RH_ScopedInstall(LoadIplBoundingBox, 0x405C00);
    RH_ScopedInstall(RemoveIplSlot, 0x405B60);
    RH_ScopedInstall(AddIplSlot, 0x405AC0);
    RH_ScopedInstall(RemoveIplWhenFarAway, 0x4058D0);
    RH_ScopedInstall(RemoveIplAndIgnore, 0x405890);
    RH_ScopedInstall(RequestIplAndIgnore, 0x405850);
    RH_ScopedInstall(LoadAllRemainingIpls, 0x405780);
    RH_ScopedInstall(RemoveAllIpls, 0x405720);
    RH_ScopedInstall(HaveIplsLoaded, 0x405600);
    RH_ScopedInstall(RequestIpls, 0x405520);
    RH_ScopedInstall(Load, 0x5D54A0, { .reversed = false });
    RH_ScopedInstall(Save, 0x5D5420, { .reversed = false });
    RH_ScopedInstall(EnsureIplsAreInMemory, 0x4053F0);
    RH_ScopedInstall(RemoveRelatedIpls, 0x405110);
    RH_ScopedInstall(SetupRelatedIpls, 0x404DE0, { .reversed = false });
    RH_ScopedInstall(EnableDynamicStreaming, 0x404D30);
    RH_ScopedInstall(IncludeEntity, 0x404C90);
    RH_ScopedInstall(GetBoundingBox, 0x404C70);
    RH_ScopedInstall(RemoveIpl, 0x404B20);
    RH_ScopedInstall(FindIplSlot, 0x404AC0);
    RH_ScopedInstall(SetIsInterior, 0x404A90);
    RH_ScopedInstall(GetIplName, 0x404A60);
    RH_ScopedInstall(GetIplEntityIndexArray, 0x4047B0);
    RH_ScopedInstall(GetNewIplEntityIndexArray, 0x404780);
    RH_ScopedInstall(SetIplsRequired, 0x404700);
    RH_ScopedInstall(ClearIplsNeededAtPosn, 0x4045E0);
    RH_ScopedInstall(LoadIpls, 0x405170, { .reversed = false });
    RH_ScopedGlobalInstall(SetIfInteriorIplIsRequired, 0x4045F0);
    RH_ScopedGlobalInstall(SetIfIplIsRequired, 0x404660);
    RH_ScopedGlobalInstall(SetIfIplIsRequiredReducedBB, 0x404690);
}

/*!
 * @addr 0x405EC0
 * @brief Allocate pool if it doesn't exist yet, allocate quad tree, etc..
 */
void CIplStore::Initialise() {
    gbIplsNeededAtPosn = false;

    if (!ms_pPool) {
        ms_pPool = new CPool<IplDef>(TOTAL_IPL_MODEL_IDS, "IPL Files");
    }

    AddIplSlot("generic");

    NumIplEntityIndexArrays = 0;
    ppCurrIplInstance = nullptr;

    ms_pQuadTree = new CQuadTreeNode(WORLD_BOUNDS, 3);
    assert(ms_pQuadTree);
}

/*!
 * @addr 0x405FA0
 */
void CIplStore::Shutdown() {
    RemoveAllIpls();
    for (auto i = 0; i < ms_pPool->GetSize(); i++) {
        if (!ms_pPool->IsFreeSlotAtIndex(i)) {
            RemoveIplSlot(i);
        }
    }
    delete ms_pPool;
    ms_pPool = nullptr;

    for (auto array : IplEntityIndexArrays | rng::views::take(NumIplEntityIndexArrays)) {
        delete array;
    }
    NumIplEntityIndexArrays = 0;

    delete ms_pQuadTree;
    ms_pQuadTree = nullptr;
}

/*!
 * @addr 0x405AC0
 * @returns Slot index
 */
int32 CIplStore::AddIplSlot(const char* name) {
    const auto def = new (ms_pPool->New()) IplDef{ name }; // MOTE: Seemingly they didn't overload `operator new` for it..
    return ms_pPool->GetIndex(def);
}

/*!
 * @addr 0x4045B0
 */
void CIplStore::AddIplsNeededAtPosn(const CVector& posn) {
    gvecIplsNeededAtPosn = posn;
    gbIplsNeededAtPosn = true;
}

/*!
 * @addr 0x4045E0
 */
void CIplStore::ClearIplsNeededAtPosn() {
    gbIplsNeededAtPosn = false;
}

/*!
 * @addr 0x404D30
 */
void CIplStore::EnableDynamicStreaming(int32 iplSlotIndex, bool enable) {
    GetInSlot(iplSlotIndex)->m_bDisableDynamicStreaming = !enable;
}

eAreaCodes ResolveAreaCode(int32 ec) {
    if (ec == -1) {
        if (const auto player = FindPlayerPed()) {
            return player->m_nAreaCode;
        }
        return (eAreaCodes)CGame::currArea;
    }
    return (eAreaCodes)ec;
}

/*!
 * @addr 0x4053F0
 * @brief Make sure all IPls that requested around posn (in a 190 unit circle) are loaded.
 */
void CIplStore::EnsureIplsAreInMemory(const CVector& posn) {
    if (CStreaming::ms_disableStreaming) {
        return;
    }

    if (ResolveAreaCode(-1) != CGame::currArea) {
        return;
    }

    SetIplsRequired(posn);

    for (auto slot = 1 /*skip first*/; slot < TOTAL_IPL_MODEL_IDS; slot++) {
        const auto def = GetInSlot(slot);
        if (!def) {
            continue;
        }

        if (def->m_bDisableDynamicStreaming || !def->m_bLoadRequest) {
            continue;
        }

        if (!def->m_boundBox.IsPointInside(posn, -190.f) || CStreaming::IsModelLoaded(IPLToModelId(slot))) {
            continue;
        }

        // Load IPL

        CStreaming::RequestModel(IPLToModelId(slot), STREAMING_PRIORITY_REQUEST | STREAMING_KEEP_IN_MEMORY);

        if (TheCamera.GetScreenFadeStatus() == 0) {
            FrontEndMenuManager.MessageScreen("LOADCOL", false, false);
        }

        CTimer::Suspend();
        CStreaming::LoadAllRequestedModels(true);
        CTimer::Resume();

        def->m_bLoadRequest = false;
    }
}

/*!
 * @addr 0x404AC0
 * @returns -1 if slot not found
 */
int32 CIplStore::FindIplSlot(const char* name) {
    for (auto& def : ms_pPool->GetAllValid()) {
        if (!_stricmp(name, def.m_szName)) {
            return ms_pPool->GetIndex(&def);
        }
    }
    return -1;
}

/*!
 * @addr 0x404C70
 */
CRect* CIplStore::GetBoundingBox(int32 iplSlotIndex) { // No xrefs
    return &GetInSlot(iplSlotIndex)->m_boundBox;
}

/*!
 * @addr 0x4047B0
 */
CEntity** CIplStore::GetIplEntityIndexArray(int32 arrayIndex) {
    return IplEntityIndexArrays[arrayIndex];
}

/*!
 * @addr 0x404A60
 */
const char* CIplStore::GetIplName(int32 iplSlotIndex) { // No xrefs
    return GetInSlot(iplSlotIndex)->m_szName;
}

/*!
 * @addr 0x404780
 * @brief Make a new `CEntity*[entitiesCount]` array
 * @returns The index of the array in `IplEntityIndexArrays`
 * @param entitiesCount Size of `CEntity*` array
 */
int32 CIplStore::GetNewIplEntityIndexArray(int32 entitiesCount) {
    const auto idx = NumIplEntityIndexArrays++;
    IplEntityIndexArrays[idx] = new CEntity*[entitiesCount];
    return idx;
}

/*!
 * @addr 0x405600
 * @returns If all IPLs around `coords` in a 190 unit radius have loaded
 */
bool CIplStore::HaveIplsLoaded(const CVector& coords, int32 /*playerNumber*/) {
    // Can't use `ms_pPool->GetAllValid()` here, because we must ignore the first slot (whenever it's valid or not).
    bool ret = true;
    for (auto slot = 1; slot < TOTAL_IPL_MODEL_IDS; slot++) {
        auto def = ms_pPool->GetAt(slot);
        if (!def) {
            continue;
        }
        if (!def->m_bLoadRequest) {
            continue;
        }
        if (def->m_boundBox.IsPointInside(coords, notsa::IsFixBugs() ? 190.f : -190.f) && !def->m_IsLoaded && !def->m_bDisableDynamicStreaming) {
            ret = false;
        }
        def->m_bLoadRequest = false;
    }
    return ret;
}

/*!
 * @addr 0x404C90
 */
void CIplStore::IncludeEntity(int32 iplSlotIndex, CEntity* entity) {
    const auto ipldef = ms_pPool->GetAt(iplSlotIndex);

    switch (entity->GetType()) {
    case ENTITY_TYPE_BUILDING: {
        const auto buildingId = GetBuildingPool()->GetIndex(entity->AsBuilding());
        ipldef->m_nMinBuildingId = std::min(ipldef->m_nMinBuildingId, (int16)buildingId);
        ipldef->m_nMaxBuildingId = std::max(ipldef->m_nMinBuildingId, (int16)buildingId);
        break;
    }
    case ENTITY_TYPE_DUMMY: {
        const auto dummyId = GetDummyPool()->GetIndex(entity->AsDummy());
        ipldef->m_nMinDummyId = std::min(ipldef->m_nMinDummyId, (int16)dummyId);
        ipldef->m_nMaxDummyId = std::max(ipldef->m_nMaxDummyId, (int16)dummyId);
        break;
    }
    default: {
        NOTSA_UNREACHABLE("Incorrect entity type");
    }
    }
}

/*!
 * @addr 0x405780
 * @brief Load remaining IPL defs (using the streamer)
 */
void CIplStore::LoadAllRemainingIpls() {
    // Can't use `ms_pPool->GetAllValid()` here, because we must ignore the first slot (whenever it's valid or not).
    for (auto slot = 1 /*skip 1st*/; slot < TOTAL_IPL_MODEL_IDS; slot++) {
        auto def = ms_pPool->GetAt(slot);

        if (!def) {
            continue;
        }

        if (!def->m_boundBox.IsFlipped()) {
            continue;
        }

        if (CColAccel::isCacheLoading()) {
            *def = CColAccel::getIplDef(slot);
            def->m_IsLoaded = false;
            ms_pQuadTree->AddItem(&def, def->m_boundBox);
        } else {
            CStreaming::RequestModel(IPLToModelId(slot), STREAMING_PRIORITY_REQUEST | STREAMING_KEEP_IN_MEMORY);
            CStreaming::LoadAllRequestedModels(true);
            CStreaming::RemoveModel(IPLToModelId(slot));
        }
    }
}

/*!
 * @addr 0x406080
 * @NOTSA Originally took `uchar*`, but for simplicity's sake we're going to use `char*`. Makes no difference.
 */
bool CIplStore::LoadIpl(int32 iplSlotIndex, char* data, int32 dataSize) {
    auto& def = *GetInSlot(iplSlotIndex);
    def.m_IsLoaded = true; // We're setting this here, as it's set in all cases.

    // First of all, load bounding box (if not loaded already)
    if (def.m_boundBox.IsFlipped()) {
        // def.field_2D = true; // Moved to top

        if (!LoadIplBoundingBox(iplSlotIndex, data, dataSize)) {
            return false;
        }

        if (def.field_31) {
            def.m_boundBox.Resize(350.f, 350.f);
        } else {
            def.m_boundBox.Resize(200.f, 200.f);
        }

        CColAccel::setIplDef(iplSlotIndex, def);
        ms_pQuadTree->AddItem(&def, def.m_boundBox);

        return true;
    }

    // Load file.
    // It might be either in text or binary.
    // If in binary the data beings with `bnry`.

    const auto pIPLLODEntities = def.m_nRelatedIpl != -1 ? IplEntityIndexArrays[def.m_nRelatedIpl] : nullptr;

    // Anti copy-paste code helper.
    // Finish loading an ObjectInstance
    const auto FinishLoadObjInst = [&](CEntity* obj) {
        obj->m_nIplIndex = (uint8)iplSlotIndex;

        // Assign LOD to `obj` (if set)
        if (obj->m_nLodIndex == -1) {
            obj->m_pLod = nullptr;
        } else {
            assert(pIPLLODEntities);
            obj->m_pLod = pIPLLODEntities[obj->m_nLodIndex];
            obj->m_pLod->m_nNumLodChildren++;
        }

        obj->Add(); // Add it to the world

        IncludeEntity(iplSlotIndex, obj);
    };

    if (strncmp((char*)data, "bnry", 4u) != 0) { // IPL in text format
        bool inSection{};
        for (auto line = CFileLoader::LoadLine(data, dataSize); line; line = CFileLoader::LoadLine(data, dataSize)) {
            switch (line[0]) {
            case 0:   // Empty line
            case '#': // Comment
                continue;
            }

            const auto LineBeginsWith = [linesv = std::string_view{ line }](auto with) {
                return linesv.starts_with(with);
            };

            if (!inSection) {
                inSection = LineBeginsWith("inst");
                continue;
            }

            if (LineBeginsWith("end")) {
                inSection = false;
                continue;
            }

            FinishLoadObjInst(CFileLoader::LoadObjectInstance(line));
        }
    } else { // Binary IPL
        auto ipl = reinterpret_cast<tBinaryIplFile*>(data);

        for (auto& inst : ipl->GetObjInstances()) {
            FinishLoadObjInst(CFileLoader::LoadObjectInstance(&inst, nullptr));
        }

        for (auto& cargen : ipl->GetCarGens()) {
            CFileLoader::LoadCarGenerator(&cargen, iplSlotIndex);
        }
    }

    // def.field_2D = true; // Moved to top

    return true;
}

/*!
 * @addr 0x405C00
 * @brief Nearly 100% same as `LoadIpl`, but it modifies `ppCurrIplInstance`, and calculates bounding box of the IPL. Unsure honestly.
 * @returns Always true
 * @NOTSA Originally took `uchar*`, but for simplicity's sake we're going to use `char*`. Makes no difference.
 */
bool CIplStore::LoadIplBoundingBox(int32 iplSlotIndex, char* data, int32 dataSize) {
    auto& def = *GetInSlot(iplSlotIndex);

    const auto pIPLLODEntities = def.m_nRelatedIpl != -1 ? IplEntityIndexArrays[def.m_nRelatedIpl] : nullptr;

    // Anti copy-paste code helper.
    // Finish loading an ObjectInstance
    const auto FinishLoadObjInst = [&](CEntity* obj) {
        obj->m_nIplIndex = (uint8)iplSlotIndex;

        if (obj->m_nLodIndex == -1) {
            obj->m_pLod = nullptr;
        } else {
            assert(pIPLLODEntities);
            obj->m_pLod = pIPLLODEntities[obj->m_nLodIndex];
            obj->m_pLod->m_nNumLodChildren++;

            if (ppCurrIplInstance) {
                *ppCurrIplInstance = obj;
                ppCurrIplInstance++;
            }
        }

        if (obj->GetModelInfo()->m_fDrawDistance > 150.f) {
            def.field_31 = true;
        }

        obj->Add(); // Add it to the world

        IncludeEntity(iplSlotIndex, obj);

        CRect rect;
        obj->GetBoundRect(&rect);
        def.m_boundBox.Restrict(rect);
    };

    if (strncmp((char*)data, "bnry", 4u) != 0) { // IPL in text format
        bool inSection{};
        for (auto line = CFileLoader::LoadLine(data, dataSize); line; line = CFileLoader::LoadLine(data, dataSize)) {
            switch (line[0]) {
            case 0:   // Empty line
            case '#': // Comment
                continue;
            }

            const auto LineBeginsWith = [linesv = std::string_view{ line }](auto with) {
                return linesv.starts_with(with);
            };

            if (!inSection) {
                inSection = LineBeginsWith("inst");
                continue;
            }

            if (LineBeginsWith("end")) {
                inSection = false;
                continue;
            }

            FinishLoadObjInst(CFileLoader::LoadObjectInstance(line));
        }
    } else { // Binary IPL
        auto ipl = reinterpret_cast<tBinaryIplFile*>(data);
        for (auto& inst : ipl->GetObjInstances()) {
            FinishLoadObjInst(CFileLoader::LoadObjectInstance(&inst, nullptr));
        }
    }

    return true;
}

/*!
 * @addr 0x405170
 */
void CIplStore::LoadIpls(CVector posn, bool bAvoidLoadInPlayerVehicleMovingDirection) {
    return plugin::Call<0x405170, CVector, bool>(posn, bAvoidLoadInPlayerVehicleMovingDirection);

    if (CStreaming::ms_disableStreaming) {
        return;
    }

    if (FindPlayerPed() && !bAvoidLoadInPlayerVehicleMovingDirection) {
        if (const auto veh = FindPlayerVehicle()) {
            const auto& velocity = veh->m_vecMoveSpeed;
            posn.x += std::min(40.f, velocity.x * 80.f);
            posn.y += std::min(40.f, velocity.y * 80.f);
        }
    }

    SetIplsRequired(posn);
    if (gbIplsNeededAtPosn) {
        SetIplsRequired(&gvecIplsNeededAtPosn, CGame::currArea);
    }

    //
    // Above code should be okay, but code below is a mess.
    //
}

/*!
 * @addr 0x405720
 * @brief Unload all loaded IPL's using `CStreaming::RemoveModel`
 */
void CIplStore::RemoveAllIpls() {
    // Can't use `ms_pPool->GetAllValid()` here, because we must ignore the first slot (whenever it's valid or not).
    for (auto slot = 1 /*skip 1st*/; slot < TOTAL_IPL_MODEL_IDS; slot++) {
        auto def = ms_pPool->GetAt(slot);
        if (!def) {
            continue;
        }

        if (!CStreaming::GetInfo(IPLToModelId(slot)).IsMissionOrGameRequired()) {
            CStreaming::RemoveModel(IPLToModelId(slot));
        }
    }
}

/*!
 * @addr 0x404B20
 */
void CIplStore::RemoveIpl(int32 iplSlotIndex) {
    auto def = ms_pPool->GetAt(iplSlotIndex);
    def->m_IsLoaded = false;

    const auto ProcessPool = [iplSlotIndex]<typename PoolT>(PoolT& pool, int32 minId, int32 maxId) {
        for (auto i = minId; i < maxId; i++) {
            const auto entity = pool.GetAt(i);
            if (!entity)
                continue;

            if (entity->m_nIplIndex == iplSlotIndex) {
                if constexpr (std::is_same_v<PoolT, CObjectPool>) {
                    if (entity->m_pDummyObject) {
                        CWorld::Add(entity->m_pDummyObject);
                    }
                }

                CWorld::Remove(entity);
                delete entity;
            }
        }
    };

    // In same order as originally
    ProcessPool(*GetBuildingPool(), def->m_nMinBuildingId, def->m_nMaxBuildingId);
    ProcessPool(*GetObjectPool(),   0,                     GetObjectPool()->GetSize());
    ProcessPool(*GetDummyPool(),    def->m_nMinDummyId,    def->m_nMaxDummyId);

    CTheCarGenerators::RemoveCarGenerators((uint8)iplSlotIndex);
}

/*!
 * @addr 0x405890
 */
void CIplStore::RemoveIplAndIgnore(int32 iplSlotIndex) {
    auto& def = *ms_pPool->GetAt(iplSlotIndex);

    CStreaming::RemoveModel(IPLToModelId(iplSlotIndex));

    def.m_bDisableDynamicStreaming = true;
    def.field_30 = false;
}

/*!
 * @addr 0x405B60
 */
void CIplStore::RemoveIplSlot(int32 iplSlotIndex) {
    auto def = ms_pPool->GetAt(iplSlotIndex);
    if (def->m_IsLoaded) {
        RemoveIpl(iplSlotIndex);
    }
    ms_pQuadTree->DeleteItem(def);
    ms_pPool->Delete(def);
}

/*!
 * @addr 0x4058D0
 */
void CIplStore::RemoveIplWhenFarAway(int32 iplSlotIndex) {
    auto def = ms_pPool->GetAt(iplSlotIndex);
    def->m_bDisableDynamicStreaming = false;
    def->field_30 = true;
}

/*!
 * @addr 0x405110
 */
void CIplStore::RemoveRelatedIpls(int32 iplSlotIndex) {
    for (auto&& [idx, def] : ms_pPool->GetAllValidWithIndex()) {
        if (def.m_nRelatedIpl == iplSlotIndex) {
            CStreaming::RemoveModel(IPLToModelId(idx));
        }
    }
}

/*!
 * @addr 0x405850
 */
void CIplStore::RequestIplAndIgnore(int32 iplSlotIndex) {
    auto& def = *ms_pPool->GetAt(iplSlotIndex);
    CStreaming::RequestModel(IPLToModelId(iplSlotIndex), STREAMING_KEEP_IN_MEMORY);
    def.m_bDisableDynamicStreaming = true;
    def.field_30 = false;
}

/*!
 * @addr 0x405520
 */
void CIplStore::RequestIpls(const CVector& posn, int32 playerNumber) {
    for (auto slot = 1 /*skip first*/; slot < TOTAL_IPL_MODEL_IDS; slot++) {
        const auto def = GetInSlot(slot);
        if (!def) {
            continue;
        }

        if (def->m_bLoadRequest) {
            if (def->m_boundBox.IsPointInside(posn, -190.f)) {
                CStreaming::RequestModel(IPLToModelId(slot), STREAMING_PRIORITY_REQUEST | STREAMING_KEEP_IN_MEMORY);
            }
            def->m_bLoadRequest = false;
        }
    }
}

/*!
 * @addr 0x404700
 */
void CIplStore::SetIplsRequired(const CVector& posn, int32 gameArea) {
    ms_currentIPLAreaCode = ResolveAreaCode(gameArea);

    const auto GetCallback = [&] {
        if (ms_currentIPLAreaCode != AREA_CODE_NORMAL_WORLD && posn.z >= 900.f) {
            return SetIfIplIsRequired;
        } else if (ms_currentIPLAreaCode == CGame::currArea) {
            return SetIfInteriorIplIsRequired;
        } else {
            return SetIfIplIsRequiredReducedBB;
        }
    };
    ms_pQuadTree->ForAllMatching(posn, GetCallback());
}

/*!
 * @addr 0x404A90
 */
void CIplStore::SetIsInterior(int32 iplSlotIndex, bool isInterior) {
    GetInSlot(iplSlotIndex)->m_bInterior = isInterior;
}

/*!
 * @addr 0x404DE0
 */
int32 CIplStore::SetupRelatedIpls(const char* iplFilePath, int32 entityArraysIndex, CEntity** pIPLInsts) {
    char iplName[32]{};

    // Extract name of IPL from path
    if (const auto pathSep = strrchr(iplFilePath, '\\')) { // Find last path separator
        if (const auto dot = strchr(pathSep, '.')) {
            memcpy_s(iplName, sizeof(iplName), pathSep + 1, dot - (pathSep + 1)); // They used a manual loop, but this is better.
        } else {
            return 0;
        }
    } else {
        return 0;
    }

    const auto isIPLAnInterior = [&iplName] {
        if (!_stricmp(iplName, "gen_int1") ||
            !_stricmp(iplName, "gen_int2") ||
            !_stricmp(iplName, "gen_int3") ||
            !_stricmp(iplName, "gen_int4") ||
            !_stricmp(iplName, "gen_int5") ||
            !_stricmp(iplName, "gen_intb") ||
            !_stricmp(iplName, "savehous") ||
            !_stricmp(iplName, "stadint")  ||
            !_stricmp(iplName, "int_la")   ||
            !_stricmp(iplName, "int_sf")   ||
            !_stricmp(iplName, "int_veg")  ||
            !_stricmp(iplName, "int_cont") ||
            !_stricmp(iplName, "levelmap")
        ) {
            return true;
        }
        return false;
    }();

    strcat_s(iplName, "_stream");
    const auto iplNameLen = strlen(iplName);

    ppCurrIplInstance = pIPLInsts;

    if (CColAccel::isCacheLoading()) { // NOTSA: Inverted conditional
        for (auto&& [slot, def] : ms_pPool->GetAllValidWithIndex()) {
            if (!_strnicmp(iplName, def.m_szName, iplNameLen /*they used strlen(iplName), but we optimized it*/)) {
                def = CColAccel::getIplDef(slot);
                def.m_nRelatedIpl = entityArraysIndex;
                def.m_bInterior = isIPLAnInterior;
                def.m_IsLoaded = false;
                ms_pQuadTree->AddItem(&def, def.m_boundBox);
            }
        }
    } else {
        for (auto&& [slot, def] : ms_pPool->GetAllValidWithIndex()) {
            if (!_strnicmp(iplName, def.m_szName, iplNameLen /*they used strlen(iplName), but we optimized it*/)) {
                def.m_nRelatedIpl = entityArraysIndex;
                def.m_bInterior = isIPLAnInterior;
                def.m_bDisableDynamicStreaming = false; // NOTE: Inlined function was used to set this.
                CStreaming::RequestModel(IPLToModelId(slot), STREAMING_KEEP_IN_MEMORY);
            }
        }
        CStreaming::LoadAllRequestedModels(false);
    }

    const auto ret = ppCurrIplInstance - pIPLInsts; // NOTE: `ppCurrIplInstance` is set to `pIPLInsts` at the beginning.. And I doubt it's changed in-between. But who knows.
    ppCurrIplInstance = nullptr;
    return ret;
}

/*!
 * @addr 0x5D5420
 */
bool CIplStore::Save() {
    return plugin::CallAndReturn<bool, 0x5D5420>();
}

/*!
 * @addr 0x5D54A0
 */
bool CIplStore::Load() {
    return plugin::CallAndReturn<bool, 0x5D54A0>();
}

/*!
 * @addr 0x4045F0
 * @brief Callback used in `SetIplsRequired`
 */
void SetIfInteriorIplIsRequired(const CVector2D& posn, void* data) {
    auto& def = *static_cast<IplDef*>(data);

    if (def.m_bInterior) {
        if (!ms_currentIPLAreaCode) {
            return;
        }
        if (def.m_boundBox.IsPointInside(posn, -140.f)) {
            def.m_bLoadRequest = true;
        }
    } else {
        if (def.m_boundBox.IsPointInside(posn)) {
            def.m_bLoadRequest = true;
        }
    }
}

/*!
 * @addr 0x404660
 * @brief Callback used in `SetIplsRequired`
 */
void SetIfIplIsRequired(const CVector2D& posn, void* data) {
    auto& def = *static_cast<IplDef*>(data);

    if (def.m_bInterior && def.m_boundBox.IsPointInside(posn, -140.f)) {
        def.m_bLoadRequest = true;
    }
}

/*!
 * @addr 0x404690
 * @brief Callback used in `SetIplsRequired`
 */
void SetIfIplIsRequiredReducedBB(const CVector2D& posn, void* data) {
    auto& def = *static_cast<IplDef*>(data);

    if (def.m_boundBox.IsPointInside(posn, -160.f)) {
        if (ms_currentIPLAreaCode != AREA_CODE_NORMAL_WORLD) {
            if (!def.m_bInterior) {
                return;
            }
        } else if (def.m_bInterior) {
            return;
        }
        def.m_bLoadRequest = true;
    }
}
