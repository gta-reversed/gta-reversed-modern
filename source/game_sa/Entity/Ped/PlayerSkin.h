#pragma once

#include "RenderWare.h"

class CPlayerSkin {
public:
    static int32&    m_txdSlot;

public:
    static void InjectHooks();

    static void       Initialise();
    static void       Shutdown();
    static void       RenderFrontendSkinEdit();
    static RwTexture* GetSkinTexture(const char* name);
};
