/*
    Plugin-SDK (Grand Theft Auto) SHARED header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include <cstddef>
#include <cstdint>

#include "Base.h"

namespace plugin {
int GetBaseAddress();

int GetGlobalAddress(int address);

// helpers for constructor overloading (deprecated)

struct dummy_func_t {};          // Dummy func tag type
static const dummy_func_t dummy; // Dummy func tag object

// meta template for functions
#if (defined(__GNUC__) || defined(__GNUG__) || defined(__clang__))
template <auto Func> struct meta;
#elif (defined(_MSC_VER))
template <typename FuncType, FuncType Func> struct meta;
#else

#endif

// vtable description
template <typename ClassType> struct vtable_meta;

// Gets the virtual method table from the object @self
inline void** GetVMT(const void* self) {
    return *(void***)(self);
}

// Gets the virtual method from @self in the table index @index
inline void* GetVMT(const void* self, size_t index) {
    return GetVMT(self)[index];
}

template <unsigned int address, typename... Args> void Call(Args... args) {
    reinterpret_cast<void(__cdecl*)(Args...)>(address)(args...);
}

template <typename Ret, unsigned int address, typename... Args> Ret CallAndReturn(Args... args) {
    return reinterpret_cast<Ret(__cdecl*)(Args...)>(address)(args...);
}

template <unsigned int address, typename C, typename... Args> void CallMethod(C _this, Args... args) {
    reinterpret_cast<void(__thiscall*)(C, Args...)>(address)(_this, args...);
}

template <typename Ret, unsigned int address, typename C, typename... Args> Ret CallMethodAndReturn(C _this, Args... args) {
    return reinterpret_cast<Ret(__thiscall*)(C, Args...)>(address)(_this, args...);
}

template <unsigned int tableIndex, typename C, typename... Args> void CallVirtualMethod(C _this, Args... args) {
    reinterpret_cast<void(__thiscall*)(C, Args...)>((*reinterpret_cast<void***>(_this))[tableIndex])(_this, args...);
}

template <typename Ret, unsigned int tableIndex, typename C, typename... Args> Ret CallVirtualMethodAndReturn(C _this, Args... args) {
    return reinterpret_cast<Ret(__thiscall*)(C, Args...)>((*reinterpret_cast<void***>(_this))[tableIndex])(_this, args...);
}

} // namespace plugin

// vtable description - macro

#define VTABLE_DESC(className, vtAddr, vtSize)                                                                                                                                     \
    namespace plugin {                                                                                                                                                             \
    template <> struct vtable_meta<className> {                                                                                                                                    \
        static const unsigned int address = vtAddr;                                                                                                                                \
        static const unsigned int size = vtSize;                                                                                                                                   \
    };                                                                                                                                                                             \
    }

// custom object construction

#define PLUGIN_NO_DEFAULT_CONSTRUCTION(className)                                                                                                                                  \
    className() = delete;                                                                                                                                                          \
    className(className const&) = delete;                                                                                                                                          \
    className(className&&) = delete;                                                                                                                                               \
    ~className() = delete;                                                                                                                                                         \
    className& operator=(className&&) = delete;

#define PLUGIN_NO_DEFAULT_CONSTRUCTION_VIRTUALBASE(className)                                                                                                                      \
    className() = delete;                                                                                                                                                          \
    className(className const&) = delete;                                                                                                                                          \
    className(className&&) = delete;                                                                                                                                               \
    virtual ~className() = delete;                                                                                                                                                 \
    className& operator=(className&&) = delete;
