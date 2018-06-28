/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CColModel.h"
#include "CColPoint.h"
#include "CStoredCollPoly.h"

class CEntity;
class CVehicle;
class CColCacheEntry;

class CCollision {
public:
    // dummy function
    static void Update();
    static void SortOutCollisionAfterLoad();
    static bool TestSphereSphere(CColSphere const& sphere1, CColSphere const& sphere2);
    static bool TestSphereBox(CSphere const& sphere, CBox const& box);
    static bool ProcessSphereBox(CColSphere const& sphere, CColBox const& box, CColPoint& colPoint, float& maxTouchDistance);
    static bool PointInTriangle(CVector const& point, CVector const* triPoints);
    static float DistToLineSqr(CVector const* lineStart, CVector const* lineEnd, CVector const* point);
    static float DistToMathematicalLine(CVector const* lineStart, CVector const* lineEnd, CVector const* point);
    static float DistToMathematicalLine2D(float lineStartX, float lineStartY, float lineEndX, float lineEndY, float pointX, float pointY);
    static float DistAlongLine2D(float lineX, float lineY, float lineDirX, float lineDirY, float pointX, float pointY);
    static bool ProcessLineSphere(CColLine const& line, CColSphere const& sphere, CColPoint& colPoint, float& depth);
    static bool TestLineBox_DW(CColLine const& line, CBox const& box);
    static bool TestLineBox(CColLine const& line, CBox const& box);
    static bool TestVerticalLineBox(CColLine const& line, CBox const& box);
    static bool ProcessLineBox(CColLine const& line, CColBox const& box, CColPoint& colPoint, float& maxTouchDistance);
    static bool Test2DLineAgainst2DLine(float line1StartX, float line1StartY, float line1EndX, float line1EndY, float line2StartX, float line2StartY, float line2EndX, float line2EndY);
    static bool TestLineTriangle(CColLine const& line, CompressedVector const* verts, CColTriangle const& tri, CColTrianglePlane const& triPlane);
    static bool ProcessLineTriangle(CColLine const& line, CompressedVector const* verts, CColTriangle const& tri, CColTrianglePlane const& triPlane, CColPoint& colPoint, float& maxTouchDistance, CStoredCollPoly* collPoly);
    static bool ProcessVerticalLineTriangle(CColLine const& line, CompressedVector const* verts, CColTriangle const& tri, CColTrianglePlane const& triPlane, CColPoint& colPoint, float& maxTouchDistance, CStoredCollPoly* collPoly);
    static bool IsStoredPolyStillValidVerticalLine(CVector const& lineOrigin, float lineDist, CColPoint& colPoint, CStoredCollPoly* collPoly);
    static void GetBoundingBoxFromTwoSpheres(CColBox* bbox, CColSphere* sphere1, CColSphere* sphere2);
    static bool IsThisVehicleSittingOnMe(CVehicle* vehicle, CVehicle* vehicleOnMe);
    static bool CheckCameraCollisionPeds(int sectorX, int sectorY, CVector* pos, CVector* dir, float* arg4);
    static bool CheckPeds(CVector* pos, CVector* dir, float* arg2);
    static bool SphereCastVsBBox(CColSphere* sphere1, CColSphere* sphere2, CColBox* box);
    static bool RayPolyPOP(CVector* arg0, CVector* arg1, CColTriangle* arg2, CVector* arg3, CVector* arg4);
    static int GetPrincipleAxis(CVector* vec);
    static bool PointInPoly(CVector* point, CColTriangle* tri, CVector* arg2, CVector* triVerts);
    static void Closest3(CVector* arg0, CVector* arg1);
    static bool SphereCastVersusVsPoly(CColSphere* sphere1, CColSphere* sphere2, CColTriangle* tri, CColTrianglePlane* triPlane, CompressedVector* verts);
    static void Init();
    static void Shutdown();
    static void CalculateTrianglePlanes(CCollisionData* colData);
    static void RemoveTrianglePlanes(CCollisionData* colData);
    static bool ProcessSphereSphere(CColSphere const& sphere1, CColSphere const& sphere2, CColPoint& colPoint, float& maxTouchDistance);
    static bool TestSphereTriangle(CColSphere const& sphere, CompressedVector const* verts, CColTriangle const& tri, CColTrianglePlane const& triPlane);
    static bool ProcessSphereTriangle(CColSphere const& sphere, CompressedVector const* verts, CColTriangle const& tri, CColTrianglePlane const& triPlane, CColPoint& colPoint, float& maxTouchDistance);
    static bool TestLineSphere(CColLine const& line, CColSphere const& sphere);
    static float DistToLine(CVector const* lineStart, CVector const* lineEnd, CVector const* point);
    static bool TestLineOfSight(CColLine const& line, CMatrix const& transform, CColModel& colModel, bool doSeeThroughCheck, bool doShootThroughCheck);
    static bool ProcessLineOfSight(CColLine const& line, CMatrix const& transform, CColModel& colModel, CColPoint& colPoint, float& maxTouchDistance, bool doSeeThroughCheck, bool doShootThroughCheck);
    static bool ProcessVerticalLine(CColLine const& line, CMatrix const& transform, CColModel& colModel, CColPoint& colPoint, float& maxTouchDistance, bool doSeeThroughCheck, bool doShootThroughCheck, CStoredCollPoly* collPoly);
    static bool SphereCastVsSphere(CColSphere* arg0, CColSphere* arg1, CColSphere* arg2);
    static void ClosestPointOnLine(CVector* arg0, CVector* arg1, CVector* arg2, CVector* arg3);
    static void ClosestPointsOnPoly(CColTriangle* arg0, CVector* arg1, CVector* arg2, CVector* arg3);
    static void ClosestPointOnPoly(CColTriangle* arg0, CVector* arg1, CVector* arg2);
    static bool SphereCastVsCaches(CColSphere* sphere, CVector* arg1, int arg2, CColCacheEntry* arg3, int* arg4, CColCacheEntry* arg5);
    static void CalculateTrianglePlanes(CColModel* colModel);
    static void RemoveTrianglePlanes(CColModel* colModel);
    // returns number of resulting collision points
    static int ProcessColModels(CMatrix const& transform1, CColModel& colModel1, CMatrix const& transform2, CColModel& colModel2, CColPoint* colPoint1, CColPoint* colPoint2, float* maxTouchDistance, bool arg7);
    static bool SphereCastVsEntity(CColSphere* sphere1, CColSphere* sphere2, CEntity* entity);
    static bool SphereVsEntity(CColSphere* sphere, CEntity* entity);
    static bool CheckCameraCollisionBuildings(int sectorX, int sectorY, CColBox* arg2, CColSphere* arg3, CColSphere* arg4, CColSphere* arg5);
    static bool CheckCameraCollisionVehicles(int sectorX, int sectorY, CColBox* arg2, CColSphere* arg3, CColSphere* arg4, CColSphere* arg5, CVector* arg6);
    static bool CheckCameraCollisionObjects(int sectorX, int sectorY, CColBox* arg2, CColSphere* arg3, CColSphere* arg4, CColSphere* arg5);
    static bool BuildCacheOfCameraCollision(CColSphere* sphere1, CColSphere* sphere2);
    static bool CameraConeCastVsWorldCollision(CColSphere* sphere1, CColSphere* sphere2, float* arg2, float arg3);
};

void CalculateColPointInsideBox(CBox const& box, CVector const& point, CColPoint& colPoint);
bool ProcessDiscCollision(CColPoint& colPoint1, CMatrix const& mat, CColDisk const& disk, CColPoint& colPoint2, bool& arg4, float& arg5, CColPoint& colPoint3);
void ResetMadeInvisibleObjects();
float ClosestSquaredDistanceBetweenFiniteLines(CVector* line1Start, CVector* line1End, CVector* line2Start, CVector* line2End, float arg4);