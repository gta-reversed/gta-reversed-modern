#ifdef EXTRA_DEBUG_FEATURES
#pragma once

struct ImGuiContext;

namespace TeleportDebugModule {
    void TeleportTo(const CVector& pos, eAreaCodes areaCode = eAreaCodes::AREA_CODE_NORMAL_WORLD);
    void ProcessImGui();
    void ProcessInput();
    void Initialise(ImGuiContext& ctx);
};
#endif
