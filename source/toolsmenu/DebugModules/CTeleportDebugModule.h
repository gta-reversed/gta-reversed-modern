#ifdef EXTRA_DEBUG_FEATURES
#pragma once

struct ImGuiContext;
namespace TeleportDebugModule {
    void ProcessImGui();
    void ProcessRender();
    void Initialise(ImGuiContext& ctx);
};
#endif
