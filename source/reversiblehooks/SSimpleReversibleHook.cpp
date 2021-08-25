#include "StdInc.h"

SSimpleReversibleHook::SSimpleReversibleHook(uint32_t installAddress, void* addressToJumpTo, int iJmpCodeSize) {
    m_iLibFunctionAddress = (uint32_t)addressToJumpTo;
    m_iRealHookedAddress = installAddress;
    m_iHookedBytes = iJmpCodeSize;

    m_HookContent.jumpLocation = ReversibleHooks::GetJMPLocation(installAddress, m_iLibFunctionAddress);
    memset(m_HookContent.possibleNops, NOP_OPCODE, iJmpCodeSize - ReversibleHooks::x86JMPSize);

    //Copy lib function content
    m_LibHookContent.jumpLocation = ReversibleHooks::GetJMPLocation(m_iLibFunctionAddress, installAddress);
    m_iLibHookedBytes = ReversibleHooks::x86JMPSize;
    memcpy(&m_LibOriginalFunctionContent, (void*)m_iLibFunctionAddress, m_iLibHookedBytes);

    auto installHook = [&](bool bVirtProtect) {
        DWORD dwProtectHoodlum[2] = { 0 };
        if (bVirtProtect)
            VirtualProtect((void*)m_iRealHookedAddress, m_iHookedBytes, PAGE_EXECUTE_READWRITE, &dwProtectHoodlum[0]);

        memcpy(&m_OriginalFunctionContent, (void*)m_iRealHookedAddress, m_iHookedBytes);
        memcpy((void*)m_iRealHookedAddress, &m_HookContent, m_iHookedBytes);

        if (bVirtProtect)
            VirtualProtect((void*)m_iRealHookedAddress, m_iHookedBytes, dwProtectHoodlum[0], &dwProtectHoodlum[1]);

        m_bIsHooked = true;
        m_bImguiHooked = true;
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
            m_iRealHookedAddress = hoodlumHookAddress;
            m_HookContent.jumpLocation = ReversibleHooks::GetJMPLocation(hoodlumHookAddress, m_iLibFunctionAddress);
            m_iHookedBytes = ReversibleHooks::x86JMPSize;

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
}

std::shared_ptr<SSimpleReversibleHook> SSimpleReversibleHook::InstallHook(uint32_t installAddress, void* addressToJumpTo, int iJmpCodeSize) {
    return std::make_shared<SSimpleReversibleHook>(installAddress, addressToJumpTo, iJmpCodeSize);
}

void SSimpleReversibleHook::Switch()
{
    DWORD dwProtect[2] = { 0 };
    if (m_bIsHooked) {
        auto pGTADst = (void*)m_iRealHookedAddress;
        auto pGTASrc = (void*)&m_OriginalFunctionContent;
        VirtualProtect(pGTADst, m_iHookedBytes, PAGE_EXECUTE_READWRITE, &dwProtect[0]);
        memcpy(pGTADst, pGTASrc, m_iHookedBytes);
        VirtualProtect(pGTADst, m_iHookedBytes, dwProtect[0], &dwProtect[1]);

        auto pLibDst = (void*)m_iLibFunctionAddress;
        auto pLibSrc = (void*)&m_LibHookContent;
        VirtualProtect(pLibDst, m_iLibHookedBytes, PAGE_EXECUTE_READWRITE, &dwProtect[0]);
        memcpy(pLibDst, pLibSrc, m_iLibHookedBytes);
        VirtualProtect(pLibDst, m_iLibHookedBytes, dwProtect[0], &dwProtect[1]);
    }
    else {
        auto pGTADst = (void*)m_iRealHookedAddress;
        auto pGTASrc = (void*)&m_HookContent;
        VirtualProtect(pGTADst, m_iHookedBytes, PAGE_EXECUTE_READWRITE, &dwProtect[0]);
        memcpy(pGTADst, pGTASrc, m_iHookedBytes);
        VirtualProtect(pGTADst, m_iHookedBytes, dwProtect[0], &dwProtect[1]);

        auto pLibDst = (void*)m_iLibFunctionAddress;
        auto pLibSrc = (void*)&m_LibOriginalFunctionContent;
        VirtualProtect(pLibDst, m_iLibHookedBytes, PAGE_EXECUTE_READWRITE, &dwProtect[0]);
        memcpy(pLibDst, pLibSrc, m_iLibHookedBytes);
        VirtualProtect(pLibDst, m_iLibHookedBytes, dwProtect[0], &dwProtect[1]);
    }

    m_bIsHooked = !m_bIsHooked;
    m_bImguiHooked = m_bIsHooked;
}
