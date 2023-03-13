#pragma once

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include <spdlog/spdlog.h>

namespace notsa {
void InitLogging();
void ShutdownLogging();

namespace detail {
static void VerifyMacroImpl(bool result) {
    assert(result); // In release mode this won't do anything
}
};
};

#define VERIFY notsa::detail::VerifyMacroImpl
#define VERIFY_TODO_FIX(_expr) (_expr) // Macro used to mark shit that uses `VERIFY and sometimes fails

//! Use this to pass pointers to logging functions
#define LOG_PTR(x) ((const void*)x)

#define DEV_LOG SPDLOG_INFO
#define NOTSA_LOG_CRIT SPDLOG_CRITICAL
#define NOTSA_LOG_ERR SPDLOG_ERROR
#define NOTASA_LOG_TRACE SPDLOG_TRACE
#define PUSH_RENDERGROUP(str) 0
#define POP_RENDERGROUP() 0

void CreateDebugFont();
void DestroyDebugFont();
//void ObrsPrintfString(const char* str, int16 x, int16 y);
void FlushObrsPrintfs();
