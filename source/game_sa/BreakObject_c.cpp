#include "StdInc.h"

#include "BreakObject_c.h"

void BreakObject_c::InjectHooks() {
    RH_ScopedClass(BreakObject_c);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(CalcGroupCenter, 0x59D190);
    RH_ScopedInstall(SetGroupData, 0x59D570);
    //RH_ScopedInstall(SetBreakInfo, 0x59D7F0);
    RH_ScopedInstall(Exit, 0x59DDD0);
    //RH_ScopedInstall(DoCollisionResponse, 0x59DE40);
    //RH_ScopedInstall(DoCollision, 0x59E1F0);
    //RH_ScopedInstall(Update, 0x59E220);
    //RH_ScopedInstall(Render, 0x59E480);
    RH_ScopedInstall(Init, 0x59E750);
}

// 0x59D170
BreakObject_c::BreakObject_c() {
    m_JustFaces = false;
    m_bActive = false;
    m_BreakGroup = nullptr;
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
    if (m_BreakGroup) {
        for (auto i = 0; i < m_NumBreakGroups; ++i) {
            if (m_BreakGroup[i].m_Texture) {
                RwTextureDestroy(m_BreakGroup[i].m_Texture);
                m_BreakGroup[i].m_Texture = 0;
            }

            if (m_BreakGroup[i].m_RenderInfo)
                delete m_BreakGroup[i].m_RenderInfo;
        }

        delete[] m_BreakGroup;
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
                group->m_LongestSide = height * 0.5;
            }
        } else {
            group->m_Type = 1;
            group->m_LongestSide = width * 0.5;
        }
    } else {
        group->m_Type = 0;
        group->m_LongestSide = length * 0.5;
    }
}

// 0x59D570
void BreakObject_c::SetGroupData(RwMatrix* matrix, RwV3d* vecVelocity, float fVelocityRand) {
    for (int i = 0; i < m_NumBreakGroups; ++i) {
        auto& group = m_BreakGroup[i];
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
    plugin::CallMethod<0x59D7F0, BreakObject_c*, BreakInfo_t*, int32>(this, info, bJustFaces);
}

// 0x59DE40
void BreakObject_c::DoCollisionResponse(BreakGroup_t* group, float timeStep, RwV3d* vecNormal, float groundZ) {
    plugin::CallMethod<0x59DE40, BreakObject_c*, BreakGroup_t*, float, RwV3d*, float>(this, group, timeStep, vecNormal, groundZ);
}

// 0x59E1F0
void BreakObject_c::DoCollision(BreakGroup_t* group, float timeStep) {
    plugin::CallMethod<0x59E1F0, BreakObject_c*, BreakGroup_t*, float>(this, group, timeStep);
}

// 0x59E220
void BreakObject_c::Update(float timeStep) {
    plugin::CallMethod<0x59E220, BreakObject_c*, float>(this, timeStep);
}

// 0x59E480
void BreakObject_c::Render(bool isDrawLast) {
    plugin::CallMethod<0x59E480, BreakObject_c*>(this, isDrawLast);
}
