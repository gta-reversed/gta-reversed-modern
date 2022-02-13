#include "StdInc.h"

#include "Virtual.h"

namespace ReversibleHooks{
namespace ReversibleHook{
Virtual::Virtual(std::string fnName, void* libFuncAddress, std::vector<uint32> vecAddressesToHook) :
    Base{ std::move(fnName), HookType::Virtual },
    m_LibFunctionAddress{ reinterpret_cast<uint32>(libFuncAddress) },
    m_vecHookedAddresses{ std::move(vecAddressesToHook) }
{
    assert(!vecAddressesToHook.empty());

    DWORD dwProtectInitial[2] = { 0 };
    VirtualProtect((void*)vecAddressesToHook[0], 4, PAGE_EXECUTE_READWRITE, &dwProtectInitial[0]);
    m_OriginalFunctionAddress = *reinterpret_cast<uint32*>(vecAddressesToHook[0]);
    VirtualProtect((void*)vecAddressesToHook[0], 4, dwProtectInitial[0], &dwProtectInitial[1]);

    m_bIsHooked = false;
    Switch(); // Installs hooks (also sets `m_bIsHooked` to `true`)
};

void Virtual::Switch()
{
    for (auto uiAddress : m_vecHookedAddresses) {
        using namespace ReversibleHooks::detail;
        VirtualCopy((void*)uiAddress, (void*)(m_bIsHooked ? m_OriginalFunctionAddress : m_LibFunctionAddress), 5);
    }

    m_bIsHooked = !m_bIsHooked;
    m_isVisible = m_bIsHooked;
}
};
};
