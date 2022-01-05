#include "StdInc.h"
#include "Glass.h"
#include "FallingGlassPane.h"
#include <numeric>
#include <ranges>
#include <array>
namespace rng = std::ranges;

CVector2D (&CGlass::PanePolyPositions)[4][3] = *(CVector2D(*)[4][3])0x8D5CD8;
int32& CGlass::ReflectionPolyVertexBaseIdx = *(int32*)0xC71B18;
int32& CGlass::ReflectionPolyIndexBaseIdx = *(int32*)0xC71B1C;
int32& CGlass::ShatteredVerticesBaseIdx = *(int32*)0xC71B20;
int32& CGlass::ShatteredIndicesBaseIdx = *(int32*)0xC71B24;
uint32& CGlass::NumHiLightPolyVertices = *(uint32*)0xC71B28;
int32& CGlass::NumHiLightPolyIndices = *(int32*)0xC71B2C;
CVector2D (&CGlass::PanePolyCenterPositions)[5] = *(CVector2D(*)[5])0xC71B30;
int32 (&CGlass::apEntitiesToBeRendered)[1] = *(int32(*)[1])0xC71B58;
int32& CGlass::NumGlassEntities = *(int32*)0xC71BD8;
CFallingGlassPane (&CGlass::aGlassPanes)[44] = *(CFallingGlassPane(*)[44])0xC71BF8;
int32& CGlass::LastColCheckMS = *(int32*)0xC72FA8;

void CGlass::InjectHooks() {
    ReversibleHooks::Install("CGlass", "Init", 0x71A8D0, &CGlass::Init);
    // ReversibleHooks::Install("CGlass", "HasGlassBeenShatteredAtCoors", 0x71CB70, &CGlass::HasGlassBeenShatteredAtCoors);
    ReversibleHooks::Install("CGlass", "CarWindscreenShatters", 0x71C2B0, &CGlass::CarWindscreenShatters);
    ReversibleHooks::Install("CGlass", "WasGlassHitByBullet", 0x71C0D0, &CGlass::WasGlassHitByBullet);
    ReversibleHooks::Install("CGlass", "WindowRespondsToCollision", 0x71BC40, &CGlass::WindowRespondsToCollision);
    ReversibleHooks::Install("CGlass", "GeneratePanesForWindow", 0x71B620, &CGlass::GeneratePanesForWindow);
    ReversibleHooks::Install("CGlass", "Update", 0x71B0D0, &CGlass::Update);
    // ReversibleHooks::Install("CGlass", "Render", 0x71CE20, &CGlass::Render);
    // ReversibleHooks::Install("CGlass", "FindWindowSectorList", 0x71AFC0, &CGlass::FindWindowSectorList);
    // ReversibleHooks::Install("CGlass", "RenderReflectionPolys", 0x71AED0, &CGlass::RenderReflectionPolys);
    // ReversibleHooks::Install("CGlass", "RenderShatteredPolys", 0x71AE30, &CGlass::RenderShatteredPolys);
    // ReversibleHooks::Install("CGlass", "RenderHiLightPolys", 0x71ADA0, &CGlass::RenderHiLightPolys);
    // ReversibleHooks::Install("CGlass", "CalcAlphaWithNormal", 0x71ACF0, &CGlass::CalcAlphaWithNormal);
    // ReversibleHooks::Install("CGlass", "AskForObjectToBeRenderedInGlass", 0x71ACD0, &CGlass::AskForObjectToBeRenderedInGlass);
    // ReversibleHooks::Install("CGlass", "FindFreePane", 0x71ACA0, &CGlass::FindFreePane);
    // ReversibleHooks::Install("CGlass", "WindowRespondsToSoftCollision", 0x71AF70, &CGlass::WindowRespondsToSoftCollision);
    // ReversibleHooks::Install("CGlass", "BreakGlassPhysically", 0x71CF50, &CGlass::BreakGlassPhysically);
}

// Static functions
// 0x71A8D0
void CGlass::Init() {
    for (auto& pane : aGlassPanes) {
        pane.existFlag = false;
    }

    for (auto i = 0u; i < std::size(PanePolyPositions); i++) {
        const auto& poly = PanePolyPositions[i];
        PanePolyCenterPositions[i] = std::accumulate(std::begin(poly), std::end(poly), CVector2D{}) / (float)std::size(PanePolyPositions);
    }
}

// 0x71CB70
// Unused
bool CGlass::HasGlassBeenShatteredAtCoors(CVector pos) {
    return plugin::CallAndReturn<bool, 0x71CB70, CVector>(pos);
}

// 0x71C2B0
void CGlass::CarWindscreenShatters(CVehicle* pVeh) {
    const auto colModel = pVeh->GetColModel();
    if (!colModel || colModel->GetTriCount() < 2) {
        return;
    }

    const auto& triangles = colModel->m_pColData->m_pTriangles;

    // Find the triangle of the glass rectangle
    // They're after each other, so we just have to find the first one here
    uint32_t glassTriIdx{};
    for (; glassTriIdx < colModel->GetTriCount(); glassTriIdx++) {
        if (g_surfaceInfos->IsGlass(triangles[glassTriIdx].m_nMaterial)) {
            break;
        }
    }

    // `glassTriIdx` is the first triangle of the glass rectangle, the second one is the one after it.
    // So, logically, if `glassTriIdx + 1` is valid, `glassTriIdx` is going to be valid as well.
    if (glassTriIdx + 1 >= colModel->GetTriCount())
        return;

    CCollision::CalculateTrianglePlanes(colModel);

    auto& vehMat = (CMatrix&)pVeh->GetMatrix();

    // Grab normal and transform it to world space
    const auto normal = Multiply3x3(
        vehMat,
        colModel->m_pColData->m_pTrianglePlanes[glassTriIdx].GetNormal()
    );

    // Calculate direction vectors
    const auto fwd   = Normalized(CrossProduct(vehMat.GetRight(), normal));
    const auto right = Normalized(CrossProduct(vehMat.GetUp(), normal));

    // Store world space vertex positions of both triangles
    CVector triVertices[6]{};
    for (auto t = 0; t < 2; t++) {
        const auto& tri = triangles[glassTriIdx + t];
        for (auto v = 0; v < 3; v++) {
            triVertices[t * 3 + v] = MultiplyMatrixWithVector(
                vehMat,
                UncompressVector(colModel->m_pColData->m_pVertices[tri.m_vertIndices[v]])
            );
        }
    }

    // Calculate dot products for both directions
    // The dot product of the position of a vertex and `right` will give it's "position" on the `right` axis
    // same goes for `fwd`

    const auto CalculateDotProducts = [&](CVector direction) {
        std::array<float, 6> out{};
        for (auto i = 0; i < 6; i++) {
            out[i] = DotProduct(triVertices[i], direction);
        }
        return out;
    };

    // Calculate dot products for all vertices on both direction vectors
    const auto rightDots = CalculateDotProducts(right);
    const auto fwdDots   = CalculateDotProducts(fwd);

    const float maxDotFwd   = *rng::max_element(fwdDots);
    const float maxDotRight = *rng::max_element(rightDots);

    float minRightFwdDotSum = FLT_MAX;
    uint32 minRightFwdDotSumIdx{};
    for (auto i = 0; i < 6; i++) {
        const auto rightDot = rightDots[i], fwdDot = fwdDots[i];
        if (rightDot + fwdDot < minRightFwdDotSum) {
            minRightFwdDotSum = rightDot + fwdDot;
            minRightFwdDotSumIdx = i;
        }
    }

    const struct { float right, fwd; } extent{
        maxDotRight - rightDots[minRightFwdDotSumIdx],
        maxDotFwd - fwdDots[minRightFwdDotSumIdx]
    };

    const auto blPos = triVertices[minRightFwdDotSumIdx];
    GeneratePanesForWindow(
        2,
        blPos,
        fwd * extent.fwd,
        right * extent.right,
        pVeh->m_vecMoveSpeed,
        blPos + fwd * extent.fwd / 2.f + right * extent.right / 2.f,
        0.1f,
        false,
        false,
        2,
        true
    );
}

// 0x71C0D0
void CGlass::WasGlassHitByBullet(CEntity* entity, CVector hitPos) {
    if (!entity->IsObject())
        return;

    if (!entity->m_bUsesCollision)
        return;

    const auto object = entity->AsObject();
    const auto MI = CModelInfo::GetModelInfo(object->m_nModelIndex)->AsAtomicModelInfoPtr();
    switch (MI->nSpecialType) {
    case eModelInfoSpecialType::GLASS_TYPE_1:
    case eModelInfoSpecialType::GLASS_TYPE_2: {
        if (object->objectFlags.bGlassBroken) {
            if (rand() % 4 == 2) {
                WindowRespondsToCollision(entity, 0.0f, {}, hitPos, false);
            }
        } else {
            object->objectFlags.bGlassBroken = true; // Just mark it as broken
        }
        break;
    }
    }
}

template<size_t N>
std::pair<float, float> FindMinMaxZOfVertices(CVector (&vertices)[N]) {
    float min = FLT_MAX, max = FLT_MIN;
    for (const auto& v : vertices) {
        min = std::min(min, v.z);
        max = std::max(max, v.z);
    }
    return { min, max };
}

// 0x71BC40
void CGlass::WindowRespondsToCollision(CEntity* pEntity, float fDamageIntensity, CVector vecMoveSpeed, CVector vecPoint, bool max1PaneSection) {
    auto object = pEntity->AsObject();
    if (!object->objectFlags.b0x20)
        return;

    object->objectFlags.bGlassBroken = true;

    if (const auto colModel = object->GetColModel(); colModel && colModel->GetTriCount() == 2) {
        // Object space vertices
        CVector verticesOS[4]{};
        for (auto i = 0; i < 4; i++) {
            verticesOS[i] = UncompressVector(colModel->m_pColData->m_pVertices[i]);
        }

        const auto [minZ, maxZ] = FindMinMaxZOfVertices(verticesOS);
        //const auto vert01MaxZ = std::

        uint32 furthestFromV0Idx{};
        {
            float max{ FLT_MIN };
            for (auto i = 1; i < 4; i++) {
                const auto dist = DistanceBetweenPoints2D(verticesOS[0], verticesOS[i]);
                if (dist > max) {
                    max = dist;
                    furthestFromV0Idx = i;
                }
            }
        }

        // Transform vertices to world space
        const auto vert01MinZ        = std::min(verticesOS[0].z, verticesOS[1].z);
        const auto vert0Pos          = Multiply3x3(object->GetMatrix(), { verticesOS[0].x, verticesOS[0].y, vert01MinZ });
        const auto furthestFromV0Pos = Multiply3x3(object->GetMatrix(), { verticesOS[furthestFromV0Idx].x, verticesOS[furthestFromV0Idx].y, vert01MinZ });

        AudioEngine.ReportGlassCollisionEvent(AE_GLASS_BREAK_FAST, object->GetPosition());
        GeneratePanesForWindow(fDamageIntensity <= 300.f ? 1 : 0, vert0Pos, { 0.f, 0.f, maxZ - minZ }, furthestFromV0Pos - vert0Pos, vecMoveSpeed, vecPoint, 0.1f, object->objectFlags.bGlassBroken, max1PaneSection, 1, false);
    }

}

/*
 * 0x71B620
 *
 * Corners:
 * TL ----- TR
 * |  0 | 1 |
 * | ------ | fwd
 * |  2 | 3 |
 * BL ----- BR
 *  right
 *
 * - Neither 'size' vectors are normalized!
 *
 * type                    - 0, 1, 2 - Undocumented yet
 * pos                     - BL
 * fwd, right      - As illustrated above
 * center                  - The centre of the above rectangle (each pane is a piece of it)
 * velocity                - How fast the panes fly
 * velocityCenterDragCoeff - Modify the velocity's direction to be more towards the center point
 * bShatter                - Render shatter polys
 * numSectionsMax1         - Limit no. of sections to 1 - Unsure what's it use-case as setting `numSections` to 1 achieves the same
 * numSections             - No. of sections of each axis, the total number of sections will be `numSections ^ 2` (squared)
**/
void CGlass::GeneratePanesForWindow(uint32 type, CVector pos, CVector fwd, CVector right, CVector velocity, CVector center, float velocityCenterDragCoeff,
                                    bool bShatter, bool numSectionsMax1, int32 numSections, bool unk) {

    const float totalSizeY = fwd.Magnitude(), totalSizeX = right.Magnitude();


    // Calculate no. of sections, and section size
    const auto CalculateCountOfSectionsAndSizeAxis = [&](auto axisSize) {
        const auto count = numSectionsMax1 ? 1 : std::min(numSections * (uint32)(axisSize + 0.75f/*make it round upwards*/), 3u);
        return std::make_pair(count, axisSize / (float)count);
    };

    const auto [countX, sizeX] = CalculateCountOfSectionsAndSizeAxis(totalSizeX);
    const auto [countY, sizeY] = CalculateCountOfSectionsAndSizeAxis(totalSizeY);

    //printf("Panes: %u x %u (%.3f x %.3f) \n", countX, countY, sizeX, sizeY);

    bool hitGround{};
    float groundZ = CWorld::FindGroundZFor3DCoord(pos.x, pos.y, pos.z, &hitGround, nullptr);
    if (!hitGround)
        groundZ = pos.z - 2.f;

    if (!countY)
        return;

    for (auto posY = 0u; posY < countY; posY++) {
        for (auto posX = 0u; posX < countX; posX++) {
            for (auto piece = 0u; piece < 5u; piece++) {
                if (auto pane = FindFreePane()) {
                    pane->nPieceIndex = piece;

                    // Calculate matrix
                    auto& mat = pane->matrix;
                    mat.GetRight() = Normalized(right) * sizeX;
                    mat.GetUp() = Normalized(fwd) * sizeY;
                    mat.GetForward() = Normalized(CrossProduct(mat.GetRight(), mat.GetUp()));

                    const auto paneCenterPos = PanePolyCenterPositions[piece] * CVector2D{ sizeX, sizeY } + CVector2D{(float)posX, (float)posY};
                    mat.GetPosition() = pos + Normalized(fwd) * paneCenterPos.y + Normalized(right) * paneCenterPos.x;

                    {
                        constexpr auto RandomFactor = [] {return (float)((rand() % 128) - 64) * 0.0015f; };
                        pane->velocity = velocity + CVector{ RandomFactor(), RandomFactor(), 0.f };
                    }

                    if (velocityCenterDragCoeff != 0.0f) {
                        pane->velocity += Normalized(mat.GetPosition() - center) * velocityCenterDragCoeff;
                    }

                    {
                        constexpr auto RandomFactor = [] { return (float)((rand() % 128) - 64) / 500.f; }; // Random number in range (-0.128, 0.128)
                        pane->randomNumbers = CVector{ RandomFactor(), RandomFactor(), RandomFactor() };
                    }

                    switch (type) {
                    case 1: {
                        pane->createdTime = CTimer::GetTimeInMS() + (uint32)((mat.GetPosition() - center).Magnitude() * 100.f);
                        break;
                    }
                    case 2:
                    default: {
                        pane->createdTime = CTimer::GetTimeInMS();
                        break;
                    }
                    }

                    pane->groundZ = groundZ;
                    pane->bRenderShatter = bShatter;
                    pane->size = sizeY;
                    pane->field_6F = unk;
                    pane->existFlag = true;
                }
            }

        }
    }
}

// 0x71B0D0
void CGlass::Update() {
    for (auto& pane : aGlassPanes) {
        if (pane.existFlag) {
            pane.Update();
        }
    }
}

// 0x71CE20
void CGlass::Render() {
    plugin::Call<0x71CE20>();
}

// 0x71AFC0
void CGlass::FindWindowSectorList(CPtrList& objList, float& outDist, CEntity*& outEntity, CVector point) {
    plugin::Call<0x71AFC0, CPtrList&, float&, CEntity*&, CVector>(objList, outDist, outEntity, point);
}

// 0x71AED0
void CGlass::RenderReflectionPolys() {
    plugin::Call<0x71AED0>();
}

// 0x71AE30
void CGlass::RenderShatteredPolys() {
    plugin::Call<0x71AE30>();
}

// 0x71ADA0
void CGlass::RenderHiLightPolys() {
    plugin::Call<0x71ADA0>();
}

// 0x71ACF0
uint8 CGlass::CalcAlphaWithNormal(CVector* normal) {
    return plugin::CallAndReturn<uint8, 0x71ACF0, CVector*>(normal);
}

// 0x71ACD0
void CGlass::AskForObjectToBeRenderedInGlass(CEntity* a1) {
    plugin::Call<0x71ACD0, CEntity*>(a1);
}

// 0x71ACA0
CFallingGlassPane* CGlass::FindFreePane() {
    return plugin::CallAndReturn<CFallingGlassPane*, 0x71ACA0>();
}

// 0x71AF70
void CGlass::WindowRespondsToSoftCollision(CEntity* pEntity, float fDamageIntensity) {
    plugin::Call<0x71AF70, CEntity*, float>(pEntity, fDamageIntensity);
}

// 0x71CF50
void CGlass::BreakGlassPhysically(CVector pos, float radius) {
    plugin::Call<0x71CF50, CVector, float>(pos, radius);
}
