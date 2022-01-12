/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Vector.h"
#include "RGBA.h"

enum eWeaponEffectsLockTexture {
    WEAPONEFFECTS_LOCK_ON = 0,
    WEAPONEFFECTS_LOCK_ON_FIRE = 1
};

class CWeaponEffects {
public:
    bool    m_bActive;
    char    _pad01[3];
    int32   m_nTimeWhenToDeactivate; // -1 default
    CVector m_vecPosn;
    CRGBA   m_color;
    float   m_fSize;
    int32   field_1C;
    int32   field_20;
    float   m_fRotation;
    char    field_28;
    char    _pad29[3];

public:
    static void InjectHooks();

    CWeaponEffects();
    ~CWeaponEffects();

    static void Init();
    static void Shutdown();
    static bool IsLockedOn(int32 crosshairId);
    static void MarkTarget(int32 crosshairId, CVector posn, uint8 red, uint8 green, uint8 blue, uint8 alpha, float size, uint8 arg7);
    static void ClearCrossHair(int32 crosshairId);
    static void ClearCrossHairs();
    static void ClearCrossHairImmediately(int32 crosshairId);
    static void ClearCrossHairsImmediately();
    static void Render();
};

VALIDATE_SIZE(CWeaponEffects, 0x2C);

extern uint32 MAX_NUM_WEAPON_CROSSHAIRS; // default 2
extern CWeaponEffects *gCrossHair; // CWeaponEffects gCrossHair[MAX_NUM_WEAPON_CROSSHAIRS]
extern RwTexture *&gpCrossHairTex;
extern RwTexture **gpCrossHairTexFlight; // RwTexture *gpCrossHairTexFlight[2];