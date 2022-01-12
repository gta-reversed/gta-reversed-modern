#include "StdInc.h"

SSimpleReversibleHook::SSimpleReversibleHook(std::string id, std::string name, uint32 installAddress, void* addressToJumpTo, int iJmpCodeSize) :
    SReversibleHook(id, name, eReversibleHookType::Simple),
    m_iLibFunctionAddress((uint32)addressToJumpTo),
    m_iRealHookedAddress(installAddress),
    m_iHookedBytes(iJmpCodeSize)
{
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
    if (*(uint8*)installAddress == NOP_OPCODE) {
        bool bJumpFound = false;
        uint32 i = 0;
        for (; i < 4; i++) {
            if (*(uint8*)(installAddress + i) == JUMP_OPCODE) {
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

// VS has this magic called `Edit and Continue`
// The way it works is as follows:
// A function address basically just points to a `jmp` instruction, which
// then jumps to the actual function.
// Whenever a function is edited the compiler changes the `jmp` address
// thus, what we've stored as `m_LibOriginalFunctionContent` has changed.
// So, here we check if thats the case, and update `m_LibOriginalFunctionContent` if necessary
bool SSimpleReversibleHook::CheckLibFnForChangesAndStore(void* expected) {
    if (memcmp((void*)m_iLibFunctionAddress, expected, m_iLibHookedBytes) != 0) {
        memcpy(&m_LibOriginalFunctionContent, (void*)m_iLibFunctionAddress, m_iLibHookedBytes);
        return true;
    }
    return false;
}

void SSimpleReversibleHook::ApplyJumpToGTACode() {
    using namespace ReversibleHooks::detail;
    VirtualCopy((void*)m_iLibFunctionAddress, (void*)&m_LibHookContent, m_iLibHookedBytes);
}

void SSimpleReversibleHook::Switch()
{
    using namespace ReversibleHooks::detail;
    if (m_bIsHooked) {
        // Unhook (make our code jump to the GTA function)

        VirtualCopy((void*)m_iRealHookedAddress, (void*)&m_OriginalFunctionContent, m_iHookedBytes);
        ApplyJumpToGTACode();
    } else {
        // Hook (make the GTA function jump to ours)

        VirtualCopy((void*)m_iRealHookedAddress, (void*)&m_HookContent, m_iHookedBytes);
        VirtualCopy((void*)m_iLibFunctionAddress, (void*)&m_LibOriginalFunctionContent, m_iLibHookedBytes);
    }
    m_bIsHooked = !m_bIsHooked;
    m_bImguiHooked = m_bIsHooked;
}

void SSimpleReversibleHook::Check() {
    if (m_bIsHooked) {
        CheckLibFnForChangesAndStore((void*)m_LibOriginalFunctionContent);
    } else {
        if (CheckLibFnForChangesAndStore((void*)&m_LibHookContent)) {
            ApplyJumpToGTACode(); // Compiler overwrote it, so we must re-apply the jump
        }
    }
}
