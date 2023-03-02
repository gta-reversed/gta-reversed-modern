#include "StdInc.h"

#include "win.h"
#include <ddraw.h>
#include <dsound.h>

#include "platform.h"
#include "LoadingScreen.h"
#include "C_PcSave.h"

#define USE_D3D9

// TODO: Move these into premake/cmake
#ifndef USE_D3D9
#pragma comment(lib, "d3d8.lib")
#endif
#pragma comment(lib, "ddraw.lib")
#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "strmiids.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dsound.lib")

static auto& PsGlobal = StaticRef<psGlobalType, 0xC8CF88>();

//! Disable "This function was depracated"
#pragma warning (disable : 28159 4996)

// 0x7455E0 - Get available videomem
HRESULT GetVideoMemInfo(LPDWORD total, LPDWORD available) {
	LPDIRECTDRAW7 dd;

    if (HRESULT hr = DirectDrawCreateEx(NULL, (LPVOID*)&dd, IID_IDirectDraw7, NULL); FAILED(hr)) {
        return hr;
    }

	DDSCAPS2 caps;
	ZeroMemory(&caps, sizeof(DDSCAPS2));
	caps.dwCaps = DDSCAPS_VIDEOMEMORY;
	HRESULT hr = dd->GetAvailableVidMem(&caps, total, available);
	dd->Release();

    return hr;
}

//! Check if D3D9 can be loaded (Originally this checked for versions 7 => 9, but GTA can only run with 9, so... :D
BOOL CheckDirectX() {
    const auto hD3D9DLL = LoadLibrary("D3D9.DLL");
    if (hD3D9DLL == NULL) {
        return FALSE;
    }
    FreeLibrary(hD3D9DLL);
    return TRUE;
}

//! 0x745840 - Check if DirectSound can be loaded
BOOL CheckDirectSound() {
    LPDIRECTSOUND ds;

    if (FAILED(DirectSoundCreate(NULL, &ds, NULL))) {
        return FALSE;
    }

    DSCAPS  caps{ sizeof(DSCAPS) };
    HRESULT hr = ds->GetCaps(&caps);

    ds->Release();

    return SUCCEEDED(hr);
}

// 0x7465B0
void InitialiseLanguage() {
//#pragma warning (disable : 4302) // "Type truncation from HKL to 

    // TODO: Use `GetLocaleInfoEx`
    const auto sysDefaultLCID = PRIMARYLANGID(GetSystemDefaultLCID());
	const auto usrDefaultLCID = PRIMARYLANGID(GetUserDefaultLCID());
    const auto kbLayoutLCID   = PRIMARYLANGID(LOWORD(GetKeyboardLayout(0)));

	FrontEndMenuManager.m_nTitleLanguage = sysDefaultLCID;

    FrontEndMenuManager.m_nTextLanguage = (int32)[&] {
	    switch (kbLayoutLCID) {
		case LANG_GERMAN:  return eLanguage::GERMAN;
		case LANG_SPANISH: return eLanguage::SPANISH;
		case LANG_FRENCH:  return eLanguage::FRENCH;
		case LANG_ITALIAN: return eLanguage::ITALIAN;
		default:           return eLanguage::AMERICAN;
	    }
    }();

    FrontEndMenuManager.m_nPrefsLanguage = [&] {
        switch (usrDefaultLCID) {
        case LANG_SPANISH: return eLanguage::SPANISH;
        default:           return eLanguage::AMERICAN;
        }
    }();

    // Reload text
	TheText.Unload(false);
	TheText.Load(false);
}

// 0x747420
RwBool psInitialize() {
    auto ps = &PsGlobal;

    RsGlobal.ps = ps;

    ps->lastMousePos.y = 0.f;
    ps->lastMousePos.x = 0.f;
    ps->fullScreen    = FALSE;
    ps->diInterface   = NULL;
    ps->diMouse       = NULL;
    ps->diDevice1     = NULL;
    ps->diDevice2     = NULL;
    
    CFileMgr::Initialise();
    const auto usrdir = InitUserDirectories();
    s_PcSaveHelper.SetSaveDirectory(usrdir);

    gGameState = GAME_STATE_INITIAL;

    // TODO: Load vendor from CPUID

    // Figure out Windows version (TODO: Use `IsWindowsVersion*` from VersionHelpers.h instead)
    s_OSStatus.OSVer = [&] {
        OSVERSIONINFO verInfo{ sizeof(OSVERSIONINFO) };	
	    GetVersionEx(&verInfo);

        if (verInfo.dwPlatformId == VER_PLATFORM_WIN32_NT) {
            switch (const auto mv = verInfo.dwMajorVersion) {
            case 4:  return WinVer::WIN_NT;
            case 5:  return WinVer::WIN_2000_XP_2003;
            case 6:  return WinVer::WIN_VISTA_OR_LATER;
            default: return mv < 4 ? WinVer::WIN_NT : WinVer::WIN_VISTA_OR_LATER;
            }
        } else if (verInfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) {
            return verInfo.dwMajorVersion > 4 || verInfo.dwMajorVersion == 4 && verInfo.dwMinorVersion != 0
                ? WinVer::WIN_98
                : WinVer::WIN_95;
        }
        NOTSA_UNREACHABLE(); // If this is reached the game wouldn't run anyways, so might as well just crash it.
    }();

    if (s_OSStatus.OSVer == WinVer::WIN_95) {
        MessageBoxW(
            NULL,
            (LPCWSTR)TheText.Get("WIN_95"),	 // Grand Theft Auto San Andreas cannot run on Windows 95
            (LPCWSTR)TheText.Get("WIN_TTL"), // Grand Theft Auto San Andreas
            MB_OK
        );

        return FALSE;
    }

    // Originally figured out available dx version and only allowed dx9, but we've simplified it.
    if (!CheckDirectX()) {
        MessageBoxW(
            NULL,
            (LPCWSTR)TheText.Get("WIN_DX"),	 // Grand Theft Auto San Andreas requires at least DirectX version 8.1
            (LPCWSTR)TheText.Get("WIN_TTL"), // Grand Theft Auto San Andreas
            MB_OK
        );
        return FALSE;
    }

    // CheckDirectX() Checks for Dx9 only, so use that
    s_OSStatus.DxVer = 0x900;

    if (!CheckDirectSound()) {
        MessageBoxW(
            NULL,
            (LPCWSTR)TheText.Get("WIN_NSC"), // Grand Theft Auto San Andreas requires a sound card (I guess?)
            (LPCWSTR)TheText.Get("WIN_TTL"), // Grand Theft Auto San Andreas
            MB_ICONEXCLAMATION
        );
        return FALSE;
    }

    MEMORYSTATUS memstat{ sizeof(MEMORYSTATUS) };
    GlobalMemoryStatus(&memstat); // TODO: `GlobalMemoryStatusEx`
    s_OSStatus.RAM.TotalPhys    = memstat.dwTotalPhys;
    s_OSStatus.RAM.AvailPhys    = memstat.dwAvailPhys;
    s_OSStatus.RAM.TotalVirtual = memstat.dwTotalVirtual;
    s_OSStatus.RAM.AvailVirtual = memstat.dwAvailVirtual;

    VERIFY(SUCCEEDED(GetVideoMemInfo(&s_OSStatus.VRAM.Total, &s_OSStatus.VRAM.Avail)));
    VERIFY(SUCCEEDED(CoInitialize(NULL)));

    // Load setting only after everything was checked - TODO: Move this out from here, it's not platform specific
    FrontEndMenuManager.LoadSettings();

    return TRUE;
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
    auto flags = FrontEndMenuManager.m_bPrefsFrameLimiter || CLoadingScreen::m_bActive ? rwRASTERFLIPWAITVSYNC : rwRASTERFLIPDONTWAIT;
    return RwCameraShowRaster(camera, PSGLOBAL(window), flags);
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

void WinPsInjectHooks() {
    RH_ScopedCategory("Win");
    RH_ScopedNamespaceName("Ps");

    RH_ScopedGlobalInstall(psInitialize, 0x747420);
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

    RH_ScopedGlobalInstall(InitialiseLanguage, 0x7465B0);
    RH_ScopedGlobalInstall(CheckDirectSound, 0x745840);
    RH_ScopedGlobalInstall(GetVideoMemInfo, 0x7455E0);
}
