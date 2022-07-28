#pragma once

#include "RenderWare.h"

struct RxOpenGLMeshInstanceData;

constexpr auto EXTRA_VERTCOLOUR_PLUGIN_ID = 0x253F2F9;
constexpr auto CUSTOM_BUILDING_DN_PIPELINE_ID = 0x0;

class CCustomBuildingDNPipeline {
public:
    static inline float& m_fDNBalanceParam = *(float*)0x8D12C0; // 1.0f
    static inline uint32& ms_extraVertColourPluginOffset = *(uint32*)0x8D12BC; // -1
    static inline RxPipeline*& ObjPipeline = *(RxPipeline**)0xC02C1C;
    static bool& m_bCameraChange;
    static uint32& m_AtmDNWorkingIndex;

public:
    static void InjectHooks();

    static bool ExtraVertColourPluginAttach();

    static bool CreatePipe();
    static RxPipeline* CreateCustomObjPipe();
    static void DestroyPipe();

    static RpAtomic* CustomPipeAtomicSetup(RpAtomic* atomic);
    static uint32 UsesThisPipeline(RpAtomic* atomic);
    static RwBool CustomPipeInstanceCB(void* object, RwResEntry* resEntry, RxD3D9AllInOneInstanceCallBack instanceCallback);
    static void PreRenderUpdate(RpAtomic* atomic, bool ignoreDNBalanceParam);
    static RpAtomic* PreRenderUpdateRpAtomicCB(RpAtomic* atomic, void* data);

    static void* pluginExtraVertColourConstructorCB(void* object, int32 offsetInObject, int32 sizeInObject);
    static void* pluginExtraVertColourDestructorCB(void* object, int32 offsetInObject, int32 sizeInObject);
    static RwStream* pluginExtraVertColourStreamReadCB(RwStream* stream, int32 binaryLength, void* object, int32 offsetInObject, int32 sizeInObject);
    static RwStream* pluginExtraVertColourStreamWriteCB(RwStream* stream, int32 binaryLength, const void* object, int32 offsetInObject, int32 sizeInObject);
    static int32 pluginExtraVertColourStreamGetSizeCB(const void* object, int32 offsetInObject, int32 sizeInObject);

    static RpMaterial* CustomPipeMaterialSetup(RpMaterial* material, void* a2);
    static void CustomPipeRenderCB(RwResEntry* entry, void* object, uint8 type, uint32 flags);

    static void* GetExtraVertColourPtr(RpGeometry* geometry);

    static RwTexture* GetFxEnvTexture(RpMaterial* material);
    static void SetFxEnvTexture(RpMaterial* material, RwTexture* texture);

    static float GetFxEnvScaleX(RpMaterial* material);
    static float GetFxEnvScaleY(RpMaterial* material);
    static void SetFxEnvScale(RpMaterial* material, float x, float y);

    static float GetFxEnvTransSclX(RpMaterial* material);
    static float GetFxEnvTransSclY(RpMaterial* material);
    static void SetFxEnvTransScl(RpMaterial* material, float x, float y);

    static float GetFxEnvShininess(RpMaterial* material);
    static void SetFxEnvShininess(RpMaterial* material, float value);
};
