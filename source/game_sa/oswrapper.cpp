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

bool IsWin7OrGreater() {
#ifdef _WIN32
    OSVERSIONINFOEXW osvi = { sizeof(osvi), 0, 0, 0, 0, {0}, 0, 0 };
    DWORDLONG        const dwlConditionMask = VerSetConditionMask(
            VerSetConditionMask(
                    VerSetConditionMask(0, VER_MAJORVERSION, VER_GREATER_EQUAL),
                    VER_MINORVERSION, VER_GREATER_EQUAL
            ),
            VER_SERVICEPACKMAJOR, VER_GREATER_EQUAL
    );

    osvi.dwMajorVersion = HIBYTE(_WIN32_WINNT_WIN7);
    osvi.dwMinorVersion = LOBYTE(_WIN32_WINNT_WIN7);
    osvi.wServicePackMajor = 0;

    return VerifyVersionInfoW(&osvi, VER_MAJORVERSION | VER_MINORVERSION | VER_SERVICEPACKMAJOR, dwlConditionMask) != FALSE;
#else
    return false;
#endif
}
