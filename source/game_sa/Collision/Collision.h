/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "ColModel.h"
#include "ColPoint.h"
#include "StoredCollPoly.h"

class CEntity;
class CVehicle;
class CColCacheEntry;

class CCollision {
public:
    static CLinkList<CCollisionData*> &ms_colModelCache;
    static int32& ms_iProcessLineNumCrossings;
    static uint32& ms_collisionInMemory;
    static bool& bCamCollideWithVehicles;
    static bool& bCamCollideWithObjects;
    static bool& bCamCollideWithPeds;
    static float& relVelCamCollisionVehiclesSqr;

public:
    static void InjectHooks();
    static void Tests();

    static void Init();
    static void Shutdown();
    static void Update();
    static void SortOutCollisionAfterLoad();
    static bool TestSphereSphere(const CColSphere& sphere1, const CColSphere& sphere2);
    static bool TestSphereBox(const CSphere& sphere, const CBox& box);
    static bool ProcessSphereBox(const CColSphere& sphere, const CColBox& box, CColPoint& colPoint, float& maxTouchDistance);
    static bool PointInTriangle(const CVector& point, const CVector* triPoints);
    static float DistToLineSqr(const CVector* lineStart, const CVector* lineEnd, const CVector* point);
    static float DistToMathematicalLine(const CVector* lineStart, const CVector* lineEnd, const CVector* point);
    static float DistToMathematicalLine2D(float lineStartX, float lineStartY, float lineEndX, float lineEndY, float pointX, float pointY);
    static float DistAlongLine2D(float lineX, float lineY, float lineDirX, float lineDirY, float pointX, float pointY);
    static bool ProcessLineSphere(const CColLine& line, const CColSphere& sphere, CColPoint& colPoint, float& depth);
    static bool TestLineBox_DW(const CColLine& line, const CBox& box);
    static bool TestLineBox(const CColLine& line, const CBox& box);
    static bool TestVerticalLineBox(const CColLine& line, const CBox& box);
    static bool ProcessLineBox(const CColLine& line, const CColBox& box, CColPoint& colPoint, float& maxTouchDistance);
    static bool Test2DLineAgainst2DLine(float line1StartX, float line1StartY, float line1EndX, float line1EndY, float line2StartX, float line2StartY, float line2EndX, float line2EndY);
    static bool TestLineTriangle(const CColLine& line, const CompressedVector* verts, const CColTriangle& tri, const CColTrianglePlane& triPlane);
    static bool ProcessLineTriangle(const CColLine& line, const CompressedVector* verts, const CColTriangle& tri, const CColTrianglePlane& triPlane, CColPoint& colPoint, float& maxTouchDistance, CStoredCollPoly* collPoly);
    static bool ProcessVerticalLineTriangle(const CColLine& line, const CompressedVector* verts, const CColTriangle& tri, const CColTrianglePlane& triPlane, CColPoint& colPoint, float& maxTouchDistance, CStoredCollPoly* collPoly);
    static bool IsStoredPolyStillValidVerticalLine(const CVector& lineOrigin, float lineDist, CColPoint& colPoint, CStoredCollPoly* collPoly);
    static void GetBoundingBoxFromTwoSpheres(CColBox* bbox, CColSphere* sphere1, CColSphere* sphere2);
    static bool IsThisVehicleSittingOnMe(CVehicle* vehicle, CVehicle* vehicleOnMe);
    static bool CheckCameraCollisionPeds(int32 sectorX, int32 sectorY, CVector* pos, CVector* dir, float* arg4);
    static bool CheckPeds(CVector* pos, CVector* dir, float* arg2);
    static bool SphereCastVsBBox(CColSphere* sphere1, CColSphere* sphere2, CColBox* box);
    static bool RayPolyPOP(CVector* arg0, CVector* arg1, CColTriangle* arg2, CVector* arg3, CVector* arg4);
    static int32 GetPrincipleAxis(CVector* vec);
    static bool PointInPoly(CVector* point, CColTriangle* tri, CVector* arg2, CVector* triVerts);
    static void Closest3(CVector* arg0, CVector* arg1);
    static bool SphereCastVersusVsPoly(CColSphere* sphere1, CColSphere* sphere2, CColTriangle* tri, CColTrianglePlane* triPlane, CompressedVector* verts);
    static void CalculateTrianglePlanes(CCollisionData* colData);
    static void RemoveTrianglePlanes(CCollisionData* colData);
    static bool ProcessSphereSphere(const CColSphere& sphere1, const CColSphere& sphere2, CColPoint& colPoint, float& maxTouchDistance);
    static bool TestSphereTriangle(const CColSphere& sphere, const CompressedVector* verts, const CColTriangle& tri, const CColTrianglePlane& triPlane);
    static bool ProcessSphereTriangle(const CColSphere& sphere, const CompressedVector* verts, const CColTriangle& tri, const CColTrianglePlane& triPlane, CColPoint& colPoint, float& maxTouchDistance);
    static bool TestLineSphere(const CColLine& line, const CColSphere& sphere);
    static float DistToLine(const CVector& lineStart, const CVector& lineEnd, const CVector& point);
    static bool TestLineOfSight(const CColLine& line, const CMatrix& transform, CColModel& colModel, bool doSeeThroughCheck, bool doShootThroughCheck);
    static bool ProcessLineOfSight(const CColLine& line, const CMatrix& transform, CColModel& colModel, CColPoint& colPoint, float& maxTouchDistance, bool doSeeThroughCheck, bool doShootThroughCheck);
    static bool ProcessVerticalLine(const CColLine& line, const CMatrix& transform, CColModel& colModel, CColPoint& colPoint, float& maxTouchDistance, bool doSeeThroughCheck, bool doShootThroughCheck, CStoredCollPoly* collPoly);
    static bool SphereCastVsSphere(CColSphere* arg0, CColSphere* arg1, CColSphere* arg2);
    static void ClosestPointOnLine(CVector* arg0, CVector* arg1, CVector* arg2, CVector* arg3);
    static void ClosestPointsOnPoly(CColTriangle* arg0, CVector* arg1, CVector* arg2, CVector* arg3);
    static void ClosestPointOnPoly(CColTriangle* arg0, CVector* arg1, CVector* arg2);
    static bool SphereCastVsCaches(CColSphere* sphere, CVector* arg1, int32 arg2, CColCacheEntry* arg3, int32* arg4, CColCacheEntry* arg5);
    static void CalculateTrianglePlanes(CColModel* colModel);
    static void RemoveTrianglePlanes(CColModel* colModel);
    // returns number of resulting collision points
    static int32 ProcessColModels(
        const CMatrix& transformA, CColModel& cmA,
        const CMatrix& transformB, CColModel& cmB,
        std::array<CColPoint, 32>& sphereCPs,
        CColPoint* lineCPs,
        float* maxTouchDistances,
        bool arg7
    );
    static bool SphereCastVsEntity(CColSphere* sphere1, CColSphere* sphere2, CEntity* entity);
    static bool SphereVsEntity(CColSphere* sphere, CEntity* entity);
    static bool CheckCameraCollisionBuildings(int32 sectorX, int32 sectorY, CColBox* arg2, CColSphere* arg3, CColSphere* arg4, CColSphere* arg5);
    static bool CheckCameraCollisionVehicles(int32 sectorX, int32 sectorY, CColBox* arg2, CColSphere* arg3, CColSphere* arg4, CColSphere* arg5, CVector* arg6);
    static bool CheckCameraCollisionObjects(int32 sectorX, int32 sectorY, CColBox* arg2, CColSphere* arg3, CColSphere* arg4, CColSphere* arg5);
    static bool BuildCacheOfCameraCollision(CColSphere* sphere1, CColSphere* sphere2);
    static bool CameraConeCastVsWorldCollision(const CColSphere& spA, const CColSphere& spB, float* outDist, float minDist);
};

void CalculateColPointInsideBox(const CBox& box, const CVector& point, CColPoint& colPoint);
bool ProcessDiscCollision(CColPoint& colPoint1, const CMatrix& mat, const CColDisk& disk, CColPoint& colPoint2, bool& arg4, float& arg5, CColPoint& colPoint3);
void ResetMadeInvisibleObjects();
float ClosestSquaredDistanceBetweenFiniteLines(CVector* line1Start, CVector* line1End, CVector* line2Start, CVector* line2End, float arg4);
