/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

unsigned int* CKeyGen::keyTable = (unsigned int*)0x8CD068;

// Converted from cdecl uint CKeyGen::GetKey(char const* str,int size) 0x53CED0
unsigned int CKeyGen::GetKey(char const* str, int size) {
    return ((unsigned int(__cdecl*)(char const*, int))0x53CED0)(str, size);
}

// Converted from cdecl uint CKeyGen::GetKey(char const* str) 0x53CF00
unsigned int CKeyGen::GetKey(char const* str) {
    return ((unsigned int(__cdecl*)(char const*))0x53CF00)(str);
}

// Converted from cdecl uint CKeyGen::GetUppercaseKey(char const* str) 0x53CF30
unsigned int CKeyGen::GetUppercaseKey(char const* str) {
    return ((unsigned int(__cdecl*)(char const*))0x53CF30)(str);
}

// Converted from cdecl uint CKeyGen::AppendStringToKey(uint key,char const* str) 0x53CF70
unsigned int CKeyGen::AppendStringToKey(unsigned int key, char const* str) {
    return ((unsigned int(__cdecl*)(unsigned int, char const*))0x53CF70)(key, str);
}