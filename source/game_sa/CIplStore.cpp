/*
Plugin-SDK (Grand Theft Auto San Andreas) source file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

CQuadTreeNode *&CIplStore::ms_pQuadTree = *(CQuadTreeNode **)0x8E3FAC;
CPool<IplDef> *&CIplStore::ms_pPool = *(CPool<IplDef> **)0x8E3FB0;

unsigned int MAX_IPL_ENTITY_INDEX_ARRAYS = 40;
unsigned int MAX_IPL_INSTANCES = 1000;

CEntity** ppCurrIplInstance = (CEntity**)0x8E3EFC;
unsigned int& NumIplEntityIndexArrays = *(unsigned int*)0x8E3F00;
int** IplEntityIndexArrays = (int**)0x8E3F08;
bool& gbIplsNeededAtPosn = *(bool*)0x8E3FA8;
CVector& gvecIplsNeededAtPosn = *(CVector*)0x8E3FD0;
unsigned int& gCurrIplInstancesCount = *(unsigned int*)0xBCC0D8;
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

// Converted from cdecl int CIplStore::AddIplSlot(char const*name) 0x405AC0
int CIplStore::AddIplSlot(char const* name) {
    return plugin::CallAndReturn<int, 0x405AC0, char const*>(name);
}

// Converted from cdecl void CIplStore::AddIplsNeededAtPosn(CVector const&posn) 0x4045B0
void CIplStore::AddIplsNeededAtPosn(CVector const& posn) {
    plugin::Call<0x4045B0, CVector const&>(posn);
}

// Converted from cdecl void CIplStore::ClearIplsNeededAtPosn(void) 0x4045E0
void CIplStore::ClearIplsNeededAtPosn() {
    plugin::Call<0x4045E0>();
}

// Converted from cdecl void CIplStore::EnableDynamicStreaming(int iplSlotIndex, bool enable) 0x404D30
void CIplStore::EnableDynamicStreaming(int iplSlotIndex, bool enable) {
    plugin::Call<0x404D30, int, bool>(iplSlotIndex, enable);
}

// Converted from cdecl void CIplStore::EnsureIplsAreInMemory(CVector const&posn) 0x4053F0
void CIplStore::EnsureIplsAreInMemory(CVector const& posn) {
    plugin::Call<0x4053F0, CVector const&>(posn);
}

// Converted from cdecl int CIplStore::FindIplSlot(char const*name) 0x404AC0
int CIplStore::FindIplSlot(char const* name) {
    return plugin::CallAndReturn<int, 0x404AC0, char const*>(name);
}

// Converted from cdecl CRect* CIplStore::GetBoundingBox(int iplSlotIndex) 0x404C70
CRect* CIplStore::GetBoundingBox(int iplSlotIndex) {
    return plugin::CallAndReturn<CRect*, 0x404C70, int>(iplSlotIndex);
}

// 0x4047B0
int* CIplStore::GetIplEntityIndexArray(int arrayIndex) {
    return IplEntityIndexArrays[arrayIndex];
}

// Converted from cdecl char* CIplStore::GetIplName(int iplSlotIndex) 0x404A60
char* CIplStore::GetIplName(int iplSlotIndex) {
    return plugin::CallAndReturn<char*, 0x404A60, int>(iplSlotIndex);
}

// Converted from cdecl int CIplStore::GetNewIplEntityIndexArray(int entitiesCount) 0x404780
int CIplStore::GetNewIplEntityIndexArray(int entitiesCount) {
    return plugin::CallAndReturn<int, 0x404780, int>(entitiesCount);
}

// Converted from cdecl bool CIplStore::HaveIplsLoaded(CVector const&coords, int playerNumber) 0x405600
bool CIplStore::HaveIplsLoaded(CVector const& coords, int playerNumber) {
    return plugin::CallAndReturn<bool, 0x405600, CVector const&, int>(coords, playerNumber);
}

// Converted from cdecl void CIplStore::IncludeEntity(int iplSlotIndex, CEntity *entity) 0x404C90
void CIplStore::IncludeEntity(int iplSlotIndex, CEntity* entity) {
    plugin::Call<0x404C90, int, CEntity*>(iplSlotIndex, entity);
}

// 0x5D5420
void CIplStore::Save() {
    plugin::Call<0x5D5420>();
}

// 0x5D54A0
void CIplStore::Load() {
    plugin::Call<0x5D54A0>();
}

// Converted from cdecl void CIplStore::LoadAllRemainingIpls(void) 0x405780
void CIplStore::LoadAllRemainingIpls() {
    plugin::Call<0x405780>();
}

// Converted from cdecl bool CIplStore::LoadIpl(int iplSlotIndex, uchar *data, int dataSize) 0x406080
bool CIplStore::LoadIpl(int iplSlotIndex, unsigned char* data, int dataSize) {
    return plugin::CallAndReturn<bool, 0x406080, int, unsigned char*, int>(iplSlotIndex, data, dataSize);
}

// Converted from cdecl bool CIplStore::LoadIplBoundingBox(int iplSlotIndex,uchar *data,int dataSize) 0x405C00
bool CIplStore::LoadIplBoundingBox(int iplSlotIndex, unsigned char* data, int dataSize) {
    return plugin::CallAndReturn<bool, 0x405C00, int, unsigned char*, int>(iplSlotIndex, data, dataSize);
}

// Converted from cdecl void CIplStore::LoadIpls(CVector posn,bool) 0x405170
void CIplStore::LoadIpls(CVector posn, bool bAvoidLoadInPlayerVehicleMovingDirection) {
    plugin::Call<0x405170, CVector, bool>(posn, bAvoidLoadInPlayerVehicleMovingDirection);
}

// Converted from cdecl void CIplStore::RemoveAllIpls(void) 0x405720
void CIplStore::RemoveAllIpls() {
    plugin::Call<0x405720>();
}

// Converted from cdecl void CIplStore::RemoveIpl(int iplSlotIndex) 0x404B20
void CIplStore::RemoveIpl(int iplSlotIndex) {
    plugin::Call<0x404B20, int>(iplSlotIndex);
}

// Converted from cdecl void CIplStore::RemoveIplAndIgnore(int iplSlotIndex) 0x405890
void CIplStore::RemoveIplAndIgnore(int iplSlotIndex) {
    plugin::Call<0x405890, int>(iplSlotIndex);
}

// Converted from cdecl void CIplStore::RemoveIplSlot(int iplSlotIndex) 0x405B60
void CIplStore::RemoveIplSlot(int iplSlotIndex) {
    plugin::Call<0x405B60, int>(iplSlotIndex);
}

// Converted from cdecl void CIplStore::RemoveIplWhenFarAway(int iplSlotIndex) 0x4058D0
void CIplStore::RemoveIplWhenFarAway(int iplSlotIndex) {
    plugin::Call<0x4058D0, int>(iplSlotIndex);
}

// Converted from cdecl void CIplStore::RemoveRelatedIpls(int entityArraysIndex) 0x405110
void CIplStore::RemoveRelatedIpls(int entityArraysIndex) {
    plugin::Call<0x405110, int>(entityArraysIndex);
}

// Converted from cdecl void CIplStore::RequestIplAndIgnore(int iplSlotIndex) 0x405850
void CIplStore::RequestIplAndIgnore(int iplSlotIndex) {
    plugin::Call<0x405850, int>(iplSlotIndex);
}

// Converted from cdecl void CIplStore::RequestIpls(CVector const&posn,int playerNumber) 0x405520
void CIplStore::RequestIpls(CVector const& posn, int playerNumber) {
    plugin::Call<0x405520, CVector const&, int>(posn, playerNumber);
}

// Converted from cdecl void CIplStore::SetIplsRequired(CVector const&posn,int playerNumber) 0x404700
void CIplStore::SetIplsRequired(CVector const& posn, int playerNumber) {
    plugin::Call<0x404700, CVector const&, int>(posn, playerNumber);
}

// Converted from cdecl void CIplStore::SetIsInterior(int iplSlotIndex,bool isInterior) 0x404A90
void CIplStore::SetIsInterior(int iplSlotIndex, bool isInterior) {
    plugin::Call<0x404A90, int, bool>(iplSlotIndex, isInterior);
}

// 0x404DE0
int CIplStore::SetupRelatedIpls(char const* iplName, int entityArraysIndex, CEntity** instances) {
    return plugin::CallAndReturn<int, 0x404DE0, char const*, int, CEntity**>(iplName, entityArraysIndex, instances);
}

// Converted from cdecl void SetIfInteriorIplIsRequired(CVector2D const&posn,void *data) 0x4045F0
void SetIfInteriorIplIsRequired(CVector2D const& posn, void* data) {
    plugin::Call<0x4045F0, CVector2D const&, void*>(posn, data);
}

// Converted from cdecl void SetIfIplIsRequired(CVector2D const&posn,void *data) 0x404660
void SetIfIplIsRequired(CVector2D const& posn, void* data) {
    plugin::Call<0x404660, CVector2D const&, void*>(posn, data);
}

// Converted from cdecl void SetIfIplIsRequiredReducedBB(CVector2D const&posn,void *data) 0x404690
void SetIfIplIsRequiredReducedBB(CVector2D const& posn, void* data) {
    plugin::Call<0x404690, CVector2D const&, void*>(posn, data);
}
