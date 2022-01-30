#include "StdInc.h"
#include "Glass.h"
#include "FallingGlassPane.h"
#include <numeric>
#include <ranges>
#include <array>
#include <functional>
#include <Lines.h>
namespace rng = std::ranges;

CVector2D (&CGlass::PanePolyPositions)[4][3] = *(CVector2D(*)[4][3])0x8D5CD8;
int32& CGlass::ReflectionPolyVertexBaseIdx = *(int32*)0xC71B18;
int32& CGlass::ReflectionPolyIndexBaseIdx = *(int32*)0xC71B1C;
RxObjSpace3DLitVertex(&CGlass::ReflectionPolyVertexBuffer)[1706] = *(RxObjSpace3DLitVertex(*)[1706])0xC5B158;
RxObjSpace3DLitVertex(&CGlass::ShatteredPolyVertexBuffer)[512] = *(RxObjSpace3DLitVertex(*)[512])0xC5B158;
int32& CGlass::ShatteredVerticesBaseIdx = *(int32*)0xC71B20;
int32& CGlass::ShatteredIndicesBaseIdx = *(int32*)0xC71B24;
uint32& CGlass::H1iLightPolyVerticesIdx = *(uint32*)0xC71B28;
int32& CGlass::HiLightPolyIndicesIdx = *(int32*)0xC71B2C;
CVector2D (&CGlass::PanePolyCenterPositions)[5] = *(CVector2D(*)[5])0xC71B30;
CEntity*(&CGlass::apEntitiesToBeRendered)[32] = *(CEntity*(*)[32])0xC71B58;
int32& CGlass::NumGlassEntities = *(int32*)0xC71BD8;
CFallingGlassPane (&CGlass::aGlassPanes)[44] = *(CFallingGlassPane(*)[44])0xC71BF8;
uint32& CGlass::LastColCheckMS = *(uint32*)0xC72FA8;

void CGlass::InjectHooks() {
    RH_ScopedClass(CGlass);
    RH_ScopedCategoryGlobal();
    
    RH_ScopedInstall(Init, 0x71A8D0);
    RH_ScopedInstall(HasGlassBeenShatteredAtCoors, 0x71CB70);
    RH_ScopedInstall(CarWindscreenShatters, 0x71C2B0);
    RH_ScopedInstall(WasGlassHitByBullet, 0x71C0D0);
    RH_ScopedInstall(WindowRespondsToCollision, 0x71BC40);
    RH_ScopedInstall(GeneratePanesForWindow, 0x71B620);
    RH_ScopedInstall(Update, 0x71B0D0);
    RH_ScopedInstall(Render, 0x71CE20);
    RH_ScopedInstall(FindWindowSectorList, 0x71AFC0);
    RH_ScopedInstall(RenderReflectionPolys, 0x71AED0);
    RH_ScopedInstall(RenderShatteredPolys, 0x71AE30);
    RH_ScopedInstall(RenderHiLightPolys, 0x71ADA0);
    RH_ScopedInstall(CalcAlphaWithNormal, 0x71ACF0);
    RH_ScopedInstall(AskForObjectToBeRenderedInGlass, 0x71ACD0);
    RH_ScopedInstall(FindFreePane, 0x71ACA0);
    RH_ScopedInstall(WindowRespondsToSoftCollision, 0x71AF70);
    RH_ScopedInstall(BreakGlassPhysically, 0x71CF50);
    RH_ScopedInstall(WindowRespondsToExplosion, 0x71C1A0);
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
bool CGlass::HasGlassBeenShatteredAtCoors(CVector point) {
    CWorld::IncrementCurrentScanCode();
    const float minX = point.x - 30.f;
    const float maxX = point.x + 30.f;
    const float minY = point.y - 30.f;
    const float maxY = point.y + 30.f;
    const int32 startSectorX = std::max(CWorld::GetSectorX(minX), 0);
    const int32 startSectorY = std::max(CWorld::GetSectorY(minY), 0);
    const int32 endSectorX = std::min(CWorld::GetSectorX(maxX), MAX_SECTORS_X - 1);
    const int32 endSectorY = std::min(CWorld::GetSectorY(maxY), MAX_SECTORS_Y - 1);
    float maxDist = 20.f;
    CEntity* entity{};
    for (int32 sectorY = startSectorY; sectorY <= endSectorY; ++sectorY) {
        for (int32 sectorX = startSectorX; sectorX <= endSectorX; ++sectorX) {
            FindWindowSectorList(GetRepeatSector(sectorX, sectorY)->m_lists[REPEATSECTOR_OBJECTS], maxDist, entity, point);
            FindWindowSectorList(GetSector(sectorX, sectorY)->m_dummies, maxDist, entity, point);
        }
    }
    return entity && !entity->IsDummy() && entity->AsObject()->objectFlags.bGlassBroken;
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

bool IsGlassObjectWithCol(CEntity* entity) {
    if (entity->IsObject() && entity->m_bUsesCollision) {
        const auto object = entity->AsObject();
        const auto MI = CModelInfo::GetModelInfo(object->m_nModelIndex)->AsAtomicModelInfoPtr();
        switch (MI->nSpecialType) {
        case eModelInfoSpecialType::GLASS_TYPE_1:
        case eModelInfoSpecialType::GLASS_TYPE_2:
            return true;
        }
    }
    return false;
}

// 0x71C0D0
void CGlass::WasGlassHitByBullet(CEntity* entity, CVector hitPos) {
    if (!IsGlassObjectWithCol(entity))
        return;

    const auto object = entity->AsObject();
    if (object->objectFlags.bGlassBroken) {
        if (rand() % 4 == 2) {
            WindowRespondsToCollision(entity, 0.0f, {}, hitPos, false);
        }
    } else {
        object->objectFlags.bGlassBroken = true; // Just mark it as broken
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
 * point                     - BL
 * fwd, right      - As illustrated above
 * center                  - The centre of the above rectangle (each pane is a piece of it)
 * velocity                - How fast the panes fly
 * velocityCenterDragCoeff - Modify the velocity's direction to be more towards the center point
 * bShatter                - Render shatter polys
 * numSectionsMax1         - Limit no. of sections to 1 - Unsure what's it use-case as setting `numSections` to 1 achieves the same
 * numSections             - No. of sections of each axis, the total number of sections will be `numSections ^ 2` (squared)
**/
void CGlass::GeneratePanesForWindow(uint32 type, CVector point, CVector fwd, CVector right, CVector velocity, CVector center, float velocityCenterDragCoeff,
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
    float groundZ = CWorld::FindGroundZFor3DCoord(point.x, point.y, point.z, &hitGround, nullptr);
    if (!hitGround)
        groundZ = point.z - 2.f;

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
                    mat.GetPosition() = point + Normalized(fwd) * paneCenterPos.y + Normalized(right) * paneCenterPos.x;

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
    H1iLightPolyVerticesIdx = 0;
    HiLightPolyIndicesIdx = 0;

    ShatteredVerticesBaseIdx = 1024;
    ShatteredIndicesBaseIdx = 2048;
    ReflectionPolyVertexBaseIdx = 1536;
    ReflectionPolyIndexBaseIdx = 3072;

    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void*)FALSE);
    RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, (void*)rwFILTERLINEAR);
    RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void*)TRUE);
    RwRenderStateSet(rwRENDERSTATEFOGCOLOR, (void*)CTimeCycle::m_CurrentColours.GetSkyBottom(0).ToIntARGB());
    RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)rwBLENDONE);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDONE);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)TRUE);

    for (auto& pane : aGlassPanes) {
        if (pane.existFlag) {
            pane.Render();
        }
    }

    RenderHiLightPolys();
    RenderShatteredPolys();
    RenderReflectionPolys();

    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void*)TRUE);
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void*)TRUE);
    RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)rwBLENDSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDINVSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void*)FALSE);
}

// 0x71AFC0
void CGlass::FindWindowSectorList(CPtrList& objList, float& outDist, CEntity*& outEntity, CVector point) {
    if (!objList.GetNode())
        return;

    for (CPtrNode *it = objList.GetNode(); it;) {
        const auto entity = static_cast<CEntity*>(it->m_item);
        it = it->GetNext();
        if (!entity->IsObject())
            continue;
        const auto object = entity->AsObject();
        const auto pAMI = CModelInfo::GetModelInfo(entity->m_nModelIndex)->AsAtomicModelInfoPtr();
        if (!pAMI)
            continue;
        if (object->m_nScanCode == CWorld::ms_nCurrentScanCode)
            continue;
        switch (pAMI->nSpecialType) {
        case eModelInfoSpecialType::GLASS_TYPE_1:
        case eModelInfoSpecialType::GLASS_TYPE_2: {
            object->m_nScanCode = CWorld::ms_nCurrentScanCode;
            if (const auto dist = (object->GetPosition() - point).Magnitude(); dist < outDist) {
                outEntity = entity;
                outDist = dist;
            }
            break;
        }
        }
    }
}

// 0x71AED0
void CGlass::RenderReflectionPolys() {
    if (ReflectionPolyVertexBaseIdx != 1536) {

        RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void*)gpShadowHeadLightsTex->raster);
        RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)rwBLENDSRCALPHA);
        RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDINVSRCALPHA);

        if (RwIm3DTransform(ReflectionPolyVertexBuffer, ReflectionPolyVertexBaseIdx - 1536, nullptr, 1u)) {
            RwIm3DRenderIndexedPrimitive(rwPRIMTYPETRILIST, &aTempBufferIndices[3072], ReflectionPolyIndexBaseIdx - 3072);
            RwIm3DEnd();
        }

        ReflectionPolyVertexBaseIdx = 1536;
        ReflectionPolyIndexBaseIdx = 3072;
    }
}

// 0x71AE30
void CGlass::RenderShatteredPolys() {
    if (ShatteredVerticesBaseIdx != 1024)
    {
        RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void*)gpCrackedGlassTex->raster);
        RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)rwBLENDSRCALPHA);
        RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDINVSRCALPHA);

        if (RwIm3DTransform(ShatteredPolyVertexBuffer, ShatteredVerticesBaseIdx - 1024, nullptr, rwIM3D_VERTEXUV))
        {
            RwIm3DRenderIndexedPrimitive(rwPRIMTYPETRILIST, &aTempBufferIndices[2048], ShatteredIndicesBaseIdx - 2048);
            RwIm3DEnd();
        }

        ShatteredVerticesBaseIdx = 1024;
        ShatteredIndicesBaseIdx = 2048;
    }
}

// 0x71ADA0
void CGlass::RenderHiLightPolys() {
    if (H1iLightPolyVerticesIdx != 0)
    {
        RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)rwBLENDONE);
        RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDONE);
        RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void*)gpShadowExplosionTex->raster);

        if (RwIm3DTransform(aTempBufferVertices, H1iLightPolyVerticesIdx, nullptr, rwIM3D_VERTEXUV)) {
            RwIm3DRenderIndexedPrimitive(rwPRIMTYPETRILIST, aTempBufferIndices, HiLightPolyIndicesIdx);
            RwIm3DEnd();
        }

        HiLightPolyIndicesIdx = 0;
        H1iLightPolyVerticesIdx = 0;
    }
}

// 0x71ACF0
uint8 CGlass::CalcAlphaWithNormal(const CVector& normal) {
    const auto camFwd = TheCamera.GetForward();
    const auto fwdOnNormalProj2x = ProjectVector(camFwd, normal) * 2.f;
    const auto factor = ( // TODO: What the fuck is going on here???
          camFwd.x - fwdOnNormalProj2x.x
        + camFwd.y - fwdOnNormalProj2x.y
        - camFwd.z + fwdOnNormalProj2x.z
    ) / SQRT_3;
    return (uint8)(std::pow(factor, 6) * 235.f + 20.f);
}

// 0x71ACD0
void CGlass::AskForObjectToBeRenderedInGlass(CEntity* entity) {
    if (NumGlassEntities < 31) {
        apEntitiesToBeRendered[NumGlassEntities++] = entity;
    }
}

// 0x71ACA0
CFallingGlassPane* CGlass::FindFreePane() {
    for (auto& pane : aGlassPanes) {
        if (!pane.existFlag) {
            return &pane;
        }
    }
    return nullptr;
}

// 0x71AF70
void CGlass::WindowRespondsToSoftCollision(CObject* object, float fDamageIntensity) {
    if (object->m_bUsesCollision && fDamageIntensity > 50.f && !object->objectFlags.bGlassBroken) {
        AudioEngine.ReportGlassCollisionEvent(AE_GLASS_HIT, object->GetPosition());
        object->objectFlags.bGlassBroken = true;
    }
}

// 0x71CF50
void CGlass::BreakGlassPhysically(CVector point, float radius) {
    if (CTimer::GetTimeInMS() < LastColCheckMS + 1000 && CTimer::GetTimeInMS() >= LastColCheckMS)
        return;

    for (auto objIdx = 0; objIdx < CPools::ms_pObjectPool->GetSize(); objIdx++) {
        if (auto object = CPools::ms_pObjectPool->GetAt(objIdx)) {
            if (!IsGlassObjectWithCol(object))
                continue;

            if (const auto colModel = object->GetColModel()) {
                const auto colData = colModel->m_pColData;
                if (!colData)
                    continue;

                if (colModel->GetTriCount() < 2)
                    continue;

                // Test if point touches any of the model's triangles
                {
                    const CColSphere sphere{
                        Multiply3x3(object->GetMatrix(), point - object->GetPosition()),
                        radius
                    };
                    CCollision::CalculateTrianglePlanes(colModel);

                    // TODO / NOTE: Shouldn't the loop stop the first time it hits a triangle? Unsure why they didn't do it like that?
                    bool hasHit{};
                    for (auto tri = 0u; tri < colModel->GetTriCount(); tri++) {
                        if (CCollision::TestSphereTriangle(sphere, colData->m_pVertices, colData->m_pTriangles[tri], colData->m_pTrianglePlanes[tri])) {
                            hasHit = true;
                        }
                    }
                    if (!hasHit)
                        continue;
                }

                LastColCheckMS = CTimer::m_snTimeInMilliseconds;

                if (!object->objectFlags.bGlassBroken) {
                    AudioEngine.ReportGlassCollisionEvent(AE_GLASS_HIT, object->GetPosition());
                    object->objectFlags.bGlassBroken = true;
                } else {
                    CVector verticesObjSpace[4];
                    for (auto i = 0u; i < 4u; i++) {
                        verticesObjSpace[i] = UncompressVector(colData->m_pVertices[i]);
                    }

                    const auto [minZ, maxZ] = FindMinMaxZOfVertices(verticesObjSpace);

                    // Vertex furthest of vertex 0
                    const auto furthestOfV0 = rng::max_element(verticesObjSpace, {},
                        [&](const auto& v) { return (v - verticesObjSpace[0]).Magnitude2D(); }
                    );

                    const auto v0Pos = MultiplyMatrixWithVector(object->GetMatrix(), { verticesObjSpace[0].x, verticesObjSpace[0].y, minZ });
                    const auto furthestOfV0Pos = MultiplyMatrixWithVector(object->GetMatrix(), { furthestOfV0->x, furthestOfV0->y, minZ });

                    AudioEngine.ReportGlassCollisionEvent(AE_GLASS_HIT, object->GetPosition());

                    GeneratePanesForWindow(
                        1,
                        v0Pos,
                        {0.f, 0.f, maxZ - minZ},
                        furthestOfV0Pos - v0Pos,
                        {},
                        point,
                        0.1f,
                        object->objectFlags.bGlassBroken,
                        false,
                        1,
                        false
                    );
                    object->m_bUsesCollision = false;
                    object->m_bIsVisible = false;
                    object->objectFlags.bGlassBroken = true;
                }
            }
        }
    }
}

// 0x71C1A0
void CGlass::WindowRespondsToExplosion(CEntity* entity, const CVector& pos) {
    plugin::Call<0x71C1A0, CEntity*, CVector>(entity, pos);
}
