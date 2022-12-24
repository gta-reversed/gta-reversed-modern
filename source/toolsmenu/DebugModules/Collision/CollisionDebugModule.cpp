// Based on https://github.com/Sergeanur/DrawColsSA
#include "StdInc.h"

#include <imgui.h>

#include "CollisionDebugModule.h"

#include "Lines.h"
#include "TaskSimpleClimb.h"

constexpr auto BB_COLOR       = 0xFF0000FF; // red
constexpr auto BOX_COLOR      = 0xFFFFFFFF; // white
constexpr auto SPHERE_COLOR   = 0xFF00FFFF; // magenta
constexpr auto LINE_COLOR     = 0x00FFFFFF; // light blue
constexpr auto TRI_COLOR      = 0x00FF00FF; // green
constexpr auto SHDW_TRI_COLOR = 0xFFFFFFFF; // white

CollisionDebugModule::CollisionDebugModule() :
    DebugModuleSingleWindow{ "Collision", {400.f, 400.f} }
{
}

void CollisionDebugModule::RenderMainWindow() {
    if (ImGui::TreeNode("Visualize Entity Collision Models")) {
        ImGui::Checkbox("Draw Collision", &m_visualizationEnabled);
        if (m_visualizationEnabled) {
            ImGui::Checkbox("Boxes",            &m_drawBoxes);
            ImGui::Checkbox("Lines",            &m_drawLines);
            ImGui::Checkbox("Spheres",          &m_drawSpheres);
            ImGui::Checkbox("Triangles",        &m_drawTris);
            ImGui::Checkbox("Bounding Boxes",   &m_drawBBs);
            ImGui::Checkbox("Shadow Triangles", &m_drawShdwTris);
        }
        ImGui::TreePop();
    }
}

void CollisionDebugModule::RenderMenuEntry() {
    if (ImGui::BeginMenu("Visualize")) {
        if (ImGui::MenuItem("Collision")) {
            SetMainWindowOpen(true);
        }
        ImGui::EndMenu();
    }
}

void CollisionDebugModule::Render3D() {
    if (m_visualizationEnabled) {
        RenderVisibleColModels();
    }
}

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

    CLines::RenderLineWithClipping(v1, v2, BB_COLOR, BB_COLOR);
    CLines::RenderLineWithClipping(v1, v3, BB_COLOR, BB_COLOR);
    CLines::RenderLineWithClipping(v1, v4, BB_COLOR, BB_COLOR);
    CLines::RenderLineWithClipping(v5, v2, BB_COLOR, BB_COLOR);
    CLines::RenderLineWithClipping(v5, v8, BB_COLOR, BB_COLOR);
    CLines::RenderLineWithClipping(v5, v4, BB_COLOR, BB_COLOR);
    CLines::RenderLineWithClipping(v6, v2, BB_COLOR, BB_COLOR);
    CLines::RenderLineWithClipping(v6, v8, BB_COLOR, BB_COLOR);
    CLines::RenderLineWithClipping(v6, v3, BB_COLOR, BB_COLOR);
    CLines::RenderLineWithClipping(v7, v8, BB_COLOR, BB_COLOR);
    CLines::RenderLineWithClipping(v7, v3, BB_COLOR, BB_COLOR);
    CLines::RenderLineWithClipping(v7, v4, BB_COLOR, BB_COLOR);
}

void DrawSphere(const CMatrix& matrix, const CColSphere& sphere) {
    const CVector center = matrix * sphere.m_vecCenter;
    const float radius = sphere.m_fRadius;

    CVector v13 = center;
    v13.z       += radius;

    CVector v21 = center;
    v21.z       -= radius;

    CVector v32 = center;
    v32.x       += radius;

    CVector v41 = center;
    v41.x       -= radius;

    CVector v52 = center;
    v52.y       += radius;

    CVector v61 = center;
    v61.y       -= radius;

    CLines::RenderLineWithClipping(v13, v32, SPHERE_COLOR, SPHERE_COLOR);
    CLines::RenderLineWithClipping(v13, v41, SPHERE_COLOR, SPHERE_COLOR);
    CLines::RenderLineWithClipping(v21, v32, SPHERE_COLOR, SPHERE_COLOR);
    CLines::RenderLineWithClipping(v21, v41, SPHERE_COLOR, SPHERE_COLOR);
    CLines::RenderLineWithClipping(v13, v52, SPHERE_COLOR, SPHERE_COLOR);
    CLines::RenderLineWithClipping(v13, v61, SPHERE_COLOR, SPHERE_COLOR);
    CLines::RenderLineWithClipping(v21, v52, SPHERE_COLOR, SPHERE_COLOR);
    CLines::RenderLineWithClipping(v21, v61, SPHERE_COLOR, SPHERE_COLOR);
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

    CLines::RenderLineWithClipping(v11, v23, BOX_COLOR, BOX_COLOR);
    CLines::RenderLineWithClipping(v11, v31, BOX_COLOR, BOX_COLOR);
    CLines::RenderLineWithClipping(v11, v42, BOX_COLOR, BOX_COLOR);
    CLines::RenderLineWithClipping(v51, v23, BOX_COLOR, BOX_COLOR);
    CLines::RenderLineWithClipping(v51, v81, BOX_COLOR, BOX_COLOR);
    CLines::RenderLineWithClipping(v51, v42, BOX_COLOR, BOX_COLOR);
    CLines::RenderLineWithClipping(v62, v23, BOX_COLOR, BOX_COLOR);
    CLines::RenderLineWithClipping(v62, v81, BOX_COLOR, BOX_COLOR);
    CLines::RenderLineWithClipping(v62, v31, BOX_COLOR, BOX_COLOR);
    CLines::RenderLineWithClipping(v71, v81, BOX_COLOR, BOX_COLOR);
    CLines::RenderLineWithClipping(v71, v31, BOX_COLOR, BOX_COLOR);
    CLines::RenderLineWithClipping(v71, v42, BOX_COLOR, BOX_COLOR);
}

void DrawTriangles(const CMatrix& matrix, const CColTriangle* triangles, const CompressedVector* vertices, const uint32& count, const uint32& startColor, const uint32& endColor) {
    for (const auto& triangle : std::span{ triangles, count }) {
        const CVector vA = matrix * UncompressVector(vertices[triangle.m_nVertA]);
        const CVector vB = matrix * UncompressVector(vertices[triangle.m_nVertB]);
        const CVector vC = matrix * UncompressVector(vertices[triangle.m_nVertC]);

        CLines::RenderLineWithClipping(vA, vB, startColor, endColor);
        CLines::RenderLineWithClipping(vA, vC, startColor, endColor);
        CLines::RenderLineWithClipping(vB, vC, startColor, endColor);
    }
}

void DrawLine(const CMatrix& matrix, const CColLine& line) {
    CLines::RenderLineWithClipping(matrix * line.m_vecStart, matrix * line.m_vecEnd, LINE_COLOR, LINE_COLOR);
}

void CollisionDebugModule::DrawColModel(const CMatrix& matrix, const CColModel& cm) {
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

    if (m_drawBoxes) {
        for (auto& boxes : cm.m_pColData->GetBoxes()) {
            DrawBox(matrix, boxes);
        }
    }

    if (m_drawLines) {
        for (auto& lines : cm.m_pColData->GetLines()) {
            DrawLine(matrix, lines);
        }
    }

    if (m_drawSpheres) {
        for (auto& spheres : cm.m_pColData->GetSpheres()) {
            DrawSphere(matrix, spheres);
        }
    }

    if (m_drawTris) {
        DrawTriangles(matrix, cm.m_pColData->m_pTriangles, cm.m_pColData->m_pVertices, cm.m_pColData->m_nNumTriangles, TRI_COLOR, TRI_COLOR);
    }

    if (m_drawBBs) {
        DrawBoundingBox(matrix, cm.m_boundBox);
    }

    if (cm.m_pColData->bHasShadowInfo) {
        if (m_drawShdwTris) {
            DrawTriangles(matrix, cm.m_pColData->m_pShadowTriangles, cm.m_pColData->m_pShadowVertices, cm.m_pColData->m_nNumShadowTriangles, SHDW_TRI_COLOR, SHDW_TRI_COLOR);
        }
    }

    ResetState();
}

void CollisionDebugModule::RenderVisibleColModels() {
    assert(CRenderer::ms_nNoOfVisibleEntities >= 0);
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
