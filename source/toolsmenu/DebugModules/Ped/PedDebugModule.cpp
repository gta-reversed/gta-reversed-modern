#include "StdInc.h"
#include "PedDebugModule.h"
#include "Pools.h"
#include "TaskManager.h"
#include "Hud.h"
#include <format>

// Define extra conversion function from our vector type to imgui's vec2d
#define IM_VEC2_CLASS_EXTRA \
    operator CVector2D() const { return {x, y}; } \
    ImVec2(const CVector2D& v) : x{v.x}, y{v.y} {} \

#include <imgui.h>

using namespace ImGui;

namespace Tasks {
void ProcessTask(CTask* task) {
    const auto taskType = task->GetTaskType();
    PushID((int)taskType);
    if (TreeNodeEx(GetTaskTypeName(taskType), ImGuiTreeNodeFlags_DefaultOpen)) {
        if (const auto sub = task->GetSubTask()) {
            ProcessTask(sub);
        }
        TreePop();
    }
    PopID();
}

/*!
* @brief Process category, eg.: secondary or primary
*/
void ProcessTaskCategory(const char* label, const auto& tasks) {
    if (TreeNodeEx(label, ImGuiTreeNodeFlags_DefaultOpen)) {
        for (const auto task : tasks) {
            if (task) {
                ProcessTask(task);
            }
        }
        TreePop();
    }
}

/*!
* @brief Process a single ped. This is call is done within a imgui window
*/
void ProcessPed(CPed& ped) {
    if (BeginChild("Tasks")) {
        auto& taskMgr = ped.GetTaskManager();
        ProcessTaskCategory("Primary", taskMgr.GetPrimaryTasks());
        ProcessTaskCategory("Secondary", taskMgr.GetSecondaryTasks());        
    }
    EndChild();
}
};

namespace {
void ProcessPed(CPed& ped) {
    if (!ped.GetIsOnScreen()) {
        return;
    }
    const auto remap = [](auto value, auto low1, auto high1, auto low2, auto high2) {
        return low2 + (value - low1) * (high2 - low2) / (high1 - low1);
    };
    if (CVector pedHeadOnScreenPos{}; CalcScreenCoors(ped.GetBonePosition(BONE_HEAD) + ped.GetRightVector() * 0.5f, &pedHeadOnScreenPos)) {
        const auto depth = pedHeadOnScreenPos.z;

        if (depth > 100.f) {
            return; // Too distant
        }

        SetNextWindowPos(ImVec2{ pedHeadOnScreenPos.x, pedHeadOnScreenPos.y });

        SetNextWindowSize(CVector2D{ 400, 200 } / remap(depth, 0.f, 100.f, 1.f, 4.f));

        // Format a title with a custom ID that should hopefully match only this ped
        char title[1024];
        *std::format_to(title, "Ped Debug###{}{}", (ptrdiff_t)(&ped), ped.m_nRandomSeed) = 0; // Null terminate :D

        const auto OPEN_STATE_KEY = std::hash<std::string_view>{}({"OpenState"});
        bool open = GetStateStorage()->GetBool(OPEN_STATE_KEY, true);
        if (Begin(title, &open, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings)) {
            //const auto scale = pedHeadOnScreenPos.z;
            //SetWindowSize(CVector2D(GetWindowSize()) / scale); // Scale down by depth
            Tasks::ProcessPed(ped);
            //SetWindowSize(CVector2D(GetWindowSize()) * scale); // Scale back, this way user resizes are preserved (hopefully?)
        }
        GetStateStorage()->SetBool(OPEN_STATE_KEY, open);

        End();
    } else {
        DEV_LOG("Failed to calculate on-screen coords of ped");
    }
}
};

namespace PedDebugModule{ 
void ProcessImGui() {
    rng::for_each(GetPedPool()->GetAllValid(), ProcessPed);
}

void ProcessRender() {

}
};
