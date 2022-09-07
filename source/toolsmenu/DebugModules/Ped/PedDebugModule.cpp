#include "StdInc.h"
#include "extensions/enumerate.hpp"
#include "PedDebugModule.h"
#include "Pools.h"
#include "TaskManager.h"
#include "Hud.h"
#include <vector>
#include <list>
#include <optional>
#include <format>

// Define extra conversion function from our vector type to imgui's vec2d
#define IM_VEC2_CLASS_EXTRA \
    operator CVector2D() const { return {x, y}; } \
    ImVec2(const CVector2D& v) : x{v.x}, y{v.y} {} \

#include <imgui.h>

using namespace ImGui;

namespace PedDebugModule {

void General::ProcessPed(CPed& ped) {
    if (BeginTabItem("General")) {
        // Don't allow CJ to be removed kekw
        if (FindPlayerPed() != &ped) {
            if (Button("Remove")) {
                CPopulation::RemovePed(&ped);
            }
        }
        SameLine();
        if (Button("Catapult")) {
            const auto entity = ped.IsInVehicle() ? (CPhysical*)ped.m_pVehicle : &ped;
            entity->ApplyMoveForce(entity->GetUpVector() * 10000.f);
        }

        Text("Pool ID: %d", GetPedPool()->GetIndex(&ped));
        Text("Skin Model: %d", ped.m_nModelIndex);

        const auto& pos = ped.GetPosition();
        Text("Position: %.3f, %.3f, %.3f", pos.x, pos.y, pos.z);

        EndTabItem();
    }
}


void Tasks::ProcessTask(CTask* task, std::optional<size_t> idx) {
    const auto taskType = task->GetTaskType();

    const auto DoTreeNode = [&] {
        return idx // If set, this is a root task
            ? TreeNodeEx(task, ImGuiTreeNodeFlags_DefaultOpen, "%i: %s", (int)*idx, GetTaskTypeName(taskType)) // For root tasks show index, eventually as a string from `ePrimaryTasks` and `eSecondaryTask`
            : TreeNodeEx(GetTaskTypeName(taskType), ImGuiTreeNodeFlags_DefaultOpen);
    };

    PushID((int)taskType);
    if (DoTreeNode()) {
        if (const auto sub = task->GetSubTask()) {
            ProcessTask(sub, std::nullopt);
        }
        TreePop();
    }
    PopID();
}

/*!
* @brief Process category, eg.: secondary or primary
*/
void Tasks::ProcessTaskCategory(const char* label, const auto& tasks) {
    if (TreeNodeEx(label, ImGuiTreeNodeFlags_DefaultOpen)) {
        for (const auto& [idx, task] : notsa::enumerate(tasks)) {
            if (task) {
                ProcessTask(task, idx);
            }
        }
        TreePop();
    }
}

/*!
* @brief Process a single ped. This call is done within an imgui tab 
*/
void Tasks::ProcessPed(CPed& ped) {
    if (BeginTabItem("Tasks")) {
        auto& taskMgr = ped.GetTaskManager();
        ProcessTaskCategory("Primary", taskMgr.GetPrimaryTasks());
        ProcessTaskCategory("Secondary", taskMgr.GetSecondaryTasks());        
        EndTabItem();
    }
}

void PerPedDebug::ProcessImGui() {
    if (TreeNode("Per-ped debug")) {
        Checkbox("Enabled", &m_visible);
        SliderFloat("Draw distance", &m_drawDist, 4.f, 300.f); // Realistically GTA won't generate peds even at 200 units
        if (TreeNode("Auto-collapse")) {
            Checkbox("Enabled", &m_autoCollapse);
            SliderFloat("Distance", &m_collapseToggleDist, 4.f, 300.f);
            TreePop();
        }
        TreePop();
    }
}

// https://stackoverflow.com/a/60971856
template<rng::range R>
constexpr auto to_vector(R&& r) {
    using elem_t = std::decay_t<rng::range_value_t<R>>;
    return std::vector<elem_t>{r.begin(), r.end()};
}

void PerPedDebug::ProcessRender() {
    if (m_visible) {
        auto peds = to_vector(
              GetPedPool()->GetAllValid()
            | rng::views::transform([this](CPed& ped) -> std::optional<PedInfo> {
                if (!ped.GetIsOnScreen()) {
                    return std::nullopt;
                }

                PedInfo pi{
                    .ped = &ped,
                    .posWorld = ped.GetPosition()
                };

                if (!CalcScreenCoors(ped.GetBonePosition(BONE_HEAD) + ped.GetRightVector() * 0.5f, &pi.posScreen)) {
                    DEV_LOG("Failed to calculate on-screen coords of ped");
                    return std::nullopt;
                }
               
                if (pi.posScreen.z >= m_drawDist) { // posScreen.z == depth == distance from camera
                    return std::nullopt;
                }

                return pi;
            })
            | rng::views::filter([](auto&& optPI) { return optPI.has_value(); })
            | rng::views::transform([](auto&& optPI) { return *optPI; })
        );
        // Sort by depth (furthest away first, this way when windows are rendered the closest ped's will be drawn last => on top of everythign else)
        rng::sort(peds, std::greater<>{}, [](const PedInfo& pi) -> float { return pi.posScreen.z; });

        for (PedInfo& pi : peds) {
            ProcessPed(pi);
        }
    }
}

void PerPedDebug::ProcessPed(PedInfo& pi) {
    if (!pi.ped->GetIsOnScreen()) {
        return;
    }

    const auto remap = [](auto value, auto low1, auto high1, auto low2, auto high2) {
        return low2 + (value - low1) * (high2 - low2) / (high1 - low1);
    };
    
    const auto depth = pi.posScreen.z;

    if (depth > 100.f) {
        return; // Too distant
    }

    SetNextWindowPos(CVector2D{ pi.posScreen });
    SetNextWindowSize(CVector2D{ 600, 400 } / remap(depth, 0.f, 100.f, 1.f, 4.f));
    //SetNextWindowSize({ 600, 400 }, ImGuiCond_FirstUseEver);

    // Format a title with a custom ID that should hopefully match only this ped
    char title[1024];
    *std::format_to(title, "Ped Debug###{}{}", (ptrdiff_t)(pi.ped), pi.ped->m_nRandomSeed) = 0; // Null terminate :D

    if (m_autoCollapse) {
        SetNextWindowCollapsed((pi.ped->GetPosition() - TheCamera.GetPosition()).SquaredMagnitude() >= sq(m_collapseToggleDist));
    } else {
        SetNextWindowCollapsed(true, ImGuiCond_Once);
    }

    if (Begin(title, nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing)) {
        if (BeginTabBar("##tabbar")) {
            m_tasksDebug.ProcessPed(*pi.ped);
            m_generalDebug.ProcessPed(*pi.ped);

            EndTabBar();
        }
    }

    End();
}

// Called from inside a tab item
void Module::ProcessImGui() {
    m_perPedDebug.ProcessImGui();
}

void Module::ProcessRender() {
    m_perPedDebug.ProcessRender();
}
};
