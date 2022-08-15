/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#define PLUGIN_API

#define VALIDATE_SIZE(struc, size) static_assert(sizeof(struc) == size, "Invalid structure size of " #struc)
#define VALIDATE_OFFSET(struc, member, offset) \
	static_assert(offsetof(struc, member) == offset, "The offset of " #member " in " #struc " is not " #offset "...")

VALIDATE_SIZE(bool, 1);
VALIDATE_SIZE(char, 1);
VALIDATE_SIZE(short, 2);
VALIDATE_SIZE(int, 4);
VALIDATE_SIZE(float, 4);
VALIDATE_SIZE(long long, 8);

// Use this to add const that wasn't there in the original code
#define Const const

#define NOTASA_ASSERT assert

// Basic types for structures describing
typedef int8_t    int8;
typedef int16_t   int16;
typedef int32_t   int32;
typedef int64_t   int64;
typedef uint8_t   uint8;
typedef uint16_t  uint16;
typedef uint32_t  uint32;
typedef uint64_t  uint64;
typedef intptr_t  intptr;
typedef uintptr_t uintptr;

typedef uint8     bool8;
typedef uint16    bool16;
typedef uint32    bool32;

// Use the `NOTSA_UNREACHABLE` macro for unreachable code paths.
// In debug mode it will do a DebugBreak() and print a message to the console,
// while in release code it'll be optimized away (by using special compiler directives)
// Also serves as a way to supress compiler warnings (for example, when you don't have need a `default` case in a `switch`)
#if _DEBUG
#include <format>

namespace notsa {
template<typename... Ts>
static void unreachable(const char* method, const char* file, int line, std::string_view fmt = "", Ts&&... fmtArgs) {
    const auto usrMsg = std::vformat(fmt, std::make_format_args(std::forward<Ts>(fmtArgs)...));
    std::cout << std::format("[{}:{}:{}]: Unreachable code reached! Details: {}\n", file, method, line, usrMsg.empty() ? "None" : usrMsg);
    DebugBreak();
}
};
// TODO/NOTE: We might need to manually suppress warnings here?
// Since all the code here is perfectly valid, so the compiler might
// still complain that, for example, the function doesn't return on all code paths, etc
#define NOTSA_UNREACHABLE(...) do { notsa::unreachable(__FUNCTION__, __FILE__, __LINE__ __VA_OPT__(,) ##__VA_ARGS__); } while (false)
#else
#if __has_builtin(__builtin_unreachable)
#define NOTSA_UNREACHABLE(...) __builtin_unreachable()
#elif defined(_MSC_VER)
#define NOTSA_UNREACHABLE(...) __assume(false)
#endif
#endif
// Macro for unused function arguments - Use it to avoid compiler warnings of unused arguments
#define UNUSED(x) (void)(x);

// Macro for unused function return values.
// Eventually could instead verify the returned value? In case of `sscanf` etc...
#define RET_IGNORED(x) (void)(x);

#define _IGNORED_
#define _CAN_BE_NULL_

#if (defined(__GNUC__) || defined(__GNUG__) || defined(__clang__))
#define PLUGIN_SOURCE_FILE
#define PLUGIN_VARIABLE
#define _NOINLINE_
#elif (defined(_MSC_VER))
#define PLUGIN_SOURCE_FILE  __pragma(init_seg(lib))
#define PLUGIN_VARIABLE
#define _NOINLINE_ __declspec(noinline)
#else
#define PLUGIN_SOURCE_FILE
#define PLUGIN_VARIABLE
#define _NOINLINE_
#endif

// III/VC char > wchar_t string conversion
#define _SWSTRING_INIT(str, id) std::wstring my_ws##id; for (size_t i = 0; i < strlen(str); i++) my_ws##id += str[i]
#define _SWSTRING(id) const_cast<wchar_t *>(my_ws##id.c_str())
#define _SWSTRING_STATIC_INIT(id) static wchar_t my_ws##id[512] ; my_ws##id[0] = 0
#define _SWSTRING_STATIC(id) my_ws##id
#define _SWSTRING_STATIC_FROM(id, src) for (size_t i = 0; i < strlen(src); i++) my_ws##id[i] = src[i]
#define _SWSTRING_STATIC_TO(id, dst) for (size_t i = 0; i < wcslen(my_ws##id); i++) dst[i] = static_cast<char>(my_ws##id[i])
