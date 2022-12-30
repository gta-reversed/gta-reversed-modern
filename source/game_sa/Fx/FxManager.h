/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "RenderWare.h"
#include "List_c.h"

#include "FxFrustumInfo.h"
#include "FxMemoryPool.h"
#include "FxSystemBP.h"
#include "FxSystem.h"

class FxEmitterPrt_c;

class FxManager_c {
public:
    TList_c<FxSystemBP_c>   m_fxSystemBPs;
    TList_c<FxSystem_c>     m_fxSystems;
    FxEmitterPrt_c*         m_pFxEmitters;
    TList_c<FxEmitterPrt_c> m_fxEmitterParticles;
    int32                     m_nFxTxdIndex;
    RwV3d*                  m_pWindDir;
    float*                  m_pfWindSpeed;
    FxFrustumInfo_c         m_frustum;
    uint32                  m_nCurrentMatrix;
    RwMatrix*               m_apMatrices[8];
    FxMemoryPool_c          m_pool;
    bool                    m_bHeatHazeEnabled;

public:
    static void InjectHooks();

    FxManager_c();
    FxManager_c* Constructor();

    ~FxManager_c();
    FxManager_c* Destructor();

    bool Init();
    void Exit();
    void DestroyFxSystem(FxSystem_c* system);
    void DestroyAllFxSystems();
    void Update(RwCamera* arg0, float timeDelta);

    bool LoadFxProject(const char* filename);
    void UnloadFxProject();

    FxSystemBP_c* LoadFxSystemBP(char* filename, int32 file);
    FxSystemBP_c* FindFxSystemBP(const char* name);

    FxFrustumInfo_c* GetFrustumInfo();
    void CalcFrustumInfo(RwCamera* camera);

    void ReturnParticle(FxEmitterPrt_c* emitter);
    FxEmitterPrt_c* GetParticle(int8 arg0);
    void FreeUpParticle();

    void Render(RwCamera* camera, uint8 arg1);

    void SetWindData(RwV3d* dir, float* speed);

    RwMatrix* FxRwMatrixCreate();
    void FxRwMatrixDestroy(RwMatrix* matrix);

    bool ShouldCreate(FxSystemBP_c* bpSystem, RwMatrix* transform, RwMatrix* objectMatrix, bool ignoreBoundingChecks = false);
    FxSystem_c* CreateFxSystem(FxSystemBP_c* bpSystem, RwMatrix* transform, RwMatrix* objectMatrix, bool ignoreBoundingChecks = false);
    FxSystem_c* CreateFxSystem(const char* name, RwMatrix* transform, RwMatrix* objectMatrix, bool ignoreBoundingChecks = false);
    FxSystem_c* CreateFxSystem(FxSystemBP_c* bpSystem, RwV3d* position, RwMatrix* objectMatrix, bool ignoreBoundingChecks = false);
    FxSystem_c* CreateFxSystem(const char* name, RwV3d* position, RwMatrix* objectMatrix, bool ignoreBoundingChecks = false);
};

VALIDATE_SIZE(FxManager_c, 0xBC);

extern FxManager_c& g_fxMan;
