/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

CLinkList<CCollisionData*>& CCollision::ms_colModelCache = *(CLinkList<CCollisionData*>*)0x96592C;

void CCollision::InjectHooks()
{
    ReversibleHooks::Install("CCollision", "CalculateTrianglePlanes_colData", 0x416330, static_cast<void(*)(CCollisionData*)>(&CCollision::CalculateTrianglePlanes));
    ReversibleHooks::Install("CCollision", "RemoveTrianglePlanes_colData", 0x416400, static_cast<void(*)(CCollisionData*)>(&CCollision::RemoveTrianglePlanes));
}

// Converted from cdecl void CCollision::Update(void) 0x411E20
void CCollision::Update() {
    plugin::Call<0x411E20>();
}

// Converted from cdecl void CCollision::SortOutCollisionAfterLoad(void) 0x411E30
void CCollision::SortOutCollisionAfterLoad() {
    plugin::Call<0x411E30>();
}

// Converted from cdecl bool CCollision::TestSphereSphere(CColSphere const&sphere1,CColSphere const&sphere2) 0x411E70
bool CCollision::TestSphereSphere(CColSphere const& sphere1, CColSphere const& sphere2) {
    return plugin::CallAndReturn<bool, 0x411E70, CColSphere const&, CColSphere const&>(sphere1, sphere2);
}

// Converted from cdecl void CalculateColPointInsideBox(CBox const&box,CVector const&point,CColPoint &colPoint) 0x411EC0
void CalculateColPointInsideBox(CBox const& box, CVector const& point, CColPoint& colPoint) {
    plugin::Call<0x411EC0, CBox const&, CVector const&, CColPoint&>(box, point, colPoint);
}

// Converted from cdecl bool CCollision::TestSphereBox(CSphere const&sphere,CBox const&box) 0x4120C0
bool CCollision::TestSphereBox(CSphere const& sphere, CBox const& box) {
    return plugin::CallAndReturn<bool, 0x4120C0, CSphere const&, CBox const&>(sphere, box);
}

// Converted from cdecl bool CCollision::ProcessSphereBox(CColSphere const&sphere,CColBox const&box,CColPoint &colPoint,float &maxTouchDistance) 0x412130
bool CCollision::ProcessSphereBox(CColSphere const& sphere, CColBox const& box, CColPoint& colPoint, float& maxTouchDistance) {
    return plugin::CallAndReturn<bool, 0x412130, CColSphere const&, CColBox const&, CColPoint&, float&>(sphere, box, colPoint, maxTouchDistance);
}

// Converted from cdecl bool CCollision::PointInTriangle(CVector const&point,CVector const*triPoints) 0x412700
bool CCollision::PointInTriangle(CVector const& point, CVector const* triPoints) {
    return plugin::CallAndReturn<bool, 0x412700, CVector const&, CVector const*>(point, triPoints);
}

// Converted from cdecl float CCollision::DistToLineSqr(CVector const*lineStart,CVector const*lineEnd,CVector const*point) 0x412850
float CCollision::DistToLineSqr(CVector const* lineStart, CVector const* lineEnd, CVector const* point) {
    return plugin::CallAndReturn<float, 0x412850, CVector const*, CVector const*, CVector const*>(lineStart, lineEnd, point);
}

// Converted from cdecl float CCollision::DistToMathematicalLine(CVector const*lineStart,CVector const*lineEnd,CVector const*point) 0x412970
float CCollision::DistToMathematicalLine(CVector const* lineStart, CVector const* lineEnd, CVector const* point) {
    return plugin::CallAndReturn<float, 0x412970, CVector const*, CVector const*, CVector const*>(lineStart, lineEnd, point);
}

// Converted from cdecl float CCollision::DistToMathematicalLine2D(float lineStartX,float lineStartY,float lineEndX,float lineEndY,float pointX,float pointY) 0x412A30
float CCollision::DistToMathematicalLine2D(float lineStartX, float lineStartY, float lineEndX, float lineEndY, float pointX, float pointY) {
    return plugin::CallAndReturn<float, 0x412A30, float, float, float, float, float, float>(lineStartX, lineStartY, lineEndX, lineEndY, pointX, pointY);
}

// Converted from cdecl float CCollision::DistAlongLine2D(float lineX,float lineY,float lineDirX,float lineDirY,float pointX,float pointY) 0x412A80
float CCollision::DistAlongLine2D(float lineX, float lineY, float lineDirX, float lineDirY, float pointX, float pointY) {
    return plugin::CallAndReturn<float, 0x412A80, float, float, float, float, float, float>(lineX, lineY, lineDirX, lineDirY, pointX, pointY);
}

// Converted from cdecl bool CCollision::ProcessLineSphere(CColLine const&line,CColSphere const&sphere,CColPoint &colPoint,float &depth) 0x412AA0
bool CCollision::ProcessLineSphere(CColLine const& line, CColSphere const& sphere, CColPoint& colPoint, float& depth) {
    return plugin::CallAndReturn<bool, 0x412AA0, CColLine const&, CColSphere const&, CColPoint&, float&>(line, sphere, colPoint, depth);
}

// Converted from cdecl bool CCollision::TestLineBox_DW(CColLine const&line,CBox const&box) 0x412C70
bool CCollision::TestLineBox_DW(CColLine const& line, CBox const& box) {
    return plugin::CallAndReturn<bool, 0x412C70, CColLine const&, CBox const&>(line, box);
}

// Converted from cdecl bool CCollision::TestLineBox(CColLine const&line,CBox const&box) 0x413070
bool CCollision::TestLineBox(CColLine const& line, CBox const& box) {
    return plugin::CallAndReturn<bool, 0x413070, CColLine const&, CBox const&>(line, box);
}

// Converted from cdecl bool CCollision::TestVerticalLineBox(CColLine const&line,CBox const&box) 0x413080
bool CCollision::TestVerticalLineBox(CColLine const& line, CBox const& box) {
    return plugin::CallAndReturn<bool, 0x413080, CColLine const&, CBox const&>(line, box);
}

// Converted from cdecl bool CCollision::ProcessLineBox(CColLine const&line,CColBox const&box,CColPoint &colPoint,float &maxTouchDistance) 0x413100
bool CCollision::ProcessLineBox(CColLine const& line, CColBox const& box, CColPoint& colPoint, float& maxTouchDistance) {
    return plugin::CallAndReturn<bool, 0x413100, CColLine const&, CColBox const&, CColPoint&, float&>(line, box, colPoint, maxTouchDistance);
}

// Converted from cdecl bool CCollision::Test2DLineAgainst2DLine(float line1StartX,float line1StartY,float line1EndX,float line1EndY,float line2StartX,float line2StartY,float line2EndX,float line2EndY) 0x4138D0
bool CCollision::Test2DLineAgainst2DLine(float line1StartX, float line1StartY, float line1EndX, float line1EndY, float line2StartX, float line2StartY, float line2EndX, float line2EndY) {
    return plugin::CallAndReturn<bool, 0x4138D0, float, float, float, float, float, float, float, float>(line1StartX, line1StartY, line1EndX, line1EndY, line2StartX, line2StartY, line2EndX, line2EndY);
}

// Converted from cdecl bool ProcessDiscCollision(CColPoint &colPoint1,CMatrix const&mat,CColDisk const&disk,CColPoint &colPoint2,bool &,float &,CColPoint &colPoint3) 0x413960
bool ProcessDiscCollision(CColPoint& colPoint1, CMatrix const& mat, CColDisk const& disk, CColPoint& colPoint2, bool& arg4, float& arg5, CColPoint& colPoint3) {
    return plugin::CallAndReturn<bool, 0x413960, CColPoint&, CMatrix const&, CColDisk const&, CColPoint&, bool&, float&, CColPoint&>(colPoint1, mat, disk, colPoint2, arg4, arg5, colPoint3);
}

// Converted from cdecl bool CCollision::TestLineTriangle(CColLine const&line,CompressedVector const*verts,CColTriangle const&tri,CColTrianglePlane const&triPlane) 0x413AC0
bool CCollision::TestLineTriangle(CColLine const& line, CompressedVector const* verts, CColTriangle const& tri, CColTrianglePlane const& triPlane) {
    return plugin::CallAndReturn<bool, 0x413AC0, CColLine const&, CompressedVector const*, CColTriangle const&, CColTrianglePlane const&>(line, verts, tri, triPlane);
}

// Converted from cdecl bool CCollision::ProcessLineTriangle(CColLine const&line,CompressedVector const*verts,CColTriangle const&tri,CColTrianglePlane const&triPlane,CColPoint &colPoint,float &maxTouchDistance,CStoredCollPoly *collPoly) 0x4140F0
bool CCollision::ProcessLineTriangle(CColLine const& line, CompressedVector const* verts, CColTriangle const& tri, CColTrianglePlane const& triPlane, CColPoint& colPoint, float& maxTouchDistance, CStoredCollPoly* collPoly) {
    return plugin::CallAndReturn<bool, 0x4140F0, CColLine const&, CompressedVector const*, CColTriangle const&, CColTrianglePlane const&, CColPoint&, float&, CStoredCollPoly*>(line, verts, tri, triPlane, colPoint, maxTouchDistance, collPoly);
}

// Converted from cdecl bool CCollision::ProcessVerticalLineTriangle(CColLine const&line,CompressedVector const*verts,CColTriangle const&tri,CColTrianglePlane const&triPlane,CColPoint &colPoint,float &maxTouchDistance,CStoredCollPoly *collPoly) 0x4147E0
bool CCollision::ProcessVerticalLineTriangle(CColLine const& line, CompressedVector const* verts, CColTriangle const& tri, CColTrianglePlane const& triPlane, CColPoint& colPoint, float& maxTouchDistance, CStoredCollPoly* collPoly) {
    return plugin::CallAndReturn<bool, 0x4147E0, CColLine const&, CompressedVector const*, CColTriangle const&, CColTrianglePlane const&, CColPoint&, float&, CStoredCollPoly*>(line, verts, tri, triPlane, colPoint, maxTouchDistance, collPoly);
}

// Converted from cdecl bool CCollision::IsStoredPolyStillValidVerticalLine(CVector const&lineOrigin,float lineDist,CColPoint &colPoint,CStoredCollPoly *collPoly) 0x414D70
bool CCollision::IsStoredPolyStillValidVerticalLine(CVector const& lineOrigin, float lineDist, CColPoint& colPoint, CStoredCollPoly* collPoly) {
    return plugin::CallAndReturn<bool, 0x414D70, CVector const&, float, CColPoint&, CStoredCollPoly*>(lineOrigin, lineDist, colPoint, collPoly);
}

// Converted from cdecl void CCollision::GetBoundingBoxFromTwoSpheres(CColBox *bbox,CColSphere *sphere1,CColSphere *sphere2) 0x415230
void CCollision::GetBoundingBoxFromTwoSpheres(CColBox* bbox, CColSphere* sphere1, CColSphere* sphere2) {
    plugin::Call<0x415230, CColBox*, CColSphere*, CColSphere*>(bbox, sphere1, sphere2);
}

// Converted from cdecl bool CCollision::IsThisVehicleSittingOnMe(CVehicle *vehicle,CVehicle *vehicleOnMe) 0x4152C0
bool CCollision::IsThisVehicleSittingOnMe(CVehicle* vehicle, CVehicle* vehicleOnMe) {
    return plugin::CallAndReturn<bool, 0x4152C0, CVehicle*, CVehicle*>(vehicle, vehicleOnMe);
}

// Converted from cdecl bool CCollision::CheckCameraCollisionPeds(int sectorX,int sectorY,CVector *pos,CVector *dir,float *) 0x415320
bool CCollision::CheckCameraCollisionPeds(int sectorX, int sectorY, CVector* pos, CVector* dir, float* arg4) {
    return plugin::CallAndReturn<bool, 0x415320, int, int, CVector*, CVector*, float*>(sectorX, sectorY, pos, dir, arg4);
}

// Converted from cdecl bool CCollision::CheckPeds(CVector *pos,CVector *dir,float *) 0x4154A0
bool CCollision::CheckPeds(CVector* pos, CVector* dir, float* arg2) {
    return plugin::CallAndReturn<bool, 0x4154A0, CVector*, CVector*, float*>(pos, dir, arg2);
}

// Converted from cdecl void ResetMadeInvisibleObjects(void) 0x415540
void ResetMadeInvisibleObjects() {
    plugin::Call<0x415540>();
}

// Converted from cdecl bool CCollision::SphereCastVsBBox(CColSphere *sphere1,CColSphere *sphere2,CColBox *box) 0x415590
bool CCollision::SphereCastVsBBox(CColSphere* sphere1, CColSphere* sphere2, CColBox* box) {
    return plugin::CallAndReturn<bool, 0x415590, CColSphere*, CColSphere*, CColBox*>(sphere1, sphere2, box);
}

// Converted from cdecl bool CCollision::RayPolyPOP(CVector *,CVector *,CColTriangle *,CVector *,CVector *) 0x415620
bool CCollision::RayPolyPOP(CVector* arg0, CVector* arg1, CColTriangle* arg2, CVector* arg3, CVector* arg4) {
    return plugin::CallAndReturn<bool, 0x415620, CVector*, CVector*, CColTriangle*, CVector*, CVector*>(arg0, arg1, arg2, arg3, arg4);
}

// Converted from cdecl int CCollision::GetPrincipleAxis(CVector *vec) 0x4156D0
int CCollision::GetPrincipleAxis(CVector* vec) {
    return plugin::CallAndReturn<int, 0x4156D0, CVector*>(vec);
}

// Converted from cdecl bool CCollision::PointInPoly(CVector *point,CColTriangle *tri,CVector *,CVector *triVerts) 0x415730
bool CCollision::PointInPoly(CVector* point, CColTriangle* tri, CVector* arg2, CVector* triVerts) {
    return plugin::CallAndReturn<bool, 0x415730, CVector*, CColTriangle*, CVector*, CVector*>(point, tri, arg2, triVerts);
}

// Converted from cdecl void CCollision::Closest3(CVector *,CVector *) 0x415950
void CCollision::Closest3(CVector* arg0, CVector* arg1) {
    plugin::Call<0x415950, CVector*, CVector*>(arg0, arg1);
}

// Converted from cdecl float ClosestSquaredDistanceBetweenFiniteLines(CVector *line1Start,CVector *line1End,CVector *line2Start,CVector *line2End,float) 0x415A40
float ClosestSquaredDistanceBetweenFiniteLines(CVector* line1Start, CVector* line1End, CVector* line2Start, CVector* line2End, float arg4) {
    return plugin::CallAndReturn<float, 0x415A40, CVector*, CVector*, CVector*, CVector*, float>(line1Start, line1End, line2Start, line2End, arg4);
}

// Converted from cdecl bool CCollision::SphereCastVersusVsPoly(CColSphere *sphere1,CColSphere *sphere2,CColTriangle *tri,CColTrianglePlane *triPlane,CompressedVector *verts) 0x415CF0
bool CCollision::SphereCastVersusVsPoly(CColSphere* sphere1, CColSphere* sphere2, CColTriangle* tri, CColTrianglePlane* triPlane, CompressedVector* verts) {
    return plugin::CallAndReturn<bool, 0x415CF0, CColSphere*, CColSphere*, CColTriangle*, CColTrianglePlane*, CompressedVector*>(sphere1, sphere2, tri, triPlane, verts);
}

// Converted from cdecl void CCollision::Init(void) 0x416260
void CCollision::Init() {
    plugin::Call<0x416260>();
}

// Converted from cdecl void CCollision::Shutdown(void) 0x4162E0
void CCollision::Shutdown() {
    plugin::Call<0x4162E0>();
}

// Converted from cdecl void CCollision::CalculateTrianglePlanes(CCollisionData *colData) 0x416330
void CCollision::CalculateTrianglePlanes(CCollisionData* colData) {
    if (!colData->m_nNumTriangles)
        return;

    if (colData->m_pTrianglePlanes)
    {
        auto* pLink = colData->GetLinkPtr();
        pLink->Remove();
        CCollision::ms_colModelCache.usedListHead.Insert(pLink);
    }
    else
    {
        auto* pLink = CCollision::ms_colModelCache.Insert(colData);
        if (!pLink)
        {
            auto* pToRemove = CCollision::ms_colModelCache.usedListTail.prev;
            pToRemove->data->RemoveTrianglePlanes();
            CCollision::ms_colModelCache.Remove(pToRemove);
            pLink = CCollision::ms_colModelCache.Insert(colData);
        }

        colData->CalculateTrianglePlanes();
        colData->SetLinkPtr(pLink);
    }
}

// Converted from cdecl void CCollision::RemoveTrianglePlanes(CCollisionData *colData) 0x416400
void CCollision::RemoveTrianglePlanes(CCollisionData* colData) {
    if (!colData->m_pTrianglePlanes)
        return;

    auto* pLink = colData->GetLinkPtr();
    CCollision::ms_colModelCache.Remove(pLink);
    colData->RemoveTrianglePlanes();
}

// Converted from cdecl bool CCollision::ProcessSphereSphere(CColSphere const&sphere1,CColSphere const&sphere2,CColPoint &colPoint,float &maxTouchDistance) 0x416450
bool CCollision::ProcessSphereSphere(CColSphere const& sphere1, CColSphere const& sphere2, CColPoint& colPoint, float& maxTouchDistance) {
    return plugin::CallAndReturn<bool, 0x416450, CColSphere const&, CColSphere const&, CColPoint&, float&>(sphere1, sphere2, colPoint, maxTouchDistance);
}

// Converted from cdecl bool CCollision::TestSphereTriangle(CColSphere const&sphere,CompressedVector const*verts,CColTriangle const&tri,CColTrianglePlane const&triPlane) 0x4165B0
bool CCollision::TestSphereTriangle(CColSphere const& sphere, CompressedVector const* verts, CColTriangle const& tri, CColTrianglePlane const& triPlane) {
    return plugin::CallAndReturn<bool, 0x4165B0, CColSphere const&, CompressedVector const*, CColTriangle const&, CColTrianglePlane const&>(sphere, verts, tri, triPlane);
}

// Converted from cdecl bool CCollision::ProcessSphereTriangle(CColSphere const&sphere,CompressedVector const*verts,CColTriangle const&tri,CColTrianglePlane const&triPlane,CColPoint &colPoint,float &maxTouchDistance) 0x416BA0
bool CCollision::ProcessSphereTriangle(CColSphere const& sphere, CompressedVector const* verts, CColTriangle const& tri, CColTrianglePlane const& triPlane, CColPoint& colPoint, float& maxTouchDistance) {
    return plugin::CallAndReturn<bool, 0x416BA0, CColSphere const&, CompressedVector const*, CColTriangle const&, CColTrianglePlane const&, CColPoint&, float&>(sphere, verts, tri, triPlane, colPoint, maxTouchDistance);
}

// Converted from cdecl bool CCollision::TestLineSphere(CColLine const&line,CColSphere const&sphere) 0x417470
bool CCollision::TestLineSphere(CColLine const& line, CColSphere const& sphere) {
    return plugin::CallAndReturn<bool, 0x417470, CColLine const&, CColSphere const&>(line, sphere);
}

// Converted from cdecl float CCollision::DistToLine(CVector const*lineStart,CVector const*lineEnd,CVector const*point) 0x417610
float CCollision::DistToLine(CVector const* lineStart, CVector const* lineEnd, CVector const* point) {
    return plugin::CallAndReturn<float, 0x417610, CVector const*, CVector const*, CVector const*>(lineStart, lineEnd, point);
}

// Converted from cdecl bool CCollision::TestLineOfSight(CColLine const&line,CMatrix const&transform,CColModel &colModel,bool doSeeThroughCheck,bool doShootThroughCheck) 0x417730
bool CCollision::TestLineOfSight(CColLine const& line, CMatrix const& transform, CColModel& colModel, bool doSeeThroughCheck, bool doShootThroughCheck) {
    return plugin::CallAndReturn<bool, 0x417730, CColLine const&, CMatrix const&, CColModel&, bool, bool>(line, transform, colModel, doSeeThroughCheck, doShootThroughCheck);
}

// Converted from cdecl bool CCollision::ProcessLineOfSight(CColLine const&line,CMatrix const&transform,CColModel &colModel,CColPoint &colPoint,float &maxTouchDistance,bool doSeeThroughCheck,bool doShootThroughCheck) 0x417950
bool CCollision::ProcessLineOfSight(CColLine const& line, CMatrix const& transform, CColModel& colModel, CColPoint& colPoint, float& maxTouchDistance, bool doSeeThroughCheck, bool doShootThroughCheck) {
    return plugin::CallAndReturn<bool, 0x417950, CColLine const&, CMatrix const&, CColModel&, CColPoint&, float&, bool, bool>(line, transform, colModel, colPoint, maxTouchDistance, doSeeThroughCheck, doShootThroughCheck);
}

// Converted from cdecl bool CCollision::ProcessVerticalLine(CColLine const&line,CMatrix const&transform,CColModel &colModel,CColPoint &colPoint,float &maxTouchDistance,bool doSeeThroughCheck,bool doShootThroughCheck,CStoredCollPoly *collPoly) 0x417BF0
bool CCollision::ProcessVerticalLine(CColLine const& line, CMatrix const& transform, CColModel& colModel, CColPoint& colPoint, float& maxTouchDistance, bool doSeeThroughCheck, bool doShootThroughCheck, CStoredCollPoly* collPoly) {
    return plugin::CallAndReturn<bool, 0x417BF0, CColLine const&, CMatrix const&, CColModel&, CColPoint&, float&, bool, bool, CStoredCollPoly*>(line, transform, colModel, colPoint, maxTouchDistance, doSeeThroughCheck, doShootThroughCheck, collPoly);
}

// Converted from cdecl bool CCollision::SphereCastVsSphere(CColSphere *,CColSphere *,CColSphere *) 0x417F20
bool CCollision::SphereCastVsSphere(CColSphere* arg0, CColSphere* arg1, CColSphere* arg2) {
    return plugin::CallAndReturn<bool, 0x417F20, CColSphere*, CColSphere*, CColSphere*>(arg0, arg1, arg2);
}

// Converted from cdecl void CCollision::ClosestPointOnLine(CVector *,CVector *,CVector *,CVector *) 0x417FD0
void CCollision::ClosestPointOnLine(CVector* arg0, CVector* arg1, CVector* arg2, CVector* arg3) {
    plugin::Call<0x417FD0, CVector*, CVector*, CVector*, CVector*>(arg0, arg1, arg2, arg3);
}

// Converted from cdecl void CCollision::ClosestPointsOnPoly(CColTriangle *,CVector *,CVector *,CVector *) 0x418100
void CCollision::ClosestPointsOnPoly(CColTriangle* arg0, CVector* arg1, CVector* arg2, CVector* arg3) {
    plugin::Call<0x418100, CColTriangle*, CVector*, CVector*, CVector*>(arg0, arg1, arg2, arg3);
}

// Converted from cdecl void CCollision::ClosestPointOnPoly(CColTriangle *,CVector *,CVector *) 0x418150
void CCollision::ClosestPointOnPoly(CColTriangle* arg0, CVector* arg1, CVector* arg2) {
    plugin::Call<0x418150, CColTriangle*, CVector*, CVector*>(arg0, arg1, arg2);
}

// Converted from cdecl bool CCollision::SphereCastVsCaches(CColSphere *sphere,CVector *,int,CColCacheEntry *,int *,CColCacheEntry *) 0x4181B0
bool CCollision::SphereCastVsCaches(CColSphere* sphere, CVector* arg1, int arg2, CColCacheEntry* arg3, int* arg4, CColCacheEntry* arg5) {
    return plugin::CallAndReturn<bool, 0x4181B0, CColSphere*, CVector*, int, CColCacheEntry*, int*, CColCacheEntry*>(sphere, arg1, arg2, arg3, arg4, arg5);
}

// Converted from cdecl void CCollision::CalculateTrianglePlanes(CColModel *colModel) 0x418580
void CCollision::CalculateTrianglePlanes(CColModel* colModel) {
    plugin::Call<0x418580, CColModel*>(colModel);
}

// Converted from cdecl void CCollision::RemoveTrianglePlanes(CColModel *colModel) 0x4185A0
void CCollision::RemoveTrianglePlanes(CColModel* colModel) {
    plugin::Call<0x4185A0, CColModel*>(colModel);
}

// Converted from cdecl int CCollision::ProcessColModels(CMatrix const&transform1,CColModel &colModel1,CMatrix const&transform2,CColModel &colModel2,CColPoint *colPoint1,CColPoint *colPoint2,float *maxTouchDistance, bool) 0x4185C0
int CCollision::ProcessColModels(CMatrix const& transform1, CColModel& colModel1, CMatrix const& transform2, CColModel& colModel2, CColPoint* colPoint1, CColPoint* colPoint2, float* maxTouchDistance, bool arg7) {
    return plugin::CallAndReturn<int, 0x4185C0, CMatrix const&, CColModel&, CMatrix const&, CColModel&, CColPoint*, CColPoint*, float*, bool>(transform1, colModel1, transform2, colModel2, colPoint1, colPoint2, maxTouchDistance, arg7);
}

// Converted from cdecl bool CCollision::SphereCastVsEntity(CColSphere *sphere1,CColSphere *sphere2,CEntity *entity) 0x419F00
bool CCollision::SphereCastVsEntity(CColSphere* sphere1, CColSphere* sphere2, CEntity* entity) {
    return plugin::CallAndReturn<bool, 0x419F00, CColSphere*, CColSphere*, CEntity*>(sphere1, sphere2, entity);
}

// Converted from cdecl bool CCollision::SphereVsEntity(CColSphere *sphere,CEntity *entity) 0x41A5A0
bool CCollision::SphereVsEntity(CColSphere* sphere, CEntity* entity) {
    return plugin::CallAndReturn<bool, 0x41A5A0, CColSphere*, CEntity*>(sphere, entity);
}

// Converted from cdecl bool CCollision::CheckCameraCollisionBuildings(int sectorX,int sectorY,CColBox *,CColSphere *,CColSphere *,CColSphere *) 0x41A820
bool CCollision::CheckCameraCollisionBuildings(int sectorX, int sectorY, CColBox* arg2, CColSphere* arg3, CColSphere* arg4, CColSphere* arg5) {
    return plugin::CallAndReturn<bool, 0x41A820, int, int, CColBox*, CColSphere*, CColSphere*, CColSphere*>(sectorX, sectorY, arg2, arg3, arg4, arg5);
}

// Converted from cdecl bool CCollision::CheckCameraCollisionVehicles(int sectorX,int sectorY,CColBox *,CColSphere *,CColSphere *,CColSphere *,CVector *) 0x41A990
bool CCollision::CheckCameraCollisionVehicles(int sectorX, int sectorY, CColBox* arg2, CColSphere* arg3, CColSphere* arg4, CColSphere* arg5, CVector* arg6) {
    return plugin::CallAndReturn<bool, 0x41A990, int, int, CColBox*, CColSphere*, CColSphere*, CColSphere*, CVector*>(sectorX, sectorY, arg2, arg3, arg4, arg5, arg6);
}

// Converted from cdecl bool CCollision::CheckCameraCollisionObjects(int sectorX,int sectorY,CColBox *,CColSphere *,CColSphere *,CColSphere *) 0x41AB20
bool CCollision::CheckCameraCollisionObjects(int sectorX, int sectorY, CColBox* arg2, CColSphere* arg3, CColSphere* arg4, CColSphere* arg5) {
    return plugin::CallAndReturn<bool, 0x41AB20, int, int, CColBox*, CColSphere*, CColSphere*, CColSphere*>(sectorX, sectorY, arg2, arg3, arg4, arg5);
}

// Converted from cdecl bool CCollision::BuildCacheOfCameraCollision(CColSphere *sphere1,CColSphere *sphere2) 0x41AC40
bool CCollision::BuildCacheOfCameraCollision(CColSphere* sphere1, CColSphere* sphere2) {
    return plugin::CallAndReturn<bool, 0x41AC40, CColSphere*, CColSphere*>(sphere1, sphere2);
}

// Converted from cdecl bool CCollision::CameraConeCastVsWorldCollision(CColSphere *sphere1,CColSphere *sphere2,float *,float) 0x41B000
bool CCollision::CameraConeCastVsWorldCollision(CColSphere* sphere1, CColSphere* sphere2, float* arg2, float arg3) {
    return plugin::CallAndReturn<bool, 0x41B000, CColSphere*, CColSphere*, float*, float>(sphere1, sphere2, arg2, arg3);
}
