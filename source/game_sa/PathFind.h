/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "CompressedVector.h"
#include "Vector.h"
#include "NodeAddress.h"
#include "NodeRoute.h"

static constexpr auto NUM_PATH_MAP_AREA_X{ 8 };
static constexpr auto NUM_PATH_MAP_AREA_Y{ 8 };
static constexpr auto NUM_PATH_MAP_AREAS{ NUM_PATH_MAP_AREA_X * NUM_PATH_MAP_AREA_Y };
static constexpr auto NUM_PATH_INTERIOR_AREAS{ 8 };
static constexpr auto NUM_DYNAMIC_LINKS_PER_AREA{ 16 };

enum ePathType : uint8 {
    PATH_TYPE_CARS = 0,
    PATH_TYPE_BOATS
};

enum eTrafficLevel {
    TRAFFIC_FULL = 0,
    TRAFFIC_HIGH = 1,
    TRAFFIC_MEDIUM = 2,
    TRAFFIC_LOW = 3,
};

class CForbiddenArea {
public:
    float m_fXMin;
    float m_fXMax;
    float m_fYMin;
    float m_fYMax;
    float m_fZMin;
    float m_fZMax;
    bool  m_bEnable;
    uint8 m_nType;
};
VALIDATE_SIZE(CForbiddenArea, 0x1C);

class CCarPathLinkAddress {
public:
    CCarPathLinkAddress() {
        m_wCarPathLinkId = -1;
        m_wAreaId = -1;
    }

    operator CNodeAddress() const { return CNodeAddress{ m_wAreaId, m_wCarPathLinkId }; }

public:
    uint16 m_wCarPathLinkId : 10;
    uint16 m_wAreaId : 6;

    inline bool IsValid() {
        return *reinterpret_cast<uint16*>(this) != 0xFFFF;
    }
};
VALIDATE_SIZE(CCarPathLinkAddress, 0x2);

class CPathIntersectionInfo {
public:
    uint8 m_bRoadCross : 1;
    uint8 m_bPedTrafficLight : 1;

    inline void Clear() {
        *(uint8*)this = 0u;
    }
};
VALIDATE_SIZE(CPathIntersectionInfo, 0x1);

class CPathUnknClass {
public:
    union {
        uint32 value;
        struct {
            uint32 pad : 31;
            uint32 lastBit : 1;
        };
    } m_aLinks[NUM_DYNAMIC_LINKS_PER_AREA];
};
VALIDATE_SIZE(CPathUnknClass, 0x40);

class CCarPathLink {
public:
    struct {
        int16 x;
        int16 y;
    } m_posn;
    CNodeAddress m_address;
    int8         m_nDirX;
    int8         m_nDirY;
    int8         m_nPathNodeWidth; /// Has to be divided by `0.011574074f` (not yet sure why)
    uint8        m_nNumLeftLanes : 3;
    uint8        m_nNumRightLanes : 3;
    uint8        m_bTrafficLightDirection : 1; // 1 if the navi node has the same direction as the traffic light and 0 if the navi node points somewhere else
    uint8        unk1 : 1;

    uint16 m_nTrafficLightState : 2; // 1 - North-South, 2 - West-East cycle, enum: eTrafficLightsDirection
    uint16 m_bTrainCrossing : 1;

    float OneWayLaneOffset() const {
        if (m_nNumLeftLanes) {
            return 0.5f - (float)m_nNumRightLanes / 2.f;
        }        
        if (m_nNumRightLanes) {
            return 0.5f - (float)m_nPathNodeWidth * 0.011574074f / 2.f;
        }
        return 0.5f - (float)m_nNumLeftLanes / 2.f;
    }
};
VALIDATE_SIZE(CCarPathLink, 0xE);

class CPathNode {
public:
    void*            ptr;
    void*            ptr2;
    CompressedVector m_vPos;
    uint16           m_wSearchList; // search list id
    int16            m_wBaseLinkId;
    int16            m_wAreaId;
    int16            m_wNodeId;
    uint8            m_nPathWidth;
    uint8            m_nFloodFill;

    uint32 m_nNumLinks : 4;
    uint32 m_nTrafficLevel : 2; // TrafficLevel uses 4 steps: 0 = full 1 = high 2 = medium 3 = low
    uint32 m_bRoadBlocks : 1;
    uint32 m_bWaterNode : 1;

    uint32 m_bEmergencyVehiclesOnly : 1;
    uint32 unk1 : 1; // not used in paths data files
    uint32 m_bDontWander : 1;
    uint32 unk2 : 1; // not used in paths data files
    uint32 m_bNotHighway : 1;
    uint32 m_bHighway : 1;
    uint32 unk3 : 1; // not used in paths data files
    uint32 unk4 : 1; // not used in paths data files

    uint32 m_nSpawnProbability : 4;
    uint32 m_nBehaviourType : 4; // 1 - roadblock
                                 // 2 - parking node

public:
    static void InjectHooks();
    CVector GetNodeCoors();

    inline bool IsLowTrafficLevel() const {
        return m_nTrafficLevel == TRAFFIC_MEDIUM || m_nTrafficLevel == TRAFFIC_LOW;
    }
};
VALIDATE_SIZE(CPathNode, 0x1C);

class CPathFind {
public:
    CNodeAddress           m_Info;
    CPathNode*             m_apNodesSearchLists[512];
    CPathNode*             m_pPathNodes[NUM_PATH_MAP_AREAS + NUM_PATH_INTERIOR_AREAS];
    // Use CPathFind::GetCarPathLink to access
    CCarPathLink*          m_pNaviNodes[NUM_PATH_MAP_AREAS + NUM_PATH_INTERIOR_AREAS];
    CNodeAddress*          m_pNodeLinks[NUM_PATH_MAP_AREAS + NUM_PATH_INTERIOR_AREAS];
    uint8*                 m_pLinkLengths[NUM_PATH_MAP_AREAS + NUM_PATH_INTERIOR_AREAS];
    CPathIntersectionInfo* m_pPathIntersections[NUM_PATH_MAP_AREAS + NUM_PATH_INTERIOR_AREAS];
    CCarPathLinkAddress*   m_pNaviLinks[NUM_PATH_MAP_AREAS];
    void*                  m_aUnused[NUM_PATH_MAP_AREAS];
    uint32                 m_anNumNodes[NUM_PATH_MAP_AREAS + NUM_PATH_INTERIOR_AREAS];
    uint32                 m_anNumVehicleNodes[NUM_PATH_MAP_AREAS + NUM_PATH_INTERIOR_AREAS];
    uint32                 m_anNumPedNodes[NUM_PATH_MAP_AREAS + NUM_PATH_INTERIOR_AREAS];
    uint32                 m_anNumCarPathLinks[NUM_PATH_MAP_AREAS + NUM_PATH_INTERIOR_AREAS];
    uint32                 m_anNumAddresses[NUM_PATH_MAP_AREAS + NUM_PATH_INTERIOR_AREAS];
    CPathUnknClass         m_aDynamicLinksBaseIds[NUM_PATH_MAP_AREAS];
    CPathUnknClass         m_aDynamicLinksIds[NUM_PATH_MAP_AREAS];
    uint32                 m_dwTotalNumNodesInSearchList;
    CNodeAddress           m_aInteriorNodes[NUM_PATH_INTERIOR_AREAS];
    uint32                 m_nNumForbiddenAreas;
    CForbiddenArea         m_aForbiddenAreas[NUM_PATH_MAP_AREAS];
    bool                   m_bNodesLoadingRequested;
    float                  m_fForbiddenForScrCarsX1;
    float                  m_fForbiddenForScrCarsX2;
    float                  m_fForbiddenForScrCarsY1;
    float                  m_fForbiddenForScrCarsY2;

public:
    static int32& InteriorIDBeingBuilt;
    static bool& bInteriorBeingBuilt;
    static int32& NumNodesGiven;
    static int32& NumLinksToExteriorNodes;
    static int32& NewInteriorSlot;

public:
    static void InjectHooks();

    void Init();
    static void PreparePathData() { /*noop 0x44D0E0*/ }
    void UnLoadPathFindData(int32 index);
    void RemoveBadStartNode(CVector pos, CNodeAddress* address, int16* numPathFindNodes);
    void CountFloodFillGroups(uint8 type);
    void CheckGrid();
    float CalcRoadDensity(float x, float y);
    void RemoveNodeFromList(CPathNode* node);
    void AddNodeToList(CPathNode* node, int list);
    float CalcDistToAnyConnectingLinks(CPathNode* node, CVector pos);
    void FindNodeClosestInRegion(CNodeAddress* outAddress, uint16 areaId, CVector pos, uint8 nodeType, float* outDist, bool bLowTraffic, bool bUnkn, bool bBoats, bool bUnused);
    bool These2NodesAreAdjacent(CNodeAddress address1, CNodeAddress address2);
    void RecordNodesInCircle(const CVector& center, float radius, uint8 nodeType, int maxNum, CNodeAddress* outAddresses, bool bLowTraffic, bool a8, bool bUnkn, bool maxNumNodes, bool bUnused);
    CNodeAddress FindNodeClosestToCoorsFavourDirection(CVector pos, uint8 nodeType, float dirX, float dirY);
    void FindNodePairClosestToCoors(CVector pos, uint8 nodeType, CNodeAddress* outFirst, CNodeAddress* outSecond, float* outDist, float minDist, float maxDist, bool bLowTraffic, bool bUnused, bool bBoats);
    float FindNodeOrientationForCarPlacement(CNodeAddress address);
    float FindNodeOrientationForCarPlacementFacingDestination(CNodeAddress address, float dirX, float dirY, bool bUnkn) { return 0.0f; } /*noop, not in PC idb, unused in mobile*/
    static void AllocatePathFindInfoMem() { /*noop 0x44D2B0*/ }
    void StoreNodeInfoCar(int16, int16, int8, int8, int16, int16, int16, float, int8, int8, bool, bool, uint8, bool, bool, uint8, uint8) { /*noop*/ }
    void StoreNodeInfoPed(int16, int16, int8, int8, int16, int16, int16, float, bool, uint8, bool, uint8) { /*noop*/ }
    void StoreDetachedNodeInfoPed(int, int8, int, float, float, float, float, bool, bool, bool, uint8, bool, uint8, bool) { /*noop*/ }
    void StoreDetachedNodeInfoCar(int, int8, int, float, float, float, float, int8, int8, bool, bool, uint8, bool, bool, uint8, bool, uint8) { /*noop*/ }
    void RegisterMarker(CVector* pos) { /*noop*/ }
    bool ThisNodeWillLeadIntoADeadEnd(CPathNode* startNode, CPathNode* endNode);
    void TidyUpNodeSwitchesAfterMission();
    void SwitchRoadsInAngledArea(float, float, float, float, float, float, float, uint8, uint8) { /*noop*/ }
    bool ThisNodeHasToBeSwitchedOff(CPathNode* node);
    int CountNeighboursToBeSwitchedOff(CPathNode* node);
    void SwitchOffNodeAndNeighbours(CPathNode* node, CPathNode** out1, CPathNode** out2, char bLowTraffic, uint8 areaId);
    void SwitchRoadsOffInAreaForOneRegion(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax, bool bLowTraffic, uint8 nodeType, int areaId, uint8 bUnused);
    void SwitchRoadsOffInArea(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax, bool bLowTraffic, uint8 nodeType, bool bForbidden);
    void SwitchPedRoadsOffInArea(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax, bool bLowTraffic, uint8 nodeType);
    void LoadPathFindData(RwStream* stream, int32 areaId);
    void LoadPathFindData(int32 areaId);
    void UnMarkAllRoadNodesAsDontWander();
    void MarkRoadsBetweenLevelsInArea(float, float, float, float, float, float) { /*noop*/ }
    void PedMarkRoadsBetweenLevelsInArea(float, float, float, float, float, float) { /*noop*/ }
    void MarkRoadsBetweenLevelsNodeAndNeighbours(int) { /*noop*/ }
    bool TestForPedTrafficLight(CNodeAddress startNodeAddress, CNodeAddress targetNodeAddress);
    bool TestCrossesRoad(CNodeAddress startNodeAddress, CNodeAddress targetNodeAddress);
    uint32 FindRegionForCoors(float x, float y);
    bool GeneratePedCreationCoors_Interior(float x, float y, CVector* outCoords, CNodeAddress* unused1, CNodeAddress* unused2, float* outOrientation);
    void GeneratePedCreationCoors(float x, float y, float minDist1, float maxDist1, float minDist2, float maxDist2, CVector* outCoords, CNodeAddress* outAddress1,
                                  CNodeAddress* outAddress2, float* outOrientation, bool bLowTraffic, CMatrix* transformMatrix);
    uint32 FindXRegionForCoors(float x);
    uint32 FindYRegionForCoors(float y);
    float FindXCoorsForRegion(uint32 regionX);
    float FindYCoorsForRegion(uint32 regionY);
    CNodeAddress FindNodeClosestToCoors(CVector pos, int32 nodeType, float maxDistance, uint16 unk2, int32 unk3, uint16 unk4,
                                         uint16 bBoatsOnly, int32 unk6);
    void MarkRoadNodeAsDontWander(float x, float y, float z);
    void RecordNodesClosestToCoors(CVector pos, uint8 nodeType, int count, CNodeAddress* outAddresses, float maxDist, bool, bool, bool, bool);
    void Find2NodesForCarCreation(CVector pos, CNodeAddress* outAddress1, CNodeAddress* outAddress2, bool bLowTraffic);
    CNodeAddress FindNthNodeClosestToCoors(CVector pos, uint8 nodeType, float maxDistance, bool bLowTraffic, bool bUnkn, int nthNode, bool bBoatsOnly, bool bIgnoreInterior,
                                           CNodeAddress* outNode);
    void FindNextNodeWandering(uint8 nodeType, CVector vecPos, CNodeAddress* originAddress, CNodeAddress* targetAddress, uint8 dir, uint8* outDir);
    void DoPathSearch(uint8 pathType, CVector origin, CNodeAddress originAddr, CVector target, CNodeAddress* pResultNodes, int16* pNodesCount, int32 maxNodesToFind,
                      float* pDistance, float maxSearchDistance, CNodeAddress* targetAddr, float maxUnkLimit, bool oneSideOnly, CNodeAddress forbiddenNodeAddr,
                      bool includeNodesWithoutLinks, bool waterPath);
    bool TestCoorsCloseness(CVector vecEnd, uint8 nodeType, CVector vecStart); // unused
    void ComputeRoute(uint8 nodeType, const CVector& vecStart, const CVector& vecEnd, const CNodeAddress& address, CNodeRoute& nodeRoute);
    void FindStartPointOfRegion(int regionX, int regionY, float& outX, float& outY);
    void SetLinksBridgeLights(float fXMin, float fXMax, float fYMin, float fYMax, bool bTrainCrossing);
    CVector FindNodeCoorsForScript(CNodeAddress address, bool* bFound);
    CVector FindNodeCoorsForScript(CNodeAddress address1, CNodeAddress address2, float* fOutDir, bool* bFound);
    void Shutdown();
    CVector TakeWidthIntoAccountForWandering(CNodeAddress nodeAddress, uint16 randomSeed);
    void TakeWidthIntoAccountForCoors(CNodeAddress address, CNodeAddress address2, uint16 seed, float* fOut1, float* fOut2);
    static void MarkRegionsForCoors(CVector vecPos, float radius);
    void SetPathsNeededAtPosition(const CVector& vecPos);
    void UpdateStreaming(bool bForceStreaming);
    void MakeRequestForNodesToBeLoaded(float x1, float x2, float y1, float y2);
    void ReleaseRequestedNodes();
    void ReInit();
    bool AreNodesLoadedForArea(float minX, float maxX, float minY, float maxY);
    bool HaveRequestedNodesBeenLoaded();
    void LoadSceneForPathNodes(CVector point);
    bool IsWaterNodeNearby(CVector position, float radius);
    void StartNewInterior(int interiorNum);
    CNodeAddress AddNodeToNewInterior(float x, float y, float z, bool bDontWander, int8 con0, int8 con1, int8 con2, int8 con3, int8 con4, int8 con5);
    void AddInteriorLink(int unkn1, int unkn2);
    void AddInteriorLinkToExternalNode(int unkn, CNodeAddress interiorAddress, CNodeAddress exteriorAddress);
    void RemoveInteriorLinks(int unkn);
    CNodeAddress FindNearestExteriorNodeToInteriorNode(int interiorId);
    void AddDynamicLinkBetween2Nodes_For1Node(CNodeAddress node1, CNodeAddress node2);
    void AddDynamicLinkBetween2Nodes(CNodeAddress node1, CNodeAddress node2);
    void CompleteNewInterior(CNodeAddress* outAddress);
    void RemoveInterior(uint32 interior);
    CNodeAddress ReturnInteriorNodeIndex(int32 unkn, CNodeAddress addressToFind, int16 nodeId);
    CNodeAddress FindLinkBetweenNodes(CNodeAddress node1, CNodeAddress node2);
    CVector FindParkingNodeInArea(float minX, float maxX, float minY, float maxY, float minZ, float maxZ);
    bool Load();
    bool Save();

    CPathNode* GetPathNode(CNodeAddress address);

    inline CCarPathLink& GetCarPathLink(const CCarPathLinkAddress& address) {
        assert(address.m_wAreaId < NUM_PATH_MAP_AREAS + NUM_PATH_INTERIOR_AREAS);
        return m_pNaviNodes[address.m_wAreaId][address.m_wCarPathLinkId];
    }

    // Helpers - NOTSA
    bool FindNodeCoorsForScript(CVector& outPos, CNodeAddress addr);

    bool IsNodeAreaLoaded(CNodeAddress addr) const { assert(addr.IsAreaValid()); return m_pPathNodes[addr.m_wAreaId]; }
    bool IsNodeAreaLoaded(const std::initializer_list<CNodeAddress>& addrs) const;
};

VALIDATE_SIZE(CPathFind, 0x3C80);

extern CPathFind& ThePaths;
