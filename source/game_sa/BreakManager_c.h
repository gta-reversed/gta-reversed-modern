#pragma once

#include "BreakObject_c.h"

class BreakManager_c {
public:
    BreakObject_c m_aObjects[64];

public:
    static void InjectHooks();

    bool           Init();
    void           Exit();
    void           ResetAll();
    bool           Add(CObject* object, CVector* vecPos, float fVelocityRand, bool bSmash);
    void           Update(float timeStep);
    void           Render(uint8 state);
    BreakObject_c* GetFirstFreeSlot();
};

VALIDATE_SIZE(BreakManager_c, 0x800);

extern BreakManager_c& g_breakMan;
