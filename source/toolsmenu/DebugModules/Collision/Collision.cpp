// Based on https://github.com/Sergeanur/DrawColsSA
#include "StdInc.h"

#include <imgui.h>

#include "Collision.h"

#include "CLines.h"

namespace CollisionDebugModule {

CollisionModule gDrawCollisionModule;

constexpr uint32 boundingBoxColor = 0xFF0000FF; // red
constexpr uint32 boxColor         = 0xFFFFFFFF; // white
constexpr uint32 sphereColor      = 0xFF00FFFF; // magenta
constexpr uint32 lineColor        = 0xFFFFFF;   // light blue
constexpr uint32 triangleColor    = 0xFF00FF;   // green

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

void DrawTriangle(const CMatrix& matrix, const CColModel& colModel, const int32& index) {
    CVector v14, v24, v33;
    const auto triangle = colModel.m_pColData->m_pTriangles[index];

    colModel.m_pColData->GetTrianglePoint(v14, triangle.m_nVertA);
    colModel.m_pColData->GetTrianglePoint(v24, triangle.m_nVertB);
    colModel.m_pColData->GetTrianglePoint(v33, triangle.m_nVertC);

    v14 = matrix * v14;
    v24 = matrix * v24;
    v33 = matrix * v33;

    CLines::RenderLineWithClipping(v14, v24, triangleColor, triangleColor);
    CLines::RenderLineWithClipping(v14, v33, triangleColor, triangleColor);
    CLines::RenderLineWithClipping(v24, v33, triangleColor, triangleColor);
}

void DrawLine(const CMatrix& matrix, const CColLine& line) {
    const CVector v12 = matrix * line.m_vecStart;
    const CVector v22 = matrix * line.m_vecEnd;
    CLines::RenderLineWithClipping(v12, v22, lineColor, lineColor);
}

void DrawColModel(const CMatrix& matrix, const CColModel& colModel) {
    const auto SetState = []() {
        RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,      (void*)TRUE);
        RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)TRUE);
        RwRenderStateSet(rwRENDERSTATESRCBLEND,          (void*)rwBLENDSRCALPHA);
        RwRenderStateSet(rwRENDERSTATEDESTBLEND,         (void*)rwBLENDINVSRCALPHA);
        RwRenderStateSet(rwRENDERSTATETEXTURERASTER,     (void*)NULL);
    };

    const auto ResetState = []() {
        RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,     (void*)FALSE);
        RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE,(void*)FALSE);
    };

    if (!colModel.m_pColData) {
        return;
    }

    SetState();

    if (gDrawCollisionModule.draw_box) {
        for (int32 i = 0; i < colModel.m_pColData->m_nNumBoxes; i++) {
            DrawBox(matrix, colModel.m_pColData->m_pBoxes[i]);
        }
    }

    if (gDrawCollisionModule.draw_line) {
        for (int32 i = 0; i < colModel.m_pColData->m_nNumLines; i++) {
            DrawLine(matrix, colModel.m_pColData->m_pLines[i]);
        }
    }

    if (gDrawCollisionModule.draw_sphere) {
        for (int32 i = 0; i < colModel.m_pColData->m_nNumSpheres; i++) {
            DrawSphere(matrix, colModel.m_pColData->m_pSpheres[i]);
        }
    }

    if (gDrawCollisionModule.draw_triangle) {
        for (int32 i = 0; i < colModel.m_pColData->m_nNumTriangles; i++) {
            DrawTriangle(matrix, colModel, i);
        }
    }

    if (gDrawCollisionModule.draw_bounding_box) {
        DrawBoundingBox(matrix, colModel.m_boundBox);
    }

    ResetState();
}

void ProcessImgui() {
    ImGui::Checkbox("Draw Collision", &gDrawCollisionModule.enabled);
    if (gDrawCollisionModule.enabled) {
        ImGui::Checkbox("Draw Box",          &gDrawCollisionModule.draw_box);
        ImGui::Checkbox("Draw Line",         &gDrawCollisionModule.draw_line);
        ImGui::Checkbox("Draw Sphere",       &gDrawCollisionModule.draw_sphere);
        ImGui::Checkbox("Draw Triangle",     &gDrawCollisionModule.draw_triangle);
        ImGui::Checkbox("Draw Bounding Box", &gDrawCollisionModule.draw_bounding_box);
    }
}

void ProcessRender() {
    if (!gDrawCollisionModule.enabled)
        return;

    for (int32 i = 0; i < CRenderer::ms_nNoOfVisibleEntities; i++) {
        const auto& entity = CRenderer::ms_aVisibleEntityPtrs[i];
        if (!entity)
            continue;

        if (!entity->m_matrix)
            continue;

        const auto& modelInfo = CModelInfo::GetModelInfo(entity->m_nModelIndex);
        if (!modelInfo)
            continue;

        const auto& colModel = modelInfo->GetColModel();
        if (!colModel)
            continue;

        DrawColModel(entity->GetMatrix(), *colModel);
    }
}

}