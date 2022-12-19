#include "StdInc.h"
#include "WaterLevelDebugModule.hpp"
#include "WaterLevel.h"

#include <imgui.h>

namespace WaterLevelDebugModule {
void ProcessImGui() {
    using namespace ImGui;

    Checkbox("Skip Camera Range Update", &CWaterLevel::DontUpdateCameraRange);
    Checkbox("Don't render Y split tri", &CWaterLevel::DontRenderYSplitTri);

    const auto ColorEditRGBA = [](const char* name, CRGBA& inOutColor) {
        RwRGBAReal colorToEdit = inOutColor;
        if (ColorEdit4(name, (float*)&colorToEdit)) {
            inOutColor = CRGBA{ colorToEdit };
        }
    };

    ColorEditRGBA("Triangle Water Color", CWaterLevel::DebugWaterColorTriangle);

    // Doesn't work (Color is always set to be the same as TimeCyc's water color -> Edit that instead)
    //DoWaterColorEdit("Triangle Water Color", CWaterLevel::WaterColorTriangle);
    //DoWaterColorEdit("Quad Water Color", CWaterLevel::WaterColor);

    // Doesn't work (Alpha is set each frame in the code, so this doesn't work)
    //for (auto& alpha : CWaterLevel::WaterLayerAlpha) {
    //    SliderInt("Water Layer Alpha", (int*)&alpha, 0, 255);
    //}
}
}; // namespace WaterLevelDebugModule
