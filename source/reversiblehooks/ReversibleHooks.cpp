#include "StdInc.h"
#include <dbghelp.h>
#include <unordered_set>

#include "extensions/enumerate.hpp"

#include "ReversibleHooks.h"
#include "ReversibleHook/Simple.h"
#include "ReversibleHook/Virtual.h"
#include "RootHookCategory.h"

#define always_assert(expr) do { if (!(expr)) { assert(0); NOTSA_UNREACHABLE(); } } while(false)

namespace ReversibleHooks {

RootHookCategory s_RootCategory{};
HMODULE          s_hThisDLL{}; // Handle to this DLL, only valid after `OnInjectionBegin` is called.

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

void OnInjectionBegin(HMODULE hThisDLL) {
    s_hThisDLL = hThisDLL;
    always_assert(SymInitialize(GetCurrentProcess(), "", TRUE)); // Load debug symbols
    SymSetOptions(SymGetOptions() & ~SYMOPT_UNDNAME & ~SYMOPT_PUBLICS_ONLY);

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

void InstallVTable(std::string_view baseCategory, std::string_view className, void** pvtblGTA, size_t numfns) {
    const auto pvtblOur = detail::GetVTableAddress(className);

    const auto itemCategory = GetRootCategory().FindCategoryForItem(std::format("{}/{}", baseCategory, className));

    printf("Installing VT for %.*s; numfns: %i; [%#X | %#X]\n", (int)className.length(), className.data(), numfns, (int)pvtblGTA, (int)pvtblOur);
    for (auto i = 0u; i < numfns; i++) {
        auto name = detail::GetProcNameFromAddress(pvtblOur[i]);
        printf("[%2i]: %-50s [%#X | %#X];\n", (int)i, name.c_str(), (int)pvtblGTA[i], (int)pvtblOur[i]);
        itemCategory->AddItem(std::make_shared<ReversibleHook::Virtual>(std::string{name}, pvtblGTA, pvtblOur, i));
    }
    //for (const auto&& [fnIdx, fn] : notsa::enumerate(fns.begin(), fns.end())) {
    //    printf("[%i]: %.*s\n", (int)fnIdx, (int)fn.name.length(), fn.name.data());
    //    //itemCategory->AddItem(std::make_shared<ReversibleHook::Virtual>(std::string{ fn.name }, pvtblGTA, pvtblOur, fnIdx));
    //    itemCategory->AddItem(std::make_shared<ReversibleHook::Virtual>(std::string{ detail::GetProcNameFromAddress(pvtblOur[fnIdx])}, pvtblGTA, pvtblOur, fnIdx));
    //}
}

namespace detail {
void HookInstall(std::string_view category, std::string fnName, uint32 installAddress, void* addressToJumpTo, int iJmpCodeSize, bool bDisableByDefault, int stackArguments) {
    // Functions with the same name are asserted in `HookCategory::AddItem()`
    assert(s_HookedAddresses.insert(installAddress).second); // If this asserts that means the address was hooked once already - Thats bad!

    auto item = std::make_shared<ReversibleHook::Simple>(std::move(fnName), installAddress, addressToJumpTo, iJmpCodeSize, stackArguments);
    item->State(!bDisableByDefault);
    s_RootCategory.AddItemToNamedCategory(category, std::move(item));
}

void VirtualCopy(void* dst, void* src, size_t nbytes) {
    DWORD dwProtect[2] = { 0 };
    VirtualProtect(dst, nbytes, PAGE_EXECUTE_READWRITE, &dwProtect[0]);
    memcpy(dst, src, nbytes);
    VirtualProtect(dst, nbytes, dwProtect[0], &dwProtect[1]);
}

// Based on: https://gist.github.com/Merlin/227385822206ae4e3d38f169c9a824b5
// Special thanks to Merlin for helping me out with this one!!
// Get name of a function from it's address. 
std::string GetProcNameFromAddress(LPVOID pfn) {
    constexpr DWORD MaxNameLen{ 1024u };
    char memory[sizeof(SYMBOL_INFO) + (MaxNameLen - 1)]; // The reason to subtract one is that the first character in the name is accounted for in the size of the structure.
    auto si = new (memory) SYMBOL_INFO{
        .SizeOfStruct = sizeof(SYMBOL_INFO),
        .MaxNameLen = MaxNameLen
    };

    always_assert(SymFromAddr(GetCurrentProcess(), (DWORD64)pfn, NULL, si));

    auto dname = std::string_view{ si->Name, si->NameLen };
    if (const auto decorationBegin = dname.find("?"); decorationBegin != std::string_view::npos) {
        // For whatever reason `SymFromAddr` returns names like `ILT+94225(??_ECPlaceableMAEPAXIZ)` even though `SYMOPT_UNDNAME` is set..
        // But in order for `UnDecorateSymbolName` to work we must get rid of all that stuff.
        dname = dname.substr(decorationBegin);     // Strip everything before ?? (As that's where the mangled name begins)
        dname = dname.substr(0, dname.size() - 1); // Strip last bracket
    }

    // De-mangle its name
    std::array<CHAR, MaxNameLen> udname;
    const auto udnemlen = UnDecorateSymbolName(dname.data(), udname.data(), udname.size(), UNDNAME_NAME_ONLY);
    always_assert(udnemlen);
    const auto udnamesv{ std::string_view{ udname.data(), udnemlen }};

    // The demangled name contains the scope, but we only want the name, so strip the scope.
    if (const auto off = udnamesv.rfind("::"); off != std::string_view::npos) { // Find last `::`, before that should be the function name
        return std::string{ udnamesv.substr(off + 2) };
    } else {
        return std::string{ udnamesv };
    }
    //static const auto init = 

    //const auto MakeMapping = [] {
    //    const auto pDosHdr = (PIMAGE_DOS_HEADER )s_hThisDLL;
    //    const auto pNtHdr  = (PIMAGE_NT_HEADERS)((LPBYTE)s_hThisDLL + pDosHdr->e_lfanew);

    //    const auto pExports = (PIMAGE_EXPORT_DIRECTORY)((LPBYTE)s_hThisDLL + pNtHdr->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);

    //    const auto pNames          = (PDWORD)((LPBYTE)s_hThisDLL + pExports->AddressOfNames);
    //    const auto pFunctions      = (PDWORD)((LPBYTE)s_hThisDLL + pExports->AddressOfFunctions);
    //    const auto pNameOfOrdinals = (PWORD)((LPBYTE)s_hThisDLL + pExports->AddressOfNameOrdinals);

    //    std::unordered_map<LPVOID, std::string> mapping;
    //    mapping.reserve(pExports->NumberOfNames);
    //    for (DWORD ordinal = 0; ordinal < pExports->NumberOfNames; ordinal++) {
    //        std::array<CHAR, 1024> udname;
    //        const auto GetFunctionNameOnly = [&]() {
    //            UnDecorateSymbolName((PCSTR)(s_hThisDLL) + pNames[ordinal], udname.data(), udname.size(), UNDNAME_NAME_ONLY);

    //            const auto udnamesv{ std::string_view{ udname } };
    //            if (const auto off = udnamesv.rfind("::"); off != std::string_view::npos) { // Find last `::`, before that should be the function name
    //                return udnamesv.substr(off + 2); 
    //            } else {
    //                return udnamesv;
    //            }
    //        };
    //        const auto name = GetFunctionNameOnly();
    //        mapping[(LPVOID)((LPBYTE)s_hThisDLL + pFunctions[pNameOfOrdinals[ordinal]])] = GetFunctionNameOnly();

    //        printf("[%i][%p] = %-30.*s\n", (int)ordinal, (LPVOID)((LPBYTE)s_hThisDLL + pFunctions[pNameOfOrdinals[ordinal]]), (int)name.length(), name.data());
    //    }

    //    /*  for (auto&& [k, v] : mapping) {
    //        printf("[%p] = %-30.*s\n", k, (int)v.length(), v.data());
    //    }*/

    //    return mapping;
    //};
    //static const auto mapping = MakeMapping();
    //return mapping.at(pfn);
}

// The VTable is exported as a symbol, in the format `??_7<class name>@@6B@` where `<class name>` is the name of the class.
// In order for this to work the class has to be exported (So the `NOTSA_EXPORT_VTABLE` macro has to be used)
void** GetVTableAddress(std::string_view className) {
    SYMBOL_INFO si{
        .SizeOfStruct = sizeof(SYMBOL_INFO)
    };
    always_assert(SymFromName(GetCurrentProcess(), std::format("??_7{}@@6B@", className).c_str(), &si));
    return reinterpret_cast<void**>(si.Address);
}

}; // namespace detail
}; // namespace ReversibleHooks
