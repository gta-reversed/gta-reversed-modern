#pragma once
#include "PluginBase.h"
#define NUM_ESCALATORS 32

class CEscalators {
public:
    static CEscalator(&aEscalators)[NUM_ESCALATORS];

public:
    static void InjectHooks();

public:
    static void Shutdown();
    static void Init();
    static void AddOne(CVector const& vecStart, CVector const& vecBottom, CVector const& vecEnd, CVector const& vecTop, bool bMoveDown, CEntity* pEntity);
    static void Update();
};
