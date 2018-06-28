/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CEntity.h"
#include "CVector.h"
#include "CColTriangle.h"
#include "CCoverPoint.h"
#include "CBuilding.h"
#include "CPtrListDoubleLink.h"

class CPed;

class  CCover {
public:
     static unsigned int &m_NumPoints;
     static CCoverPoint(&m_aPoints)[100]; // static CCoverPoint m_aPoints[100]
     static CPtrListDoubleLink &m_ListOfProcessedBuildings;

     static void AddCoverPoint(int maxPeds, CEntity *coverEntity, CVector *position, char coverType, unsigned char direction);
     static float CalculateHorizontalSize(CColTriangle *triangle, CVector *vertPositions);
     static char DoLineCheckWithinObject(CColTriangle *triangle, int a2, CVector *a3, CVector *a4, CVector a5, CVector a6);
     static bool DoesCoverPointStillProvideCover(CCoverPoint *point, CVector position);
     static void Find2HighestPoints(CColTriangle *triangle, CVector *vertPositions, int &outPoint1, int &outPoint2);
     static CCoverPoint *FindAndReserveCoverPoint(CPed *ped, CVector &position, bool a3);
     static bool FindCoordinatesCoverPoint(CCoverPoint *point, CPed *ped, CVector &position, CVector &outCoordinates);
     static void FindCoverPointsForThisBuilding(CBuilding *building);
     static unsigned char FindDirFromVector(float x, float y);
     static CVector FindVectorFromDir(unsigned char direction);
     static CVector FindVectorFromFirstToMissingVertex(CColTriangle *triangle, int *a3, CVector *vertPositions);
     static void Init();
     static void RemoveCoverPointIfEntityLost(CCoverPoint *point);
     static void RemoveCoverPointsForThisEntity(CEntity *entity);
     static bool ShouldThisBuildingHaveItsCoverPointsCreated(CBuilding *building);
     static void Update();
};

//#include "meta/meta.CCover.h"
