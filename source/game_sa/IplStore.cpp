/*
Plugin-SDK (Grand Theft Auto San Andreas) source file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

CQuadTreeNode *&CIplStore::ms_pQuadTree = *(CQuadTreeNode **)0x8E3FAC;
CPool<IplDef> *&CIplStore::ms_pPool = *(CPool<IplDef> **)0x8E3FB0;

uint32 MAX_IPL_ENTITY_INDEX_ARRAYS = 40;
uint32 MAX_IPL_INSTANCES = 1000;

CEntity** ppCurrIplInstance = (CEntity**)0x8E3EFC;
uint32& NumIplEntityIndexArrays = *(uint32*)0x8E3F00;
CEntity** (&IplEntityIndexArrays)[40] = *(CEntity**(*)[40])0x8E3F08;
bool& gbIplsNeededAtPosn = *(bool*)0x8E3FA8;
CVector& gvecIplsNeededAtPosn = *(CVector*)0x8E3FD0;
uint32& gCurrIplInstancesCount = *(uint32*)0xBCC0D8;
CEntity** gCurrIplInstances = (CEntity**)0xBCC0E0;

void CIplStore::InjectHooks() {
    ReversibleHooks::Install("CIplStore", "GetIplEntityIndexArray", 0x4047B0, &CIplStore::GetIplEntityIndexArray);
}

// 0x405EC0
void CIplStore::Initialise() {
    plugin::Call<0x405EC0>();
}

// 0x405FA0
void CIplStore::Shutdown() {
    plugin::Call<0x405FA0>();
}

// 0x405AC0
int32 CIplStore::AddIplSlot(char const* name) {
    return plugin::CallAndReturn<int32, 0x405AC0, char const*>(name);
}

// 0x4045B0
void CIplStore::AddIplsNeededAtPosn(CVector const& posn) {
    plugin::Call<0x4045B0, CVector const&>(posn);
}

// 0x4045E0
void CIplStore::ClearIplsNeededAtPosn() {
    plugin::Call<0x4045E0>();
}

// 0x404D30
void CIplStore::EnableDynamicStreaming(int32 iplSlotIndex, bool enable) {
    plugin::Call<0x404D30, int32, bool>(iplSlotIndex, enable);
}

// 0x4053F0
void CIplStore::EnsureIplsAreInMemory(CVector const& posn) {
    plugin::Call<0x4053F0, CVector const&>(posn);
}

// 0x404AC0
int32 CIplStore::FindIplSlot(char const* name) {
    return plugin::CallAndReturn<int32, 0x404AC0, char const*>(name);
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
bool CIplStore::HaveIplsLoaded(CVector const& coords, int32 playerNumber) {
    return plugin::CallAndReturn<bool, 0x405600, CVector const&, int32>(coords, playerNumber);
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
void CIplStore::RequestIpls(CVector const& posn, int32 playerNumber) {
    plugin::Call<0x405520, CVector const&, int32>(posn, playerNumber);
}

// 0x404700
void CIplStore::SetIplsRequired(CVector const& posn, int32 playerNumber) {
    plugin::Call<0x404700, CVector const&, int32>(posn, playerNumber);
}

// 0x404A90
void CIplStore::SetIsInterior(int32 iplSlotIndex, bool isInterior) {
    plugin::Call<0x404A90, int32, bool>(iplSlotIndex, isInterior);
}

// 0x404DE0
int32 CIplStore::SetupRelatedIpls(char const* iplName, int32 entityArraysIndex, CEntity** instances) {
    return plugin::CallAndReturn<int32, 0x404DE0, char const*, int32, CEntity**>(iplName, entityArraysIndex, instances);
}

// 0x4045F0
void SetIfInteriorIplIsRequired(CVector2D const& posn, void* data) {
    plugin::Call<0x4045F0, CVector2D const&, void*>(posn, data);
}

// 0x404660
void SetIfIplIsRequired(CVector2D const& posn, void* data) {
    plugin::Call<0x404660, CVector2D const&, void*>(posn, data);
}

// 0x404690
void SetIfIplIsRequiredReducedBB(CVector2D const& posn, void* data) {
    plugin::Call<0x404690, CVector2D const&, void*>(posn, data);
}
