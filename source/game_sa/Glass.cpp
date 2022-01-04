#include "StdInc.h"
#include "Glass.h"
#include "FallingGlassPane.h"
#include <numeric>
#include <ranges>
namespace rng = std::ranges;

CVector2D (&PanePolyPositions)[4][3] = *(CVector2D(*)[4][3])0x8D5CD8;
int32& CGlass::ReflectionPolyVertexBaseIdx = *(int32*)0xC71B18;
int32& CGlass::ReflectionPolyIndexBaseIdx = *(int32*)0xC71B1C;
int32& CGlass::ShatteredVerticesBaseIdx = *(int32*)0xC71B20;
int32& CGlass::ShatteredIndicesBaseIdx = *(int32*)0xC71B24;
uint32& CGlass::NumHiLightPolyVertices = *(uint32*)0xC71B28;
int32& CGlass::NumHiLightPolyIndices = *(int32*)0xC71B2C;
CVector2D (&PanePolyCenterPositions)[5] = *(CVector2D(*)[5])0xC71B30;
int32 (&CGlass::apEntitiesToBeRendered)[1] = *(int32(*)[1])0xC71B58;
int32& CGlass::NumGlassEntities = *(int32*)0xC71BD8;
CFallingGlassPane (&aGlassPanes)[44] = *(CFallingGlassPane(*)[44])0xC71BF8;
int32& CGlass::LastColCheckMS = *(int32*)0xC72FA8;

void CGlass::InjectHooks() {
    ReversibleHooks::Install("CGlass", "Init", 0x71A8D0, &CGlass::Init);
    // ReversibleHooks::Install("CGlass", "HasGlassBeenShatteredAtCoors", 0x71CB70, &CGlass::HasGlassBeenShatteredAtCoors);
    ReversibleHooks::Install("CGlass", "CarWindscreenShatters", 0x71C2B0, &CGlass::CarWindscreenShatters);
    // ReversibleHooks::Install("CGlass", "WasGlassHitByBullet", 0x71C0D0, &CGlass::WasGlassHitByBullet);
    // ReversibleHooks::Install("CGlass", "WindowRespondsToCollision", 0x71BC40, &CGlass::WindowRespondsToCollision);
    // ReversibleHooks::Install("CGlass", "GeneratePanesForWindow", 0x71B620, &CGlass::GeneratePanesForWindow);
    // ReversibleHooks::Install("CGlass", "Update", 0x71B0D0, &CGlass::Update);
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
    auto FindNextGlassTriangle = [&, idx = 0u]() mutable -> uint32 {
        for (; idx < colModel->GetTriCount(); idx++) {
            if (g_surfaceInfos->IsGlass(triangles[idx].m_nMaterial))
                return idx;
        }
        return -1u;
    };

    const uint32 glassTriIdx[]{ FindNextGlassTriangle(), FindNextGlassTriangle() };
    if (glassTriIdx[0] == -1u || glassTriIdx[1] == -1u)
        return;

    colModel->CalculateTrianglePlanes();

    auto& vehMat = (CMatrix&)pVeh->GetMatrix();

    // Grab normal and transform it to world space
    const auto normal = Multiply3x3(
        vehMat,
        colModel->m_pColData->m_pTrianglePlanes[glassTriIdx[0]].GetNormal()
    );

    // Calculate direction vectors
    const auto fwd   = Normalized(CrossProduct(vehMat.GetRight(), normal));
    const auto right = Normalized(CrossProduct(vehMat.GetUp(), normal));

    // Store world space vertex positions of both triangles
    CVector triVertices[6]{};
    for (auto t = 0; t < 2; t++) {
        const auto& tri = triangles[glassTriIdx[t]];
        for (auto v = 0; v < 3; v++) {
            triVertices[t * 3 + v] = MultiplyMatrixWithVector(
                vehMat,
                UncompressUnitVector(colModel->m_pColData->m_pVertices[tri.m_vertIndices[v]])
            );
        }
    }

    const auto CalculateDotProducts = [&](float(&out)[6], CVector direction) {
        for (auto i = 0; i < 6; i++) {
            out[i] = DotProduct(triVertices[i], direction);
        }
    };

    // Calculate dot products for all vertices on both direction vectors
    float rightDots[6]{};
    CalculateDotProducts(rightDots, right);

    float fwdDots[6]{};
    CalculateDotProducts(fwdDots, fwd);

    // Find min, max values
    float maxDotFwd = FLT_MIN, minDotRight = FLT_MAX, minRightFwdDotSum = FLT_MAX;
    uint32 minRightFwdDotSumIdx{};
    for (auto i = 0; i < 6; i++) {
        const auto rightDot = rightDots[i], fwdDot = fwdDots[i];

        maxDotFwd = std::max(maxDotFwd, fwdDot);
        minDotRight = std::min(minDotRight, rightDot);

        if (rightDot + fwdDot < minRightFwdDotSum) {
            minRightFwdDotSum = rightDot + fwdDot;
            minRightFwdDotSumIdx = i;
        }
    }

    const struct { float right, fwd; } size{
        minDotRight - rightDots[minRightFwdDotSumIdx],
        maxDotFwd - fwdDots[minRightFwdDotSumIdx]
    };

    const auto blPos = triVertices[minRightFwdDotSumIdx];
    GeneratePanesForWindow(
        2,
        blPos,
        fwd * size.fwd,
        right * size.right,
        pVeh->m_vecMoveSpeed,
        blPos + fwd * size.fwd / 2.f + right * size.right / 2.f,
        0.1f,
        false,
        false,
        2,
        true
    );
}

// 0x71C0D0
void CGlass::WasGlassHitByBullet(CEntity* pObj, CVector hitPos) {
    plugin::Call<0x71C0D0, CEntity*, CVector>(pObj, hitPos);
}

// 0x71BC40
void CGlass::WindowRespondsToCollision(CEntity* pEntity, float fDamageIntensity, CVector vecMoveSpeed, CVector vecPoint, bool a5) {
    return plugin::Call<0x71BC40, CEntity*, float, CVector, CVector, bool>(pEntity, fDamageIntensity, vecMoveSpeed, vecPoint, a5);
}

/*
 * 0x71B620
 *
 * Corners:
 * TL ----- TR
 * |  0 | 1 |
 * | ------ | fwdSize
 * |  2 | 3 |
 * BL ----- BR
 *  rightSize
 *
 * - Neither 'size' vectors are normalized!
 *
 * type                    - 0, 1, 2 - Undocumented yet
 * pos                     - BL
 * fwdSize, rightSize      - As illustrated above
 * center                  - The centre of the above rectangle (each pane is a piece of it)
 * velocity                - How fast the panes fly
 * velocityCenterDragCoeff - Modify the velocity's direction to be more towards the center point
 * bShatter                - Render shatter polys
 * numSectionsMax1         - Limit no. of sections to 1 - Unsure what's it use-case as setting `numSections` to 1 achieves the same
 * numSections             - No. of sections of each axis, the total number of sections will be `numSections ^ 2` (squared)
**/
void CGlass::GeneratePanesForWindow(uint32 type, CVector pos, CVector fwdSize, CVector rightSize, CVector velocity, CVector center, float velocityCenterDragCoeff,
                                    bool bShatter, bool numSectionsMax1, int32 numSections, bool unk) {
    plugin::Call<0x71B620, uint32, CVector, CVector, CVector, CVector, CVector, float, bool, bool, int32, bool>(
        type, pos, fwdSize, rightSize, velocity, center, velocityCenterDragCoeff, bShatter, numSectionsMax1, numSections, unk);
}

// 0x71B0D0
void CGlass::Update() {
    plugin::Call<0x71B0D0>();
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
