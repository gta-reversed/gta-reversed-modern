#include "StdInc.h"

static std::map<std::string, std::vector<std::shared_ptr<SReversibleHook>>> m_HooksMap;

namespace ReversibleHooks{

std::map<std::string, std::vector<std::shared_ptr<SReversibleHook>>>& GetAllHooks() {
    return m_HooksMap;
}

void UnHook(const std::string& className, const char* functionName)
{
    if (className.empty())
        return;

    const auto& allHooks = GetAllHooks();
    if (functionName) {
        for (auto& classHooks : allHooks) {
            if (classHooks.first == className) {
                for (auto& hook : classHooks.second) {
                    if (hook->m_bIsHooked && strcmp(hook->m_sFunctionName.c_str(), functionName) == 0) {
                        hook->Switch();
                        printf("UnHooked %s::%s\n", className.c_str(), functionName);
                        return;
                    }
                }
            }
        }
    } else {
        for (auto& classHooks : allHooks) {
            if (classHooks.first == className) {
                for (auto& hook : classHooks.second) {
                    if (hook->m_bIsHooked)
                        hook->Switch();
                }
                printf("UnHooked class %s\n", className.c_str());
                return;
            }
        }
    }
}

void CheckAll() {
    for (auto& pair : m_HooksMap) {
        for (auto& hook : pair.second) {
            hook->Check();
        }
    }
}

namespace detail {
void HookInstall(const std::string& sIdentifier, const std::string& sFuncName, uint32 installAddress, void* addressToJumpTo, int iJmpCodeSize, bool bDisableByDefault)
{
    assert(!GetHook(sIdentifier, sFuncName));

    auto& usedVector = m_HooksMap[sIdentifier];
    usedVector.emplace_back(std::make_shared<SSimpleReversibleHook>(sIdentifier, sFuncName, installAddress, addressToJumpTo, iJmpCodeSize));
    if (bDisableByDefault)
        usedVector.back()->Switch();
}

void HookInstallVirtual(const std::string& sIdentifier, const std::string& sFuncName, void* libVTableAddress, const std::vector<uint32>& vecAddressesToHook)
{
    assert(!GetHook(sIdentifier, sFuncName));
    m_HooksMap[sIdentifier].emplace_back(std::make_shared<SVirtualReversibleHook>(sIdentifier, sFuncName, libVTableAddress, vecAddressesToHook));
}

void HookSwitch(std::shared_ptr<SReversibleHook> pHook)
{
    pHook->Switch();
}

bool IsFunctionHooked(const std::string& sIdentifier, const std::string& sFuncName)
{
    auto hook = GetHook(sIdentifier, sFuncName);
    if (!hook)
        return false;

    return hook->m_bIsHooked;
}

std::shared_ptr<SReversibleHook> GetHook(const std::string& sIdentifier, const std::string& sFuncName)
{
    auto hooks = m_HooksMap.find(sIdentifier);
    if (hooks != m_HooksMap.end())
        for (auto& hook : hooks->second)
            if (hook->m_sFunctionName == sFuncName)
                return hook;
    return nullptr;
}

void VirtualCopy(void* dst, void* src, size_t nbytes) {
    DWORD dwProtect[2] = { 0 };
    VirtualProtect(dst, nbytes, PAGE_EXECUTE_READWRITE, &dwProtect[0]);
    memcpy(dst, src, nbytes);
    VirtualProtect(dst, nbytes, dwProtect[0], &dwProtect[1]);
}

}; // namespace detail
}; // namespace ReversibleHooks

SReversibleHook::SReversibleHook(std::string id, std::string name, eReversibleHookType type) :
    m_sIdentifier(std::move(id)),
    m_sFunctionName(std::move(name)),
    m_eHookType(type)
{
}
