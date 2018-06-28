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
protected:
    CBuilding(plugin::dummy_func_t) : CEntity(plugin::dummy) {}
public:
	void ReplaceWithNewModel(int newModelIndex);

    static void* operator new(unsigned int size);
    static void operator delete(void* data);
    CBuilding();
};

VALIDATE_SIZE(CBuilding, 0x38);