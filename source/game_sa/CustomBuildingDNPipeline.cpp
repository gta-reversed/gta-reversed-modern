#include "StdInc.h"

#include "CustomBuildingDNPipeline.h"

float& CCustomBuildingDNPipeline::m_fDNBalanceParam = *(float*)0x8D12C0;
RxPipeline*& CCustomBuildingDNPipeline::ObjPipeline = *(RxPipeline**)0xC02C1C;

void CCustomBuildingDNPipeline::InjectHooks() {
    RH_ScopedClass(CCustomBuildingDNPipeline);
    RH_ScopedCategoryRoot();

    using namespace ReversibleHooks;
    // Install("CCustomBuildingDNPipeline", "", 0x5D7D90, &CCustomBuildingDNPipeline::);
}

// 0x5D7200
void CCustomBuildingDNPipeline::PreRenderUpdate(RpAtomic* atomic, bool ignoreDNBalanceParam) {
    plugin::Call<0x5D7200, RpAtomic*, bool>(atomic, ignoreDNBalanceParam);
}

// 0x5D72A0
RpAtomic* CCustomBuildingDNPipeline::PreRenderUpdateRpAtomicCB(RpAtomic* atomic, void* data) {
    CCustomBuildingDNPipeline::PreRenderUpdate(atomic, static_cast<bool>(reinterpret_cast<intptr_t>(data)));
    return atomic;
}

// 0x5D6DC0
void CCustomBuildingDNPipeline::pluginExtraVertColourStreamGetSizeCB(const void*, int32, int32) {
    assert(false);
}

// 0x5D6DE0
void CCustomBuildingDNPipeline::pluginExtraVertColourStreamReadCB(RwStream* stream, int32, void*, int32, int32) {
    assert(false);
}

// 0x5D6D80
void CCustomBuildingDNPipeline::pluginExtraVertColourStreamWriteCB(RwStream* stream, int32, const void*, int32, int32) {
    assert(false);
}

// 0x5D6D10
void CCustomBuildingDNPipeline::pluginExtraVertColourConstructorCB(void*, int32, int32) {
    assert(false);
}

// 0x5D6D30
void CCustomBuildingDNPipeline::pluginExtraVertColourDestructorCB(void*, int32, int32) {
    assert(false);
}

//
void CCustomBuildingDNPipeline::CustomPipeInstanceCB(void*, RxOpenGLMeshInstanceData* data, int32, int32) {
    assert(false);
}

//
CCustomBuildingDNPipeline::CCustomBuildingDNPipeline() {
    // NOP
}

//
CCustomBuildingDNPipeline::~CCustomBuildingDNPipeline() {
    // NOP
}

// 0x5D5FA0
void CCustomBuildingDNPipeline::DestroyPipe() {
    plugin::Call<0x5D5FA0>();
}

// 0x5D71C0
RpAtomic* CCustomBuildingDNPipeline::CustomPipeAtomicSetup(RpAtomic* atomic) {
    return plugin::CallAndReturn<RpAtomic*, 0x5D71C0, RpAtomic*>(atomic);
}

// android, unused
uint32 CCustomBuildingDNPipeline::UsesThisPipeline(RpAtomic* atomic) {
    return atomic->pipeline
           - ObjPipeline
           + (atomic->pipeline == ObjPipeline)
           + ObjPipeline
           - atomic->pipeline;
}

// 0x5D6750
void CCustomBuildingDNPipeline::CreateCustomObjPipe() {
    plugin::Call<0x5D6750>();
}

// 0x5D7100
bool CCustomBuildingDNPipeline::CreatePipe() {
    return plugin::CallAndReturn<bool, 0x5D7100>();
}

// 0x5D72E0
bool CCustomBuildingDNPipeline::ExtraVertColourPluginAttach() {
    return plugin::CallAndReturn<bool, 0x5D72E0>();
}

// 0x5D6E90
void* CCustomBuildingDNPipeline::GetExtraVertColourPtr(RpGeometry* geometry) {
    return plugin::CallAndReturn<void*, 0x0, RpGeometry*>(geometry);
}

// android, inlined
void CCustomBuildingDNPipeline::SetFxEnvTexture(RpMaterial* material, RwTexture* texture) {
    plugin::Call<0x0, RpMaterial*, RwTexture*>(material, texture);
}

// android, inlined
RwTexture* CCustomBuildingDNPipeline::GetFxEnvTexture(RpMaterial* material) {
    return plugin::CallAndReturn<RwTexture*, 0x0, RpMaterial*>(material);
}

// android, inlined
void CCustomBuildingDNPipeline::SetFxEnvScale(RpMaterial* material, float scaleX, float scaleY) {
    plugin::Call<0x0, RpMaterial*, float, float>(material, scaleX, scaleY);
 }

// android, inlined
float CCustomBuildingDNPipeline::GetFxEnvScaleX(RpMaterial* material) {
    return plugin::CallAndReturn<float, 0x0, RpMaterial*>(material);
}

// android, inlined
float CCustomBuildingDNPipeline::GetFxEnvScaleY(RpMaterial* material) {
    return plugin::CallAndReturn<float, 0x0, RpMaterial*>(material);
}

// android, inlined
void CCustomBuildingDNPipeline::SetFxEnvTransScl(RpMaterial* material, float scaleX, float scaleY) {
    plugin::Call<0x0, RpMaterial*, float, float>(material, scaleX, scaleY);
}

// android, inlined
float CCustomBuildingDNPipeline::GetFxEnvTransSclX(RpMaterial* material) {
    return plugin::CallAndReturn<float, 0x0, RpMaterial*>(material);
}

// android, inlined
float CCustomBuildingDNPipeline::GetFxEnvTransSclY(RpMaterial* material) {
    return plugin::CallAndReturn<float, 0x0, RpMaterial*>(material);
}

// android, inlined
void CCustomBuildingDNPipeline::SetFxEnvShininess(RpMaterial* material, float value) {
    plugin::Call<0x0, RpMaterial*, float>(material, value);
}

// android, inlined
float CCustomBuildingDNPipeline::GetFxEnvShininess(RpMaterial* material) {
    return plugin::CallAndReturn<float, 0x0, RpMaterial*>(material);
}

// android, inlined
void CCustomBuildingDNPipeline::CustomPipeMaterialSetup(RpMaterial* material, void* a2) {
    plugin::Call<0x0, RpMaterial*, void*>(material, a2);
}

// 0x5D6480
void CCustomBuildingDNPipeline::CustomPipeRenderCB(RwResEntry* entry, void* object, uint8 type, uint32 flags) {
    plugin::Call<0x5D6480, RwResEntry*, void*, uint8, uint32>(entry, object, type, flags);
}
