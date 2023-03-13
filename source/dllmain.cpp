// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "StdInc.h"

#include "config.h"

void InjectHooksMain(HMODULE hThisDLL);

void DisplayConsole()
{
    if (AllocConsole()) {
        FILESTREAM fs{};
        VERIFY(freopen_s(&fs, "CONIN$",  "r", stdin)  == NOERROR);
        VERIFY(freopen_s(&fs, "CONOUT$", "w", stdout) == NOERROR);
        VERIFY(freopen_s(&fs, "CONOUT$", "w", stderr) == NOERROR);
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

} // namespace CommandLineArguments

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        // Fail if RenderWare has already been started
        if (*(RwCamera**)0xC1703C)
        {
            MessageBox(NULL, "gta_reversed failed to load (RenderWare has already been started)", "Error", MB_ICONERROR | MB_OK);
            return FALSE;
        }

        DisplayConsole();
        CommandLineArguments::Process();
        InjectHooksMain(hModule);
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
