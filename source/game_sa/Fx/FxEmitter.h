#pragma once

#include "FxPrim.h"

struct EmissionInfo_t;

class FxEmitter_c : public FxPrim_c {
public:
    float m_fEmissionIntensity;

public:
    FxEmitter_c() = default; // 0x4A1920
    ~FxEmitter_c() override = default; // 0x4A2BB0

    bool Init(FxPrimBP_c* primBP, FxSystem_c* system) override;
    void Update(float currentTime, float deltaTime) override;
    void Reset() override;
    void AddParticle(RwMatrix* mat, CVector* vel, float timeSince, FxPrtMult_c* fxMults, float rotZ, float brightness, bool createLocal) override;
    void AddParticle(CVector* pos, CVector* vel, float timeSince, FxPrtMult_c* fxMults, float rotZ, float brightness, bool createLocal) override;
    void CreateParticles(float currentTime, float deltaTime);
    FxEmitterPrt_c* CreateParticle(EmissionInfo_t* emissionInfo, RwMatrix* wldMat, CVector* velOverride, float timeSince, FxPrtMult_c* fxMults, float brightness, bool createLocal);

    static void InjectHooks();
    bool Init_Reversed(FxPrimBP_c* primBP, FxSystem_c* system);
    void Update_Reversed(float currentTime, float deltaTime);
    void Reset_Reversed();
    void AddParticle_Reversed(RwMatrix* mat, CVector* vel, float timeSince, FxPrtMult_c* fxMults, float rotZ, float brightness, bool createLocal);
    void AddParticle_Reversed(CVector* pos, CVector* vel, float timeSince, FxPrtMult_c* fxMults, float rotZ, float brightness, bool createLocal);
};
VALIDATE_SIZE(FxEmitter_c, 0x14);
