#include "StdInc.h"
#include "WaterLevelDebugModule.hpp"
#include "WaterLevel.h"

#include <imgui.h>

namespace WaterLevelDebugModule {
void ProcessImGui() {
    using namespace ImGui;

    Checkbox("Skip Camera Range Update", &CWaterLevel::DontUpdateCameraRange);

    //const auto DoWaterColorEdit = [](const char* name, auto& inOutColorRGB) {
    //    RwRGBAReal colorToEdit = inOutColorRGB;
    //    ColorEdit3(name, (float*)&colorToEdit); // Ignoring alpha
    //    inOutColorRGB = CRGBA{ colorToEdit };
    //};

    // Doesn't work (Color is always set to be the same as TimeCyc's water color -> Edit that instead)
    //DoWaterColorEdit("Triangle Water Color", CWaterLevel::WaterColorTriangle);
    //DoWaterColorEdit("Quad Water Color", CWaterLevel::WaterColor);

    // Doesn't work (Alpha is set each frame in the code, so this doesn't work)
    //for (auto& alpha : CWaterLevel::WaterLayerAlpha) {
    //    SliderInt("Water Layer Alpha", (int*)&alpha, 0, 255);
    //}
}
}; // namespace WaterLevelDebugModule
