#include "StdInc.h"

#include <imgui.h>

#include "C3dMarkersDebugModule.h"
#include "CTeleportDebugModule.h"

#include "3dMarkers.h"

namespace C3dMarkersDebugModule {

using namespace ImGui;

void DrawDirectionArrow(tDirectionArrow& arrow) {
    TableNextRow();
    PushID(&arrow);

    TableNextColumn();
    Text(arrow.m_bIsUsed ? "true" : "false");

    TableNextColumn();
    Text("%.2f %.2f %.2f", arrow.m_vecPosition.x, arrow.m_vecPosition.y, arrow.m_vecPosition.z);

    TableNextColumn();
    Text("%.2f %.2f %.2f", arrow.m_vecDirection.x, arrow.m_vecDirection.y, arrow.m_vecDirection.z);

    TableNextColumn();
    Text("%.2f", arrow.m_fSize);

    PopID();
}

void DrawUser3dMarker(tUser3dMarker& marker) {
    TableNextRow();
    PushID(&marker);

    TableNextColumn();
    Text(marker.m_bIsUsed ? "true" : "false");

    TableNextColumn();
    Text("%.2f %.2f %.2f", marker.m_vecPosition.x, marker.m_vecPosition.y, marker.m_vecPosition.z);

    if (IsItemHovered()) {
        SetTooltip("Double Click To Teleport");
        if (IsMouseDoubleClicked(0))
            TeleportDebugModule::TeleportTo(marker.m_vecPosition);
    }

    TableNextColumn();
    InputScalarN("", ImGuiDataType_U32, &marker.m_nRed, 3);

    PopID();
}

void Draw3dMarker(C3dMarker& marker) {
    TableNextRow();
    PushID(&marker);

    TableNextColumn();
    Text(marker.m_bIsUsed ? "true" : "false");

    TableNextColumn();
    Text("%.2f %.2f %.2f", marker.m_vecLastPosition.x, marker.m_vecLastPosition.y, marker.m_vecLastPosition.z);

    if (IsItemHovered() && IsMouseDoubleClicked(0)) {
        TeleportDebugModule::TeleportTo(marker.m_vecLastPosition);
    }

    TableNextColumn();
    InputScalarN("", ImGuiDataType_U8, &marker.m_colour, 4);

    // m_nType m_bIsUsed m_nPulsePeriod m_nRotateRate m_nStartTime m_fPulseFraction m_fStdSize m_fSize m_fBrightness m_fCameraRange m_fRoofHeight m_nOnScreenTestTime

    PopID();
}

static bool s_DrawArrow = false;
static CVector s_AddPos{ 0.0f, 0.0f, -2.0f };
static CVector s_AddDir{ 1.0f, 0.0f,  0.5f };
static float s_Size{ 0.5f };

void ProcessImGui() {
    Checkbox("Add Direction Arrow", &s_DrawArrow);
    if (s_DrawArrow) {
        SliderFloat("Size", &s_Size, 0.0f, 10.0f);
        SliderFloat3("Add Pos", reinterpret_cast<float*>(&s_AddPos), -10.0f, 10.0f);
        SliderFloat3("Add Dir", reinterpret_cast<float*>(&s_AddDir), -10.0f, 10.0f);
    }

    Text("Direction Arrows");
    if (BeginTable("Direction Arrows", 4, ImGuiTableFlags_Borders)) {
        TableSetupColumn("Used");
        TableSetupColumn("Position");
        TableSetupColumn("Direction");
        TableSetupColumn("Size");
        TableHeadersRow();

        for (auto& arrow : C3dMarkers::ms_directionArrows) {
            DrawDirectionArrow(arrow);
        }
        EndTable();
    }

    Dummy({0, 5});
    Text("User 3D Markers");
    if (BeginTable("User 3D Markers", 3, ImGuiTableFlags_Borders)) {
        TableSetupColumn("Used");
        TableSetupColumn("Position");
        TableSetupColumn("Color");
        TableHeadersRow();

        for (auto& marker : C3dMarkers::ms_user3dMarkers) {
            DrawUser3dMarker(marker);
        }
        EndTable();
    }

    Dummy({0, 5});
    Text("Markers");
    if (BeginTable("Markers", 3, ImGuiTableFlags_Borders)) {
        TableSetupColumn("Used");
        TableSetupColumn("Last Position");
        TableSetupColumn("Color");
        TableHeadersRow();

        for (auto& marker : C3dMarkers::m_aMarkerArray) {
            Draw3dMarker(marker);
        }
        EndTable();
    }
}

void ProcessRender() {
    if (s_DrawArrow) {
        const auto player = FindPlayerPed();
        const auto forward = TheCamera.GetForward() + s_AddDir;
        C3dMarkers::DirectionArrowSet(player->GetPosition() + s_AddPos, s_Size, 0, 255, 0, 255, forward.x, forward.y, forward.z);
    }
}

} // namespace PoolsDebugModule
