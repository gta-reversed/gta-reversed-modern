#pragma once

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include <spdlog/spdlog.h>
#include <spdlog/logger.h>

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

//! Use this to pass pointers to logging functions [both std::format, logs, and printf-style stuff]
// We're casting to uintptr_t, because formatting just works better that way
#define LOG_PTR(x) ((uintptr_t)(x))
static_assert(sizeof(void*) == sizeof(uintptr_t));

#define DEV_LOG SPDLOG_INFO
#define NOTSA_LOG_CRIT SPDLOG_CRITICAL
#define NOTSA_LOG_ERR SPDLOG_ERROR
#define NOTSA_LOG_TRACE SPDLOG_TRACE
#define PUSH_RENDERGROUP(str) 0
#define POP_RENDERGROUP() 0

namespace notsa::details {
auto NewLogger(const char* name) -> std::shared_ptr<spdlog::logger>;
};
#define NOTSA_MAKE_LOGGER notsa::details::NewLogger

void CreateDebugFont();
void DestroyDebugFont();
//void ObrsPrintfString(const char* str, int16 x, int16 y);
void FlushObrsPrintfs();
