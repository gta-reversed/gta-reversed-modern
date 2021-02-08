/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "CEntity.h"

class CBuilding : public CEntity {
public:
    CBuilding();
    static void* operator new(unsigned int size);
    static void operator delete(void* data);

public:
    static void InjectHooks();

    void ReplaceWithNewModel(int newModelIndex);
};

VALIDATE_SIZE(CBuilding, 0x38);

bool IsBuildingPointerValid(CBuilding* pBuilding);

extern int32_t& gBuildings;
