#pragma once

#include "BreakObject_c.h"

class BreakManager_c {
public:
    BreakObject_c m_aObjects[512];

public:
    static void InjectHooks();

    void           Init();
    void           Exit();
    void           Update(float fTimestep);
    void           Render(bool bState);
    void           ResetAll();
    BreakObject_c* Add(CObject* pObject, RwV3d* vecPos, float fVelocityRand, bool bSmash);
};

extern BreakManager_c& g_breakMan;
