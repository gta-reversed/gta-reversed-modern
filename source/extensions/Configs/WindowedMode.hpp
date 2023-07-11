#pragma once
#include <cassert>
#include "extensions/Configuration.hpp"

inline struct WindowedModeConfig {
    INI_CONFIG_SECTION("WindowedMode");

    uint32 WindowWidth{640};
    uint32 WindowHeight{480};
    
    void Load() {
        STORE_INI_CONFIG_VALUE(WindowWidth, 640);
        STORE_INI_CONFIG_VALUE(WindowHeight, 480);
    }
} g_WindowedModeConfig{};
