#include "StdInc.h"

#include "CustomCarEnvMapPipeline.h"
#include "CustomBuildingDNPipeline.h"

// 0x5D8BD0
void* CCustomCarEnvMapPipeline::pluginEnvMatConstructorCB(void* object, int32 offsetInObject, int32 sizeInObject) {
    *RWPLUGINOFFSET(CustomEnvMapPipeMaterialData*, object, offsetInObject) = &fakeEnvMapPipeMatData;
    return object;
}

// 0x5D95B0
void* CCustomCarEnvMapPipeline::pluginEnvMatDestructorCB(void* object, int32 offsetInObject, int32 sizeInObject) {
    auto matData = *RWPLUGINOFFSET(CustomEnvMapPipeMaterialData*, object, offsetInObject);
    if (matData && matData != &fakeEnvMapPipeMatData) {
        m_gEnvMapPipeMatDataPool->Delete(matData);
        *RWPLUGINOFFSET(CustomEnvMapPipeMaterialData*, object, offsetInObject) = nullptr;
    }
    return object;
}

// 0x5D9600
void* CCustomCarEnvMapPipeline::pluginEnvMatCopyConstructorCB(void* dstObject, const void* srcObject, int32 offsetInObject, int32 sizeInObject) {
    auto srcMatData = *RWPLUGINOFFSET(CustomEnvMapPipeMaterialData*, srcObject, offsetInObject);
    auto dstMatData = *RWPLUGINOFFSET(CustomEnvMapPipeMaterialData*, dstObject, offsetInObject);
    if (srcMatData) {
        if (!dstMatData) {
            dstMatData = m_gEnvMapPipeMatDataPool->New();
            *RWPLUGINOFFSET(CustomEnvMapPipeMaterialData*, dstObject, offsetInObject) = dstMatData;
            if (!dstMatData) {
                *RWPLUGINOFFSET(CustomEnvMapPipeMaterialData*, dstObject, offsetInObject) = &fakeEnvMapPipeMatData;
                return dstObject;
            }
        }
        memcpy(dstMatData, srcMatData, sizeInObject);
    }
    return dstObject;
}

// 0x5D9660
RwStream* CCustomCarEnvMapPipeline::pluginEnvMatStreamReadCB(RwStream* stream, int32 binaryLength, void* object, int32 offsetInObject, int32 sizeInObject) {
    return plugin::CallAndReturn<RwStream*, 0x5D9660, RwStream*, int32, void*, int32, int32>(stream, binaryLength, object, offsetInObject, sizeInObject);

    ReflectionMaterialStream buffer{};
    CustomEnvMapPipeMaterialData data{};
    RwStreamRead(stream, &buffer, binaryLength);
    data.FromStream(buffer);
}

// 0x5D8CD0
// unsupported
RwStream* CCustomCarEnvMapPipeline::pluginEnvMatStreamWriteCB(RwStream* stream, int32 binaryLength, const void* object, int32 offsetInObject, int32 sizeInObject) {
    return plugin::CallAndReturn<RwStream*, 0x5D8CD0, RwStream*, int32, const void*, int32, int32>(stream, binaryLength, object, offsetInObject, sizeInObject);
}

// 0x5D8D10
int32 CCustomCarEnvMapPipeline::pluginEnvMatStreamGetSizeCB(const void* object, int32 offsetInObject, int32 sizeInObject) {
    return object ? sizeof(ReflectionMaterialStream) : 0;
}

// 0x5D6F90
float CCustomCarEnvMapPipeline::GetFxEnvScaleX(RpMaterial* material) {
    auto data = *RWPLUGINOFFSET(CustomEnvMapPipeMaterialData*, material, ms_envMapPluginOffset);
    return data ? (float)data->scaleX / 8.0f : 0.0f;
}

// 0x5D6FC0
float CCustomCarEnvMapPipeline::GetFxEnvScaleY(RpMaterial* material) {
    auto data = *RWPLUGINOFFSET(CustomEnvMapPipeMaterialData*, material, ms_envMapPluginOffset);
    return data ? (float)data->scaleY / 8.0f : 0.0f;
}

// 0x5D6F40
void CCustomCarEnvMapPipeline::SetFxEnvScale(RpMaterial* material, float x, float y) {
    auto envData = RWPLUGINOFFSET(CustomEnvMapPipeMaterialData*, material, ms_envMapPluginOffset);
    auto* data = DuplicateCustomEnvMapPipeMaterialData(envData);
    if (data) {
        data->scaleX = (uint8)(x * 8.0f);
        data->scaleY = (uint8)(y * 8.0f);
    }
}

// 0x5D7040
float CCustomCarEnvMapPipeline::GetFxEnvTransSclX(RpMaterial* material) {
    auto data = *RWPLUGINOFFSET(CustomEnvMapPipeMaterialData*, material, ms_envMapPluginOffset);
    return data ? (float)data->transSclX / 8.0f : 0.0f;
}

// 0x5D7070
float CCustomCarEnvMapPipeline::GetFxEnvTransSclY(RpMaterial* material) {
    auto data = *RWPLUGINOFFSET(CustomEnvMapPipeMaterialData*, material, ms_envMapPluginOffset);
    return data ? (float)data->transSclY / 8.0f : 0.0f;
}

// 0x5D6FF0
void CCustomCarEnvMapPipeline::SetFxEnvTransScl(RpMaterial* material, float x, float y) {
    auto envData = RWPLUGINOFFSET(CustomEnvMapPipeMaterialData*, material, ms_envMapPluginOffset);
    auto* data = DuplicateCustomEnvMapPipeMaterialData(envData);
    if (data) {
        data->transSclX = (uint8)(x * 8.0f);
        data->transSclY = (uint8)(y * 8.0f);
    }
}

// 0x5D8AD0
float CCustomCarEnvMapPipeline::GetFxEnvShininess(RpMaterial* material) {
    auto data = *RWPLUGINOFFSET(CustomEnvMapPipeMaterialData*, material, ms_envMapPluginOffset);
    return data ? (float)data->shininess / 255.0f : 0.0f;
}

// 0x5D70A0
void CCustomCarEnvMapPipeline::SetFxEnvShininess(RpMaterial* material, float value) {
    auto envData = RWPLUGINOFFSET(CustomEnvMapPipeMaterialData*, material, ms_envMapPluginOffset);
    auto* data = DuplicateCustomEnvMapPipeMaterialData(envData);
    if (data) {
        data->shininess = (uint8)(value * 255.0f);
    }
}

//
RwTexture* CCustomCarEnvMapPipeline::GetFxEnvTexture(RpMaterial* material) {
    auto data = *RWPLUGINOFFSET(CustomEnvMapPipeMaterialData*, material, ms_envMapPluginOffset);
    return data ? data->texture : nullptr;
}

// 0x5DA230
void CCustomCarEnvMapPipeline::SetFxEnvTexture(RpMaterial* material, RwTexture* texture) {
    plugin::Call<0x5DA230, RpMaterial*, RwTexture*>(material, texture);
}

// 0x5D8BB0
void CCustomCarEnvMapPipeline::SetCustomEnvMapPipeMaterialDataDefaults(CustomEnvMapPipeMaterialData* data) {
    data->scaleX = 8;
    data->scaleY = 8;
    data->transSclX = 8;
    data->transSclY = 8;
    data->shininess = UINT8_MAX;
    data->texture = nullptr;
    data->renderFrameCounter = 0;
}
