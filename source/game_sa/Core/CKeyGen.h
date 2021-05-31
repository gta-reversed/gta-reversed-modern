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
    static const unsigned int keyTable[256];

public:
    static void InjectHooks();

    static unsigned int AppendStringToKey(unsigned int key, const char* str);
    static unsigned int GetKey(const char* str);
    static unsigned int GetKey(const char* str, int size);
    static unsigned int GetUppercaseKey(const char* str);
};
