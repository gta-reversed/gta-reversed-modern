/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"

template <typename ObjectType, unsigned int Capacity>
class CStore {
public:
    unsigned int count;
    ObjectType   objects[Capacity];

    CStore() {
        count = 0;
    }
};