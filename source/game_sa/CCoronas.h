/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CRegisteredCorona.h"

class  CCoronas {
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
	static CRegisteredCorona *aCoronas;

	// Initialises coronas
	static void Init();
	// Terminates coronas
	static void Shutdown();
	// Updates coronas
	static void Update();
	// Renders coronas
	static void Render();
	// Renders coronas reflections on a wet ground
	static void RenderReflections();
	// Renders sun reflection on a water
	static void RenderSunReflection();
	// Creates corona by texture
	static void RegisterCorona(unsigned int id, CEntity *attachTo, unsigned char red, unsigned char green, unsigned char blue, 
        unsigned char alpha, CVector const &posn, float radius, float farClip, RwTexture *texture, eCoronaFlareType flaretype, 
        bool enableReflection, bool checkObstacles, int _param_not_used, float angle, bool longDistance, float nearClip,
        unsigned char fadeState, float fadeSpeed, bool onlyFromBelow, bool reflectionDelay);
	// Creates corona by type
	static void RegisterCorona(unsigned int id, CEntity *attachTo, unsigned char red, unsigned char green, unsigned char blue,
        unsigned char alpha, CVector const &posn, float radius, float farClip, eCoronaType coronaType, eCoronaFlareType flaretype,
        bool enableReflection, bool checkObstacles, int _param_not_used, float angle, bool longDistance, float nearClip, 
        unsigned char fadeState, float fadeSpeed, bool onlyFromBelow, bool reflectionDelay);

	static void UpdateCoronaCoors(unsigned int id, CVector  const& posn, float farClip, float angle);
	// Draw sun (Moon went to CClouds since SA)
	static void DoSunAndMoon();
};

extern unsigned int MAX_CORONAS;
extern RwTexture **gpCoronaTexture;