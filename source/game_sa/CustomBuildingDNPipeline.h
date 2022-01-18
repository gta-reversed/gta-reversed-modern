#pragma once

#include "RenderWare.h"

struct RxOpenGLMeshInstanceData;

class CCustomBuildingDNPipeline {
public:
    static bool& m_bCameraChange;
    static RwUInt32& m_AtmDNWorkingIndex;
    static RxPipeline*& ObjPipeline;
    static RwUInt32& ms_extraVertColourPluginOffset;
    static float& m_fDNBalanceParam;

public:
    static void InjectHooks();

    static void PreRenderUpdate(RpAtomic* atomic, bool ignoreDNBalanceParam);
    static RpAtomic* PreRenderUpdateRpAtomicCB(RpAtomic* atomic, void* data);

    static void pluginExtraVertColourConstructorCB(void*, int32, int32);
    static void pluginExtraVertColourDestructorCB(void*, int32, int32);
    static void pluginExtraVertColourStreamGetSizeCB(const void*, int32, int32);
    static void pluginExtraVertColourStreamReadCB(RwStream* stream, int32, void*, int32, int32);
    static void pluginExtraVertColourStreamWriteCB(RwStream* stream, int32, const void*, int32, int32);

    static void CustomPipeInstanceCB(void*, RxOpenGLMeshInstanceData* data, int32, int32);

    CCustomBuildingDNPipeline();
    ~CCustomBuildingDNPipeline();

    static void DestroyPipe();
    static RpAtomic* CustomPipeAtomicSetup(RpAtomic* atomic);
    static uint32 UsesThisPipeline(RpAtomic* atomic);
    static void CreateCustomObjPipe();
    static bool CreatePipe();

    static bool ExtraVertColourPluginAttach();

    static void* GetExtraVertColourPtr(RpGeometry* geometry);
    static void SetFxEnvTexture(RpMaterial* material, RwTexture* texture);
    static RwTexture* GetFxEnvTexture(RpMaterial* material);
    static void SetFxEnvScale(RpMaterial* material, float scaleX, float scaleY);
    static float GetFxEnvScaleX(RpMaterial* material);
    static float GetFxEnvScaleY(RpMaterial* material);
    static void SetFxEnvTransScl(RpMaterial* material, float scaleX, float scaleY);
    static float GetFxEnvTransSclX(RpMaterial* material);
    static float GetFxEnvTransSclY(RpMaterial* material);
    static void SetFxEnvShininess(RpMaterial* material, float value);
    static float GetFxEnvShininess(RpMaterial* material);
    static void CustomPipeMaterialSetup(RpMaterial* material, void* a2);
    static void CustomPipeRenderCB(RwResEntry* entry, void* object, uint8 type, uint32 flags);
};
