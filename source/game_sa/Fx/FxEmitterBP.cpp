#include "StdInc.h"

#include "FxEmitterBP.h"
#include "FxEmitter.h"
#include "FxPrimBP.h"
#include "FxEmitterPrt.h"
// #include "FxInfo.h"
#include "FxInfoManager.h"

#include "Particle.h"
#include "FxTools.h"

void FxEmitterBP_c::InjectHooks() {
    RH_ScopedClass(FxEmitterBP_c);
    RH_ScopedCategory("Fx");

    // RH_ScopedInstall(Constructor, 0x4A18D0);
    // RH_ScopedInstall(RenderHeatHaze, 0x4A1940);
    // RH_ScopedInstall(UpdateParticle, 0x4A21D0);
    // RH_ScopedInstall(CreateInstance_Reversed, 0x4A2B40); // bad
    // RH_ScopedInstall(Update_Reversed, 0x4A2BC0);
    // RH_ScopedInstall(Load_Reversed, 0x5C25F0);
    // RH_ScopedInstall(LoadTextures_Reversed, 0x5C0A30);
    // RH_ScopedInstall(Render_Reversed, 0x4A2C40);
    // RH_ScopedInstall(FreePrtFromPrim_Reversed, 0x4A2510);
}

FxPrim_c* FxEmitterBP_c::CreateInstance() { return CreateInstance_Reversed(); }
void FxEmitterBP_c::Update(float time) { Update_Reversed(time); }
bool FxEmitterBP_c::LoadTextures(FxName32_t* textureNames, int32 version) { return LoadTextures_Reversed(textureNames, version); }
bool FxEmitterBP_c::Load(FILESTREAM file, int32 version, FxName32_t* textureNames) { return Load_Reversed(file, version, textureNames); }
void FxEmitterBP_c::Render(RwCamera* camera, uint32 a2, float dayNightBalance, bool bCanRenderHeatHaze) { Render_Reversed(camera, a2, dayNightBalance, bCanRenderHeatHaze); }
bool FxEmitterBP_c::FreePrtFromPrim(FxSystem_c* system) { return FreePrtFromPrim_Reversed(system); }

// 0x4A18D0
FxEmitterBP_c::FxEmitterBP_c() : FxPrimBP_c() {
    field_4 = 0; // see ForAllParticles
}

// 0x4A1940
void FxEmitterBP_c::RenderHeatHaze(RwCamera* camera, uint32 a3, float a4) {
    return plugin::CallMethod<0x4A1940, FxEmitterBP_c*, RwCamera*, uint32, float>(this, camera, a3, a4);
}

// 0x4A21D0
bool FxEmitterBP_c::UpdateParticle(float time, FxEmitterPrt_c* emitter) {
    return plugin::CallMethodAndReturn<bool, 0x4A21D0, FxEmitterBP_c*, float, FxEmitterPrt_c*>(this, time, emitter);
}

// 0x4A2B40
FxPrim_c* FxEmitterBP_c::CreateInstance_Reversed() {
    return new FxEmitter_c();
}

// 0x4A2BC0
void FxEmitterBP_c::Update_Reversed(float time) {
    plugin::CallMethod<0x4A2BC0, FxEmitterBP_c*, float>(this, time);
    return;

    /*
    for (auto it = m_Particles.GetHead(); it; it = m_Particles.GetNext(it)) {
        if (it->m_System->m_nKillStatus == eFxSystemKillStatus::FX_3) {
            it->m_System->m_nKillStatus = eFxSystemKillStatus::FX_KILLED;
        }

        if (it->m_System->m_nPlayStatus != eFxSystemPlayStatus::T2 && UpdateParticle(time, it)) {
            m_Particles.RemoveItem(it);
            g_fxMan.ReturnParticle(it);
        }
    }
    */
}

// 0x5C25F0
bool FxEmitterBP_c::Load_Reversed(FILESTREAM file, int32 version, FxName32_t* textureNames) {
    return plugin::CallMethodAndReturn<bool, 0x5C25F0, FxEmitterBP_c*, FILESTREAM, int32, FxName32_t*>(this, file, version, textureNames);

    FxPrimBP_c::Load(file, version, textureNames);

    m_nLodStart = uint16(ReadField<float>(file, "LODSTART:") * 64.0f);
    m_nLodEnd   = uint16(ReadField<float>(file, "LODEND:") * 64.0f);

    return true;
}

// 0x5C0A30
bool FxEmitterBP_c::LoadTextures_Reversed(FxName32_t* textureNames, int32 version) {
    // return plugin::CallMethodAndReturn<bool, 0x5C0A30, FxEmitterBP_c*, int32, FxName32_t*>(this, version, textureNames);

    assert(textureNames);

    const auto LoadTexture = [&](auto ind) -> RwTexture* {
        const auto name = textureNames[ind].value;
        char mask[64];
        sprintf(mask, "%sm", name);

        auto* texture = RwTextureRead(name, mask);
        return texture ? texture : RwTextureRead(name, nullptr);
    };

    const auto LoadTextureIfExists = [=](auto ind) -> RwTexture* {
        assert(&textureNames[ind]);
        auto name = textureNames[ind].value;
        return strncmp(name, "NULL", 5u) != 0 ? LoadTexture(ind) : nullptr;
    };

    m_apTextures[0] = LoadTexture(0);

    if (version > 101) {
        m_apTextures[1] = LoadTextureIfExists(1);
        m_apTextures[2] = LoadTextureIfExists(2);
        m_apTextures[3] = LoadTextureIfExists(3);
    }

    return true;
}

// 0x4A2C40
void FxEmitterBP_c::Render_Reversed(RwCamera* camera, uint32 a2, float dayNightBalance, bool bCanRenderHeatHaze) {
    plugin::CallMethod<0x4A2C40, FxEmitterBP_c*, RwCamera*, uint32, float, bool>(this, camera, a2, dayNightBalance, bCanRenderHeatHaze);
}

// 0x4A2510
bool FxEmitterBP_c::FreePrtFromPrim_Reversed(FxSystem_c* system) {
    return plugin::CallMethodAndReturn<bool, 0x4A2510, FxEmitterBP_c*, FxSystem_c*>(this, system);
}

// todo: eFxInfo
// 0x4A24D0
bool FxEmitterBP_c::IsFxInfoPresent(int32 type) const {
    return plugin::CallMethodAndReturn<bool, 0x4A24D0, const FxEmitterBP_c*, int32>(this, type);
    /*
    if (m_FxInfoManager.m_nNumInfos <= 0)
        return false;

    for (auto& info : m_FxInfoManager.GetInfos()) {
        if (info->m_nType == type) {
            return true;
        }
    }
    return false;
    */
}
