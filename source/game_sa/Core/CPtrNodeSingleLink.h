/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"

class  CPtrNodeSingleLink {
public:
    void *pItem;
    CPtrNodeSingleLink *pNext;

    inline CPtrNodeSingleLink(void *item) : pItem(item) {}

    static void* operator new(unsigned int size);
    static void operator delete(void* data);
};

VALIDATE_SIZE(CPtrNodeSingleLink, 8);