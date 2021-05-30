/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

bool& CHeli::bPoliceHelisAllowed = *(bool*)0x8D338C;
unsigned int& CHeli::TestForNewRandomHelisTimer = *(unsigned int*)0xC1C960;
CHeli** CHeli::pHelis = (CHeli**)0xC1C964;
unsigned int& CHeli::NumberOfSearchLights = *(unsigned int*)0xC1C96C;
bool& CHeli::bHeliControlsCheat = *(bool*)0xC1C970;
tHeliLight* CHeli::HeliSearchLights = (tHeliLight*)0xC1C990;

// Converted from thiscall void CHeli::CHeli(int modelIndex,uchar createdBy) 0x6C4190
CHeli::CHeli(int modelIndex, unsigned char createdBy) : CAutomobile(plugin::dummy) {
    plugin::CallMethod<0x6C4190, CHeli*, int, unsigned char>(this, modelIndex, createdBy);
}

// Converted from cdecl void CHeli::InitHelis(void) 0x6C4560
void CHeli::InitHelis() {
    ((void(__cdecl*)())0x6C4560)();
}

// Converted from cdecl void CHeli::AddHeliSearchLight(CVector const& origin,CVector const& target,float targetRadius,float power,uint coronaIndex,uchar unknownFlag,uchar drawShadow) 0x6C45B0
void CHeli::AddHeliSearchLight(CVector const& origin, CVector const& target, float targetRadius, float power, unsigned int coronaIndex, unsigned char unknownFlag, unsigned char drawShadow) {
    ((void(__cdecl*)(CVector const&, CVector const&, float, float, unsigned int, unsigned char, unsigned char))0x6C45B0)(origin, target, targetRadius, power, coronaIndex, unknownFlag, drawShadow);
}

// Converted from thiscall void CHeli::PreRenderAlways(void) 0x6C4640
void CHeli::PreRenderAlways() {
    ((void(__thiscall*)(CHeli*))0x6C4640)(this);
}

// Converted from cdecl void CHeli::Pre_SearchLightCone(void) 0x6C4650
void CHeli::Pre_SearchLightCone() {
    ((void(__cdecl*)())0x6C4650)();
}

// Converted from cdecl void CHeli::Post_SearchLightCone(void) 0x6C46E0
void CHeli::Post_SearchLightCone() {
    ((void(__cdecl*)())0x6C46E0)();
}

// Converted from cdecl void CHeli::SpecialHeliPreRender(void) 0x6C4750
void CHeli::SpecialHeliPreRender() {
    ((void(__cdecl*)())0x6C4750)();
}

// Converted from thiscall CVector CHeli::FindSwatPositionRelativeToHeli(int swatNumber) 0x6C4760
CVector CHeli::FindSwatPositionRelativeToHeli(int swatNumber) {
    CVector result;
    ((void(__thiscall*)(CHeli*, CVector*, int))0x6C4760)(this, &result, swatNumber);
    return result;
}

// Converted from cdecl void CHeli::SwitchPoliceHelis(bool enable) 0x6C4800
void CHeli::SwitchPoliceHelis(bool enable) {
    ((void(__cdecl*)(bool))0x6C4800)(enable);
}

// Converted from cdecl void CHeli::SearchLightCone(int coronaIndex,CVector origin,CVector target,float targetRadius,float power,uchar unknownFlag,uchar drawShadow,CVector* ,CVector* ,CVector* ,bool,float baseRadius) 0x6C58E0
void CHeli::SearchLightCone(int coronaIndex, CVector origin, CVector target, float targetRadius, float power, unsigned char unknownFlag, unsigned char drawShadow, CVector* arg7, CVector* arg8, CVector* arg9, bool arg10, float baseRadius) {
    ((void(__cdecl*)(int, CVector, CVector, float, float, unsigned char, unsigned char, CVector*, CVector*, CVector*, bool, float))0x6C58E0)(coronaIndex, origin, target, targetRadius, power, unknownFlag, drawShadow, arg7, arg8, arg9, arg10, baseRadius);
}

// Converted from cdecl CHeli* CHeli::GenerateHeli(CPed *target,bool newsHeli) 0x6C6520
CHeli* CHeli::GenerateHeli(CPed* target, bool newsHeli) {
    return ((CHeli * (__cdecl*)(CPed*, bool))0x6C6520)(target, newsHeli);
}

// Converted from cdecl bool CHeli::TestSniperCollision(CVector *origin,CVector *target) 0x6C6890
bool CHeli::TestSniperCollision(CVector* origin, CVector* target) {
    return ((bool(__cdecl*)(CVector*, CVector*))0x6C6890)(origin, target);
}

// Converted from thiscall bool CHeli::SendDownSwat(void) 0x6C69C0
bool CHeli::SendDownSwat() {
    return ((bool(__thiscall*)(CHeli*))0x6C69C0)(this);
}

// Converted from cdecl void CHeli::UpdateHelis(void) 0x6C79A0
void CHeli::UpdateHelis() {
    ((void(__cdecl*)())0x6C79A0)();
}

// Converted from cdecl void CHeli::RenderAllHeliSearchLights(void) 0x6C7C50
void CHeli::RenderAllHeliSearchLights() {
    ((void(__cdecl*)())0x6C7C50)();
}
