/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

// CRC-32-IEEE
// https://www.xilinx.com/support/documentation/application_notes/xapp209.pdf

class CKeyGen {
public:
    static const uint32 keyTable[256];

public:
    static void InjectHooks();

    static uint32 AppendStringToKey(uint32 key, const char* str);
    static uint32 GetKey(const char* str);
    static uint32 GetKey(const char* str, int32 size);
    static uint32 GetUppercaseKey(const char* str);
};
