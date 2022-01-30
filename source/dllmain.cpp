// dllmain.cpp : Defines the entry point for the DLL application.
#include "StdInc.h"

#include "config.h"

void InjectHooksMain();

void DisplayConsole()
{
    if (AllocConsole())
    {
        freopen("CONIN$", "r", stdin);
        freopen("CONOUT$", "w", stdout);
        freopen("CONOUT$", "w", stderr);
    }
}

void WaitForDebugger() {
    while (!::IsDebuggerPresent()) {
        printf("Debugger not present\n");
        ::Sleep(100);
    }
}

namespace CommandLineArguments {

std::vector<std::wstring> Get() {
    std::vector<std::wstring> out;
    int numArgs{0};
    LPWSTR* szArgs = CommandLineToArgvW(GetCommandLineW(), &numArgs);
    out.reserve(numArgs);
    if (szArgs) {
        for (int i = 0; i < numArgs; i++) {
            out.emplace_back(szArgs[i]);
        }
    }
    LocalFree(szArgs);
    return out;
}

void Process() {
    using namespace std::literals;
    const auto args = Get();
    for (const auto& arg : args) {
        if (arg == L"--debug") {
            WaitForDebugger();
        }
    }
}

}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        RwCamera * pRwCamera = *(RwCamera**)0xC1703C;

        // Fail if RenderWare has already been started
        if (pRwCamera)
        {
            MessageBox(NULL, "gta_reversed failed to load (RenderWare has already been started)", "Error", MB_ICONERROR | MB_OK);
            return FALSE;
        }

        DisplayConsole();
        CommandLineArguments::Process();
        InjectHooksMain();
        break;
    }
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

