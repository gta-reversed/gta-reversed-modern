#include "StdInc.h"
#include "ReversibleHooks.h"
#include "ReversibleHook/Simple.h"
#include "ReversibleHook/Virtual.h"
#include "RootHookCategory.h"


namespace ReversibleHooks {

RootHookCategory s_RootCategory{};

RootHookCategory& GetRootCategory() {
    return s_RootCategory;
}

void CheckAll() {
    s_RootCategory.ForEachItem([](auto& item) {
        item->Check();
    });
}

namespace detail {
void HookInstall(std::string_view category, std::string fnName, uint32 installAddress, void* addressToJumpTo, int iJmpCodeSize, bool bDisableByDefault) {
    auto item = std::make_shared<ReversibleHook::Simple>(std::move(fnName), installAddress, addressToJumpTo, iJmpCodeSize);
    item->SetState(!bDisableByDefault);
    s_RootCategory.AddItemToNamedCategory(category, std::move(item));
}

void HookInstallVirtual(std::string_view category, std::string fnName, void* libVTableAddress, std::vector<uint32> vecAddressesToHook) {
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
