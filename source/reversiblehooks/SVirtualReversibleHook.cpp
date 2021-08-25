#include "StdInc.h"

SVirtualReversibleHook::SVirtualReversibleHook(std::string id, std::string name, void* libFuncAddress, const std::vector<uint32_t>& vecAddressesToHook) :
    SReversibleHook(id, name, eReversibleHookType::Virtual)
{
    assert(vecAddressesToHook.size() > 0);

    m_LibFunctionAddress = reinterpret_cast<uint32_t>(libFuncAddress);

    DWORD dwProtectInitial[2] = { 0 };
    VirtualProtect((void*)vecAddressesToHook[0], 4, PAGE_EXECUTE_READWRITE, &dwProtectInitial[0]);
    m_OriginalFunctionAddress = *reinterpret_cast<uint32_t*>(vecAddressesToHook[0]);
    VirtualProtect((void*)vecAddressesToHook[0], 4, dwProtectInitial[0], &dwProtectInitial[1]);

    for (auto uiAddress : vecAddressesToHook) {
        using namespace ReversibleHooks::detail;
        
        VirtualCopy((void*)uiAddress, (void*)m_LibFunctionAddress, 4);
        m_vecHookedAddresses.push_back(uiAddress);
    }

    m_bIsHooked = true;
    m_bImguiHooked = true;
};

void SVirtualReversibleHook::Switch()
{
    for (auto uiAddress : m_vecHookedAddresses) {
        using namespace ReversibleHooks::detail;
        VirtualCopy((void*)uiAddress, (void*)(m_bIsHooked ? m_OriginalFunctionAddress : m_LibFunctionAddress), 5);
    }

    m_bIsHooked = !m_bIsHooked;
    m_bImguiHooked = m_bIsHooked;
}
