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
    RH_ScopedInstall(ReleaseRequestedNodes, 0x44DD00);
    RH_ScopedInstall(MarkRoadNodeAsDontWander, 0x450560);
    RH_ScopedInstall(ReturnInteriorNodeIndex, 0x451300);
    RH_ScopedInstall(StartNewInterior, 0x44DE80);
    RH_ScopedOverloadedInstall(LoadPathFindData, "void", 0x452F40, void (CPathFind::*)(int));
    RH_ScopedOverloadedInstall(LoadPathFindData, "stream", 0x4529F0, void (CPathFind::*)(RwStream*, int));    
    RH_ScopedInstall(UnLoadPathFindData, 0x44D0F0);
    RH_ScopedInstall(GetPathNode, 0x420AC0);
    RH_ScopedInstall(AddDynamicLinkBetween2Nodes_For1Node, 0x44E000);
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
    m_bNodesLoadingRequested = false;

    for (auto i = 0u; i < NUM_PATH_MAP_AREAS + NUM_PATH_INTERIOR_AREAS; ++i) {
        m_pPathNodes[i] = nullptr;
        m_pNaviNodes[i] = nullptr;
        m_pNodeLinks[i] = nullptr;
        m_pLinkLengths[i] = nullptr;
        m_pPathIntersections[i] = nullptr;
        m_pNaviLinks[i] = nullptr; //BUG: Out of array bounds write, same as in original code
        m_aUnused[i] = nullptr; // BUG: Out of array bounds write, same as in original code
    }

    memset(m_aInteriorNodes, 0xFF, sizeof(m_aInteriorNodes));
}

// 0x44E4E0
void CPathFind::ReInit() {
    m_dwNumForbiddenAreas = 0;
    m_bNodesLoadingRequested = false;
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
void CPathFind::ReleaseRequestedNodes() {
    m_bNodesLoadingRequested = false;
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

CVector CPathFind::TakeWidthIntoAccountForWandering(CNodeAddress nodeAddress, uint16 randomSeed)
{
    CVector vecOut;
    plugin::CallMethod<0x4509A0, CPathFind*, CVector*, CNodeAddress, uint16>(this, &vecOut, nodeAddress, randomSeed);
    return vecOut;
}

//  0x44F8C0
CNodeAddress CPathFind::FindNthNodeClosestToCoors(CVector pos, uint8 nodeType, float maxDistance, bool bLowTraffic, bool bUnkn, int nthNode, bool bBoatsOnly, bool bIgnoreInterior,
                                                  CNodeAddress* outNode) {
    CNodeAddress outAddress;
    plugin::CallMethod<0x44F8C0, CPathFind*, CNodeAddress*, CVector, unsigned char, float, bool, bool, int, bool, bool, CNodeAddress*>(
        this, &outAddress, pos, nodeType, maxDistance, bLowTraffic, bUnkn, nthNode, bBoatsOnly, bIgnoreInterior, outNode);
    return outAddress;
}

// 0x451B70
void CPathFind::FindNextNodeWandering(uint8 nodeType, CVector vecPos, CNodeAddress* originAddress, CNodeAddress* targetAddress, uint8 dir, uint8* outDir) {
    plugin::CallMethod<0x451B70, CPathFind*, uint8, CVector, CNodeAddress*, CNodeAddress*, uint8, uint8*>(this, nodeType, vecPos, originAddress, targetAddress, dir, outDir);
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

// 0x4505E0
CVector CPathFind::FindNodeCoorsForScript(CNodeAddress address, bool* bFound) {
    CVector vecOut;
    plugin::CallMethod<0x4505E0, CPathFind*, CVector*, CNodeAddress, bool*>(this, &vecOut, address, bFound);
    return vecOut;
}

// 0x450780
CVector CPathFind::FindNodeCoorsForScript(CNodeAddress address1, CNodeAddress address2, float* fOutDir, bool* bFound) {
    CVector vecOut;
    plugin::CallMethod<0x450780, CPathFind*, CVector*, CNodeAddress, CNodeAddress, float*, bool*>(this, &vecOut, address1, address2, fOutDir, bFound);
    return vecOut;
}

// 0x450560
void CPathFind::MarkRoadNodeAsDontWander(float x, float y, float z) {
    CVector pos = {x, y, z};
    auto node = FindNodeClosestToCoors(pos, 0, 999999.88f, 0, 0, 0, 0, 0);
    if (!node.IsValid())
        return;

    m_pPathNodes[node.m_wAreaId][node.m_wNodeId].m_bDontWander = true;
}

void CPathFind::SwitchRoadsOffInAreaForOneRegion(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax, bool bLowTraffic, uint8 nodeType, int areaId,
                                                 uint8 bUnused) {
    return plugin::CallMethod<0x452820, CPathFind*, float, float, float, float, float, float, bool, char, int, bool>(this, xMin, xMax, yMin, yMax, zMin, zMax, bLowTraffic,
                                                                                                                     nodeType, areaId, bUnused);
}

CPathNode *CPathFind::GetPathNode(CNodeAddress address)
{
    assert(address.IsValid());
    return &m_pPathNodes[address.m_wAreaId][address.m_wNodeId];
}

void CPathFind::LoadPathFindData(int32 areaId) {
    CTimer::Suspend();
    sprintf(gString, "data\\paths\\nodes%d.dat", areaId);
    auto* stream = RwStreamOpen(RwStreamType::rwSTREAMFILENAME, RwStreamAccessType::rwSTREAMREAD, gString);
    LoadPathFindData(stream, areaId);
    CTimer::Resume();
}

void CPathFind::LoadPathFindData(RwStream *stream, int32 areaId)
{
    RwStreamRead(stream, &m_dwNumNodes[areaId], sizeof(uint32));
    RwStreamRead(stream, &m_dwNumVehicleNodes[areaId], sizeof(uint32));
    RwStreamRead(stream, &m_dwNumPedNodes[areaId], sizeof(uint32));
    RwStreamRead(stream, &m_dwNumCarPathLinks[areaId], sizeof(uint32));
    RwStreamRead(stream, &m_dwNumAddresses[areaId], sizeof(uint32));

    auto numNodes = m_dwNumNodes[areaId];
    if (numNodes) {
        m_pPathNodes[areaId] = new CPathNode[numNodes];
        RwStreamRead(stream, m_pPathNodes[areaId], sizeof(CPathNode) * numNodes);
    } else {
        m_pPathNodes[areaId] = new CPathNode[1];
    }

    auto numCarPathLinks = m_dwNumCarPathLinks[areaId];
    if (numCarPathLinks) {
        m_pNaviNodes[areaId] = new CCarPathLink[numCarPathLinks];
        RwStreamRead(stream, m_pNaviNodes[areaId], sizeof(CCarPathLink) * numCarPathLinks);
    } else {
        m_pNaviNodes[areaId] = nullptr;
    }

    auto numAddresses = m_dwNumAddresses[areaId];
    if (numAddresses) {
        auto numToAdd = numAddresses + NUM_DYNAMIC_LINKS_PER_AREA * 12;
        m_pNodeLinks[areaId] = new CNodeAddress[numToAdd];
        m_pNaviLinks[areaId] = new CCarPathLinkAddress[numAddresses];
        m_pLinkLengths[areaId] = new uint8[numToAdd];
        m_pPathIntersections[areaId] = new CPathIntersectionInfo[numToAdd];
        RwStreamRead(stream, m_pNodeLinks[areaId], sizeof(CNodeAddress) * numToAdd);
        RwStreamRead(stream, m_pNaviLinks[areaId], sizeof(CCarPathLinkAddress) * numAddresses);
        RwStreamRead(stream, m_pLinkLengths[areaId], sizeof(uint8) * numToAdd);
        RwStreamRead(stream, m_pPathIntersections[areaId], sizeof(CPathIntersectionInfo) * numToAdd);
    } else {
        m_pNodeLinks[areaId] = nullptr;
        m_pNaviLinks[areaId] = nullptr;
        m_pLinkLengths[areaId] = nullptr;
        m_pPathIntersections[areaId] = nullptr;
    }

    for (auto i = 0u; i < numNodes; ++i) {
        auto& node = m_pPathNodes[areaId][i];
        node.m_bEmergencyVehiclesOnly = node.IsLowTrafficLevel();
    }

    for (auto i = 0u; i < m_dwNumForbiddenAreas; ++i) {
        auto& area = m_aForbiddenAreas[i];
        SwitchRoadsOffInAreaForOneRegion(area.m_fxMin, area.m_fXMax, area.m_fYMin, area.m_fYMax, area.m_fZMin, area.m_fZMax, area.m_bEnable, area.type, areaId, false);
    }

    for (auto i = 0u; i < NUM_DYNAMIC_LINKS_PER_AREA; ++i) {
        m_aDynamicLinksBaseIds[areaId].m_aLinks[i].value = (uint32)-1;
        m_aDynamicLinksIds[areaId].m_aLinks[i].value = (uint32)-1;
    }
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

void CPathFind::LoadSceneForPathNodes(CVector point)
{
    plugin::CallMethod<0x44DE00, CPathFind*, CVector>(this, point);
}

bool CPathFind::IsWaterNodeNearby(CVector position, float radius)
{
    return plugin::CallMethodAndReturn<bool, 0x450DE0, CPathFind*, CVector, float>(this, position, radius);
}

CNodeAddress CPathFind::FindNodeClosestToCoors(CVector pos, int32 nodeType, float maxDistance,
    uint16 unk2, int32 unk3, uint16 unk4, uint16 bBoatsOnly, int32 unk6)
{
    CNodeAddress tempAddress;
    plugin::CallMethodAndReturn<CNodeAddress*, 0x44F460, CPathFind*, CNodeAddress*, CVector, int32, float, uint16, int32, uint16, uint16, int32>(
        this, &tempAddress, pos, nodeType, maxDistance, unk2, unk3, unk4, bBoatsOnly, unk6);
    return tempAddress;
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
void CPathFind::UpdateStreaming(bool bForceStreaming) {
    return plugin::CallMethod<0x450A60, CPathFind*, bool>(this, bForceStreaming);
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

// 0x450E90
CNodeAddress CPathFind::AddNodeToNewInterior(float x, float y, float z, bool bDontWander, int8 con0, int8 con1, int8 con2, int8 con3, int8 con4, int8 con5) {
    CNodeAddress outAddress;
    plugin::CallMethod<0x450E90, CPathFind*, CNodeAddress*, float, float, float, bool, signed char, signed char, signed char, signed char, signed char, signed char>(
        this, &outAddress, x, y, z, bDontWander, con0, con1, con2, con3, con4, con5);
    return outAddress;
}

// 0x451300 unused
CNodeAddress CPathFind::ReturnInteriorNodeIndex(int32 unkn, CNodeAddress addressToFind, int16 nodeId) {
    for (auto interiorInd = 0; interiorInd < NUM_PATH_INTERIOR_AREAS; ++interiorInd) {
        if (m_aInteriorNodes[interiorInd] == addressToFind)
            return CNodeAddress(NUM_PATH_MAP_AREAS + interiorInd, nodeId);
    }

    return CNodeAddress((uint16)-1, addressToFind.m_wNodeId);
}

// 0x451350
CNodeAddress CPathFind::FindLinkBetweenNodes(CNodeAddress node1, CNodeAddress node2) {
    CNodeAddress outAddress;
    plugin::CallMethod<0x451350, CPathFind*, CNodeAddress*, CNodeAddress, CNodeAddress>(this, &outAddress, node1, node2);
    return outAddress;
}

// 0x4513F0
CVector CPathFind::FindParkingNodeInArea(float minX, float maxX, float minY, float maxY, float minZ, float maxZ) {
    CVector vecOut;
    plugin::CallMethod<0x4513F0, CPathFind*, CVector*, float, float, float, float, float, float>(this, &vecOut, minX, maxX, minY, maxY, minZ, maxZ);
    return vecOut;
}

// 0x450F30
CNodeAddress CPathFind::FindNearestExteriorNodeToInteriorNode(int interiorId) {
    CNodeAddress outAddress;
    plugin::CallMethod<0x450F30, CPathFind*, CNodeAddress*, int>(this, &outAddress, interiorId);
    return outAddress;
}

// 0x44E000
void CPathFind::AddDynamicLinkBetween2Nodes_For1Node(CNodeAddress first, CNodeAddress second) {
    auto& firstPathInfo = m_pPathNodes[first.m_wAreaId][first.m_wNodeId];
    auto numAddresses = m_dwNumAddresses[first.m_wAreaId];

    uint32_t firstLinkId;
    if (firstPathInfo.m_wBaseLinkId >= numAddresses)
        firstLinkId = firstPathInfo.m_wBaseLinkId;
    else {
        auto* nodeLink = &m_pNodeLinks[first.m_wAreaId][numAddresses];
        auto linkCounter = 0u;
        while (!nodeLink->IsAreaValid()) {
            nodeLink += 12; // No clue why we jump 12 objects each time
            ++linkCounter;
        }

        firstLinkId = numAddresses + 12 * linkCounter;
        for (auto i = 0u; i < firstPathInfo.m_nNumLinks; ++i) {
            m_pNodeLinks[first.m_wAreaId][firstLinkId + i] = m_pNodeLinks[first.m_wAreaId][firstPathInfo.m_wBaseLinkId + i];
            m_pLinkLengths[first.m_wAreaId][firstLinkId + i] = m_pLinkLengths[first.m_wAreaId][firstPathInfo.m_wBaseLinkId + i];
            m_pPathIntersections[first.m_wAreaId][firstLinkId + i] = m_pPathIntersections[first.m_wAreaId][firstPathInfo.m_wBaseLinkId + i];
        }

        if (first.m_wAreaId < NUM_PATH_MAP_AREAS) {
            auto& linkInfo = m_aDynamicLinksBaseIds[first.m_wAreaId];
            for (auto i = 0u; i < NUM_DYNAMIC_LINKS_PER_AREA; ++i) {
                // Uninitialized dynamic link is set to -1, so if it's assigned anything last bit will change, no clue why R* didn't compare with -1 directly
                if (!linkInfo.m_aLinks[i].lastBit)
                    continue;

                m_aDynamicLinksBaseIds[first.m_wAreaId].m_aLinks[i].value = firstPathInfo.m_wBaseLinkId;
                m_aDynamicLinksIds[first.m_wAreaId].m_aLinks[i].value = firstLinkId;
                break;
            }
        }
    }

    m_pNodeLinks[first.m_wAreaId][firstLinkId + firstPathInfo.m_nNumLinks] = second;
    m_pLinkLengths[first.m_wAreaId][firstLinkId + firstPathInfo.m_nNumLinks] = 5;
    m_pPathIntersections[first.m_wAreaId][firstLinkId + firstPathInfo.m_nNumLinks].Clear();
    firstPathInfo.m_nNumLinks++;
    firstPathInfo.m_wBaseLinkId = firstLinkId;
}

// 0x44FCE0
CNodeAddress CPathFind::FindNodeClosestToCoorsFavourDirection(CVector pos, uint8 nodeType, float dirX, float dirY) {
    CNodeAddress outAddress;
    plugin::CallMethod<0x44FCE0, CPathFind*, CNodeAddress*, CVector, unsigned char, float, float>(this, &outAddress, pos, nodeType, dirX, dirY);
    return outAddress;
}
