#pragma once

#include <rwplcore.h>

class CClumpModelInfo;

/**
 * collision plugin unique rwID
 */
#define rwID_COLLISIONPLUGIN  MAKECHUNKID(rwVENDORID_ROCKSTAR, 0xFA)

class CCollisionPlugin {
public:
    static CClumpModelInfo*& ms_currentModel;

public:
    static void InjectHooks();

    static bool PluginAttach();
    static void SetModelInfo(CClumpModelInfo* modelInfo);
};
