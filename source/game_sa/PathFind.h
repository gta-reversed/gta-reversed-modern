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

#define NUM_PATH_MAP_AREAS 64
#define NUM_PATH_INTERIOR_AREAS 8

enum ePathType {
    PATH_TYPE_CARS = 0,
    PATH_TYPE_BOATS
};

class CForbiddenArea {
public:
    float x1, x2, y1, y2, z1, z2;
    bool  bEnable;
    uint8 type;
    char  _padding[2];
};

VALIDATE_SIZE(CForbiddenArea, 0x1C);

class CCarPathLinkAddress {
public:
    CCarPathLinkAddress() {
        m_wCarPathLinkId = -1;
        m_wAreaId = -1;
    }

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
};

VALIDATE_SIZE(CPathIntersectionInfo, 0x1);

class CCarPathLink {
public:
    struct {
        int16 x;
        int16 y;
    } m_posn;
    CNodeAddress m_address;
    char         m_nDirX;
    char         m_nDirY;
    char         m_nPathNodeWidth;
    uint8        m_nNumLeftLanes : 3;
    uint8        m_nNumRightLanes : 3;
    uint8        m_bTrafficLightDirection : 1; // 1 if the navi node has the same direction as the traffic light and 0 if the navi node points somewhere else
    uint8        unk1 : 1;

    uint16 m_nTrafficLightState : 2; // 1 - North-South, 2 - West-East cycle, enum: eTrafficLightsDirection
    uint16 m_bTrainCrossing : 1;
};

VALIDATE_SIZE(CCarPathLink, 0xE);

class CPathNode {
public:
    void*            ptr;
    void*            ptr2;
    CompressedVector m_posn;
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

    CVector GetNodeCoors();
};

VALIDATE_SIZE(CPathNode, 0x1C);

class CPathFind {
public:
    CNodeAddress           info;
    CPathNode*             m_apNodesSearchLists[512];
    CPathNode*             m_pPathNodes[NUM_PATH_MAP_AREAS + NUM_PATH_INTERIOR_AREAS];
    // Use CPathFind::GetCarPathLink to access
    CCarPathLink*          m_pNaviNodes[NUM_PATH_MAP_AREAS + NUM_PATH_INTERIOR_AREAS];
    CNodeAddress*          m_pNodeLinks[NUM_PATH_MAP_AREAS + NUM_PATH_INTERIOR_AREAS];
    uint8*                 m_pLinkLengths[NUM_PATH_MAP_AREAS + NUM_PATH_INTERIOR_AREAS];
    CPathIntersectionInfo* m_pPathIntersections[NUM_PATH_MAP_AREAS + NUM_PATH_INTERIOR_AREAS];
    CCarPathLinkAddress*   m_pNaviLinks[NUM_PATH_MAP_AREAS];
    void*                  field_EA4[NUM_PATH_MAP_AREAS];
    uint32                 m_dwNumNodes[NUM_PATH_MAP_AREAS + NUM_PATH_INTERIOR_AREAS];
    uint32                 m_dwNumVehicleNodes[NUM_PATH_MAP_AREAS + NUM_PATH_INTERIOR_AREAS];
    uint32                 m_dwNumPedNodes[NUM_PATH_MAP_AREAS + NUM_PATH_INTERIOR_AREAS];
    uint32                 m_dwNumCarPathLinks[NUM_PATH_MAP_AREAS + NUM_PATH_INTERIOR_AREAS];
    uint32                 m_dwNumAddresses[NUM_PATH_MAP_AREAS + NUM_PATH_INTERIOR_AREAS];
    int32                  field_1544[2048];
    uint32                 m_dwTotalNumNodesInSearchList;
    CNodeAddress           char3548[8];
    uint32                 m_dwNumForbiddenAreas;
    CForbiddenArea         m_aForbiddenAreas[64];
    bool                   m_bForbiddenForScriptedCarsEnabled;
    char                   _padding[3];
    float                  m_fForbiddenForScrCarsX1;
    float                  m_fForbiddenForScrCarsX2;
    float                  m_fForbiddenForScrCarsY1;
    float                  m_fForbiddenForScrCarsY2;

public:
    static void InjectHooks();

    void Init();
    void Shutdown();
    bool TestCrossesRoad(CNodeAddress startNodeAddress, CNodeAddress targetNodeAddress);
    bool TestForPedTrafficLight(CNodeAddress startNodeAddress, CNodeAddress targetNodeAddress);
    CVector* TakeWidthIntoAccountForWandering(CVector* outPosition, CNodeAddress nodeAddress, uint16 randomSeed);
    void FindNextNodeWandering(int32 pathType, float x, float y, float z, CNodeAddress* startNodeAddress, CNodeAddress* targetNodeAddress, uint32 dir, int8* outDir);
    void DoPathSearch(uint8 pathType, CVector origin, CNodeAddress originAddr, CVector target, CNodeAddress* pResultNodes, int16* pNodesCount, int32 maxNodesToFind,
                      float* pDistance, float maxSearchDistance, CNodeAddress* targetAddr, float maxUnkLimit, bool oneSideOnly, CNodeAddress forbiddenNodeAddr,
                      bool includeNodesWithoutLinks, bool waterPath);

    void SetLinksBridgeLights(float fXMin, float fXMax, float fYMin, float fYMax, bool bTrainCrossing);

    CPathNode* GetPathNode(CNodeAddress address);
    int32 LoadPathFindData(RwStream* stream, int32 index);
    void UnLoadPathFindData(int32 index);
    int32 LoadSceneForPathNodes(CVector point);
    bool IsWaterNodeNearby(CVector position, float radius);
    static void AllocatePathFindInfoMem();
    static void PreparePathData();
    bool Load();
    bool Save();
    void UpdateStreaming(bool a1);

    // pathLink is the same as the returned pointer(at least on success)
    // pathLink should be a pointer to CNodeAddress on the stack or somewhere, and
    // the result is stored in it
    CNodeAddress* FindNodeClosestToCoors(CNodeAddress* pathLink, float X, float Y, float Z, int32 _nodeType, float maxDistance, uint16 unk2, int32 unk3, uint16 unk4,
                                         uint16 bBoatsOnly, int32 unk6);

    inline CCarPathLink& GetCarPathLink(const CCarPathLinkAddress& address) { return m_pNaviNodes[address.m_wAreaId][address.m_wCarPathLinkId]; }
};

VALIDATE_SIZE(CPathFind, 0x3C80);

extern CPathFind& ThePaths;
