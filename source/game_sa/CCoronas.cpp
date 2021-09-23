#include "StdInc.h"

float& CCoronas::SunScreenX = *(float*)0xC3E028;
float& CCoronas::SunScreenY = *(float*)0xC3E02C;
//bool& CCoronas::SunBlockedByClouds = *(bool*)0x0;
bool& CCoronas::bChangeBrightnessImmediately = *(bool*)0xC3E034;
uint32& CCoronas::NumCoronas = *(uint32*)0xC3E038;
float& CCoronas::LightsMult = *(float*)0x8D4B5C; // 1.0f
uint32& CCoronas::MoonSize = *(uint32*)0x8D4B60; // 3
RwTexture* (&gpCoronaTexture)[CORONA_TEXTURES_COUNT] = *(RwTexture*(*)[CORONA_TEXTURES_COUNT])0xC3E000;
CRegisteredCorona(&CCoronas::aCoronas)[MAX_NUM_CORONAS] = *(CRegisteredCorona(*)[MAX_NUM_CORONAS])0xC3E058;

uint16(&CCoronas::ms_aEntityLightsOffsets)[8] = *(uint16(*)[8])0x8D5028;

char (&coronaTexturesAlphaMasks)[260] = *(char (*)[260])0x8D4A58;

void CCoronas::InjectHooks() {
//    ReversibleHooks::Install("CCoronas", "Init", 0x6FAA70, &CCoronas::Init);
//    ReversibleHooks::Install("CCoronas", "Shutdown", 0x6FAB00, &CCoronas::Shutdown);
//    ReversibleHooks::Install("CCoronas", "Update", 0x6FADF0, &CCoronas::Update);
//    ReversibleHooks::Install("CCoronas", "Render", 0x6FAEC0, &CCoronas::Render);
//    ReversibleHooks::Install("CCoronas", "RenderReflections", 0x6FB630, &CCoronas::RenderReflections);
//    ReversibleHooks::Install("CCoronas", "RenderSunReflection", 0x6FBAA0, &CCoronas::RenderSunReflection);
//    ReversibleHooks::Install("CCoronas", "RegisterCorona_texture", 0x6FC180, &CCoronas::RegisterCorona);
//    ReversibleHooks::Install("CCoronas", "RegisterCorona_type", 0x6FC580, &CCoronas::RegisterCorona);
//    ReversibleHooks::Install("CCoronas", "UpdateCoronaCoors", 0x6FC4D0, &CCoronas::UpdateCoronaCoors);
//    ReversibleHooks::Install("CCoronas", "DoSunAndMoon", 0x6FC5A0, &CCoronas::DoSunAndMoon);
}

// Initialises coronas
// 0x6FAA70
void CCoronas::Init() {
    plugin::Call<0x6FAA70>();
}

// Terminates coronas
// 0x6FAB00
void CCoronas::Shutdown() {
    plugin::Call<0x6FAB00>();
}

// Updates coronas
// 0x6FADF0
void CCoronas::Update() {
    plugin::Call<0x6FADF0>();
}

// Renders coronas
// 0x6FAEC0
void CCoronas::Render() {
    plugin::Call<0x6FAEC0>();
}

// Renders coronas reflections on a wet ground
// 0x6FB630
void CCoronas::RenderReflections() {
    plugin::Call<0x6FB630>();
}

// Renders sun reflection on a water
// 0x6FBAA0
void CCoronas::RenderSunReflection() {
    plugin::Call<0x6FBAA0>();
}

// Creates corona by texture
// 0x6FC180
void CCoronas::RegisterCorona(uint32 id, CEntity* attachTo, uint8 red, uint8 green, uint8 blue, uint8 alpha, CVector const& posn, float radius, float farClip, RwTexture* texture, eCoronaFlareType flareType, bool enableReflection, bool checkObstacles, int32 _param_not_used, float angle, bool longDistance, float nearClip, uint8 fadeState, float fadeSpeed, bool onlyFromBelow, bool reflectionDelay) {
    plugin::Call<0x6FC180, uint32, CEntity*, uint8, uint8, uint8, uint8, CVector const&, float, float, RwTexture*, eCoronaFlareType, bool, bool, int32, float, bool, float, uint8, float, bool, bool>(id, attachTo, red, green, blue, alpha, posn, radius, farClip, texture, flareType, enableReflection, checkObstacles, _param_not_used, angle, longDistance, nearClip, fadeState, fadeSpeed, onlyFromBelow, reflectionDelay);
}

// Creates corona by type
// 0x6FC580
void CCoronas::RegisterCorona(uint32 id, CEntity* attachTo, uint8 red, uint8 green, uint8 blue, uint8 alpha, CVector const& posn, float radius, float farClip, eCoronaType coronaType, eCoronaFlareType flareType, bool enableReflection, bool checkObstacles, int32 _param_not_used, float angle, bool longDistance, float nearClip, uint8 fadeState, float fadeSpeed, bool onlyFromBelow, bool reflectionDelay) {
    plugin::Call<0x6FC580, uint32, CEntity*, uint8, uint8, uint8, uint8, CVector const&, float, float, eCoronaType, eCoronaFlareType, bool, bool, int32, float, bool, float, uint8, float, bool, bool>(id, attachTo, red, green, blue, alpha, posn, radius, farClip, coronaType, flareType, enableReflection, checkObstacles, _param_not_used, angle, longDistance, nearClip, fadeState, fadeSpeed, onlyFromBelow, reflectionDelay);
}

// 0x6FC4D0
void CCoronas::UpdateCoronaCoors(uint32 id, CVector const& posn, float farClip, float angle) {
    plugin::Call<0x6FC4D0, uint32, CVector const&, float, float>(id, posn, farClip, angle);
}

// Draw sun (Moon went to CClouds since SA)
// 0x6FC5A0
void CCoronas::DoSunAndMoon() {
    plugin::Call<0x6FC5A0>();
}