// Based on https://github.com/Sergeanur/DrawColsSA

#include <imgui.h>
#include "StdInc.h"

#include "Collision.h"

#include "CLines.h"

namespace CollisionDebugModule {

CollisionModule gDrawCollisionModule;

// todo:?
//constexpr CRGBA sphereColor   = CRGBA();
//constexpr CRGBA boxColor      = CRGBA();
//constexpr CRGBA lineColor     = CRGBA();
//constexpr CRGBA triangleColor = CRGBA();

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

    CLines::RenderLineWithClipping(v1, v2, 0xFF0000FF, 0xFF0000FF);
    CLines::RenderLineWithClipping(v1, v3, 0xFF0000FF, 0xFF0000FF);
    CLines::RenderLineWithClipping(v1, v4, 0xFF0000FF, 0xFF0000FF);
    CLines::RenderLineWithClipping(v5, v2, 0xFF0000FF, 0xFF0000FF);
    CLines::RenderLineWithClipping(v5, v8, 0xFF0000FF, 0xFF0000FF);
    CLines::RenderLineWithClipping(v5, v4, 0xFF0000FF, 0xFF0000FF);
    CLines::RenderLineWithClipping(v6, v2, 0xFF0000FF, 0xFF0000FF);
    CLines::RenderLineWithClipping(v6, v8, 0xFF0000FF, 0xFF0000FF);
    CLines::RenderLineWithClipping(v6, v3, 0xFF0000FF, 0xFF0000FF);
    CLines::RenderLineWithClipping(v7, v8, 0xFF0000FF, 0xFF0000FF);
    CLines::RenderLineWithClipping(v7, v3, 0xFF0000FF, 0xFF0000FF);
    CLines::RenderLineWithClipping(v7, v4, 0xFF0000FF, 0xFF0000FF);
}

void DrawSphere(const CMatrix& matrix, const CColSphere& sphere) {
    const CVector workVec2 = matrix * sphere.m_vecCenter;
    const float radius = sphere.m_fRadius;

    CVector v13 = workVec2;
    v13.z += radius;

    CVector v21 = workVec2;
    v21.z -= radius;

    CVector v32 = workVec2;
    v32.x += radius;

    CVector v41 = workVec2;
    v41.x -= radius;

    CVector v52 = workVec2;
    v52.y += radius;

    CVector v61 = workVec2;
    v61.y -= radius;

    CLines::RenderLineWithClipping(v13, v32, 0xFF00FFFF, 0xFF00FFFF);
    CLines::RenderLineWithClipping(v13, v41, 0xFF00FFFF, 0xFF00FFFF);
    CLines::RenderLineWithClipping(v21, v32, 0xFF00FFFF, 0xFF00FFFF);
    CLines::RenderLineWithClipping(v21, v41, 0xFF00FFFF, 0xFF00FFFF);

    CLines::RenderLineWithClipping(v13, v52, 0xFF00FFFF, 0xFF00FFFF);
    CLines::RenderLineWithClipping(v13, v61, 0xFF00FFFF, 0xFF00FFFF);
    CLines::RenderLineWithClipping(v21, v52, 0xFF00FFFF, 0xFF00FFFF);
    CLines::RenderLineWithClipping(v21, v61, 0xFF00FFFF, 0xFF00FFFF);
}

void DrawBox(const CMatrix& matrix, const CColBox& box) {
    auto workVec1 = box.m_vecMin;
    CVector v11 = matrix * workVec1;

    workVec1.z = box.m_vecMax.z;
    CVector v23 = matrix * workVec1;

    workVec1 = box.m_vecMin;
    workVec1.x = box.m_vecMax.x;
    CVector v31 = matrix * workVec1;

    workVec1 = box.m_vecMin;
    workVec1.y = box.m_vecMax.y;
    CVector v42 = matrix * workVec1;

    workVec1 = box.m_vecMin;
    workVec1.y = box.m_vecMax.y;
    workVec1.z = box.m_vecMax.z;
    CVector v51 = matrix * workVec1;

    workVec1 = box.m_vecMin;
    workVec1.x = box.m_vecMax.x;
    workVec1.z = box.m_vecMax.z;
    CVector v62 = matrix * workVec1;

    workVec1 = box.m_vecMin;
    workVec1.x = box.m_vecMax.x;
    workVec1.y = box.m_vecMax.y;
    CVector v71 = matrix * workVec1;

    workVec1 = box.m_vecMax;
    CVector v81 = matrix * workVec1;

    CLines::RenderLineWithClipping(v11, v23, 0xFFFFFFFF, 0xFFFFFFFF);
    CLines::RenderLineWithClipping(v11, v31, 0xFFFFFFFF, 0xFFFFFFFF);
    CLines::RenderLineWithClipping(v11, v42, 0xFFFFFFFF, 0xFFFFFFFF);
    CLines::RenderLineWithClipping(v51, v23, 0xFFFFFFFF, 0xFFFFFFFF);
    CLines::RenderLineWithClipping(v51, v81, 0xFFFFFFFF, 0xFFFFFFFF);
    CLines::RenderLineWithClipping(v51, v42, 0xFFFFFFFF, 0xFFFFFFFF);
    CLines::RenderLineWithClipping(v62, v23, 0xFFFFFFFF, 0xFFFFFFFF);
    CLines::RenderLineWithClipping(v62, v81, 0xFFFFFFFF, 0xFFFFFFFF);
    CLines::RenderLineWithClipping(v62, v31, 0xFFFFFFFF, 0xFFFFFFFF);
    CLines::RenderLineWithClipping(v71, v81, 0xFFFFFFFF, 0xFFFFFFFF);
    CLines::RenderLineWithClipping(v71, v31, 0xFFFFFFFF, 0xFFFFFFFF);
    CLines::RenderLineWithClipping(v71, v42, 0xFFFFFFFF, 0xFFFFFFFF);
}

void DrawColModel(const CMatrix& matrix, const CColModel& colModel) {
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,      (void*)TRUE);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)TRUE);
    RwRenderStateSet(rwRENDERSTATESRCBLEND,          (void*)rwBLENDSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND,         (void*)rwBLENDINVSRCALPHA);
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER,     (void*)NULL);

    if (gDrawCollisionModule.draw_bounding_box)
        DrawBoundingBox(matrix, colModel.m_boundBox);

    const auto ResetState = []() {
        RwRenderStateSet(rwRENDERSTATESRCBLEND,         (void*)rwBLENDSRCALPHA);
        RwRenderStateSet(rwRENDERSTATEDESTBLEND,        (void*)rwBLENDINVSRCALPHA);
        RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE,(void*)FALSE);
        RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,     (void*)TRUE);
        RwRenderStateSet(rwRENDERSTATEZTESTENABLE,      (void*)TRUE);
    };

    if (!colModel.m_pColData) {
        ResetState();
        return;
    }

    if (gDrawCollisionModule.draw_sphere) {
        for (int32 i = 0; i < colModel.m_pColData->m_nNumSpheres; i++) {
            DrawSphere(matrix, colModel.m_pColData->m_pSpheres[i]);
        }
    }

    if (gDrawCollisionModule.draw_line) {
        for (int32 i = 0; i < colModel.m_pColData->m_nNumLines; i++) {
            CVector v12 = matrix * colModel.m_pColData->m_pLines[i].m_vecStart;
            CVector v22 = matrix * colModel.m_pColData->m_pLines[i].m_vecEnd;
            CLines::RenderLineWithClipping(v12.x, v12.y, v12.z, v22.x, v22.y, v22.z, 0xFFFFFF, 0xFFFFFF);
        }
    }

    if (gDrawCollisionModule.draw_box) {
        for (int32 i = 0; i < colModel.m_pColData->m_nNumBoxes; i++) {
            DrawBox(matrix, colModel.m_pColData->m_pBoxes[i]);
        }
    }

    if (gDrawCollisionModule.draw_triangle) {
        for (int32 i = 0; i < colModel.m_pColData->m_nNumTriangles; i++) {
            CVector v14, v24, v33;
            colModel.m_pColData->GetTrianglePoint(v14, colModel.m_pColData->m_pTriangles[i].m_nVertA);
            colModel.m_pColData->GetTrianglePoint(v24, colModel.m_pColData->m_pTriangles[i].m_nVertB);
            colModel.m_pColData->GetTrianglePoint(v33, colModel.m_pColData->m_pTriangles[i].m_nVertC);

            v14 = matrix * v14;
            v24 = matrix * v24;
            v33 = matrix * v33;

            CLines::RenderLineWithClipping(v14, v24, 0xFF00FF, 0xFF00FF);
            CLines::RenderLineWithClipping(v14, v33, 0xFF00FF, 0xFF00FF);
            CLines::RenderLineWithClipping(v24, v33, 0xFF00FF, 0xFF00FF);
        }
    }

    ResetState();
}

void ProcessImgui() {
    if (ImGui::CollapsingHeader("Collision")) {
        ImGui::Checkbox("Draw Collision", &gDrawCollisionModule.enabled);
        if (gDrawCollisionModule.enabled) {
            ImGui::Checkbox("Draw Bounding Box", &gDrawCollisionModule.draw_bounding_box);
            ImGui::Checkbox("Draw Box", &gDrawCollisionModule.draw_box);
            ImGui::Checkbox("Draw Line", &gDrawCollisionModule.draw_line);
            ImGui::Checkbox("Draw Sphere", &gDrawCollisionModule.draw_sphere);
            ImGui::Checkbox("Draw Triangle", &gDrawCollisionModule.draw_triangle);
        }
    }
}

void ProcessRender() {
    if (!gDrawCollisionModule.enabled)
        return;

    for (int32 i = 0; i < CRenderer::ms_nNoOfVisibleEntities; i++) {
        auto entity = CRenderer::ms_aVisibleEntityPtrs[i];
        if (!entity)
            continue;

        if (!entity->m_matrix)
            continue;

        auto modelInfo = CModelInfo::GetModelInfo(entity->m_nModelIndex);
        if (!modelInfo)
            continue;

        auto colModel = modelInfo->GetColModel();
        if (!colModel)
            continue;

        DrawColModel(entity->GetMatrix(), *colModel);
    }
}

}