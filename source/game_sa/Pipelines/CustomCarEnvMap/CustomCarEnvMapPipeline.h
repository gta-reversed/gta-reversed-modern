/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "RenderWare.h"
#include "Pool.h"
#include "Object.h"

constexpr auto ENV_MAP_PLUGIN_ID = 0x253F2FC;
constexpr auto ENV_MAP_ATM_PLUGIN_ID = 0x253F2F4;
constexpr auto SPECULAR_MAP_PLUGIN_ID = 0x253F2F6;
constexpr auto CUSTOM_CAR_ENV_MAP_PIPELINE_PLUGIN_ID = 0x53F2009A;

struct ReflectionMaterialStream {
    float scaleX;
    float scaleY;
    float transSclX;
    float transSclY;
    float shininess;
    RwTexture* texture;
};

struct CustomEnvMapPipeMaterialData {
    uint8 scaleX;
    uint8 scaleY;
    uint8 transSclX;
    uint8 transSclY;

    uint8 shininess;
    int16 renderFrameCounter;
    RwTexture* texture;

    void FromStream(const ReflectionMaterialStream& stream) { // 0x5D8BE0
        scaleX    = (uint8)(stream.scaleX * 8.0f);
        scaleY    = (uint8)(stream.scaleY * 8.0f);
        transSclX = (uint8)(stream.transSclX * 8.0f);
        transSclY = (uint8)(stream.transSclY * 8.0f);
        shininess = (uint8)(stream.shininess * 255.0f);
        texture   = stream.texture;
        renderFrameCounter = 0;
    };
};
VALIDATE_SIZE(CustomEnvMapPipeMaterialData, 0xC);

struct CustomEnvMapPipeAtomicData {
    float lastTrans;
    float posx;
    float posy;
};
VALIDATE_SIZE(CustomEnvMapPipeAtomicData, 0xC);

struct SpecMatBuffer {
    float specularity;
    char name[24];
};

struct CustomSpecMapPipeMaterialData {
    float specularity;
    RwTexture* texture;
};
VALIDATE_SIZE(CustomSpecMapPipeMaterialData, 0x8);

typedef CPool<CustomEnvMapPipeMaterialData, CustomEnvMapPipeMaterialData, true>  CustomEnvMapPipeMaterialDataPool;
typedef CPool<CustomEnvMapPipeAtomicData, CustomEnvMapPipeAtomicData, true>    CustomEnvMapPipeAtomicDataPool;
typedef CPool<CustomSpecMapPipeMaterialData, CustomSpecMapPipeMaterialData, true> CustomSpecMapPipeMaterialDataPool;

class CCustomCarEnvMapPipeline {
public:
    static inline int32& ms_envMapPluginOffset = *(int32*)0x8D12C4;      // -1
    static inline int32& ms_envMapAtmPluginOffset = *(int32*)0x8D12C8;   // -1
    static inline int32& ms_specularMapPluginOffset = *(int32*)0x8D12CC; // -1

    static inline RxPipeline*& ObjPipeline = *(RxPipeline**)0xC02D24;

    static inline CustomEnvMapPipeMaterialData& fakeEnvMapPipeMatData = *(CustomEnvMapPipeMaterialData*)0xC02D18;
    static inline CustomEnvMapPipeMaterialDataPool*& m_gEnvMapPipeMatDataPool = *(CustomEnvMapPipeMaterialDataPool**)0xC02D28;
    static inline CustomEnvMapPipeAtomicDataPool*& m_gEnvMapPipeAtmDataPool = *(CustomEnvMapPipeAtomicDataPool**)0xC02D2C;
    static inline CustomSpecMapPipeMaterialDataPool*& m_gSpecMapPipeMatDataPool = *(CustomSpecMapPipeMaterialDataPool**)0xC02D30;

    static inline D3DLIGHT9& g_GameLight = *(D3DLIGHT9*)0xC02CB0;

public:
    static void InjectHooks();

    static bool RegisterPlugin();

    static bool CreatePipe();
    static void DestroyPipe();
    static RxPipeline* CreateCustomObjPipe();
    static void CustomPipeRenderCB(RwResEntry* repEntry, void* object, uint8 type, uint32 flags);
    static RwBool CustomPipeInstanceCB(void* object, RwResEntry* resEntry, RxD3D9AllInOneInstanceCallBack instanceCallback);

    static RpMaterial* CustomPipeMaterialSetup(RpMaterial* material, void* data);
    static RpAtomic* CustomPipeAtomicSetup(RpAtomic* atomic);

    static void PreRenderUpdate();
    static CustomEnvMapPipeMaterialData* DuplicateCustomEnvMapPipeMaterialData(CustomEnvMapPipeMaterialData** data);

    static void AllocEnvMapPipeAtomicData(RpAtomic* atomic);
    static void SetCustomEnvMapPipeAtomicDataDefaults(CustomEnvMapPipeAtomicData* data);
    static void SetCustomEnvMapPipeMaterialDataDefaults(CustomEnvMapPipeMaterialData* data);

    // Env Mat
    static void* pluginEnvMatConstructorCB(void* object, int32 offsetInObject, int32 sizeInObject);
    static void* pluginEnvMatDestructorCB(void* object, int32 offsetInObject, int32 sizeInObject);
    static void* pluginEnvMatCopyConstructorCB(void* dstObject, const void* srcObject, int32 offsetInObject, int32 sizeInObject);
    static RwStream* pluginEnvMatStreamReadCB(RwStream* stream, int32 binaryLength, void* object, int32 offsetInObject, int32 sizeInObject);
    static RwStream* pluginEnvMatStreamWriteCB(RwStream* stream, int32 binaryLength, const void* object, int32 offsetInObject, int32 sizeInObject);
    static int32 pluginEnvMatStreamGetSizeCB(const void* object, int32 offsetInObject, int32 sizeInObject);

    static float GetFxEnvScaleX(RpMaterial* material);
    static float GetFxEnvScaleY(RpMaterial* material);
    static void SetFxEnvScale(RpMaterial* material, float x, float y);

    static float GetFxEnvTransSclX(RpMaterial* material);
    static float GetFxEnvTransSclY(RpMaterial* material);
    static void SetFxEnvTransScl(RpMaterial* material, float x, float y);

    static float GetFxEnvShininess(RpMaterial* material);
    static void SetFxEnvShininess(RpMaterial* material, float value);

    static RwTexture* GetFxEnvTexture(RpMaterial* material);
    static void SetFxEnvTexture(RpMaterial* material, RwTexture* texture);

    // Env Atm
    static void* pluginEnvAtmConstructorCB(void* object, int32 offsetInObject, int32 sizeInObject);
    static void* pluginEnvAtmDestructorCB(void* object, int32 offsetInObject, int32 sizeInObject);
    static void* pluginEnvAtmCopyConstructorCB(void* dstObject, const void* srcObject, int32 offsetInObject, int32 sizeInObject);

    // Spec Mat
    static void* pluginSpecMatConstructorCB(void* object, int32 offsetInObject, int32 sizeInObject);
    static void* pluginSpecMatDestructorCB(void* object, int32 offsetInObject, int32 sizeInObject);
    static void* pluginSpecMatCopyConstructorCB(void* dstObject, const void* srcObject, int32 offsetInObject, int32 sizeInObject);
    static RwStream* pluginSpecMatStreamReadCB(RwStream* stream, int32 binaryLength, void* object, int32 offsetInObject, int32 sizeInObject);
    static RwStream* pluginSpecMatStreamWriteCB(RwStream* stream, int32 binaryLength, const void* object, int32 offsetInObject, int32 sizeInObject);
    static int32 pluginSpecMatStreamGetSizeCB(const void* object, int32 offsetInObject, int32 sizeInObject);

    static float GetFxSpecSpecularity(RpMaterial* material);
    static RwTexture* GetFxSpecTexture(RpMaterial* material);
    static void SetFxSpecTexture(RpMaterial* material, RwTexture* texture);
    static void SetFxSpecSpecularity(RpMaterial* material, float value);
};
