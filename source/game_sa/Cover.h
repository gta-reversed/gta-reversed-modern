/*
    Plugin-SDK (Grand Theft Auto San Andreas) file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Vector.h"

class CEntity;
class CPtrListDoubleLink;
class CCoverPoint;
class CColTriangle;
class CBuilding;
class CPed;

class CCover {
public:
    static uint32& m_NumPoints;
    static CCoverPoint (&m_aPoints)[100]; // static CCoverPoint m_aPoints[100]
    static CPtrListDoubleLink& m_ListOfProcessedBuildings;

public:
    static void InjectHooks();

    static void AddCoverPoint(int32 maxPeds, CEntity* coverEntity, CVector* position, char coverType, uint8 direction);
    static float CalculateHorizontalSize(CColTriangle* triangle, CVector* vertPositions);
    static char DoLineCheckWithinObject(CColTriangle* triangle, int32 a2, CVector* a3, CVector* a4, CVector a5, CVector a6);
    static bool DoesCoverPointStillProvideCover(CCoverPoint* point, CVector position);
    static void Find2HighestPoints(CColTriangle* triangle, CVector* vertPositions, int32& outPoint1, int32& outPoint2);
    static CCoverPoint* FindAndReserveCoverPoint(CPed* ped, CVector& position, bool a3);
    static bool FindCoordinatesCoverPoint(CCoverPoint* point, CPed* ped, CVector& position, CVector& outCoordinates);
    static void FindCoverPointsForThisBuilding(CBuilding* building);
    static uint8 FindDirFromVector(float x, float y);
    static CVector FindVectorFromDir(uint8 direction);
    static CVector FindVectorFromFirstToMissingVertex(CColTriangle* triangle, int32* a3, CVector* vertPositions);

    static void Init();
    static void RemoveCoverPointIfEntityLost(CCoverPoint* point);
    static void RemoveCoverPointsForThisEntity(CEntity* entity);
    static bool ShouldThisBuildingHaveItsCoverPointsCreated(CBuilding* building);
    static void Update();
};
