/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"
#include "IplStore.h"
#include "extensions/enumerate.hpp"

uint32 MAX_IPL_ENTITY_INDEX_ARRAYS = 40;
uint32 MAX_IPL_INSTANCES = 1000;

CEntity** ppCurrIplInstance = (CEntity**)0x8E3EFC;
uint32& NumIplEntityIndexArrays = *(uint32*)0x8E3F00;
bool& gbIplsNeededAtPosn = *(bool*)0x8E3FA8;
CVector& gvecIplsNeededAtPosn = *(CVector*)0x8E3FD0;
uint32& gCurrIplInstancesCount = *(uint32*)0xBCC0D8;
CEntity** gCurrIplInstances = (CEntity**)0xBCC0E0;

void CIplStore::InjectHooks() {
    RH_ScopedClass(CIplStore);
    RH_ScopedCategoryGlobal();

    RH_ScopedGlobalInstall(AddIplsNeededAtPosn, 0x4045B0);
    //RH_ScopedGlobalInstall(LoadIpl, 0x406080);
    RH_ScopedGlobalInstall(Shutdown, 0x405FA0);
    RH_ScopedGlobalInstall(Initialise, 0x405EC0);
    //RH_ScopedGlobalInstall(LoadIplBoundingBox, 0x405C00);
    //RH_ScopedGlobalInstall(RemoveIplSlot, 0x405B60);
    RH_ScopedGlobalInstall(AddIplSlot, 0x405AC0);
    //RH_ScopedGlobalInstall(RemoveIplWhenFarAway, 0x4058D0);
    //RH_ScopedGlobalInstall(RemoveIplAndIgnore, 0x405890);
    //RH_ScopedGlobalInstall(RequestIplAndIgnore, 0x405850);
    //RH_ScopedGlobalInstall(LoadAllRemainingIpls, 0x405780);
    //RH_ScopedGlobalInstall(RemoveAllIpls, 0x405720);
    //RH_ScopedGlobalInstall(HaveIplsLoaded, 0x405600);
    //RH_ScopedGlobalInstall(RequestIpls, 0x405520);
    //RH_ScopedGlobalInstall(Save, 0x5D5420);
    //RH_ScopedGlobalInstall(EnsureIplsAreInMemory, 0x4053F0);
    //RH_ScopedGlobalInstall(RemoveRelatedIpls, 0x405110);
    //RH_ScopedGlobalInstall(SetupRelatedIpls, 0x404DE0);
    RH_ScopedGlobalInstall(EnableDynamicStreaming, 0x404D30);
    //RH_ScopedGlobalInstall(IncludeEntity, 0x404C90);
    //RH_ScopedGlobalInstall(GetBoundingBox, 0x404C70);
    //RH_ScopedGlobalInstall(RemoveIpl, 0x404B20);
    //RH_ScopedGlobalInstall(FindIplSlot, 0x404AC0);
    //RH_ScopedGlobalInstall(SetIsInterior, 0x404A90);
    //RH_ScopedGlobalInstall(GetIplName, 0x404A60);
    RH_ScopedGlobalInstall(GetIplEntityIndexArray, 0x4047B0);
    //RH_ScopedGlobalInstall(GetNewIplEntityIndexArray, 0x404780);
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

    for (auto a : std::span{ IplEntityIndexArrays, (size_t)NumIplEntityIndexArrays }) {
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

// 0x404D30
void CIplStore::EnableDynamicStreaming(int32 iplSlotIndex, bool enable) {
    GetInSlot(iplSlotIndex)->m_bDisableDynamicStreaming = !enable;
}

// 0x4053F0
void CIplStore::EnsureIplsAreInMemory(const CVector& posn) {
    plugin::Call<0x4053F0, const CVector&>(posn);
}

// 0x404AC0
int32 CIplStore::FindIplSlot(const char* name) {
    return plugin::CallAndReturn<int32, 0x404AC0, const char*>(name);
}

// 0x404C70
CRect* CIplStore::GetBoundingBox(int32 iplSlotIndex) {
    return plugin::CallAndReturn<CRect*, 0x404C70, int32>(iplSlotIndex);
}

// 0x4047B0
CEntity** CIplStore::GetIplEntityIndexArray(int32 arrayIndex) {
    return IplEntityIndexArrays[arrayIndex];
}

// 0x404A60
char* CIplStore::GetIplName(int32 iplSlotIndex) {
    return plugin::CallAndReturn<char*, 0x404A60, int32>(iplSlotIndex);
}

// 0x404780
int32 CIplStore::GetNewIplEntityIndexArray(int32 entitiesCount) {
    return plugin::CallAndReturn<int32, 0x404780, int32>(entitiesCount);
}

// 0x405600
bool CIplStore::HaveIplsLoaded(const CVector& coords, int32 playerNumber) {
    return plugin::CallAndReturn<bool, 0x405600, const CVector&, int32>(coords, playerNumber);
}

// 0x404C90
void CIplStore::IncludeEntity(int32 iplSlotIndex, CEntity* entity) {
    plugin::Call<0x404C90, int32, CEntity*>(iplSlotIndex, entity);
}

// 0x5D5420
void CIplStore::Save() {
    plugin::Call<0x5D5420>();
}

// 0x5D54A0
void CIplStore::Load() {
    plugin::Call<0x5D54A0>();
}

// 0x405780
void CIplStore::LoadAllRemainingIpls() {
    plugin::Call<0x405780>();
}

// 0x406080
bool CIplStore::LoadIpl(int32 iplSlotIndex, uint8* data, int32 dataSize) {
    return plugin::CallAndReturn<bool, 0x406080, int32, uint8*, int32>(iplSlotIndex, data, dataSize);
}

// 0x405C00
bool CIplStore::LoadIplBoundingBox(int32 iplSlotIndex, uint8* data, int32 dataSize) {
    return plugin::CallAndReturn<bool, 0x405C00, int32, uint8*, int32>(iplSlotIndex, data, dataSize);
}

// 0x405170
void CIplStore::LoadIpls(CVector posn, bool bAvoidLoadInPlayerVehicleMovingDirection) {
    plugin::Call<0x405170, CVector, bool>(posn, bAvoidLoadInPlayerVehicleMovingDirection);
}

// 0x405720
void CIplStore::RemoveAllIpls() {
    plugin::Call<0x405720>();
}

// 0x404B20
void CIplStore::RemoveIpl(int32 iplSlotIndex) {
    plugin::Call<0x404B20, int32>(iplSlotIndex);
}

// 0x405890
void CIplStore::RemoveIplAndIgnore(int32 iplSlotIndex) {
    plugin::Call<0x405890, int32>(iplSlotIndex);
}

// 0x405B60
void CIplStore::RemoveIplSlot(int32 iplSlotIndex) {
    plugin::Call<0x405B60, int32>(iplSlotIndex);
}

// 0x4058D0
void CIplStore::RemoveIplWhenFarAway(int32 iplSlotIndex) {
    plugin::Call<0x4058D0, int32>(iplSlotIndex);
}

// 0x405110
void CIplStore::RemoveRelatedIpls(int32 entityArraysIndex) {
    plugin::Call<0x405110, int32>(entityArraysIndex);
}

// 0x405850
void CIplStore::RequestIplAndIgnore(int32 iplSlotIndex) {
    plugin::Call<0x405850, int32>(iplSlotIndex);
}

// 0x405520
void CIplStore::RequestIpls(const CVector& posn, int32 playerNumber) {
    plugin::Call<0x405520, const CVector&, int32>(posn, playerNumber);
}

// 0x404700
void CIplStore::SetIplsRequired(const CVector& posn, int32 playerNumber) {
    plugin::Call<0x404700, const CVector&, int32>(posn, playerNumber);
}

// 0x404A90
void CIplStore::SetIsInterior(int32 iplSlotIndex, bool isInterior) {
    plugin::Call<0x404A90, int32, bool>(iplSlotIndex, isInterior);
}

// 0x404DE0
int32 CIplStore::SetupRelatedIpls(const char* iplName, int32 entityArraysIndex, CEntity** instances) {
    return plugin::CallAndReturn<int32, 0x404DE0, const char*, int32, CEntity**>(iplName, entityArraysIndex, instances);
}

// 0x4045F0
void SetIfInteriorIplIsRequired(const CVector2D& posn, void* data) {
    plugin::Call<0x4045F0, const CVector2D&, void*>(posn, data);
}

// 0x404660
void SetIfIplIsRequired(const CVector2D& posn, void* data) {
    plugin::Call<0x404660, const CVector2D&, void*>(posn, data);
}

// 0x404690
void SetIfIplIsRequiredReducedBB(const CVector2D& posn, void* data) {
    plugin::Call<0x404690, const CVector2D&, void*>(posn, data);
}
