#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include "HookSystem.h"

//
// Helper macros - For help regarding usage see how they're used (`Find all references` and take a look)
// Generally on top of `InjectHooks` you will need to call `RH_ScopedClass` (or `RH_ScopedNamespace`) and `RH_ScopedCategory`
// `RH_ScopedCategory` generally follows the directory layout - Anything in, lets say, the `Entity` directory should be in the `Entity` category.
// The root folder (source/game_sa) can be referred to by `RH_ScopedCategoryGlobal()` - Thus any source files in it should use this category.
//

// Set scoped namespace name (This only works if you only use `ScopedGlobal` macros)
#define RH_ScopedNamespaceName(name) \
    ReversibleHooks::ScopeName RHCurrentScopeName {name};

// Use when `name` is a class
#define RH_ScopedClass(name) \
    using RHCurrentNS = name; \
    ReversibleHooks::ScopeName RHCurrentScopeName {#name};

// Use when `name` is a namespace
#define RH_ScopedNamespace(name) \
    namespace RHCurrentNS = name; \
    ReversibleHooks::ScopeName RHCurrentScopeName {#name};

// Supports nested categories separeted by `/`. Eg.: `Entities/Ped`
#define RH_ScopedCategory(name) \
    ReversibleHooks::ScopeCategory  RhCurrentCat{name};

#define RH_RootCategoryName "Root"
#define RH_GlobalCategoryName "Global"
#define RH_ScopedCategoryGlobal() \
    ReversibleHooks::ScopeCategory  RhCurrentCat{ RH_GlobalCategoryName };

// Install a hook living in the current scoped class/namespace
#define RH_ScopedInstall(fn, fnAddr, ...) \
    ReversibleHooks::Install(RhCurrentCat.name + "/" + RHCurrentScopeName.name, #fn, fnAddr, &RHCurrentNS::fn __VA_OPT__(,) __VA_ARGS__)

// Install a hook on a global function
#define RH_ScopedGlobalInstall(fn, fnAddr, ...) \
    ReversibleHooks::Install(RhCurrentCat.name + "/" + RHCurrentScopeName.name, #fn, fnAddr, &fn __VA_OPT__(,) __VA_ARGS__)

// Install a hook on a virtual function
#define RH_ScopedVirtualInstall(fn, fnAddr, ...) \
    ReversibleHooks::Install(RhCurrentCat.name + "/" + RHCurrentScopeName.name, #fn, fnAddr, &RHCurrentNS::fn ## _Reversed __VA_OPT__(,) __VA_ARGS__)

// Tip: If a member function is const just add the `const` keyword after the function arg list;
// Eg.: `void(CRect::*)(float*, float*) const` (Notice the const at the end) (See function `CRect::GetCenter`)
#define RH_ScopedOverloadedInstall(fn, suffix, fnAddr, addrCast, ...) \
    ReversibleHooks::Install(RhCurrentCat.name + "/" + RHCurrentScopeName.name, #fn "-" suffix, fnAddr, static_cast<addrCast>(&RHCurrentNS::fn) __VA_OPT__(,) __VA_ARGS__)

#define RH_ScopedGlobalOverloadedInstall(fn, suffix, fnAddr, addrCast, ...) \
    ReversibleHooks::Install(RhCurrentCat.name + "/" + RHCurrentScopeName.name, #fn "-" suffix, fnAddr, static_cast<addrCast>(&fn) __VA_OPT__(,) __VA_ARGS__)

#define RH_ScopedVirtualOverloadedInstall(fn, suffix, fnAddr, addrCast, ...) \
    ReversibleHooks::Install(RhCurrentCat.name + "/" + RHCurrentScopeName.name, #fn "-" suffix, fnAddr, static_cast<addrCast>(&fn ## _Reversed) __VA_OPT__(,) __VA_ARGS__)

// Used in CCheat only - Install global `fn` as name `fnName`
#define RH_ScopedNamedGlobalInstall(fn, fnName, fnAddr, ...) \
    ReversibleHooks::Install(RhCurrentCat.name + "/" + RHCurrentScopeName.name, fnName, fnAddr, &fn __VA_OPT__(,) __VA_ARGS__)

// Similar to RH_ScopedInstall but you can specify the name explicitly.
#define RH_ScopedNamedInstall(fn, fnName, fnAddr, ...) \
    ReversibleHooks::Install(RhCurrentCat.name + "/" + RHCurrentScopeName.name, fnName, fnAddr, &RHCurrentNS::fn __VA_OPT__(,) __VA_ARGS__)

#define RH_VTFPure                          ReversibleHooks::detail::purevtblfn
#define RH_ScopedVTInstall(pvtblGTA, ...)   ReversibleHooks::InstallVTable(RhCurrentCat.name, RHCurrentScopeName.name, reinterpret_cast<void**>(pvtblGTA), {__VA_ARGS__})
#define RH_VTFDef(name)                     ReversibleHooks::detail::VTableFunction{name}

namespace ReversibleHooks {
    class RootHookCategory;

    struct ScopeName {
        std::string name{};
    };

    struct ScopeCategory {
        std::string name{};
    };

    RootHookCategory& GetRootCategory();

    namespace detail {
        // Change protection of memory pages, and automatically rollback on scope exit
        struct ScopedVirtualProtectAutoRollback {
            ScopedVirtualProtectAutoRollback(LPVOID address, SIZE_T sz, DWORD newProtect = PAGE_EXECUTE_READWRITE) :
                m_addr{ address },
                m_sz{ sz }
            {
                if (VirtualProtect(address, sz, newProtect, &m_oldProtect) == 0) {
                    NOTSA_UNREACHABLE();
                }
            }

            ~ScopedVirtualProtectAutoRollback() {
                DWORD currentProtect{}; // Should be the same as `newProtect` given in the ctor.. But we wont check for it.
                if (VirtualProtect(m_addr, m_sz, m_oldProtect, &currentProtect) == 0) {
                    NOTSA_UNREACHABLE();
                }
            }

        private:
            DWORD  m_oldProtect{};
            LPVOID m_addr{};
            DWORD  m_sz{};
        };

        struct VTableFunction {
            std::string_view name{};
        };
        static constexpr VTableFunction purevtblfn{}; // Marking a pure vtable function

        void HookInstall(std::string_view category, std::string fnName, uint32 installAddress, void* addressToJumpTo, int iJmpCodeSize = 5, bool bDisableByDefault = false, int stackArguments = -1);
        void HookInstallVirtual(std::string_view category, std::string fnName, void* libVTableAddress, std::vector<uint32> vecAddressesToHook);
        /*void HookSwitch(std::shared_ptr<SReversibleHook> pHook);
        bool IsFunctionHooked(const std::string& category, const std::string& fnName);
        std::shared_ptr<SReversibleHook> GetHook(const std::string& category, const std::string& fnName);*/
        void VirtualCopy(void* dst, void* src, size_t nbytes);
    };

    template <typename T>
    static void Install(std::string_view category, std::string fnName, DWORD installAddress, T addressToJumpTo, bool bDisableByDefault = false, int iJmpCodeSize = 5, int stackArguments = -1) {
        auto ptr = FunctionPointerToVoidP(addressToJumpTo);
        detail::HookInstall(category, std::move(fnName), installAddress, ptr, iJmpCodeSize, bDisableByDefault, stackArguments);
    }

    template <typename T>
    static void InstallVirtual(std::string_view category, std::string_view className, std::string fnName, uint32 vtblIdx, void** pvtblGTA) {
        auto ptr = FunctionPointerToVoidP(libVTableAddress);
        detail::HookInstallVirtual(category, std::move(fnName), ptr, std::move(vecAddressesToHook));
    }

    static void InstallVTable(std::string category, std::string_view className, void** pvtblGTA, std::initializer_list<detail::VTableFunction> fns);

    /*static void Switch(std::shared_ptr<SReversibleHook> pHook) {
        detail::HookSwitch(pHook);
    }*/

    void CheckAll();

    // Stuff called from InjectHooksMain()

    void OnInjectionBegin();
    void OnInjectionEnd();
};
