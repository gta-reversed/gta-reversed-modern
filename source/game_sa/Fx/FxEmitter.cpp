#include "StdInc.h"

#include "FxEmitter.h"
#include "EmissionInfo.h"
#include "FxEmitterPrt.h"
#include "FxPrimBP.h"
#include "FxEmitterBP.h"
#include "FxPrtMult.h"

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
void FxEmitter_c::Update(float currentTime, float mult) { Update_Reversed(currentTime, mult); }
void FxEmitter_c::Reset() { Reset_Reversed(); }
void FxEmitter_c::AddParticle(RwMatrix* mat, CVector* direction, float a4, FxPrtMult_c* prtMult, float a6, float a7, bool bLocalParticles) { AddParticle_Reversed(mat, direction, a4, prtMult, a6, a7, bLocalParticles); }
void FxEmitter_c::AddParticle(CVector* pos, CVector* direction, float a4, FxPrtMult_c* prtMult, float a6, float a7, bool bLocalParticles) { AddParticle_Reversed(pos, direction, a4, prtMult, a6, a7, bLocalParticles); }

// 0x4A2550
bool FxEmitter_c::Init_Reversed(FxPrimBP_c* primBP, FxSystem_c* system) {
    m_PrimBP             = primBP;
    m_System             = system;
    m_fEmissionIntensity = 0.0f;
    return true;
}

// 0x4A4460
void FxEmitter_c::Update_Reversed(float currentTime, float mult) {
    if (m_bEnabled && !m_System->m_bUnknown4) {
        CreateParticles(currentTime, mult);
    }
}

// 0x4A2570
void FxEmitter_c::Reset_Reversed() {
    m_fEmissionIntensity = 0.0f;
}

// 0x4A3EA0
void FxEmitter_c::AddParticle_Reversed(CVector* pos, CVector* direction, float a4, FxPrtMult_c* prtMult, float a6, float a7, bool bLocalParticles) {
    return plugin::CallMethod<0x4A3EA0, FxEmitter_c*, CVector*, CVector*, float, FxPrtMult_c*, float, float, bool>(this, pos, direction, a4, prtMult, a6, a7, bLocalParticles);

    // todo:
    EmissionInfo_t emission;
    m_PrimBP->m_FxInfoManager.ProcessEmissionInfo(0.0f, 0.0f, m_System->m_SystemBP->m_fLength, m_System->m_bConstTimeSet, &emission);

    auto mat1 = g_fxMan.FxRwMatrixCreate();
    auto mat0 = g_fxMan.FxRwMatrixCreate();
    auto mat  = g_fxMan.FxRwMatrixCreate();

    RwMatrixSetIdentity(mat);
    RwV3dAssign(RwMatrixGetPos(mat), pos);

    RwMatrixUpdate(mat);
    if (m_System->m_pParentMatrix) {
        RwMatrixMultiply(mat0, mat, m_System->m_pParentMatrix);
    }
    else {
        mat0 = mat;
    }

    auto mat2 = g_fxMan.FxRwMatrixCreate();
    m_PrimBP->GetRWMatrix(mat2);
    RwMatrixMultiply(mat1, mat2, mat0);
    g_fxMan.FxRwMatrixDestroy(mat2);

    if (auto* particle = CreateParticle(&emission, mat1, direction, a4, prtMult, a7, bLocalParticles)) {
        if (a6 >= 0.0f) {
            particle->field_36 = (uint8)(a6 / 2.0f); // todo: int8/uint8 conversion
        }
    }

    g_fxMan.FxRwMatrixDestroy(mat);
    g_fxMan.FxRwMatrixDestroy(mat0);
    g_fxMan.FxRwMatrixDestroy(mat1);
}

// 0x4A4050
void FxEmitter_c::AddParticle_Reversed(RwMatrix* mat, CVector* direction, float a4, FxPrtMult_c* prtMult, float a6, float a7, bool bLocalParticles) {
    return plugin::CallMethod<0x4A4050, FxEmitter_c*, RwMatrix*, CVector*, float, FxPrtMult_c*, float, float, bool>(this, mat, direction, a4, prtMult, a6, a7, bLocalParticles);

    // todo:
    EmissionInfo_t emission;
    m_PrimBP->m_FxInfoManager.ProcessEmissionInfo(0.0f, 0.0f, m_System->m_SystemBP->m_fLength, m_System->m_bConstTimeSet, &emission);
    auto mat2 = g_fxMan.FxRwMatrixCreate();
    auto mat1 = g_fxMan.FxRwMatrixCreate();
    auto mat0 = g_fxMan.FxRwMatrixCreate();
    RwMatrixSetIdentity(mat0);
    mat0 = mat;

    RwMatrixUpdate(mat0);
    if (m_System->m_pParentMatrix) {
        RwMatrixMultiply(mat1, mat0, m_System->m_pParentMatrix);
    } else {
        mat1 = mat0;
    }

    auto mat3 = g_fxMan.FxRwMatrixCreate();
    m_PrimBP->GetRWMatrix(mat3);
    RwMatrixMultiply(mat2, mat3, mat1);
    g_fxMan.FxRwMatrixDestroy(mat3);

    if (auto* particle = CreateParticle(&emission, mat2, direction, a4, prtMult, a7, bLocalParticles)) {
        if (a6 >= 0.0f)
            particle->field_36 = (uint8)(a6 * 2.0f); // todo:: see above
    }

    g_fxMan.FxRwMatrixDestroy(mat0);
    g_fxMan.FxRwMatrixDestroy(mat1);
    g_fxMan.FxRwMatrixDestroy(mat2);
}

// 0x4A41E0
void FxEmitter_c::CreateParticles(float currentTime, float mult) {
    return plugin::CallMethod<0x4A41E0, FxEmitter_c*, float, float>(this, currentTime, mult);

    EmissionInfo_t emission;
    m_PrimBP->m_FxInfoManager.ProcessEmissionInfo(currentTime, mult, m_System->m_SystemBP->m_fLength, m_System->m_bConstTimeSet, &emission);

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

    m_fEmissionIntensity += emission.m_fRate * visibility * ((float)m_System->m_nRateMult * 1000.0f);
    if (   CWeather::Wind >= emission.m_fMinWind
        && CWeather::Wind <= emission.m_fMaxWind
        && CWeather::Rain >= emission.m_fMinRain
        && CWeather::Rain <= emission.m_fMaxRain
        && m_fEmissionIntensity >= 1.0f
    ) {
        auto mat = g_fxMan.FxRwMatrixCreate();
        auto mat1 = g_fxMan.FxRwMatrixCreate();
        RwMatrixUpdate(&m_System->m_LocalMatrix);
        if (m_System->m_pParentMatrix) {
            RwMatrixMultiply(mat1, &m_System->m_LocalMatrix, m_System->m_pParentMatrix);
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
            auto a5 = (float)step / m_fEmissionIntensity * mult;
            CreateParticle(&emission, mat, nullptr, a5, &prtMult, 1.2f, m_System->m_bLocalParticles);
            counter++;
        }
        m_fEmissionIntensity -= m_fEmissionIntensity;

        g_fxMan.FxRwMatrixDestroy(mat1);
        g_fxMan.FxRwMatrixDestroy(mat);
    }
}

// 0x4A2580
FxEmitterPrt_c* FxEmitter_c::CreateParticle(EmissionInfo_t* emission, RwMatrix* transformMatrix, CVector* direction, float a5, FxPrtMult_c* prtMult, float a7, bool bLocalParticles) {
    return plugin::CallMethodAndReturn<FxEmitterPrt_c*, 0x4A2580, FxEmitter_c*, EmissionInfo_t*, RwMatrix*, CVector*, float, FxPrtMult_c*, float, bool>(this, emission, transformMatrix, direction, a5, prtMult, a7, bLocalParticles);

    // todo:
    auto* particle = g_fxMan.GetParticle(0);
    if (!particle && !(m_System->m_bMustCreateParticles && (g_fxMan.FreeUpParticle(), (particle = g_fxMan.GetParticle(0)) != nullptr)))
        return particle;

    particle->m_fCurrentLife = 0.0f;
    particle->m_fTotalLife = (((float)(CGeneral::GetRandomNumber() % 10000) / 5000.0f - 1.0f) * emission->m_fLifeBias + emission->m_fLife) * prtMult->m_fLife;
    particle->m_System = m_System;

    particle->m_Color.red   = (uint8)(prtMult->m_Color.red * 255.0f);
    particle->m_Color.green = (uint8)(prtMult->m_Color.green * 255.0f);
    particle->m_Color.blue  = (uint8)(prtMult->m_Color.blue * 255.0f);
    particle->m_Color.alpha = (uint8)(prtMult->m_Color.alpha * 255.0f);

    particle->m_nSize = (uint8)(prtMult->m_fSize * 255.0f);
    particle->field_31 = (uint8)(prtMult->field_14 * 255.0f);

    particle->m_bLocalParticles = bLocalParticles;

    particle->field_32 = (uint8)((float)(CGeneral::GetRandomNumber() % 10000) / 10000.0f * 255.0f);
    particle->field_33 = (uint8)((float)(CGeneral::GetRandomNumber() % 10000) / 10000.0f * 255.0f);
    particle->field_34 = (uint8)((float)(CGeneral::GetRandomNumber() % 10000) / 10000.0f * 255.0f);
    particle->field_35 = (uint8)(a7 * 100.0f);

    particle->field_36 = -1;
    particle->m_fRotation =
        (float)(CGeneral::GetRandomNumber() % 10000) / 10000.0f * (emission->m_fRotationMaxAngle - emission->m_fRotationMinAngle) + emission->m_fRotationMinAngle;

    if (bLocalParticles) {
        m_PrimBP->GetRWMatrix(transformMatrix);
    }

    CVector vec;
    if (std::fabs(emission->m_fRadius) < 0.001000000047497451) { //
        vec = CVector{
            (float)(CGeneral::GetRandomNumber() % 10000) / 10000.0f * (emission->m_Max.x - emission->m_Min.x) + emission->m_Min.x,
            (float)(CGeneral::GetRandomNumber() % 10000) / 10000.0f * (emission->m_Max.y - emission->m_Min.y) + emission->m_Min.y,
            (float)(CGeneral::GetRandomNumber() % 10000) / 10000.0f * (emission->m_Max.z - emission->m_Min.z) + emission->m_Min.z,
        };
    } else {
        vec = CVector{
            (float)(CGeneral::GetRandomNumber() % 10000) / 5000.0f - 1.0f,
            (float)(CGeneral::GetRandomNumber() % 10000) / 5000.0f - 1.0f,
            (float)(CGeneral::GetRandomNumber() % 10000) / 5000.0f - 1.0f,
        };

        float radius;
        auto invDist = 1.0f / vec.Magnitude();
        if (emission->m_fRadius < 0.0f) { // todo: check comp.
            radius = invDist * emission->m_fRadius;
        } else {
            radius = (invDist * (float)(CGeneral::GetRandomNumber() % 10000) / 10000.0f) * emission->m_fRadius;
        }
        vec *= radius;
    }
    vec += emission->m_0x44;

    particle->m_WaterPos = vec.z * transformMatrix->at + vec.y * transformMatrix->up + vec.x * transformMatrix->right + transformMatrix->pos;

    if (direction) {
        particle->m_f1C = *direction;
    } else {
        auto index = (float)(CGeneral::GetRandomNumber() % 10000) / 10000.0f * TWO_PI;
        auto minAngle = DegreesToRadians(emission->m_fAngleMin);
        auto maxAngle = DegreesToRadians(emission->m_fAngleMax);

        auto sinY = ((float)(CGeneral::GetRandomNumber() % 10000) / 10000.0f * (maxAngle - minAngle) + minAngle) * 40.743664;

        CVector v37;
        v37.x = CMaths::ms_SinTable[(uint8)((index * 40.743664f) + 64.0f) + 1] * CMaths::ms_SinTable[(uint8)sinY + 1];
        v37.y = CMaths::ms_SinTable[(uint8)(sinY + 64.0f) + 1];
        v37.z = CMaths::ms_SinTable[(uint8)(index * 40.743664f) + 1] * CMaths::ms_SinTable[(uint8)sinY + 1];

        CVector vectorsIn;
        CVector vectorsOut;
        if (emission->m_0x28.x <= 10.0f) {
            vectorsIn = emission->m_0x28;
            vectorsIn.Normalise();
        } else {
            vectorsIn = particle->m_WaterPos;
        }
        RwV3dTransformVectors(&vectorsOut, &vectorsIn, 1, transformMatrix);
        CVector v38;
        RotateVecIntoVec(&v38, &v37, &vectorsOut);
        particle->m_f1C = v38 * (((float)(CGeneral::GetRandomNumber() % 10000) / 5000.0f - 1.0f) * emission->m_fSpeedBias + emission->m_fSpeed);
    }

    particle->m_f1C += m_System->m_vecVelAdd;
    static_cast<FxEmitterBP_c*>(m_PrimBP)->UpdateParticle(a5, particle);
    m_PrimBP->m_Particles.AddItem(particle);

    return particle;
}
