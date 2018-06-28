/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CLink.h"

template<typename T>
class CLinkList {
public:
    CLink<T> usedListHead;
    CLink<T> usedListTail;
    CLink<T> freeListHead;
    CLink<T> freeListTail;
    CLink<T>* links;
};

VALIDATE_SIZE(CLinkList<void *>, 0x34);