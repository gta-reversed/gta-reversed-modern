/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

#include "PathFind.h"

CPathFind &ThePaths = *(CPathFind *)(0x96F050);
int32& CPathFind::InteriorIDBeingBuilt = *(int32*)0x96EF88;
bool& CPathFind::bInteriorBeingBuilt = *(bool*)0x96F031 ;
int32& CPathFind::NumNodesGiven = *(int32*)0x96EF80;
int32& CPathFind::NumLinksToExteriorNodes = *(int32*)0x96EAB8;
int32& CPathFind::NewInteriorSlot = *(int32*)0x96EF84;

void CPathFind::InjectHooks()
{
    RH_ScopedClass(CPathFind);
    RH_ScopedCategoryGlobal();
    RH_ScopedInstall(Init, 0x44D080);
    RH_ScopedInstall(ReInit, 0x44E4E0);
    RH_ScopedInstall(Shutdown, 0x450950);
    RH_ScopedInstall(TidyUpNodeSwitchesAfterMission, 0x44D3B0);
    RH_ScopedInstall(UnMarkAllRoadNodesAsDontWander, 0x44D400);
    RH_ScopedInstall(RemoveForbiddenForScriptedCars, 0x44DD00);
    RH_ScopedInstall(MarkRoadNodeAsDontWander, 0x450560);
    RH_ScopedInstall(ReturnInteriorNodeIndex, 0x451300);
    RH_ScopedInstall(StartNewInterior, 0x44DE80);
    RH_ScopedInstall(UnLoadPathFindData, 0x44D0F0);
}

void CPathNode::InjectHooks() {
    RH_ScopedClass(CPathNode);
    RH_ScopedCategoryGlobal();
    RH_ScopedInstall(GetNodeCoors, 0x420A10);
}

CVector CPathNode::GetNodeCoors()
{
    return UncompressLargeVector(m_posn);
}

// 0x44D080
void CPathFind::Init()
{
    static int32 NumTempExternalNodes = 0; //Unused
    m_dwNumForbiddenAreas = 0;
    m_bForbiddenForScriptedCarsEnabled = false;

    for (auto i = 0u; i < NUM_PATH_MAP_AREAS + NUM_PATH_INTERIOR_AREAS; ++i) {
        m_pPathNodes[i] = nullptr;
        m_pNaviNodes[i] = nullptr;
        m_pNodeLinks[i] = nullptr;
        m_pLinkLengths[i] = nullptr;
        m_pPathIntersections[i] = nullptr;
        m_pNaviLinks[i] = nullptr; // Out of array bounds write, same as in original code
        field_EA4[i] = nullptr; // Out of array bounds write, same as in original code
    }

    memset(m_aInteriorNodes, 0xFF, sizeof(m_aInteriorNodes));
}

// 0x44E4E0
void CPathFind::ReInit() {
    m_dwNumForbiddenAreas = 0;
    m_bForbiddenForScriptedCarsEnabled = false;
}

// 0x450950
void CPathFind::Shutdown() {
    for (auto i = 0u; i < 8; ++i) {
        for (auto k = 0u; k < 8; ++k) {
            auto modelIndex = RESOURCE_ID_DAT + i + (k * 8);
            if (m_pPathNodes[k * 8 + i])
                CStreaming::RemoveModel(modelIndex);
        }
    }
}

// 0x44D3B0
void CPathFind::TidyUpNodeSwitchesAfterMission() {
    m_dwNumForbiddenAreas = std::min(54u, m_dwNumForbiddenAreas);
}

// 0x44D400
void CPathFind::UnMarkAllRoadNodesAsDontWander() {
    for (auto i = 0u; i < NUM_PATH_MAP_AREAS; ++i) {
        if (!m_pPathNodes[i])
            continue;

        for (auto nodeInd = 0u; nodeInd < m_dwNumVehicleNodes[i]; ++nodeInd) {
            m_pPathNodes[i][nodeInd].m_bDontWander = false;
        }
    }
}

// 0x44DD00
void CPathFind::RemoveForbiddenForScriptedCars() {
    m_bForbiddenForScriptedCarsEnabled = false;
}

bool CPathFind::TestCrossesRoad(CNodeAddress startNodeAddress, CNodeAddress targetNodeAddress)
{
    return plugin::CallMethodAndReturn<bool, 0x44D790, CPathFind*, CNodeAddress, CNodeAddress>
        (this, startNodeAddress, targetNodeAddress);
}

bool CPathFind::TestForPedTrafficLight(CNodeAddress startNodeAddress, CNodeAddress targetNodeAddress)
{
    return plugin::CallMethodAndReturn<bool, 0x44D480, CPathFind*, CNodeAddress, CNodeAddress>
        (this, startNodeAddress, targetNodeAddress);
}

CVector* CPathFind::TakeWidthIntoAccountForWandering(CVector* outPosition, CNodeAddress nodeAddress, uint16 randomSeed)
{
    return plugin::CallMethodAndReturn<CVector*, 0x4509A0, CPathFind*, CVector*, CNodeAddress, uint16>
        (this, outPosition, nodeAddress, randomSeed);
}

void CPathFind::FindNextNodeWandering(int32 pathType, float x, float y, float z, CNodeAddress* startNodeAddress,
                                      CNodeAddress* targetNodeAddress, uint32 dir, int8* outDir)
{
    plugin::CallMethod <0x451B70, CPathFind*, int32, float, float, float, CNodeAddress*, CNodeAddress*, uint32, int8*>
        (this, pathType, x, y, z, startNodeAddress, targetNodeAddress, dir, outDir);
}

void CPathFind::DoPathSearch(uint8 pathType, CVector origin, CNodeAddress originAddr,
    CVector target, CNodeAddress *pResultNodes, int16 *pNodesCount, int32 maxNodesToFind, float *pDistance,
    float maxSearchDistance, CNodeAddress *targetAddr, float maxUnkLimit, bool oneSideOnly,
    CNodeAddress forbiddenNodeAddr, bool includeNodesWithoutLinks, bool waterPath)
{
    ((void(__thiscall *)(CPathFind *, uint8, CVector, CNodeAddress, CVector, CNodeAddress *,
        int16 *, int32, float *, float, CNodeAddress *, float, bool, CNodeAddress, bool, bool))0x4515D0)(
            this, pathType, origin, originAddr, target, pResultNodes, pNodesCount, maxNodesToFind, pDistance,
            maxSearchDistance, targetAddr, maxUnkLimit, oneSideOnly, forbiddenNodeAddr, includeNodesWithoutLinks,
            waterPath);
}

void CPathFind::SetLinksBridgeLights(float fXMin, float fXMax, float fYMin, float fYMax, bool bTrainCrossing)
{
    return plugin::CallMethod<0x44D960, CPathFind*, float, float, float, float, bool>(this, fXMin, fXMax, fYMin, fYMax, bTrainCrossing);
}

// 0x450560
void CPathFind::MarkRoadNodeAsDontWander(float x, float y, float z) {
    auto node = FindNodeClosestToCoors(x, y, z, 0, 999999.88f, 0, 0, 0, 0, 0);
    if (!node.IsValid())
        return;

    m_pPathNodes[node.m_wAreaId][node.m_wNodeId].m_bDontWander = true;
}

CPathNode *CPathFind::GetPathNode(CNodeAddress address)
{
    return ((CPathNode *(__thiscall *)(CPathFind *, CNodeAddress))0x420AC0)(this, address);
}

int32 CPathFind::LoadPathFindData(RwStream *stream, int32 index)
{
    return plugin::CallMethodAndReturn<int32, 0x4529F0, CPathFind*, RwStream *, int32>(this, stream, index);
}

void CPathFind::UnLoadPathFindData(int32 index)
{
    delete[] m_pPathNodes[index];
    delete[] m_pNaviNodes[index];
    delete[] m_pNodeLinks[index];
    delete[] m_pNaviLinks[index];
    delete[] m_pLinkLengths[index];
    delete[] m_pPathIntersections[index];

    m_pPathNodes[index] = nullptr;
    m_pNaviNodes[index] = nullptr;
    m_pNodeLinks[index] = nullptr;
    m_pNaviLinks[index] = nullptr;
    m_pLinkLengths[index] = nullptr;
    m_pPathIntersections[index] = nullptr;
}

int32 CPathFind::LoadSceneForPathNodes(CVector point)
{
    return plugin::CallMethodAndReturn<int32, 0x44DE00, CPathFind*, CVector>(this, point);
}

bool CPathFind::IsWaterNodeNearby(CVector position, float radius)
{
    return plugin::CallMethodAndReturn<bool, 0x450DE0, CPathFind*, CVector, float>(this, position, radius);
}

CNodeAddress CPathFind::FindNodeClosestToCoors(float X, float Y, float Z, int32 _nodeType, float maxDistance,
    uint16 unk2, int32 unk3, uint16 unk4, uint16 bBoatsOnly, int32 unk6)
{
    CNodeAddress tempAddress;
    plugin::CallMethodAndReturn<CNodeAddress*, 0x44F460, CPathFind*, CNodeAddress*, float, float, float, int32, float, uint16, int32, uint16, uint16, int32>(
        this, &tempAddress, X, Y, Z, _nodeType, maxDistance, unk2, unk3, unk4, bBoatsOnly, unk6);
    return tempAddress;
}

// 0x44D2B0
void CPathFind::AllocatePathFindInfoMem() {
    // NOP
}

// 0x44D0E0
void CPathFind::PreparePathData() {
    // NOP
}

// 0x5D3500
bool CPathFind::Load() {
    return plugin::CallMethodAndReturn<bool, 0x5D3500>(this);
}

// 0x5D1502
bool CPathFind::Save() {
    return plugin::CallMethodAndReturn<bool, 0x5D1502>(this);
}

// 0x450A60
void CPathFind::UpdateStreaming(bool a1) {
    return plugin::CallMethod<0x450A60, CPathFind*, bool>(this, a1);
}

// 0x44DE80
void CPathFind::StartNewInterior(int interiorNum) {
    InteriorIDBeingBuilt = interiorNum;
    bInteriorBeingBuilt = true;
    NumNodesGiven = 0;
    NumLinksToExteriorNodes = 0;

    // BUG: Possible endless loop if 8 interiors are loaded i think
    NewInteriorSlot = 0;
    while (m_aInteriorNodes[NewInteriorSlot].IsValid())
        NewInteriorSlot++;
}

// 0x451300 unused
CNodeAddress CPathFind::ReturnInteriorNodeIndex(int32 unkn, CNodeAddress addressToFind, int16 nodeId) {
    for (auto interiorInd = 0; interiorInd < NUM_PATH_INTERIOR_AREAS; ++interiorInd) {
        if (m_aInteriorNodes[interiorInd] == addressToFind)
            return CNodeAddress(NUM_PATH_MAP_AREAS + interiorInd, nodeId);
    }

    return CNodeAddress((uint16)-1, addressToFind.m_wNodeId);
}
