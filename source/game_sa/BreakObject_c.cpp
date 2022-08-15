#include "StdInc.h"

#include "BreakObject_c.h"
#include "PostEffects.h"

void BreakObject_c::InjectHooks() {
    RH_ScopedClass(BreakObject_c);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(CalcGroupCenter, 0x59D190);
    RH_ScopedInstall(SetGroupData, 0x59D570);
    RH_ScopedInstall(SetBreakInfo, 0x59D7F0);
    RH_ScopedInstall(Exit, 0x59DDD0);
    RH_ScopedInstall(DoCollisionResponse, 0x59DE40);
    RH_ScopedInstall(DoCollision, 0x59E1F0);
    //RH_ScopedInstall(Update, 0x59E220);
    //RH_ScopedInstall(Render, 0x59E480);
    RH_ScopedInstall(Init, 0x59E750);
}

// 0x59D170
BreakObject_c::BreakObject_c() {
    m_JustFaces = false;
    m_bActive = false;
    m_BreakGroups = nullptr;
}

// 0x59E750
bool BreakObject_c::Init(CObject* object, RwV3d* vecVelocity, float fVelocityRand, int32 bJustFaces) {
    if (!object->m_pRwObject)
        return false;

    if (RwObjectGetType(object->m_pRwObject) != rpATOMIC)
        return false;

    auto* info = BREAKABLEPLG(RpAtomicGetGeometry(object->m_pRwAtomic), m_pBreakableInfo);
    if (!info)
        return false;

    SetBreakInfo(info, bJustFaces);
    auto ltm = RwFrameGetLTM(RpAtomicGetFrame(object->m_pRwAtomic));
    SetGroupData(ltm, vecVelocity, fVelocityRand);

    m_JustFaces = bJustFaces;
    m_bActive = true;
    m_FramesActive = 0;
    m_AddSparks = object->m_pObjectInfo->m_nSparksOnImpact;
    m_bDrawLast = object->m_bDrawLast;

    CVector vecOrigin; 
    if (info->m_uiPosRule != eBreakablePluginPositionRule::OBJECT_ORIGIN) {
        auto* colModel = object->GetModelInfo()->GetColModel();
        auto usedPoint = colModel->GetBoundingBox().GetCenter();
        usedPoint.z += 0.25f;

        vecOrigin = *object->m_matrix * usedPoint;
    } else {
        auto* colModel = object->GetModelInfo()->GetColModel();
        vecOrigin = *RwMatrixGetPos(ltm);
        vecOrigin.z += colModel->GetBoundingBox().m_vecMin.z + 0.25f;
    }

    CColPoint colPoint;
    CEntity* colEntity;
    if (CWorld::ProcessVerticalLine(vecOrigin, -1000.0f, colPoint, colEntity, true)) {
        m_GroundZ = colPoint.m_vecPoint.z;
        m_VecNormal = colPoint.m_vecNormal;
        if (fabs(m_VecNormal.x) < 0.01f
            && fabs(m_VecNormal.y) < 0.01f
            && fabs(m_VecNormal.z) < 0.01f) {

            m_VecNormal.Set(0.0f, 0.0f, 1.0f);
        }
    } else {
        m_GroundZ = -1000.0f;
        m_VecNormal.Set(0.0f, 0.0f, 1.0f);
    }

    return true;
}

// 0x59DDD0
void BreakObject_c::Exit() {
    if (m_BreakGroups) {
        for (auto i = 0; i < m_NumBreakGroups; ++i) {
            if (m_BreakGroups[i].m_Texture) {
                RwTextureDestroy(m_BreakGroups[i].m_Texture);
                m_BreakGroups[i].m_Texture = 0;
            }

            if (m_BreakGroups[i].m_RenderInfo)
                delete m_BreakGroups[i].m_RenderInfo;
        }

        delete[] m_BreakGroups;
    }

    m_bActive = false;
}

// Methods
// 0x59D190
void BreakObject_c::CalcGroupCenter(BreakGroup_t* group) {
    CVector vecMin(9999999.0f, 9999999.0f, 9999999.0f);
    CVector vecMax(-9999999.0f, -9999999.0f, -9999999.0f);

    for (auto i = 0; i < group->m_NumTriangles; ++i) {
        auto& info = group->m_RenderInfo[i];
        for (auto posInd = 0; posInd < 3; ++posInd) {
            vecMin.x = std::min(vecMin.x, info.positions[posInd].x);
            vecMax.x = std::max(vecMax.x, info.positions[posInd].x);
            vecMin.y = std::min(vecMin.y, info.positions[posInd].y);
            vecMax.y = std::max(vecMax.y, info.positions[posInd].y);
            vecMin.z = std::min(vecMin.z, info.positions[posInd].z);
            vecMax.z = std::max(vecMax.z, info.positions[posInd].z);
        }
    }

    auto vecCenter = (vecMax + vecMin) / 2.0f;
    for (auto i = 0; i < group->m_NumTriangles; ++i) {
        auto& info = group->m_RenderInfo[i];
        for (auto posInd = 0; posInd < 3; ++posInd)
            info.positions[posInd] -= vecCenter;
    }

    vecMin -= vecCenter;
    vecMax -= vecCenter;

    RwV3d vecTransformedCenter;
    RwV3dTransformVector(&vecTransformedCenter, &vecCenter, &group->m_Matrix);
    auto* pos = RwMatrixGetPos(&group->m_Matrix);
    pos->x += vecTransformedCenter.x;
    pos->y += vecTransformedCenter.y;
    pos->z += vecTransformedCenter.z;

    auto length = vecMax.x - vecMin.x;
    auto width = vecMax.y - vecMin.y;
    auto height = vecMax.z - vecMin.z;

    if (length > width || length > height) {
        if (width > length || width > height) {
            if (height <= width && height <= (double)length) {
                group->m_Type = 2;
                group->m_BoundingSize = height * 0.5f;
            }
        } else {
            group->m_Type = 1;
            group->m_BoundingSize = width * 0.5f;
        }
    } else {
        group->m_Type = 0;
        group->m_BoundingSize = length * 0.5f;
    }
}

// 0x59D570
void BreakObject_c::SetGroupData(RwMatrix* matrix, RwV3d* vecVelocity, float fVelocityRand) {
    for (int i = 0; i < m_NumBreakGroups; ++i) {
        auto& group = m_BreakGroups[i];
        group.m_Matrix = *matrix;

        CalcGroupCenter(&group);

        if (vecVelocity) {
            group.m_Velocity = *vecVelocity;
            if (fVelocityRand != 0.0f) {
                group.m_Velocity.x += CGeneral::GetRandomNumberInRange(-fVelocityRand, fVelocityRand);
                group.m_Velocity.y += CGeneral::GetRandomNumberInRange(-fVelocityRand, fVelocityRand);
                group.m_Velocity.z += CGeneral::GetRandomNumberInRange(-fVelocityRand, fVelocityRand);
            }
        } else {
            group.m_Velocity.x = CGeneral::GetRandomNumberInRange(-fVelocityRand, fVelocityRand);
            group.m_Velocity.y = CGeneral::GetRandomNumberInRange(-fVelocityRand, fVelocityRand);
            group.m_Velocity.z = CGeneral::GetRandomNumberInRange(-fVelocityRand, fVelocityRand);
        }

        group.m_RotationSpeed = CGeneral::GetRandomNumberInRange(3.0f, 6.0f);

        group.m_RotationAxis.x = CGeneral::GetRandomNumberInRange(-1.0f, 1.0f);
        group.m_RotationAxis.y = CGeneral::GetRandomNumberInRange(-1.0f, 1.0f);
        group.m_RotationAxis.z = CGeneral::GetRandomNumberInRange(-1.0f, 1.0f);
        RwV3dNormalize(&group.m_RotationAxis, &group.m_RotationAxis);

        group.m_bStoppedMoving = 0;
    }
}

// 0x59D7F0
void BreakObject_c::SetBreakInfo(BreakInfo_t* info, int32 bJustFaces) {
    static float& ambientRed = *(float*)0x8D0A0C;    // TODO | STATICREF // = 32.0f;
    static float& ambientGreen = *(float*)0x8D0A08;  // TODO | STATICREF // = 32.0f;
    static float& ambientBlue = *(float*)0x8D0A04;   // TODO | STATICREF // = 32.0f;

    if (bJustFaces)
        m_NumBreakGroups = info->m_usNumTriangles;
    else
        m_NumBreakGroups = info->m_usNumMaterials;

    m_BreakGroups = new BreakGroup_t[m_NumBreakGroups];

    for (auto i = 0; i < m_NumBreakGroups; ++i) {
        auto& group = m_BreakGroups[i];
        group.m_NumTriangles = 0;
        group.m_Texture = nullptr;

        auto numMaterials = 0u;
        if (bJustFaces)
            numMaterials = 1u;
        else {
            auto* pIndice = info->m_pTrianglesMaterialIndices;
            for (auto triInd = 0; triInd < info->m_usNumTriangles; ++triInd) {
                if (*pIndice == i)
                    ++numMaterials;

                ++pIndice;
            }
        }

        group.m_RenderInfo = new BreakGroupRenderInfo_t[numMaterials];
        group.m_FramesToLive = 256 + CGeneral::GetRandomNumberInRange(0, 32);
    }

    for (auto i = 0; i < info->m_usNumTriangles; ++i) {
        auto curIndice = i;
        if (!bJustFaces)
            curIndice = info->m_pTrianglesMaterialIndices[curIndice];

        auto& triangle = info->m_pTriangles[i];
        auto& group = m_BreakGroups[curIndice];
        // BUG: (?) Compiler shows that invalid access can happen in next line, possibly something wrong with reversed code
        auto& curRenderInfo = group.m_RenderInfo[group.m_NumTriangles];
        for (auto ind = 0; ind < 3; ++ind)
            curRenderInfo.positions[ind] = info->m_pVertexPos[triangle.vertIndex[ind]];

        auto textureInd = bJustFaces ? info->m_pTrianglesMaterialIndices[i] : curIndice;
        group.m_Texture = info->m_pTextures[textureInd];

        auto& matColor = info->m_pMaterialProperties[textureInd];
        if (!CPostEffects::IsVisionFXActive()) {
            ambientRed = AmbientLightColourForFrame.red * 255.0f;
            ambientGreen = AmbientLightColourForFrame.green * 255.0f;
            ambientBlue = AmbientLightColourForFrame.blue * 255.0f;
        }

        for (auto ind = 0; ind < 3; ++ind) {
            auto& vertColor = info->m_pVertexColors[triangle.vertIndex[ind]];
            auto fRed = std::min(255.0f, vertColor.red * matColor.red + ambientRed);
            auto fGreen = std::min(255.0f, vertColor.green * matColor.green + ambientGreen);
            auto fBlue = std::min(255.0f, vertColor.blue * matColor.blue + ambientBlue);

            curRenderInfo.colors[ind].Set(fRed, fGreen, fBlue);
            curRenderInfo.texCoords[ind] = info->m_pTexCoors[triangle.vertIndex[ind]];
        }

        ++group.m_NumTriangles;
    }

    for (auto i = 0; i < m_NumBreakGroups; ++i) {
        auto& group = m_BreakGroups[i];
        if (group.m_Texture)
            ++group.m_Texture->refCount;
    }
}

// 0x59DE40
void BreakObject_c::DoCollisionResponse(BreakGroup_t* group, float timeStep, RwV3d* vecNormal, float groundZ) {
    static float& dotMultiplier = *(float*)0x8D0A18; // TODO | STATICREF // = 0.85f;
    static float& timestepScaling = *(float*)0x8D0A14; // TODO | STATICREF // = 0.05f;
    static float& velocityScaling = *(float*)0x8D0A10; // TODO | STATICREF // = 0.8f;

    auto dotProd = RwV3dDotProduct(&group->m_Velocity, vecNormal) * dotMultiplier;
    RwV3d newVelocity, velocityChange;
    RwV3dAssign(&velocityChange, vecNormal);
    RwV3dScale(&velocityChange, &velocityChange, dotProd * 2);

    RwV3dAssign(&newVelocity, &group->m_Velocity);
    RwV3dSub(&newVelocity, &newVelocity, &velocityChange);

    auto fTimeScale = timeStep * timestepScaling;
    RwV3d vecRand;
    vecRand.x = CGeneral::GetRandomNumberInRange(-1.0f, 1.0f);
    vecRand.y = CGeneral::GetRandomNumberInRange(-1.0f, 1.0f);
    vecRand.z = CGeneral::GetRandomNumberInRange(-1.0f, 1.0f);
    RwV3dNormalize(&vecRand, &vecRand);
    RwV3dScale(&vecRand, &vecRand, fTimeScale);

    auto fOriginalVelocityScale = RwV3dLength(&newVelocity);
    RwV3dAdd(&newVelocity, &newVelocity, &vecRand);
    RwV3dNormalize(&newVelocity, &newVelocity);
    RwV3dScale(&newVelocity, &newVelocity, fOriginalVelocityScale);
    RwV3dScale(&newVelocity, &newVelocity, velocityScaling);

    group->m_RotationSpeed = 0.0f;
    RwV3dAssign(&group->m_Velocity, &newVelocity);
    RwMatrixGetPos(&group->m_Matrix)->z = groundZ + group->m_BoundingSize;

    if (fOriginalVelocityScale >= 0.05f) {
        if (m_JustFaces)
            return;
    } else {
        group->m_bStoppedMoving = true;
        if (m_JustFaces) {
            group->m_FramesToLive = 32 + CGeneral::GetRandomNumberInRange(0, 32);
            return;
        }
    }

    auto particle = FxPrtMult_c(1.0f, 1.0f, 1.0f, 0.1f, 0.3f, 0.0f, 0.15f);
    auto* groupPos = RwMatrixGetPos(&group->m_Matrix);
    for (auto i = 0; i < 4; ++i) {
        RwV3d particlePos, particleVelocity;
        RwV3dAssign(&particlePos, groupPos);
        particlePos.x += CGeneral::GetRandomNumberInRange(-0.5f, 0.5f);
        particlePos.y += CGeneral::GetRandomNumberInRange(-0.5f, 0.5f);

        particleVelocity.x = CGeneral::GetRandomNumberInRange(-0.15f, 0.15f);
        particleVelocity.y = CGeneral::GetRandomNumberInRange(-0.15f, 0.15f);
        particleVelocity.z = 0.0f;

        g_fx.m_SmokeII3expand->AddParticle(&particlePos, &particleVelocity, 0.0f, &particle, -1.0f, 1.2f, 0.6f, 0);
    }

    if (m_AddSparks) {
        auto fSpeed = RwV3dLength(&group->m_Velocity);
        RwV3d particlePos, particleVelocity;
        RwV3dAssign(&particlePos, groupPos);
        particleVelocity.x = 0.0f;
        particleVelocity.y = 0.0f;
        particleVelocity.z = 1.0f;

        //TODO: (?) Fx_c methods originally take in RwV3d instead of CVectors, as the debug symbols show
        g_fx.AddSparks(*reinterpret_cast<CVector*>(&particlePos),
            *reinterpret_cast<CVector*>(&particleVelocity),
            2.0f,
            static_cast<int32>(fSpeed * 100.0f),
            CVector(0.0f, 0.0f, 0.0f),
            eSparkType::SPARK_PARTICLE_SPARK,
            0.4f,
            1.0f);
    }
}

// 0x59E1F0
void BreakObject_c::DoCollision(BreakGroup_t* group, float timeStep) {
    if (RwMatrixGetPos(&group->m_Matrix)->z - group->m_BoundingSize < m_GroundZ)
        DoCollisionResponse(group, timeStep, &m_VecNormal, m_GroundZ);
}

// 0x59E220
void BreakObject_c::Update(float timeStep) {
    plugin::CallMethod<0x59E220, BreakObject_c*, float>(this, timeStep);
}

// 0x59E480
void BreakObject_c::Render(bool isDrawLast) {
    plugin::CallMethod<0x59E480, BreakObject_c*>(this, isDrawLast);
}
