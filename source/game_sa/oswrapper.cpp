#include "StdInc.h"

#include "oswrapper.h"

#include <windows.h>

// 0x5617A0
uint64 GetOSWPerformanceTime() {
    LARGE_INTEGER PerformanceCount = { 0 };
    ::QueryPerformanceCounter(&PerformanceCount);
    return PerformanceCount.QuadPart;
}

int64 GetOSWPerformanceFrequency() {
    LARGE_INTEGER frequency;
    ::QueryPerformanceFrequency(&frequency);
    return frequency.QuadPart;
}