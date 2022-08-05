#include "StdInc.h"

#ifdef EXTRA_DEBUG_FEATURES

#include "CullZonesDebugModule.h"
#include "Lines.h"

#include "imgui.h"

namespace CullZonesDebugModule {

static bool Enabled = false;

static float AddHeight = 0.0f;

static bool DrawMirrors = true;
static CCullZoneReflection* MirrorCurrent = nullptr;
static auto MirrorCurrentIdx = 0;

static bool DrawTunnels = true;
static CCullZone* TunnelCurrent = nullptr;
static auto TunnelCurrentIdx = 0;

static bool DrawCulls = true;
static CCullZone* CullCurrent = nullptr;
static auto CullCurrentIdx = 0;

void ProcessImGui() {
    ImGui::Checkbox("Enabled", &Enabled);
    ImGui::Checkbox("Draw Mirrors", &DrawMirrors);
    ImGui::Checkbox("Draw Tunnels", &DrawTunnels);
    ImGui::Checkbox("Draw Culls", &DrawCulls);

    ImGui::SliderFloat("Height", &AddHeight, 0.0f, 100.0f);

    ImGui::NewLine();
    ImGui::Text("Current Mirror: %d", MirrorCurrentIdx);
    ImGui::SameLine();
    ImGui::Text("Tunnel: %d", TunnelCurrentIdx);
    ImGui::SameLine();
    ImGui::Text("Cull: %d", CullCurrentIdx);
}

void ProcessRender() {
    if (!Enabled) {
        return;
    }

    const auto RenderLine = [](float x1, float y1, float z1, float x2, float y2, float z2) {
        CLines::RenderLineNoClipping(x1, y1, z1, x2, y2, z2, 0xFF0000FF, 0x00FF00FF); // from red to green
    };

    auto& camPos = TheCamera.GetPosition();
    const auto DrawZone = [&](const char* name, const auto& arr, const auto* zone) {
        const auto& def = zone->zoneDef;
        float x1 = def.m_x1, y1 = def.m_y1, y2 = def.m_lenY, x3 = def.m_lenX;
        float bottomZ = def.bottomZ + AddHeight, topZ = def.topZ + AddHeight;

        RenderLine(x1 + x3, y1,      topZ,    x1,      y1,      topZ);
        RenderLine(x1,      y1,      topZ,    x1,      y1 + y2, topZ);
        RenderLine(x1 + x3, y1,      topZ,    x1 + x3, y1 + y2, topZ);
        RenderLine(x1 + x3, y1 + y2, topZ,    x1,      y1 + y2, topZ);
        RenderLine(x1 + x3, y1,      topZ,    x1 + x3, y1,      bottomZ);
        RenderLine(x1,      y1,      topZ,    x1,      y1,      bottomZ);
        RenderLine(x1,      y1 + y2, topZ,    x1,      y1 + y2, bottomZ);
        RenderLine(x1 + x3, y1 + y2, topZ,    x1 + x3, y1 + y2, bottomZ);
        RenderLine(x1,      y1,      bottomZ, x1,      y1 + y2, bottomZ);
        RenderLine(x1 + x3, y1,      bottomZ, x1 + x3, y1 + y2, bottomZ);
        RenderLine(x1 + x3, y1,      bottomZ, x1,      y1,      bottomZ);
        RenderLine(x1 + x3, y1 + y2, bottomZ, x1,      y1 + y2, bottomZ);
    };

    MirrorCurrentIdx = TunnelCurrentIdx = CullCurrentIdx = -1;

    const auto ProcessCull = [&](const bool& render, const char* name,
                                 auto& culls, const auto& cullCount,
                                 auto& cull, auto& cullIdx)
    {
        if (render) {
            for (auto i = 0; i < cullCount; ++i) {
                auto& v = culls[i];
                DrawZone(name, culls, &v);
                if (v.zoneDef.IsPointWithin(camPos)) {
                    cull = &v;
                    cullIdx = i;
                }
            }
        }
    };

    ProcessCull(DrawMirrors, "mirror",  CCullZones::aMirrorAttributeZones, CCullZones::NumMirrorAttributeZones, MirrorCurrent, MirrorCurrentIdx);
    ProcessCull(DrawTunnels, "tunnel",  CCullZones::aTunnelAttributeZones, CCullZones::NumTunnelAttributeZones, TunnelCurrent, TunnelCurrentIdx);
    ProcessCull(DrawCulls,   "default", CCullZones::aAttributeZones,       CCullZones::NumAttributeZones,       CullCurrent,   CullCurrentIdx);
}

};
#endif
