#pragma once

class CCarFXRenderer {
public:
    static constexpr int32 NUM_DIRT_TEXTURES = 16;
    static RwTexture* (&ms_aDirtTextures)[NUM_DIRT_TEXTURES];

public:
    static void InjectHooks();

    static bool Initialise();
    static void Shutdown();
    static void PreRenderUpdate();

    static void RegisterPlugins();
    static bool IsCCPCPipelineAttached(RpAtomic* pAtomic);

    static void CustomCarPipeAtomicSetup(RpAtomic* pAtomic);
    static void CustomCarPipeClumpSetup(RpClump* pClump);

    static void InitialiseDirtTexture();
    static RpMaterial* MaterialRemapDirtCB(RpMaterial*, void*);
    static RpAtomic* AtomicRemapDirtCB(RpAtomic*, void*);
    static RpAtomic* SetCustomFXAtomicRenderPipelinesVMICB(RpAtomic* pAtomic, void* data);

    static float GetFxEnvMapLightMult();
    static void SetFxEnvMapLightMult(float multiplier);
};
