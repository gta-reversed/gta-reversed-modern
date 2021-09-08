#pragma once

enum class eOnscreenCounter : uint16 {
    SIMPLE = 0, // counter (%)
    LINE   = 1,
    DOUBLE = 2 // counter/counter (%/%)
};

enum class eTimerDirection : uint8 {
    INCREASE,
    DECREASE,
};