#include "StdInc.h"

#include "CustomBuildingDNPipeline.h"
#include "CustomCarEnvMapPipeline.h"

void CCustomBuildingDNPipeline::InjectHooks() {
    RH_ScopedClass(CCustomBuildingDNPipeline);
    RH_ScopedCategory("Pipelines");

    RH_ScopedInstall(ExtraVertColourPluginAttach, 0x5D72E0);
    RH_ScopedInstall(pluginExtraVertColourConstructorCB, 0x5D6D10, { .reversed = false });
    RH_ScopedInstall(pluginExtraVertColourDestructorCB, 0x5D6D30, { .reversed = false });
    RH_ScopedInstall(pluginExtraVertColourStreamReadCB, 0x5D6DE0, { .reversed = false });
    RH_ScopedInstall(pluginExtraVertColourStreamWriteCB, 0x5D6D80, { .reversed = false });
    RH_ScopedInstall(pluginExtraVertColourStreamGetSizeCB, 0x5D6DC0, { .reversed = false });
    RH_ScopedInstall(PreRenderUpdate, 0x5D7200, { .reversed = false });
    RH_ScopedInstall(PreRenderUpdateRpAtomicCB, 0x5D72A0);
    RH_ScopedInstall(CreatePipe, 0x5D7100);
    RH_ScopedInstall(DestroyPipe, 0x5D5FA0);
    RH_ScopedInstall(CreateCustomObjPipe, 0x5D6750);
    RH_ScopedInstall(CustomPipeAtomicSetup, 0x5D71C0);
}

// 0x5D72E0
bool CCustomBuildingDNPipeline::ExtraVertColourPluginAttach() {
    ms_extraVertColourPluginOffset = -1;
    ms_extraVertColourPluginOffset = RpGeometryRegisterPlugin(12, EXTRA_VERTCOLOUR_PLUGIN_ID, pluginExtraVertColourConstructorCB, pluginExtraVertColourDestructorCB, nullptr);
    if (ms_extraVertColourPluginOffset == -1) {
        return false;
    }

    if (RpGeometryRegisterPluginStream(EXTRA_VERTCOLOUR_PLUGIN_ID, pluginExtraVertColourStreamReadCB, pluginExtraVertColourStreamWriteCB, pluginExtraVertColourStreamGetSizeCB) < 0) {
        ms_extraVertColourPluginOffset = -1;
        return false;
    }

    return true;
}

// 0x5D6D10
void* CCustomBuildingDNPipeline::pluginExtraVertColourConstructorCB(void* object, int32 offsetInObject, int32 sizeInObject) {
    return plugin::CallAndReturn<void*, 0x5D6D10, void*, int32, int32>(object, offsetInObject, sizeInObject);
}

// 0x5D6D30
void* CCustomBuildingDNPipeline::pluginExtraVertColourDestructorCB(void* object, int32 offsetInObject, int32 sizeInObject) {
    return plugin::CallAndReturn<void*, 0x5D6D30, void*, int32, int32>(object, offsetInObject, sizeInObject);
}

// 0x5D6DE0
RwStream* CCustomBuildingDNPipeline::pluginExtraVertColourStreamReadCB(RwStream* stream, int32 binaryLength, void* object, int32 offsetInObject, int32 sizeInObject) {
    return plugin::CallAndReturn<RwStream*, 0x5D6DE0, RwStream*, int32, void*, int32, int32>(stream, binaryLength, object, offsetInObject, sizeInObject);
}

// 0x5D6D80
RwStream* CCustomBuildingDNPipeline::pluginExtraVertColourStreamWriteCB(RwStream* stream, int32 binaryLength, const void* object, int32 offsetInObject, int32 sizeInObject) {
    return plugin::CallAndReturn<RwStream*, 0x5D6D80, RwStream *, int32, const void*, int32, int32>(stream, binaryLength, object, offsetInObject, sizeInObject);
}

// 0x5D6DC0
int32 CCustomBuildingDNPipeline::pluginExtraVertColourStreamGetSizeCB(const void* object, int32 offsetInObject, int32 sizeInObject) {
    return plugin::CallAndReturn<int32, 0x5D6DC0, const void*, int32, int32>(object, offsetInObject, sizeInObject);
}

// 0x5D7200
void CCustomBuildingDNPipeline::PreRenderUpdate(RpAtomic* atomic, bool ignoreDNBalanceParam) {
    plugin::Call<0x5D7200, RpAtomic*, bool>(atomic, ignoreDNBalanceParam);
}

// 0x5D72A0
RpAtomic* CCustomBuildingDNPipeline::PreRenderUpdateRpAtomicCB(RpAtomic* atomic, void* data) {
    PreRenderUpdate(atomic, reinterpret_cast<bool*>(data));
    return atomic;
}

// 0x5D7100
bool CCustomBuildingDNPipeline::CreatePipe() {
    ObjPipeline = CreateCustomObjPipe();
    return ObjPipeline != nullptr;
}

// 0x5D6750
RxPipeline* CCustomBuildingDNPipeline::CreateCustomObjPipe() {
    auto pipeline = RxPipelineCreate();
    auto nodeDefinition = RxNodeDefinitionGetD3D9AtomicAllInOne();
    if (!pipeline)
        return nullptr;

    auto lockedPipe = RxPipelineLock(pipeline);
    if (!lockedPipe || !RxLockedPipeAddFragment(lockedPipe, 0, nodeDefinition, 0) || !RxLockedPipeUnlock(lockedPipe)) {
        _rxPipelineDestroy(pipeline);
        return nullptr;
    }

    auto node = RxPipelineFindNodeByName(pipeline, nodeDefinition->name, nullptr, nullptr);
    if (*reinterpret_cast<int32*>(0xC02C20)) { // read only
        RxD3D9AllInOneSetInstanceCallBack(node, RxD3D9AllInOneGetInstanceCallBack(node));
        RxD3D9AllInOneSetReinstanceCallBack(node, CustomPipeInstanceCB);
    } else {
        RxD3D9AllInOneSetInstanceCallBack(node, RxD3D9AllInOneGetInstanceCallBack(node));
        RxD3D9AllInOneSetReinstanceCallBack(node, RxD3D9AllInOneGetReinstanceCallBack(node));
    }
    RxD3D9AllInOneSetRenderCallBack(node, CustomPipeRenderCB);
    pipeline->pluginId = CUSTOM_BUILDING_DN_PIPELINE_ID;
    pipeline->pluginData = CUSTOM_BUILDING_DN_PIPELINE_ID;
    return pipeline;
}

// 0x5D5FA0
void CCustomBuildingDNPipeline::DestroyPipe() {
    if (ObjPipeline) {
        _rxPipelineDestroy(ObjPipeline);
        ObjPipeline = nullptr;
    }
}

// sub_5D63E0
RwBool CCustomBuildingDNPipeline::CustomPipeInstanceCB(void* object, RwResEntry* resEntry, RxD3D9AllInOneInstanceCallBack instanceCallback) {
    if (instanceCallback) {
        auto entry = *reinterpret_cast<RwResEntrySA*>(resEntry);
        return instanceCallback(object, &entry.header, true);
    }
    return true;
}

// 0x5D71C0
RpAtomic* CCustomBuildingDNPipeline::CustomPipeAtomicSetup(RpAtomic* atomic) {
    RpGeometryForAllMaterials(atomic->geometry, CustomPipeMaterialSetup, nullptr);
    RpD3D9GeometrySetUsageFlags(atomic->geometry, rpD3D9GEOMETRYUSAGE_DYNAMICPRELIT);
    atomic->pipeline = ObjPipeline;
    SetPipelineID(atomic, CUSTOM_BUILDING_DN_PIPELINE_ID);
    return atomic;
}

// android, unused
uint32 CCustomBuildingDNPipeline::UsesThisPipeline(RpAtomic* atomic) {
    return atomic->pipeline
           - ObjPipeline
           + (atomic->pipeline == ObjPipeline) // AtomicHasNVCPipeline	0x5D5FC0
           + ObjPipeline
           - atomic->pipeline;
}

// 0x5D7120
RpMaterial* CCustomBuildingDNPipeline::CustomPipeMaterialSetup(RpMaterial* material, void* data) {
    return plugin::CallAndReturn<RpMaterial*, 0x5D7120, RpMaterial*, void*>(material, data);
}

// 0x5D6480
void CCustomBuildingDNPipeline::CustomPipeRenderCB(RwResEntry* entry, void* object, uint8 type, uint32 flags) {
    plugin::Call<0x5D6480, RwResEntry*, void*, uint8, uint32>(entry, object, type, flags);
}

// 0x5D6E90
void* CCustomBuildingDNPipeline::GetExtraVertColourPtr(RpGeometry* geometry) {
    return *RWPLUGINOFFSET(void*, geometry, ms_extraVertColourPluginOffset); // todo: return type
}

void CCustomBuildingDNPipeline::SetFxEnvTexture(RpMaterial* material, RwTexture* texture) {
    plugin::Call<0x5D9570, RpMaterial*, RwTexture*>(material, texture);
}

RwTexture* CCustomBuildingDNPipeline::GetFxEnvTexture(RpMaterial* material) {
    return CCustomCarEnvMapPipeline::GetFxEnvTexture(material);
}

void CCustomBuildingDNPipeline::SetFxEnvScale(RpMaterial* material, float x, float y) {
    CCustomCarEnvMapPipeline::SetFxEnvScale(material, x, y);
}

float CCustomBuildingDNPipeline::GetFxEnvScaleX(RpMaterial* material) {
    return CCustomCarEnvMapPipeline::GetFxEnvScaleX(material);
}

float CCustomBuildingDNPipeline::GetFxEnvScaleY(RpMaterial* material) {
    return CCustomCarEnvMapPipeline::GetFxEnvScaleY(material);
}

void CCustomBuildingDNPipeline::SetFxEnvTransScl(RpMaterial* material, float x, float y) {
    CCustomCarEnvMapPipeline::SetFxEnvTransScl(material, x, y);
}

float CCustomBuildingDNPipeline::GetFxEnvTransSclX(RpMaterial* material) {
    return CCustomCarEnvMapPipeline::GetFxEnvTransSclX(material);
}

float CCustomBuildingDNPipeline::GetFxEnvTransSclY(RpMaterial* material) {
    return CCustomCarEnvMapPipeline::GetFxEnvTransSclY(material);
}

void CCustomBuildingDNPipeline::SetFxEnvShininess(RpMaterial* material, float value) {
    CCustomCarEnvMapPipeline::SetFxEnvShininess(material, value);
}

float CCustomBuildingDNPipeline::GetFxEnvShininess(RpMaterial* material) {
    return CCustomCarEnvMapPipeline::GetFxEnvShininess(material);
}
