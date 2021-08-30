/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

Fx_c& g_fx = *(Fx_c*)0xA9AE00;

// 0x49E620
Fx_c::Fx_c() {
    ((void(__thiscall*)(Fx_c*))0x49E620)(this);
}

// 0x49E630
Fx_c::~Fx_c() {
    ((void(__thiscall*)(Fx_c*))0x49E630)(this);
}

// 0x49E640
void Fx_c::Update(RwCamera* camera, float timeDelta) {
    ((void(__thiscall*)(Fx_c*, RwCamera*, float))0x49E640)(this, camera, timeDelta);
}

// 0x49E650
void Fx_c::Render(RwCamera* camera, unsigned char arg1) {
    ((void(__thiscall*)(Fx_c*, RwCamera*, unsigned char))0x49E650)(this, camera, arg1);
}

// 0x49E660
void Fx_c::InitStaticSystems() {
    ((void(__thiscall*)(Fx_c*))0x49E660)(this);
}

// 0x49E850
void Fx_c::ExitStaticSystems() {
    ((void(__thiscall*)(Fx_c*))0x49E850)(this);
}

// 0x49E950
void Fx_c::CreateMatFromVec(RwMatrix* out, CVector* origin, CVector* direction) {
    ((void(__thiscall*)(Fx_c*, RwMatrix*, CVector*, CVector*))0x49E950)(this, out, origin, direction);
}

// 0x49EA40
void Fx_c::SetFxQuality(FxQuality_e quality) {
    ((void(__thiscall*)(Fx_c*, FxQuality_e))0x49EA40)(this, quality);
}

// 0x49EA50
FxQuality_e Fx_c::GetFxQuality() {
    return ((FxQuality_e(__thiscall*)(Fx_c*))0x49EA50)(this);
}

// 0x49EA60
void Fx_c::InitEntitySystems() {
    ((void(__thiscall*)(Fx_c*))0x49EA60)(this);
}

// 0x49EA90
bool Fx_c::Init() {
    return ((bool(__thiscall*)(Fx_c*))0x49EA90)(this);
}

// 0x49EAE0
void Fx_c::Reset() {
    ((void(__thiscall*)(Fx_c*))0x49EAE0)(this);
}

// 0x49EB00
void Fx_c::AddBlood(CVector& origin, CVector& direction, int amount, float arg3) {
    ((void(__thiscall*)(Fx_c*, CVector&, CVector&, int, float))0x49EB00)(this, origin, direction, amount, arg3);
}

// 0x49EE10
void Fx_c::AddWood(CVector& origin, CVector& direction, int amount, float arg3) {
    ((void(__thiscall*)(Fx_c*, CVector&, CVector&, int, float))0x49EE10)(this, origin, direction, amount, arg3);
}

// 0x49F040
void Fx_c::AddSparks(CVector& origin, CVector& direction, float force, int amount, CVector across, unsigned char sparksType, float spread, float life) {
    ((void(__thiscall*)(Fx_c*, CVector&, CVector&, float, int, CVector, unsigned char, float, float))0x49F040)(this, origin, direction, force, amount, across, sparksType, spread, life);
}

// 0x49F300
void Fx_c::AddTyreBurst(CVector& position, CVector& velocity) {
    ((void(__thiscall*)(Fx_c*, CVector&, CVector&))0x49F300)(this, position, velocity);
}

// 0x49F3D0
void Fx_c::AddBulletImpact(CVector& position, CVector& direction, int bulletFxType, int amount, float arg4) {
    ((void(__thiscall*)(Fx_c*, CVector&, CVector&, int, int, float))0x49F3D0)(this, position, direction, bulletFxType, amount, arg4);
}

// 0x49F670
void Fx_c::AddPunchImpact(CVector& position, CVector& velocity, int arg2) {
    ((void(__thiscall*)(Fx_c*, CVector&, CVector&, int))0x49F670)(this, position, velocity, arg2);
}

// 0x49F750
void Fx_c::AddDebris(CVector& position, RwRGBA& color, float scale, int amount) {
    ((void(__thiscall*)(Fx_c*, CVector&, RwRGBA&, float, int))0x49F750)(this, position, color, scale, amount);
}

// 0x49F970
void Fx_c::AddGlass(CVector& position, RwRGBA& color, float scale, int amount) {
    ((void(__thiscall*)(Fx_c*, CVector&, RwRGBA&, float, int))0x49F970)(this, position, color, scale, amount);
}

// 0x49FB30
void Fx_c::AddWheelSpray(CVehicle* vehicle, CVector position, unsigned char arg2, unsigned char arg3, float arg4) {
    ((void(__thiscall*)(Fx_c*, CVehicle*, CVector, unsigned char, unsigned char, float))0x49FB30)(this, vehicle, position, arg2, arg3, arg4);
}

// 0x49FF20
void Fx_c::AddWheelGrass(CVehicle* vehicle, CVector position, unsigned char arg2, float arg3) {
    ((void(__thiscall*)(Fx_c*, CVehicle*, CVector, unsigned char, float))0x49FF20)(this, vehicle, position, arg2, arg3);
}

// 0x4A0170
void Fx_c::AddWheelGravel(CVehicle* vehicle, CVector position, unsigned char arg2, float arg3) {
    ((void(__thiscall*)(Fx_c*, CVehicle*, CVector, unsigned char, float))0x4A0170)(this, vehicle, position, arg2, arg3);
}

// 0x4A03C0
void Fx_c::AddWheelMud(CVehicle* vehicle, CVector position, unsigned char arg2, float arg3) {
    ((void(__thiscall*)(Fx_c*, CVehicle*, CVector, unsigned char, float))0x4A03C0)(this, vehicle, position, arg2, arg3);
}

// 0x4A0610
void Fx_c::AddWheelSand(CVehicle* vehicle, CVector position, unsigned char arg2, float arg3) {
    ((void(__thiscall*)(Fx_c*, CVehicle*, CVector, unsigned char, float))0x4A0610)(this, vehicle, position, arg2, arg3);
}

// 0x4A09C0
void Fx_c::AddWheelDust(CVehicle* vehicle, CVector position, unsigned char arg2, float arg3) {
    ((void(__thiscall*)(Fx_c*, CVehicle*, CVector, unsigned char, float))0x4A09C0)(this, vehicle, position, arg2, arg3);
}

// 0x4A0D70
void Fx_c::TriggerWaterHydrant(CVector& position) {
    ((void(__thiscall*)(Fx_c*, CVector&))0x4A0D70)(this, position);
}

// 0x4A0DE0
void Fx_c::TriggerGunshot(CEntity* entity, CVector& origin, CVector& target, bool doGunflash) {
    ((void(__thiscall*)(Fx_c*, CEntity*, CVector&, CVector&, bool))0x4A0DE0)(this, entity, origin, target, doGunflash);
}

// 0x4A0FA0
void Fx_c::TriggerTankFire(CVector& origin, CVector& target) {
    ((void(__thiscall*)(Fx_c*, CVector&, CVector&))0x4A0FA0)(this, origin, target);
}

// 0x4A1070
void Fx_c::TriggerWaterSplash(CVector& position) {
    ((void(__thiscall*)(Fx_c*, CVector&))0x4A1070)(this, position);
}

// 0x4A10E0
void Fx_c::TriggerBulletSplash(CVector& position) {
    ((void(__thiscall*)(Fx_c*, CVector&))0x4A10E0)(this, position);
}

// 0x4A1150
void Fx_c::TriggerFootSplash(CVector& position) {
    ((void(__thiscall*)(Fx_c*, CVector&))0x4A1150)(this, position);
}

// 0x4A11E0
void Fx_c::CreateEntityFx(CEntity* entity, char* fxName, RwV3d* position, RwMatrix* transform) {
    ((void(__thiscall*)(Fx_c*, CEntity*, char*, RwV3d*, RwMatrix*))0x4A11E0)(this, entity, fxName, position, transform);
}

// 0x4A1280
void Fx_c::DestroyEntityFx(CEntity* entity) {
    ((void(__thiscall*)(Fx_c*, CEntity*))0x4A1280)(this, entity);
}

// 0x4A12D0
void Fx_c::ExitEntitySystems() {
    ((void(__thiscall*)(Fx_c*))0x4A12D0)(this);
}

// 0x4A1320
void Fx_c::Exit() {
    ((void(__thiscall*)(Fx_c*))0x4A1320)(this);
}

// 0x4A13B0
void RenderBegin(RwRaster* raster, RwMatrix* transform, unsigned int transformRenderFlags) {
    ((void(__cdecl*)(RwRaster*, RwMatrix*, unsigned int))0x4A13B0)(raster, transform, transformRenderFlags);
}

// 0x4A1410
void RenderAddTri(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float u1, float v1, float u2, float v2, float u3, float v3, int r1, int g1, int b1, int a1, int r2, int g2, int b2, int a2, int r3, int g3, int b3, int a3) {
    ((void(__cdecl*)(float, float, float, float, float, float, float, float, float, float, float, float, float, float, float, int, int, int, int, int, int, int, int, int, int, int, int))0x4A1410)(x1, y1, z1, x2, y2, z2, x3, y3, z3, u1, v1, u2, v2, u3, v3, r1, g1, b1, a1, r2, g2, b2, a2, r3, g3, b3, a3);
}

// 0x4A1600
void RenderEnd() {
    ((void(__cdecl*)())0x4A1600)();
}

// 0x4A1660
void RotateVecIntoVec(RwV3d* vectorsOut, RwV3d* vectorsIn, RwV3d* dir) {
    ((void(__cdecl*)(RwV3d*, RwV3d*, RwV3d*))0x4A1660)(vectorsOut, vectorsIn, dir);
}

// 0x4A1780
void RotateVecAboutVec(RwV3d* out, RwV3d* arg1, RwV3d* arg2, float angle) {
    ((void(__cdecl*)(RwV3d*, RwV3d*, RwV3d*, float))0x4A1780)(out, arg1, arg2, angle);
}