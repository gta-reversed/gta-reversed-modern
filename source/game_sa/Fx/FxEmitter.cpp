#include "StdInc.h"

#include "FxEmitter.h"
#include "EmissionInfo.h"
#include "FxEmitterPrt.h"
#include "FxPrimBP.h"
#include "FxEmitterBP.h"

void FxEmitter_c::InjectHooks() {
    RH_ScopedClass(FxEmitter_c);
    RH_ScopedCategory("Fx");

    // RH_ScopedInstall(Init_Reversed, 0x4A2550);
    // RH_ScopedInstall(Update_Reversed, 0x4A4460); // bad
    // RH_ScopedInstall(Reset_Reversed, 0x4A2570);
    // RH_ScopedOverloadedInstall(AddParticle_Reversed, "matrix", 0x4A3EA0, void(FxEmitter_c::*)(RwMatrix*, CVector*, float, FxPrtMult_c*, float, float, bool));
    // RH_ScopedOverloadedInstall(AddParticle_Reversed, "", 0x4A4050, void(FxEmitter_c::*)(CVector*, CVector*, float, FxPrtMult_c*, float, float, bool));
    // RH_ScopedInstall(CreateParticles, 0x4A41E0);
    // RH_ScopedInstall(CreateParticle, 0x4A2580);
}

bool FxEmitter_c::Init(FxPrimBP_c* primBP, FxSystem_c* system) { return Init_Reversed(primBP, system); }
void FxEmitter_c::Update(float currentTime, float deltaTime) { Update_Reversed(currentTime, deltaTime); }
void FxEmitter_c::Reset() { Reset_Reversed(); }
void FxEmitter_c::AddParticle(RwMatrix* mat, CVector* vel, float timeSince, FxPrtMult_c* fxMults, float rotZ, float brightness, bool createLocal) { AddParticle_Reversed(mat, vel, timeSince, fxMults, rotZ, brightness, createLocal); }
void FxEmitter_c::AddParticle(CVector* pos, CVector* vel, float timeSince, FxPrtMult_c* fxMults, float rotZ, float brightness, bool createLocal) { AddParticle_Reversed(pos, vel, timeSince, fxMults, rotZ, brightness, createLocal); }

// 0x4A2550
bool FxEmitter_c::Init_Reversed(FxPrimBP_c* primBP, FxSystem_c* system) {
    m_PrimBP             = primBP;
    m_System             = system;
    m_fEmissionIntensity = 0.0f;
    return true;
}

// 0x4A4460
void FxEmitter_c::Update_Reversed(float currentTime, float deltaTime) {
    if (m_bEnabled && !m_System->m_stopParticleCreation) {
        CreateParticles(currentTime, deltaTime);
    }
}

// 0x4A2570
void FxEmitter_c::Reset_Reversed() {
    m_fEmissionIntensity = 0.0f;
}

// 0x4A3EA0
void FxEmitter_c::AddParticle_Reversed(CVector* pos, CVector* vel, float timeSince, FxPrtMult_c* fxMults, float rotZ, float brightness, bool createLocal) {
    return plugin::CallMethod<0x4A3EA0, FxEmitter_c*, CVector*, CVector*, float, FxPrtMult_c*, float, float, bool>(this, pos, vel, timeSince, fxMults, rotZ, brightness,
                                                                                                                   createLocal);

    // todo:
    EmissionInfo_t emission;
    m_PrimBP->m_FxInfoManager.ProcessEmissionInfo(0.0f, 0.0f, m_System->m_SystemBP->m_fLength, m_System->m_UseConstTime, &emission);

    auto mat1 = g_fxMan.FxRwMatrixCreate();
    auto mat0 = g_fxMan.FxRwMatrixCreate();
    auto mat  = g_fxMan.FxRwMatrixCreate();

    RwMatrixSetIdentity(mat);
    RwV3dAssign(RwMatrixGetPos(mat), pos);

    RwMatrixUpdate(mat);
    if (m_System->m_ParentMatrix) {
        RwMatrixMultiply(mat0, mat, m_System->m_ParentMatrix);
    }
    else {
        mat0 = mat;
    }

    auto mat2 = g_fxMan.FxRwMatrixCreate();
    m_PrimBP->GetRWMatrix(mat2);
    RwMatrixMultiply(mat1, mat2, mat0);
    g_fxMan.FxRwMatrixDestroy(mat2);

    if (auto* particle = CreateParticle(&emission, mat1, vel, timeSince, fxMults, brightness, createLocal)) {
        if (rotZ >= 0.0f) {
            particle->m_RotZ = (uint8)(rotZ / 2.0f); // todo: int8/uint8 conversion
        }
    }

    g_fxMan.FxRwMatrixDestroy(mat);
    g_fxMan.FxRwMatrixDestroy(mat0);
    g_fxMan.FxRwMatrixDestroy(mat1);
}

// 0x4A4050
void FxEmitter_c::AddParticle_Reversed(RwMatrix* mat, CVector* vel, float timeSince, FxPrtMult_c* fxMults, float rotZ, float brightness, bool createLocal) {
    return plugin::CallMethod<0x4A4050, FxEmitter_c*, RwMatrix*, CVector*, float, FxPrtMult_c*, float, float, bool>(this, mat, vel, timeSince, fxMults, rotZ, brightness,
                                                                                                                    createLocal);

    // todo:
    EmissionInfo_t emission;
    m_PrimBP->m_FxInfoManager.ProcessEmissionInfo(0.0f, 0.0f, m_System->m_SystemBP->m_fLength, m_System->m_UseConstTime, &emission);
    auto mat2 = g_fxMan.FxRwMatrixCreate();
    auto mat1 = g_fxMan.FxRwMatrixCreate();
    auto mat0 = g_fxMan.FxRwMatrixCreate();
    RwMatrixSetIdentity(mat0);
    mat0 = mat;

    RwMatrixUpdate(mat0);
    if (m_System->m_ParentMatrix) {
        RwMatrixMultiply(mat1, mat0, m_System->m_ParentMatrix);
    } else {
        mat1 = mat0;
    }

    auto mat3 = g_fxMan.FxRwMatrixCreate();
    m_PrimBP->GetRWMatrix(mat3);
    RwMatrixMultiply(mat2, mat3, mat1);
    g_fxMan.FxRwMatrixDestroy(mat3);

    if (auto* particle = CreateParticle(&emission, mat2, vel, timeSince, fxMults, brightness, createLocal)) {
        if (rotZ >= 0.0f)
            particle->m_RotZ = (uint8)(rotZ * 2.0f); // todo:: see above
    }

    g_fxMan.FxRwMatrixDestroy(mat0);
    g_fxMan.FxRwMatrixDestroy(mat1);
    g_fxMan.FxRwMatrixDestroy(mat2);
}

// 0x4A41E0
void FxEmitter_c::CreateParticles(float currentTime, float deltaTime) {
    return plugin::CallMethod<0x4A41E0, FxEmitter_c*, float, float>(this, currentTime, deltaTime);

    EmissionInfo_t emission;
    m_PrimBP->m_FxInfoManager.ProcessEmissionInfo(currentTime, deltaTime, m_System->m_SystemBP->m_fLength, m_System->m_UseConstTime, &emission);

    auto lodStart = (float)m_PrimBP->m_FxInfoManager.m_nLodStart / 64.0f;
    auto lodEnd   = (float)m_PrimBP->m_FxInfoManager.m_nLodEnd   / 64.0f;

    float visibility;
    if (m_System->m_fCameraDistance >= lodStart) {
        if (m_System->m_fCameraDistance <= lodEnd) {
            visibility = 1.0f - (m_System->m_fCameraDistance - lodStart) / (lodEnd - lodStart);
        } else {
            visibility = 0.0f;
        }
    } else {
        visibility = 1.0f;
    }

    m_fEmissionIntensity += emission.m_fCount * visibility * ((float)m_System->m_nRateMult * 1000.0f);
    if (   CWeather::Wind >= emission.m_fMinWind
        && CWeather::Wind <= emission.m_fMaxWind
        && CWeather::Rain >= emission.m_fMinRain
        && CWeather::Rain <= emission.m_fMaxRain
        && m_fEmissionIntensity >= 1.0f
    ) {
        auto mat = g_fxMan.FxRwMatrixCreate();
        auto mat1 = g_fxMan.FxRwMatrixCreate();
        RwMatrixUpdate(&m_System->m_LocalMatrix);
        if (m_System->m_ParentMatrix) {
            RwMatrixMultiply(mat1, &m_System->m_LocalMatrix, m_System->m_ParentMatrix);
        } else {
            *mat1 = m_System->m_LocalMatrix;
        }

        auto mat2 = g_fxMan.FxRwMatrixCreate();
        m_PrimBP->GetRWMatrix(mat2);
        RwMatrixMultiply(mat, mat2, mat1);
        g_fxMan.FxRwMatrixDestroy(mat2);

        auto counter = 0u;
        for (auto step = 0u; counter < (uint32)m_fEmissionIntensity; step = counter) {
            FxPrtMult_c prtMult;
            auto timeSince = (float)step / m_fEmissionIntensity * deltaTime;
            CreateParticle(&emission, mat, nullptr, timeSince, &prtMult, 1.2f, m_System->m_createLocal);
            counter++;
        }
        m_fEmissionIntensity -= m_fEmissionIntensity; // OG shit

        g_fxMan.FxRwMatrixDestroy(mat1);
        g_fxMan.FxRwMatrixDestroy(mat);
    }
}

// 0x4A2580
FxEmitterPrt_c* FxEmitter_c::CreateParticle(EmissionInfo_t* emissionInfo, RwMatrix* wldMat, CVector* velOverride, float timeSince, FxPrtMult_c* fxMults, float brightness, bool createLocal) {
    return plugin::CallMethodAndReturn<FxEmitterPrt_c*, 0x4A2580, FxEmitter_c*, EmissionInfo_t*, RwMatrix*, CVector*, float, FxPrtMult_c*, float, bool>(this, emissionInfo, wldMat, velOverride, timeSince, fxMults, brightness, createLocal);

    // todo:
    auto* particle = g_fxMan.GetParticle(0);
    if (!particle && !(m_System->m_MustCreateParticles && (g_fxMan.FreeUpParticle(), (particle = g_fxMan.GetParticle(0)) != nullptr)))
        return particle;

    particle->m_fCurrentLife = 0.0f;
    particle->m_fTotalLife = (((float)(CGeneral::GetRandomNumber() % 10'000) / 5'000.0f - 1.0f) * emissionInfo->m_fLifeBias + emissionInfo->m_fLife) * fxMults->m_fLife;
    particle->m_System = m_System;

    particle->m_MultColor.red   = (uint8)(fxMults->m_Color.red   * 255.0f);
    particle->m_MultColor.green = (uint8)(fxMults->m_Color.green * 255.0f);
    particle->m_MultColor.blue  = (uint8)(fxMults->m_Color.blue  * 255.0f);
    particle->m_MultColor.alpha = (uint8)(fxMults->m_Color.alpha * 255.0f);

    particle->m_MultSize = (uint8)(fxMults->m_fSize * 255.0f);
    particle->m_MultRot = (uint8)(fxMults->m_Rot * 255.0f);

    particle->m_bLocalToSystem = createLocal;

    particle->m_RandR = (uint8)((float)(CGeneral::GetRandomNumber() % 10'000) / 10'000.0f * 255.0f);
    particle->m_RandG = (uint8)((float)(CGeneral::GetRandomNumber() % 10'000) / 10'000.0f * 255.0f);
    particle->m_RandB = (uint8)((float)(CGeneral::GetRandomNumber() % 10'000) / 10'000.0f * 255.0f);
    particle->m_Brightness = (uint8)(brightness * 100.0f);

    particle->m_RotZ = -1;
    particle->m_CurrentRotation = (float)(CGeneral::GetRandomNumber() % 10'000) / 10'000.0f * (emissionInfo->m_fRotationMaxAngle - emissionInfo->m_fRotationMinAngle) + emissionInfo->m_fRotationMinAngle;

    if (createLocal) {
        m_PrimBP->GetRWMatrix(wldMat);
    }

    CVector vec;
    if (std::fabs(emissionInfo->m_fRadius) < 0.001000000047497451f) { // todo
        vec = CVector{
            (float)(CGeneral::GetRandomNumber() % 10'000) / 10'000.0f * (emissionInfo->m_SizeMax.x - emissionInfo->m_SizeMin.x) + emissionInfo->m_SizeMin.x,
            (float)(CGeneral::GetRandomNumber() % 10'000) / 10'000.0f * (emissionInfo->m_SizeMax.y - emissionInfo->m_SizeMin.y) + emissionInfo->m_SizeMin.y,
            (float)(CGeneral::GetRandomNumber() % 10'000) / 10'000.0f * (emissionInfo->m_SizeMax.z - emissionInfo->m_SizeMin.z) + emissionInfo->m_SizeMin.z,
        };
    } else {
        vec = CVector{
            (float)(CGeneral::GetRandomNumber() % 10'000) / 5000.0f - 1.0f,
            (float)(CGeneral::GetRandomNumber() % 10'000) / 5000.0f - 1.0f,
            (float)(CGeneral::GetRandomNumber() % 10'000) / 5000.0f - 1.0f,
        };

        float radius;
        auto invDist = 1.0f / vec.Magnitude();
        if (emissionInfo->m_fRadius < 0.0f) { // todo: check comp.
            radius = invDist * emissionInfo->m_fRadius;
        } else {
            radius = (invDist * (float)(CGeneral::GetRandomNumber() % 10'000) / 10'000.0f) * emissionInfo->m_fRadius;
        }
        vec *= radius;
    }
    vec += emissionInfo->m_Pos;

    particle->m_Pos = vec.z * wldMat->at + vec.y * wldMat->up + vec.x * wldMat->right + wldMat->pos;

    if (velOverride) {
        particle->m_Velocity = *velOverride;
    } else {
        auto index = (float)(CGeneral::GetRandomNumber() % 10'000) / 10'000.0f * TWO_PI;
        auto minAngle = DegreesToRadians(emissionInfo->m_fAngleMin);
        auto maxAngle = DegreesToRadians(emissionInfo->m_fAngleMax);

        auto sinY = ((float)(CGeneral::GetRandomNumber() % 10'000) / 10'000.0f * (maxAngle - minAngle) + minAngle) * 40.743664f;

        CVector v37;
        v37.x = CMaths::ms_SinTable[(uint8)((index * 40.743664f) + 64.0f) + 1] * CMaths::ms_SinTable[(uint8)sinY + 1];
        v37.y = CMaths::ms_SinTable[(uint8)(sinY + 64.0f) + 1];
        v37.z = CMaths::ms_SinTable[(uint8)(index * 40.743664f) + 1] * CMaths::ms_SinTable[(uint8)sinY + 1];

        CVector vectorsIn;
        CVector vectorsOut;
        if (emissionInfo->m_Direction.x <= 10.0f) {
            vectorsIn = emissionInfo->m_Direction;
            vectorsIn.Normalise();
        } else {
            vectorsIn = particle->m_Pos;
        }
        RwV3dTransformVectors(&vectorsOut, &vectorsIn, 1, wldMat);
        CVector v38;
        RotateVecIntoVec(&v38, &v37, &vectorsOut);
        particle->m_Velocity = v38 * (((float)(CGeneral::GetRandomNumber() % 10'000) / 5000.0f - 1.0f) * emissionInfo->m_fSpeedBias + emissionInfo->m_fSpeed);
    }

    particle->m_Velocity += m_System->m_VelAdd;
    static_cast<FxEmitterBP_c*>(m_PrimBP)->UpdateParticle(timeSince, particle);
    m_PrimBP->m_Particles.AddItem(particle);

    return particle;
}
