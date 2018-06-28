/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CVector.h"
#include "CRGBA.h"

enum eWeaponEffectsLockTexture {
    WEAPONEFFECTS_LOCK_ON = 0,
    WEAPONEFFECTS_LOCK_ON_FIRE = 1
};

class  CWeaponEffects {
public:
    bool    m_bActive;
private:
    char _pad01[3];
public:
    int     m_nTimeWhenToDeactivate; // -1 default
    CVector m_vecPosn;
    CRGBA   m_color;
    float   m_fSize;
    int field_1C;
    int field_20;
    float   m_fRotation;
    char field_28;
private:
    char _pad29[3];
public:

    CWeaponEffects();
    ~CWeaponEffects();
    static void Init();
    static void Shutdown();
    static bool IsLockedOn(int crosshairId);
    static void MarkTarget(int crosshairId, CVector posn, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha, float size, unsigned char arg7);
    static void ClearCrossHair(int crosshairId);
    static void ClearCrossHairs();
    static void ClearCrossHairImmediately(int crosshairId);
    static void ClearCrossHairsImmediately();
    static void Render();
};

VALIDATE_SIZE(CWeaponEffects, 0x2C);

extern unsigned int MAX_NUM_WEAPON_CROSSHAIRS; // default 2
extern CWeaponEffects *gCrossHair; // CWeaponEffects gCrossHair[MAX_NUM_WEAPON_CROSSHAIRS]
extern RwTexture *&gpCrossHairTex;
extern RwTexture **gpCrossHairTexFlight; // RwTexture *gpCrossHairTexFlight[2];