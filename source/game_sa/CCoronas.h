/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "CRegisteredCorona.h"

class CCoronas {
public:
    // sun 2d position
    static float& SunScreenX;
    static float& SunScreenY;
    // are there any obstacles between sun and camera
    static bool& SunBlockedByClouds;
    // change coronas brightness immediately
    static bool& bChangeBrightnessImmediately;
    // num of registered coronas in frame
    static unsigned int& NumCoronas;
    // coronas intensity multiplier
    static float& LightsMult;
    // this is used to control moon size when you shooting it with sniper
    static unsigned int& MoonSize;
    // Coronas array. count: MAX_NUM_CORONAS (default: 64)
    static constexpr int MAX_NUM_CORONAS = 64;
    static CRegisteredCorona (&aCoronas)[MAX_NUM_CORONAS];

    static unsigned short (&ms_aEntityLightsOffsets)[8];

public:
    static void InjectHooks();

    static void Init();
    static void Shutdown();
    static void Update();
    static void Render();
    static void RenderReflections();
    static void RenderSunReflection();
    static void RegisterCorona(unsigned int id, CEntity* attachTo, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha, CVector const& posn,
                               float radius, float farClip, RwTexture* texture, eCoronaFlareType flareType, bool enableReflection, bool checkObstacles, int _param_not_used,
                               float angle, bool longDistance, float nearClip, unsigned char fadeState, float fadeSpeed, bool onlyFromBelow, bool reflectionDelay);
    static void RegisterCorona(unsigned int id, CEntity* attachTo, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha, CVector const& posn,
                               float radius, float farClip, eCoronaType coronaType, eCoronaFlareType flareType, bool enableReflection, bool checkObstacles, int _param_not_used,
                               float angle, bool longDistance, float nearClip, unsigned char fadeState, float fadeSpeed, bool onlyFromBelow, bool reflectionDelay);

    static void UpdateCoronaCoors(unsigned int id, CVector const& posn, float farClip, float angle);
    static void DoSunAndMoon();
};

extern unsigned int MAX_CORONAS;
constexpr int CORONA_TEXTURES_COUNT = 10;
extern RwTexture* (&gpCoronaTexture)[CORONA_TEXTURES_COUNT];
