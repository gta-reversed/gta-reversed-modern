#include "StdInc.h"

#include "win.h"

#include "platform.h"
#include "LoadingScreen.h"

void WinPsInjectHooks() {
    RH_ScopedCategory("Win");
    RH_ScopedNamespaceName("Ps");

    RH_ScopedGlobalInstall(psInitialize, 0x747420, {.reversed = false});
    RH_ScopedGlobalInstall(psTerminate, 0x7458A0);
    RH_ScopedGlobalInstall(psWindowSetText, 0x7451B0);
    RH_ScopedGlobalInstall(psErrorMessage, 0x7451D0);
    RH_ScopedGlobalInstall(psWarningMessage, 0x7451F0);
    RH_ScopedGlobalInstall(psCameraBeginUpdate, 0x745210);
    RH_ScopedGlobalInstall(psCameraShowRaster, 0x745240);
    RH_ScopedGlobalInstall(psTimer, 0x745270);
    RH_ScopedGlobalInstall(psGrabScreen, 0x7452B0);
    RH_ScopedGlobalInstall(psMouseSetVisibility, 0x7453E0);
    RH_ScopedGlobalInstall(psMouseSetPos, 0x7453F0);
    RH_ScopedGlobalInstall(psPathnameCreate, 0x745470);
    RH_ScopedGlobalInstall(psPathnameDestroy, 0x7454E0);
    RH_ScopedGlobalInstall(psPathGetSeparator, 0x745500);
    RH_ScopedGlobalInstall(psInstallFileSystem, 0x745520);
    RH_ScopedGlobalInstall(psNativeTextureSupport, 0x745530);
    RH_ScopedGlobalInstall(psDebugMessageHandler, 0x745540);
    RH_ScopedGlobalInstall(psAlwaysOnTop, 0x7458B0);
    RH_ScopedGlobalInstall(psSelectDevice, 0x746190, {.reversed = false});
}

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
    MessageBoxA(nullptr, str, RsGlobal.appName, MB_ICONWARNING | MB_TASKMODAL | MB_TOPMOST);
}

// 0x745210
bool psCameraBeginUpdate(RwCamera* camera) {
    if (RwCameraBeginUpdate(Scene.m_pRwCamera)) {
        return true;
    }
    RsEventHandler(rsACTIVATE, nullptr);
    return false;
}

// 0x745240
RwCamera* psCameraShowRaster(RwCamera* camera) {
    return RwCameraShowRaster(
        camera,
        PSGLOBAL(window),
        FrontEndMenuManager.m_bPrefsFrameLimiter || CLoadingScreen::m_bActive
            ? rwRASTERFLIPWAITVSYNC
            : rwRASTERFLIPDONTWAIT
    );
}

// 0x745270
uint32 psTimer() {
    return OS_TimeMS();
}

// 0x7452B0
RwImage* psGrabScreen(RwCamera* camera) {
    auto* device = static_cast<IDirect3DDevice9*>(RwD3D9GetCurrentD3DDevice());
    assert(device);

    D3DDISPLAYMODE displayMode{};
    VERIFY(SUCCEEDED(device->GetDisplayMode(0, &displayMode)));

    IDirect3DSurface9* surface = nullptr;
    VERIFY(SUCCEEDED(device->CreateOffscreenPlainSurface(displayMode.Width, displayMode.Height, D3DFMT_A8R8G8B8, D3DPOOL_SYSTEMMEM, &surface, nullptr)));
    VERIFY(SUCCEEDED(device->GetFrontBufferData(0, surface)));

    D3DLOCKED_RECT lockedRect{};
#ifndef FIX_BUGS
    // It's not needed as ClientToScreen func works with fullscreen mode.
    if (PSGLOBAL(fullScreen)) { // todo: Doesn't work properly with III.VC.SA.WindowedMode.asi
        VERIFY(SUCCEEDED(surface->LockRect(&lockedRect, nullptr, D3DLOCK_READONLY)));
    } else {
#endif
        RECT rect;
#ifdef FIX_BUGS
        // SA code gets the whole window of the game, which includes the titlebar etc.
        //
        // BUG: There should be bugs for older versions of Windows IIRC.
        // One example would be Vista version of the func doesn't count Aero effects of windows.
        //
        // TODO: Test with dual monitors etc.

        GetClientRect(PSGLOBAL(window), &rect);

        // GetClientRect returns relative positions unlike GetWindowRect.
        // i.e. will return { 0, 0, width, height }.
        ClientToScreen(PSGLOBAL(window), (POINT*)(&rect)); // kinda hacky but should work.
        rect.right += rect.left;
        rect.bottom += rect.top;
#else
        GetWindowRect(PSGLOBAL(window), &rect);
#endif
        displayMode.Height = rect.bottom - rect.top;
        displayMode.Width = rect.right - rect.left;
        VERIFY(SUCCEEDED(surface->LockRect(&lockedRect, &rect, D3DLOCK_READONLY)));
#ifndef FIX_BUGS
    }
#endif

    RwImage* image = RwImageCreate(int32(displayMode.Width), int32(displayMode.Height), 32);
    if (image) {
        RwImageAllocatePixels(image);

        auto* pixels = (RwRGBA*)RwImageGetPixels(image);
        auto* imagePixels = (uint8*)lockedRect.pBits;
        assert(pixels && imagePixels);

        for (auto h = 0u; h < displayMode.Height; h++) {
            for (auto w = 0u; w < displayMode.Width; w++) {
                pixels->red   = imagePixels[sizeof(RwRGBA) * w + 2];
                pixels->green = imagePixels[sizeof(RwRGBA) * w + 1];
                pixels->blue  = imagePixels[sizeof(RwRGBA) * w + 0];
                pixels->alpha = 255;
                pixels++;
            }
            imagePixels += lockedRect.Pitch;
        }
    }

    { // FIX_BUGS
        surface->UnlockRect();
        surface->Release();
        delete surface;
    }

    return image;
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
    const auto pathSize = std::strlen(buffer) + 1u;
    auto path = (char*)CMemoryMgr::Malloc(pathSize);
    if (path) {
        strcpy_s(path, pathSize, buffer);

        while (auto ch = std::strchr(path, '/')) {
            *ch = psPathGetSeparator();
        }
    }

    return path;
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
