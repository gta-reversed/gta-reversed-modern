#pragma once
//#include "common.h"

namespace notsa {
namespace detail {
static void VerifyMacroImpl(bool result) {
    assert(result); // In release mode this won't do anything
}
};
};

#define VERIFY notsa::detail::VerifyMacroImpl

#ifdef _DEBUG
namespace notsa {

template<typename... Ts>
static void DevPrint(int lineno, std::string_view file, std::string_view fmt, Ts&&... fmtArgs) {
    const auto userFormat = std::vformat(fmt, std::make_format_args(std::forward<Ts>(fmtArgs)...));
    std::cout << std::format("[{} @ {}] {}", fs::relative(file, SOURCE_PATH).string(), lineno, userFormat);

    if (fmt.back() != '\n') {
        std::cout << std::endl;
    }
}
};
// WARNING: Use std::format specifiers! Use LOG_PTR macro for pointer arguments.
#define DEV_LOG(...) notsa::DevPrint(__LINE__, __FILE__, ##__VA_ARGS__)
#define LOG_PTR(x) ((const void*)x)
#else
#define DEV_LOG(...)
#define LOG_PTR(x)
#endif

#define PUSH_RENDERGROUP(str) 0
#define POP_RENDERGROUP() 0

void CreateDebugFont();
void DestroyDebugFont();
void ObrsPrintfString(const char* str, int16 x, int16 y);
void FlushObrsPrintfs();
