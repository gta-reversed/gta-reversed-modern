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
#include <functional>

static constexpr auto NUM_PATH_MAP_AREA_X{ 8 };
static constexpr auto NUM_PATH_MAP_AREA_Y{ 8 };
static constexpr auto NUM_PATH_MAP_AREAS{ NUM_PATH_MAP_AREA_X * NUM_PATH_MAP_AREA_Y };
static constexpr auto NUM_PATH_INTERIOR_AREAS{ 8 };
static constexpr auto NUM_DYNAMIC_LINKS_PER_AREA{ 16 };

enum ePathType : uint8 {
    PATH_TYPE_VEH, /// Cars, boats, race tracks
    PATH_TYPE_PED, /// Peds

    PATH_TYPE_ALL /// @notsa
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
    CCarPathLinkAddress(size_t area, size_t nodeId) :
        m_wCarPathLinkId{ (uint16)nodeId },
        m_wAreaId{ (uint16)area }
    {
    }

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
    } m_posn; /// Fixed-point ("compressed") position
    CNodeAddress m_address;
    int8         m_nDirX;
    int8         m_nDirY;
    int8         m_nPathNodeWidth; /// Has to be divided by `0.011574074f` (not yet sure why)
    uint8        m_nNumLeftLanes : 3;
    uint8        m_nNumRightLanes : 3;
    uint8        m_bTrafficLightDirection : 1; // 1 if the navi node has the same direction as the traffic light and 0 if the navi node points somewhere else
    uint8        unk1 : 1;

    uint16 m_nTrafficLightState : 2; // 1 - North-South, 2 - West-East cycle, enum: eTrafficLightsDirection
    uint16 m_bridgeLights : 1;

    float OneWayLaneOffset() const {
        if (m_nNumLeftLanes) {
            return 0.5f - (float)m_nNumRightLanes / 2.f;
        }        
        if (m_nNumRightLanes) {
            return 0.5f - (float)m_nPathNodeWidth * 0.011574074f / 2.f;
        }
        return 0.5f - (float)m_nNumLeftLanes / 2.f;
    }

    /// Get uncompressed world position
    auto GetNodeCoors() const {
        return CVector2D{ (float)m_posn.x, (float)m_posn.y } / 8.f;
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
    uint16           m_wAreaId; // TODO: Replace these 2 with `CNodeAddress`
    uint16           m_wNodeId;
    uint8            m_nPathWidth;
    uint8            m_nFloodFill;

    // byte 0
    uint32 m_nNumLinks : 4; // Mask: 0xF
    uint32 m_nTrafficLevel : 2; // TrafficLevel uses 4 steps: 0 = full 1 = high 2 = medium 3 = low
    uint32 m_bRoadBlocks : 1;
    uint32 m_bWaterNode : 1;

    // byte 1
    uint32 m_bEmergencyVehiclesOnly : 1;
    uint32 unk1 : 1; // not used in paths data files
    uint32 m_bDontWander : 1;
    uint32 unk2 : 1; // not used in paths data files
    uint32 m_bNotHighway : 1;
    uint32 m_bHighway : 1;
    uint32 unk3 : 1; // not used in paths data files
    uint32 unk4 : 1; // not used in paths data files

    // byte 2
    uint32 m_nSpawnProbability : 4;
    uint32 m_nBehaviourType : 4; // 1 - roadblock
                                 // 2 - parking node
    // byte 3
public:
    static void InjectHooks();

    /// Get uncompressed world position
    CVector GetNodeCoors() const {
        return UncompressLargeVector(m_vPos);
    }

    inline bool IsLowTrafficLevel() const {
        return m_nTrafficLevel == TRAFFIC_MEDIUM || m_nTrafficLevel == TRAFFIC_LOW;
    }

    CNodeAddress GetAddress() const {
        return { m_wAreaId, m_wNodeId };
    }
};
VALIDATE_SIZE(CPathNode, 0x1C);

class CPathFind {
    static constexpr auto NUM_TOTAL_PATH_NODE_AREAS = NUM_PATH_MAP_AREAS + NUM_PATH_INTERIOR_AREAS;

public:
    CNodeAddress           m_Info; // 0x0
    CPathNode*             m_apNodesSearchLists[512]; // 0x4

    /*!
    * Pointer to an array containing all path nodes in an area (count: `m_anNumNodes`)
    * The first part of the array has the vehicle nodes (count: `m_anNumVehicleNodes`)
    * the remaining part has ped nodes (count: `m_anNumPedNodes`)
    */
    CPathNode*             m_pPathNodes[NUM_PATH_MAP_AREAS + NUM_PATH_INTERIOR_AREAS]; // 0x804

    // Use CPathFind::GetCarPathLink to access
    CCarPathLink*          m_pNaviNodes[NUM_PATH_MAP_AREAS + NUM_PATH_INTERIOR_AREAS]; // 0x924
    CNodeAddress*          m_pNodeLinks[NUM_PATH_MAP_AREAS + NUM_PATH_INTERIOR_AREAS]; // 0xA44
    uint8*                 m_pLinkLengths[NUM_PATH_MAP_AREAS + NUM_PATH_INTERIOR_AREAS]; // 0xB64
    CPathIntersectionInfo* m_pPathIntersections[NUM_PATH_MAP_AREAS + NUM_PATH_INTERIOR_AREAS]; // 0xC84
    CCarPathLinkAddress*   m_pNaviLinks[NUM_PATH_MAP_AREAS]; // 0xDA4
    void*                  m_aUnused[22]; // 0xEA4
    uint32                 m_aUnk[NUM_PATH_MAP_AREAS - 22]; // 0xEFC
    uint32                 m_anNumNodes[NUM_PATH_MAP_AREAS + NUM_PATH_INTERIOR_AREAS]; // 0xFA4
    uint32                 m_anNumVehicleNodes[NUM_PATH_MAP_AREAS + NUM_PATH_INTERIOR_AREAS]; // 0x10C4
    uint32                 m_anNumPedNodes[NUM_PATH_MAP_AREAS + NUM_PATH_INTERIOR_AREAS]; // 0x11E4
    uint32                 m_anNumCarPathLinks[NUM_PATH_MAP_AREAS + NUM_PATH_INTERIOR_AREAS];
    uint32                 m_anNumAddresses[NUM_PATH_MAP_AREAS + NUM_PATH_INTERIOR_AREAS];
    CPathUnknClass         m_aDynamicLinksBaseIds[NUM_PATH_MAP_AREAS];
    CPathUnknClass         m_aDynamicLinksIds[NUM_PATH_MAP_AREAS];
    uint32                 m_dwTotalNumNodesInSearchList;
    CNodeAddress           m_aInteriorNodes[NUM_PATH_INTERIOR_AREAS];
    uint32                 m_nNumForbiddenAreas;
    CForbiddenArea         m_aForbiddenAreas[NUM_PATH_MAP_AREAS];
    bool                   m_bForbiddenForScriptedCarsEnabled;
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
    /*!
    * @addr 0x44D230
    * @return If `nodeAddress2` is linked by `nodeAddress1`
    */
    bool These2NodesAreAdjacent(CNodeAddress nodeAddress1, CNodeAddress nodeAddress2);
    void RecordNodesInCircle(const CVector& center, float radius, uint8 nodeType, int maxNum, CNodeAddress* outAddresses, bool bLowTraffic, bool a8, bool bUnkn, bool maxNumNodes, bool bUnused);

    /*
    * @brief Find the node closest to `pos` favoring the direction `dir`
    *
    * @param pos The position to search around
    * @param nodeType The path node type to search
    * @param dir The direction, doesn't need to be unit length (eg.: normalized), it is normalized by the function
    */
    CNodeAddress FindNodeClosestToCoorsFavourDirection(CVector pos, ePathType nodeType, CVector2D dir); // "dir" was 2 floats originally
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
    void GeneratePedCreationCoors_Interior(float x, float y, CVector* outCoords, CNodeAddress* unused1, CNodeAddress* unused2, float* outOrientation);
    void GeneratePedCreationCoors(float x, float y, float minDist1, float maxDist1, float minDist2, float maxDist2, CVector* outCoords, CNodeAddress* outAddress1,
                                  CNodeAddress* outAddress2, float* outOrientation, bool bLowTraffic, CMatrix* transformMatrix);
    CNodeAddress FindNodeClosestToCoors(CVector pos, int32 nodeType, float maxDistance, uint16 unk2, int32 unk3, uint16 unk4,
                                         uint16 bBoatsOnly, int32 unk6);
    void MarkRoadNodeAsDontWander(float x, float y, float z);
    void RecordNodesClosestToCoors(CVector pos, uint8 nodeType, int count, CNodeAddress* outAddresses, float maxDist, bool, bool, bool, bool);
    void Find2NodesForCarCreation(CVector pos, CNodeAddress* outAddress1, CNodeAddress* outAddress2, bool bLowTraffic);
    CNodeAddress FindNthNodeClosestToCoors(CVector pos, uint8 nodeType, float maxDistance, bool bLowTraffic, bool bUnkn, int nthNode, bool bBoatsOnly, bool bIgnoreInterior,
                                           CNodeAddress* outNode);
    void FindNextNodeWandering(uint8 nodeType, CVector vecPos, CNodeAddress* originAddress, CNodeAddress* targetAddress, uint8 dir, uint8* outDir);
    void DoPathSearch(ePathType pathType, CVector origin, CNodeAddress originAddr, CVector target, CNodeAddress* pResultNodes, int16* pNodesCount, int32 maxNodesToFind,
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

    /*!
    * TODO: Move this garbage to source file instead, no need for it in here.
    */
    void MarkRegionsForCoors(CVector vecPos, float radius);

    /*!
    * @addr 0x44DCD0
    * @brief Load paths around the given position in a 350 radius next time `UpdateStreaming` is called
    */
    void SetPathsNeededAtPosition(const CVector& posn);
    void UpdateStreaming(bool bForceStreaming);
    void MakeRequestForNodesToBeLoaded(float x1, float x2, float y1, float y2);
    void ReleaseRequestedNodes();
    void ReInit();

    /*!
    * @addr 0x44DD10
    * @return If all areas within the given bounding rect are loaded
    */
    bool AreNodesLoadedForArea(float minX, float maxX, float minY, float maxY);

    bool HaveRequestedNodesBeenLoaded();
    /*
    * @addr 0x44DE00
    * @brief Request all paths in a radius of 350 units from the point to be loaded
    */
    void LoadSceneForPathNodes(CVector point);
    /*!
    * @addr 0x450DE0
    * @return If there's a water node on the map for vehicles in the given radius
    */
    bool IsWaterNodeNearby(CVector position, float radius);
    void StartNewInterior(int interiorNum);
    CNodeAddress AddNodeToNewInterior(float x, float y, float z, bool bDontWander, int8 con0, int8 con1, int8 con2, int8 con3, int8 con4, int8 con5);
    void AddInteriorLink(int unkn1, int unkn2);

    /*!
    * @addr 0x44DF30
    */
    void AddInteriorLinkToExternalNode(int32 interiorNodeIdx, CNodeAddress externalNodeAddr);
    void RemoveInteriorLinks(int unkn);
    CNodeAddress FindNearestExteriorNodeToInteriorNode(int interiorId);
    void AddDynamicLinkBetween2Nodes_For1Node(CNodeAddress node1, CNodeAddress node2);
    void AddDynamicLinkBetween2Nodes(CNodeAddress node1, CNodeAddress node2);
    void CompleteNewInterior(CNodeAddress* outAddress);
    void RemoveInterior(uint32 interior);
    CNodeAddress ReturnInteriorNodeIndex(int32 unkn, CNodeAddress addressToFind, int16 nodeId);
    CCarPathLinkAddress FindLinkBetweenNodes(CNodeAddress node1, CNodeAddress node2);
    CVector FindParkingNodeInArea(float minX, float maxX, float minY, float maxY, float minZ, float maxZ);
    bool Load();
    bool Save();

    CPathNode* GetPathNode(CNodeAddress address);

    inline CCarPathLink& GetCarPathLink(const CCarPathLinkAddress& address) {
        assert(address.m_wAreaId < NUM_PATH_MAP_AREAS + NUM_PATH_INTERIOR_AREAS);
        return m_pNaviNodes[address.m_wAreaId][address.m_wCarPathLinkId];
    }

    /*!
    * @addr 0x44D830
    * @brief Find the AreaId in which the given coords are
    */
    size_t FindRegionForCoors(CVector2D posn) { // NOTSA: Using a v2d instead of 2 floats here
        const auto [x, y] = FindXYRegionForCoors(posn);
        return GetAreaIdFromXY(x, y);
    }

    /*!
    * @addr 0x44D890
    * @brief Find the X region of an X axis coord
    */
    size_t FindXRegionForCoors(float x) const;

    /*!
    * @addr 0x44D8C0
    * @brief Find the Y region of a Y axis coord
    */
    size_t FindYRegionForCoors(float y) const;

    /*!
    * @notsa
    * @brief Return a pair of X, Y coords for a coordinate. The actual AreaId can be obtained using `GetAreaIdFromXY` (Or by using `FindRegionForCoors` directly)
    */
    std::pair<size_t, size_t> FindXYRegionForCoors(CVector2D coors) const {
        return { FindXRegionForCoors(coors.x), FindYRegionForCoors(coors.y) };
    }

    float FindXCoorsForRegion(uint32 regionX);
    float FindYCoorsForRegion(uint32 regionY);

    /*!
    * @notsa
    *
    * @return A span of the specified path nodes in the area, or an empty one if the area is not loaded (or it has no nodes of the specified type)
    *
    * Code based on 0x44FD6E
    */
    std::span<CPathNode> GetPathNodesInArea(size_t areaId, ePathType ptype = PATH_TYPE_ALL) const;

    /*!
    * @notsa
    * 
    * @return Whenever the area is loaded
    */
    bool IsAreaLoaded(size_t areaId) const { return m_pPathNodes[areaId] != nullptr; }

    /*!
    * @notsa
    * 
    * @param x The X (column) of the area 
    * @param y The Y (row) of the area
    */
    static constexpr size_t GetAreaIdFromXY(size_t x, size_t y) {
        assert(x < NUM_PATH_MAP_AREA_X && y < NUM_PATH_MAP_AREA_Y);
        return y * NUM_PATH_MAP_AREA_Y + x;
    }

    /*!
    * @addr 0x420AA0
    * 
    * @brief Check if the node's area is loaded
    * @param node Must have a valid area
    */
    bool IsAreaNodesAvailable(CNodeAddress node) const { return IsAreaLoaded(node.m_wAreaId); }

    bool FindNodeCoorsForScript(CVector& outPos, CNodeAddress addr);

    /*!
    * @notsa
    * 
    * @return The intersection info (if any) of 2 nodes or null if either node's area isn't loaded or if there's no intersection
    */
    auto FindIntersection(const CNodeAddress& startNodeAddress, const CNodeAddress& targetNodeAddress) -> CPathIntersectionInfo*;

    /*!
    * @notsa
    * 
    * @brief Check if all node's areas in the list are loaded
    */
    bool AreNodeAreasLoaded(const std::initializer_list<CNodeAddress>& addrs) const;

    /*!
    * @notsa
    * 
    * @brief Call function `fn` with each area ID touching the specified rect.
    * 
    * @param rect The rectangle
    * @param fn   The function to be called with each area's ID. If it returns `false` iteration is stopped and `false` is returned from this function, continues iteration otherwise.
    * 
    * @return If `fn` returned `false` at any point then false, otherwise true.
    */
    template<std::predicate<size_t> T>
    bool IterAreasTouchingRect(CRect rect, T&& fn) {
        const auto [minAreaX, minAreaY] = FindXYRegionForCoors({ rect.left, rect.bottom });
        const auto [maxAreaX, maxAreaY] = FindXYRegionForCoors({ rect.right, rect.top });
        for (auto x = minAreaX; x <= maxAreaX; x++) {
            for (auto y = minAreaY; y <= maxAreaY; y++) {
                if (!std::invoke(fn, GetAreaIdFromXY(x, y))) {
                    return false;
                }
            }
        }
        return true;
    }
};

VALIDATE_SIZE(CPathFind, 0x3C80);

extern CPathFind& ThePaths;
