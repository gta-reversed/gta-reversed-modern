/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "RenderWare.h"
#include "List_c.h"
#include "FxFrustumInfo_c.h"
#include "FxMemoryPool_c.h"
#include "FxSystemBP_c.h"
#include "FxSystem_c.h"

class FxEmitterPrt_c;

class FxManager_c {
public:
	TList_c<FxSystemBP_c>   m_fxSystemBPList;
	TList_c<FxSystem_c>     m_fxSystemList;
	FxEmitterPrt_c *        m_pFxEmitters;
	TList_c<FxEmitterPrt_c> m_fxEmitterPrtList;
	int                     m_nFxTxdIndex;
	RwV3d *                 m_pWindDir;
	float *                 m_pfWindSpeed;
	FxFrustumInfo_c         m_frustum;
	unsigned int            m_nCurrentMatrix;
	RwMatrix *              m_apMatrices[8];
	FxMemoryPool_c          m_pool;

public:
	FxManager_c();
    ~FxManager_c();
    FxFrustumInfo_c* GetFrustumInfo();
    void CalcFrustumInfo(RwCamera* camera);
    void Render(RwCamera* camera, unsigned char arg1);
    FxSystemBP_c* FindFxSystemBP(char* name);
    void ReturnParticle(FxEmitterPrt_c* emitter);
    FxEmitterPrt_c* GetParticle(signed char arg0);
    void SetWindData(RwV3d* dir, float* speed);
    void FreeUpParticle();
    RwMatrix* FxRwMatrixCreate();
    void FxRwMatrixDestroy(RwMatrix* matrix);
    bool ShouldCreate(FxSystemBP_c* bpSystem, RwMatrix* transform, RwMatrix* objectMatrix, unsigned char ignoreBoundingChecks);
    FxSystem_c* CreateFxSystem(FxSystemBP_c* bpSystem, RwMatrix* transform, RwMatrix* objectMatrix, unsigned char ignoreBoundingChecks);
    FxSystem_c* CreateFxSystem(FxSystemBP_c* bpSystem, RwV3d* position, RwMatrix* objectMatrix, unsigned char ignoreBoundingChecks);
    void DestroyFxSystem(FxSystem_c* system);
    void DestroyAllFxSystems();
    bool Init();
    void Exit();
    void Update(RwCamera* arg0, float timeDelta);
    void UnloadFxProject();
    FxSystem_c* CreateFxSystem(char* name, RwMatrix* transform, RwMatrix* objectMatrix, unsigned char ignoreBoundingChecks);
    FxSystem_c* CreateFxSystem(char* name, RwV3d* position, RwMatrix* objectMatrix, unsigned char ignoreBoundingChecks);
    FxSystemBP_c* LoadFxSystemBP(char* filename, int file);
    bool LoadFxProject(char* filename);
};

VALIDATE_SIZE(FxManager_c, 0xB8);

extern  FxManager_c &g_fxMan;
