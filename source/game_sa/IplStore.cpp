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

void CIplStore::InjectHooks() {
    RH_ScopedClass(CIplStore);
    RH_ScopedCategoryGlobal();

    RH_ScopedGlobalInstall(AddIplsNeededAtPosn, 0x4045B0);
    RH_ScopedGlobalInstall(LoadIpl, 0x406080);
    RH_ScopedGlobalInstall(Shutdown, 0x405FA0);
    RH_ScopedGlobalInstall(Initialise, 0x405EC0);
    RH_ScopedGlobalInstall(LoadIplBoundingBox, 0x405C00);
    //RH_ScopedGlobalInstall(RemoveIplSlot, 0x405B60);
    RH_ScopedGlobalInstall(AddIplSlot, 0x405AC0);
    //RH_ScopedGlobalInstall(RemoveIplWhenFarAway, 0x4058D0);
    //RH_ScopedGlobalInstall(RemoveIplAndIgnore, 0x405890);
    //RH_ScopedGlobalInstall(RequestIplAndIgnore, 0x405850);
    RH_ScopedGlobalInstall(LoadAllRemainingIpls, 0x405780);
    //RH_ScopedGlobalInstall(RemoveAllIpls, 0x405720);
    //RH_ScopedGlobalInstall(HaveIplsLoaded, 0x405600);
    //RH_ScopedGlobalInstall(RequestIpls, 0x405520);
    //RH_ScopedGlobalInstall(Save, 0x5D5420);
    RH_ScopedGlobalInstall(EnsureIplsAreInMemory, 0x4053F0);
    //RH_ScopedGlobalInstall(RemoveRelatedIpls, 0x405110);
    //RH_ScopedGlobalInstall(SetupRelatedIpls, 0x404DE0);
    RH_ScopedGlobalInstall(EnableDynamicStreaming, 0x404D30);
    RH_ScopedGlobalInstall(IncludeEntity, 0x404C90);
    RH_ScopedGlobalInstall(GetBoundingBox, 0x404C70);
    //RH_ScopedGlobalInstall(RemoveIpl, 0x404B20);
    RH_ScopedGlobalInstall(FindIplSlot, 0x404AC0);
    //RH_ScopedGlobalInstall(SetIsInterior, 0x404A90);
    RH_ScopedGlobalInstall(GetIplName, 0x404A60);
    RH_ScopedGlobalInstall(GetIplEntityIndexArray, 0x4047B0);
    RH_ScopedGlobalInstall(GetNewIplEntityIndexArray, 0x404780);
    //RH_ScopedGlobalInstall(SetIplsRequired, 0x404700);
    RH_ScopedGlobalInstall(ClearIplsNeededAtPosn, 0x4045E0);
    //RH_ScopedGlobalInstall(LoadIpls, 0x405170);
    //RH_ScopedGlobalInstall(Load, 0x5D54A0);

}

/*!
* @addr 0x405EC0
* @brief Allocate pool if it doesn't exist yet, allocate quad tree, etc..
*/
void CIplStore::Initialise() {
    gbIplsNeededAtPosn = 0;

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

    for (auto a : IplEntityIndexArrays | rng::views::take(NumIplEntityIndexArrays)) {
        delete a;
    }
    NumIplEntityIndexArrays = 0;

    delete ms_pQuadTree;
    ms_pQuadTree = nullptr;
}

/*!
* @addr 0x405AC0
*/
int32 CIplStore::AddIplSlot(const char* name) {
    const auto def = new(ms_pPool->New()) IplDef{name}; // MOTE: Seemingly they didn't overload `operator new` for it..
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

/*!
* @addr 0x4053F0
* @brief Make sure all IPls that requested around posn (in a 190 unit cirlce) are loaded.
*/
void CIplStore::EnsureIplsAreInMemory(const CVector& posn) {
    if (CStreaming::ms_disableStreaming) {
        return;
    }

    // Simplified this bit a little.. Originally it was something like.. ((FindPlayerPed() ? FindPlayerPed().m_nAreaCode : CGame::currArea) == CGame::currArea)
    // I suspect the function to get the area code was inlined..
    if (const auto pp = FindPlayerPed()) {
        if (pp->m_nAreaCode != CGame::currArea) {
            return;
        }
    }

    SetIplsRequired(posn);

    for (auto slot = 1/*notice*/; slot < TOTAL_IPL_MODEL_IDS; slot++) {
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
*/
bool CIplStore::HaveIplsLoaded(const CVector& coords, int32 playerNumber) {
    return plugin::CallAndReturn<bool, 0x405600, const CVector&, int32>(coords, playerNumber);
    /*
    // Can't use `ms_pPool->GetAllValid()` here, because we must ignore the first slot (whenever it's valid or not).
    for (auto slot = 1; slot < TOTAL_IPL_MODEL_IDS; slot++) {
       auto def = ms_pPool->GetAt(slot);
       if (!def) {
           continue;
       }

        if (!def.m_bLoadRequest) {
            continue;
        }

        if (def.m_boundBox.IsPointInside(coords, -190.f) && !def.field_2D && !def.m_bDisableDynamicStreaming) {
            // Stuff from 0x4056B9 should go here
            // Should probably use a lambad here
            // Also should figure out what field_2D is, otherwise this doesn't make a lot of sense.

            return false;
        } else {
            def.m_bLoadRequest = false;
        }
    }
    return true;
    */
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
        NOTSA_UNREACHABLE(); // Incorrect entity type
    }
    }
}

/*!
* @addr 0x5D5420
*/
void CIplStore::Save() {
    plugin::Call<0x5D5420>();
}

/*!
* @addr 0x5D54A0
*/
void CIplStore::Load() {
    plugin::Call<0x5D54A0>();
}

/*!
* @addr 0x405780
* @brief Load remaining IPL defs (using the streamer)
*/
void CIplStore::LoadAllRemainingIpls() {
    // Can't use `ms_pPool->GetAllValid()` here, because we must ignore the first slot (whenever it's valid or not).
    for (auto slot = 1/*skip 1st*/; slot < TOTAL_IPL_MODEL_IDS; slot++) {
        auto def = ms_pPool->GetAt(slot);

        if (!def) {
            continue;
        }

        if (!def->m_boundBox.IsFlipped()) {
            continue;
        }

        if (CColAccel::isCacheLoading()) {
            *def = CColAccel::getIplDef(slot);
            def->field_2D = false;
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
*/
bool CIplStore::LoadIpl(int32 iplSlotIndex, char* data, int32 dataSize) {
    auto& def = *GetInSlot(iplSlotIndex);
    def.field_2D = true; // We're setting this here, as it's set in all cases.

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

    if (strncmp((char*)data, "bnry", 4u)) { // IPL in text format
        bool inSection{};
        for (auto l = CFileLoader::LoadLine(data, dataSize); l; l = CFileLoader::LoadLine(data, dataSize)) {
            switch (l[0]) {
            case 0:   // Empty line
            case '#': // Comment
                continue;
            }

            const auto LineBeginsWith = [linesv = std::string_view{ l }](auto with) {
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

            FinishLoadObjInst(CFileLoader::LoadObjectInstance(l));
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

    if (strncmp((char*)data, "bnry", 4u)) { // IPL in text format
        bool inSection{};
        for (auto l = CFileLoader::LoadLine(data, dataSize); l; l = CFileLoader::LoadLine(data, dataSize)) {
            switch (l[0]) {
            case 0:   // Empty line
            case '#': // Comment
                continue;
            }

            const auto LineBeginsWith = [linesv = std::string_view{ l }](auto with) {
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

            FinishLoadObjInst(CFileLoader::LoadObjectInstance(l));     
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
    plugin::Call<0x405170, CVector, bool>(posn, bAvoidLoadInPlayerVehicleMovingDirection);
    
    /*if (CStreaming::ms_disableStreaming) {
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

    */
}

/*!
* @addr 0x405720
* @brief Unload all loaded IPL's using `CStreaming::RemoveModel`
*/
void CIplStore::RemoveAllIpls() {
    // Can't use `ms_pPool->GetAllValid()` here, because we must ignore the first slot (whenever it's valid or not).
    for (auto slot = 1/*skip 1st*/; slot < TOTAL_IPL_MODEL_IDS; slot++) {
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
    plugin::Call<0x404B20, int32>(iplSlotIndex);
}

/*!
* @addr 0x405890
*/
void CIplStore::RemoveIplAndIgnore(int32 iplSlotIndex) {
    plugin::Call<0x405890, int32>(iplSlotIndex);
}

/*!
* @addr 0x405B60
*/
void CIplStore::RemoveIplSlot(int32 iplSlotIndex) {
    plugin::Call<0x405B60, int32>(iplSlotIndex);
}

/*!
* @addr 0x4058D0
*/
void CIplStore::RemoveIplWhenFarAway(int32 iplSlotIndex) {
    plugin::Call<0x4058D0, int32>(iplSlotIndex);
}

/*!
* @addr 0x405110
*/
void CIplStore::RemoveRelatedIpls(int32 entityArraysIndex) {
    plugin::Call<0x405110, int32>(entityArraysIndex);
}

/*!
* @addr 0x405850
*/
void CIplStore::RequestIplAndIgnore(int32 iplSlotIndex) {
    plugin::Call<0x405850, int32>(iplSlotIndex);
}

/*!
* @addr 0x405520
*/
void CIplStore::RequestIpls(const CVector& posn, int32 playerNumber) {
    plugin::Call<0x405520, const CVector&, int32>(posn, playerNumber);
}

/*!
* @addr 0x404700
*/
void CIplStore::SetIplsRequired(const CVector& posn, int32 gameArea) {
    plugin::Call<0x404700, const CVector&, int32>(posn, gameArea);
}

/*!
* @addr 0x404A90
*/
void CIplStore::SetIsInterior(int32 iplSlotIndex, bool isInterior) {
    plugin::Call<0x404A90, int32, bool>(iplSlotIndex, isInterior);
}

/*!
* @addr 0x404DE0
*/
int32 CIplStore::SetupRelatedIpls(const char* iplName, int32 entityArraysIndex, CEntity** instances) {
    return plugin::CallAndReturn<int32, 0x404DE0, const char*, int32, CEntity**>(iplName, entityArraysIndex, instances);
}

/*!
* @addr 0x4045F0
*/
void SetIfInteriorIplIsRequired(const CVector2D& posn, void* data) {
    plugin::Call<0x4045F0, const CVector2D&, void*>(posn, data);
}

/*!
* @addr 0x404660
*/
void SetIfIplIsRequired(const CVector2D& posn, void* data) {
    plugin::Call<0x404660, const CVector2D&, void*>(posn, data);
}

/*!
* @addr 0x404690
*/
void SetIfIplIsRequiredReducedBB(const CVector2D& posn, void* data) {
    plugin::Call<0x404690, const CVector2D&, void*>(posn, data);
}
