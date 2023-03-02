#pragma once

#include <windows.h>

LRESULT CALLBACK NOTSA_WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void InjectHooksWndProcStuff();
