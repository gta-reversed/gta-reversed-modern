#include "StdInc.h"

CBulletTrace(&CBulletTraces::aTraces)[16] = *(CBulletTrace(*)[16])0xC7C748;

void CBulletTraces::InjectHooks()
{
    ReversibleHooks::Install("CBulletTraces", "Init", 0x721D50, &CBulletTraces::Init);
    ReversibleHooks::Install("CBulletTraces", "AddTrace", 0x723750, static_cast<void(*)(const CVector&, const CVector&, float, uint32_t, uint8_t)>(&CBulletTraces::AddTrace));
    ReversibleHooks::Install("CBulletTraces", "Render", 0x723C10, &CBulletTraces::Render);
    ReversibleHooks::Install("CBulletTraces", "Update", 0x723FB0, &CBulletTraces::Update);
    ReversibleHooks::Install("CBulletTraces", "AddTrace_Wrapper", 0x726AF0, static_cast<void(*)(const CVector&, const CVector&, eWeaponType, CEntity*)>(&CBulletTraces::AddTrace));
}

// 0x721D50
void CBulletTraces::Init()
{
    for (auto& trace : aTraces) {
        trace.m_bExists = false;
    }
}

CBulletTrace* CBulletTraces::GetFree() {
    for (auto& trace : aTraces) {
        if (!trace.m_bExists) {
            return &trace;
        }
    }
    return nullptr;
}

// 0x723750
void CBulletTraces::AddTrace(const CVector& from, const CVector& to, float radius, uint32_t dissapearTime, uint8_t alpha)
{
    if (CBulletTrace* pTrace = GetFree()) {
        pTrace->m_vecStart = from;
        pTrace->m_vecEnd = to;
        pTrace->m_nCreationTime = CTimer::m_snTimeInMilliseconds;
        pTrace->m_nTransparency = alpha;
        pTrace->m_bExists = true;
        pTrace->m_fRadius = radius;

        // Determinate lifetime based on index in aTraces array
        // (Probably done to keep the amount of traces as low as possible)
        const auto traceIdx = GetTraceIndex(pTrace);
        if (traceIdx < 10) {
            pTrace->m_nLifeTime = (uint32_t)(traceIdx < 5 ? dissapearTime : dissapearTime / 2.0f);
        } else {
            pTrace->m_nLifeTime = (uint32_t)(dissapearTime / 4.0f);
        }
    }
    // Play sound front-end

    const CVector camPos = TheCamera.GetPosition();

    const float fromCamDir_Dot_CamRight = DotProduct(from - camPos, TheCamera.GetMatrix().GetRight());
    const float fromCamDir_Dot_CamUp = DotProduct(from - camPos, TheCamera.GetMatrix().GetUp());
    const float fromCamDir_Dot_CamFwd = DotProduct(from - camPos, TheCamera.GetMatrix().GetForward());

    const float toCamDir_Dot_CamRight = DotProduct(to - camPos, TheCamera.GetMatrix().GetRight());
    const float toCamDir_Dot_CamFwd = DotProduct(to - camPos, TheCamera.GetMatrix().GetForward());

    if (toCamDir_Dot_CamFwd * fromCamDir_Dot_CamFwd < 0.0f) {
        const float absFromCamDir_Dot_CamFwd = fabs(fromCamDir_Dot_CamFwd);
        const float absToCamDir_Dot_CamFwd = fabs(toCamDir_Dot_CamFwd);

        const float v43 = absFromCamDir_Dot_CamFwd / (absFromCamDir_Dot_CamFwd + absToCamDir_Dot_CamFwd);
        const float v51 = DotProduct(to - camPos, TheCamera.GetMatrix().GetUp()) - fromCamDir_Dot_CamUp;
        const float v52 = v51 * v43;
        const float v44 = (toCamDir_Dot_CamRight - fromCamDir_Dot_CamRight) * v43 + fromCamDir_Dot_CamRight;
        const float v42 = CVector2D{ v52 + fromCamDir_Dot_CamUp, v44 }.Magnitude(); // Originally uses sqrt and stuff, but this is cleaner

        if (v42 < 2.0f) {
            const float v45 = 1.0f - v42 * 0.5f;
            const auto ReportFrontEndAudioEvent = [&](auto event) {
                const float volumeChange = v45 == 0.0f ? -100.0f : std::log10(v45);
                AudioEngine.ReportFrontendAudioEvent(event, volumeChange, 1.0f);
            };
            if (v45 != 0.0f) {
                if (fromCamDir_Dot_CamFwd <= 0.0f) {
                    ReportFrontEndAudioEvent(AE_FRONTEND_BULLET_PASS_RIGHT_REAR);
                } else {
                    ReportFrontEndAudioEvent(AE_FRONTEND_BULLET_PASS_RIGHT_FRONT);
                }
            } else {
                if (fromCamDir_Dot_CamFwd <= 0.0f) {
                    ReportFrontEndAudioEvent(AE_FRONTEND_BULLET_PASS_LEFT_REAR);
                } else {
                    ReportFrontEndAudioEvent(AE_FRONTEND_BULLET_PASS_LEFT_FRONT);
                }
            }
        }
    }
}

// 0x723C10
void CBulletTraces::Render()
{
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void*)FALSE);
    RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)RwBlendFunction::rwBLENDSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)RwBlendFunction::rwBLENDINVSRCALPHA);
    RwRenderStateSet(rwRENDERSTATECULLMODE, (void*)RwCullMode::rwCULLMODECULLNONE);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)TRUE);
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void*)NULL);

    RxObjSpace3DVertex verts[6];
    for (auto& trace : aTraces) {
        if (!trace.m_bExists)
            continue;

        // Visualization of how this stuff works:
        // https://discord.com/channels/479682870047408139/670955312496246784/872593057726496788
        // Or if the above link is dead: https://imgur.com/a/2hWCyS8

        CVector startToCamDirNorm = trace.m_vecStart - TheCamera.GetPosition();
        startToCamDirNorm.Normalise();

        CVector traceDirNorm = trace.GetDirection();
        const float traceLength = traceDirNorm.NormaliseAndMag();

        const float invertedLifetimeProgress = 1.0f - (float)trace.GetRemainingLifetime() / (float)trace.m_nLifeTime;
        const float fSphereRadius = invertedLifetimeProgress * trace.m_fRadius;

        // Imagine a sphere.
        // This vector right here goes from the center of that sphere towards the surface
        // of the sphere.
        CVector sphereSurfaceDir = CrossProduct(startToCamDirNorm, traceDirNorm);
        sphereSurfaceDir.Normalise();

        // The point on the surface of the sphere which has a radius of `fCurrRadius`
        const CVector pointOnSuraceOfRadiusSphere = sphereSurfaceDir * fSphereRadius;

        // Current position on the trace
        const CVector currPosOnTrace = trace.m_vecEnd - trace.GetDirection() * invertedLifetimeProgress;

        // Set vertex positions
        const CVector vertPositions[std::size(verts)] = {
            currPosOnTrace,
            currPosOnTrace + pointOnSuraceOfRadiusSphere,
            currPosOnTrace - pointOnSuraceOfRadiusSphere,

            trace.m_vecEnd,
            trace.m_vecEnd + pointOnSuraceOfRadiusSphere,
            trace.m_vecEnd - pointOnSuraceOfRadiusSphere,
        };

        for (auto i = 0; i < std::size(verts); i++) {
            const CVector& pos = vertPositions[i];
            RwIm3DVertexSetPos(&verts[i], pos.x, pos.y, pos.z);
        }
        
        // Set colors
        for (auto& vert : verts)
            RwIm3DVertexSetRGBA(&vert, 255, 255, 128, 0);
        RwIm3DVertexSetRGBA(&verts[3], 255, 255, 128, (char)(invertedLifetimeProgress * trace.m_nTransparency)); // Only vertex 3 has non-zero alpha

        if (RwIm3DTransform(verts, std::size(verts), nullptr, rwIM3D_VERTEXRGBA)) {
            RwImVertexIndex indices[] = {
                // Each row represents a triangle
                4, 1, 3,
                1, 0, 3,
                0, 2, 3,
                3, 2, 5
            };
            RwIm3DRenderIndexedPrimitive(RwPrimitiveType::rwPRIMTYPETRILIST, indices, std::size(indices));
            RwIm3DEnd();
        }
    }

    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void*)TRUE);
    RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)RwBlendFunction::rwBLENDSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)RwBlendFunction::rwBLENDINVSRCALPHA);
    RwRenderStateSet(rwRENDERSTATECULLMODE, (void*)RwCullMode::rwCULLMODECULLBACK);
}

// 0x723FB0
void CBulletTraces::Update()
{
    for (auto& trace : aTraces) {
        trace.Update();
    }
}

// 0x726AF0
void CBulletTraces::AddTrace(const CVector& posMuzzle, const CVector& posBulletHit, eWeaponType weaponType, CEntity* pFromEntity)
{
    if (FindPlayerPed() == pFromEntity || FindPlayerVehicle() && FindPlayerVehicle() == pFromEntity) {
        switch (CCamera::GetActiveCamera().m_nMode) {
        case MODE_M16_1STPERSON:
        case MODE_SNIPER:
        case MODE_CAMERA:
        case MODE_ROCKETLAUNCHER:
        case MODE_ROCKETLAUNCHER_HS:
        case MODE_M16_1STPERSON_RUNABOUT:
        case MODE_SNIPER_RUNABOUT:
        case MODE_ROCKETLAUNCHER_RUNABOUT:
        case MODE_ROCKETLAUNCHER_RUNABOUT_HS:
        case MODE_HELICANNON_1STPERSON: {
            if (FindPlayerEntity()->AsPhysical()->m_vecMoveSpeed.Magnitude() < 0.05f) {
                return;
            }
        }
        }
    }
    
    CVector dir = posBulletHit - posMuzzle;
    const float traceLengthOriginal = dir.Magnitude();
    dir.Normalise();

    const float traceLengthNew = CGeneral::GetRandomNumberInRange(0.0f, traceLengthOriginal);
    const CVector from = posMuzzle + dir * traceLengthNew;
    const float fRadius = std::min(CGeneral::GetRandomNumberInRange(2.0f, 5.0f), traceLengthOriginal - traceLengthNew);
    AddTrace(
        from,
        from + dir * fRadius,
        0.01f,
        300u,
        70u
    );
}
