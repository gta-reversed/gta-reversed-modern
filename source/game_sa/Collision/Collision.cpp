/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

#include "Collision.h"
#include "ColHelpers.h"
#include "extensions/enumerate.hpp"

namespace rng = std::ranges;

void CalculateColPointInsideBox(CBox const& box, CVector const& point, CColPoint& colPoint); // Forward declaration needed for `InjectHooks`

void CCollision::InjectHooks()
{
    // Must be done be4 hooks are injected
#ifdef _DEBUG
    for (auto i = 0; i < 20; i++) {
        Tests();
    }
#endif

    RH_ScopedClass(CCollision);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(Init, 0x416260);
    RH_ScopedInstall(Shutdown, 0x4162E0, { .reversed = false });
    RH_ScopedInstall(Update, 0x411E20);
    RH_ScopedInstall(SortOutCollisionAfterLoad, 0x411E30);
    RH_ScopedInstall(TestSphereSphere, 0x411E70);
    RH_ScopedGlobalInstall(CalculateColPointInsideBox, 0x411EC0);
    RH_ScopedInstall(TestSphereBox, 0x4120C0);
    RH_ScopedInstall(ProcessSphereBox, 0x412130);
    RH_ScopedInstall(PointInTriangle, 0x412700);
    RH_ScopedInstall(DistToLineSqr, 0x412850);
    RH_ScopedInstall(DistToMathematicalLine, 0x412970);
    RH_ScopedInstall(DistToMathematicalLine2D, 0x412A30);
    RH_ScopedInstall(DistAlongLine2D, 0x412A80);
    RH_ScopedInstall(ProcessLineSphere, 0x412AA0);
    RH_ScopedInstall(TestLineBox_DW, 0x412C70);
    RH_ScopedInstall(TestLineBox, 0x413070);
    RH_ScopedInstall(TestVerticalLineBox, 0x413080);
    RH_ScopedInstall(ProcessLineBox, 0x413100);
    RH_ScopedInstall(Test2DLineAgainst2DLine, 0x4138D0);
    //RH_ScopedInstall(ProcessDiscCollision, 0x413960);
    //RH_ScopedInstall(TestLineTriangle, 0x413AC0);
    //RH_ScopedInstall(ProcessLineTriangle, 0x4140F0);
    //RH_ScopedInstall(ProcessVerticalLineTriangle, 0x4147E0);
    //RH_ScopedInstall(IsStoredPolyStillValidVerticalLine, 0x414D70);
    //RH_ScopedInstall(GetBoundingBoxFromTwoSpheres, 0x415230);
    //RH_ScopedInstall(IsThisVehicleSittingOnMe, 0x4152C0);
    //RH_ScopedInstall(CheckCameraCollisionPeds, 0x415320);
    //RH_ScopedInstall(CheckPeds, 0x4154A0);
    //RH_ScopedInstall(ResetMadeInvisibleObjects, 0x415540);
    //RH_ScopedInstall(SphereCastVsBBox, 0x415590);
    //RH_ScopedInstall(RayPolyPOP, 0x415620);
    //RH_ScopedInstall(GetPrincipleAxis, 0x4156D0);
    //RH_ScopedInstall(PointInPoly, 0x415730);
    //RH_ScopedInstall(Closest3, 0x415950);
    //RH_ScopedInstall(ClosestSquaredDistanceBetweenFiniteLines, 0x415A40);
    //RH_ScopedInstall(SphereCastVersusVsPoly, 0x415CF0);
    //RH_ScopedInstall(Init, 0x416260);
    //RH_ScopedInstall(Shutdown, 0x4162E0);
    //RH_ScopedInstall(ProcessSphereSphere, 0x416450);
    //RH_ScopedInstall(TestSphereTriangle, 0x4165B0);
    //RH_ScopedInstall(ProcessSphereTriangle, 0x416BA0);
    //RH_ScopedInstall(TestLineSphere, 0x417470);
    //RH_ScopedInstall(DistToLine, 0x417610);
    //RH_ScopedInstall(TestLineOfSight, 0x417730);
    //RH_ScopedInstall(ProcessLineOfSight, 0x417950);
    //RH_ScopedInstall(ProcessVerticalLine, 0x417BF0);
    //RH_ScopedInstall(SphereCastVsSphere, 0x417F20);
    //RH_ScopedInstall(ClosestPointOnLine, 0x417FD0);
    //RH_ScopedInstall(ClosestPointsOnPoly, 0x418100);
    //RH_ScopedInstall(ClosestPointOnPoly, 0x418150);
    RH_ScopedInstall(ProcessColModels, 0x4185C0);
    //RH_ScopedInstall(SphereCastVsCaches, 0x4181B0);
    //RH_ScopedInstall(SphereCastVsEntity, 0x419F00);
    //RH_ScopedInstall(SphereVsEntity, 0x41A5A0);
    //RH_ScopedInstall(CheckCameraCollisionBuildings, 0x41A820);
    //RH_ScopedInstall(CheckCameraCollisionVehicles, 0x41A990);
    //RH_ScopedInstall(CheckCameraCollisionObjects, 0x41AB20);
    //RH_ScopedInstall(BuildCacheOfCameraCollision, 0x41AC40);
    //RH_ScopedInstall(CameraConeCastVsWorldCollision, 0x41B000);

    RH_ScopedOverloadedInstall(CalculateTrianglePlanes, "colData", 0x416330, void (*)(CCollisionData*));
    RH_ScopedOverloadedInstall(RemoveTrianglePlanes, "colData", 0x416400, void (*)(CCollisionData*));
    RH_ScopedInstall(ProcessLineOfSight, 0x417950);
    RH_ScopedInstall(ProcessColModels, 0x4185C0, { .reversed = false });
}

void CCollision::Tests() {
    const auto seed = time(nullptr);
    srand(seed + rand());
    std::cout << "CCollision::Tests seed: " << seed << std::endl;

    const auto VectorEq = [](const CVector& lhs, const CVector& rhs, float epsilon = 0.01f) {
        for (auto i = 0u; i < 3u; i++) {
            if (approxEqual(lhs[i], rhs[i], epsilon)) {
                return false;
            }
        }
        return true;
    };

    const auto ColPointEq = [&](const CColPoint& lhs, const CColPoint& rhs) {
        return VectorEq(lhs.m_vecPoint, rhs.m_vecPoint)
            && lhs.m_fDepth == rhs.m_fDepth
            && VectorEq(lhs.m_vecNormal, rhs.m_vecNormal);
    };

    const auto RandomVector = [](float min = -100.f, float max = 100.f) {
        return CVector{
            CGeneral::GetRandomNumberInRange(min, max),
            CGeneral::GetRandomNumberInRange(min, max),
            CGeneral::GetRandomNumberInRange(min, max)
        };
    };

    const auto RandomSphere = [&](float min = -100.f, float max = 100.f) {
        return CColSphere{ RandomVector(min, max), CGeneral::GetRandomNumberInRange(min, max) };
    };

    const auto RandomBox = [&](float min = -100.f, float max = 100.f) {
        CColBox cb{ RandomVector(min, max), RandomVector(min, max) };
        cb.Recalc();
        return cb;
    };

    const auto RandomLine = [&](float min = -100.f, float max = 100.f) {
        return CColLine{ RandomVector(min, max) , RandomVector(min, max) };
    };

    const auto RandomVerticalLine = [&](float min = -100.f, float max = 100.f) {
        const auto pos = RandomVector(min, max);
        return CColLine{ {pos.x, pos.y, pos.z + fabs(pos.x)}, {pos.x, pos.y, pos.z - fabs(pos.x)} };
    };

    const auto Test = [](auto name, auto org, auto rev, auto cmp, auto&&... args) {
        const auto orgResult = org(args...);
        const auto revResult = rev(args...);
        if (!cmp(orgResult, revResult)) {
            std::cerr << "[CCollision::Tests]: " << name << " failed. " << std::endl;
            assert(0);
        }
    };

    // TestSphereSphere
    {
        auto sp1 = RandomSphere(), sp2 = RandomSphere();
        auto Original = plugin::CallAndReturn<bool, 0x411E70, CColSphere const&, CColSphere const&>;
        Test("TestSphereSphere", Original, TestSphereSphere, std::equal_to<>{}, sp1, sp2);
    }

    // CalculateColPointInsideBox
    {
        const auto Org = [&](auto box, auto point) {
            CColPoint cp{};
            plugin::Call<0x411EC0, CBox const&, CVector const&, CColPoint&>(box, point, cp);
            return cp;
        };

        const auto Rev = [](auto box, auto point) {
            CColPoint cp{};
            CalculateColPointInsideBox(box, point, cp);
            return cp;
        };

        Test("CalculateColPointInsideBox", Org, Rev, ColPointEq, RandomBox(), RandomVector());
    }

    // TestSphereBox
    {
        const auto Org = plugin::CallAndReturn<bool, 0x4120C0, CSphere const&, CBox const&>;
        Test("TestSphereBox", Org, TestSphereBox, std::equal_to{}, RandomSphere(), RandomBox());
    }

    // CalculateColPointInsideBox
    {
        // both will be of type pair<CColPoint, float> 
        const auto CmpEq = [&](auto o, auto r) {
            return o.second == r.second && ColPointEq(o.first, r.first);
        };

        const auto Org = [&](auto sp, auto box) {
            CColPoint cp{};
            float dist{1.f};
            plugin::Call<0x412130, CColSphere const&, CColBox const&, CColPoint&, float&>(sp, box, cp, dist);
            return std::make_pair(cp, dist);
        };

        const auto Rev = [](auto sp, auto box) {
            CColPoint cp{};
            float dist{1.f};
            ProcessSphereBox(sp, box, cp, dist);
            return std::make_pair(cp, dist);
        };

        Test("CalculateColPointInsideBox", Org, Rev, CmpEq, RandomSphere(), RandomBox());
    }

    // PointInTriangle
    {
        const CVector tri[3]{ RandomVector(), RandomVector(), RandomVector() };
        const auto Org = (bool(__stdcall*)(CVector const&, CVector const*))0x412700;
        Test("PointInTriangle", Org, PointInTriangle, std::equal_to{}, RandomVector(), tri);
    }

    // DistToLineSqr
    {
        const auto Org = plugin::CallAndReturn<double, 0x412850, CVector const*, CVector const*, CVector const*>;
        const auto ls{ RandomVector() }, le{ RandomVector() }, p{ RandomVector() };
        const auto CmpEq = [](float org, float rev) {
            return approxEqual(org, rev, 0.02f);
        };
        Test("DistToLineSqr", Org, DistToLineSqr, CmpEq, &ls, &le, &p);
    }

    // DistToMathematicalLine2D
    {
        const auto Org = plugin::CallAndReturn<float, 0x412A30, float, float, float, float, float, float>;
        const auto ls{ RandomVector() }, le{ RandomVector() }, p{ RandomVector() };
        const auto CmpEq = [](float org, float rev) {
            return approxEqual(org, rev, 0.02f);
        };
        Test("DistToLineSqr", Org, DistToMathematicalLine2D, CmpEq, ls.x, ls.y, le.x, le.y, p.x, p.y);
    }

    // ProcessLineSphere
    {
        const auto Org = [&](auto line, auto sp) {
            CColPoint cp{};
            float depth{ 100.f };
            const bool s = plugin::CallAndReturn<bool, 0x412AA0, CColLine const&, CColSphere const&, CColPoint&, float&>(line, sp, cp, depth);
            return std::make_tuple(cp, depth, s);
        };

        const auto Rev = [](auto line, auto sp) {
            CColPoint cp{};
            float depth{ 100.f };
            const bool s = ProcessLineSphere(line, sp, cp, depth);
            return std::make_tuple(cp, depth, s);
        };

        const auto CmpEq = [&](auto org, auto rev) {
            auto [org_cp, org_d, org_s] = org;
            auto [rev_cp, rev_d, rev_s] = rev;
            return org_s == rev_s && approxEqual(rev_d, org_d, 0.001f) && ColPointEq(org_cp, rev_cp);
        };

        Test("ProcessLineSphere", Org, Rev, CmpEq, RandomLine(), RandomSphere());
    }

    // TestLineBox
    {
        const auto Org = plugin::CallAndReturn<bool, 0x413070, CColLine const&, CBox const&>;
        Test("TestLineBox", Org, TestLineBox, std::equal_to{}, RandomLine(), RandomBox());
    }

    // TestVerticalLineBox
    {
        const auto Org = plugin::CallAndReturn<bool, 0x413080, CColLine const&, CBox const&>;
        Test("TestVerticalLineBox", Org, TestVerticalLineBox, std::equal_to{}, RandomVerticalLine(), RandomBox());
    }

    // ProcessLineBox
    /*{
        const auto Org = [&](auto line, auto box) {
            CColPoint cp{};
            float depth{ 100.f };
            const bool s = plugin::CallAndReturn<bool, 0x413100, CColLine const&, CColBox const&, CColPoint&, float&>(line, box, cp, depth);
            return std::make_tuple(cp, depth, s);
        };

        const auto Rev = [](auto line, auto box) {
            CColPoint cp{};
            float depth{ 100.f };
            const bool s = ProcessLineBox(line, box, cp, depth);
            return std::make_tuple(cp, depth, s);
        };

        const auto CmpEq = [&](auto org, auto rev) {
            auto [org_cp, org_d, org_s] = org;
            auto [rev_cp, rev_d, rev_s] = rev;
            return org_s == rev_s && approxEqual(rev_d, org_d, 0.001f) && ColPointEq(org_cp, rev_cp);
        };

        Test("ProcessLineBox", Org, Rev, CmpEq, RandomLine(), RandomBox());
    }*/
}

/*!
* @address 0x416260
*/
void CCollision::Init() {
    ms_colModelCache.Init(50);
    ms_collisionInMemory = 0;
    CColStore::Initialise();
}

// 0x411E20
void CCollision::Update() {
    // empty
}

// 0x411E30
void CCollision::SortOutCollisionAfterLoad() {
    CColStore::LoadCollision(TheCamera.m_mCameraMatrix.GetPosition(), false);
    CStreaming::LoadAllRequestedModels(false);
}

// 0x411E70
bool CCollision::TestSphereSphere(CColSphere const& sphere1, CColSphere const& sphere2) {
    return (sphere1.m_vecCenter - sphere2.m_vecCenter).SquaredMagnitude() <= std::pow(sphere1.m_fRadius + sphere2.m_fRadius, 2);
}

// 0x411EC0
void CalculateColPointInsideBox(CBox const& box, CVector const& point, CColPoint& colPoint) {
    const auto pointToCenter = point - box.GetCenter();

    // Calculate point's component-wise distance to each corner on each axis
    #define DoAxis(a) pointToCenter.a <= 0 ? point.a - box.m_vecMin.a : box.m_vecMax.a - point.a
    const CVector pointToClosest{ DoAxis(x), DoAxis(y), DoAxis(z) };
    #undef DoAxis

    const auto CalcNormal = [](float a) {
        return a <= 0.f ? -1.f : 1.f;
    };

    colPoint = {};
    colPoint.m_vecPoint = point;

    if (pointToClosest.x >= pointToClosest.y || pointToClosest.x >= pointToClosest.z) {
        if (pointToClosest.y >= pointToClosest.x || pointToClosest.y >= pointToClosest.z) {
            colPoint.m_vecNormal.z = CalcNormal(pointToCenter.z);
            colPoint.m_fDepth = pointToClosest.z;
        } else {
            colPoint.m_vecNormal.y = CalcNormal(pointToCenter.y);
            colPoint.m_fDepth = pointToClosest.y;
        }
    } else {
        colPoint.m_vecNormal.x = CalcNormal(pointToCenter.x);
        colPoint.m_fDepth = pointToClosest.x;
    }
}

/*!
* @address 0x4120C0
* @brief Tests if \a box is fully inside \a sphere
*/
bool CCollision::TestSphereBox(CSphere const& sphere, CBox const& box) {
    for (auto i = 0u; i < 3u; i++) {
        if (sphere.m_vecCenter[i] + sphere.m_fRadius < box.m_vecMin[i] ||
            sphere.m_vecCenter[i] - sphere.m_fRadius > box.m_vecMax[i]
        ) {
            return false;
        }
    }
    return true;
}

/*!
* @address 0x412130
*/
bool CCollision::ProcessSphereBox(CColSphere const& sph, CColBox const& box, CColPoint & colp, float& minDistSq) {
	// GTA's code is too complicated, uses a huge 3x3x3 if statement
	// we can simplify the structure a lot
    // Some of the original code, to give you an idea:
    /*
    if (sphere.m_vecCenter.x + sphere.m_fRadius < box.m_vecMin.x)
        return false;

    if (sphere.m_vecCenter.x + sphere.m_fRadius > box.m_vecMax.x)
        return false;

    CVector colPos{};

    if (sphere.m_vecCenter.x >= box.m_vecMin.x) {
        if (sphere.m_vecCenter.x <= box.m_vecMax.x) {
            if (sphere.m_vecCenter.y + sphere.m_fRadius > box.m_vecMin.y)
                return false;

            if (sphere.m_vecCenter.y - sphere.m_fRadius > box.m_vecMax.y)
                return false;

            if (sphere.m_vecCenter.y >= box.m_vecMin.y) {
                if (sphere.m_vecCenter.y <= box.m_vecMax.y) {
                    if (sphere.m_vecCenter.z + sphere.m_fRadius > box.m_vecMin.z)
                        return false;

                    if (sphere.m_vecCenter.z - sphere.m_fRadius > box.m_vecMax.z)
                        return false;

                    if (sphere.m_vecCenter.z >= box.m_vecMin.z) {
                        if (sphere.m_vecCenter.z <= box.m_vecMax.z) {
                            CColPoint boxCP{};
                            CalculateColPointInsideBox(box, sphere.m_vecCenter, boxCP);

                            colPoint.m_vecPoint = boxCP.m_vecPoint - boxCP.m_vecNormal * sphere.m_fRadius;
                            colPoint.m_fDepth = boxCP.m_fDepth;

                            colPoint.m_nLightingA = sphere.m_nLighting;
                            colPoint.m_nSurfaceTypeA = sphere.m_nMaterial;

                            colPoint.m_nLightingB = box.m_nLighting;
                            colPoint.m_nSurfaceTypeB = box.m_nMaterial;

                            maxTouchDistance = 0.f;

                            return true;
                        } else {
                            colPos.x = sphere.m_vecCenter.x;
                            colPos.y = sphere.m_vecCenter.y;
                            colPos.z = box.m_vecMax.z;
                        }
                    } else {
                        colPos.x = sphere.m_vecCenter.x;
                        colPos.y = sphere.m_vecCenter.y;
                        colPos.z = box.m_vecMin.z;
                    }
                } else {
                    if (sphere.m_vecCenter.z + sphere.m_fRadius > box.m_vecMin.z)
                        return false;

                    if (sphere.m_vecCenter.z - sphere.m_fRadius > box.m_vecMax.z)
                        return false;

                    if (sphere.m_vecCenter.z >= box.m_vecMin.z) {
                        if (sphere.m_vecCenter.z <= box.m_vecMax.z) {
                            colPos.x = sphere.m_vecCenter.x;
                            colPos.y = box.m_vecMax.y;

                            if (sphere.m_vecCenter.z > box.m_vecMax.z)
                                colPos.y = box.m_vecMax.y;

                            if (sphere.m_vecCenter.z <= box.m_vecMax.z) {
                                colPos.z = sphere.m_vecCenter.z;
                                colPos.y = box.m_vecMax.y;
                            } else {
                                colPos.z = box.m_vecMax.z;
                            }
                        } else {

                        }
                    } else {
                        colPos.y = box.m_vecMax.y;
                        colPos.x = sphere.m_vecCenter.x;
                        colPos.z = box.m_vecMin.z;
                    }
                }
            } else {
                if (sphere.m_vecCenter.z + sphere.m_fRadius > box.m_vecMin.z)
                    return false;

                if (sphere.m_vecCenter.z - sphere.m_fRadius > box.m_vecMax.z)
                    return false;

                if (sphere.m_vecCenter.z)
            }
        }
    }
    */

	// First make sure we have a collision at all
    if (!TestSphereBox(sph, box))
        return false;

	// Now find out where the sphere center lies in relation to all the sides
    enum class ClosestCorner {
        INSIDE,
        MIN,    
        MAX,
    };
    using enum ClosestCorner;

    ClosestCorner axies[3];
    for (auto i = 0; i < 3; i++) {
        axies[i] = sph.m_vecCenter[i] < box.m_vecMin[i] ? MIN :
                   sph.m_vecCenter[i] > box.m_vecMax[i] ? MAX :
                   INSIDE;
    }

	if(axies[0] == INSIDE && axies[1] == INSIDE && axies[2] == INSIDE) { // Sphere center is inside the box
        const auto p{ box.GetCenter() };

		const auto dir = sph.m_vecCenter - p;
        const auto distSq = dir.SquaredMagnitude();
		if(distSq < minDistSq){
            colp.m_vecNormal = dir / sqrt(distSq); // Normalize direction
			colp.m_vecPoint = sph.m_vecCenter - colp.m_vecNormal;

            colp.m_nSurfaceTypeA = sph.m_nMaterial;
            colp.m_nLightingA = sph.m_nLighting;

            colp.m_nSurfaceTypeB = box.m_nMaterial;
            colp.m_nLightingB = box.m_nLighting;

			// find absolute distance to the closer side in each dimension
			const float dx = dir.x > 0.0f ?
				box.m_vecMax.x - sph.m_vecCenter.x :
				sph.m_vecCenter.x - box.m_vecMin.x;

			const float dy = dir.y > 0.0f ?
				box.m_vecMax.y - sph.m_vecCenter.y :
				sph.m_vecCenter.y - box.m_vecMin.y;

			const float dz = dir.z > 0.0f ?
				box.m_vecMax.z - sph.m_vecCenter.z :
				sph.m_vecCenter.z - box.m_vecMin.z;

			// collision depth is maximum of that:
            colp.m_fDepth = std::max({ dx, dy, dz });

			return true;
		}
	} else { // Sphere centre is outside on at least one axis
		
		// Position of closest corner:
        const CVector p{
            axies[0] == MIN ? box.m_vecMin.x :
            axies[0] == MAX ? box.m_vecMax.x :
                              sph.m_vecCenter.x,

            axies[1] == MIN ? box.m_vecMin.y :
            axies[1] == MAX ? box.m_vecMax.y :
                              sph.m_vecCenter.y,

            axies[2] == MIN ? box.m_vecMin.z :
            axies[2] == MAX ? box.m_vecMax.z :
                              sph.m_vecCenter.z,
        };

        const auto dir = sph.m_vecCenter - p;
        const auto distSq = dir.SquaredMagnitude();
        if (distSq < minDistSq) {
            colp.m_vecNormal = dir / sqrt(distSq); // Normalize vector
            colp.m_vecPoint = p;

            colp.m_nSurfaceTypeA = sph.m_nMaterial;
            colp.m_nLightingA = sph.m_nLighting;

            colp.m_nSurfaceTypeB = box.m_nMaterial;
            colp.m_nLightingB = box.m_nLighting;

			minDistSq = distSq;

			return true;
		}
	}
	return false;
}

/*!
* @address 0x412700
*/
bool __stdcall CCollision::PointInTriangle(CVector const& point, CVector const* triPoints) {
    // Make everything relative to 0th vertex of the triangle
    const auto v1 = triPoints[1] - triPoints[0];
    const auto v2 = triPoints[2] - triPoints[0];
    const auto p  = point        - triPoints[0];

    // NOTE:
    // Because no vectors are normalized all dot products are scaled.
    // In order to compensate for this they multiply values by either vector's squared magnitude.

    const auto v1_dot_v2 = DotProduct(v1, v2); 

    const auto v2_dot_p = DotProduct(v2, p);
    const auto v2_magSq = v2.SquaredMagnitude();

    const auto v1_dot_p = DotProduct(v1, p);
    const auto v1_magSq = v1.SquaredMagnitude();

    const auto a = (v2_magSq * v1_dot_p) - (v1_dot_v2 * v2_dot_p);
    if (a >= 0.f) {
        const auto b = (v1_magSq * v2_dot_p) - (v1_dot_v2 * v1_dot_p);
        if (b >= 0.f) {
            const auto c = (v1_magSq * v2_magSq) - (v1_dot_v2 * v1_dot_v2);
            return c >= (a + b);
        }
    }
    return false;
}

/*!
* @address 0x412850
* @brief Retruns the squared magnitude of the perpendicular vector starting at \a point and ending on the line defined by \a lineStart and \a lineEnd.
*
* If this vector doesn't intersect the line (eg.: Intersection point would be before\after \a lineStart or \a lineEnd respectively) either
* \a lineStart or \a lineEnd is returned (whichever is closer)
*/
float CCollision::DistToLineSqr(CVector const& lineStart, CVector const& lineEnd, CVector const& point) {
    // Make line end (l) and point (p) relative to lineStart (by this lineStart becomes the space origin)
    const auto l = lineEnd - lineStart;
    const auto p = point - lineStart;

    //        * P
    //      / |
    //   c /  | a
    //    /   |
    // O *----+--------* L
    //     b  IP
    //
    // O    - Origin (line start)
    // L    - Line end
    // P    - Point
    // IP   - Intersection point
    // b, c - Triangle sides
    // a    - The distance we want to find out :D

    const auto lineMagSq = l.SquaredMagnitude();
    const auto bScaled   = DotProduct(p, l); // Side b scaled by magnitude of `l`

    if (bScaled <= 0.f) // Before beginning of line, return distance to beginning
        return p.SquaredMagnitude();

    if (bScaled >= lineMagSq) // After end of line, return distance to end
        return (p - l).SquaredMagnitude();

    // Simple Pythagorean here, we gotta find side `a`

    const auto cSq = p.SquaredMagnitude();
    const auto bSq = bScaled * bScaled / lineMagSq; // Clever trick to divide by `l`'s magntiude without taking it's sqrt

    const auto aSq = cSq - bSq;
    return aSq;
}

/*!
* @address 0x412970
* @brief Similar to \r DistToLineSqr it always returns the distance to the projected intersection point.
*/
float CCollision::DistToMathematicalLine(CVector const* lineStart, CVector const* lineEnd, CVector const* point) {
    const auto l = *lineEnd - *lineStart;
    const auto p = *point - *lineStart;

    // See `DistToLineSqr` for a nice illustration.
    // Simple Pythagorean here, we gotta find side `a`

    const auto pMagSq = p.SquaredMagnitude();
    const auto cSq = pMagSq;
    const auto bSq = (float)std::pow(DotProduct(p, l), 2) / pMagSq; // Dot product is scaled by `pMagSq` - Clever trick to get descale it without using sqrt

    const auto aSq = cSq - bSq;
    return aSq > 0.0f ? std::sqrt(aSq) : 0.0f; // Little optimization to not call `sqrt` if the dist is 0 (it wont ever be negative)
}

/*!
* @address 0x412A30
* @brief Same as \r DistToMathematicalLine but in 2D
*/
float CCollision::DistToMathematicalLine2D(float lineStartX, float lineStartY, float lineEndX, float lineEndY, float pointX, float pointY) {
    const float px{ pointX - lineStartX }, py{ pointY - lineStartY };
    const auto  dot = px * lineEndX + py * lineEndY;
    const auto distSq = px * px + py * py - dot * dot;
    return distSq > 0.f ? std::sqrt(distSq) : 0.f;
}

/*!
* @address 0x412A80
* @brief TODO
*/
float CCollision::DistAlongLine2D(float lineX, float lineY, float lineDirX, float lineDirY, float pointX, float pointY) {
    return (pointX - lineX) * lineDirX + (pointY - lineY) * lineDirY;
}

/*!
* @address 0x412AA0
* @brief Process line sphere intersection - Doesn't deal well with cases where line starts/ends inside the sphere.
*
* @param[in,out] depth `t` parameter - relative distance on line from it's origin (`line.start`)
*/
bool CCollision::ProcessLineSphere(CColLine const& line, CColSphere const& sphere, CColPoint& colPoint, float& depth) {
    const auto l      = line.m_vecEnd - line.m_vecStart;
    const auto lmagsq = l.SquaredMagnitude();
    const auto sph    = sphere.m_vecCenter - line.m_vecStart;

    // Scaled by |l|
    const auto projLineMagScaled = DotProduct(l, sph);

    // Tanget of line to sphere centre
    const auto tanDistSq = sph.SquaredMagnitude() - (sphere.m_fRadius * sphere.m_fRadius);

    // `projLineMagScaled` is scaled by |l|, and the only way around it without using sqrt is to make both sides scaled by lmagsq
    // Scaled by |l|^2 (`lmagsq`)
    const auto distOnLineSqScaled = (projLineMagScaled * projLineMagScaled) - tanDistSq * lmagsq;

    if (distOnLineSqScaled < 0.f) { // Line doesn't intersect sphere
        return false;
    }

    const auto t = (projLineMagScaled - std::sqrt(distOnLineSqScaled)) / lmagsq; // Interpolation on the line
    if (t < 0.f || t > 1.f || t >= depth) {
        return false;
    }

    colPoint.m_vecPoint = line.m_vecStart + l * t;
    colPoint.m_vecNormal = Normalized(colPoint.m_vecPoint - sphere.m_vecCenter); // A little different from the original, but same effect

    colPoint.m_nSurfaceTypeB = sphere.m_nMaterial;
    colPoint.m_nLightingB = sphere.m_nLighting;

    colPoint.m_nSurfaceTypeA = eSurfaceType::SURFACE_DEFAULT;
    colPoint.m_nLightingA = 0;

    depth = t;

    ms_iProcessLineNumCrossings += 2;

    return true;
}

// 0x412C70
// Maybe just adapt the code from: http://www.3dkingdoms.com/weekly/weekly.php?a=3 ? Looks nicer than this one
bool CCollision::TestLineBox_DW(CColLine const& line, CBox const& box) {
    const auto IsInBox = [bb = CBoundingBox(box)](const CVector& point) {
        return bb.IsPointWithin(point);
    };

    // Quick early exit if any of the line are in the box
    if (IsInBox(line.m_vecStart) || IsInBox(line.m_vecEnd))
        return true;

    float x, y, z, t;

    // check if points are on opposite sides of min x plane
    if ((box.m_vecMin.x - line.m_vecEnd.x) * (box.m_vecMin.x - line.m_vecStart.x) < 0.0f) {
        // parameter along line where we intersect
        t = (box.m_vecMin.x - line.m_vecStart.x) / (line.m_vecEnd.x - line.m_vecStart.x);
        // y of intersection
        y = line.m_vecStart.y + (line.m_vecEnd.y - line.m_vecStart.y) * t;
        if (y > box.m_vecMin.y && y < box.m_vecMax.y) {
            // z of intersection
            z = line.m_vecStart.z + (line.m_vecEnd.z - line.m_vecStart.z) * t;
            if (z > box.m_vecMin.z && z < box.m_vecMax.z)
                return true;
        }
    }

    // same test with max x plane
    if ((line.m_vecEnd.x - box.m_vecMax.x) * (line.m_vecStart.x - box.m_vecMax.x) < 0.0f) {
        t = (line.m_vecStart.x - box.m_vecMax.x) / (line.m_vecStart.x - line.m_vecEnd.x);
        y = line.m_vecStart.y + (line.m_vecEnd.y - line.m_vecStart.y) * t;
        if (y > box.m_vecMin.y && y < box.m_vecMax.y) {
            z = line.m_vecStart.z + (line.m_vecEnd.z - line.m_vecStart.z) * t;
            if (z > box.m_vecMin.z && z < box.m_vecMax.z)
                return true;
        }
    }

    // min y plne
    if ((box.m_vecMin.y - line.m_vecStart.y) * (box.m_vecMin.y - line.m_vecEnd.y) < 0.0f) {
        t = (box.m_vecMin.y - line.m_vecStart.y) / (line.m_vecEnd.y - line.m_vecStart.y);
        x = line.m_vecStart.x + (line.m_vecEnd.x - line.m_vecStart.x) * t;
        if (x > box.m_vecMin.x && x < box.m_vecMax.x) {
            z = line.m_vecStart.z + (line.m_vecEnd.z - line.m_vecStart.z) * t;
            if (z > box.m_vecMin.z && z < box.m_vecMax.z)
                return true;
        }
    }

    // max y plane
    if ((line.m_vecStart.y - box.m_vecMax.y) * (line.m_vecEnd.y - box.m_vecMax.y) < 0.0f) {
        t = (line.m_vecStart.y - box.m_vecMax.y) / (line.m_vecStart.y - line.m_vecEnd.y);
        x = line.m_vecStart.x + (line.m_vecEnd.x - line.m_vecStart.x) * t;
        if (x > box.m_vecMin.x && x < box.m_vecMax.x) {
            z = line.m_vecStart.z + (line.m_vecEnd.z - line.m_vecStart.z) * t;
            if (z > box.m_vecMin.z && z < box.m_vecMax.z)
                return true;
        }
    }

    // min z plne
    if ((box.m_vecMin.z - line.m_vecStart.z) * (box.m_vecMin.z - line.m_vecEnd.z) < 0.0f) {
        t = (box.m_vecMin.z - line.m_vecStart.z) / (line.m_vecEnd.z - line.m_vecStart.z);
        x = line.m_vecStart.x + (line.m_vecEnd.x - line.m_vecStart.x) * t;
        if (x > box.m_vecMin.x && x < box.m_vecMax.x) {
            y = line.m_vecStart.y + (line.m_vecEnd.y - line.m_vecStart.y) * t;
            if (y > box.m_vecMin.y && y < box.m_vecMax.y)
                return true;
        }
    }

    // max z plane
    if ((line.m_vecStart.z - box.m_vecMax.z) * (line.m_vecEnd.z - box.m_vecMax.z) < 0.0f) {
        t = (line.m_vecStart.z - box.m_vecMax.z) / (line.m_vecStart.z - line.m_vecEnd.z);
        x = line.m_vecStart.x + (line.m_vecEnd.x - line.m_vecStart.x) * t;
        if (x > box.m_vecMin.x && x < box.m_vecMax.x) {
            y = line.m_vecStart.y + (line.m_vecEnd.y - line.m_vecStart.y) * t;
            if (y > box.m_vecMin.y && y < box.m_vecMax.y)
                return true;
        }
    }

    return false;
}

// 0x413070
bool CCollision::TestLineBox(CColLine const& line, CBox const& box) {
    return TestLineBox_DW(line, box);
}

/*!
* @address 0x413080
* @brief Test vertical \a line against \a box
*/
bool CCollision::TestVerticalLineBox(CColLine const& line, CBox const& box) {
    for (auto i = 0u; i < 2u; i++) { // Deal with x, y axies
        if (   line.m_vecStart[i] <= box.m_vecMin[i]
            || line.m_vecStart[i] >= box.m_vecMax[i]
        ) {
            return false;
        }
    }

    // Line might go from top to bottom, or from bottom to top, so we have to account for both cases
    const auto [minz, maxz] = std::minmax(line.m_vecStart.z, line.m_vecEnd.z);
    return minz <= box.m_vecMax.z && maxz >= box.m_vecMin.z;
}

// 0x413100
/*!
* @address 0x413100
* @brief Process \a line and \a box collision.
*
* @param[out]    colPoint         Collision point
* @param[in,out] maxTouchDistance Collision point depth inside box - If calculated value is higher than this value the function will return false, and no colpoint will be set.
*
* @returns If there was a collision or not. If there was a collision, but calculated depth is bigger than `maxTouchDistance` it returns false regardless.
*/
bool CCollision::ProcessLineBox(CColLine const& line, CColBox const& box, CColPoint& colPoint, float& maxTouchDistance) {
    float mint, t, x, y, z;
    CVector normal;
    CVector p;

    mint = 1.0f;
    // check if points are on opposite sides of min x plane
    if ((box.m_vecMin.x - line.m_vecEnd.x) * (box.m_vecMin.x - line.m_vecStart.x) < 0.0f) {
        // parameter along line where we intersect
        t = (box.m_vecMin.x - line.m_vecStart.x) / (line.m_vecEnd.x - line.m_vecStart.x);
        // y of intersection
        y = line.m_vecStart.y + (line.m_vecEnd.y - line.m_vecStart.y) * t;
        if (y > box.m_vecMin.y && y < box.m_vecMax.y) {
            // z of intersection
            z = line.m_vecStart.z + (line.m_vecEnd.z - line.m_vecStart.z) * t;
            if (z > box.m_vecMin.z && z < box.m_vecMax.z)
                if (t < mint) {
                    mint = t;
                    p = CVector(box.m_vecMin.x, y, z);
                    normal = CVector(-1.0f, 0.0f, 0.0f);
                }
        }
    }

    // max x plane
    if ((line.m_vecEnd.x - box.m_vecMax.x) * (line.m_vecStart.x - box.m_vecMax.x) < 0.0f) {
        t = (line.m_vecStart.x - box.m_vecMax.x) / (line.m_vecStart.x - line.m_vecEnd.x);
        y = line.m_vecStart.y + (line.m_vecEnd.y - line.m_vecStart.y) * t;
        if (y > box.m_vecMin.y && y < box.m_vecMax.y) {
            z = line.m_vecStart.z + (line.m_vecEnd.z - line.m_vecStart.z) * t;
            if (z > box.m_vecMin.z && z < box.m_vecMax.z)
                if (t < mint) {
                    mint = t;
                    p = CVector(box.m_vecMax.x, y, z);
                    normal = CVector(1.0f, 0.0f, 0.0f);
                }
        }
    }

    // min y plne
    if ((box.m_vecMin.y - line.m_vecStart.y) * (box.m_vecMin.y - line.m_vecEnd.y) < 0.0f) {
        t = (box.m_vecMin.y - line.m_vecStart.y) / (line.m_vecEnd.y - line.m_vecStart.y);
        x = line.m_vecStart.x + (line.m_vecEnd.x - line.m_vecStart.x) * t;
        if (x > box.m_vecMin.x && x < box.m_vecMax.x) {
            z = line.m_vecStart.z + (line.m_vecEnd.z - line.m_vecStart.z) * t;
            if (z > box.m_vecMin.z && z < box.m_vecMax.z)
                if (t < mint) {
                    mint = t;
                    p = CVector(x, box.m_vecMin.y, z);
                    normal = CVector(0.0f, -1.0f, 0.0f);
                }
        }
    }

    // max y plane
    if ((line.m_vecStart.y - box.m_vecMax.y) * (line.m_vecEnd.y - box.m_vecMax.y) < 0.0f) {
        t = (line.m_vecStart.y - box.m_vecMax.y) / (line.m_vecStart.y - line.m_vecEnd.y);
        x = line.m_vecStart.x + (line.m_vecEnd.x - line.m_vecStart.x) * t;
        if (x > box.m_vecMin.x && x < box.m_vecMax.x) {
            z = line.m_vecStart.z + (line.m_vecEnd.z - line.m_vecStart.z) * t;
            if (z > box.m_vecMin.z && z < box.m_vecMax.z)
                if (t < mint) {
                    mint = t;
                    p = CVector(x, box.m_vecMax.y, z);
                    normal = CVector(0.0f, 1.0f, 0.0f);
                }
        }
    }

    // min z plne
    if ((box.m_vecMin.z - line.m_vecStart.z) * (box.m_vecMin.z - line.m_vecEnd.z) < 0.0f) {
        t = (box.m_vecMin.z - line.m_vecStart.z) / (line.m_vecEnd.z - line.m_vecStart.z);
        x = line.m_vecStart.x + (line.m_vecEnd.x - line.m_vecStart.x) * t;
        if (x > box.m_vecMin.x && x < box.m_vecMax.x) {
            y = line.m_vecStart.y + (line.m_vecEnd.y - line.m_vecStart.y) * t;
            if (y > box.m_vecMin.y && y < box.m_vecMax.y)
                if (t < mint) {
                    mint = t;
                    p = CVector(x, y, box.m_vecMin.z);
                    normal = CVector(0.0f, 0.0f, -1.0f);
                }
        }
    }

    // max z plane
    if ((line.m_vecStart.z - box.m_vecMax.z) * (line.m_vecEnd.z - box.m_vecMax.z) < 0.0f) {
        t = (line.m_vecStart.z - box.m_vecMax.z) / (line.m_vecStart.z - line.m_vecEnd.z);
        x = line.m_vecStart.x + (line.m_vecEnd.x - line.m_vecStart.x) * t;
        if (x > box.m_vecMin.x && x < box.m_vecMax.x) {
            y = line.m_vecStart.y + (line.m_vecEnd.y - line.m_vecStart.y) * t;
            if (y > box.m_vecMin.y && y < box.m_vecMax.y)
                if (t < mint) {
                    mint = t;
                    p = CVector(x, y, box.m_vecMax.z);
                    normal = CVector(0.0f, 0.0f, 1.0f);
                }
        }
    }

    if (mint >= maxTouchDistance)
        return false;

    colPoint.m_vecPoint = p;
    colPoint.m_vecNormal = normal;

    colPoint.m_nSurfaceTypeA = eSurfaceType::SURFACE_DEFAULT;
    colPoint.m_nLightingA = 0;

    colPoint.m_nSurfaceTypeB = box.m_nMaterial;
    colPoint.m_nLightingB = box.m_nLighting;

    maxTouchDistance = mint;

    return true;
}

/*!
* @address 0x4138D0
* @returns If there was an intersection - TODO: What if lines are colinear?
*/
bool CCollision::Test2DLineAgainst2DLine(float line1StartX, float line1StartY, float line1EndX, float line1EndY, float line2StartX, float line2StartY, float line2EndX, float line2EndY) {
    return ((line2StartX - line1StartX + line2EndX) * line1EndY - (line2StartY - line1StartY + line2EndY) * line1EndX)
        * ((line2StartX - line1StartX) * line1EndY - (line2StartY - line1StartY) * line1EndX) <= 0.0
        &&
        ((line1StartX - line2StartX + line1EndX) * line2EndY - (line1StartY - line2StartY + line1EndY) * line2EndX)
        * ((line1StartX - line2StartX) * line2EndY - (line1StartY - line2StartY) * line2EndX) <= 0.0;
}

/*
* @address 0x413960
* @brief Used in the original ProcessColModels code. SA doesn't uses disks, so I won't bother with this function :D
* @returns I dont know
*/
// 0x413960
bool ProcessDiscCollision(CColPoint& colPoint1, const CMatrix& mat, const CColDisk& disk, CColPoint& colPoint2, bool& arg4, float& arg5, CColPoint& colPoint3) {
    return plugin::CallAndReturn<bool, 0x413960, CColPoint&, const CMatrix&, const CColDisk&, CColPoint&, bool&, float&, CColPoint&>(colPoint1, mat, disk, colPoint2, arg4, arg5,
                                                                                                                                     colPoint3);
}

// 0x413AC0
/*!
* @address 0x413AC0
*/
bool CCollision::TestLineTriangle(const CColLine& line, const CompressedVector* verts, const CColTriangle& tri, const CColTrianglePlane& triPlane) {
    return plugin::CallAndReturn<bool, 0x413AC0, const CColLine&, const CompressedVector*, const CColTriangle&, const CColTrianglePlane&>(line, verts, tri, triPlane);
}

/*!
* @address 0x4140F0
* @Processes \a line \a tri collision.
*
* @param[out]    colPoint         Collision point
* @param[in,out] maxTouchDistance Distance from line origin to intersection point
* @pram[out]     collPoly         If given (can be null) stored the uncompressed vertices of the triangle and set's it's `actual` field to `true`
*
* @returns If there was a collision or not. If there was a collision, but calculated touch distance is bigger than `maxTouchDistance` it returns false regardless.
*/
bool CCollision::ProcessLineTriangle(const CColLine& line, const CompressedVector* verts, const CColTriangle& tri, const CColTrianglePlane& triPlane, CColPoint& colPoint, float& maxTouchDistance, CStoredCollPoly* collPoly) {
    return plugin::CallAndReturn<bool, 0x4140F0, const CColLine&, const CompressedVector*, const CColTriangle&, const CColTrianglePlane&, CColPoint&, float&, CStoredCollPoly*>(line, verts, tri, triPlane, colPoint, maxTouchDistance, collPoly);
}

// 0x4147E0
bool CCollision::ProcessVerticalLineTriangle(const CColLine& line, const CompressedVector* verts, const CColTriangle& tri, const CColTrianglePlane& triPlane, CColPoint& colPoint,
                                             float& maxTouchDistance, CStoredCollPoly* collPoly) {
    return plugin::CallAndReturn<bool, 0x4147E0, const CColLine&, const CompressedVector*, const CColTriangle&, const CColTrianglePlane&, CColPoint&, float&, CStoredCollPoly*>(
        line, verts, tri, triPlane, colPoint, maxTouchDistance, collPoly);
}

// 0x414D70
bool CCollision::IsStoredPolyStillValidVerticalLine(const CVector& lineOrigin, float lineDist, CColPoint& colPoint, CStoredCollPoly* collPoly) {
    return plugin::CallAndReturn<bool, 0x414D70, const CVector&, float, CColPoint&, CStoredCollPoly*>(lineOrigin, lineDist, colPoint, collPoly);
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

    if (colData->m_pTrianglePlanes) {
        auto* link = colData->GetLinkPtr();
        link->Remove();
        ms_colModelCache.usedListHead.Insert(link);
    } else {
        auto* link = ms_colModelCache.Insert(colData);
        if (!link) {
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
    return plugin::CallAndReturn<bool, 0x416450, const CColSphere&, const CColSphere&, CColPoint&, float&>(sphere1, sphere2, colPoint, maxTouchDistance);
}

// 0x4165B0
bool CCollision::TestSphereTriangle(const CColSphere& sphere, const CompressedVector* verts, const CColTriangle& tri, const CColTrianglePlane& triPlane) {
    return plugin::CallAndReturn<bool, 0x4165B0, const CColSphere&, const CompressedVector*, const CColTriangle&, const CColTrianglePlane&>(sphere, verts, tri, triPlane);
}

// 0x416BA0
bool CCollision::ProcessSphereTriangle(const CColSphere& sphere, const CompressedVector* verts, const CColTriangle& tri, const CColTrianglePlane& triPlane, CColPoint& colPoint,
                                       float& maxTouchDistance) {
    return plugin::CallAndReturn<bool, 0x416BA0, const CColSphere&, const CompressedVector*, const CColTriangle&, const CColTrianglePlane&, CColPoint&, float&>(
        sphere, verts, tri, triPlane, colPoint, maxTouchDistance);
}

// 0x417470
bool CCollision::TestLineSphere(const CColLine& line, const CColSphere& sphere) {
    return plugin::CallAndReturn<bool, 0x417470, const CColLine&, const CColSphere&>(line, sphere);
}

// 0x417610
float CCollision::DistToLine(const CVector& lineStart, const CVector& lineEnd, const CVector& point) {
    return plugin::CallAndReturn<float, 0x417610, const CVector&, const CVector&, const CVector&>(lineStart, lineEnd, point);
}

// 0x417730
bool CCollision::TestLineOfSight(const CColLine& line, const CMatrix& transform, CColModel& colModel, bool doSeeThroughCheck, bool doShootThroughCheck) {
    return plugin::CallAndReturn<bool, 0x417730, const CColLine&, const CMatrix&, CColModel&, bool, bool>(line, transform, colModel, doSeeThroughCheck, doShootThroughCheck);
}

// 0x417950
bool CCollision::ProcessLineOfSight(const CColLine& line, const CMatrix& transform, CColModel& colModel, CColPoint& colPoint, float& maxTouchDistance, bool doSeeThroughCheck,
                                    bool doShootThroughCheck) {
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
        return (!doSeeThroughCheck || !g_surfaceInfos.IsSeeThrough(material)) && (!doShootThroughCheck || !g_surfaceInfos.IsShootThrough(material));
    };

    float localMinTouchDist = maxTouchDistance;

    bool results{};
    for (auto i = 0; i < colData->m_nNumSpheres; i++) {
        if (const auto& sphere = colData->m_pSpheres[i]; CheckSeeAndShootThrough(sphere.m_Surface.m_nMaterial)) {
            results |= ProcessLineSphere(line_OS, sphere, colPoint, localMinTouchDist);
        }
    }

    for (auto i = 0; i < colData->m_nNumBoxes; i++) {
        if (const auto& box = colData->m_pBoxes[i]; CheckSeeAndShootThrough(box.m_Surface.m_nMaterial)) {
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

    if (localMinTouchDist < maxTouchDistance) {
        colPoint.m_vecPoint = MultiplyMatrixWithVector(transform, colPoint.m_vecPoint);
        colPoint.m_vecNormal = Multiply3x3(transform, colPoint.m_vecNormal);
        maxTouchDistance = localMinTouchDist;
        return true;
    }
    return false;
}

// 0x417BF0
bool CCollision::ProcessVerticalLine(const CColLine& line, const CMatrix& transform, CColModel& colModel, CColPoint& colPoint, float& maxTouchDistance, bool doSeeThroughCheck,
                                     bool doShootThroughCheck, CStoredCollPoly* collPoly) {
    return plugin::CallAndReturn<bool, 0x417BF0, const CColLine&, const CMatrix&, CColModel&, CColPoint&, float&, bool, bool, CStoredCollPoly*>(
        line, transform, colModel, colPoint, maxTouchDistance, doSeeThroughCheck, doShootThroughCheck, collPoly);
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
    if (colModel->m_pColData && colModel->m_pColData->m_pTriangles) {
        assert(colModel->m_pColData->m_pTrianglePlanes); // If model has triangles it should also have planes by now (otherwise random crashes will occour)
    }
}

// 0x4185A0
void CCollision::RemoveTrianglePlanes(CColModel* colModel) {
    plugin::Call<0x4185A0, CColModel*>(colModel);
}

// TODO: This function could be refactored to use ranges instead of these ugly static variables :D
/*!
 * @brief 0x4185C0 Calculate collisions between \a cmA and \a cmB.
 *
 * Collisions calculated:
 *  A\B  Tri Sp  Box Lines
 * Tri       +
 * Sp    +   +   +
 * Box       +
 * Lines +   +   +
 *
 * Note: Originally the game calculated some disk stuff as well, but SA doesn't use disks (they're disabled when loadedin CFileLoader)
 * thus I omitted the code for it (it would've made the already messy code even worse)
 *
 * @param         transformA       Transformation matrix of model A - Usually owning entity's matrix.
 * @param         cmA              Col model A
 * @param         transformB       Transformation matrix of model B - Usually owning entity's matrix.
 * @param         cmA              Col model B
 * @param[out]    lineCPs          Line collision points (At most 16 - It can be null if you're sure the model has no lines)
 * @param[out]    sphereCPs        Sphere collision points (At most 32)
 * @param[in,out] maxTouchDistance Only used if model has lines - If you're sure it has none it can be null.
 * @param         arg7             Not 100% sure how to explain what this does. TODO.
 *
 * @returns Number of sphere collision points found (At most ~~32~~ 31 - Original function is buggy)
 */
int32 CCollision::ProcessColModels(const CMatrix& transformA, CColModel& cmA, const CMatrix& transformB, CColModel& cmB, CColPoint (&sphereCPs)[32], CColPoint* lineCPs,
                                   float* maxTouchDistance, bool arg7) {
    return plugin::CallAndReturn<int32, 0x4185C0, const CMatrix&, CColModel&, const CMatrix&, CColModel&, CColPoint(&)[32], CColPoint*, float*, bool>(
        transformA, cmA, transformB, cmB, sphereCPs, lineCPs, maxTouchDistance, arg7);

    // Don't these this should ever happen, but okay?
    if (!cmA.m_pColData) {
        return 0;
    }

    if (!cmB.m_pColData) {
        return 0;
    }

    const auto& cdA = *cmA.m_pColData;
    const auto& cdB = *cmB.m_pColData;

    // Transform matrix from A's space to B's
    const auto transformAtoB = Invert(transformB) * transformA;

    // A's bounding box in B's space
    const CColSphere colABoundSphereSpaceB{MultiplyMatrixWithVector(transformAtoB, cmA.m_boundSphere.m_vecCenter), cmA.m_boundSphere.m_fRadius};

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
    constexpr auto MAX_LINES{ 16u };    // Game didn't originally check for this, so I assume no models ever have more than 16 lines.

    // Transform `spheres` center position using `transform` and store them in `outSpheres`
    const auto TransformSpheres = []<size_t N>(auto&& spheres, const CMatrix& transform, CColSphere(&outSpheres)[N]) {
        std::ranges::transform(spheres, outSpheres, [&](const auto& sp) {
            CColSphere transformed = sp;                                                   // Copy sphere
            transformed.m_vecCenter = MultiplyMatrixWithVector(transform, sp.m_vecCenter); // Set copy's center as the transformed point
            return transformed;
        });
    };

    // Test `spheres` against bounding box `bb` and store all colliding sphere's indices in `collidedIdxs`
    const auto TestSpheresAgainstBB = []<size_t N>(auto&& spheres, const auto& bb, uint32& numCollided, uint32(&collidedIdxs)[N]) {
        for (const auto& [i, sp] : notsa::enumerate(spheres)) {
            if (TestSphereBox(sp, bb)) {
                assert(numCollided < N); // Avoid out-of-bounds (Game originally didn't check)
                collidedIdxs[numCollided++] = (uint32)i;
            }
        }
    };

    // Transform both model's spheres into each other's space
    // then store all sphere's indices colliding with the other's bounding box

    // Process A

    // 0x418722
    static CColSphere sphA[MAX_SPHERES];
    TransformSpheres(cdA.GetSpheres(), transformAtoB, sphA);

    // 0x4187A1
    static uint32 collSphA[MAX_SPHERES];
    uint32 numCollSphA{};
    TestSpheresAgainstBB(std::span{sphA, cdA.m_nNumSpheres}, cmB.GetBoundingBox(), numCollSphA, collSphA);

    // Process B

    // 0x4187ED
    static CColSphere sphB[MAX_SPHERES];
    TransformSpheres(cdB.GetSpheres(), transformBtoA, sphB);

    // 0x418862
    static uint32 collSphB[MAX_SPHERES];
    uint32 numCollSphB{};
    TestSpheresAgainstBB(std::span{sphB, cdB.m_nNumSpheres}, cmA.GetBoundingBox(), numCollSphB, collSphB);

    if (!numCollSphA && !cdA.m_nNumLines && !numCollSphB) {
        return 0;
    }

    // 0x418902
    // Here the game tests collision of disks, but SA doesn't use disks, so I won't bother with it.
    assert(!cdB.bUsesDisks); // If this asserts then I was wrong and this part has to be reversed as well :D

    // 0x418A4E
    // Test B's boxes against A's bounding sphere
    static uint32 collBoxB[MAX_BOXES]; // Indices of B's boxes colliding with A's bounding sphere
    uint32 numCollBoxB{};
    for (auto&& [i, box] : notsa::enumerate(cdB.GetBoxes())) {
        if (TestSphereBox(colABoundSphereSpaceB, box)) {
            collBoxB[numCollBoxB++] = i;
            if (numCollBoxB >= MAX_BOXES) {
                break;
            }
        }
    }

    // 0x418B0F
    // Test B's triangles against A's bounding sphere
    static uint32 collTrisB[MAX_TRIS];
    uint32 numCollTrisB{};

    if (cdB.m_nNumTriangles) {
        CalculateTrianglePlanes(&cmB); // Moved check inside if (Doesn't make a difference practically)
        assert(cdB.m_pTrianglePlanes);

        // Process a single triangle
        const auto ProcessOneTri = [&](uint32 triIdx) {
            if (TestSphereTriangle(colABoundSphereSpaceB, cdB.m_pVertices, cdB.m_pTriangles[triIdx], cdB.m_pTrianglePlanes[triIdx])) {
                collTrisB[numCollTrisB++] = triIdx;
            }
        };

        if (cdB.bHasFaceGroups) { // Test by using face groups - Thanks to those who helped me figure this out :)
            // 0x418B23
            for (auto&& group : cdB.GetFaceGroups()) {
                if (TestSphereBox(colABoundSphereSpaceB, group.bb)) { // Quick BB check
                    for (auto i{group.first}; i <= group.last; i++) { // Check all triangles in this group
                        ProcessOneTri(i);
                    }
                }
            }
        } else { // Game checked here if B.m_nNumTriangles > 0, but that is a redundant check.
            // 0x418C40
            for (auto i = 0u; i < cdB.m_nNumTriangles; i++) {
                ProcessOneTri(i);
            }
        }
    }

    if (!numCollSphA && !numCollTrisB && !numCollSphB) {
        return 0;
    }

    // 0x418CAD
    // Process all of A's colliding spheres against all of B's colliding spheres, boxes and triangles
    sphereCPs[0].m_fDepth = -1.f;
    uint32 nNumSphereCPs{};
    if (numCollSphA) {
        for (auto sphereAIdx : std::span{collSphA, numCollSphA}) {
            assert(cdA.m_pSpheres);
            assert(sphereAIdx < cdA.m_nNumSpheres);
            const auto& sphereA{sphA[sphereAIdx]}; // Sphere in B's space

            bool advanceColPointIdx{};
            float minTouchDist{1e24f};

            // 0x418CF9
            // Spheres
            for (auto sphereBIdx : std::span{collSphB, numCollSphB}) {
                assert(cdB.m_pSpheres);
                assert(sphereBIdx < cdB.m_nNumSpheres);
                const auto& sphereB{cdB.m_pSpheres[sphereBIdx]};

                if (ProcessSphereSphere(sphereA, sphereB, sphereCPs[nNumSphereCPs], minTouchDist)) {
                    advanceColPointIdx = true;
                    // These tests are cheap, so continue processing
                }

                // Original code also processed disk's spheres here (which were added to `colBCollSpheres` above (I skipped that part as well :D))
                // But since the game doesn't use disks we skip this part.
            }

            // 0x418D86
            // Boxes
            for (auto boxIdx : std::span{collBoxB, numCollBoxB}) {
                const auto& box{cdB.m_pBoxes[boxIdx]};
                auto& cp = sphereCPs[nNumSphereCPs];

                if (ProcessSphereBox(sphereA, box, cp, minTouchDist)) {
                    cp.m_nSurfaceTypeA = box.m_Surface.m_nMaterial;
                    cp.m_nPieceTypeA = box.m_Surface.m_nPiece;
                    cp.m_nLightingA = box.m_Surface.m_nLighting;

                    if (arg7 && sphereA.m_Surface.m_nPiece <= 2 && nNumSphereCPs < std::size(sphereCPs)) {
                        advanceColPointIdx = false;
                        minTouchDist = 1e24f;
                        sphereCPs[nNumSphereCPs + 1].m_fDepth = -1.f;
                        nNumSphereCPs++;
                    } else {
                        advanceColPointIdx = true;
                    }
                }
            }

            // 0x418E44
            // Triangles
            for (auto triIdx : std::span{collTrisB, numCollTrisB}) {
                auto& cp = sphereCPs[nNumSphereCPs];

                if (ProcessSphereTriangle(sphereA, cdB.m_pVertices, cdB.m_pTriangles[triIdx], cdB.m_pTrianglePlanes[triIdx], cp, minTouchDist)) {
                    // Same code as above in boxes
                    if (arg7 && sphereA.m_Surface.m_nPiece <= 2 && nNumSphereCPs < std::size(sphereCPs)) {
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
                if (nNumSphereCPs + 1 >= std::size(sphereCPs)) { // BUG: Should preincrement here instead of + 1
                    break;
                }
                sphereCPs[nNumSphereCPs++].m_fDepth = -1.f; // Set next's depth
            }
        }

        // 0x41996E
        // Transform all colpoints into world space (Originally not here)
        for (auto&& cp : std::span{sphereCPs, nNumSphereCPs}) {
            cp.m_vecPoint = MultiplyMatrixWithVector(transformB, cp.m_vecPoint);
            cp.m_vecNormal = Multiply3x3(transformB, cp.m_vecNormal);
        }
    }

    // 0x418F4C
    assert(!cdA.bUsesDisks); // Again, game does something with disks.. or it would if it had any disks :D

    // 0x41996E
    // ColPoint transform - Moved into the `if` above

    // 0x4196B9
    // Test all of A's lines against all of B's colliding spheres, boxes and triangles,
    // and store colpoints for all lines (even if they didn't collide)
    // (I really don't understand how the caller will know which lines have collided?)
    if (cdA.m_nNumLines) {
        assert(maxTouchDistance);
        assert(lineCPs);
        assert(cdA.m_nNumLines <= MAX_LINES);

        // 0x419731 - Moved logic into loop (storing all lines in a separate array isn't necessary at all)
        // 0x419752 - Skipped this, as it just filled an array with 1:1 index mapping - Useless - They probably had some BB checking logic here?

        for (auto lineIdx = 0u; lineIdx < cdA.m_nNumLines; lineIdx++) {
            const CColLine lineA{
                // A's line in B's space
                MultiplyMatrixWithVector(transformAtoB, cdA.m_pLines[lineIdx].m_vecStart),
                MultiplyMatrixWithVector(transformAtoB, cdA.m_pLines[lineIdx].m_vecEnd),
            };

            // if (!TestLineSphere(line, CColSphere{ cmB.m_boundSphere })) { // NOTSA: Quick check to (possibly) speed things up
            //     continue;
            // }

            auto& thisLineCP{lineCPs[lineIdx]};
            auto& thisLineTochDist{maxTouchDistance[lineIdx]};

            bool hasCollided{}; // Instead of the static array we just use a variable (Same functionality)

            // 0x419799
            // Spheres
            for (auto&& spIdx : std::span{collSphB, numCollSphB}) {
                hasCollided |= ProcessLineSphere(lineA, cdB.m_pSpheres[spIdx], thisLineCP, thisLineTochDist);
            }

            // 0x419803
            // Boxes
            for (auto&& boxIdx : std::span{collBoxB, numCollBoxB}) {
                hasCollided |= ProcessLineBox(lineA, cdB.m_pBoxes[boxIdx], thisLineCP, thisLineTochDist);
            }

            // 0x419865
            // Triangles
            for (auto&& triIdx : std::span{collTrisB, numCollTrisB}) {
                hasCollided |= ProcessLineTriangle(lineA, cdB.m_pVertices, cdB.m_pTriangles[triIdx], cdB.m_pTrianglePlanes[triIdx], thisLineCP, thisLineTochDist, nullptr);
            }

            // 0x4198DA
            // Now, transform colpoint if it the line collided into world space
            if (hasCollided) {
                thisLineCP.m_vecPoint = MultiplyMatrixWithVector(transformB, thisLineCP.m_vecPoint);
                thisLineCP.m_vecNormal = Multiply3x3(transformB, thisLineCP.m_vecNormal);
            }
        }
    }

    // 0x4185C0
    // Originally game transformed all sphereCPs to world space here, but I've moved that into the above `if` stuff

    // 0x4199E5
    // Find all A's triangles and boxes colliding with B's b.sphere
    // Then process them all against B's colliding spheres
    if (numCollSphB && (cdA.m_nNumTriangles || cdA.m_nNumBoxes)) {
        const CColSphere colBSphereInASpace{MultiplyMatrixWithVector(transformBtoA, cmB.m_boundSphere.m_vecCenter), cmB.m_boundSphere.m_fRadius};

        const auto numCPsPrev{nNumSphereCPs};

        // Process all of A's triangles against B's b.sphere
        static uint32 collTriA[MAX_TRIS];
        uint32 numCollTriA{};
        if (cdA.m_nNumTriangles) {
            CalculateTrianglePlanes(&cmA);
            assert(cdA.m_pTrianglePlanes);

            // NOTE/TODO: Weird how they didn't use the facegroup stuff here as well.
            //            Should probably implement it here some day too, as it speeds up the process quite a bit.
            for (auto i = 0; i < cdA.m_nNumTriangles; i++) {
                if (TestSphereTriangle(colBSphereInASpace, cdA.m_pVertices, cdA.m_pTriangles[i], cdA.m_pTrianglePlanes[i])) {
                    collTriA[numCollTriA++] = i;
                }
            }
        }

        // 0x419AB6
        // Process all of A's boxes against B's b.sphere
        static uint32 collBoxA[MAX_TRIS];
        uint32 numCollBoxA{};
        for (auto i = 0; i < cdA.m_nNumBoxes; i++) {
            if (TestSphereBox(colBSphereInASpace, cdA.m_pBoxes[i])) {
                collBoxA[numCollBoxA++] = i;
            }
        }

        // 0x419B76
        // Process all of B's colliding spheres against all of A's colliding triangles
        for (auto sphereIdx : std::span{collSphB, numCollSphB}) {
            auto minTouchDist{1e24f};
            bool anyCollided{};
            for (auto triIdx : std::span{collTriA, numCollTriA}) {
                if (ProcessSphereTriangle(sphB[sphereIdx], // B's sph in A's space
                                          cdA.m_pVertices, cdA.m_pTriangles[triIdx], cdA.m_pTrianglePlanes[triIdx], sphereCPs[nNumSphereCPs], minTouchDist)) {
                    anyCollided = true;
                }
            }

            if (anyCollided) {
                sphereCPs[nNumSphereCPs].m_vecNormal *= -1.f;
                if (nNumSphereCPs + 1 >= std::size(sphereCPs)) { // BUG: Should preincrement here instead of + 1
                    break;
                }
                sphereCPs[nNumSphereCPs++].m_fDepth = -1.f; // Set next CP's depth
            }
        }

        // 0x419CC4
        // Process all of B's colliding spheres against all of A's colliding boxes
        for (auto sphereIdx : std::span{collSphB, numCollSphB}) {
            const auto& sphere{sphB[sphereIdx]}; // B's sphere in A's space

            float minTouchDist{1e24f};
            for (auto boxIdx : std::span{collBoxA, numCollBoxA}) {
                const auto& box{cdA.m_pBoxes[boxIdx]};
                auto& cp = sphereCPs[nNumSphereCPs];
                if (ProcessSphereBox(sphere, box, cp, minTouchDist)) {
                    cp.m_nSurfaceTypeA = box.m_Surface.m_nMaterial;
                    cp.m_nPieceTypeA = box.m_Surface.m_nPiece;
                    cp.m_nLightingA = box.m_Surface.m_nLighting;

                    cp.m_nSurfaceTypeB = sphere.m_Surface.m_nMaterial;
                    cp.m_nPieceTypeB = sphere.m_Surface.m_nPiece;
                    cp.m_nLightingB = sphere.m_Surface.m_nLighting;

                    cp.m_vecNormal *= -1.f; // Invert direction

                    if (nNumSphereCPs + 1 >= std::size(sphereCPs)) { // BUG: Should preincrement here instead of + 1
                        break;
                    }
                    sphereCPs[nNumSphereCPs++].m_fDepth = -1.f; // Set next CP's depth
                }
            }
        }

        // 0x419E56
        // Transform added colpoints into world space
        if (numCPsPrev != nNumSphereCPs) {                                                   // If we've processed any items..
            for (auto& cp : std::span{sphereCPs + numCPsPrev, nNumSphereCPs - numCPsPrev}) { // Transform all newly added colpoints
                cp.m_vecPoint = MultiplyMatrixWithVector(transformA, cp.m_vecPoint);
                cp.m_vecNormal = Multiply3x3(transformA, cp.m_vecNormal);

                // Weird stuff, idk why they do this
                cp.m_nSurfaceTypeB = cp.m_nSurfaceTypeA;
                cp.m_nPieceTypeB = cp.m_nPieceTypeA;
                cp.m_nLightingB = cp.m_nLightingA;
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
