#pragma once
#include "PluginBase.h"

class CEscalators {
public:
    static constexpr unsigned int NUM_ESCALATORS = 32;
    static CEscalator(&aEscalators)[NUM_ESCALATORS];

public:
    static void InjectHooks();

public:
    static void Init();
    static void Shutdown();
    static void Update();
    static void AddOne(CVector const& vecStart, CVector const& vecBottom, CVector const& vecEnd, CVector const& vecTop, bool bMoveDown, CEntity* pEntity);
};
