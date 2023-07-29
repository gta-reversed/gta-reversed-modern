/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

#include "Fx.h"

#include "rwcore.h" // RxObjSpace3dVertex

static RxObjSpace3DVertex (&TempVertexBuffer)[4] = *(RxObjSpace3DVertex (*)[4])0xC4D958;

Fx_c& g_fx = *(Fx_c*)0xA9AE00;

void Fx_c::InjectHooks() {
    RH_ScopedClass(Fx_c);
    RH_ScopedCategory("Fx");

    RH_ScopedInstall(Constructor, 0x49E620, { .reversed = false });
    RH_ScopedInstall(Destructor, 0x49E630, { .reversed = false });
    RH_ScopedInstall(InitStaticSystems, 0x49E660);
    RH_ScopedInstall(ExitStaticSystems, 0x49E850);
    RH_ScopedInstall(InitEntitySystems, 0x49EA60);
    RH_ScopedInstall(ExitEntitySystems, 0x4A12D0, { .reversed = false });
    RH_ScopedInstall(Init, 0x49EA90);
    RH_ScopedInstall(Exit, 0x4A1320);
    RH_ScopedInstall(Reset, 0x49EAE0);
    RH_ScopedInstall(CreateEntityFx, 0x4A11E0, { .reversed = false });
    RH_ScopedInstall(DestroyEntityFx, 0x4A1280, { .reversed = false });
    RH_ScopedInstall(Update, 0x49E640, { .reversed = false });
    RH_ScopedInstall(Render, 0x49E650);
    RH_ScopedInstall(CreateMatFromVec, 0x49E950, { .reversed = false });
    RH_ScopedInstall(SetFxQuality, 0x49EA40);
    RH_ScopedInstall(GetFxQuality, 0x49EA50);
    RH_ScopedInstall(AddBlood, 0x49EB00, { .reversed = false });
    RH_ScopedInstall(AddWood, 0x49EE10, { .reversed = false });
    RH_ScopedInstall(AddSparks, 0x49F040, { .reversed = false });
    RH_ScopedInstall(AddTyreBurst, 0x49F300, { .reversed = false });
    RH_ScopedInstall(AddBulletImpact, 0x49F3D0, { .reversed = false });
    RH_ScopedInstall(AddPunchImpact, 0x49F670, { .reversed = false });
    RH_ScopedInstall(AddDebris, 0x49F750, { .reversed = false });
    RH_ScopedInstall(AddGlass, 0x49F970, { .reversed = false });
    RH_ScopedInstall(AddWheelSpray, 0x49FB30, { .reversed = false });
    RH_ScopedInstall(AddWheelGrass, 0x49FF20, { .reversed = false });
    RH_ScopedInstall(AddWheelGravel, 0x4A0170, { .reversed = false });
    RH_ScopedInstall(AddWheelMud, 0x4A03C0, { .reversed = false });
    RH_ScopedInstall(AddWheelSand, 0x4A0610, { .reversed = false });
    RH_ScopedInstall(AddWheelDust, 0x4A09C0, { .reversed = false });
    RH_ScopedInstall(TriggerWaterHydrant, 0x4A0D70, { .reversed = false });
    RH_ScopedInstall(TriggerGunshot, 0x4A0DE0, { .reversed = false });
    RH_ScopedInstall(TriggerTankFire, 0x4A0FA0, { .reversed = false });
    RH_ScopedInstall(TriggerWaterSplash, 0x4A1070, { .reversed = false });
    RH_ScopedInstall(TriggerBulletSplash, 0x4A10E0, { .reversed = false });
    RH_ScopedInstall(TriggerFootSplash, 0x4A1150, { .reversed = false });

    RH_ScopedGlobalInstall(RenderAddTri_, 0x4A1410);
    RH_ScopedGlobalInstall(RenderEnd, 0x4A1600);
    RH_ScopedGlobalInstall(RenderBegin, 0x4A13B0);
}

Fx_c* Fx_c::Constructor() {
    this->Fx_c::Fx_c();
    return this;
}

Fx_c* Fx_c::Destructor() {
    this->Fx_c::~Fx_c();
    return this;
}

// 0x49E660
void Fx_c::InitStaticSystems() {
    CVector point;
    m_Blood          = g_fxMan.CreateFxSystem("prt_blood",            &point, nullptr, true);
    m_BoatSplash     = g_fxMan.CreateFxSystem("prt_boatsplash",       &point, nullptr, true);
    m_Bubble         = g_fxMan.CreateFxSystem("prt_bubble",           &point, nullptr, true);
    m_Cardebris      = g_fxMan.CreateFxSystem("prt_cardebris",        &point, nullptr, true);
    m_CollisionSmoke = g_fxMan.CreateFxSystem("prt_collisionsmoke",   &point, nullptr, true);
    m_GunShell       = g_fxMan.CreateFxSystem("prt_gunshell",         &point, nullptr, true);
    m_Sand           = g_fxMan.CreateFxSystem("prt_sand",             &point, nullptr, true);
    m_Sand2          = g_fxMan.CreateFxSystem("prt_sand2",            &point, nullptr, true);
    m_SmokeHuge      = g_fxMan.CreateFxSystem("prt_smoke_huge",       &point, nullptr, true);
    m_SmokeII3expand = g_fxMan.CreateFxSystem("prt_smokeII_3_expand", &point, nullptr, true);
    m_Spark          = g_fxMan.CreateFxSystem("prt_spark",            &point, nullptr, true);
    m_Spark2         = g_fxMan.CreateFxSystem("prt_spark_2",          &point, nullptr, true);
    m_Splash         = g_fxMan.CreateFxSystem("prt_splash",           &point, nullptr, true);
    m_Wake           = g_fxMan.CreateFxSystem("prt_wake",             &point, nullptr, true);
    m_WaterSplash    = g_fxMan.CreateFxSystem("prt_watersplash",      &point, nullptr, true);
    m_WheelDirt      = g_fxMan.CreateFxSystem("prt_wheeldirt",        &point, nullptr, true);
    m_Glass          = g_fxMan.CreateFxSystem("prt_glass",            &point, nullptr, true);
}

// 0x49E850
void Fx_c::ExitStaticSystems() {
    g_fxMan.DestroyFxSystem(m_Blood);
    g_fxMan.DestroyFxSystem(m_BoatSplash);
    g_fxMan.DestroyFxSystem(m_Bubble);
    g_fxMan.DestroyFxSystem(m_Cardebris);
    g_fxMan.DestroyFxSystem(m_CollisionSmoke);
    g_fxMan.DestroyFxSystem(m_GunShell);
    g_fxMan.DestroyFxSystem(m_Sand);
    g_fxMan.DestroyFxSystem(m_Sand2);
    g_fxMan.DestroyFxSystem(m_SmokeHuge);
    g_fxMan.DestroyFxSystem(m_SmokeII3expand);
    g_fxMan.DestroyFxSystem(m_Spark);
    g_fxMan.DestroyFxSystem(m_Spark2);
    g_fxMan.DestroyFxSystem(m_Splash);
    g_fxMan.DestroyFxSystem(m_Wake);
    g_fxMan.DestroyFxSystem(m_WaterSplash);
    g_fxMan.DestroyFxSystem(m_WheelDirt);
    g_fxMan.DestroyFxSystem(m_Glass);
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
    ZoneScoped;

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
void Fx_c::CreateEntityFx(CEntity* entity, char* fxName, CVector* posn, RwMatrix* transform) {
    ((void(__thiscall*)(Fx_c*, CEntity*, char*, CVector*, RwMatrix*))0x4A11E0)(this, entity, fxName, posn, transform);
}

// 0x4A1280
void Fx_c::DestroyEntityFx(CEntity* entity) {
    ((void(__thiscall*)(Fx_c*, CEntity*))0x4A1280)(this, entity);
}

// 0x49E640
void Fx_c::Update(RwCamera* camera, float timeDelta) {
    ZoneScoped;

    ((void(__thiscall*)(Fx_c*, RwCamera*, float))0x49E640)(this, camera, timeDelta);
}

// 0x49E650
void Fx_c::Render(RwCamera* camera, bool heatHaze) {
    ZoneScoped;

    g_fxMan.Render(camera, heatHaze);
}

// 0x49E950
void Fx_c::CreateMatFromVec(RwMatrix* out, CVector* origin, CVector* direction) {
    ((void(__thiscall*)(Fx_c*, RwMatrix*, CVector*, CVector*))0x49E950)(this, out, origin, direction);
}

// 0x49EA40
void Fx_c::SetFxQuality(FxQuality_e quality) {
    m_FxQuality = quality;
}

// 0x49EA50
FxQuality_e Fx_c::GetFxQuality() const {
    return m_FxQuality;
}

// 0x49EB00
void Fx_c::AddBlood(Const CVector& origin, Const CVector& direction, int32 amount, float arg3) {
    ((void(__thiscall*)(Fx_c*, Const CVector&, Const CVector&, int32, float))0x49EB00)(this, origin, direction, amount, arg3);
}

// 0x49EE10
void Fx_c::AddWood(CVector& origin, CVector& direction, int32 amount, float arg3) {
    ((void(__thiscall*)(Fx_c*, CVector&, CVector&, int32, float))0x49EE10)(this, origin, direction, amount, arg3);
}

// 0x49F040
void Fx_c::AddSparks(Const CVector& origin, Const CVector& direction, float force, int32 amount, CVector across, eSparkType sparksType, float spread, float life) {
    ((void(__thiscall*)(Fx_c*, Const CVector&, Const CVector&, float, int32, CVector, uint8, float, float))0x49F040)(this, origin, direction, force, amount, across, sparksType, spread, life);
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
void Fx_c::TriggerGunshot(CEntity* entity, const CVector& origin, const CVector& direction, bool doGunflash) {
    ((void(__thiscall*)(Fx_c*, CEntity*, const CVector&, const CVector&, bool))0x4A0DE0)(this, entity, origin, direction, doGunflash);
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

// see RwIm3DTransformFlags
// 0x4A13B0
void RenderBegin(RwRaster* newRaster, RwMatrix* transform, uint32 transformRenderFlags) {
    g_fx.m_pTransformLTM = transform;
    g_fx.m_nVerticesCount = 0;
    g_fx.m_nVerticesCount2 = 0;
    g_fx.m_pRasterToRender = newRaster;
    g_fx.m_nTransformRenderFlags = transformRenderFlags;
    g_fx.m_pVerts = aTempBufferVertices;

    // And maybe update raster on RW if the same isnt already set...
    RwRaster* currRaster{};
    RwRenderStateGet(rwRENDERSTATETEXTURERASTER, &currRaster);
    if (currRaster != newRaster)
        RwRenderStateSet(rwRENDERSTATETEXTURERASTER, RWRSTATE(newRaster));
}

// Wrapper for original func
// 0x4A1410
void RenderAddTri_(
    float x1, float y1, float z1,
    float x2, float y2, float z2,
    float x3, float y3, float z3,
    float u1, float v1,
    float u2, float v2,
    float u3, float v3,
    int32 r1, int32 g1, int32 b1, int32 a1,
    int32 r2, int32 g2, int32 b2, int32 a2,
    int32 r3, int32 g3, int32 b3, int32 a3
) {
    RenderAddTri(
        { x1, y1, z1 },
        { x2, y2, z2 },
        { x3, y3, z3 },
        { u1, v1 },
        { u2, v2 },
        { u3, v3 },
        CRGBA().FromInt32(r1, g1, b1, a1),
        CRGBA().FromInt32(r2, g2, b2, a2),
        CRGBA().FromInt32(r3, g3, b3, a3)
    );
}

// TODO: I honestly think this should be a class method...
// Although originally it wasnt.
// NOTE: Method signature changed to use CVector + RwTexCoords instead of raw values for convenience.
void RenderAddTri(CVector pos1, CVector pos2, CVector pos3, RwTexCoords coord1, RwTexCoords coord2, RwTexCoords coord3, const CRGBA& color1, const CRGBA& color2, const CRGBA& color3) {
    const auto GetVertex = [](unsigned i) {
        return &g_fx.m_pVerts[i];
    };

    const CVector pos[] = { pos1, pos2, pos3 };
    const RwRGBA color[] = {
        { color1.ToRwRGBA() },
        { color2.ToRwRGBA() },
        { color3.ToRwRGBA() },
    };
    for (unsigned i = 0; i < 3; i++) {
        RxObjSpace3DVertexSetPos(GetVertex(i), &pos[i]);
        RxObjSpace3DVertexSetPreLitColor(GetVertex(i), &color[i]);
    }

    if (g_fx.m_pRasterToRender) {
        const RwTexCoords uvs[] = { coord1, coord2, coord3 };
        for (unsigned i = 0; i < 3; i++) {
            RxObjSpace3DVertexSetU(GetVertex(i), uvs[i].u);
            RxObjSpace3DVertexSetV(GetVertex(i), uvs[i].v);
        }
    }

    g_fx.m_pVerts += 3;
    g_fx.m_nVerticesCount2 += 3;
    g_fx.m_nVerticesCount++;

    if (g_fx.m_nVerticesCount2 >= TOTAL_TEMP_BUFFER_VERTICES - 3 || g_fx.m_nVerticesCount >= TOTAL_TEMP_BUFFER_INDICES - 1) {
        RenderEnd(); // Render vertices to free up vertex buffer
    }
}

// 0x4A1600
void RenderEnd() {
    if (!g_fx.m_nVerticesCount)
        return;

    if (RwIm3DTransform(aTempBufferVertices, 3 * g_fx.m_nVerticesCount, g_fx.m_pTransformLTM, g_fx.m_nTransformRenderFlags)) {
        RwIm3DRenderPrimitive(rwPRIMTYPETRILIST);
        RwIm3DEnd();
    }

    g_fx.m_pVerts = aTempBufferVertices;
    g_fx.m_nVerticesCount2 = 0;
    g_fx.m_nVerticesCount = 0;
}

// 0x4A1660
void RotateVecIntoVec(RwV3d* vectorsOut, RwV3d* vectorsIn, RwV3d* dir) {
    ((void(__cdecl*)(RwV3d*, RwV3d*, RwV3d*))0x4A1660)(vectorsOut, vectorsIn, dir);
}

// 0x4A1780
void RotateVecAboutVec(RwV3d* out, RwV3d* arg1, RwV3d* arg2, float angle) {
    ((void(__cdecl*)(RwV3d*, RwV3d*, RwV3d*, float))0x4A1780)(out, arg1, arg2, angle);
}

