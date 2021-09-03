/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

bool& CHeli::bPoliceHelisAllowed = *(bool*)0x8D338C;
uint32& CHeli::TestForNewRandomHelisTimer = *(uint32*)0xC1C960;
CHeli** CHeli::pHelis = (CHeli**)0xC1C964;
uint32& CHeli::NumberOfSearchLights = *(uint32*)0xC1C96C;
bool& CHeli::bHeliControlsCheat = *(bool*)0xC1C970;
tHeliLight* CHeli::HeliSearchLights = (tHeliLight*)0xC1C990;

void CHeli::InjectHooks() {

}

// 0x6C4190
CHeli::CHeli(int32 modelIndex, eVehicleCreatedBy createdBy) : CAutomobile(plugin::dummy) {
    plugin::CallMethod<0x6C4190, CHeli*, int32, eVehicleCreatedBy>(this, modelIndex, createdBy);
}

// 0x6C4560
void CHeli::InitHelis() {
    ((void(__cdecl*)())0x6C4560)();
}

// 0x6C45B0
void CHeli::AddHeliSearchLight(CVector const& origin, CVector const& target, float targetRadius, float power, uint32 coronaIndex, uint8 unknownFlag, uint8 drawShadow) {
    ((void(__cdecl*)(CVector const&, CVector const&, float, float, uint32, uint8, uint8))0x6C45B0)(origin, target, targetRadius, power, coronaIndex, unknownFlag, drawShadow);
}

// 0x6C4640
void CHeli::PreRenderAlways() {
    // NOP
}

// 0x6C4650
void CHeli::Pre_SearchLightCone() {
    ((void(__cdecl*)())0x6C4650)();
}

// 0x6C46E0
void CHeli::Post_SearchLightCone() {
    ((void(__cdecl*)())0x6C46E0)();
}

// 0x6C4750
void CHeli::SpecialHeliPreRender() {
    // NOP
}

// 0x6C4760
CVector CHeli::FindSwatPositionRelativeToHeli(int32 swatNumber) {
    CVector result;
    ((void(__thiscall*)(CHeli*, CVector*, int32))0x6C4760)(this, &result, swatNumber);
    return result;
}

// 0x6C4800
void CHeli::SwitchPoliceHelis(bool enable) {
    bPoliceHelisAllowed = enable;
}

// 0x6C58E0
void CHeli::SearchLightCone(int32 coronaIndex, CVector origin, CVector target, float targetRadius, float power, uint8 unknownFlag, uint8 drawShadow, CVector* arg7, CVector* arg8, CVector* arg9, bool arg10, float baseRadius) {
    ((void(__cdecl*)(int32, CVector, CVector, float, float, uint8, uint8, CVector*, CVector*, CVector*, bool, float))0x6C58E0)(coronaIndex, origin, target, targetRadius, power, unknownFlag, drawShadow, arg7, arg8, arg9, arg10, baseRadius);
}

// 0x6C6520
CHeli* CHeli::GenerateHeli(CPed* target, bool newsHeli) {
    return ((CHeli * (__cdecl*)(CPed*, bool))0x6C6520)(target, newsHeli);
}

// 0x6C6890
bool CHeli::TestSniperCollision(CVector* origin, CVector* target) {
    return ((bool(__cdecl*)(CVector*, CVector*))0x6C6890)(origin, target);
}

// 0x6C69C0
bool CHeli::SendDownSwat() {
    return ((bool(__thiscall*)(CHeli*))0x6C69C0)(this);
}

// 0x6C79A0
void CHeli::UpdateHelis() {
    ((void(__cdecl*)())0x6C79A0)();
}

// 0x6C7C50
void CHeli::RenderAllHeliSearchLights() {
    ((void(__cdecl*)())0x6C7C50)();
}

// 0x6C6D30
void CHeli::BlowUpCar(CEntity* damager, uint8 bHideExplosion) {
    return BlowUpCar_Reversed(damager, bHideExplosion);
}

void CHeli::BlowUpCar_Reversed(CEntity* damager, uint8 bHideExplosion) {
    plugin::CallMethod<0x6C6D30, CHeli*, CEntity*, uint8>(this, damager, bHideExplosion);
}

// 0x6C4530
void CHeli::Fix() {
    Fix_Reversed();
}

void CHeli::Fix_Reversed() {
    plugin::CallMethod<0x6C4530, CHeli*>(this);
}
