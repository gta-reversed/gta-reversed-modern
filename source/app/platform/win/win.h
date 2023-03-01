#pragma once

#define APP_CLASS "Grand theft auto San Andreas"

#define JIF(x) do { \
        if (FAILED(hr=(x))) { \
	        DEV_LOG(TEXT("FAILED(hr=0x{:x}) in ") TEXT(#x) TEXT("\n"), (size_t)(hr)); \
            return; \
        } \
    } while (0) \

static bool& anisotropySupportedByGFX = *(bool*)0xC87FFC;
static bool& isForeground = *(bool*)0xC920EC;
static bool& Windowed = *(bool*)0xC920CC;

void Win32InjectHooks();

#define IDD_DIALOG1                     104
#define IDC_DEVICESEL                   1000
#define IDC_VIDMODE                     1001
#define IDEXIT                          1002
#define IDC_SELECTDEVICE                1005

#define IDI_MAIN_ICON                   1042
