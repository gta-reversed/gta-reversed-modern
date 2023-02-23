/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

#include "PathFind.h"

CPathFind& ThePaths = *(CPathFind*)(0x96F050);
int32& CPathFind::InteriorIDBeingBuilt = *(int32*)0x96EF88;
bool& CPathFind::bInteriorBeingBuilt = *(bool*)0x96F031;
int32& CPathFind::NumNodesGiven = *(int32*)0x96EF80;
int32& CPathFind::NumLinksToExteriorNodes = *(int32*)0x96EAB8;
int32& CPathFind::NewInteriorSlot = *(int32*)0x96EF84;

void CPathFind::InjectHooks() {
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
    RH_ScopedOverloadedInstall(LoadPathFindData, "void", 0x452F40, void(CPathFind::*)(int32));
    RH_ScopedOverloadedInstall(LoadPathFindData, "stream", 0x4529F0, void(CPathFind::*)(RwStream*, int32));
    RH_ScopedInstall(UnLoadPathFindData, 0x44D0F0);
    RH_ScopedInstall(GetPathNode, 0x420AC0);
    RH_ScopedInstall(AddDynamicLinkBetween2Nodes_For1Node, 0x44E000);
}

void CPathNode::InjectHooks() {
    RH_ScopedClass(CPathNode);
    RH_ScopedCategoryGlobal();
    RH_ScopedInstall(GetNodeCoors, 0x420A10);
}

CVector CPathNode::GetNodeCoors() {
    return UncompressLargeVector(m_vPos);
}

// 0x44D080
void CPathFind::Init() {
    static int32 NumTempExternalNodes = 0; // Unused
    m_nNumForbiddenAreas = 0;
    m_bNodesLoadingRequested = false;

    for (auto i = 0u; i < NUM_PATH_MAP_AREAS + NUM_PATH_INTERIOR_AREAS; ++i) {
        m_pPathNodes[i] = nullptr;
        m_pNaviNodes[i] = nullptr;
        m_pNodeLinks[i] = nullptr;
        m_pLinkLengths[i] = nullptr;
        m_pPathIntersections[i] = nullptr;
        m_pNaviLinks[i] = nullptr; // BUG: Out of array bounds write, same as in original code
        m_aUnused[i] = nullptr;    // BUG: Out of array bounds write, same as in original code
    }

    memset(m_aInteriorNodes, 0xFF, sizeof(m_aInteriorNodes));
}

// 0x44E4E0
void CPathFind::ReInit() {
    m_nNumForbiddenAreas = 0;
    m_bNodesLoadingRequested = false;
}

// 0x44DD10
bool CPathFind::AreNodesLoadedForArea(float minX, float maxX, float minY, float maxY) {
    return plugin::CallMethodAndReturn<bool, 0x44DD10, CPathFind*, float, float, float, float>(this, minX, maxX, minY, maxY);
}

// 0x450950
void CPathFind::Shutdown() {
    for (auto x = 0u; x < NUM_PATH_MAP_AREA_X; ++x) {
        for (auto y = 0u; y < NUM_PATH_MAP_AREA_Y; ++y) {
            auto relativeId = x + y * NUM_PATH_MAP_AREA_X;
            if (m_pPathNodes[relativeId]) {
                CStreaming::RemoveModel(DATToModelId(relativeId));
            }
        }
    }
}

// 0x44D3B0
void CPathFind::TidyUpNodeSwitchesAfterMission() {
    m_nNumForbiddenAreas = std::min(54u, m_nNumForbiddenAreas); // todo: magic number
}

// 0x44D400
void CPathFind::UnMarkAllRoadNodesAsDontWander() {
    for (auto i = 0u; i < NUM_PATH_MAP_AREAS; ++i) {
        if (!m_pPathNodes[i])
            continue;

        for (auto nodeInd = 0u; nodeInd < m_anNumVehicleNodes[i]; ++nodeInd) {
            m_pPathNodes[i][nodeInd].m_bDontWander = false;
        }
    }
}

// 0x44DD00
void CPathFind::ReleaseRequestedNodes() {
    m_bNodesLoadingRequested = false;
}

// 0x44D790
bool CPathFind::TestCrossesRoad(CNodeAddress startNodeAddress, CNodeAddress targetNodeAddress) {
    return plugin::CallMethodAndReturn<bool, 0x44D790, CPathFind*, CNodeAddress, CNodeAddress>(this, startNodeAddress, targetNodeAddress);
}

// 0x44ECA0
bool CPathFind::GeneratePedCreationCoors_Interior(float x, float y, CVector* outCoords, CNodeAddress* unused1, CNodeAddress* unused2, float* outOrientation) {
    return plugin::CallMethodAndReturn<bool, 0x44ECA0>(this, x, y, outCoords, unused1, unused2, outOrientation);
}

// 0x44D480
bool CPathFind::TestForPedTrafficLight(CNodeAddress startNodeAddress, CNodeAddress targetNodeAddress) {
    return plugin::CallMethodAndReturn<bool, 0x44D480, CPathFind*, CNodeAddress, CNodeAddress>(this, startNodeAddress, targetNodeAddress);
}

CVector CPathFind::TakeWidthIntoAccountForWandering(CNodeAddress nodeAddress, uint16 randomSeed) {
    CVector vecOut;
    plugin::CallMethod<0x4509A0, CPathFind*, CVector*, CNodeAddress, uint16>(this, &vecOut, nodeAddress, randomSeed);
    return vecOut;
}

//  0x44F8C0
CNodeAddress CPathFind::FindNthNodeClosestToCoors(CVector pos, uint8 nodeType, float maxDistance, bool bLowTraffic, bool bUnkn, int32 nthNode, bool bBoatsOnly,
                                                  bool bIgnoreInterior, CNodeAddress* outNode) {
    CNodeAddress outAddress;
    plugin::CallMethod<0x44F8C0, CPathFind*, CNodeAddress*, CVector, uint8, float, bool, bool, int32, bool, bool, CNodeAddress*>(
        this, &outAddress, pos, nodeType, maxDistance, bLowTraffic, bUnkn, nthNode, bBoatsOnly, bIgnoreInterior, outNode);
    return outAddress;
}

// 0x451B70
void CPathFind::FindNextNodeWandering(uint8 nodeType, CVector vecPos, CNodeAddress* originAddress, CNodeAddress* targetAddress, uint8 dir, uint8* outDir) {
    plugin::CallMethod<0x451B70, CPathFind*, uint8, CVector, CNodeAddress*, CNodeAddress*, uint8, uint8*>(this, nodeType, vecPos, originAddress, targetAddress, dir, outDir);
}

void CPathFind::DoPathSearch(uint8 pathType, CVector origin, CNodeAddress originAddr, CVector target, CNodeAddress* pResultNodes, int16* pNodesCount, int32 maxNodesToFind,
                             float* pDistance, float maxSearchDistance, CNodeAddress* targetAddr, float maxUnkLimit, bool oneSideOnly, CNodeAddress forbiddenNodeAddr,
                             bool includeNodesWithoutLinks, bool waterPath) {
    ((void(__thiscall*)(CPathFind*, uint8, CVector, CNodeAddress, CVector, CNodeAddress*, int16*, int32, float*, float, CNodeAddress*, float, bool, CNodeAddress, bool,
                        bool))0x4515D0)(this, pathType, origin, originAddr, target, pResultNodes, pNodesCount, maxNodesToFind, pDistance, maxSearchDistance, targetAddr,
                                        maxUnkLimit, oneSideOnly, forbiddenNodeAddr, includeNodesWithoutLinks, waterPath);
}

void CPathFind::SetLinksBridgeLights(float fXMin, float fXMax, float fYMin, float fYMax, bool bTrainCrossing) {
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

// 0x452820
void CPathFind::SwitchRoadsOffInAreaForOneRegion(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax, bool bLowTraffic, uint8 nodeType, int32 areaId,
                                                 uint8 bUnused) {
    return plugin::CallMethod<0x452820, CPathFind*, float, float, float, float, float, float, bool, char, int32, bool>(this, xMin, xMax, yMin, yMax, zMin, zMax, bLowTraffic,
                                                                                                                       nodeType, areaId, bUnused);
}

// NOTSA
CPathNode* CPathFind::GetPathNode(CNodeAddress address) {
    assert(address.IsValid());
    return &m_pPathNodes[address.m_wAreaId][address.m_wNodeId];
}

// NOTSA
bool CPathFind::FindNodeCoorsForScript(CVector& outPos, CNodeAddress addr) {
    bool valid{};
    FindNodeCoorsForScript(addr, &valid);
    return valid;
}

// 0x452F40
void CPathFind::LoadPathFindData(int32 areaId) {
    CTimer::Suspend();
    sprintf_s(gString, "data\\paths\\nodes%d.dat", areaId);
    auto* stream = RwStreamOpen(RwStreamType::rwSTREAMFILENAME, RwStreamAccessType::rwSTREAMREAD, gString);
    LoadPathFindData(stream, areaId);
    CTimer::Resume();
}

// 0x4529F0
void CPathFind::LoadPathFindData(RwStream* stream, int32 areaId) {
    RwStreamRead(stream, &m_anNumNodes[areaId],        sizeof(m_anNumNodes[areaId]));
    RwStreamRead(stream, &m_anNumVehicleNodes[areaId], sizeof(m_anNumVehicleNodes[areaId]));
    RwStreamRead(stream, &m_anNumPedNodes[areaId],     sizeof(m_anNumPedNodes[areaId]));
    RwStreamRead(stream, &m_anNumCarPathLinks[areaId], sizeof(m_anNumCarPathLinks[areaId]));
    RwStreamRead(stream, &m_anNumAddresses[areaId],    sizeof(m_anNumAddresses[areaId]));

    auto numNodes = m_anNumNodes[areaId];
    if (numNodes) {
        m_pPathNodes[areaId] = new CPathNode[numNodes];
        RwStreamRead(stream, m_pPathNodes[areaId], sizeof(CPathNode) * numNodes);
    } else {
        m_pPathNodes[areaId] = new CPathNode[1];
    }

    auto numCarPathLinks = m_anNumCarPathLinks[areaId];
    if (numCarPathLinks) {
        m_pNaviNodes[areaId] = new CCarPathLink[numCarPathLinks];
        RwStreamRead(stream, m_pNaviNodes[areaId], sizeof(CCarPathLink) * numCarPathLinks);
    } else {
        m_pNaviNodes[areaId] = nullptr;
    }

    auto numAddresses = m_anNumAddresses[areaId];
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

    for (auto i = 0u; i < m_nNumForbiddenAreas; ++i) {
        auto& area = m_aForbiddenAreas[i];
        SwitchRoadsOffInAreaForOneRegion(area.m_fXMin, area.m_fXMax, area.m_fYMin, area.m_fYMax, area.m_fZMin, area.m_fZMax, area.m_bEnable, area.m_nType, areaId, false);
    }

    for (auto i = 0u; i < NUM_DYNAMIC_LINKS_PER_AREA; ++i) {
        m_aDynamicLinksBaseIds[areaId].m_aLinks[i].value = (uint32)-1;
        m_aDynamicLinksIds[areaId].m_aLinks[i].value = (uint32)-1;
    }
}

// 0x44D0F0
void CPathFind::UnLoadPathFindData(int32 index) {
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

// 0x44DE00
void CPathFind::LoadSceneForPathNodes(CVector point) {
    plugin::CallMethod<0x44DE00, CPathFind*, CVector>(this, point);
}

// 0x450DE0
bool CPathFind::IsWaterNodeNearby(CVector position, float radius) {
    return plugin::CallMethodAndReturn<bool, 0x450DE0, CPathFind*, CVector, float>(this, position, radius);
}

// 0x44F460
CNodeAddress CPathFind::FindNodeClosestToCoors(CVector pos, int32 nodeType, float maxDistance, uint16 unk2, int32 unk3, uint16 unk4, uint16 bBoatsOnly, int32 unk6) {
    CNodeAddress tempAddress;
    plugin::CallMethodAndReturn<CNodeAddress*, 0x44F460, CPathFind*, CNodeAddress*, CVector, int32, float, uint16, int32, uint16, uint16, int32>(
        this, &tempAddress, pos, nodeType, maxDistance, unk2, unk3, unk4, bBoatsOnly, unk6);
    return tempAddress;
}

// 0x450A60
void CPathFind::UpdateStreaming(bool bForceStreaming) {
    return plugin::CallMethod<0x450A60, CPathFind*, bool>(this, bForceStreaming);
}

// 0x44DE80
void CPathFind::StartNewInterior(int32 interiorNum) {
    InteriorIDBeingBuilt = interiorNum;
    bInteriorBeingBuilt = true;
    NumNodesGiven = 0;
    NumLinksToExteriorNodes = 0;

    // BUG: Possible endless loop if 8 interiors are loaded i think
    NewInteriorSlot = 0;
    while (m_aInteriorNodes[NewInteriorSlot].IsValid()) {
        NewInteriorSlot++;
        assert(NewInteriorSlot < 8);
    }
}

// 0x450E90
CNodeAddress CPathFind::AddNodeToNewInterior(float x, float y, float z, bool bDontWander, int8 con0, int8 con1, int8 con2, int8 con3, int8 con4, int8 con5) {
    CNodeAddress outAddress;
    plugin::CallMethod<0x450E90, CPathFind*, CNodeAddress*, float, float, float, bool, int8, int8, int8, int8, int8, int8>(this, &outAddress, x, y, z, bDontWander, con0, con1,
                                                                                                                           con2, con3, con4, con5);
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
CNodeAddress CPathFind::FindNearestExteriorNodeToInteriorNode(int32 interiorId) {
    CNodeAddress outAddress;
    plugin::CallMethod<0x450F30, CPathFind*, CNodeAddress*, int32>(this, &outAddress, interiorId);
    return outAddress;
}

// 0x44E000
void CPathFind::AddDynamicLinkBetween2Nodes_For1Node(CNodeAddress first, CNodeAddress second) {
    auto& firstPathInfo = m_pPathNodes[first.m_wAreaId][first.m_wNodeId];
    auto numAddresses = m_anNumAddresses[first.m_wAreaId];

    uint32 firstLinkId;
    if (static_cast<uint32>(firstPathInfo.m_wBaseLinkId) >= numAddresses)
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
    plugin::CallMethod<0x44FCE0, CPathFind*, CNodeAddress*, CVector, uint8, float, float>(this, &outAddress, pos, nodeType, dirX, dirY);
    return outAddress;
}

// 0x5D3500
bool CPathFind::Load() {
    return plugin::CallMethodAndReturn<bool, 0x5D3500>(this);
}

// 0x5D1502
bool CPathFind::Save() {
    return plugin::CallMethodAndReturn<bool, 0x5D1502>(this);
}
