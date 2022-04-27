#include "StdInc.h"

#include "win.h"

#include "platform.h"
#include "LoadingScreen.h"

// 0x747420
bool psInitialize() {
    return plugin::CallAndReturn<bool, 0x747420>();
}

// 0x7458A0
void psTerminate() {
    // NOP
}

// 0x7451B0
void psWindowSetText(const char* str) {
    SetWindowTextA(PSGLOBAL(window), str);
}

// 0x7451D0
void psErrorMessage(const char* str) {
    MessageBoxA(nullptr, str, RsGlobal.appName, MB_ICONERROR | MB_TASKMODAL | MB_TOPMOST);
}

// 0x7451F0
void psWarningMessage(const char* str) {
    MessageBox(nullptr, str, RsGlobal.appName, MB_ICONWARNING | MB_TASKMODAL | MB_TOPMOST);
}

// 0x745210
bool psCameraBeginUpdate(RwCamera* camera) {
    return plugin::CallAndReturn<bool, 0x745210, RwCamera*>(camera);

    /*
    if (RwCameraBeginUpdate(Scene.m_pRwCamera)) {
        return true;
    }
    RsEventHandler(rsACTIVATE, nullptr);
    return false;
    */
}

// 0x745240
RwCamera* psCameraShowRaster(RwCamera* camera) {
    auto flags = FrontEndMenuManager.m_bPrefsFrameLimiter || CLoadingScreen::m_bActive ? rwRASTERFLIPWAITVSYNC : rwRASTERFLIPDONTWAIT;
    return RwCameraShowRaster(camera, PSGLOBAL(window), flags);
}

// 0x745270
uint32 psTimer() {
    return OS_TimeMS();
}

// 0x7452B0
RwImage* psGrabScreen(RwCamera* camera) {
    return plugin::CallAndReturn<RwImage*, 0x7452B0, RwCamera*>(camera);
}

// 0x7453E0
void psMouseSetVisibility(bool visible) {
    ::ShowCursor(visible);
}

// 0x7453F0
void psMouseSetPos(RwV2d* pos) {
    POINT point = { .x = LONG(pos->x), .y = LONG(pos->y) };
    ::ClientToScreen(PSGLOBAL(window), &point);
    ::SetCursorPos(point.x, point.y);
    PSGLOBAL(lastMousePos) = *pos;
}

// 0x745470
char* psPathnameCreate(const char* buffer) {
    return plugin::CallAndReturn<char*, 0x745470, const char*>(buffer);
}

// 0x7454E0
void psPathnameDestroy(char* buffer) {
    if (buffer) {
        RwFree(buffer);
    }
}

// 0x745500
char psPathGetSeparator() {
    return '\\';
}

// 0x745520
bool psInstallFileSystem() {
    return true;
}

// 0x745530
bool psNativeTextureSupport() {
    return RwD3D9DeviceSupportsDXTTexture();
}

// 0x745540
RsEventStatus psDebugMessageHandler(RsEvent event, void* param) {
    if (rsINITDEBUG == event) {
        RwDebugSetHandler(psDebugMessageHandler);
#if defined(DEBUG) && defined(RWTRACE)
        RwDebugSetTraceState(true);
#else
        RwDebugSetTraceState(false);
#endif
    }

    return rsEVENTNOTPROCESSED;
}

// 0x7458B0
bool psAlwaysOnTop(bool alwaysOnTop) {
    RECT winRect;

    HWND hwnd = PSGLOBAL(window);
    GetWindowRect(hwnd, &winRect);

    if (alwaysOnTop) {
        return (bool)SetWindowPos(hwnd, HWND_TOPMOST, winRect.left, winRect.top, winRect.right - winRect.left, winRect.bottom - winRect.top, 0);
    } else {
        return (bool)SetWindowPos(hwnd, HWND_NOTOPMOST, winRect.left, winRect.top, winRect.right - winRect.left, winRect.bottom - winRect.top, 0);
    }
}

// 0x746190
bool psSelectDevice() {
    return plugin::CallAndReturn<bool, 0x746190>();
}
