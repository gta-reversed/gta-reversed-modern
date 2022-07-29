#include "StdInc.h"

#include "CustomCarEnvMapPipeline.h"

// 0x5D8D30
void* CCustomCarEnvMapPipeline::pluginEnvAtmConstructorCB(void* object, int32 offsetInObject, int32 sizeInObject) {
    *RWPLUGINOFFSET(CustomEnvMapPipeAtomicData*, object, offsetInObject) = nullptr;
    return object;
}

// 0x5D9730
void* CCustomCarEnvMapPipeline::pluginEnvAtmDestructorCB(void* object, int32 offsetInObject, int32 sizeInObject) {
    auto* obj = *RWPLUGINOFFSET(CustomEnvMapPipeAtomicData*, object, offsetInObject);
    if (obj) {
        m_gEnvMapPipeAtmDataPool->Delete(obj);
        obj = nullptr;
    }
    return object;
}

// 0x5D9780
void* CCustomCarEnvMapPipeline::pluginEnvAtmCopyConstructorCB(void* dstObject, const void* srcObject, int32 offsetInObject, int32 sizeInObject) {
    return plugin::CallAndReturn<void*, 0x5D9780, void*, const void*, int32, int32>(dstObject, srcObject, offsetInObject, sizeInObject);
}

// 0x5D96F0
void CCustomCarEnvMapPipeline::AllocEnvMapPipeAtomicData(RpAtomic* atomic) {
    auto data = *RWPLUGINOFFSET(CustomEnvMapPipeAtomicData*, atomic, ms_envMapAtmPluginOffset);
    if (!data) {
        auto newData = m_gEnvMapPipeAtmDataPool->New();
        *RWPLUGINOFFSET(CustomEnvMapPipeAtomicData*, atomic, ms_envMapAtmPluginOffset) = newData;
        if (newData) {
            SetCustomEnvMapPipeAtomicDataDefaults(newData);
        }
    }
}

void CCustomCarEnvMapPipeline::SetCustomEnvMapPipeAtomicDataDefaults(CustomEnvMapPipeAtomicData* data) {
    data->lastTrans = 0.0f;
    data->posy = 0.0f;
    data->posx = 0.0f;
}
