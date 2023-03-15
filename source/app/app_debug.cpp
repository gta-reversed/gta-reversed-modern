#include "StdInc.h"

#include "app_debug.h"
#include <windows.h>
#include <DbgHelp.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#define FINAL 0

#ifndef FINAL
RtCharset* debugCharset;
bool g_bDebugRenderGroups;
#endif

#if !defined(FINAL)
static bool charsetOpen;
void OpenCharsetSafe() {
    if (!charsetOpen)
        RtCharsetOpen();
    charsetOpen = true;
}
#endif

// 0x734610
void CreateDebugFont() {
#ifndef FINAL
    RwRGBA color = { 255, 255, 128, 255 };
    RwRGBA colorbg = { 0, 0, 0, 0 };
    OpenCharsetSafe();
    debugCharset = RtCharsetCreate(&color, &colorbg);
#endif
}

// 0x734620
void DestroyDebugFont() {
#ifndef FINAL
    RtCharsetDestroy(debugCharset);
    RtCharsetClose();
    charsetOpen = false;
#endif
}

// unused
// 0x734630
void ObrsPrintfString(const char* str, int16 x, int16 y) {
#ifndef FINAL
    RtCharsetPrintBuffered(debugCharset, str, x * 8, y * 16, true);
#endif
}

// 0x734640
void FlushObrsPrintfs() {
#ifndef FINAL
    RtCharsetBufferFlush();
#endif
}

// This probably should be in winps :D
LONG WINAPI WindowsExceptionHandler(PEXCEPTION_POINTERS pExceptionInfo) {
    // If this function itself crashes it's invoked again
    // So let's prevent the recusion with this simple hack
    static bool s_HasHandled = false;
    if (s_HasHandled) {
        return EXCEPTION_CONTINUE_EXECUTION;
    }
    s_HasHandled = true;

    spdlog::dump_backtrace();

    const auto Section = [](const char* name) {
        SPDLOG_INFO("*********{}**********", name);
    };

    Section("UNHANDLED EXCEPTION");

    SPDLOG_INFO("Exception Code: {:#010x}", pExceptionInfo->ExceptionRecord->ExceptionCode);
    SPDLOG_INFO("Exception Flags: {:#010x}", pExceptionInfo->ExceptionRecord->ExceptionFlags);
    SPDLOG_INFO("Exception Address: {:#010x}", (uintptr_t)pExceptionInfo->ExceptionRecord->ExceptionAddress);

    // Dump exception parameters
    Section("PARAMTERS");
    SPDLOG_INFO("Parameters[{}]:", pExceptionInfo->ExceptionRecord->NumberParameters);
    for (DWORD i = 0; i < pExceptionInfo->ExceptionRecord->NumberParameters; i++) {
        SPDLOG_INFO("{:>8}: {:#010x}", i, pExceptionInfo->ExceptionRecord->ExceptionInformation[i]);
    }

    CONTEXT& context = *pExceptionInfo->ContextRecord;

    // Dump registers
    Section("REGISTERS");
    const auto DumpRegister = [](auto name, auto value) {
        SPDLOG_INFO("{:>8}: {:#010x}", name, value);
    };
    DumpRegister("EAX", context.Eax);
    DumpRegister("EBX", context.Ebx);
    DumpRegister("ECX", context.Ecx);
    DumpRegister("EDX", context.Edx);
    DumpRegister("ESI", context.Esi);
    DumpRegister("EDI", context.Edi);
    DumpRegister("EBP", context.Ebp);
    DumpRegister("ESP", context.Esp);
    DumpRegister("EIP", context.Eip);
    DumpRegister("EFLAGS", context.EFlags);

    // Dump call stack
    Section("CALL STACK");
    HANDLE hProcess = GetCurrentProcess();
    HANDLE hThread = GetCurrentThread();
    
    // Initialize symbol handler
    SymInitialize(hProcess, NULL, TRUE);

    STACKFRAME stackFrame = {};
    stackFrame.AddrPC.Mode = AddrModeFlat;
    stackFrame.AddrStack.Mode = AddrModeFlat;
    stackFrame.AddrFrame.Mode = AddrModeFlat;
    stackFrame.AddrPC.Offset = context.Eip;
    stackFrame.AddrStack.Offset = context.Esp;
    stackFrame.AddrFrame.Offset = context.Ebp;

    while (StackWalk(
        IMAGE_FILE_MACHINE_I386, hProcess, hThread, &stackFrame, &context, NULL,
        SymFunctionTableAccess, SymGetModuleBase, NULL))
    {
        DWORD symbolAddress = stackFrame.AddrPC.Offset;
        char symbolBuffer[sizeof(SYMBOL_INFO) + MAX_SYM_NAME] = { 0 };
        PSYMBOL_INFO pSymbol = (PSYMBOL_INFO)symbolBuffer;
        pSymbol->SizeOfStruct = sizeof(SYMBOL_INFO);
        pSymbol->MaxNameLen = MAX_SYM_NAME;

        if (SymFromAddr(hProcess, symbolAddress, NULL, pSymbol)) {
            SPDLOG_INFO("{:#010x}: {}", pSymbol->Address, &pSymbol->Name[0]);
        } else {
            SPDLOG_INFO("{:#010x}: [UNKNOWN]", symbolAddress);
        }   
    }

    // Cleanup symbol handler
    SymCleanup(hProcess);

    Section("END OF UNHANDLED EXCEPTION");

    // Close spdlog now, this way everything is flushed
    spdlog::shutdown();

    return EXCEPTION_EXECUTE_HANDLER;
}

void notsa::InitLogging() {
    // See https://github.com/gabime/spdlog/wiki/3.-Custom-formatting#pattern-flags
    spdlog::set_pattern("%^[%l][%H:%M:%S.%e][%s:%#]: %v%$");
    spdlog::default_logger()->sinks().emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/log.log"));
    spdlog::enable_backtrace(128);

    AddVectoredExceptionHandler(1, WindowsExceptionHandler);

    //*reinterpret_cast<int*>(rand()) = 1;
}

void notsa::ShutdownLogging() {
    spdlog::shutdown();
}

// Doesn't work as expected [console doesn't appear, etc... but would be nice to get this to work...]
//auto notsa::details::NewLogger(const char* name) -> std::shared_ptr<spdlog::logger> {
//    auto logger = spdlog::stdout_color_mt(name);
//    spdlog::initialize_logger(logger);
//    return logger;
//}
