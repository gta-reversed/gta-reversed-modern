#include "StdInc.h"

#include "CustomCarEnvMapPipeline.h"
#include "app_light.h"

void CCustomCarEnvMapPipeline::InjectHooks() {
    RH_ScopedClass(CCustomCarEnvMapPipeline);
    RH_ScopedCategory("Pipelines");

    RH_ScopedInstall(RegisterPlugin, 0x5DA450);
    RH_ScopedInstall(CreatePipe, 0x5DA020);
    RH_ScopedInstall(DestroyPipe, 0x5DA130);
    RH_ScopedInstall(PreRenderUpdate, 0x5D8870);
    RH_ScopedInstall(CustomPipeMaterialSetup, 0x5DA560);
    RH_ScopedInstall(CustomPipeAtomicSetup, 0x5DA610);
    RH_ScopedInstall(CreateCustomObjPipe, 0x5D9F80);
    RH_ScopedInstall(CustomPipeInstanceCB, 0x5D8490);
    // RH_ScopedInstall(CustomPipeRenderCB, 0x5D9900);
    RH_ScopedInstall(pluginEnvAtmConstructorCB, 0x5D8D30);
    RH_ScopedInstall(pluginEnvAtmDestructorCB, 0x5D9730);
    // RH_ScopedInstall(pluginEnvAtmCopyConstructorCB, 0x5D9780);
    RH_ScopedInstall(AllocEnvMapPipeAtomicData, 0x5D96F0);
    RH_ScopedInstall(pluginEnvMatConstructorCB, 0x5D8BD0);
    RH_ScopedInstall(pluginEnvMatDestructorCB, 0x5D95B0);
    RH_ScopedInstall(pluginEnvMatCopyConstructorCB, 0x5D9600);
    // RH_ScopedInstall(pluginEnvMatStreamReadCB, 0x5D9660);
    // RH_ScopedInstall(pluginEnvMatStreamWriteCB, 0x5D8CD0);
    RH_ScopedInstall(pluginEnvMatStreamGetSizeCB, 0x5D8D10);
    RH_ScopedInstall(GetFxEnvScaleX, 0x5D6F90);
    RH_ScopedInstall(GetFxEnvScaleY, 0x5D6FC0);
    RH_ScopedInstall(SetFxEnvScale, 0x5D6F40);
    RH_ScopedInstall(GetFxEnvTransSclX, 0x5D7040);
    RH_ScopedInstall(GetFxEnvTransSclY, 0x5D7070);
    RH_ScopedInstall(SetFxEnvTransScl, 0x5D6FF0);
    RH_ScopedInstall(GetFxEnvShininess, 0x5D8AD0);
    RH_ScopedInstall(SetFxEnvShininess, 0x5D70A0);
    // RH_ScopedInstall(SetFxEnvTexture, 0x5DA230);
    RH_ScopedInstall(SetCustomEnvMapPipeMaterialDataDefaults, 0x5D8BB0);
    RH_ScopedInstall(pluginSpecMatConstructorCB, 0x5D8D40);
    RH_ScopedInstall(pluginSpecMatDestructorCB, 0x5D97D0);
    RH_ScopedInstall(pluginSpecMatCopyConstructorCB, 0x5D9830);
    RH_ScopedInstall(pluginSpecMatStreamReadCB, 0x5D9880);
    // RH_ScopedInstall(pluginSpecMatStreamWriteCB, 0x5D8D60);
    RH_ScopedInstall(pluginSpecMatStreamGetSizeCB, 0x5D8DD0);
    RH_ScopedInstall(GetFxSpecSpecularity, 0x5D8B90);
    RH_ScopedInstall(GetFxSpecTexture, 0x5D8B50);
}

// 0x5DA450
bool CCustomCarEnvMapPipeline::RegisterPlugin() {
    ms_envMapPluginOffset = RpMaterialRegisterPlugin(4, ENV_MAP_PLUGIN_ID, pluginEnvMatConstructorCB, pluginEnvMatDestructorCB, pluginEnvMatCopyConstructorCB);
    if (ms_envMapPluginOffset < 0) {
        DEV_LOG("Failed to register Env Map Plugin");
        return false;
    }
    if (RpMaterialRegisterPluginStream(ENV_MAP_PLUGIN_ID, pluginEnvMatStreamReadCB, pluginEnvMatStreamWriteCB, pluginEnvMatStreamGetSizeCB) < 0) {
        ms_envMapPluginOffset = -1;
        DEV_LOG("Failed to register Env Map Plugin");
        return false;
    }

    SetCustomEnvMapPipeMaterialDataDefaults(&fakeEnvMapPipeMatData);

    ms_envMapAtmPluginOffset = RpAtomicRegisterPlugin(4, ENV_MAP_ATM_PLUGIN_ID, pluginEnvAtmConstructorCB, pluginEnvAtmDestructorCB, pluginEnvAtmCopyConstructorCB);
    if (ms_envMapAtmPluginOffset < 0) {
        DEV_LOG("Failed to register Env Map Atm Plugin");
        return false;
    }

    ms_specularMapPluginOffset = RpMaterialRegisterPlugin(4, SPECULAR_MAP_PLUGIN_ID, pluginSpecMatConstructorCB, pluginSpecMatDestructorCB, pluginSpecMatCopyConstructorCB);
    if (ms_specularMapPluginOffset < 0) { // OG: (ms_specularMapPluginOffset & 0x80000000) != 0
        DEV_LOG("Failed to register Specular Map Plugin");
        return false;
    }
    if (RpMaterialRegisterPluginStream(SPECULAR_MAP_PLUGIN_ID, pluginSpecMatStreamReadCB, pluginSpecMatStreamWriteCB, pluginSpecMatStreamGetSizeCB) < 0) {
        ms_specularMapPluginOffset = -1;
        DEV_LOG("Failed to register Specular Map Plugin");
        return false;
    }

    return true;
}

// 0x5D8980
bool IsEnvironmentMappingSupported() {
    const auto caps = RwD3D9GetCaps();
    return caps->MaxTextureBlendStages > 1 &&
           caps->MaxSimultaneousTextures >= 2 &&
           caps->TextureOpCaps & D3DTEXOPCAPS_BLENDFACTORALPHA &&
           caps->TextureOpCaps & D3DTEXOPCAPS_MULTIPLYADD &&
           caps->ShadeCaps & D3DPSHADECAPS_SPECULARGOURAUDRGB;
}

// 0x5DA020
bool CCustomCarEnvMapPipeline::CreatePipe() {
    ObjPipeline = CreateCustomObjPipe();
    if (!ObjPipeline || !IsEnvironmentMappingSupported()) {
        return false;
    }
    memset(&g_GameLight, 0, sizeof(g_GameLight));
    m_gEnvMapPipeMatDataPool = new CustomEnvMapPipeMaterialDataPool(4096, "CustomEnvMapPipeMatDataPool");
    m_gEnvMapPipeAtmDataPool = new CustomEnvMapPipeAtomicDataPool(1024, "CustomEnvMapPipeAtmDataPool");
    m_gSpecMapPipeMatDataPool = new CustomSpecMapPipeMaterialDataPool(4096, "CustomSpecMapPipeMaterialDataPool");
    return true;
}

// 0x5DA130
void CCustomCarEnvMapPipeline::DestroyPipe() {
    delete m_gEnvMapPipeMatDataPool;
    m_gEnvMapPipeMatDataPool = nullptr;

    delete m_gEnvMapPipeAtmDataPool;
    m_gEnvMapPipeAtmDataPool = nullptr;

    delete m_gSpecMapPipeMatDataPool;
    m_gSpecMapPipeMatDataPool = nullptr;

    if (ObjPipeline) {
        _rxPipelineDestroy(ObjPipeline);
        ObjPipeline = nullptr;
    }
}

// 0x5D8870
void CCustomCarEnvMapPipeline::PreRenderUpdate() {
    std::memset(&g_GameLight, 0, sizeof(g_GameLight));
    CVector lightDir = RpLightGetFrame(pDirect)->modelling.at;
    lightDir.Normalise();
    g_GameLight.Direction = *(D3DVECTOR*)&lightDir;
    g_GameLight.Type = D3DLIGHT_DIRECTIONAL;
    g_GameLight.Diffuse  = { 0.25f, 0.25f, 0.25f, 1.0f };
    g_GameLight.Ambient  = { 0.75f, 0.75f, 0.75f, 1.0f };
    g_GameLight.Specular = { 0.65f, 0.65f, 0.65f, 1.0f };
    g_GameLight.Range = 1000.0f;
    g_GameLight.Falloff = 0.0f;
    g_GameLight.Attenuation0 = 1.0f;
    g_GameLight.Attenuation1 = 0.0f;
    g_GameLight.Attenuation2 = 0.0f;
}

// 0x5DA560
RpMaterial* CCustomCarEnvMapPipeline::CustomPipeMaterialSetup(RpMaterial* material, void* data) {
    // No other explanation honestly.
    // According to the docs, `specular` isn't used, so I guess that explains it?
    auto& flags = reinterpret_cast<uint32&>(material->surfaceProps.specular);

    flags = 0u;

    if (RpMatFXMaterialGetEffects(material) == rpMATFXEFFECTENVMAP) {
        SetFxEnvTexture(material, nullptr);
    }

    if (GetFxEnvShininess(material) != 0.0f) {
        if (const auto tex = GetFxEnvTexture(material)) {
            flags |= RwTextureGetName(tex)[0] == 'x' ? 0b10 : 0b01;
        }
    }

    if (GetFxSpecSpecularity(material) != 0.0f && GetFxSpecTexture(material)) {
        flags |= 0b100;
    }

    return material;
}

// 0x5DA610
RpAtomic* CCustomCarEnvMapPipeline::CustomPipeAtomicSetup(RpAtomic* atomic) {
    RpGeometryForAllMaterials(atomic->geometry, CustomPipeMaterialSetup, nullptr);
    atomic->pipeline = ObjPipeline;
    SetPipelineID(atomic, CUSTOM_CAR_ENV_MAP_PIPELINE_PLUGIN_ID);
    return atomic;
}

// Android - CreateCustomOpenGLObjPipe
// 0x5D9F80
RxPipeline* CCustomCarEnvMapPipeline::CreateCustomObjPipe() {
    auto pipeline = RxPipelineCreate();
    if (!pipeline)
        return nullptr;

    auto lock = RxPipelineLock(pipeline);
    if (lock) {
        auto nodeDefinition = RxNodeDefinitionGetD3D9AtomicAllInOne();
        auto lockedPipe = RxLockedPipeAddFragment(lock, 0, nodeDefinition);
        if (RxLockedPipeUnlock(lockedPipe)) {
            auto node = RxPipelineFindNodeByName(pipeline, nodeDefinition->name, nullptr, nullptr);
            RxD3D9AllInOneSetInstanceCallBack(node, RxD3D9AllInOneGetInstanceCallBack(node));
            RxD3D9AllInOneSetReinstanceCallBack(node, CustomPipeInstanceCB);
            RxD3D9AllInOneSetRenderCallBack(node, CustomPipeRenderCB);
            pipeline->pluginId = CUSTOM_CAR_ENV_MAP_PIPELINE_PLUGIN_ID;
            pipeline->pluginData = CUSTOM_CAR_ENV_MAP_PIPELINE_PLUGIN_ID;
            return pipeline;
        }
    }
    _rxPipelineDestroy(pipeline);
    return nullptr;
}

// todo: check signature
// 0x5D8490
RwBool CCustomCarEnvMapPipeline::CustomPipeInstanceCB(void* object, RwResEntry* resEntry, RxD3D9AllInOneInstanceCallBack instanceCallback) {
    if (instanceCallback) {
        auto entry = *reinterpret_cast<RwResEntrySA*>(resEntry);
        return instanceCallback(object, &entry.header, true) != 0;
    }
    return true;
}

// 0x5D9900
void CCustomCarEnvMapPipeline::CustomPipeRenderCB(RwResEntry *repEntry, void *object, uint8 type, uint32 flags) {
    return plugin::Call<0x5D9900, RwResEntry*, void*, uint8, uint32>(repEntry, object, type, flags);
}

CustomEnvMapPipeMaterialData* CCustomCarEnvMapPipeline::DuplicateCustomEnvMapPipeMaterialData(CustomEnvMapPipeMaterialData** data) {
    assert(false);
    return nullptr;
}
