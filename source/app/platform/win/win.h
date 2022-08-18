#pragma once

static bool& anisotropySupportedByGFX = *(bool*)0xC87FFC;
static bool& isForeground = *(bool*)0xC920EC;
static bool& Windowed = *(bool*)0xC920CC;

void PsInjectHooks();
void Win32InjectHooks();
