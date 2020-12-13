#include "StdInc.h"

void ReversibleHooks::HookInstall(const std::string& sIdentifier, const std::string& sFuncName, unsigned int installAddress, void* addressToJumpTo, int iJmpCodeSize)
{
    assert(!GetHook(sIdentifier, sFuncName));
    if (m_HooksMap.find(sIdentifier) == m_HooksMap.end())
        m_HooksMap[sIdentifier] = std::vector<SReversibleHook>();

    auto& usedVector = m_HooksMap[sIdentifier];

    unsigned int dwAddressToJumpTo = (unsigned int)FunctionPointerToVoidP(addressToJumpTo);
    const unsigned int x86FixedJumpSize = 5U;
    SReversibleHook theHook;
    theHook.m_iLibFunctionAddress = dwAddressToJumpTo;
    theHook.m_sIdentifier = sIdentifier;
    theHook.m_sFunctionName = sFuncName;
    theHook.m_iRealHookedAddress = installAddress;
    theHook.m_iHookedBytes = iJmpCodeSize;

    theHook.m_HookContent.jumpLocation = ReversibleHooks::GetJMPLocation(installAddress, dwAddressToJumpTo);
    memset(theHook.m_HookContent.possibleNops, NOP_OPCODE, iJmpCodeSize - ReversibleHooks::x86JMPSize);

    //Copy lib function content
    theHook.m_LibHookContent.jumpLocation = ReversibleHooks::GetJMPLocation(dwAddressToJumpTo, installAddress);
    theHook.m_iLibHookedBytes = ReversibleHooks::x86JMPSize;
    memcpy((void*)&theHook.m_LibOriginalFunctionContent, (void*)dwAddressToJumpTo, theHook.m_iLibHookedBytes);

    auto installHook = [&](bool bVirtProtect) {
        DWORD dwProtectHoodlum[2] = { 0 };
        if (bVirtProtect)
            VirtualProtect((void*)theHook.m_iRealHookedAddress, theHook.m_iHookedBytes, PAGE_EXECUTE_READWRITE, &dwProtectHoodlum[0]);

        memcpy((void*)&theHook.m_OriginalFunctionContent, (void*)theHook.m_iRealHookedAddress, theHook.m_iHookedBytes);
        memcpy((void*)theHook.m_iRealHookedAddress, &theHook.m_HookContent, theHook.m_iHookedBytes);

        if (bVirtProtect)
            VirtualProtect((void*)theHook.m_iRealHookedAddress, theHook.m_iHookedBytes, dwProtectHoodlum[0], &dwProtectHoodlum[1]);

        theHook.m_bIsHooked = true;
        theHook.m_bImguiHooked = true;
    };

    const int maxBytesToProtect = std::max(iJmpCodeSize, 8);
    DWORD dwProtect[2] = { 0 };
    VirtualProtect((void*)installAddress, maxBytesToProtect, PAGE_EXECUTE_READWRITE, &dwProtect[0]);

    // workaround for hoodlum crashes due to securom protection.
    if (*(std::uint8_t*)installAddress == NOP_OPCODE) {
        bool bJumpFound = false;
        std::uint32_t i = 0;
        for (; i < 4; i++) {
            if (*(std::uint8_t*)(installAddress + i) == JUMP_OPCODE) {
                bJumpFound = true;
                break;
            }
        }
        if (bJumpFound) {
            DWORD newInstallAddress = installAddress + i;
            DWORD hoodlumHookAddress = *(DWORD*)(newInstallAddress + 1) + newInstallAddress + ReversibleHooks::x86JMPSize;
            theHook.m_iRealHookedAddress = hoodlumHookAddress;
            theHook.m_HookContent.jumpLocation = ReversibleHooks::GetJMPLocation(hoodlumHookAddress, dwAddressToJumpTo);
            theHook.m_iHookedBytes = ReversibleHooks::x86JMPSize;

            installHook(true);
        }
        else {
            printf("HookInstall: Couldn't find the jump for address = %#.8x\n", installAddress);
            installHook(false);
        }
    }
    else {
        installHook(false);
    }
    VirtualProtect((void*)installAddress, maxBytesToProtect, dwProtect[0], &dwProtect[1]);

    usedVector.push_back(std::move(theHook));
}

void ReversibleHooks::HookSwitch(SReversibleHook& sHook)
{
    DWORD dwProtect[2] = { 0 };
    if (sHook.m_bIsHooked) {
        auto pGTADst = (void*)sHook.m_iRealHookedAddress;
        auto pGTASrc = (void*)&sHook.m_OriginalFunctionContent;
        VirtualProtect(pGTADst, sHook.m_iHookedBytes, PAGE_EXECUTE_READWRITE, &dwProtect[0]);
        memcpy(pGTADst, pGTASrc, sHook.m_iHookedBytes);
        VirtualProtect(pGTADst, sHook.m_iHookedBytes, dwProtect[0], &dwProtect[1]);

        auto pLibDst = (void*)sHook.m_iLibFunctionAddress;
        auto pLibSrc = (void*)&sHook.m_LibHookContent;
        VirtualProtect(pLibDst, sHook.m_iLibHookedBytes, PAGE_EXECUTE_READWRITE, &dwProtect[0]);
        memcpy(pLibDst, pLibSrc, sHook.m_iLibHookedBytes);
        VirtualProtect(pLibDst, sHook.m_iLibHookedBytes, dwProtect[0], &dwProtect[1]);
    }
    else {
        auto pGTADst = (void*)sHook.m_iRealHookedAddress;
        auto pGTASrc = (void*)&sHook.m_HookContent;
        VirtualProtect(pGTADst, sHook.m_iHookedBytes, PAGE_EXECUTE_READWRITE, &dwProtect[0]);
        memcpy(pGTADst, pGTASrc, sHook.m_iHookedBytes);
        VirtualProtect(pGTADst, sHook.m_iHookedBytes, dwProtect[0], &dwProtect[1]);

        auto pLibDst = (void*)sHook.m_iLibFunctionAddress;
        auto pLibSrc = (void*)&sHook.m_LibOriginalFunctionContent;
        VirtualProtect(pLibDst, sHook.m_iLibHookedBytes, PAGE_EXECUTE_READWRITE, &dwProtect[0]);
        memcpy(pLibDst, pLibSrc, sHook.m_iLibHookedBytes);
        VirtualProtect(pLibDst, sHook.m_iLibHookedBytes, dwProtect[0], &dwProtect[1]);
    }

    sHook.m_bIsHooked = !sHook.m_bIsHooked;
    sHook.m_bImguiHooked = sHook.m_bIsHooked;
}

bool ReversibleHooks::IsFunctionHooked(const std::string& sIdentifier, const std::string& sFuncName)
{
    auto hook = GetHook(sIdentifier, sFuncName);
    if (hook == nullptr)
        return false;

    return hook->m_bIsHooked;
}

SReversibleHook* ReversibleHooks::GetHook(const std::string& sIdentifier, const std::string& sFuncName)
{
    if (m_HooksMap.find(sIdentifier) == m_HooksMap.end())
        return nullptr;

    auto& vecHooks = m_HooksMap[sIdentifier];
    auto findResult = std::find_if(vecHooks.begin(), vecHooks.end(), [&](const SReversibleHook& hook) {return hook.m_sFunctionName == sFuncName; });
    if (findResult == vecHooks.end())
        return nullptr;

    auto& refHook = *findResult;
    return &refHook;
}

unsigned int ReversibleHooks::GetJMPLocation(unsigned int dwFrom, unsigned int dwTo)
{
    return dwTo - dwFrom - ReversibleHooks::x86JMPSize;
}
