/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

#include "Fx_c.h"

#include "rwcore.h" // RxObjSpace3dVertex

static RxObjSpace3DVertex (&TempVertexBuffer)[4] = *(RxObjSpace3DVertex (*)[4])0xC4D958;

Fx_c& g_fx = *(Fx_c*)0xA9AE00;

void Fx_c::InjectHooks() {
    using namespace ReversibleHooks;
    // Install("Fx_c", "Fx_c", 0x49E620, &Fx_c::Constructor);
    // Install("Fx_c", "~Fx_c", 0x49E630, &Fx_c::Destructor);
    Install("Fx_c", "InitStaticSystems", 0x49E660, &Fx_c::InitStaticSystems);
    Install("Fx_c", "ExitStaticSystems", 0x49E850, &Fx_c::ExitStaticSystems);
    Install("Fx_c", "InitEntitySystems", 0x49EA60, &Fx_c::InitEntitySystems);
    // Install("Fx_c", "ExitEntitySystems", 0x4A12D0, &Fx_c::ExitEntitySystems);
    Install("Fx_c", "Init", 0x49EA90, &Fx_c::Init);
    Install("Fx_c", "Exit", 0x4A1320, &Fx_c::Exit);
    Install("Fx_c", "Reset", 0x49EAE0, &Fx_c::Reset);
    // Install("Fx_c", "CreateEntityFx", 0x4A11E0, &Fx_c::CreateEntityFx);
    // Install("Fx_c", "DestroyEntityFx", 0x4A1280, &Fx_c::DestroyEntityFx);
    // Install("Fx_c", "Update", 0x49E640, &Fx_c::Update);
    Install("Fx_c", "Render", 0x49E650, &Fx_c::Render);
    // Install("Fx_c", "CreateMatFromVec", 0x49E950, &Fx_c::CreateMatFromVec);
    Install("Fx_c", "SetFxQuality", 0x49EA40, &Fx_c::SetFxQuality);
    Install("Fx_c", "GetFxQuality", 0x49EA50, &Fx_c::GetFxQuality);
    // Install("Fx_c", "AddBlood", 0x49EB00, &Fx_c::AddBlood);
    // Install("Fx_c", "AddWood", 0x49EE10, &Fx_c::AddWood);
    // Install("Fx_c", "AddSparks", 0x49F040, &Fx_c::AddSparks);
    // Install("Fx_c", "AddTyreBurst", 0x49F300, &Fx_c::AddTyreBurst);
    // Install("Fx_c", "AddBulletImpact", 0x49F3D0, &Fx_c::AddBulletImpact);
    // Install("Fx_c", "AddPunchImpact", 0x49F670, &Fx_c::AddPunchImpact);
    // Install("Fx_c", "AddDebris", 0x49F750, &Fx_c::AddDebris);
    // Install("Fx_c", "AddGlass", 0x49F970, &Fx_c::AddGlass);
    // Install("Fx_c", "AddWheelSpray", 0x49FB30, &Fx_c::AddWheelSpray);
    // Install("Fx_c", "AddWheelGrass", 0x49FF20, &Fx_c::AddWheelGrass);
    // Install("Fx_c", "AddWheelGravel", 0x4A0170, &Fx_c::AddWheelGravel);
    // Install("Fx_c", "AddWheelMud", 0x4A03C0, &Fx_c::AddWheelMud);
    // Install("Fx_c", "AddWheelSand", 0x4A0610, &Fx_c::AddWheelSand);
    // Install("Fx_c", "AddWheelDust", 0x4A09C0, &Fx_c::AddWheelDust);
    // Install("Fx_c", "TriggerWaterHydrant", 0x4A0D70, &Fx_c::TriggerWaterHydrant);
    // Install("Fx_c", "TriggerGunshot", 0x4A0DE0, &Fx_c::TriggerGunshot);
    // Install("Fx_c", "TriggerTankFire", 0x4A0FA0, &Fx_c::TriggerTankFire);
    // Install("Fx_c", "TriggerWaterSplash", 0x4A1070, &Fx_c::TriggerWaterSplash);
    // Install("Fx_c", "TriggerBulletSplash", 0x4A10E0, &Fx_c::TriggerBulletSplash);
    // Install("Fx_c", "TriggerFootSplash", 0x4A1150, &Fx_c::TriggerFootSplash);
}

// 0x49E620
Fx_c::Fx_c() {
    ((void(__thiscall*)(Fx_c*))0x49E620)(this);
}

// 0x49E630
Fx_c::~Fx_c() {
    ((void(__thiscall*)(Fx_c*))0x49E630)(this);
}

// 0x49E660
void Fx_c::InitStaticSystems() {
    CVector point;
    m_pPrtBlood          = g_fxMan.CreateFxSystem("prt_blood",            &point, nullptr, true);
    m_pPrtBoatsplash     = g_fxMan.CreateFxSystem("prt_boatsplash",       &point, nullptr, true);
    m_pPrtBubble         = g_fxMan.CreateFxSystem("prt_bubble",           &point, nullptr, true);
    m_pPrtCardebris      = g_fxMan.CreateFxSystem("prt_cardebris",        &point, nullptr, true);
    m_pPrtCollisionsmoke = g_fxMan.CreateFxSystem("prt_collisionsmoke",   &point, nullptr, true);
    m_pPrtGunshell       = g_fxMan.CreateFxSystem("prt_gunshell",         &point, nullptr, true);
    m_pPrtSand           = g_fxMan.CreateFxSystem("prt_sand",             &point, nullptr, true);
    m_pPrtSand2          = g_fxMan.CreateFxSystem("prt_sand2",            &point, nullptr, true);
    m_pPrtSmoke_huge     = g_fxMan.CreateFxSystem("prt_smoke_huge",       &point, nullptr, true);
    m_pPrtSmokeII3expand = g_fxMan.CreateFxSystem("prt_smokeII_3_expand", &point, nullptr, true);
    m_pPrtSpark          = g_fxMan.CreateFxSystem("prt_spark",            &point, nullptr, true);
    m_pPrtSpark2         = g_fxMan.CreateFxSystem("prt_spark_2",          &point, nullptr, true);
    m_pPrtSplash         = g_fxMan.CreateFxSystem("prt_splash",           &point, nullptr, true);
    m_pPrtWake           = g_fxMan.CreateFxSystem("prt_wake",             &point, nullptr, true);
    m_pPrtWatersplash    = g_fxMan.CreateFxSystem("prt_watersplash",      &point, nullptr, true);
    m_pPrtWheeldirt      = g_fxMan.CreateFxSystem("prt_wheeldirt",        &point, nullptr, true);
    m_pPrtGlass          = g_fxMan.CreateFxSystem("prt_glass",            &point, nullptr, true);
}

// 0x49E850
void Fx_c::ExitStaticSystems() {
    g_fxMan.DestroyFxSystem(m_pPrtBlood);
    g_fxMan.DestroyFxSystem(m_pPrtBoatsplash);
    g_fxMan.DestroyFxSystem(m_pPrtBubble);
    g_fxMan.DestroyFxSystem(m_pPrtCardebris);
    g_fxMan.DestroyFxSystem(m_pPrtCollisionsmoke);
    g_fxMan.DestroyFxSystem(m_pPrtGunshell);
    g_fxMan.DestroyFxSystem(m_pPrtSand);
    g_fxMan.DestroyFxSystem(m_pPrtSand2);
    g_fxMan.DestroyFxSystem(m_pPrtSmoke_huge);
    g_fxMan.DestroyFxSystem(m_pPrtSmokeII3expand);
    g_fxMan.DestroyFxSystem(m_pPrtSpark);
    g_fxMan.DestroyFxSystem(m_pPrtSpark2);
    g_fxMan.DestroyFxSystem(m_pPrtSplash);
    g_fxMan.DestroyFxSystem(m_pPrtWake);
    g_fxMan.DestroyFxSystem(m_pPrtWatersplash);
    g_fxMan.DestroyFxSystem(m_pPrtWheeldirt);
    g_fxMan.DestroyFxSystem(m_pPrtGlass);
}

// 0x49EA60
// unused
void Fx_c::InitEntitySystems() {
    // NOP
}

// 0x4A12D0
void Fx_c::ExitEntitySystems() {
    ((void(__thiscall*)(Fx_c*))0x4A12D0)(this);
}

// 0x49EA90
void Fx_c::Init() {
    g_fxMan.Init();
    g_fxMan.LoadFxProject("models\\effects.fxp");
    g_fxMan.SetWindData(&CWeather::WindDir, &CWeather::Wind);
    InitStaticSystems();
    m_nBloodPoolsCount = 0;
}

// 0x4A1320
void Fx_c::Exit() {
    ExitEntitySystems();
    ExitStaticSystems();
    g_fxMan.Exit();
}

// 0x49EAE0
void Fx_c::Reset() {
    g_fxMan.DestroyAllFxSystems();
    InitStaticSystems();
}

// 0x4A11E0
void Fx_c::CreateEntityFx(CEntity* entity, char* fxName, RwV3d* posn, RwMatrix* transform) {
    ((void(__thiscall*)(Fx_c*, CEntity*, char*, RwV3d*, RwMatrix*))0x4A11E0)(this, entity, fxName, posn, transform);
}

// 0x4A1280
void Fx_c::DestroyEntityFx(CEntity* entity) {
    ((void(__thiscall*)(Fx_c*, CEntity*))0x4A1280)(this, entity);
}

// 0x49E640
void Fx_c::Update(RwCamera* camera, float timeDelta) {
    ((void(__thiscall*)(Fx_c*, RwCamera*, float))0x49E640)(this, camera, timeDelta);
}

// 0x49E650
void Fx_c::Render(RwCamera* camera, bool heatHaze) {
    g_fxMan.Render(camera, heatHaze);
}

// 0x49E950
void Fx_c::CreateMatFromVec(RwMatrix* out, CVector* origin, CVector* direction) {
    ((void(__thiscall*)(Fx_c*, RwMatrix*, CVector*, CVector*))0x49E950)(this, out, origin, direction);
}

// 0x49EA40
void Fx_c::SetFxQuality(FxQuality_e quality) {
    m_fxQuality = quality;
}

// 0x49EA50
FxQuality_e Fx_c::GetFxQuality() const {
    return m_fxQuality;
}

// 0x49EB00
void Fx_c::AddBlood(CVector& origin, CVector& direction, int32 amount, float arg3) {
    ((void(__thiscall*)(Fx_c*, CVector&, CVector&, int32, float))0x49EB00)(this, origin, direction, amount, arg3);
}

// 0x49EE10
void Fx_c::AddWood(CVector& origin, CVector& direction, int32 amount, float arg3) {
    ((void(__thiscall*)(Fx_c*, CVector&, CVector&, int32, float))0x49EE10)(this, origin, direction, amount, arg3);
}

// 0x49F040
void Fx_c::AddSparks(CVector& origin, CVector& direction, float force, int32 amount, CVector across, eSparkType sparksType, float spread, float life) {
    ((void(__thiscall*)(Fx_c*, CVector&, CVector&, float, int32, CVector, uint8, float, float))0x49F040)(this, origin, direction, force, amount, across, sparksType, spread, life);
}

// 0x49F300
void Fx_c::AddTyreBurst(CVector& posn, CVector& velocity) {
    ((void(__thiscall*)(Fx_c*, CVector&, CVector&))0x49F300)(this, posn, velocity);
}

// 0x49F3D0
void Fx_c::AddBulletImpact(CVector& posn, CVector& direction, int32 bulletFxType, int32 amount, float arg4) {
    ((void(__thiscall*)(Fx_c*, CVector&, CVector&, int32, int32, float))0x49F3D0)(this, posn, direction, bulletFxType, amount, arg4);
}

// 0x49F670
void Fx_c::AddPunchImpact(CVector& posn, CVector& velocity, int32 arg2) {
    ((void(__thiscall*)(Fx_c*, CVector&, CVector&, int32))0x49F670)(this, posn, velocity, arg2);
}

// 0x49F750
void Fx_c::AddDebris(CVector& posn, RwRGBA& color, float scale, int32 amount) {
    ((void(__thiscall*)(Fx_c*, CVector&, RwRGBA&, float, int32))0x49F750)(this, posn, color, scale, amount);
}

// 0x49F970
void Fx_c::AddGlass(CVector& posn, RwRGBA& color, float scale, int32 amount) {
    ((void(__thiscall*)(Fx_c*, CVector&, RwRGBA&, float, int32))0x49F970)(this, posn, color, scale, amount);
}

// 0x49FB30
void Fx_c::AddWheelSpray(CVehicle* vehicle, CVector posn, uint8 arg2, uint8 arg3, float arg4) {
    ((void(__thiscall*)(Fx_c*, CVehicle*, CVector, uint8, uint8, float))0x49FB30)(this, vehicle, posn, arg2, arg3, arg4);
}

// 0x49FF20
void Fx_c::AddWheelGrass(CVehicle* vehicle, CVector posn, uint8 arg2, float arg3) {
    ((void(__thiscall*)(Fx_c*, CVehicle*, CVector, uint8, float))0x49FF20)(this, vehicle, posn, arg2, arg3);
}

// 0x4A0170
void Fx_c::AddWheelGravel(CVehicle* vehicle, CVector posn, uint8 arg2, float arg3) {
    ((void(__thiscall*)(Fx_c*, CVehicle*, CVector, uint8, float))0x4A0170)(this, vehicle, posn, arg2, arg3);
}

// 0x4A03C0
void Fx_c::AddWheelMud(CVehicle* vehicle, CVector posn, uint8 arg2, float arg3) {
    ((void(__thiscall*)(Fx_c*, CVehicle*, CVector, uint8, float))0x4A03C0)(this, vehicle, posn, arg2, arg3);
}

// 0x4A0610
void Fx_c::AddWheelSand(CVehicle* vehicle, CVector posn, uint8 arg2, float arg3) {
    ((void(__thiscall*)(Fx_c*, CVehicle*, CVector, uint8, float))0x4A0610)(this, vehicle, posn, arg2, arg3);
}

// 0x4A09C0
void Fx_c::AddWheelDust(CVehicle* vehicle, CVector posn, uint8 arg2, float arg3) {
    ((void(__thiscall*)(Fx_c*, CVehicle*, CVector, uint8, float))0x4A09C0)(this, vehicle, posn, arg2, arg3);
}

// 0x4A0D70
void Fx_c::TriggerWaterHydrant(CVector& posn) {
    ((void(__thiscall*)(Fx_c*, CVector&))0x4A0D70)(this, posn);
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
void Fx_c::TriggerWaterSplash(CVector& posn) {
    ((void(__thiscall*)(Fx_c*, CVector&))0x4A1070)(this, posn);
}

// 0x4A10E0
void Fx_c::TriggerBulletSplash(CVector& posn) {
    ((void(__thiscall*)(Fx_c*, CVector&))0x4A10E0)(this, posn);
}

// 0x4A1150
void Fx_c::TriggerFootSplash(CVector& posn) {
    ((void(__thiscall*)(Fx_c*, CVector&))0x4A1150)(this, posn);
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
