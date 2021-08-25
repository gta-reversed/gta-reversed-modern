#include "StdInc.h"

SVirtualReversibleHook::SVirtualReversibleHook(void* libFuncAddress, const std::vector<uint32_t>& vecAddressesToHook) {
    m_LibFunctionAddress = reinterpret_cast<uint32_t>(libFuncAddress);

    DWORD dwProtectInitial[2] = { 0 };
    VirtualProtect((void*)vecAddressesToHook[0], 4, PAGE_EXECUTE_READWRITE, &dwProtectInitial[0]);
    m_OriginalFunctionAddress = *reinterpret_cast<uint32_t*>(vecAddressesToHook[0]);
    VirtualProtect((void*)vecAddressesToHook[0], 4, dwProtectInitial[0], &dwProtectInitial[1]);

    for (auto uiAddress : vecAddressesToHook) {
        DWORD dwProtect[2] = { 0 };
        VirtualProtect((void*)uiAddress, 4, PAGE_EXECUTE_READWRITE, &dwProtect[0]);
        *reinterpret_cast<uint32_t*>(uiAddress) = m_LibFunctionAddress;
        VirtualProtect((void*)uiAddress, 4, dwProtect[0], &dwProtect[1]);
        m_vecHookedAddresses.push_back(uiAddress);
    }

    m_bIsHooked = true;
    m_bImguiHooked = true;
};

std::shared_ptr<SVirtualReversibleHook> SVirtualReversibleHook::InstallHook(void* libFuncAddress, const std::vector<uint32_t>& vecAddressesToHook)
{
    assert(vecAddressesToHook.size() > 0);
    return std::make_shared<SVirtualReversibleHook>(libFuncAddress, vecAddressesToHook);
}

void SVirtualReversibleHook::Switch()
{
    for (auto uiAddress : m_vecHookedAddresses) {
        DWORD dwProtect[2] = { 0 };
        VirtualProtect((void*)uiAddress, 5, PAGE_EXECUTE_READWRITE, &dwProtect[0]);
        *reinterpret_cast<uint32_t*>(uiAddress) = m_bIsHooked ?  m_OriginalFunctionAddress : m_LibFunctionAddress;
        VirtualProtect((void*)uiAddress, 5, dwProtect[0], &dwProtect[1]);
    }

    m_bIsHooked = !m_bIsHooked;
    m_bImguiHooked = m_bIsHooked;
}
