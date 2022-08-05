// Based on https://github.com/Sergeanur/DrawColsSA
#include "StdInc.h"

#include <imgui.h>

#include "CollisionDebugModule.h"

#include "Lines.h"
#include "TaskSimpleClimb.h"

namespace CollisionDebugModule {

CollisionModule gDrawCollisionModule;

constexpr uint32 boundingBoxColor    = 0xFF0000FF; // red
constexpr uint32 boxColor            = 0xFFFFFFFF; // white
constexpr uint32 sphereColor         = 0xFF00FFFF; // magenta
constexpr uint32 lineColor           = 0xFFFFFF;   // light blue
constexpr uint32 triangleColor       = 0xFF00FF;   // green
constexpr uint32 shadowTriangleColor = 0xFFFFFFFF; // white

void DrawBoundingBox(const CMatrix& matrix, const CBoundingBox& boundBox) {
    auto workVec = boundBox.m_vecMin;
    CVector v1   = matrix * workVec;

    workVec.z    = boundBox.m_vecMax.z;
    CVector v2   = matrix * workVec;

    workVec      = boundBox.m_vecMin;
    workVec.x    = boundBox.m_vecMax.x;
    CVector v3   = matrix * workVec;

    workVec      = boundBox.m_vecMin;
    workVec.y    = boundBox.m_vecMax.y;
    CVector v4   = matrix * workVec;

    workVec      = boundBox.m_vecMin;
    workVec.y    = boundBox.m_vecMax.y;
    workVec.z    = boundBox.m_vecMax.z;
    CVector v5   = matrix * workVec;

    workVec      = boundBox.m_vecMin;
    workVec.x    = boundBox.m_vecMax.x;
    workVec.z    = boundBox.m_vecMax.z;
    CVector v6   = matrix * workVec;

    workVec      = boundBox.m_vecMin;
    workVec.x    = boundBox.m_vecMax.x;
    workVec.y    = boundBox.m_vecMax.y;
    CVector v7   = matrix * workVec;

    workVec      = boundBox.m_vecMax;
    CVector v8   = matrix * workVec;

    CLines::RenderLineWithClipping(v1, v2, boundingBoxColor, boundingBoxColor);
    CLines::RenderLineWithClipping(v1, v3, boundingBoxColor, boundingBoxColor);
    CLines::RenderLineWithClipping(v1, v4, boundingBoxColor, boundingBoxColor);
    CLines::RenderLineWithClipping(v5, v2, boundingBoxColor, boundingBoxColor);
    CLines::RenderLineWithClipping(v5, v8, boundingBoxColor, boundingBoxColor);
    CLines::RenderLineWithClipping(v5, v4, boundingBoxColor, boundingBoxColor);
    CLines::RenderLineWithClipping(v6, v2, boundingBoxColor, boundingBoxColor);
    CLines::RenderLineWithClipping(v6, v8, boundingBoxColor, boundingBoxColor);
    CLines::RenderLineWithClipping(v6, v3, boundingBoxColor, boundingBoxColor);
    CLines::RenderLineWithClipping(v7, v8, boundingBoxColor, boundingBoxColor);
    CLines::RenderLineWithClipping(v7, v3, boundingBoxColor, boundingBoxColor);
    CLines::RenderLineWithClipping(v7, v4, boundingBoxColor, boundingBoxColor);
}

void DrawSphere(const CMatrix& matrix, const CColSphere& sphere) {
    const CVector workVec = matrix * sphere.m_vecCenter;
    const float radius = sphere.m_fRadius;

    CVector v13 = workVec;
    v13.z       += radius;

    CVector v21 = workVec;
    v21.z       -= radius;

    CVector v32 = workVec;
    v32.x       += radius;

    CVector v41 = workVec;
    v41.x       -= radius;

    CVector v52 = workVec;
    v52.y       += radius;

    CVector v61 = workVec;
    v61.y       -= radius;

    CLines::RenderLineWithClipping(v13, v32, sphereColor, sphereColor);
    CLines::RenderLineWithClipping(v13, v41, sphereColor, sphereColor);
    CLines::RenderLineWithClipping(v21, v32, sphereColor, sphereColor);
    CLines::RenderLineWithClipping(v21, v41, sphereColor, sphereColor);
    CLines::RenderLineWithClipping(v13, v52, sphereColor, sphereColor);
    CLines::RenderLineWithClipping(v13, v61, sphereColor, sphereColor);
    CLines::RenderLineWithClipping(v21, v52, sphereColor, sphereColor);
    CLines::RenderLineWithClipping(v21, v61, sphereColor, sphereColor);
}

void DrawBox(const CMatrix& matrix, const CColBox& box) {
    auto workVec = box.m_vecMin;
    CVector v11  = matrix * workVec;

    workVec.z   = box.m_vecMax.z;
    CVector v23 = matrix * workVec;

    workVec     = box.m_vecMin;
    workVec.x   = box.m_vecMax.x;
    CVector v31 = matrix * workVec;

    workVec     = box.m_vecMin;
    workVec.y   = box.m_vecMax.y;
    CVector v42 = matrix * workVec;

    workVec     = box.m_vecMin;
    workVec.y   = box.m_vecMax.y;
    workVec.z   = box.m_vecMax.z;
    CVector v51 = matrix * workVec;

    workVec     = box.m_vecMin;
    workVec.x   = box.m_vecMax.x;
    workVec.z   = box.m_vecMax.z;
    CVector v62 = matrix * workVec;

    workVec     = box.m_vecMin;
    workVec.x   = box.m_vecMax.x;
    workVec.y   = box.m_vecMax.y;
    CVector v71 = matrix * workVec;

    workVec     = box.m_vecMax;
    CVector v81 = matrix * workVec;

    CLines::RenderLineWithClipping(v11, v23, boxColor, boxColor);
    CLines::RenderLineWithClipping(v11, v31, boxColor, boxColor);
    CLines::RenderLineWithClipping(v11, v42, boxColor, boxColor);
    CLines::RenderLineWithClipping(v51, v23, boxColor, boxColor);
    CLines::RenderLineWithClipping(v51, v81, boxColor, boxColor);
    CLines::RenderLineWithClipping(v51, v42, boxColor, boxColor);
    CLines::RenderLineWithClipping(v62, v23, boxColor, boxColor);
    CLines::RenderLineWithClipping(v62, v81, boxColor, boxColor);
    CLines::RenderLineWithClipping(v62, v31, boxColor, boxColor);
    CLines::RenderLineWithClipping(v71, v81, boxColor, boxColor);
    CLines::RenderLineWithClipping(v71, v31, boxColor, boxColor);
    CLines::RenderLineWithClipping(v71, v42, boxColor, boxColor);
}

void DrawTriangles(const CMatrix& matrix, const CColTriangle* triangles, const CompressedVector* vertices, const uint32& count, const uint32& startColor, const uint32& endColor) {
    for (const auto& triangle : std::span{ triangles, count }) {
        const CVector v14 = matrix * UncompressVector(vertices[triangle.m_nVertA]);
        const CVector v24 = matrix * UncompressVector(vertices[triangle.m_nVertB]);
        const CVector v33 = matrix * UncompressVector(vertices[triangle.m_nVertC]);

        CLines::RenderLineWithClipping(v14, v24, startColor, endColor);
        CLines::RenderLineWithClipping(v14, v33, startColor, endColor);
        CLines::RenderLineWithClipping(v24, v33, startColor, endColor);
    }
}

void DrawLine(const CMatrix& matrix, const CColLine& line) {
    const CVector v12 = matrix * line.m_vecStart;
    const CVector v22 = matrix * line.m_vecEnd;
    CLines::RenderLineWithClipping(v12, v22, lineColor, lineColor);
}

void DrawColModel(const CMatrix& matrix, const CColModel& cm) {
    const auto SetState = []() {
        RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,      RWRSTATE(TRUE));
        RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, RWRSTATE(TRUE));
        RwRenderStateSet(rwRENDERSTATESRCBLEND,          RWRSTATE(rwBLENDSRCALPHA));
        RwRenderStateSet(rwRENDERSTATEDESTBLEND,         RWRSTATE(rwBLENDINVSRCALPHA));
        RwRenderStateSet(rwRENDERSTATETEXTURERASTER,     RWRSTATE(NULL));
    };

    const auto ResetState = []() {
        RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,      RWRSTATE(FALSE));
        RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, RWRSTATE(FALSE));
    };

    if (!cm.m_pColData) {
        return;
    }

    SetState();

    if (gDrawCollisionModule.draw_box) {
        for (auto& boxes : cm.m_pColData->GetBoxes()) {
            DrawBox(matrix, boxes);
        }
    }

    if (gDrawCollisionModule.draw_line) {
        for (auto& lines : cm.m_pColData->GetLines()) {
            DrawLine(matrix, lines);
        }
    }

    if (gDrawCollisionModule.draw_sphere) {
        for (auto& spheres : cm.m_pColData->GetSpheres()) {
            DrawSphere(matrix, spheres);
        }
    }

    if (gDrawCollisionModule.draw_triangle) {
        DrawTriangles(matrix, cm.m_pColData->m_pTriangles, cm.m_pColData->m_pVertices, cm.m_pColData->m_nNumTriangles, triangleColor, triangleColor);
    }

    if (gDrawCollisionModule.draw_bounding_box) {
        DrawBoundingBox(matrix, cm.m_boundBox);
    }

    if (cm.m_pColData->bHasShadowInfo) {
        if (gDrawCollisionModule.draw_shadow_triangles) {
            DrawTriangles(matrix, cm.m_pColData->m_pShadowTriangles, cm.m_pColData->m_pShadowVertices, cm.m_pColData->m_nNumShadowTriangles, shadowTriangleColor, shadowTriangleColor);
        }
    }

    ResetState();
}

void ProcessImgui() {
    ImGui::Checkbox("Draw Collision", &gDrawCollisionModule.enabled);
    if (gDrawCollisionModule.enabled) {
        ImGui::Checkbox("Draw Box",              &gDrawCollisionModule.draw_box);
        ImGui::Checkbox("Draw Line",             &gDrawCollisionModule.draw_line);
        ImGui::Checkbox("Draw Sphere",           &gDrawCollisionModule.draw_sphere);
        ImGui::Checkbox("Draw Triangle",         &gDrawCollisionModule.draw_triangle);
        ImGui::Checkbox("Draw Bounding Box",     &gDrawCollisionModule.draw_bounding_box);
        ImGui::Checkbox("Draw Shadow Triangles", &gDrawCollisionModule.draw_shadow_triangles);
    }
}

void ProcessRender() {
    if (!gDrawCollisionModule.enabled)
        return;

    for (auto& entity : std::span{ CRenderer::ms_aVisibleEntityPtrs, (size_t)CRenderer::ms_nNoOfVisibleEntities }) {
        if (!entity || !entity->m_matrix)
            continue;

        const auto& mi = entity->GetModelInfo();
        if (!mi)
            continue;

        const auto& cm = mi->GetColModel();
        if (!cm)
            continue;

        DrawColModel(entity->GetMatrix(), *cm);
    }
}

}
