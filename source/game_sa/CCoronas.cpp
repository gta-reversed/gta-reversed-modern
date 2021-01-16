#include "StdInc.h"

RwTexture* (&gpCoronaTexture)[CORONA_TEXTURES_COUNT] = *(RwTexture*(*)[CORONA_TEXTURES_COUNT])0xC3E000;
CRegisteredCorona(&CCoronas::aCoronas)[MAX_NUM_CORONAS] = *(CRegisteredCorona(*)[MAX_NUM_CORONAS])0xC3E058;

unsigned short(&CCoronas::ms_aEntityLightsOffsets)[8] = *(unsigned short(*)[8])0x8D5028;

void CCoronas::RegisterCorona(unsigned int id, CEntity* attachTo, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha, CVector const& posn, float radius, float farClip, RwTexture* texture, eCoronaFlareType flaretype, bool enableReflection, bool checkObstacles, int _param_not_used, float angle, bool longDistance, float nearClip, unsigned char fadeState, float fadeSpeed, bool onlyFromBelow, bool reflectionDelay)
{
    plugin::Call<0x6FC180, unsigned int, CEntity*, unsigned char, unsigned char, unsigned char, unsigned char, CVector const&, float, float, RwTexture*, eCoronaFlareType, bool, bool, int, float, bool, float, unsigned char, float, bool, bool>(id, attachTo, red, green, blue, alpha, posn, radius, farClip, texture, flaretype, enableReflection, checkObstacles, _param_not_used, angle, longDistance, nearClip, fadeState, fadeSpeed, onlyFromBelow, reflectionDelay);
}

void CCoronas::RegisterCorona(unsigned int id, CEntity* attachTo, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha, CVector const& posn, float radius, float farClip, eCoronaType coronaType, eCoronaFlareType flaretype, bool enableReflection, bool checkObstacles, int _param_not_used, float angle, bool longDistance, float nearClip, unsigned char fadeState, float fadeSpeed, bool onlyFromBelow, bool reflectionDelay)
{
    plugin::Call<0x6FC580, unsigned int, CEntity*, unsigned char, unsigned char, unsigned char, unsigned char, CVector const&, float, float, eCoronaType, eCoronaFlareType, bool, bool, int, float, bool, float, unsigned char, float, bool, bool>(id, attachTo, red, green, blue, alpha, posn, radius, farClip, coronaType, flaretype, enableReflection, checkObstacles, _param_not_used, angle, longDistance, nearClip, fadeState, fadeSpeed, onlyFromBelow, reflectionDelay);
}

void CCoronas::UpdateCoronaCoors(unsigned int id, CVector const& posn, float farClip, float angle)
{
    plugin::Call<0x6FC4D0, unsigned int, CVector const&, float, float>(id, posn, farClip, angle);
}
