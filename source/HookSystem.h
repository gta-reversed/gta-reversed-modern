#pragma once

#include <cstdint>

#pragma pack(push, 1)
struct SHook
{
    unsigned char jumpOpCode;
    unsigned int jumpLocation;
    unsigned char possibleNops[47] = {0}; // maximum size for nops

    SHook ()
    {
        jumpOpCode = 0xE9;
        jumpLocation = 0;
    }
};
#pragma pack(pop)

static_assert(sizeof(SHook) == 0x34, "Incorrect struct size: SHook");

template<typename T>
void HookInstall(DWORD installAddress, T addressToJumpTo, int iJmpCodeSize)
{
    DWORD dwAddressToJumpTo;
    _asm
    {
        mov		eax, addressToJumpTo
        mov		dwAddressToJumpTo, eax
    }

    const DWORD x86FixedJumpSize = 5;
    SHook theHook;

    theHook.jumpLocation =  (DWORD)dwAddressToJumpTo - (DWORD)installAddress - (DWORD)x86FixedJumpSize;
    memset(theHook.possibleNops, 0x90, iJmpCodeSize - x86FixedJumpSize);

    DWORD dwProtect[2];
    VirtualProtect((void*)installAddress, 5, PAGE_EXECUTE_READWRITE, &dwProtect[0]);
    memcpy((void*)installAddress, &theHook, iJmpCodeSize);
    VirtualProtect((void*)installAddress, 5, dwProtect[0], &dwProtect[1]);
}