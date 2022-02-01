/*
    Plugin-SDK (Grand Theft Auto San Andreas) file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "RenderWare.h"
#include "FxManager_c.h"

enum FxQuality_e : uint32 {
    FXQUALITY_LOW,
    FXQUALITY_MEDIUM,
    FXQUALITY_HIGH,
    FXQUALITY_VERY_HIGH
};

enum eSparkType : uint8 {
    SPARK_PARTICLE_SPARK2 = 0,
    SPARK_PARTICLE_SPARK  = 1
};

class CVehicle;

class Fx_c {
public:
    FxSystem_c*         m_pPrtBlood;
    FxSystem_c*         m_pPrtBoatsplash;
    FxSystem_c*         m_pPrtBubble;
    FxSystem_c*         m_pPrtCardebris;
    FxSystem_c*         m_pPrtCollisionsmoke;
    FxSystem_c*         m_pPrtGunshell;
    FxSystem_c*         m_pPrtSand;
    FxSystem_c*         m_pPrtSand2;
    FxSystem_c*         m_pPrtSmoke_huge;
    FxSystem_c*         m_pPrtSmokeII3expand;
    FxSystem_c*         m_pPrtSpark;
    FxSystem_c*         m_pPrtSpark2;
    FxSystem_c*         m_pPrtSplash;
    FxSystem_c*         m_pPrtWake;
    FxSystem_c*         m_pPrtWatersplash;
    FxSystem_c*         m_pPrtWheeldirt;
    FxSystem_c*         m_pPrtGlass;
    TList_c<ListItem_c> m_entityFxList;
    uint32_t            m_nBloodPoolsCount;
    FxQuality_e         m_fxQuality;
    uint32_t            m_nVerticesCount2;
    uint32_t            m_nVerticesCount;
    uint32_t            m_nTransformRenderFlags;
    RwRaster*           m_pRasterToRender;
    RwMatrix*           m_pTransformLTM;
    RxObjSpace3DVertex* m_pVerts;

public:
    static void InjectHooks();

    Fx_c();
    Fx_c* Constructor();

    ~Fx_c();
    Fx_c* Destructor();

    void InitStaticSystems();
    void ExitStaticSystems();

    void InitEntitySystems();
    void ExitEntitySystems();

    void Init();
    void Exit();
    void Reset();

    void CreateEntityFx(CEntity* entity, char* fxName, RwV3d* posn, RwMatrix* transform);
    void DestroyEntityFx(CEntity* entity);

    void Update(RwCamera* camera, float timeDelta);
    void Render(RwCamera* camera, bool heatHaze);
    void CreateMatFromVec(RwMatrix* out, CVector* origin, CVector* direction);
    void SetFxQuality(FxQuality_e quality);
    FxQuality_e GetFxQuality() const;

    void AddBlood(CVector& origin, CVector& direction, int32 amount, float arg3);
    void AddWood(CVector& origin, CVector& direction, int32 amount, float arg3);
    void AddSparks(CVector& origin, CVector& direction, float force, int32 amount, CVector across, eSparkType sparksType, float spread, float life);
    void AddTyreBurst(CVector& posn, CVector& velocity);
    void AddBulletImpact(CVector& posn, CVector& direction, int32 bulletFxType, int32 amount, float arg4);
    void AddPunchImpact(CVector& posn, CVector& velocity, int32 arg2);
    void AddDebris(CVector& posn, RwRGBA& color, float scale, int32 amount);
    void AddGlass(CVector& posn, RwRGBA& color, float scale, int32 amount);
    void AddWheelSpray(CVehicle* vehicle, CVector posn, uint8 arg2, uint8 arg3, float arg4);
    void AddWheelGrass(CVehicle* vehicle, CVector posn, uint8 arg2, float arg3);
    void AddWheelGravel(CVehicle* vehicle, CVector posn, uint8 arg2, float arg3);
    void AddWheelMud(CVehicle* vehicle, CVector posn, uint8 arg2, float arg3);
    void AddWheelSand(CVehicle* vehicle, CVector posn, uint8 arg2, float arg3);
    void AddWheelDust(CVehicle* vehicle, CVector posn, uint8 arg2, float arg3);
    void TriggerWaterHydrant(CVector& posn);
    void TriggerGunshot(CEntity* entity, CVector& origin, CVector& target, bool doGunflash);
    void TriggerTankFire(CVector& origin, CVector& target);
    void TriggerWaterSplash(CVector& posn);
    void TriggerBulletSplash(CVector& posn);
    void TriggerFootSplash(CVector& posn);
};

VALIDATE_SIZE(Fx_c, 0x70);

void RenderBegin(RwRaster* raster, RwMatrix* transform, uint32 transformRenderFlags);
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
);

void RenderAddTri(
    CVector pos1, CVector pos2, CVector pos3,
    RwTexCoords coord1, RwTexCoords coord2, RwTexCoords coord3,
    const CRGBA& color1, const CRGBA& color2, const CRGBA& color3
);
void RenderEnd();
void RotateVecIntoVec(RwV3d* vectorsOut, RwV3d* vectorsIn, RwV3d* dir);
void RotateVecAboutVec(RwV3d* out, RwV3d* arg1, RwV3d* arg2, float angle);

extern Fx_c& g_fx;
