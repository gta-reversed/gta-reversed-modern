#include "StdInc.h"

#include "oswrapper.h"

#include <windows.h>

// 0x5617A0
std::uint64_t GetOSWPerformanceTime() {
    LARGE_INTEGER PerformanceCount = { 0 };
    ::QueryPerformanceCounter(&PerformanceCount);
    return PerformanceCount.QuadPart;
}

std::int64_t GetOSWPerformanceFrequency() {
    LARGE_INTEGER frequency;
    ::QueryPerformanceFrequency(&frequency);
    return frequency.QuadPart;
}