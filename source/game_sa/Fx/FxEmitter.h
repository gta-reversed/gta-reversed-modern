#pragma once

#include "FxPrim.h"

struct EmissionInfo_t;

class FxEmitter_c : public FxPrim_c {
public:
    float m_fEmissionIntensity;

public:
    static void InjectHooks();

    FxEmitter_c() = default; // 0x4A1920
    ~FxEmitter_c() override = default; // 0x4A2BB0

    bool Init(FxPrimBP_c* primBP, FxSystem_c* system) override;
    void Update(float currentTime, float mult) override;
    void Reset() override;
    void AddParticle(RwMatrix* mat, CVector* direction, float a4, FxPrtMult_c* prtMult, float a6, float a7, bool bLocalParticles) override;
    void AddParticle(CVector* pos, CVector* direction, float a4, FxPrtMult_c* prtMult, float a6, float a7, bool bLocalParticles) override;
    void CreateParticles(float currentTime, float mult);
    FxEmitterPrt_c* CreateParticle(EmissionInfo_t* emissionInfo, RwMatrix* transformMatrix, CVector* direction, float a5, FxPrtMult_c* prtMult, float a7, bool bLocalParticles);

private:
    bool Init_Reversed(FxPrimBP_c* primBP, FxSystem_c* system);
    void Update_Reversed(float currentTime, float mult);
    void Reset_Reversed();
    void AddParticle_Reversed(RwMatrix* mat, CVector* direction, float a4, FxPrtMult_c* prtMult, float a6, float a7, bool bLocalParticles);
    void AddParticle_Reversed(CVector* pos, CVector* direction, float a4, FxPrtMult_c* prtMult, float a6, float a7, bool bLocalParticles);

};
VALIDATE_SIZE(FxEmitter_c, 0x14);
