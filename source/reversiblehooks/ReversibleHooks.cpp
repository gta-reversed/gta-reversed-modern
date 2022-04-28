#include "StdInc.h"
#include <unordered_set>

#include "ReversibleHooks.h"
#include "ReversibleHook/Simple.h"
#include "ReversibleHook/Virtual.h"
#include "RootHookCategory.h"

namespace ReversibleHooks {

RootHookCategory           s_RootCategory{};

#ifndef NDEBUG
// Not particularly memmory efficient, but it should be fine
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

void OnInjectionBegin() {
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

namespace detail {
void HookInstall(std::string_view category, std::string fnName, uint32 installAddress, void* addressToJumpTo, int iJmpCodeSize, bool bDisableByDefault, int stackArguments) {
    // Functions with the same name are asserted in `HookCategory::AddItem()`
    assert(s_HookedAddresses.insert(installAddress).second); // If this asserts that means the address was hooked once already - Thats bad!

    auto item = std::make_shared<ReversibleHook::Simple>(std::move(fnName), installAddress, addressToJumpTo, iJmpCodeSize, stackArguments);
    item->State(!bDisableByDefault);
    s_RootCategory.AddItemToNamedCategory(category, std::move(item));
}

void HookInstallVirtual(std::string_view category, std::string fnName, void* libVTableAddress, std::vector<uint32> vecAddressesToHook) {
    // TODO: Duplicate hooked function detection - Currently VHooks aren't used AFAIK, so it's fine not to add them.

    auto item = std::make_shared<ReversibleHook::Virtual>(std::move(fnName), libVTableAddress, std::move(vecAddressesToHook));
    //item->SetState(!bDisableByDefault);
    s_RootCategory.AddItemToNamedCategory(category, std::move(item));
}

void VirtualCopy(void* dst, void* src, size_t nbytes) {
    DWORD dwProtect[2] = { 0 };
    VirtualProtect(dst, nbytes, PAGE_EXECUTE_READWRITE, &dwProtect[0]);
    memcpy(dst, src, nbytes);
    VirtualProtect(dst, nbytes, dwProtect[0], &dwProtect[1]);
}

}; // namespace detail
}; // namespace ReversibleHooks
