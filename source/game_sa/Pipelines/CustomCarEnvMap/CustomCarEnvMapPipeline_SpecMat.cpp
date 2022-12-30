#include "StdInc.h"

#include "CustomCarEnvMapPipeline.h"

// 0x5D8D40
void* CCustomCarEnvMapPipeline::pluginSpecMatConstructorCB(void* object, int32 offsetInObject, int32 sizeInObject) {
    *RWPLUGINOFFSET(CustomSpecMapPipeMaterialData*, object, ms_specularMapPluginOffset) = nullptr;
    return object;
}

// 0x5D97D0
void* CCustomCarEnvMapPipeline::pluginSpecMatDestructorCB(void* object, int32 offsetInObject, int32 sizeInObject) {
    auto* data = *RWPLUGINOFFSET(CustomSpecMapPipeMaterialData*, object, ms_specularMapPluginOffset);
    if (data) {
        if (data->texture) {
            RwTextureDestroy(data->texture);
            data->texture = nullptr;
        }
        m_gSpecMapPipeMatDataPool->Delete(data);
        data = nullptr;
    }
    return object;
}

// 0x5D9830
void* CCustomCarEnvMapPipeline::pluginSpecMatCopyConstructorCB(void* dstObject, const void* srcObject, int32 offsetInObject, int32 sizeInObject) {
    auto src = *RWPLUGINOFFSET(CustomSpecMapPipeMaterialData*, srcObject, ms_specularMapPluginOffset);
    auto dst = *RWPLUGINOFFSET(CustomSpecMapPipeMaterialData*, dstObject, ms_specularMapPluginOffset);
    if (src) {
        if (!dst) {
            dst = m_gSpecMapPipeMatDataPool->New();
        }
        dst->specularity = src->specularity;
        dst->texture = src->texture;
        if (src->texture) {
            src->texture->refCount++;
        }
    }
    return  dst;
}

// 0x5D9880
RwStream* CCustomCarEnvMapPipeline::pluginSpecMatStreamReadCB(RwStream* stream, int32 binaryLength, void* object, int32 offsetInObject, int32 sizeInObject) {
    auto data = *RWPLUGINOFFSET(CustomSpecMapPipeMaterialData*, object, ms_specularMapPluginOffset);
    SpecMatBuffer buffer{};
    RwStreamRead(stream, &buffer, binaryLength);
    if (buffer.specularity != 0.0f) {
        auto texture = RwTextureRead(buffer.name, nullptr);
        if (texture) {
            data = m_gSpecMapPipeMatDataPool->New();
            if (data) {
                data->texture = texture;
                data->specularity = buffer.specularity;
            }
        }
    }
    return stream;
}

// 0x5D8D60
// unsupported
RwStream* CCustomCarEnvMapPipeline::pluginSpecMatStreamWriteCB(RwStream* stream, int32 binaryLength, const void* object, int32 offsetInObject, int32 sizeInObject) {
    return plugin::CallAndReturn<RwStream*, 0x5D8D60, RwStream*, int32, const void*, int32, int32>(stream, binaryLength, object, offsetInObject, sizeInObject);
}

// 0x5D8DD0
int32 CCustomCarEnvMapPipeline::pluginSpecMatStreamGetSizeCB(const void* object, int32 offsetInObject, int32 sizeInObject) {
    return ms_specularMapPluginOffset == -1 ? -1 : sizeof(SpecMatBuffer);
}

// 0x5D8B90
float CCustomCarEnvMapPipeline::GetFxSpecSpecularity(RpMaterial* material) {
    auto data = *RWPLUGINOFFSET(CustomSpecMapPipeMaterialData*, material, ms_specularMapPluginOffset);
    return data ? data->specularity : 0.0f;
}

// 0x5D8B50
RwTexture* CCustomCarEnvMapPipeline::GetFxSpecTexture(RpMaterial* material) {
    auto data = *RWPLUGINOFFSET(CustomSpecMapPipeMaterialData*, material, ms_specularMapPluginOffset);
    return data ? data->texture : nullptr;
}

// 0x5D8B00
void CCustomCarEnvMapPipeline::SetFxSpecTexture(RpMaterial* material, RwTexture* texture) {
    auto* data = *RWPLUGINOFFSET(CustomSpecMapPipeMaterialData*, material, ms_specularMapPluginOffset);
    if (!data)
        return;

    if (texture) {
        if (data->texture) {
            RwTextureDestroy(data->texture);
            data->texture = nullptr;
        }
        data->texture = texture;
        texture->refCount++;
    }

    if (data->texture) {
        RwTextureSetAddressing(data->texture, rwTEXTUREADDRESSCLAMP);
        RwTextureSetFilterMode(data->texture, rwFILTERLINEAR);
    }
}

// 0x5D8B70
void CCustomCarEnvMapPipeline::SetFxSpecSpecularity(RpMaterial* material, float value) {
    auto data = *RWPLUGINOFFSET(CustomSpecMapPipeMaterialData*, material, ms_specularMapPluginOffset);
    if (data) {
        data->specularity = value;
    }
}
