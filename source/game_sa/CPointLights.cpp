/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

unsigned int MAX_POINTLIGHTS = 32;

unsigned int& CPointLights::NumLights = *(unsigned int*)0xC3F0D0;
CPointLight* CPointLights::aLights = (CPointLight*)0xC3F0E0;
float* CPointLights::aCachedMapReadResults = (float*)0xC3F050;
unsigned int& CPointLights::NextCachedValue = *(unsigned int*)0xC3F0D4;
CVector* CPointLights::aCachedMapReads = (CVector*)0xC3F6E0;

// 0x6FFB40
void CPointLights::Init() {
    plugin::Call<0x6FFB40>();
}

// 0x6FFBB0
float CPointLights::GenerateLightsAffectingObject(CVector const* point, float* totalLighting, CEntity* entity) {
    return plugin::CallAndReturn<float, 0x6FFBB0, CVector const*, float*, CEntity*>(point, totalLighting, entity);
}

// 0x6FFE70
float CPointLights::GetLightMultiplier(CVector const* point) {
    return plugin::CallAndReturn<float, 0x6FFE70, CVector const*>(point);
}

// 0x6FFFE0
void CPointLights::RemoveLightsAffectingObject() {
    plugin::Call<0x6FFFE0>();
}

// 0x6FFFF0
bool CPointLights::ProcessVerticalLineUsingCache(CVector point, float* outZ) {
    return plugin::CallAndReturn<bool, 0x6FFFF0, CVector, float*>(point, outZ);
}

// 0x7000E0
void CPointLights::AddLight(unsigned char lightType, CVector point, CVector direction, float radius, float red, float green, float blue, unsigned char fogType, bool generateExtraShadows, CEntity* entityAffected) {
    plugin::Call<0x7000E0, unsigned char, CVector, CVector, float, float, float, float, unsigned char, bool, CEntity*>(lightType, point, direction, radius, red, green, blue, fogType, generateExtraShadows, entityAffected);
}

// 0x7002D0
void CPointLights::RenderFogEffect() {
    plugin::Call<0x7002D0>();
}
