#include "StdInc.h"
#include <unordered_set>

#include "ReversibleHooks.h"
#include "ReversibleHook/Simple.h"
#include "ReversibleHook/Virtual.h"
#include "RootHookCategory.h"

namespace ReversibleHooks {

RootHookCategory s_RootCategory{};
HMODULE          s_hThisDLL{}; // Handle to this DLL, only valid after `OnInjectionBegin` is called.

#ifndef NDEBUG
// Not particularly memory efficient, but it should be fine
std::unordered_set<uint32> s_HookedAddresses{};  // Original GTA addresses to which we've installed hooks
#endif

RootHookCategory& GetRootCategory() {
    return s_RootCategory;
}

void CheckAll() {
    s_RootCategory.ForEachItem([](auto& item) {
        item->Check();
    });
}

void SwitchHook(std::string_view funcName) {
    s_RootCategory.ForEachItem([=](auto& item) {
        const auto name = item->Name();
        if (name == funcName) {
            item->Switch();
            return;
        }
    });
}

void OnInjectionBegin(HMODULE hThisDLL) {
    s_hThisDLL = hThisDLL;

#ifndef NDEBUG
    s_HookedAddresses.reserve(20000); // Should be enough - We free it after the injection has finished, so it should be fine
#endif
}

void OnInjectionEnd() {
#ifndef NDEBUG
    // Hopefully these deallocates all memory
    s_HookedAddresses.clear();
    s_HookedAddresses = {};
#endif

    s_RootCategory.OnInjectionEnd();
}

void InstallVirtual(std::string_view category, std::string fnName, void** vtblGTA, void** vtblOur, void* fnGTAAddr, size_t nVirtFns, const HookInstallOptions& opt) {
    // Find
    const auto spanGTAVTbl = std::span{ vtblGTA, nVirtFns };
    const auto iter = rng::find(spanGTAVTbl, fnGTAAddr);
    if (iter == spanGTAVTbl.end()) {
        /* Tips in case you ever encounter this
        * - Make sure the vtable address and size is correct
        * - Make sure function address you're hooking is correct
        */
        NOTSA_UNREACHABLE("{}: Couldn't find function [{} @ {}] in vtable\n", category, fnName, fnGTAAddr);
    }
    const auto fnVTblIdx = (size_t)rng::distance(spanGTAVTbl.begin(), iter);

#ifdef HOOKS_DEBUG
    std::cout << std::format("{}::{} => {}\n", category, fnName, fnVTblIdx);
#endif

    auto item = std::make_shared<ReversibleHook::Virtual>(std::move(fnName), vtblGTA, vtblOur, fnVTblIdx);
    item->State(opt.enabled);
    item->LockState(opt.locked);
    AddItemToCategory(category, std::move(item));
}

void AddItemToCategory(std::string_view category, std::shared_ptr<ReversibleHook::Base> item) {
    s_RootCategory.AddItemToNamedCategory(category, std::move(item));
}

namespace detail {
void HookInstall(std::string_view category, std::string fnName, uint32 installAddress, void* addressToJumpTo, HookInstallOptions&& opt) {
#ifndef NDEBUG // Functions with the same name are asserted in `HookCategory::AddItem()`
    auto [iter, inserted] = s_HookedAddresses.insert(installAddress);
    if (!inserted) {
        // If this asserts that means the address was hooked once already - Thats bad!
        printf("Warn %s %s\n", category.data(), fnName.c_str());
        return;
    }
#endif

    auto item = std::make_shared<ReversibleHook::Simple>(std::move(fnName), installAddress, addressToJumpTo, opt.jmpCodeSize, opt.stackArguments);
    item->State(opt.enabled);
    item->LockState(opt.locked);
    AddItemToCategory(category, std::move(item));
}

void VirtualCopy(void* dst, void* src, size_t nbytes) {
    DWORD dwProtect[2] = { 0 };
    VirtualProtect(dst, nbytes, PAGE_EXECUTE_READWRITE, &dwProtect[0]);
    memcpy(dst, src, nbytes);
    VirtualProtect(dst, nbytes, dwProtect[0], &dwProtect[1]);
}

// The VTable is exported as a symbol, in the format `??_7<class name>@@6B@` where `<class name>` is the name of the class.
// In order for this to work the class has to be exported (So the `NOTSA_EXPORT_VTABLE` macro has to be used)
void** GetVTableAddress(std::string_view className) {
    CHAR buffer[1024];
    sprintf_s(buffer, "??_7%.*s@@6B@", (int)className.length(), className.data());
    if (const auto vtbl = reinterpret_cast<void**>(GetProcAddress(s_hThisDLL, buffer))) {
#ifdef HOOKS_DEBUG
        std::cout << std::format("{}: Our VMT: {} \n", className, (void*)vtbl);
#endif
        return vtbl;
    }

    NOTSA_UNREACHABLE("Couldn't find VTable of `{}`", className);
}

}; // namespace detail
}; // namespace ReversibleHooks
