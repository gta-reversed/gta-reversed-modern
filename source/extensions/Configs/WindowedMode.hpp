#pragma once
#include <cassert>
#include "extensions/Configuration.hpp"

inline struct WindowedModeConfig {
    INI_CONFIG_SECTION("WindowedMode");

    uint32 WindowWidth{800};
    uint32 WindowHeight{600};
    bool Centered{true};
    
    void Load() {
        STORE_INI_CONFIG_VALUE(WindowWidth, 800);
        STORE_INI_CONFIG_VALUE(WindowHeight, 600);
        STORE_INI_CONFIG_VALUE(Centered, true);
    }
} g_WindowedModeConfig{};
