/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"

class CKeyGen {
public:
    static unsigned int *keyTable;

    static unsigned int GetKey(char const* str, int size);
    static unsigned int GetKey(char const* str);
    static unsigned int GetUppercaseKey(char const* str);
    static unsigned int AppendStringToKey(unsigned int key, char const* str);
};