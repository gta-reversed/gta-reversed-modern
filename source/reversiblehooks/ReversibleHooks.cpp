#include "StdInc.h"

void ReversibleHooks::UnHook(const std::string& className, const char* functionName)
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

void ReversibleHooks::HookInstall(const std::string& sIdentifier, const std::string& sFuncName, unsigned int installAddress, void* addressToJumpTo, int iJmpCodeSize, bool bDisableByDefault)
{
    assert(!GetHook(sIdentifier, sFuncName));
    if (m_HooksMap.find(sIdentifier) == m_HooksMap.end())
        m_HooksMap[sIdentifier] = std::vector<std::shared_ptr<SReversibleHook>>();

    auto& usedVector = m_HooksMap[sIdentifier];
    auto pHook = SSimpleReversibleHook::InstallHook(installAddress, addressToJumpTo, iJmpCodeSize);
    pHook->m_sIdentifier = sIdentifier;
    pHook->m_sFunctionName = sFuncName;
    pHook->m_eHookType = eReversibleHookType::Simple;

    usedVector.push_back(pHook);
    if (bDisableByDefault)
        pHook->Switch();
}

void ReversibleHooks::HookInstallVirtual(const std::string& sIdentifier, const std::string& sFuncName, void* libVTableAddress, const std::vector<uint32_t>& vecAddressesToHook)
{
    assert(!GetHook(sIdentifier, sFuncName));
    if (m_HooksMap.find(sIdentifier) == m_HooksMap.end())
        m_HooksMap[sIdentifier] = std::vector<std::shared_ptr<SReversibleHook>>();

    auto& usedVector = m_HooksMap[sIdentifier];
    auto pHook = SVirtualReversibleHook::InstallHook(libVTableAddress, vecAddressesToHook);
    pHook->m_sIdentifier = sIdentifier;
    pHook->m_sFunctionName = sFuncName;
    pHook->m_eHookType = eReversibleHookType::Virtual;

    usedVector.push_back(pHook);
}

void ReversibleHooks::HookSwitch(std::shared_ptr<SReversibleHook> pHook) const
{
    pHook->Switch();
}

bool ReversibleHooks::IsFunctionHooked(const std::string& sIdentifier, const std::string& sFuncName)
{
    auto hook = GetHook(sIdentifier, sFuncName);
    if (!hook)
        return false;

    return hook->m_bIsHooked;
}

std::shared_ptr<SReversibleHook> ReversibleHooks::GetHook(const std::string& sIdentifier, const std::string& sFuncName)
{
    if (m_HooksMap.find(sIdentifier) == m_HooksMap.end())
        return nullptr;

    auto& vecHooks = m_HooksMap[sIdentifier];
    auto findResult = std::find_if(vecHooks.begin(), vecHooks.end(), [&](const std::shared_ptr<SReversibleHook> hook) {return hook->m_sFunctionName == sFuncName; });
    if (findResult == vecHooks.end())
        return nullptr;

    return *findResult;
}

unsigned int ReversibleHooks::GetJMPLocation(unsigned int dwFrom, unsigned int dwTo)
{
    return dwTo - dwFrom - ReversibleHooks::x86JMPSize;
}

unsigned int ReversibleHooks::GetFunctionLocationFromJMP(unsigned int dwJmpLoc, unsigned int dwJmpOffset)
{
    return dwJmpOffset + dwJmpLoc + ReversibleHooks::x86JMPSize;
}
