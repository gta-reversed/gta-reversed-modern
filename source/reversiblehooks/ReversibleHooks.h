#pragma once

#include <unordered_map>
#include <vector>
#include <string>

//
// Helper macros - For help regarding usage see how they're used (`Find all references` and take a look)
// Generally on top of `InjectHooks` you will need to call `RH_ScopedClass` (or `RH_ScopedNamespace`) and `RH_ScopedCategory`
// `RH_ScopedCategory` generally follows the directory layout - Anything in, lets say, the `Entity` directory should be in the `Entity` category.
// The root folder (source/game_sa) can be referred to by `RH_ScopedCategoryGlobal()` - Thus any source files in it should use this category.
//

// Set scoped namespace name (This only works if you only use `ScopedGlobal` macros)
#define RH_ScopedNamespaceName(name) \
    ReversibleHooks::ScopeName RHCurrentScopeName {#name};

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
#define RH_ScopedCategoryRoot() \
    ReversibleHooks::ScopeCategory  RhCurrentCat{ RH_RootCategoryName };

// Install a hook living in the current scoped class/namespace
#define RH_ScopedInstall(fn, fnAddr, ...); \
    ReversibleHooks::Install(RHCurrentScopeName.name, #fn, fnAddr, &RHCurrentNS::fn, __VA_ARGS__)

// Install a hook on a global function
#define RH_ScopedGlobalInstall(fn, fnAddr, ...) \
    ReversibleHooks::Install(RHCurrentScopeName.name, #fn, fnAddr, &fn, __VA_ARGS__)

// Tip: If a member function is const just add the `const` keyword after the function arg list;
// Eg.: `void(CRect::*)(float*, float*) const` (Notice the const at the end) (See function `CRect::GetCenter`)
#define RH_ScopedOverloadedInstall(fn, suffix, fnAddr, addrCast, ...) \
    ReversibleHooks::Install(RHCurrentScopeName.name, #fn "-" suffix, fnAddr, static_cast<addrCast>(&RHCurrentNS::fn), __VA_ARGS__)

#define RH_ScopedGlobalOverloadedInstall(fn, suffix, fnAddr, addrCast, ...) \
    ReversibleHooks::Install(RHCurrentScopeName.name, #fn "-" suffix, fnAddr, static_cast<addrCast>(&fn), __VA_ARGS__)

enum class eReversibleHookType {
    Simple,
    Virtual
};

#pragma pack(push, 1)
struct SHookContent {
    uint8 jumpOpCode = JUMP_OPCODE;
    uint32 jumpLocation = 0;
    uint8 possibleNops[52 - sizeof(jumpOpCode) - sizeof(jumpLocation)] = { 0 };
};
#pragma pack(pop)
VALIDATE_SIZE(SHookContent, 0x34);

struct SReversibleHook {
    bool m_bIsHooked = false;
    bool m_bImguiHooked = false;
    std::string m_sIdentifier;
    std::string m_sFunctionName;
    eReversibleHookType m_eHookType;

    SReversibleHook(std::string id, std::string name, eReversibleHookType type);
    virtual ~SReversibleHook() = default;
    virtual void Switch() = 0;
    virtual void Check() = 0;

    void SetState(bool hooked) {
        if (m_bIsHooked != hooked) {
            Switch();
        }
    }
};

struct SSimpleReversibleHook : SReversibleHook {
    SHookContent m_HookContent;
    uint8        m_OriginalFunctionContent[sizeof(m_HookContent)];
    uint32       m_iHookedBytes;
    uint32       m_iRealHookedAddress;

    SHookContent m_LibHookContent;
    uint8        m_LibOriginalFunctionContent[sizeof(m_LibHookContent)];
    uint32       m_iLibHookedBytes;
    uint32       m_iLibFunctionAddress;

    SSimpleReversibleHook(std::string id, std::string name, uint32 installAddress, void* addressToJumpTo, int iJmpCodeSize = 5);
    bool CheckLibFnForChangesAndStore(void* expected);
    void ApplyJumpToGTACode();
    virtual void Switch() override;
    virtual void Check() override;
    virtual ~SSimpleReversibleHook() override = default;
};

struct SVirtualReversibleHook : SReversibleHook {
    std::vector<uint32> m_vecHookedAddresses;
    uint32              m_OriginalFunctionAddress;
    uint32              m_LibFunctionAddress;

    SVirtualReversibleHook(std::string id, std::string name, void* libFuncAddress, const std::vector<uint32>& vecAddressesToHook);
    virtual void Switch() override;
    virtual void Check() override {}
    virtual ~SVirtualReversibleHook() override = default;
};

namespace ReversibleHooks {
    struct ScopeName {
        std::string name{};
    };
    
    struct ScopeCategory {
        std::string m_name{};

        auto GetRootCategories() {

        }
    };


    /*struct ScopeName {
        std::s
    };*/

    namespace detail {
        void HookInstall(const std::string& sIdentifier, const std::string& sFuncName, uint32 installAddress, void* addressToJumpTo, int iJmpCodeSize = 5, bool bDisableByDefault = false);
        void HookInstallVirtual(const std::string& sIdentifier, const std::string& sFuncName, void* libVTableAddress, const std::vector<uint32>& vecAddressesToHook);
        void HookSwitch(std::shared_ptr<SReversibleHook> pHook);
        bool IsFunctionHooked(const std::string& sIdentifier, const std::string& sFuncName);
        std::shared_ptr<SReversibleHook> GetHook(const std::string& sIdentifier, const std::string& sFuncName);
        void VirtualCopy(void* dst, void* src, size_t nbytes);
    };

    template <typename T>
    static void Install(const std::string& sIdentifier, const std::string& sFuncName, DWORD installAddress, T addressToJumpTo, bool bDisableByDefault = false, int iJmpCodeSize = 5) {
        auto ptr = FunctionPointerToVoidP(addressToJumpTo);
        detail::HookInstall(sIdentifier, sFuncName, installAddress, ptr, iJmpCodeSize, bDisableByDefault);
    }

    template <typename T>
    static void InstallVirtual(const std::string& sIdentifier, const std::string& sFuncName, T libVTableAddress, const std::vector<uint32>& vecAddressesToHook) {
        auto ptr = FunctionPointerToVoidP(libVTableAddress);
        detail::HookInstallVirtual(sIdentifier, sFuncName, ptr, vecAddressesToHook);
    }

    static void Switch(std::shared_ptr<SReversibleHook> pHook) {
        detail::HookSwitch(pHook);
    }

    std::map<std::string, std::vector<std::shared_ptr<SReversibleHook>>>& GetAllHooks();

    void UnHook(const std::string& className, const char* functionName = nullptr);

    void CheckAll();

    constexpr uint32 x86JMPSize = 5U;
    constexpr auto GetJMPLocation(uint32 dwFrom, uint32 dwTo) { return dwTo - dwFrom - x86JMPSize; }
    constexpr auto GetFunctionLocationFromJMP(uint32 dwJmpLoc, uint32 dwJmpOffset) { return dwJmpOffset + dwJmpLoc + x86JMPSize; }
};
