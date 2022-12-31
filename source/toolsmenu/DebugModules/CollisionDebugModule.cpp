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

void CollisionDebugModule::RenderMenuEntry() {
    notsa::ui::DoNestedMenuIL({ "Visualization", "Collision" }, [&] {
        ImGui::Checkbox("Enabled", &m_Enabled);

        notsa::ui::ScopedDisable disabledScope{ !m_Enabled };

        ImGui::Checkbox("Boxes",            &m_DrawBoxes);
        ImGui::Checkbox("Lines",            &m_DrawLines);
        ImGui::Checkbox("Spheres",          &m_DrawSpheres);
        ImGui::Checkbox("Triangles",        &m_DrawTris);
        ImGui::Checkbox("Bounding Boxes",   &m_DrawBBs);
        ImGui::Checkbox("Shadow Triangles", &m_DrawShdwTris);
    });
}

void CollisionDebugModule::Render3D() {
    if (m_Enabled) {
        RenderVisibleColModels();
    }
}

void CollisionDebugModule::DrawColModel(const CMatrix& transform, const CColModel& cm) {
    const auto cd = cm.GetData();
    if (!cd) {
        return;
    }

    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,      RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATESRCBLEND,          RWRSTATE(rwBLENDSRCALPHA));
    RwRenderStateSet(rwRENDERSTATEDESTBLEND,         RWRSTATE(rwBLENDINVSRCALPHA));
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER,     RWRSTATE(NULL));

    if (m_DrawBoxes) {
        for (auto& box : cm.m_pColData->GetBoxes()) {
            box.DrawWireFrame({BB_COLOR}, transform);
        }
    }

    if (m_DrawLines) {
        for (auto& lines : cm.m_pColData->GetLines()) {
            lines.DrawWireFrame({ LINE_COLOR }, transform);
        }
    }

    if (m_DrawSpheres) {
        for (auto& spheres : cm.m_pColData->GetSpheres()) {
            spheres.DrawWireFrame({ SPHERE_COLOR }, transform );
        }
    }

    if (m_DrawTris) {
        for (const auto& triangle : cd->GetTris()) {
            triangle.DrawWireFrame({ TRI_COLOR }, cd->GetTriVerts(), transform);
        }
    }

    if (m_DrawBBs) {
        cm.m_boundBox.DrawWireFrame({ BB_COLOR }, transform);
    }

    if (cm.m_pColData->bHasShadowInfo) {
        if (m_DrawShdwTris) {
            for (const auto& triangle : cd->GetTris()) {
                triangle.DrawWireFrame({ SHDW_TRI_COLOR }, cd->m_pShadowVertices, transform);
            }
        }
    }

    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,      RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, RWRSTATE(FALSE));
}

void CollisionDebugModule::RenderVisibleColModels() {
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
