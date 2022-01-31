#include "StdInc.h"

char* (&CCutsceneObject::ms_sCutsceneVehNames)[NUM_CUTSCENE_VEHS] = *(char* (*)[NUM_CUTSCENE_VEHS])0x8D0F68;

void CCutsceneObject::InjectHooks()
{
    RH_ScopedClass(CCutsceneObject);
    RH_ScopedCategory("Entity/Object");

// VIRTUAL
    RH_ScopedInstall(SetModelIndex_Reversed, 0x5B1B20);
    RH_ScopedInstall(SetupLighting_Reversed, 0x553F40);
    RH_ScopedInstall(RemoveLighting_Reversed, 0x5533F0);
    RH_ScopedInstall(ProcessControl_Reversed, 0x5B1B90);
    RH_ScopedInstall(PreRender_Reversed, 0x5B1E00);

// HELPER
    RH_ScopedInstall(SetupCarPipeAtomicsForClump, 0x5B1AB0);
}

CCutsceneObject::CCutsceneObject() : CObject()
{
    m_vWorldPosition.Set(0.0F, 0.0F, 0.0F);
    m_vForce.Set(0.0F, 0.0F, 0.0F);
    m_bUsesCollision = false;
    m_nStatus = eEntityStatus::STATUS_SIMPLE;
    m_nObjectType = eObjectType::OBJECT_TYPE_CUTSCENE;
    m_nAttachBone = 0;
    m_pAttachmentObject = nullptr;
    m_bLightObject = true;
    m_bStreamingDontDelete = true;

    CObject::SetIsStatic(false);
    m_bBackfaceCulled = false;
    m_fContactSurfaceBrightness = 0.5F;
}

void CCutsceneObject::SetModelIndex(unsigned index)
{
    CCutsceneObject::SetModelIndex_Reversed(index);
}
void CCutsceneObject::SetModelIndex_Reversed(unsigned index)
{
    CEntity::SetModelIndex(index);
    if (RwObjectGetType(m_pRwObject) == rpCLUMP)
    {
        RpAnimBlendClumpInit(m_pRwClump);
        auto* pAnimData = RpClumpGetAnimBlendClumpData(m_pRwClump);
        pAnimData->velocity3d = &m_vecMoveSpeed;
        pAnimData->frames->m_bUpdateSkinnedWith3dVelocityExtraction = true;
        CCutsceneObject::SetupCarPipeAtomicsForClump(index, m_pRwClump);
    }
    CModelInfo::GetModelInfo(index)->m_nAlpha = 0xFF;
}

void CCutsceneObject::ProcessControl()
{
    CCutsceneObject::ProcessControl_Reversed();
}
void CCutsceneObject::ProcessControl_Reversed()
{
    if (m_nAttachBone && m_pAttachmentObject && !m_bWasPostponed)
    {
        m_bWasPostponed = true;
        return;
    }

    CPhysical::ProcessControl();
    if (m_pAttachTo)
    {
        if (m_pAttachmentObject)
        {
            auto* pHierarchy = GetAnimHierarchyFromClump(m_pAttachmentObject->m_pRwClump);
            auto* pMatArr = RpHAnimHierarchyGetMatrixArray(pHierarchy);
            const auto boneMat = CMatrix(&pMatArr[m_nAttachBone], false);
            *static_cast<CMatrix*>(m_matrix) = boneMat;
        }
        else
        {
            auto* pLtm = RwFrameGetLTM(m_pAttachTo);
            const auto attachMat = CMatrix(pLtm, false);
            *static_cast<CMatrix*>(m_matrix) = attachMat;
        }
    }
    else
    {
        if (CTimer::GetTimeStep() >= 0.01F)
            m_vecMoveSpeed *= 1.0F / CTimer::GetTimeStep();
        else
            m_vecMoveSpeed *= 100.0F;

        if (physicalFlags.bDontApplySpeed || physicalFlags.bDisableMoveForce)
            m_vecMoveSpeed.Set(0.0F, 0.0F, 0.0F);
        else
        {
            m_vForce += m_vecMoveSpeed * CTimer::GetTimeStep();
            m_matrix->SetTranslateOnly(m_vWorldPosition + m_vForce);
        }
    }
}

void CCutsceneObject::PreRender()
{
    CCutsceneObject::PreRender_Reversed();
}
void CCutsceneObject::PreRender_Reversed()
{
    if (m_pAttachTo)
    {
        if (m_pAttachmentObject)
        {
            auto* pHierarchy = GetAnimHierarchyFromClump(m_pAttachmentObject->m_pRwClump);
            auto* pMatArr = RpHAnimHierarchyGetMatrixArray(pHierarchy);
            const auto boneMat = CMatrix(&pMatArr[m_nAttachBone], false);
            *static_cast<CMatrix*>(m_matrix) = boneMat;
        }
        else
        {
            auto* pLtm = RwFrameGetLTM(m_pAttachTo);
            const auto attachMat = CMatrix(pLtm, false);
            *static_cast<CMatrix*>(m_matrix) = attachMat;
        }

        if (RwObjectGetType(m_pRwObject) == rpCLUMP)
        {
            const auto* pFirstAtomic = GetFirstAtomic(m_pRwClump);
            if (pFirstAtomic)
            {
                if (RpSkinGeometryGetSkin(RpAtomicGetGeometry(pFirstAtomic)))
                {
                    auto* pAnimData = RpClumpGetAnimBlendClumpData(m_pRwClump);
                    auto* pMorpthTarget = RpGeometryGetMorphTarget(RpAtomicGetGeometry(pFirstAtomic), 0);
                    auto* pSphere = RpMorphTargetGetBoundingSphere(pMorpthTarget);
                    pSphere->center = pAnimData->frames->m_pIFrame->translation;
                }
            }
        }
    }

    if (RwObjectGetType(m_pRwObject) == rpCLUMP)
        CEntity::UpdateRpHAnim();

    g_realTimeShadowMan.DoShadowThisFrame(this);
    if (!m_pShadowData)
    {
        CShadows::StoreShadowForPedObject(this,
                                          CTimeCycle::m_fShadowDisplacementX[CTimeCycle::m_CurrentStoredValue],
                                          CTimeCycle::m_fShadowDisplacementY[CTimeCycle::m_CurrentStoredValue],
                                          CTimeCycle::m_fShadowFrontX[CTimeCycle::m_CurrentStoredValue],
                                          CTimeCycle::m_fShadowFrontY[CTimeCycle::m_CurrentStoredValue],
                                          CTimeCycle::m_fShadowSideX[CTimeCycle::m_CurrentStoredValue],
                                          CTimeCycle::m_fShadowSideY[CTimeCycle::m_CurrentStoredValue]);
    }

    if (m_nModelIndex == eModelID::MODEL_CSPLAY)
    {
        CPed::ShoulderBoneRotation(m_pRwClump);
        m_bDontUpdateHierarchy = true;
    }

    CVector vecPos = GetPosition();
    vecPos.z += 0.5F;
    const auto fHeight = vecPos.z - 5.0F;
    CColPoint colPoint;
    CEntity* pEntity = nullptr;
    if (CWorld::ProcessVerticalLine(vecPos, fHeight, colPoint,
                                    pEntity, true, false,
                                    false, false, false,
                                    false, nullptr))
    {
        const auto fDayNight = colPoint.m_nLightingB.GetCurrentLighting();
        m_fContactSurfaceBrightness = lerp(m_fContactSurfaceBrightness, fDayNight, CTimer::GetTimeStep() / 10.0F);
    }
}

bool CCutsceneObject::SetupLighting()
{
    return CCutsceneObject::SetupLighting_Reversed();
}
bool CCutsceneObject::SetupLighting_Reversed()
{
    ActivateDirectional();
    return CRenderer::SetupLightingForEntity(this);
}

void CCutsceneObject::RemoveLighting(bool bRemove)
{
    return CCutsceneObject::RemoveLighting_Reversed(bRemove);
}
void CCutsceneObject::RemoveLighting_Reversed(bool bRemove)
{
    if (!physicalFlags.bDestroyed)
        CPointLights::RemoveLightsAffectingObject();

    SetAmbientColours();
    DeActivateDirectional();
}

void CCutsceneObject::SetupCarPipeAtomicsForClump(unsigned modelId, RpClump* pClump)
{
    static bool bCarPipeAtomicsInitialized = false;
    static uint32 anHashKeys[NUM_CUTSCENE_VEHS];

    if (!bCarPipeAtomicsInitialized)
    {
        bCarPipeAtomicsInitialized = true;
        for (auto i = 0; i < NUM_CUTSCENE_VEHS; ++i)
            anHashKeys[i] = CKeyGen::GetUppercaseKey(CCutsceneObject::ms_sCutsceneVehNames[i]);
    }

    for (auto anHashKey : anHashKeys)
    {
        if (CModelInfo::GetModelInfo(modelId)->m_nKey == anHashKey)
        {
            RpClumpForAllAtomics(pClump, CCutsceneObject::SetupCarPipeAtomicCB, nullptr);
            return;
        }
    }
}

RpAtomic* CCutsceneObject::SetupCarPipeAtomicCB(RpAtomic* pAtomic, void* data)
{
    CCarFXRenderer::CustomCarPipeAtomicSetup(pAtomic);
    return pAtomic;
}
