#pragma once

#include "RenderWare.h"

#define TXD_SKIN_SLOT "skin"

class CPlayerSkin {
public:
    static int32&    m_txdSlot;
    static float&    m_Angle;
    static float&    m_C3F04C;
    static RpClump*& m_Clump;

public:
    static void InjectHooks();

    static void       Initialise();
    static void       Shutdown();
    static void       RenderFrontendSkinEdit();
    static RwTexture* GetSkinTexture(const char* name);
};
