/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

#include "Collision.h"
#include "ColHelpers.h"
#include "extensions/enumerate.hpp"

CLinkList<CCollisionData*>& CCollision::ms_colModelCache = *(CLinkList<CCollisionData*>*)0x96592C;
int32& CCollision::ms_iProcessLineNumCrossings = *(int32*)0x9655D0;
uint32& CCollision::ms_collisionInMemory = *(uint32*)0x9655D4;

void CCollision::InjectHooks()
{
    RH_ScopedClass(CCollision);
    RH_ScopedCategory("Collision");

    RH_ScopedInstall(Init, 0x416260);
    // RH_ScopedInstall(Shutdown, 0x4162E0);
    RH_ScopedInstall(Update, 0x411E20);
    RH_ScopedInstall(SortOutCollisionAfterLoad, 0x411E30);

    RH_ScopedOverloadedInstall(CalculateTrianglePlanes, "colData", 0x416330, void(*)(CCollisionData*));
    RH_ScopedOverloadedInstall(RemoveTrianglePlanes, "colData", 0x416400, void(*)(CCollisionData*));
    RH_ScopedInstall(ProcessLineOfSight, 0x417950);
}

// 0x416260
void CCollision::Init() {
    ms_colModelCache.Init(50);
    ms_collisionInMemory = 0;
    CColStore::Initialise();
}

// 0x4162E0
void CCollision::Shutdown() {
    plugin::Call<0x4162E0>();
}

// 0x411E20
void CCollision::Update() {
    // NOP
}

// 0x411E30
void CCollision::SortOutCollisionAfterLoad() {
    CColStore::LoadCollision(TheCamera.m_mCameraMatrix.GetPosition(), false);
    CStreaming::LoadAllRequestedModels(false);
}

// 0x411E70
bool CCollision::TestSphereSphere(const CColSphere& sphere1, const CColSphere& sphere2) {
    return plugin::CallAndReturn<bool, 0x411E70, CColSphere const&, CColSphere const&>(sphere1, sphere2);
}

// 0x411EC0
void CalculateColPointInsideBox(const CBox& box, const CVector& point, CColPoint& colPoint) {
    plugin::Call<0x411EC0, CBox const&, CVector const&, CColPoint&>(box, point, colPoint);
}

// 0x4120C0
bool CCollision::TestSphereBox(const CSphere& sphere, const CBox& box) {
    return plugin::CallAndReturn<bool, 0x4120C0, CSphere const&, CBox const&>(sphere, box);
}

// 0x412130
bool CCollision::ProcessSphereBox(const CColSphere& sphere, const CColBox& box, CColPoint& colPoint, float& maxTouchDistance) {
    return plugin::CallAndReturn<bool, 0x412130, CColSphere const&, CColBox const&, CColPoint&, float&>(sphere, box, colPoint, maxTouchDistance);
}

// 0x412700
bool CCollision::PointInTriangle(const CVector& point, const CVector* triPoints) {
    return plugin::CallAndReturn<bool, 0x412700, CVector const&, CVector const*>(point, triPoints);
}

// 0x412850
float CCollision::DistToLineSqr(const CVector* lineStart, const CVector* lineEnd, const CVector* point) {
    return plugin::CallAndReturn<float, 0x412850, CVector const*, CVector const*, CVector const*>(lineStart, lineEnd, point);
}

// 0x412970
float CCollision::DistToMathematicalLine(const CVector* lineStart, const CVector* lineEnd, const CVector* point) {
    return plugin::CallAndReturn<float, 0x412970, CVector const*, CVector const*, CVector const*>(lineStart, lineEnd, point);
}

// 0x412A30
float CCollision::DistToMathematicalLine2D(float lineStartX, float lineStartY, float lineEndX, float lineEndY, float pointX, float pointY) {
    return plugin::CallAndReturn<float, 0x412A30, float, float, float, float, float, float>(lineStartX, lineStartY, lineEndX, lineEndY, pointX, pointY);
}

// 0x412A80
float CCollision::DistAlongLine2D(float lineX, float lineY, float lineDirX, float lineDirY, float pointX, float pointY) {
    return plugin::CallAndReturn<float, 0x412A80, float, float, float, float, float, float>(lineX, lineY, lineDirX, lineDirY, pointX, pointY);
}

// 0x412AA0
bool CCollision::ProcessLineSphere(const CColLine& line, const CColSphere& sphere, CColPoint& colPoint, float& depth) {
    return plugin::CallAndReturn<bool, 0x412AA0, CColLine const&, CColSphere const&, CColPoint&, float&>(line, sphere, colPoint, depth);
}

// 0x412C70
bool CCollision::TestLineBox_DW(const CColLine& line, const CBox& box) {
    return plugin::CallAndReturn<bool, 0x412C70, CColLine const&, CBox const&>(line, box);
}

// 0x413070
bool CCollision::TestLineBox(const CColLine& line, const CBox& box) {
    return plugin::CallAndReturn<bool, 0x413070, CColLine const&, CBox const&>(line, box);
}

// 0x413080
bool CCollision::TestVerticalLineBox(const CColLine& line, const CBox& box) {
    return plugin::CallAndReturn<bool, 0x413080, CColLine const&, CBox const&>(line, box);
}

// 0x413100
bool CCollision::ProcessLineBox(const CColLine& line, const CColBox& box, CColPoint& colPoint, float& maxTouchDistance) {
    return plugin::CallAndReturn<bool, 0x413100, CColLine const&, CColBox const&, CColPoint&, float&>(line, box, colPoint, maxTouchDistance);
}

// 0x4138D0
bool CCollision::Test2DLineAgainst2DLine(float line1StartX, float line1StartY, float line1EndX, float line1EndY, float line2StartX, float line2StartY, float line2EndX, float line2EndY) {
    return plugin::CallAndReturn<bool, 0x4138D0, float, float, float, float, float, float, float, float>(line1StartX, line1StartY, line1EndX, line1EndY, line2StartX, line2StartY, line2EndX, line2EndY);
}

// 0x413960
bool ProcessDiscCollision(CColPoint& colPoint1, const CMatrix& mat, const CColDisk& disk, CColPoint& colPoint2, bool& arg4, float& arg5, CColPoint& colPoint3) {
    return plugin::CallAndReturn<bool, 0x413960, CColPoint&, CMatrix const&, CColDisk const&, CColPoint&, bool&, float&, CColPoint&>(colPoint1, mat, disk, colPoint2, arg4, arg5, colPoint3);
}

// 0x413AC0
bool CCollision::TestLineTriangle(const CColLine& line, const CompressedVector* verts, const CColTriangle& tri, const CColTrianglePlane& triPlane) {
    return plugin::CallAndReturn<bool, 0x413AC0, CColLine const&, CompressedVector const*, CColTriangle const&, CColTrianglePlane const&>(line, verts, tri, triPlane);
}

// 0x4140F0
bool CCollision::ProcessLineTriangle(const CColLine& line, const CompressedVector* verts, const CColTriangle& tri, const CColTrianglePlane& triPlane, CColPoint& colPoint, float& maxTouchDistance, CStoredCollPoly* collPoly) {
    return plugin::CallAndReturn<bool, 0x4140F0, CColLine const&, CompressedVector const*, CColTriangle const&, CColTrianglePlane const&, CColPoint&, float&, CStoredCollPoly*>(line, verts, tri, triPlane, colPoint, maxTouchDistance, collPoly);
}

// 0x4147E0
bool CCollision::ProcessVerticalLineTriangle(const CColLine& line, const CompressedVector* verts, const CColTriangle& tri, const CColTrianglePlane& triPlane, CColPoint& colPoint, float& maxTouchDistance, CStoredCollPoly* collPoly) {
    return plugin::CallAndReturn<bool, 0x4147E0, CColLine const&, CompressedVector const*, CColTriangle const&, CColTrianglePlane const&, CColPoint&, float&, CStoredCollPoly*>(line, verts, tri, triPlane, colPoint, maxTouchDistance, collPoly);
}

// 0x414D70
bool CCollision::IsStoredPolyStillValidVerticalLine(const CVector& lineOrigin, float lineDist, CColPoint& colPoint, CStoredCollPoly* collPoly) {
    return plugin::CallAndReturn<bool, 0x414D70, CVector const&, float, CColPoint&, CStoredCollPoly*>(lineOrigin, lineDist, colPoint, collPoly);
}

// 0x415230
void CCollision::GetBoundingBoxFromTwoSpheres(CColBox* bbox, CColSphere* sphere1, CColSphere* sphere2) {
    plugin::Call<0x415230, CColBox*, CColSphere*, CColSphere*>(bbox, sphere1, sphere2);
}

// 0x4152C0
bool CCollision::IsThisVehicleSittingOnMe(CVehicle* vehicle, CVehicle* vehicleOnMe) {
    return plugin::CallAndReturn<bool, 0x4152C0, CVehicle*, CVehicle*>(vehicle, vehicleOnMe);
}

// 0x415320
bool CCollision::CheckCameraCollisionPeds(int32 sectorX, int32 sectorY, CVector* pos, CVector* dir, float* arg4) {
    return plugin::CallAndReturn<bool, 0x415320, int32, int32, CVector*, CVector*, float*>(sectorX, sectorY, pos, dir, arg4);
}

// 0x4154A0
bool CCollision::CheckPeds(CVector* pos, CVector* dir, float* arg2) {
    return plugin::CallAndReturn<bool, 0x4154A0, CVector*, CVector*, float*>(pos, dir, arg2);
}

// 0x415540
void ResetMadeInvisibleObjects() {
    plugin::Call<0x415540>();
}

// 0x415590
bool CCollision::SphereCastVsBBox(CColSphere* sphere1, CColSphere* sphere2, CColBox* box) {
    return plugin::CallAndReturn<bool, 0x415590, CColSphere*, CColSphere*, CColBox*>(sphere1, sphere2, box);
}

// 0x415620
bool CCollision::RayPolyPOP(CVector* arg0, CVector* arg1, CColTriangle* arg2, CVector* arg3, CVector* arg4) {
    return plugin::CallAndReturn<bool, 0x415620, CVector*, CVector*, CColTriangle*, CVector*, CVector*>(arg0, arg1, arg2, arg3, arg4);
}

// 0x4156D0
int32 CCollision::GetPrincipleAxis(CVector* vec) {
    return plugin::CallAndReturn<int32, 0x4156D0, CVector*>(vec);
}

// 0x415730
bool CCollision::PointInPoly(CVector* point, CColTriangle* tri, CVector* arg2, CVector* triVerts) {
    return plugin::CallAndReturn<bool, 0x415730, CVector*, CColTriangle*, CVector*, CVector*>(point, tri, arg2, triVerts);
}

// 0x415950
void CCollision::Closest3(CVector* arg0, CVector* arg1) {
    plugin::Call<0x415950, CVector*, CVector*>(arg0, arg1);
}

// 0x415A40
float ClosestSquaredDistanceBetweenFiniteLines(CVector* line1Start, CVector* line1End, CVector* line2Start, CVector* line2End, float arg4) {
    return plugin::CallAndReturn<float, 0x415A40, CVector*, CVector*, CVector*, CVector*, float>(line1Start, line1End, line2Start, line2End, arg4);
}

// 0x415CF0
bool CCollision::SphereCastVersusVsPoly(CColSphere* sphere1, CColSphere* sphere2, CColTriangle* tri, CColTrianglePlane* triPlane, CompressedVector* verts) {
    return plugin::CallAndReturn<bool, 0x415CF0, CColSphere*, CColSphere*, CColTriangle*, CColTrianglePlane*, CompressedVector*>(sphere1, sphere2, tri, triPlane, verts);
}

// 0x416330
void CCollision::CalculateTrianglePlanes(CCollisionData* colData) {
    if (!colData->m_nNumTriangles)
        return;

    if (colData->m_pTrianglePlanes)
    {
        auto* link = colData->GetLinkPtr();
        link->Remove();
        ms_colModelCache.usedListHead.Insert(link);
    }
    else
    {
        auto* link = ms_colModelCache.Insert(colData);
        if (!link)
        {
            auto* toRemove = ms_colModelCache.usedListTail.prev;
            toRemove->data->RemoveTrianglePlanes();
            ms_colModelCache.Remove(toRemove);
            link = ms_colModelCache.Insert(colData);
        }

        colData->CalculateTrianglePlanes();
        colData->SetLinkPtr(link);
    }
}

// 0x416400
void CCollision::RemoveTrianglePlanes(CCollisionData* colData) {
    if (!colData->m_pTrianglePlanes)
        return;

    auto* link = colData->GetLinkPtr();
    ms_colModelCache.Remove(link);
    colData->RemoveTrianglePlanes();
}

// 0x416450
bool CCollision::ProcessSphereSphere(const CColSphere& sphere1, const CColSphere& sphere2, CColPoint& colPoint, float& maxTouchDistance) {
    return plugin::CallAndReturn<bool, 0x416450, CColSphere const&, CColSphere const&, CColPoint&, float&>(sphere1, sphere2, colPoint, maxTouchDistance);
}

// 0x4165B0 - Original function took a CColSphere, but a `CSphere` should be just fine.
bool CCollision::TestSphereTriangle(const CSphere& sphere, const CompressedVector* verts, const CColTriangle& tri, CColTrianglePlane const& triPlane) {
    return plugin::CallAndReturn<bool, 0x4165B0, CSphere const&, CompressedVector const*, CColTriangle const&, CColTrianglePlane const&>(sphere, verts, tri, triPlane);
}

// 0x416BA0
bool CCollision::ProcessSphereTriangle(const CColSphere& sphere, const CompressedVector* verts, const CColTriangle& tri, const CColTrianglePlane& triPlane, CColPoint& colPoint, float& maxTouchDistance) {
    return plugin::CallAndReturn<bool, 0x416BA0, CColSphere const&, CompressedVector const*, CColTriangle const&, CColTrianglePlane const&, CColPoint&, float&>(sphere, verts, tri, triPlane, colPoint, maxTouchDistance);
}

// 0x417470
bool CCollision::TestLineSphere(const CColLine& line, const CColSphere& sphere) {
    return plugin::CallAndReturn<bool, 0x417470, CColLine const&, CColSphere const&>(line, sphere);
}

// 0x417610
float CCollision::DistToLine(const CVector& lineStart, const CVector& lineEnd, const CVector& point) {
    return plugin::CallAndReturn<float, 0x417610, CVector const&, CVector const&, CVector const&>(lineStart, lineEnd, point);
}

// 0x417730
bool CCollision::TestLineOfSight(const CColLine& line, const CMatrix& transform, CColModel& colModel, bool doSeeThroughCheck, bool doShootThroughCheck) {
    return plugin::CallAndReturn<bool, 0x417730, CColLine const&, CMatrix const&, CColModel&, bool, bool>(line, transform, colModel, doSeeThroughCheck, doShootThroughCheck);
}

// 0x417950
bool CCollision::ProcessLineOfSight(const CColLine& line, const CMatrix& transform, CColModel& colModel, CColPoint& colPoint, float& maxTouchDistance, bool doSeeThroughCheck, bool doShootThroughCheck) {
    assert(colModel.m_pColData);

    const auto colData = colModel.m_pColData;
    if (!colData)
        return false;

    const CMatrix invertedTransform = Invert(const_cast<CMatrix&>(transform)); // Hack: cast away constness. TODO: Fix-up constness of CMatrix methods

    // Transform lime into object space
    const CColLine line_OS = {
        MultiplyMatrixWithVector(invertedTransform, line.m_vecStart),
        MultiplyMatrixWithVector(invertedTransform, line.m_vecEnd),
    };

    if (!TestLineBox_DW(line_OS, colModel.GetBoundingBox()))
        return false;

    const auto CheckSeeAndShootThrough = [=](auto material) {
        return (!doSeeThroughCheck || !g_surfaceInfos->IsSeeThrough(material))
            && (!doShootThroughCheck || !g_surfaceInfos->IsShootThrough(material));
    };

    float localMinTouchDist = maxTouchDistance;

    bool results{};
    for (auto i = 0; i < colData->m_nNumSpheres; i++) {
        if (const auto& sphere = colData->m_pSpheres[i]; CheckSeeAndShootThrough(sphere.m_nMaterial)) {
            results |= ProcessLineSphere(line_OS, sphere, colPoint, localMinTouchDist);
        }
    }

    for (auto i = 0; i < colData->m_nNumBoxes; i++) {
        if (const auto& box = colData->m_pBoxes[i]; CheckSeeAndShootThrough(box.m_nMaterial)) {
            results |= ProcessLineBox(line_OS, box, colPoint, localMinTouchDist);
        }
    }

    CalculateTrianglePlanes(colData);

    for (auto i = 0; i < colData->m_nNumTriangles; i++) {
        if (const auto& tri = colData->m_pTriangles[i]; CheckSeeAndShootThrough(tri.m_nMaterial)) {
            results |= ProcessLineTriangle(line_OS, colData->m_pVertices, tri, colData->m_pTrianglePlanes[i], colPoint, localMinTouchDist, nullptr);
            ms_iProcessLineNumCrossings++;
        }
    }

    //localMinTouchDist = maxTouchDistance;
    if (localMinTouchDist < maxTouchDistance) {
        colPoint.m_vecPoint = MultiplyMatrixWithVector(transform, colPoint.m_vecPoint);
        colPoint.m_vecNormal = Multiply3x3(transform, colPoint.m_vecNormal);
        maxTouchDistance = localMinTouchDist;
        return true;
    }
    return false;
}

// 0x417BF0
bool CCollision::ProcessVerticalLine(const CColLine& line, const CMatrix& transform, CColModel& colModel, CColPoint& colPoint, float& maxTouchDistance, bool doSeeThroughCheck, bool doShootThroughCheck, CStoredCollPoly* collPoly) {
    return plugin::CallAndReturn<bool, 0x417BF0, CColLine const&, CMatrix const&, CColModel&, CColPoint&, float&, bool, bool, CStoredCollPoly*>(line, transform, colModel, colPoint, maxTouchDistance, doSeeThroughCheck, doShootThroughCheck, collPoly);
}

// 0x417F20
bool CCollision::SphereCastVsSphere(CColSphere* arg0, CColSphere* arg1, CColSphere* arg2) {
    return plugin::CallAndReturn<bool, 0x417F20, CColSphere*, CColSphere*, CColSphere*>(arg0, arg1, arg2);
}

// 0x417FD0
void CCollision::ClosestPointOnLine(CVector* arg0, CVector* arg1, CVector* arg2, CVector* arg3) {
    plugin::Call<0x417FD0, CVector*, CVector*, CVector*, CVector*>(arg0, arg1, arg2, arg3);
}

// 0x418100
void CCollision::ClosestPointsOnPoly(CColTriangle* arg0, CVector* arg1, CVector* arg2, CVector* arg3) {
    plugin::Call<0x418100, CColTriangle*, CVector*, CVector*, CVector*>(arg0, arg1, arg2, arg3);
}

// 0x418150
void CCollision::ClosestPointOnPoly(CColTriangle* arg0, CVector* arg1, CVector* arg2) {
    plugin::Call<0x418150, CColTriangle*, CVector*, CVector*>(arg0, arg1, arg2);
}

// 0x4181B0
bool CCollision::SphereCastVsCaches(CColSphere* sphere, CVector* arg1, int32 arg2, CColCacheEntry* arg3, int32* arg4, CColCacheEntry* arg5) {
    return plugin::CallAndReturn<bool, 0x4181B0, CColSphere*, CVector*, int32, CColCacheEntry*, int32*, CColCacheEntry*>(sphere, arg1, arg2, arg3, arg4, arg5);
}

// 0x418580
void CCollision::CalculateTrianglePlanes(CColModel* colModel) {
    plugin::Call<0x418580, CColModel*>(colModel);
}

// 0x4185A0
void CCollision::RemoveTrianglePlanes(CColModel* colModel) {
    plugin::Call<0x4185A0, CColModel*>(colModel);
}

// TODO: This function could be refactored to use ranges instead of these ugly static variables :D
/*!
* @brief 0x4185C0 - Test all of B's and A's spheres against each other's spheres, boxes, and triangles:
* 
*  A\B  Tri Sp  Box
* Tri       +
* Sp    +   +   +
* Box       +
*
* (Note: The game here originally processed lines and disks, but given that SA doesn't use lines and/or disks I didn't bother to do it)
*
* @param         transformA       Transformation matrix of model A - Usually owning entity's matrix.
* @param         cmA              Col model A
* @param         transformB       Transformation matrix of model B - Usually owning entity's matrix.
* @param         cmA              Col model B
* @param[out]    lineCPs          The first 32 collision points with lines - SA doesn't use lines or disks, so this is always empty. (can be null)
* @param[out]    sphereCPs        The first 32 collision points with spheres
* @param[in,out] maxTouchDistance It was only used for lines/disks - Again, SA doesn't have that, so this value isn't used (can be null)
* @param         arg7             Not 100% sure what this does. TODO.
* 
* @returns Number of sphere collision points found (At most 32)
*/
int32 CCollision::ProcessColModels(const CMatrix& transformA, CColModel& cmA, const CMatrix& transformB, CColModel& cmB, CColPoint(&sphereCPs)[32], CColPoint* _IGNORED_ lineCPs, float* _IGNORED_ maxTouchDistance, bool arg7) {

    UNUSED(lineCPs);
    UNUSED(maxTouchDistance);

    // Dont these this should ever happen, but okay?
    if (!cmA.m_pColData) {
        return;
    }

    if (!cmB.m_pColData) {
        return;
    }

    const auto cdA = *cmA.m_pColData;
    const auto cdB = *cmB.m_pColData;

    // Transform matrix from A's space to B's
    const auto transformAtoB = Invert(transformB) * transformA; 

    // A's bounding box in B's space
    const CSphere colABoundSphereSpaceB{
        MultiplyMatrixWithVector(transformAtoB, cmA.m_boundSphere.m_vecCenter),
        cmA.m_boundSphere.m_fRadius
    };

    if (!TestSphereBox(colABoundSphereSpaceB, cmB.m_boundBox)) {
        return 0;
    }

    // Transform matrix from B's space to A's
    const auto transformBtoA = Invert(transformA) * transformB;

    // Now, transform each cm's spheres and test them against each other's bounding box

    // TODO: Should probably move these out somewhere..
    constexpr auto MAX_SPHERES{ 128u }; // Max no. of spheres colliding with other model's bounding sphere. - If more - Possible crash
    constexpr auto MAX_BOXES{ 64u };    // Same, but for boxes      - If more, all following are ignored.
    constexpr auto MAX_TRIS{ 600u };    // Same, but for triangles  - If more, all following are ignored.

    // Transform `spheres` center position using `transform` and store them in `outSpheres`
    const auto TransformSpheres = []<size_t N>(const auto& spheres, const CMatrix& transform, CColSphere (&outSpheres)[N]) {
        std::ranges::transform(spheres, outSpheres, [&](const auto& sp) {
            CColSphere transformed = sp; // Copy sphere
            transformed.m_vecCenter = MultiplyMatrixWithVector(transform, sp.m_vecCenter); // Set copy's center as the transformed point
            return transformed;
        });
    };

    // Test `spheres` against bounding box `bb` and store all colliding sphere's indices in `collidedIdxs`
    const auto TestSpheresAgainstBB = []<size_t N>(const auto& spheres, const auto& bb, uint32& numCollided, uint32 (&collidedIdxs)[N]) {
        for (auto&& [i, sp] : enumerate(spheres)) {
            if (TestSphereBox(sp, bb)) {
                collidedIdxs[numCollided++] = i;
                assert(numCollided <= N); // Avoid out-of-bounds (Game originally didn't check)
            }
        }
    };

    // Process A's spheres and test them against B's

    // 0x418722 
    static CColSphere colASpheresSpaceB[MAX_SPHERES]; // A's spheres in B's space
    TransformSpheres(cdA.GetSpheres(), transformAtoB, colASpheresSpaceB);

    // 0x4187A1
    static uint32 colACollSpheres[MAX_SPHERES]; // Index of A's spheres that collided with B's BB
    uint32 colANumCollidingSpheres{};                     // No. of spheres that collided
    TestSpheresAgainstBB(colASpheresSpaceB, cmB.GetBoundingBox(), colANumCollidingSpheres, colACollSpheres);

    // Now do the same for B

    // 0x4187ED
    static CColSphere colBSpheresSpaceA[MAX_SPHERES]; // B's spheres in A's space
    TransformSpheres(cdA.GetSpheres(), transformBtoA, colBSpheresSpaceA);

    // 0x418862
    static uint32 colBCollSpheres[MAX_SPHERES]; // Index of B's spheres that collided with A's BB
    uint32 colBNumCollidingSpheres{};           // No. of spheres that collided
    TestSpheresAgainstBB(colBSpheresSpaceA, cmA.GetBoundingBox(), colBNumCollidingSpheres, colBCollSpheres);

    if (!colANumCollidingSpheres && !cdA.m_nNumLines && !colBNumCollidingSpheres) {
        return 0; // Early out if no collisions
    }

    // 0x418902 
    // Here the game tests collision of disks, but SA doesn't use disks, so I won't bother with it.
    assert(!cdB.bUsesDisks); // If this asserts then I was wrong and this part has to be reversed as well :D

    // 0x418A4E
    // Test B's boxes against A's bounding sphere
    static uint32 colBCollABoxes[MAX_BOXES]; // Indices of B's boxes colliding with A's bounding sphere
    uint32 numColBCollABoxes{};
    for (auto&& [i, box] : enumerate(cdB.GetBoxes())) {
        if (TestSphereBox(colABoundSphereSpaceB, box)) {
            colBCollABoxes[numColBCollABoxes++] = i;
            if (numColBCollABoxes >= MAX_BOXES) {
                break;
            }
        }
    }

    // Test B's triangles against A's bounding sphere
    static uint32 colBCollATris[MAX_TRIS]; // Indices of B's triangles
    uint32 colANumCollidingTris{};
    {
        CalculateTrianglePlanes(&cmB);

        // Process a single triangle
        const auto ProcessOneTri = [&](uint32 triIdx) {
            if (TestSphereTriangle(
                colABoundSphereSpaceB,
                cdB.m_pVertices,
                cdB.m_pTriangles[triIdx],
                cdB.m_pTrianglePlanes[triIdx]
            )) {
                colBCollATris[colANumCollidingTris++] = triIdx;
            }
        };

        if (cdB.m_nNumTriangles) {
            if (cdB.bHasFaceGroups) { // Test by using face groups - Thanks to those who helped me figure this out :)
                // 0x418B23
                for (auto&& group : cdB.GetFaceGroups()) {
                    if (TestSphereBox(colABoundSphereSpaceB, group.bb)) { // Quick BB check
                        for (auto i{ group.first }; i < group.last; i++) { // Check all triangles in this group
                            ProcessOneTri(i);
                        }
                    }
                }
            } else { // Game checked here if B.m_nNumTriangles > 0, but that is a redudant check.
                // 0x418C40
                for (auto i = 0u; i < cdB.m_nNumTriangles; i++) {
                    ProcessOneTri(i);
                }
            }
        }
    }

    if (!colANumCollidingSpheres && !colANumCollidingTris && !colBNumCollidingSpheres) {
        return 0;
    }

    // 0x418CAD
    // Process all of A's colliding spheres against all of B's colliding spheres, boxes and triangles
    sphereCPs->m_fDepth = -1.f;
    uint32 nNumSphereCPs{};
    if (colANumCollidingSpheres) { 
        float minTouchDist{ 1e24f };
        for (auto sphereAIdx : std::span{ colACollSpheres, colANumCollidingSpheres }) {
            const auto& sphereA{ cdA.m_pSpheres[sphereAIdx] };

            bool advanceColPointIdx{};

            // 0x418CF9
            // Spheres
            for (auto sphereBIdx : std::span{ colBCollSpheres , colBNumCollidingSpheres }) {
                const auto& sphereB{ cdB.m_pSpheres[sphereBIdx] };

                if (ProcessSphereSphere(
                    sphereA,
                    sphereB,
                    sphereCPs[nNumSphereCPs],
                    minTouchDist)
                ) {
                    advanceColPointIdx = true;
                    // These tests are cheap, so continue procesing
                }

                // Original code also processed disk's spheres here (which were added to `colBCollSpheres` above (I skipped that part as well :D))
                // But since the game doesn't use disks we skip this part.
            }

            // 0x418D86
            // Boxes
            for (auto boxIdx : std::span{ colBCollABoxes , numColBCollABoxes }) {
                const auto& box{ cdB.m_pBoxes[boxIdx] };
                
                if (auto& cp = sphereCPs[nNumSphereCPs]; ProcessSphereBox(
                    sphereA,
                    box,
                    cp,
                    minTouchDist)
                ) {
                    cp.m_nSurfaceTypeA = box.m_nMaterial;
                    cp.m_nPieceTypeA = box.m_nFlags;
                    cp.m_nLightingA = box.m_nLighting;

                    if (arg7 && sphereA.m_nFlags <= 2 && nNumSphereCPs < std::size(sphereCPs)) {
                        advanceColPointIdx = false;
                        minTouchDist = 1e24f;
                        sphereCPs[nNumSphereCPs + 1].m_fDepth = -1.f;
                        nNumSphereCPs++;
                    } else {
                        advanceColPointIdx = true;
                    }
                }
            }

            // Triangles
            // 0x418E44
            for (auto triIdx : std::span{ colBCollATris, colANumCollidingTris }) {
                const auto& tri{ cdB.m_pTriangles[triIdx] };

                if (auto& cp = sphereCPs[nNumSphereCPs]; ProcessSphereTriangle(
                    sphereA,
                    cdB.m_pVertices,
                    cdB.m_pTriangles[triIdx],
                    cdB.m_pTrianglePlanes[triIdx],
                    cp,
                    minTouchDist)
                ) {
                    // Same code as above in boxes
                    if (arg7 && sphereA.m_nFlags <= 2 && nNumSphereCPs < std::size(sphereCPs)) {
                        advanceColPointIdx = false;
                        minTouchDist = 1e24f;
                        sphereCPs[nNumSphereCPs + 1].m_fDepth = -1.f;
                        nNumSphereCPs++;
                    } else {
                        advanceColPointIdx = true;
                    }
                }
            }

            // 0x418EFC
            if (advanceColPointIdx) {
                nNumSphereCPs++;
                if (nNumSphereCPs >= std::size(sphereCPs)) { 
                    break; 
                }
                sphereCPs[nNumSphereCPs].m_fDepth = -1.f;
            }
        }

        // Transform all colpoints into world space
        for (auto&& cp : std::span{ sphereCPs, nNumSphereCPs }) {
            cp.m_vecPoint = MultiplyMatrixWithVector(transformB, cp.m_vecPoint);
            cp.m_vecNormal = Multiply3x3(transformB, cp.m_vecNormal);
        }
    }

    // 0x418F4C
    assert(!cdA.bUsesDisks); // Again, game does something with disks

    // 0x418F55
    assert(!cdA.m_nNumLines); // .. and lines so skip that.

    // 0x4185C0
    // Originally game transformed all sphereCPs to world space here, but I've moved that into the above `if` stuff

    // 0x4199E5
    // Find all A's triangles and boxes intersecting B's b.sphere
    // Then process them all against B's colliding spheres
    if (colBCollSpheres && cdA.m_nNumTriangles && cdA.m_nNumSpheres) {
        const CSphere colBSphereInASpace{
            MultiplyMatrixWithVector(transformBtoA, cmB.m_boundSphere.m_vecCenter),
            cmB.m_boundSphere.m_fRadius
        };

        const auto numCPsPrev{ nNumSphereCPs };

        // Process all of A's triangles against B's b.sphere
        static uint32 colACollTri[MAX_TRIS];
        uint32 colANumCollTri{};
        if (cdA.m_nNumTriangles) {
            CalculateTrianglePlanes(&cmA);

            // NOTE/TODO: Weird how they didn't use the facegroup stuff here as well.
            //            Should probably implement it here some day too, as it speeds up the process quite a bit.

            for (auto i = 0; i < cdA.m_nNumTriangles; i++) {
                if (TestSphereTriangle(
                    colBSphereInASpace,
                    cdA.m_pVertices,
                    cdA.m_pTriangles[i],
                    cdA.m_pTrianglePlanes[i])
                ) {
                    colACollTri[colANumCollTri++] = i;
                }
            }
        }

        // 0x419AB6
        // Process all of A's boxes against B's b.sphere
        static uint32 colACollBox[MAX_TRIS];
        uint32 colANumCollBox{};
        for (auto i = 0; i < cdA.m_nNumBoxes; i++) {
            if (TestSphereBox(colBSphereInASpace, cdA.m_pBoxes[i])) {
                colACollBox[colANumCollBox++] = i;
            }
        }

        // 0x419B76
        // Process all of B's colliding spheres against all of A's colliding triangles
        for (auto sphereIdx : std::span{ colBCollSpheres, colBNumCollidingSpheres }) {
            const auto& sphere{ cdB.m_pSpheres[sphereIdx] };

            auto minTouchDist{ 1e24f };
            bool anyCollided{};
            for (auto triIdx : std::span{ colACollBox , colANumCollBox }) {
                if (ProcessSphereTriangle(
                    sphere,
                    cdA.m_pVertices,
                    cdA.m_pTriangles[triIdx],
                    cdA.m_pTrianglePlanes[triIdx],
                    sphereCPs[nNumSphereCPs],
                    minTouchDist
                )) {
                    anyCollided = true;
                }
            }

            if (anyCollided) {
                sphereCPs[nNumSphereCPs].m_vecNormal *= -1.f;

                nNumSphereCPs++;
                if (nNumSphereCPs >= std::size(sphereCPs)) {
                    break;
                }
                sphereCPs[nNumSphereCPs].m_fDepth = -1.f; // Next col point
            }
        }

        // 0x419CC4
        // Process all of B's colliding spheres against all of A's colliding boxes
        for (auto sphereIdx : std::span{ colBCollSpheres, colBNumCollidingSpheres }) {
            const auto& sphere{ cdB.m_pSpheres[sphereIdx] };

            float minTouchDist{ 1e24f };
            for (auto boxIdx : std::span{ colACollBox, colANumCollBox }) {
                const auto& box{ cdA.m_pBoxes[boxIdx] };
                auto& cp = sphereCPs[nNumSphereCPs];
                if (ProcessSphereBox(
                    sphere,
                    box,
                    cp,
                    minTouchDist)
                ) {
                    cp.m_nSurfaceTypeA = box.m_nMaterial;
                    cp.m_nPieceTypeA = box.m_nFlags; // Presumeably box.m_nFlags aren't actually flags.
                    cp.m_nLightingA = box.m_nLighting;

                    cp.m_nSurfaceTypeB = sphere.m_nMaterial;
                    cp.m_nPieceTypeB = sphere.m_nFlags;
                    cp.m_nLightingB = sphere.m_nLighting;

                    cp.m_vecNormal *= -1.f; // Invert direction

                    nNumSphereCPs++;
                    if (nNumSphereCPs >= std::size(sphereCPs)) {
                        break;
                    }
                    sphereCPs[nNumSphereCPs].m_fDepth = -1.f; // Next col point
                }
            }
        }

        // 0x419E56
        // Transform added colpoints into world space
        if (numCPsPrev != nNumSphereCPs) { // If we've processed any items..
            for (auto& cp : std::span{ sphereCPs, numCPsPrev }) {
                cp.m_vecPoint = MultiplyMatrixWithVector(transformA, cp.m_vecPoint);
                cp.m_vecNormal = Multiply3x3(transformA, cp.m_vecNormal);

                // Weird stuff, idk why they do this
                cp.m_nSurfaceTypeB = cp.m_nSurfaceTypeA;
                cp.m_nPieceTypeB =cp.m_nPieceTypeA;
                cp.m_nLightingB =cp.m_nLightingA;
            }
        }
    }

    // Originally here there was a loop to transform all CPs that were added in the above section
    // I moved it into the above section to keep things clear.

    return (int32)nNumSphereCPs;
}

// 0x419F00
bool CCollision::SphereCastVsEntity(CColSphere* sphere1, CColSphere* sphere2, CEntity* entity) {
    return plugin::CallAndReturn<bool, 0x419F00, CColSphere*, CColSphere*, CEntity*>(sphere1, sphere2, entity);
}

// 0x41A5A0
bool CCollision::SphereVsEntity(CColSphere* sphere, CEntity* entity) {
    return plugin::CallAndReturn<bool, 0x41A5A0, CColSphere*, CEntity*>(sphere, entity);
}

// 0x41A820
bool CCollision::CheckCameraCollisionBuildings(int32 sectorX, int32 sectorY, CColBox* arg2, CColSphere* arg3, CColSphere* arg4, CColSphere* arg5) {
    return plugin::CallAndReturn<bool, 0x41A820, int32, int32, CColBox*, CColSphere*, CColSphere*, CColSphere*>(sectorX, sectorY, arg2, arg3, arg4, arg5);
}

// 0x41A990
bool CCollision::CheckCameraCollisionVehicles(int32 sectorX, int32 sectorY, CColBox* arg2, CColSphere* arg3, CColSphere* arg4, CColSphere* arg5, CVector* arg6) {
    return plugin::CallAndReturn<bool, 0x41A990, int32, int32, CColBox*, CColSphere*, CColSphere*, CColSphere*, CVector*>(sectorX, sectorY, arg2, arg3, arg4, arg5, arg6);
}

// 0x41AB20
bool CCollision::CheckCameraCollisionObjects(int32 sectorX, int32 sectorY, CColBox* arg2, CColSphere* arg3, CColSphere* arg4, CColSphere* arg5) {
    return plugin::CallAndReturn<bool, 0x41AB20, int32, int32, CColBox*, CColSphere*, CColSphere*, CColSphere*>(sectorX, sectorY, arg2, arg3, arg4, arg5);
}

// 0x41AC40
bool CCollision::BuildCacheOfCameraCollision(CColSphere* sphere1, CColSphere* sphere2) {
    return plugin::CallAndReturn<bool, 0x41AC40, CColSphere*, CColSphere*>(sphere1, sphere2);
}

// 0x41B000
bool CCollision::CameraConeCastVsWorldCollision(CColSphere* sphere1, CColSphere* sphere2, float* arg2, float arg3) {
    return plugin::CallAndReturn<bool, 0x41B000, CColSphere*, CColSphere*, float*, float>(sphere1, sphere2, arg2, arg3);
}
